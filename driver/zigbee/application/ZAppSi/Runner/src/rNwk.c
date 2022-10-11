/**************************************************************************//**
  \file  rNwk.c

  \brief Nwk related commands Implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    14/09/2009  Daniil Kasyanov - Created.
  Last change:
    $Id: rNwk.c 32998 2019-04-29 05:54:31Z I41664 $ 
******************************************************************************/
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <nwk/include/nwk.h>
#include <rTypes.h>
#include <rMem.h>
#include <rExtensions.h>
#include <ZAppSiIdentifiers.h>
#include <systemenvironment/include/sysUtils.h>
#include <systemenvironment/include/sysEndian.h>
#include <bufferallocator.h>
#include <nwk/include/nwkProfiler.h>
#include <nwk/include/nwkEndDeviceTimeout.h>
#include <aps/include/apsAIB.h>
#include <security/TrustCentre/include/tcPermissions.h>

/******************************************************************************
                   Implementations section
 ******************************************************************************/
static void rNwkDiscoveryConfirm(NWK_NetworkDiscoveryConf_t *conf)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkNetworkDiscoveryConf_t *rConf = (RNwkNetworkDiscoveryConf_t *) confirmBuffer->commandFrame.payload;

  if (NULL != confirmBuffer)
  {
    confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + R_MIN_NWK_DISC_PAYLOAD_SIZE;
    confirmBuffer->commandFrame.length += conf->networkCount * sizeof(NWK_NetworkDescriptor_t);
    confirmBuffer->commandFrame.commandId = R_NLME_NETWORK_DISCOVERY_CONFIRM;
    rConf->status = conf->status;
    rConf->networkCount = conf->networkCount;

    SYS_BYTE_MEMCPY(GET_FIELD_PTR(rConf, RNwkNetworkDiscoveryConf_t, descr),
                    conf->networkDescriptors,
                    conf->networkCount * sizeof(NWK_NetworkDescriptor_t));

    serialManager.write(confirmBuffer);
  }

  rFreeMem(conf);
}

void rNwkDiscoveryRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RNwkDiscovery_t *nwkReq = (RNwkDiscovery_t *) rGetMem();
  RNwkNetworkDiscoveryReq_t *rReq = (RNwkNetworkDiscoveryReq_t *) commandBuffer->commandFrame.payload;
  NWK_NetworkDiscoveryReq_t *req;

  nwkReq->req.scanDuration = rReq->duration;
  nwkReq->req.scanChannels = LE32_TO_CPU(rReq->channels);
  nwkReq->req.NWK_NetworkDiscoveryConf = rNwkDiscoveryConfirm;
  nwkReq->req.confirm.networkDescriptors = (NWK_NetworkDescriptor_t *)GET_FIELD_PTR(
    nwkReq, RNwkDiscovery_t, descr);
  nwkReq->req.confirm.maxNetworkDescr = R_MAX_NETWORK_DESCRIPTORS;
  nwkReq->req.clearNeighborTable = rReq->clearNeighborTable;
  req = (NWK_NetworkDiscoveryReq_t *)GET_FIELD_PTR(
    nwkReq, RNwkDiscovery_t, req);
  NWK_NetworkDiscoveryReq(req);
}

void rNwkAddrResolvRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RNwkAddrResolvReq_t *req = (RNwkAddrResolvReq_t *) commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkAddrResolvConf_t *conf = (RNwkAddrResolvConf_t *) confirmBuffer->commandFrame.payload;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RNwkAddrResolvConf_t);
  confirmBuffer->commandFrame.commandId = R_NWK_ADDR_RESOLV_CONFIRM;
  if (NWK_NO_SHORT_ADDR == req->shortAddr)
  {
    ExtAddr_t extAddr = req->extAddr;
    const ShortAddr_t *shortAddr =  NWK_GetShortByExtAddress(&extAddr);

    if (NULL != shortAddr)
      conf->shortAddr = *shortAddr;
    else
      conf->shortAddr = NWK_NO_SHORT_ADDR;
    conf->extAddr = req->extAddr;
  }
  else
  {
    const ExtAddr_t *extAddr = NWK_GetExtByShortAddress(req->shortAddr);

    if (NULL != extAddr)
      conf->extAddr = *extAddr;
    else
      conf->extAddr = 0x0ULL;

    conf->shortAddr = req->shortAddr;
  }
  serialManager.write(confirmBuffer);
}
static void rNwkLeaveConfirm(NWK_LeaveConf_t *conf)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  NWK_LeaveConf_t *rConf = (NWK_LeaveConf_t *) confirmBuffer->commandFrame.payload;

  if (NULL != confirmBuffer)
  {
    confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (uint8_t); //status
    confirmBuffer->commandFrame.commandId = R_NWK_LEAVE_CONFIRM;

    rConf->status = conf->status;
    serialManager.write(confirmBuffer);
  }

  rFreeMem(conf);
}

void rNwkLeaveRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  NWK_LeaveReq_t *nwkReq = (NWK_LeaveReq_t *) rGetMem();
  RNwkLeaveReq_t *req = (RNwkLeaveReq_t *)commandBuffer->commandFrame.payload;
  NWK_LeaveControl_t defaultValue = NWK_DEFINE_LEAVE_CONTROL_DEFAULT;

  nwkReq->deviceAddress = req->deviceAddress;
  nwkReq->leaveControl = defaultValue;
  nwkReq->noExtendedAddress = req->noExtendedAddress;
  nwkReq->rejoin = req->rejoin;
  nwkReq->removeChildren = req->removeChildren;
  if(nwkReq->noExtendedAddress)
    nwkReq->shortAddress = req->shortAddress;

  nwkReq->NWK_LeaveConf = rNwkLeaveConfirm;

  NWK_LeaveReq(nwkReq);
}

#if defined(_ROUTER_) || defined(_COORDINATOR_)
void rNwkGetNextHopRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RNwkNextHopReq_t *req = (RNwkNextHopReq_t *) commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkNextHopConf_t *conf = (RNwkNextHopConf_t *) confirmBuffer->commandFrame.payload;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ShortAddr_t);
  confirmBuffer->commandFrame.commandId = R_NWK_GET_NEXT_HOP_CONFIRM;
  conf->nextHopAddr = NWK_GetNextHop(req->dstAddr);
  serialManager.write(confirmBuffer);
}
#ifdef _CERTIFICATION_
#if defined _NWK_MESH_ROUTING_
void rNwkSetNextHopRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RNwkSetNextHopReq_t *req = (RNwkSetNextHopReq_t *) commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkSetNextHopConf_t *conf = (RNwkSetNextHopConf_t *) confirmBuffer->commandFrame.payload;
  
  NWK_UpdateNextHop(req->dstAddr,req->isGroupId,req->nextHopAddr,req->cost);
  
  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (RNwkSetNextHopConf_t);
  confirmBuffer->commandFrame.commandId = R_NWK_SET_NEXT_HOP_CONFIRM;
  conf->nextHopAddr = NWK_GetNextHop(req->dstAddr);
  if(conf->nextHopAddr == req->nextHopAddr)
  {
    conf->status = 0; // Success
  }
  else
  {
    conf->status = 1; // Failed
  }
  serialManager.write(confirmBuffer);
}
#endif //#if defined _NWK_MESH_ROUTING_
#endif //#ifdef _CERTIFICATION_

static void rNwkPermitJoiningConfirm(NWK_PermitJoiningConf_t *conf)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkPermitJoiningConfirm_t *rConf = (RNwkPermitJoiningConfirm_t *) confirmBuffer->commandFrame.payload;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (RNwkPermitJoiningConfirm_t);
  confirmBuffer->commandFrame.commandId = R_NLME_PERMIT_JOINING_CONFIRM;
  rConf->status = conf->status;

  serialManager.write(confirmBuffer);
  rFreeMem(conf);
}

void rNwkPermitJoiningRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  NWK_PermitJoiningReq_t *nwkReq = (NWK_PermitJoiningReq_t *) rGetMem();
  RNwkPermitJoiningRequest_t *rReq = (RNwkPermitJoiningRequest_t *) commandBuffer->commandFrame.payload;
  //Set to ConfigServer
  CS_WriteParameter(CS_PERMIT_DURATION_ID, &rReq->permitDuration);

  nwkReq->permitDuration = rReq->permitDuration;
  nwkReq->NWK_PermitJoiningConf = rNwkPermitJoiningConfirm;

  NWK_PermitJoiningReq(nwkReq);
}

