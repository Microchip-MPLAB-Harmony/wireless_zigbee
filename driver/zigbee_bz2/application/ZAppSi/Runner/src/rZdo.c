/**************************************************************************//**
  \file  rZdo.c

  \brief Zdo commands Implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <zdo/include/zdo.h>
#include <rMem.h>
#include <rDebug.h>
#include <rAps.h>
#include <ZAppSiIdentifiers.h>
#include <ZAppSiCommands.h>
#include <systemenvironment/include/sysUtils.h>
#include <bufferallocator.h>
#include <zdo/include/zdoSecurityManager.h>

/*****************************************************************************
                               Definitions section
******************************************************************************/
#ifndef APP_EXTENDED_ZDP_REQUEST
#define APP_EXTENDED_ZDP_REQUEST   1
#endif

#ifdef _STACK_INTERNAL_TEST_FRAMEWORK_
static void zdoReqCmdRxdHandler(SYS_EventId_t eventId, SYS_EventData_t data);

SYS_EventReceiver_t zdoReqCmdRxdReceiver = {  .func = zdoReqCmdRxdHandler };

static void zdoReqCmdValidationHandler(SYS_EventId_t eventId, SYS_EventData_t data);

SYS_EventReceiver_t zdoReqCmdValidation = {  .func = zdoReqCmdValidationHandler };

static void zdoRspCmdValidationHandler(SYS_EventId_t eventId, SYS_EventData_t data);

SYS_EventReceiver_t zdoRspCmdValidation = {  .func = zdoRspCmdValidationHandler };
#endif
/******************************************************************************
                   Implementations section
 ******************************************************************************/
void rZdoGetNeibAmountProcess(ZS_CommandBuffer_t *commandBuffer)
{
  DeviceType_t deviceType;
  ZDO_GetNeibAmount_t zdoGetNeibAmount;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  ZS_ZdoGetNeibAmountConf_t *confirm = (ZS_ZdoGetNeibAmountConf_t *) confirmBuffer->commandFrame.payload;

  (void)commandBuffer;

  CS_ReadParameter(CS_DEVICE_TYPE_ID, &deviceType);
  ZDO_GetNeibAmount(&zdoGetNeibAmount);
  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdoGetNeibAmountConf_t);
  confirmBuffer->commandFrame.commandId = R_ZDO_GET_NEIB_AMOUNT_CONFIRM;
  confirm->routersAmount = zdoGetNeibAmount.routersAmount;
  confirm->enddevicesAmount = zdoGetNeibAmount.childrenAmount;
  serialManager.write(confirmBuffer);
}

void rZdoGetNeibTableProcess(ZS_CommandBuffer_t *commandBuffer)
{
  uint8_t i;
  ZDO_GetNeibAmount_t zdoGetNeibAmount;
  ZDO_Neib_t zdoNeib[CS_NEIB_TABLE_SIZE];
  ZS_CommandBuffer_t *confirmBuffer = (ZS_CommandBuffer_t *) bufferAllocator.allocate();
  uint8_t *recordsAmount = (uint8_t *) confirmBuffer->commandFrame.payload;
  ZS_ZdoGetNeibTableRecord_t *confirm = (ZS_ZdoGetNeibTableRecord_t *) (confirmBuffer->commandFrame.payload + sizeof (uint8_t));

  (void)commandBuffer;

  ZDO_GetNeibAmount(&zdoGetNeibAmount);
  zdoGetNeibAmount.childrenAmount += zdoGetNeibAmount.routersAmount; // Summary neibs amount
  ZDO_GetNeibTable(zdoNeib);

  *recordsAmount = zdoGetNeibAmount.childrenAmount;
  for (i = 0; i < zdoGetNeibAmount.childrenAmount; i++)
  {
    confirm[i].shortAddr = zdoNeib[i].shortAddr;
    confirm[i].extAddr = zdoNeib[i].extAddr;
    confirm[i].deviceType = zdoNeib[i].deviceType;
    confirm[i].lqi = zdoNeib[i].lqi;
    confirm[i].rssi = zdoNeib[i].rssi;
  }

  confirmBuffer->commandFrame.commandId = R_ZDO_GET_NEIB_TABLE_CONFIRM;
  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (uint8_t) + zdoGetNeibAmount.childrenAmount * sizeof(ZS_ZdoGetNeibTableRecord_t);

  serialManager.write(confirmBuffer);
}

static void rZdoMgmtLeaveResponse(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdoMgmtLeaveConf_t *rConf = (ZS_ZdoMgmtLeaveConf_t *) confBuffer->commandFrame.payload;
  confBuffer->commandFrame.commandId = R_ZDO_MGMT_LEAVE_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdoMgmtLeaveConf_t);

  SYS_BYTE_MEMCPY(&rConf->status, &conf->respPayload.status, sizeof (uint8_t));
  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdoMgmtLeaveRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ExtAddr_t tempDstAddr;
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_MgmtLeaveReq_t *zdpReq = &zdpClientReq->req.reqPayload.mgmtLeaveReq;
  ZS_ZdoMgmtLeaveReq_t *rReq = (ZS_ZdoMgmtLeaveReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdoMgmtLeaveResponse;
  zdpClientReq->reqCluster = MGMT_LEAVE_CLID;
  zdpClientReq->dstAddrMode = APS_EXT_ADDRESS;

  tempDstAddr = rReq->dstAddr;
  COPY_EXT_ADDR_A(zdpClientReq->dstAddress.extAddress, &tempDstAddr);
  tempDstAddr = rReq->deviceAddr;
  COPY_EXT_ADDR_A(zdpReq->deviceAddr, &tempDstAddr);
  zdpReq->rejoin = rReq->rejoin;
  zdpReq->removeChildren = rReq->removeChildren;
  zdpReq->reserved = 0;

  ZDO_ZdpReq(zdpClientReq);

}

void rZdoMgmtNwkUpdateNotifyProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  ZDO_MgmtNwkUpdateNotf_t *req = (ZDO_MgmtNwkUpdateNotf_t *) commandBuffer->commandFrame.payload;
  //ZS_MgmtNwkUpdateNotf_t *confirm = NULL; // = (RZdoMgmtNwkUpdateNotify_t *) confirmBuffer->commandFrame.payload;
  ZS_MgmtNwkUpdateNotf_t *confirm = (ZS_MgmtNwkUpdateNotf_t *) confirmBuffer->commandFrame.payload;
  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(confirm->status);
  confirm->status = req->status;

  switch (req->status)
  {
    case ZDO_SUCCESS_STATUS:
    {
      confirmBuffer->commandFrame.length += sizeof(EDScan_t);
      confirm->scanResult = req->scanResult;
    }
    break;

    case ZDO_CHILD_JOINED_STATUS:
    case ZDO_NO_KEY_PAIR_DESCRIPTOR_STATUS:
    {
      confirmBuffer->commandFrame.length += sizeof(confirm->childInfo);
      confirm->childInfo = req->childInfo;
    }
    break;

    case ZDO_CHILD_REMOVED_STATUS:
    {
      confirmBuffer->commandFrame.length += sizeof(confirm->childAddr);
      confirm->childAddr = req->childAddr;
    }
    break;

    case ZDO_NWK_UPDATE_STATUS:
    case ZDO_NETWORK_STARTED_STATUS:
    case ZDO_NETWORK_LOST_STATUS:
    case ZDO_NETWORK_LEFT_STATUS:
    {
      if (ZDO_NETWORK_LEFT_STATUS == req->status)
      {
        ExtPanId_t extPanId;
        CS_ReadParameter(CS_NWK_EXT_PANID_ID,&extPanId);
        CS_WriteParameter(CS_EXT_PANID_ID, &extPanId);
      }
      confirmBuffer->commandFrame.length += sizeof(confirm->nwkUpdateInf);
      confirm->nwkUpdateInf = req->nwkUpdateInf;
    }
    break;

    case ZDO_USER_DESCRIPTOR_UPDATE_STATUS:
    case ZDO_TC_NOT_AVAILABLE_STATUS:
    case ZDO_INVALID_REQUEST_STATUS:
      // No additional parameters
    break;

    case ZDO_STATIC_ADDRESS_CONFLICT_STATUS:
    {
      confirmBuffer->commandFrame.length += sizeof(confirm->conflictAddress);
      confirm->conflictAddress = req->conflictAddress;
    }
    break;

    case ZDO_UPDATE_LINK_KEY_STATUS:
    case ZDO_UPDATE_MASTER_KEY_STATUS:
    case ZDO_DELETE_KEY_PAIR_STATUS:
    case ZDO_DELETE_LINK_KEY_STATUS:
    {
      confirmBuffer->commandFrame.length += sizeof(confirm->deviceExtAddr);
      confirm->deviceExtAddr = req->deviceExtAddr;
    }
    break;

    default:
      confirmBuffer->commandFrame.length = 0;
      rAssert(false, R_DBG_USART_NO_BUFFERS);
    break;
  }
  confirmBuffer->commandFrame.commandId = R_ZDO_MGMT_NWK_UPDATE_NOTIFY;

  serialManager.write(confirmBuffer);
}

static void rZdoNwkAddrConfirm(ZDO_ZdpResp_t *conf)
{
  ZDO_NwkAddrResp_t *zdpConf = (ZDO_NwkAddrResp_t *) & conf->respPayload.nwkAddrResp;
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdoNwkAddrConf_t *rConf = (ZS_ZdoNwkAddrConf_t *) confBuffer->commandFrame.payload;

  confBuffer->commandFrame.commandId = R_ZDO_NWK_ADDR_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE
    + sizeof (ZS_ZdoNwkAddrConf_t)
    - sizeof(ShortAddr_t) * (ZDP_ADDR_LIST_SIZE - zdpConf->numAssocDev);

  memcpy(&rConf->status, &conf->respPayload.status, sizeof(uint8_t));
  //rConf->status = conf->respPayload.status;
  rConf->resp = *zdpConf;

  if (APP_MAX_COMMAND_PAYLOAD_SIZE >= (confBuffer->commandFrame.length - R_COMMAND_ID_SIZE))
    serialManager.write(confBuffer);
  else
    //Error1 (maximum command payload size is reached)
    confBuffer->state = R_BUFFER_FREE_STATE;

  rFreeMem(conf);
}

void rZdoNwkAddrRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = rGetMem();
  ZDO_NwkAddrReq_t *zdpReq = &zdpClientReq->req.reqPayload.nwkAddrReq;
  ZS_ZdoNwkAddrReq_t *rReq = (ZS_ZdoNwkAddrReq_t *) commandBuffer->commandFrame.payload;
  zdpClientReq->ZDO_ZdpResp = rZdoNwkAddrConfirm;

  zdpClientReq->reqCluster = NWK_ADDR_CLID;

  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->dstAddr;

  *zdpReq = rReq->req;

  ZDO_ZdpReq(zdpClientReq);
}

static void rZdoPermitJoiningResponse(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdoMgmtPermitJoiningConf_t *rConf = (ZS_ZdoMgmtPermitJoiningConf_t *) confBuffer->commandFrame.payload;

  confBuffer->commandFrame.commandId = R_ZDO_MGMT_PERMIT_JOINING_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdoMgmtPermitJoiningConf_t);

  SYS_BYTE_MEMCPY(&rConf->status, &conf->respPayload.status, sizeof (uint8_t));
  serialManager.write(confBuffer);

  rFreeMem(conf);
}

void rZdoMgmtPermitJoiningRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_MgmtPermitJoiningReq_t *zdpReq = &zdpClientReq->req.reqPayload.mgmtPermitJoiningReq;
  ZS_ZdoMgmtPermitJoiningReq_t *rReq = (ZS_ZdoMgmtPermitJoiningReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdoPermitJoiningResponse;
  zdpClientReq->reqCluster = MGMT_PERMIT_JOINING_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->dstShortAddress;

  SYS_BYTE_MEMCPY(&zdpReq->permitDuration, &rReq->permitDuration, sizeof (uint8_t));
  SYS_BYTE_MEMCPY(&zdpReq->tcSignificance, &rReq->tcSignificance, sizeof (uint8_t));

  ZDO_ZdpReq(zdpClientReq);
}

static void rZdoSetTxPowerConfirm(ZDO_SetTxPowerConf_t *conf)
{
  ZS_CommandBuffer_t *dataBuffer = bufferAllocator.allocate();

  ZS_ZdoSetTxPowerConf_t *payload = (ZS_ZdoSetTxPowerConf_t *) dataBuffer->commandFrame.payload;

  dataBuffer->commandFrame.commandId = R_ZDO_SET_TX_POWER_CONFIRM;

  payload->status = conf->status;

  serialManager.write(dataBuffer);
  rFreeMem(conf);
  dataBuffer->state = R_BUFFER_FREE_STATE;
}

void rZdoSetTxPowerRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_SetTxPowerReq_t *setReq = (ZDO_SetTxPowerReq_t *) rGetMem();
  ZS_ZdoSetTxPowerReq_t *req = (ZS_ZdoSetTxPowerReq_t *) commandBuffer->commandFrame.payload;

  setReq->txPower = req->txPower;
  setReq->ZDO_SetTxPowerConf = rZdoSetTxPowerConfirm;

  ZDO_SetTxPowerReq(setReq);
}

void rZdoWakeupIndicationProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();

  (void)commandBuffer;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE;
  confirmBuffer->commandFrame.commandId = R_ZDO_WAKEUP_INDICATION;
  serialManager.write(confirmBuffer);
}

static void rZdoSleepConfirm(ZDO_SleepConf_t *conf)
{
  uint8_t status;

  status = (uint8_t) (conf->status);
  uint32_t sleepPeriod;

  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  ZS_ZdoSleepConf_t *confirm = (ZS_ZdoSleepConf_t *) confirmBuffer->commandFrame.payload;

  CS_ReadParameter(CS_END_DEVICE_SLEEP_PERIOD_ID, &sleepPeriod);

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdoSleepConf_t);
  confirmBuffer->commandFrame.commandId = R_ZDO_SLEEP_CONFIRM;
  confirm->sleepPeriod = sleepPeriod;
  confirm->status = status;

  serialManager.write(confirmBuffer);
  rFreeMem(conf);
}

void rZdoSleepRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZS_ZdoSleepReq_t const *zsZdoSleepReq = (ZS_ZdoSleepReq_t*) commandBuffer->commandFrame.payload;
  uint32_t leSleepPeriod;
  uint32_t sleepPeriod;
  DeviceType_t deviceType;

  ZDO_SleepReq_t *sleepReq = (ZDO_SleepReq_t *) rGetMem();
  leSleepPeriod = zsZdoSleepReq->sleepPeriod;
  sleepPeriod = LE32_TO_CPU(leSleepPeriod);

  CS_ReadParameter(CS_DEVICE_TYPE_ID, &deviceType);
  if (DEVICE_TYPE_END_DEVICE == deviceType)
  {
    CS_WriteParameter(CS_END_DEVICE_SLEEP_PERIOD_ID, &sleepPeriod);
  }
  else
  {
    CS_WriteParameter(CS_FFD_SLEEP_PERIOD_ID, &sleepPeriod);
  }

  sleepReq->ZDO_SleepConf = rZdoSleepConfirm;

  ZDO_SleepReq(sleepReq);

}

#ifdef _ENDDEVICE_
void rZdoStartSyncReqProcess(ZS_CommandBuffer_t *commandBuffer)
{


  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  ZDO_Status_t status = ZDO_StartSyncReq();

  (void)commandBuffer;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (uint8_t);
  confirmBuffer->commandFrame.commandId = R_ZDO_START_SYNC_CONFIRM;
  *(uint8_t *) (confirmBuffer->commandFrame.payload) = (uint8_t) status;

  serialManager.write(confirmBuffer);
}

void rZdoStopSyncReqProcess(ZS_CommandBuffer_t *commandBuffer)
{


  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  ZDO_Status_t status = ZDO_StopSyncReq();

  (void)commandBuffer;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (uint8_t);
  confirmBuffer->commandFrame.commandId = R_ZDO_STOP_SYNC_CONFIRM;
  *(uint8_t *) (confirmBuffer->commandFrame.payload) = (uint8_t) status;

  serialManager.write(confirmBuffer);
}

#endif /* _ENDDEVICE_ */
#if APP_ZDP_REQUESTS
#if APP_EXTENDED_ZDP_REQUEST == 1
static void rZdoNodeDescResponse(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdoNodeDescConf_t *rConf = (ZS_ZdoNodeDescConf_t *) confBuffer->commandFrame.payload;
  ZDO_NodeDescResp_t *zdpRsp = &conf->respPayload.nodeDescResp;

  confBuffer->commandFrame.commandId = R_ZDO_NODE_DESC_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdoNodeDescConf_t);

  //rConf->deviceAddress = 0xffffffffffffffffLL;  //FIXME!!! Workaround

  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpRsp;

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdoNodeDescRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_NodeDescReq_t *zdpReq = &zdpClientReq->req.reqPayload.nodeDescReq;
  ZS_ZdoNodeDescReq_t *rReq = (ZS_ZdoNodeDescReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdoNodeDescResponse;
  zdpClientReq->reqCluster = NODE_DESCRIPTOR_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->destAddr;

  zdpReq->nwkAddrOfInterest = rReq->nwkAddrOfInterest;

  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpPowerDescConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpPowerDescConf_t *rConf = (ZS_ZdpPowerDescConf_t *) confBuffer->commandFrame.payload;
  ZDO_PowerDescResp_t *zdpResp = &conf->respPayload.powerDescResp;

  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDO_POWER_DESC_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpPowerDescConf_t);

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpPowerDescRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_PowerDescReq_t *powerDescReq = &zdpClientReq->req.reqPayload.powerDescReq;
  ZS_ZdpPowerDescReq_t *rReq = (ZS_ZdpPowerDescReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdpPowerDescConfirm;
  zdpClientReq->reqCluster = POWER_DESCRIPTOR_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;
  powerDescReq->nwkAddrOfInterest = rReq->nwkAddrOfInterest;

  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpSimpleDescConfirm(ZDO_ZdpResp_t *conf)
{
  uint8_t i;
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RZdpSimpleDescConfirm_t *rConf = (RZdpSimpleDescConfirm_t *) confBuffer->commandFrame.payload;
  ZDO_SimpleDescResp_t *zdpResp = &conf->respPayload.simpleDescResp;
  RZdpClustersList_t *clusterList = (RZdpClustersList_t *)GET_FIELD_PTR(rConf, RZdpSimpleDescConfirm_t, simpleDescriptor.clusterLists);

  rConf->status = conf->respPayload.status;
  rConf->nwkAddrOfInterest = zdpResp->nwkAddrOfInterest;
  rConf->length = zdpResp->length;

  rConf->simpleDescriptor.endpoint = zdpResp->simpleDescriptor.endpoint;
  rConf->simpleDescriptor.appProfileId = zdpResp->simpleDescriptor.AppProfileId;
  rConf->simpleDescriptor.appDeviceId = zdpResp->simpleDescriptor.AppDeviceId;
  rConf->simpleDescriptor.appDeviceVersion = zdpResp->simpleDescriptor.AppDeviceVersion;
  rConf->simpleDescriptor.reserved = zdpResp->simpleDescriptor.Reserved;

  clusterList->count = zdpResp->simpleDescriptor.AppInClustersCount;

  for (i = 0; i < zdpResp->simpleDescriptor.AppInClustersCount; i++)
  {
    clusterList->pIDs[i] = zdpResp->simpleDescriptor.AppInClustersList[i];
  }

  clusterList = (RZdpClustersList_t *)(GET_FIELD_PTR(rConf, RZdpSimpleDescConfirm_t, simpleDescriptor.clusterLists) +
                                       sizeof(RZdpClustersList_t) +
                                       sizeof(uint16_t) * zdpResp->simpleDescriptor.AppInClustersCount);

  clusterList->count = zdpResp->simpleDescriptor.AppOutClustersCount;

  for (i = 0; i < zdpResp->simpleDescriptor.AppOutClustersCount; i++)
  {
    clusterList->pIDs[i] = zdpResp->simpleDescriptor.AppOutClustersList[i];
  }

  confBuffer->commandFrame.commandId = R_ZDO_SIMPLE_DESC_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(uint8_t) + sizeof(ZDO_SimpleDescResp_t);//status

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpSimpleDescRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_SimpleDescReq_t *simpleDescReq = &zdpClientReq->req.reqPayload.simpleDescReq;
  ZS_ZdpSimpleDescReq_t *rReq = (ZS_ZdpSimpleDescReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdpSimpleDescConfirm;
  zdpClientReq->reqCluster = SIMPLE_DESCRIPTOR_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->dstAddr;

  simpleDescReq->nwkAddrOfInterest = rReq->nwkAddrOfInterest;
  simpleDescReq->endpoint = rReq->endpoint;

  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpActiveEPConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpActiveEPConf_t *rConf = (ZS_ZdpActiveEPConf_t *) confBuffer->commandFrame.payload;
  ZDO_ActiveEPResp_t *zdpResp = &conf->respPayload.activeEPResp;

  rConf->status = conf->respPayload.status;
  rConf->resp.nwkAddrOfInterest = zdpResp->nwkAddrOfInterest;
  rConf->resp.activeEPCount = zdpResp->activeEPCount;
  SYS_BYTE_MEMCPY(&rConf->resp.activeEPList, &zdpResp->activeEPList, sizeof (uint8_t) * zdpResp->activeEPCount);
  confBuffer->commandFrame.commandId = R_ZDO_ACTIVE_EP_DESC_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE
    + offsetof (ZS_ZdpActiveEPConf_t, resp.activeEPList)
    + zdpResp->activeEPCount;

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpActiveEPRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZS_ZdpActiveEPReq_t *const activeEPReq = (ZS_ZdpActiveEPReq_t *)(commandBuffer->commandFrame.payload);

  zdpClientReq->req.reqPayload.activeEPReq.nwkAddrOfInterest = activeEPReq->nwkAddrOfInterest;
  zdpClientReq->ZDO_ZdpResp = rZdpActiveEPConfirm;
  zdpClientReq->reqCluster = ACTIVE_ENDPOINTS_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
//  zdpClientReq->dstAddress.shortAddress = activeEPReq->nwkAddrOfInterest;
  zdpClientReq->dstAddress.shortAddress =  activeEPReq->dstAddr;

  ZDO_ZdpReq(zdpClientReq);
}

void rZdpComplexDescConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpComplexDescConf_t *rConf = (ZS_ZdpComplexDescConf_t *) confBuffer->commandFrame.payload;
  ZDO_ComplexDescResp_t *zdpResp = &conf->respPayload.complexDescResp;

  rConf->status = conf->respPayload.status;
  rConf->resp.nwkAddrOfInterest = zdpResp->nwkAddrOfInterest;
  confBuffer->commandFrame.commandId = R_ZDO_COMPLEX_DESC_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpComplexDescConf_t);

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpComplexDescRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_ComplexDescReq_t *complexDescReq = &zdpClientReq->req.reqPayload.complexDescReq;
  ZS_ZdpComplexDescReq_t *rReq = (ZS_ZdpComplexDescReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdpComplexDescConfirm;
    zdpClientReq->reqCluster = COMPLEX_DESCRIPTOR_CLID;
  complexDescReq->nwkAddrOfInterest = rReq->nwkAddrOfInterest;

  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;

  ZDO_ZdpReq(zdpClientReq);
}
#ifdef _PARENT_ANNCE_  
void rZdpParentAnnceConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpParentAnnceResp_t *rConf = (ZS_ZdpParentAnnceResp_t *) confBuffer->commandFrame.payload;

  rConf->req.numChilds = conf->respPayload.parentAnnce.numChilds;
  for(uint8_t i = 0; i < rConf->req.numChilds; i++)
    rConf->req.childInfo[i] = conf->respPayload.parentAnnce.childInfo[i];
  rConf->status = conf->respPayload.status;
  confBuffer->commandFrame.commandId = R_ZDO_PARENT_ANNOUNCE_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(ZS_ZdpParentAnnceResp_t);

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpParentAnnceRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_ParentAnnceReq_t *parentAnnceReq = &zdpClientReq->req.reqPayload.parentAnnce;
  ZS_ZdpParentAnnceReq_t *rReq = (ZS_ZdpParentAnnceReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdpParentAnnceConfirm;
  zdpClientReq->reqCluster = PARENT_ANNCE_CLID;
  parentAnnceReq->numChilds = rReq->req.numChilds;
  for(uint8_t i = 0; i < rReq->req.numChilds; i++)
    parentAnnceReq->childInfo[i] = rReq->req.childInfo[i];

  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;

  ZDO_ZdpReq(zdpClientReq);
}
#endif // #ifdef _PARENT_ANNCE_  
static void rZdpUserDescConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpUserDescConf_t *rConf = (ZS_ZdpUserDescConf_t *) confBuffer->commandFrame.payload;
  ZDO_UserDescResp_t *zdpResp = &conf->respPayload.userDescResp;
  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDO_USER_DESC_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUserDescConf_t);

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpUserDescRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_UserDescReq_t *userDescReq = &zdpClientReq->req.reqPayload.userDescReq;
  ZS_ZdpUserDescReq_t *rReq = (ZS_ZdpUserDescReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdpUserDescConfirm;
  zdpClientReq->reqCluster = USER_DESCRIPTOR_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;

  userDescReq->nwkAddrOfInterest = rReq->nwkAddrOfInterest;

  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpEndDeviceAnnceConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpEndDeviceConf_t *rConf = (ZS_ZdpEndDeviceConf_t *) confBuffer->commandFrame.payload;
  ZDO_ZdpReq_t *zdpClientReq = GET_STRUCT_BY_FIELD_POINTER(ZDO_ZdpReq_t, resp, conf);
  ZDO_DeviceAnnceReq_t *deviceAnnceReq = &zdpClientReq->req.reqPayload.deviceAnnce;

  confBuffer->commandFrame.commandId = R_ZDO_END_DEVICE_ANNCE_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpEndDeviceConf_t);

  rConf->status = conf->respPayload.status;
  rConf->resp = *deviceAnnceReq;

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpEndDeviceAnnceRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_DeviceAnnceReq_t *deviceAnnceReq = &zdpClientReq->req.reqPayload.deviceAnnce;
  ZS_ZdpEnDeviceAnnceReq_t *rReq = (ZS_ZdpEnDeviceAnnceReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdpEndDeviceAnnceConfirm;
  zdpClientReq->reqCluster = DEVICE_ANNCE_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = BROADCAST_ADDR_ALL;

  *deviceAnnceReq = *rReq;

  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpLqiConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpLqiConf_t *rConf = (ZS_ZdpLqiConf_t *) confBuffer->commandFrame.payload;
  ZDO_MgmtLqiResp_t *zdpResp = &conf->respPayload.mgmtLqiResp;

  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDO_MGMT_LQI_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpLqiConf_t);

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