#if defined _NWK_MESH_ROUTING_ || defined _NWK_MANY_TO_ONE_ROUTING_
static void rNwkRemotelyInitiatedRouteDiscoveryConf(NWK_RouteDiscoveryConf_t * conf)
{
  NWK_RouteDiscoveryReq_t *nwkReq = GET_STRUCT_BY_FIELD_POINTER(NWK_RouteDiscoveryReq_t, confirm, conf);
  RMemEntry_t *memEntry = GET_STRUCT_BY_FIELD_POINTER(RMemEntry_t, stackReq, nwkReq);
  APS_DataReq_t *apsReq = (APS_DataReq_t *) memEntry->link;
  CidRouteDiscoveryResponse_t *resp = (CidRouteDiscoveryResponse_t *) apsReq->asdu;

  resp->status = conf->status;

  APS_DataReq(apsReq);
  rFreeMem(conf);
}

void rNwkRemotelyInitiatedRouteDiscoveryRequestProcess(APS_DataInd_t *ind, uint8_t endpoint)
{
  CidRouteDiscoveryRequest_t *reqCommand;
  NWK_RouteDiscoveryReq_t *nwkReq;
  RMemEntry_t *memEntry;
  APS_DataReq_t *apsReq;

  if (sizeof (CidRouteDiscoveryRequest_t) == ind->asduLength)
  {
    reqCommand = (CidRouteDiscoveryRequest_t *) ind->asdu;

    if (0x00 != reqCommand->dstAddrMode)
    {
      apsReq = rMakeDataReqBasedOnInd(ind, CID_ROUTE_DISCOVERY_CONFIRM, sizeof (CidRouteDiscoveryResponse_t), endpoint);

      nwkReq = (NWK_RouteDiscoveryReq_t *) rGetMem();
      memEntry = GET_STRUCT_BY_FIELD_POINTER(RMemEntry_t, stackReq, nwkReq);
      memEntry->link = apsReq;

      nwkReq->NWK_RouteDiscoveryConf = rNwkRemotelyInitiatedRouteDiscoveryConf;
      nwkReq->dstAddrMode = (NWK_DstAddrMode_t) reqCommand->dstAddrMode;
      nwkReq->dstAddr = reqCommand->nwkAddress;
      nwkReq->radius = reqCommand->radius;
      nwkReq->noRouteCache = false;

      NWK_RouteDiscoveryReq(nwkReq);
    }
  }

  endpoint = endpoint; //Warning prevention
}

static void rNwkRouteDiscoveryConf(NWK_RouteDiscoveryConf_t * conf)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkRouteDiscoveryConf_t *rConf = (RNwkRouteDiscoveryConf_t *) confirmBuffer->commandFrame.payload;

  if (NULL != confirmBuffer)
  {
    confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RNwkRouteDiscoveryConf_t);
    confirmBuffer->commandFrame.commandId = R_NLME_ROUTE_DISCOVERY_CONFIRM;
    rConf->status = conf->status;
    rConf->networkStatusCode = conf->networkStatusCode;
    rConf->nextHop = conf->nextHop;

    serialManager.write(confirmBuffer);
  }

  rFreeMem(conf);
}

void rNwkRouteDiscoveryRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  NWK_RouteDiscoveryReq_t *nwkReq = (NWK_RouteDiscoveryReq_t *) rGetMem();
  RNwkRouteDiscoveryReq_t *rReq = (RNwkRouteDiscoveryReq_t *) commandBuffer->commandFrame.payload;

  if (NULL != nwkReq)
  {
    nwkReq->dstAddrMode = rReq->dstAddrMode;
    nwkReq->dstAddr = rReq->dstAddr;
    nwkReq->radius = rReq->radius;
    nwkReq->noRouteCache = rReq->noRouteCache;
    nwkReq->NWK_RouteDiscoveryConf = rNwkRouteDiscoveryConf;
    NWK_RouteDiscoveryReq(nwkReq);
  }
}

void rNwkSetRouteFailOrderProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RNwkSetRouteFailOrderReq_t *req = (RNwkSetRouteFailOrderReq_t *)commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkSetRouteFailOrderConf_t *conf = (RNwkSetRouteFailOrderConf_t *) confirmBuffer->commandFrame.payload;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (RNwkSetRouteFailOrderConf_t);
  confirmBuffer->commandFrame.commandId = R_NWK_SET_ROUTE_FAIL_ORDER_CONFIRM;

  conf->status = (uint8_t)NWK_SetFailRouteOrder(req->order);

  serialManager.write(confirmBuffer);
}

#if defined _CERTIFICATION_ && defined _NWK_FAST_ROUTE_DISCOVERY_
void rNwkSetFastRouteDiscoveryProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RNwkSetFastRouteDiscoveryReq_t *req = (RNwkSetFastRouteDiscoveryReq_t *)commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkSetFastRouteDiscoveryConf_t *conf = (RNwkSetFastRouteDiscoveryConf_t *) confirmBuffer->commandFrame.payload;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (RNwkSetFastRouteDiscoveryConf_t);
  confirmBuffer->commandFrame.commandId = R_NWK_SET_FAST_ROUTE_DISCOVERY_CONFIRM;

  NWK_FindAnyRouteAtFirstTime(req->fastRouteDiscovery);
  conf->status = 0U;

  serialManager.write(confirmBuffer);
}
#endif /* _CERTIFICATION_ and _NWK_FAST_ROUTE_DISCOVERY_ */
#endif /* _NWK_MESH_ROUTING_ or _NWK_MANY_TO_ONE_ROUTING_ */
#endif /* defined(_ROUTER_) || defined(_COORDINATOR_) */

static void rNwkResetConfirm(NWK_ResetConf_t *conf)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkResetConfirm_t *rConf = (RNwkResetConfirm_t *) confirmBuffer->commandFrame.payload;

  if (NULL != confirmBuffer)
  {
    confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RNwkResetConfirm_t);
    confirmBuffer->commandFrame.commandId = R_NLME_RESET_CONFIRM;
    rConf->status = conf->status;

    serialManager.write(confirmBuffer);
  }

  rFreeMem(conf);
}

void rNwkResetRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  NWK_ResetReq_t *nwkReq = (NWK_ResetReq_t *) rGetMem();

  (void)commandBuffer;

  if (NULL != nwkReq)
  {
    NWK_Init();

    nwkReq->NWK_ResetConf = rNwkResetConfirm;
    NWK_ResetReq(nwkReq);
  }
}

#if defined(_NWK_DIRECT_JOIN_) && defined(_FFD_)
static void rNwkDirectJoinConfirm(NWK_DirectJoinConf_t *conf)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkDirectJoinConf_t *rConf = (RNwkDirectJoinConf_t *) confirmBuffer->commandFrame.payload;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RNwkDirectJoinConf_t);
  confirmBuffer->commandFrame.commandId = R_NLME_DIRECT_JOIN_CONFIRM;
  rConf->status = conf->status;

  serialManager.write(confirmBuffer);

  rFreeMem(conf);
}

void rNwkDirectJoinRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  NWK_DirectJoinReq_t *nwkReq = rGetMem();
  RNwkDirectJoinReq_t *rReq = (RNwkDirectJoinReq_t *) commandBuffer->commandFrame.payload;

  if(NULL != nwkReq)
  {
    nwkReq->NWK_DirectJoinConf = rNwkDirectJoinConfirm;
    nwkReq->capabilityInformation = rReq->capabilityInformation;
    nwkReq->deviceAddress = rReq->deviceAddress;
    nwkReq->networkAddress = rReq->networkAddress;
    NWK_DirectJoinReq(nwkReq);
  }
}
#endif //defined(_NWK_DIRECT_JOIN_ && _FFD_)

#if defined(_ROUTER_) || defined(_ENDDEVICE_)
static void rNwkJoinConfirm(NWK_JoinConf_t *conf)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkJoinConf_t *rConf = (RNwkJoinConf_t *) confirmBuffer->commandFrame.payload;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RNwkJoinConf_t);
  confirmBuffer->commandFrame.commandId = R_NLME_JOIN_CONFIRM;
  rConf->status = conf->status;
  rConf->networkAddress = conf->networkAddress;
  rConf->extendedPANId = conf->extendedPANId;
  rConf->activeChannel = conf->activeChannel;
  serialManager.write(confirmBuffer);

  rFreeMem(conf);
}

void rNwkJoinRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  NWK_JoinReq_t *nwkReq = rGetMem();
  RNwkJoinReq_t *rReq = (RNwkJoinReq_t *) commandBuffer->commandFrame.payload;

  if(NULL != nwkReq)
  {
    nwkReq->NWK_JoinConf = rNwkJoinConfirm;
    nwkReq->extendedPANId = rReq->extendedPANId;
    nwkReq->ctrl.method = (NWK_JoinMethod_t)rReq->method;
    nwkReq->scanChannels = LE32_TO_CPU(rReq->scanChannels);
    nwkReq->scanDuration = rReq->scanDuration;
    nwkReq->ctrl.secured = rReq->securityEnable;
    nwkReq->ctrl.discoverNetworks = true;
    NWK_JoinReq(nwkReq);
  }
}
#endif // defined(_ROUTER_) || defined(_ENDDEVICE_)

#if defined(_ROUTER_)
static void rNwkStartRouterConfirm(NWK_StartRouterConf_t *conf)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkStartRouterConf_t *rConf = (RNwkStartRouterConf_t *) confirmBuffer->commandFrame.payload;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RNwkStartRouterConf_t);
  confirmBuffer->commandFrame.commandId = R_NLME_START_ROUTER_CONFIRM;
  rConf->status = conf->status;
  serialManager.write(confirmBuffer);

  rFreeMem(conf);
}

void rNwkStartRouterRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  NWK_StartRouterReq_t *req = rGetMem();

  (void)commandBuffer;
  if(NULL != req)
  {
    req->NWK_StartRouterConf = rNwkStartRouterConfirm;
    NWK_StartRouterReq(req);
  }
}
#endif // defined(_ROUTER_)
#if defined _PROFILER_
void rNwkProfilerRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  NWK_ProfilingInfo_t *conf = (NWK_ProfilingInfo_t *) confirmBuffer->commandFrame.payload;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (NWK_ProfilingInfo_t);
  confirmBuffer->commandFrame.commandId = R_NWK_PROFILER_CONFIRM;

  NWK_CollectProfilingInfo();
  memcpy(conf, &nwkProfilingInfo, sizeof(NWK_ProfilingInfo_t));

  serialManager.write(confirmBuffer);
  (void)commandBuffer;
}
#endif /* _PROFILER_ */

void rNwkSetShortAddressRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RNwkSetShortAddressReq_t *rReq = (RNwkSetShortAddressReq_t *) commandBuffer->commandFrame.payload;

  NWK_SetShortAddr(rReq->address, rReq->silent);
}

#ifdef _SECURITY_
void rNwkGetOutSecurityCounterRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkGetOutSecurityCounterConf_t *conf =
    (RNwkGetOutSecurityCounterConf_t *)confirmBuffer->commandFrame.payload;

  conf->outCounter = NWK_GetSecOutCounter();

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RNwkGetOutSecurityCounterConf_t);
  confirmBuffer->commandFrame.commandId = R_NWK_GET_OUT_SEC_COUNTER_CONFIRM;

  serialManager.write(confirmBuffer);
  (void)commandBuffer;
}

void rNwkSetOutgoingSecFrameCounter(ZS_CommandBuffer_t *commandBuffer)
{
  RNwkSetOutSecurityCounterReq_t *rReq = (RNwkSetOutSecurityCounterReq_t *) commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkSetOutSecurityCounterConf_t *conf =
    (RNwkSetOutSecurityCounterConf_t *)confirmBuffer->commandFrame.payload;
  NwkOutFrameCounterHandle_t nwkOutFrameCounter;

  nwkOutFrameCounter.value = rReq->outCounter;
  conf->status = NWK_SetSecOutCounter(&nwkOutFrameCounter);
  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RNwkSetOutSecurityCounterConf_t);
  confirmBuffer->commandFrame.commandId = R_NWK_SET_OUT_SEC_COUNTER_CONFIRM;

  serialManager.write(confirmBuffer);
}