static void rZdpRtgConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpRtgConf_t *rConf = (ZS_ZdpRtgConf_t *) confBuffer->commandFrame.payload;
  ZDO_MgmtRtgResp_t *zdpResp = &conf->respPayload.mgmtRtgResp;

  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDO_MGMT_RTG_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpRtgConf_t);

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpLqiRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_MgmtLqiReq_t *zdpReq = &zdpClientReq->req.reqPayload.mgmtLqiReq;
  ZS_ZdpLqiReq_t *rReq = (ZS_ZdpLqiReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdpLqiConfirm;
  zdpClientReq->reqCluster = MGMT_LQI_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;

  *zdpReq = rReq->req;

  ZDO_ZdpReq(zdpClientReq);
}

void rZdpRtgRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_MgmtRtgReq_t *zdpReq = &zdpClientReq->req.reqPayload.mgmtRtgReq;
  ZS_ZdpRtgReq_t *rReq = (ZS_ZdpRtgReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdpRtgConfirm;
  zdpClientReq->reqCluster = MGMT_RTG_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;

  *zdpReq = rReq->req;

  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpUserDescSetConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpUserDescSetConf_t *rConf = (ZS_ZdpUserDescSetConf_t *) confBuffer->commandFrame.payload;
  ZDO_UserDescConfResp_t *zdpResp = &conf->respPayload.userDescConfResp;

  rConf->status = conf->respPayload.status;
  rConf->nwkAddrOfInterest = zdpResp->nwkAddrOfInterest;
  confBuffer->commandFrame.commandId = R_ZDO_USER_DESC_SET_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUserDescSetConf_t);

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpUserDescSetRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_UserDescSetReq_t *zdpReq = &zdpClientReq->req.reqPayload.userDescSetReq;
  ZS_ZdpUserDescSetReq_t *rReq = (ZS_ZdpUserDescSetReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdpUserDescSetConfirm;
  zdpClientReq->reqCluster = USER_DESC_CONF_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddrOfInterest;

  *zdpReq = *rReq;

  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpNwkUpdateConfirm(ZDO_ZdpResp_t *conf)
{
  if (ZDO_SUCCESS_STATUS != conf->respPayload.status)
  {
    ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
    ZS_MgmtNwkUpdateNotf_t *rConf = (ZS_MgmtNwkUpdateNotf_t *) confBuffer->commandFrame.payload;

    confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (uint8_t);
    confBuffer->commandFrame.commandId = R_ZDO_MGMT_NWK_UPDATE_CONFIRM;
    rConf->status = conf->respPayload.status;
    serialManager.write(confBuffer);
  }
  rFreeMem(conf);
}

void rZdoNwkUpdateRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_MgmtNwkUpdateReq_t *nwkUpdateReq = &zdpClientReq->req.reqPayload.mgmtNwkUpdateReq;
  ZS_ZdpNwkUpdateReq_t *rReq = (ZS_ZdpNwkUpdateReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdpNwkUpdateConfirm;
  zdpClientReq->reqCluster = MGMT_NWK_UPDATE_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->nwkAddr;

  *nwkUpdateReq = rReq->req;

  ZDO_ZdpReq(zdpClientReq);
}

static void rZdpSystemServerDiscoveryConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpSystemServerDiscoveryConf_t *rConf = (ZS_ZdpSystemServerDiscoveryConf_t *) confBuffer->commandFrame.payload;
  ZDO_SystemServerDiscoveryResp_t *zdpRsp = &conf->respPayload.systemServerDiscoveryResp;

  confBuffer->commandFrame.commandId = R_ZDP_SYSTEM_DISCOVERY_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpSystemServerDiscoveryConf_t);

  rConf->status = conf->respPayload.status;
  rConf->serverMask = zdpRsp->serverMask;
  serialManager.write(confBuffer);

  rFreeMem(conf);
}

void rZdpSystemServerDiscoveryRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_SystemServerDiscoveryReq_t *zdpReq = &zdpClientReq->req.reqPayload.systemServerDiscoveryReq;
  ZS_ZdpSystemServerDiscoveryReq_t *rReq = (ZS_ZdpSystemServerDiscoveryReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdpSystemServerDiscoveryConfirm;
  zdpClientReq->reqCluster = SYSTEM_SERVER_DISCOVERY_CLID;

  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = BROADCAST_ADDR_RX_ON_WHEN_IDLE;

  zdpReq->serverMask = rReq->serverMask;

  ZDO_ZdpReq(zdpClientReq);
}

#else // #if APP_EXTENDED_ZDP_REQUEST == 1
void rZdoNodeDescRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}

void rZdpPowerDescRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}

void rZdpSimpleDescRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}

void rZdpActiveEPRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}

void rZdpComplexDescRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}
#ifdef _PARENT_ANNCE_  
void rZdpParentAnnceRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}
#endif
void rZdpUserDescRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}

void rZdpEndDeviceAnnceRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}

void rZdpLqiRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}

void rZdpRtgRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}

void rZdpUserDescSetRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}

void rZdoNwkUpdateRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}

void rZdpSystemServerDiscoveryRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  (void)commandBuffer;
}
#endif // #if APP_EXTENDED_ZDP_REQUEST == 1

static void rZdoIeeeAddrConfirm(ZDO_ZdpResp_t *conf)
{
  ZDO_IeeeAddrResp_t *zdpConf = (ZDO_IeeeAddrResp_t *) & conf->respPayload.ieeeAddrResp;
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdoIeeeAddrConf_t *rConf = (ZS_ZdoIeeeAddrConf_t *) confBuffer->commandFrame.payload;

  confBuffer->commandFrame.commandId = R_ZDO_IEEE_ADDR_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE
      + sizeof (ZS_ZdoIeeeAddrConf_t)
      - sizeof (ShortAddr_t) * (ZDP_ADDR_LIST_SIZE - zdpConf->numAssocDev);

  rConf->status= conf->respPayload.status;
  rConf->resp = *zdpConf;
  if (APP_MAX_COMMAND_PAYLOAD_SIZE >= (confBuffer->commandFrame.length - R_COMMAND_ID_SIZE))
  {
    serialManager.write(confBuffer);
  }
  else
  {
    //Error (maximum command payload size is reached)
    confBuffer->state = R_BUFFER_FREE_STATE;
    rAssert(false, R_DBG_PAYLOAD_TOO_LONG);
  }
  rFreeMem(conf);
}

void rZdoIeeeAddrRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_IeeeAddrReq_t *zdpReq = &zdpClientReq->req.reqPayload.ieeeAddrReq;
  ZS_ZdoIeeeAddrReq_t *rReq = (ZS_ZdoIeeeAddrReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->ZDO_ZdpResp = rZdoIeeeAddrConfirm;
  zdpClientReq->reqCluster = IEEE_ADDR_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = rReq->dstAddr;
  
  *zdpReq = rReq->req;
  ZDO_ZdpReq(zdpClientReq);
}