void rNwkGetActiveKeySeqNum(ZS_CommandBuffer_t *commandBuffer)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkGetActiveKeySeqNumConf_t *conf =
    (RNwkGetActiveKeySeqNumConf_t *)confirmBuffer->commandFrame.payload;

  conf->keySeqNum = NWK_GetActiveKeySeqNumber();
  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RNwkGetActiveKeySeqNumConf_t);
  confirmBuffer->commandFrame.commandId = R_NWK_SET_ACTIVE_KEY_SEQ_NUM_CONFIRM;

  serialManager.write(confirmBuffer);
  (void)commandBuffer;
}


#ifdef _NWK_IN_FRAME_COUNTERS_
void rNwkSetInSecurityCounterRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RNwkSetInSecurityCounterReq_t *rReq = (RNwkSetInSecurityCounterReq_t *) commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkSetInSecurityCounterConf_t *conf =
    (RNwkSetInSecurityCounterConf_t *)confirmBuffer->commandFrame.payload;

  ExtAddr_t srcExtAddr = rReq->extAddr;
  NwkInFrameCounter_t counter = rReq->newValue;
  
  NWK_SetInFrameCounter(NWK_GetActiveKeySeqNumber(), &srcExtAddr, &counter);
  

  conf->status = 0U;
  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RNwkSetInSecurityCounterConf_t);
  confirmBuffer->commandFrame.commandId = R_NWK_SET_IN_SEC_COUNTER_CONFIRM;

  serialManager.write(confirmBuffer);
}

void rNwkGetInSecurityCounterRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RNwkGetInSecurityCounterReq_t *rReq = (RNwkGetInSecurityCounterReq_t *) commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkGetInSecurityCounterConf_t *conf =
    (RNwkGetInSecurityCounterConf_t *)confirmBuffer->commandFrame.payload;

  ExtAddr_t srcExtAddr = rReq->extAddr;
  NwkInFrameCounter_t counter = 0ul;
  
  conf->status = NWK_GetSecInCounter(&srcExtAddr, &counter) ? 1U : 0U;
  conf->currentValue = counter;
  
  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RNwkGetInSecurityCounterConf_t);
  confirmBuffer->commandFrame.commandId = R_NWK_GET_IN_SEC_COUNTER_CONFIRM;

  serialManager.write(confirmBuffer);
}
#endif /* _NWK_IN_FRAME_COUNTERS_ */

#if defined (_LINK_SECURITY_) && defined (_TRUST_CENTRE_)
void rTCPolicySetRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  APS_TCSecurityPolicy_t *rReq = (APS_TCSecurityPolicy_t *) commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RTcPolicySetConf_t *conf =
    (RTcPolicySetConf_t *)confirmBuffer->commandFrame.payload;

  //Initialize TC policy
  TC_InitializePolicy(rReq);

  //Send confirmation
  conf->status = 0;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RTcPolicySetConf_t);
  confirmBuffer->commandFrame.commandId = R_TC_POLICY_REQUEST_CONF;

  serialManager.write(confirmBuffer);
}
#endif //#if defined (_LINK_SECURITY_) && defined (_TRUST_CENTRE_)
#endif /* _SECURITY_ */

#ifdef _CHILD_MANAGEMENT_
#if 0
static void NWK_EndDeviceTimeoutConf(NWK_EndDeviceTimeoutConf_t *conf)
{

  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkEndDeviceTimeoutConf_t *rConf = (RNwkEndDeviceTimeoutConf_t *)confirmBuffer->commandFrame.payload;

  if (confirmBuffer)
  {
    confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RNwkEndDeviceTimeoutConf_t);
    confirmBuffer->commandFrame.commandId = R_NWK_END_DEVICE_TIMEOUT_CONFIRM;
    rConf->status = conf->status;

    serialManager.write(confirmBuffer);
  }

  rFreeMem(conf);
}
#endif  