#ifdef _BINDING_
static void rZdpMatchDescConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = NULL;
  ZS_ZdpMatchDescConf_t *rConf;
  ZDO_MatchDescResp_t *zdpResp = &conf->respPayload.matchDescResp;

  confBuffer = bufferAllocator.allocate();
  rConf = (ZS_ZdpMatchDescConf_t *) confBuffer->commandFrame.payload;

  rConf->status = conf->respPayload.status;
  rConf->resp = *zdpResp;
  confBuffer->commandFrame.commandId = R_ZDO_MATCH_DESC_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE +
    offsetof (ZS_ZdpMatchDescConf_t, resp.matchList) +
    zdpResp->matchLength;

  serialManager.write(confBuffer);
  if (ZDO_CMD_COMPLETED_STATUS == conf->respPayload.status)
    rFreeMem(conf);
}

void rZdpMatchDescRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZDO_MatchDescReq_t *matchDescReq = &zdpClientReq->req.reqPayload.matchDescReq;
  ZS_ZdpMatchDescReq_t *rReq = (ZS_ZdpMatchDescReq_t *) commandBuffer->commandFrame.payload;
  uint8_t *ptr = (uint8_t *) rReq;
  uint8_t i;

  if (MAX_REQUESTED_CLUSTER_NUMBER >= rReq->numInClusters)
  {
    zdpClientReq->ZDO_ZdpResp = rZdpMatchDescConfirm;
    zdpClientReq->reqCluster = MATCH_DESCRIPTOR_CLID;
    zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
    zdpClientReq->dstAddress.shortAddress = rReq->dstAddr;

    matchDescReq->nwkAddrOfInterest = rReq->nwkAddrOfInterest;
    matchDescReq->profileId = rReq->profileId;
    matchDescReq->numInClusters = rReq->numInClusters;
    for (i = 0; i < rReq->numInClusters; i++)
      matchDescReq->inClusterList[i] = rReq->inClusterList[i];

    ptr += sizeof (uint16_t) * matchDescReq->numInClusters +
      offsetof(ZS_ZdpMatchDescReq_t, inClusterList);
    matchDescReq->numOutClusters = *ptr;
    ptr++;

    SYS_BYTE_MEMCPY(GET_FIELD_PTR(matchDescReq,
                                  ZDO_MatchDescReq_t,
                                  outClusterList),
                    ptr,
                    sizeof (uint16_t) * matchDescReq->numOutClusters);
    ZDO_ZdpReq(zdpClientReq);
  }
  else
  {
    rFreeMem(zdpClientReq);
  }
}

static void rZdoBindConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpBindConf_t *rConf;

  rConf = (ZS_ZdpBindConf_t *) confBuffer->commandFrame.payload;
  rConf->status = conf->respPayload.status;
  confBuffer->commandFrame.commandId = R_ZDO_BIND_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpBindConf_t);

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpBindRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZS_ZdpBindReq_t *rReq = (ZS_ZdpBindReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->reqCluster = rReq->reqCluster;
  if (APS_EXT_ADDRESS == rReq->targetAddrMode)
  {
    zdpClientReq->dstAddrMode = APS_EXT_ADDRESS;
    ExtAddr_t tempDstAddr;
    COPY_EXT_ADDR(tempDstAddr,rReq->targetExtAddr);
    COPY_EXT_ADDR_A(zdpClientReq->dstAddress.extAddress, &tempDstAddr);
  }
  else
  {
    zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
    zdpClientReq->dstAddress.shortAddress = rReq->targetNwkAddr;
  }

  memcpy(&zdpClientReq->req.reqPayload.bindReq,
    &rReq->payload, sizeof(zdpClientReq->req.reqPayload.bindReq));

  zdpClientReq->ZDO_ZdpResp = rZdoBindConfirm;
  ZDO_ZdpReq(zdpClientReq);
}

static void rZdoUnbindConfirm(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpUnbindConf_t *rConf;

  rConf = (ZS_ZdpUnbindConf_t *) confBuffer->commandFrame.payload;
  rConf->status = conf->respPayload.status;
  confBuffer->commandFrame.commandId = R_ZDO_UNBIND_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdpUnbindConf_t);

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpUnbindRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();
  ZS_ZdpUnbindReq_t *rReq = (ZS_ZdpUnbindReq_t *) commandBuffer->commandFrame.payload;

  zdpClientReq->reqCluster = rReq->reqCluster;
  if (APS_EXT_ADDRESS == rReq->targetAddrMode)
  {
    ExtAddr_t tempDstAddr;
    COPY_EXT_ADDR(tempDstAddr,rReq->targetExtAddr);
    COPY_EXT_ADDR_A(zdpClientReq->dstAddress.extAddress, &tempDstAddr);
  }
  else
    zdpClientReq->dstAddress.shortAddress = rReq->targetNwkAddr;

  memcpy(&zdpClientReq->req.reqPayload.unbindReq,
    &rReq->payload, sizeof(zdpClientReq->req.reqPayload.unbindReq));

  zdpClientReq->ZDO_ZdpResp = rZdoUnbindConfirm;
  ZDO_ZdpReq(zdpClientReq);
}

#if defined _END_DEVICE_BINDING_
static void rZdoEndDeviceBindResp(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RZdpEndDeviceBindingResp_t *rResp;

  rResp = (RZdpEndDeviceBindingResp_t *) confBuffer->commandFrame.payload;
  rResp->status = conf->respPayload.status;
  confBuffer->commandFrame.commandId = R_ZDO_END_DEVICE_BIND_RESPONSE;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RZdpEndDeviceBindingResp_t);

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpEndDeviceBindRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *zdpClientReq = (ZDO_ZdpReq_t *) rGetMem();

  zdpClientReq->ZDO_ZdpResp = rZdoEndDeviceBindResp;
  zdpClientReq->reqCluster = END_DEVICE_BIND_CLID;
  zdpClientReq->dstAddrMode = APS_SHORT_ADDRESS;
  zdpClientReq->dstAddress.shortAddress = 0x0000;

  memcpy(&zdpClientReq->req.reqPayload.endDeviceBindReq,
    commandBuffer->commandFrame.payload,
    commandBuffer->commandFrame.length - R_COMMAND_ID_SIZE);
  ZDO_ZdpReq(zdpClientReq);
}
#endif /* _END_DEVICE_BINDING_ */

static void rZdoMgmtBindResp(ZDO_ZdpResp_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdpMgmtBindResp_t *rResp;

  rResp = (ZS_ZdpMgmtBindResp_t *)confBuffer->commandFrame.payload;

  confBuffer->commandFrame.commandId = R_ZDO_MGMT_BIND_RESPONSE;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(*rResp);

  rResp->srcAddrMode = conf->srcAddrMode;
  if (APS_EXT_ADDRESS ==conf->srcAddrMode)
  {
    ExtAddr_t tempExtAddr;
    COPY_EXT_ADDR_A(&tempExtAddr, conf->srcAddress.extAddress);
    rResp->srcExtAddr = tempExtAddr;
  }
  else
    rResp->srcNwkAddr = conf->srcAddress.shortAddress;
  memcpy(&rResp->payload, &conf->respPayload, sizeof(conf->respPayload));

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdpMgmtBindRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_ZdpReq_t *const zdpReq = (ZDO_ZdpReq_t *) rGetMem();
  ZS_ZdpMgmtBindReq_t *rReq = (ZS_ZdpMgmtBindReq_t *) commandBuffer->commandFrame.payload;

  zdpReq->reqCluster = MGMT_BIND_CLID;
  if (APS_EXT_ADDRESS == rReq->targetAddrMode)
  {
    ExtAddr_t tempExtAddr;
    tempExtAddr = rReq->targetExtAddr;
    COPY_EXT_ADDR_A(zdpReq->dstAddress.extAddress, &tempExtAddr);
    zdpReq->dstAddrMode = APS_EXT_ADDRESS;
  }
  else
  {
    zdpReq->dstAddress.shortAddress = rReq->targetNwkAddr;
    zdpReq->dstAddrMode = APS_SHORT_ADDRESS;
  }

  memcpy(&zdpReq->req.reqPayload.mgmtBindReq,
    &rReq->payload, sizeof(zdpReq->req.reqPayload.mgmtBindReq));

  zdpReq->ZDO_ZdpResp = rZdoMgmtBindResp;
  ZDO_ZdpReq(zdpReq);
}
#endif /* _BINDING_ */
#endif /* APP_ZDP_REQUESTS */

#if defined _SECURITY_ && defined _LINK_SECURITY_
static void rZdoVerifyKeyConfirmProcess(APS_VerifyKeyConf_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ZdoVerifyKeyConf_t *rConf = (ZS_ZdoVerifyKeyConf_t *) confBuffer->commandFrame.payload;
  rConf->status = (uint8_t)conf->status;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ZdoVerifyKeyConf_t);
  confBuffer->commandFrame.commandId = R_ZDO_VERIFY_KEY_CONFIRM;

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rZdoVerifyKeyRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ZDO_VerifiKeyReq_t *const verifyKey = (ZDO_VerifiKeyReq_t *) rGetMem();
  ZS_VerifyKeyReq_t *rReq = (ZS_VerifyKeyReq_t *) commandBuffer->commandFrame.payload;

  verifyKey->timeout = rReq->timeout;
  verifyKey->verifyKeyConf = rZdoVerifyKeyConfirmProcess;
  ZDO_VerifyKeyReq(verifyKey);
}

#endif //#if defined _SECURITY_ && defined _LINK_SECURITY_

#ifdef _STACK_INTERNAL_TEST_FRAMEWORK_
static void zdoReqCmdRxdHandler(SYS_EventId_t eventId, SYS_EventData_t data)
{
  ZdoZdpReqTestData_t *zdoTestData = (ZdoZdpReqTestData_t *)data;
  ClusterId_t cluster = zdoTestData->apsInd->clusterId;

  if ((cluster <= USER_DESCRIPTOR_CLID) || 
#ifdef _PARENT_ANNCE_      
      (cluster == PARENT_ANNCE_CLID) || 
#endif        
      ((cluster >= MGMT_LQI_CLID) && (cluster <= MGMT_LEAVE_CLID)) || 
        (cluster == MGMT_NWK_UPDATE_CLID) || (cluster == MGMT_PERMIT_JOINING_CLID) || 
        (cluster == BIND_CLID) || (cluster == UNBIND_CLID))
  {
    zdoTestData->internalHandlingDenied = true;
    ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
    confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(uint8_t);
  
    memcpy(confirmBuffer->commandFrame.payload, (uint8_t *)data, sizeof(uint8_t));
    confirmBuffer->commandFrame.commandId = R_ZDO_REQ_FRAME_RECEIVED;
    memset(confirmBuffer->commandFrame.payload, 0x00, sizeof(uint8_t));
    serialManager.write(confirmBuffer);
  }
}

static void zdoReqCmdValidationHandler(SYS_EventId_t eventId, SYS_EventData_t data)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(uint8_t);

  confirmBuffer->commandFrame.commandId = R_ZDO_REQ_FRAME_VALIDATED;
  memcpy(confirmBuffer->commandFrame.payload, (uint8_t *)data, sizeof(uint8_t));
  serialManager.write(confirmBuffer);
}

static void zdoRspCmdValidationHandler(SYS_EventId_t eventId, SYS_EventData_t data)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(uint8_t);
  confirmBuffer->commandFrame.commandId = R_ZDO_RSP_FRAME_VALIDATED;
  memcpy(confirmBuffer->commandFrame.payload, (uint8_t *)data, sizeof(uint8_t));
  serialManager.write(confirmBuffer);
}
#endif // _STACK_INTERNAL_TEST_FRAMEWORK_
/* eof rZdo.c */