#if 1
void rNwkEndDeviceTimeoutRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
#if 0
  RNwkEndDeviceTimeoutReq_t *rReq = (RNwkEndDeviceTimeoutReq_t *)commandBuffer->commandFrame.payload;
  NWK_EndDeviceTimeoutReq_t *req = (NWK_EndDeviceTimeoutReq_t *)rGetMem();

  req->timeout = rReq->timeout;
  req->endDeviceConfiguration = rReq->endDeviceConfiguration;
  req->NWK_EndDeviceTimeoutConf = NWK_EndDeviceTimeoutConf;
  
  NWK_EndDeviceTimeoutReq(req);
#else
  (void) commandBuffer;
#endif  
}
#endif

void NWK_EndDeviceTimeoutInd(NWK_EndDeviceTimeoutInd_t *ind)
{
#if 0
  ZS_CommandBuffer_t *indBuffer = bufferAllocator.allocate();
  RNwkEndDeviceTimeoutReqInd_t *rInd = (RNwkEndDeviceTimeoutReqInd_t *)indBuffer->commandFrame.payload;

  if (indBuffer)
  {
    indBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RNwkEndDeviceTimeoutReqInd_t);
    indBuffer->commandFrame.commandId = R_NWK_END_DEVICE_TIMEOUT_REQ_IND;
    rInd->addr = ind->networkAddress;
    rInd->timeout = ind->timeout;
    rInd->endDeviceConfiguration = ind->endDeviceConfiguration;
    rInd->parentInformation = ind->parentInformation;

    serialManager.write(indBuffer);
  }
#else
  (void) ind;
#endif
}
#endif /* _CHILD_MANAGEMENT_ */

void rNwkAddAddressMapReqProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RNwkAddressMapEntryReq_t *rReq = (RNwkAddressMapEntryReq_t *) commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkAddressMapEntryConf_t *conf =
    (RNwkAddressMapEntryConf_t *)confirmBuffer->commandFrame.payload;

  NWK_LinkShortAndExtAddress(rReq->shortAddr, rReq->extAddr);

  conf->status = 0U;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RNwkAddressMapEntryConf_t);
  confirmBuffer->commandFrame.commandId = R_NWK_ADD_ADDRESSMAP_ENTRY_CONF;

  serialManager.write(confirmBuffer);
}

void rNwkRemoveNeighborEntryProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RNwkRemoveNeighborEntryReq_t *rReq = (RNwkRemoveNeighborEntryReq_t *) commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkRemoveNeighborEntryConf_t *conf =
    (RNwkRemoveNeighborEntryConf_t *)confirmBuffer->commandFrame.payload;
  NwkNeighbor_t* neighbor;

  if (rReq->useExtAddr)
  {
    neighbor = NWK_FindNeighborByExtAddr(rReq->extAddr);
  }
  else
  {
    neighbor = NWK_FindNeighborByShortAddr(rReq->shortAddr);
  }

  if (neighbor)
    NWK_RemoveNeighbor(neighbor, true, false, false);

  if (rReq->useExtAddr)
  {
    neighbor = NWK_FindNeighborByExtAddr(rReq->extAddr);
  }
  else
  {
    neighbor = NWK_FindNeighborByShortAddr(rReq->shortAddr);
  }

  if (NULL == neighbor)
    conf->status = 0U;
  else
    conf->status = 1U;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RNwkRemoveNeighborEntryConf_t);
  confirmBuffer->commandFrame.commandId = R_NWK_REMOVE_NEIGHBOR_ENTRY_CONF;
  serialManager.write(confirmBuffer);
}
#if defined _ROUTER_ || defined _COORDINATOR_
void rNwkSetEDTimeoutByParentProcess(ZS_CommandBuffer_t *commandBuffer)
{
  uint8_t  status = false;
  RNwkSetEndDviceTimeout_t *rReq = (RNwkSetEndDviceTimeout_t *) commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RNwkSetEndDviceTimeoutConf_t *conf =
    (RNwkSetEndDviceTimeoutConf_t *)confirmBuffer->commandFrame.payload;
  status = NWK_SetEndDeviceTimeoutByParent(rReq->extAddr, rReq->edTimeout);

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RNwkSetEndDviceTimeoutConf_t);
  confirmBuffer->commandFrame.commandId = R_NWK_SET_ED_TIMEOUT_BY_PARENT_CONFIRM;
  conf->status = status;
  serialManager.write(confirmBuffer);
}
#endif

/* eof rNwk.c */
