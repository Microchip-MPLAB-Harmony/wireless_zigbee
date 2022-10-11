/**************************************************************************//**
  \file  rAps.c

  \brief Aps related commands Implementation

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
#include <aps/include/aps.h>
#include <rNwk.h>
#include <rTypes.h>
#include <rMem.h>
#include <rExtensions.h>
#include <rAps.h>
#include <ZAppSiIdentifiers.h>
#include <ZAppSiCommands.h>
#include <ZAppSiSerialManager.h>
#include <consts.h>
#include <systemenvironment/include/sysUtils.h>
#include <bufferallocator.h>

/******************************************************************************
                             Static variables section
 ******************************************************************************/
static uint8_t indCounter = 0;

/******************************************************************************
                             External variables section
******************************************************************************/
extern AIB_t csAIB;

/******************************************************************************
                             Implementations section
 ******************************************************************************/
#ifdef _ZSE_CERTIFICATION_
void rApsSetFrameCounterRequest(ZS_CommandBuffer_t *commandBuffer)
{
  RApsSetOutFrameCounterReq_t *req = (RApsSetOutFrameCounterReq_t *) commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RApsSetOutFrameCounterConf_t *conf = (RApsSetOutFrameCounterConf_t *) confirmBuffer->commandFrame.payload;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (RApsSetOutFrameCounterConf_t);
  confirmBuffer->commandFrame.commandId = R_APS_SET_FRAME_COUNTER_CONFIRM;
  conf->status = APS_SetOutSecFrameCounter(req->devAddr, req->counter);

  serialManager.write(confirmBuffer);
}
#endif // _ZSE_CERTIFICATION_

#ifdef _APS_MULTICAST_
static void rApsAddGroupConf(APS_AddGroupConf_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ApsAddGroupConf_t *rConfirm = (ZS_ApsAddGroupConf_t *) confBuffer->commandFrame.payload;
  APS_AddGroupReq_t *req = GET_STRUCT_BY_FIELD_POINTER(APS_AddGroupReq_t, confirm, conf);

  confBuffer->commandFrame.commandId = R_APSME_ADD_GROUP_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ApsAddGroupConf_t);
  rConfirm->status = (uint8_t)conf->status;
  SYS_BYTE_MEMCPY(GET_FIELD_PTR(rConfirm, ZS_ApsAddGroupConf_t, groupAddress),
                  &req->groupAddress,
                  sizeof (uint16_t));
  rConfirm->endpoint = req->endpoint;

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rApsAddGroupRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  APS_AddGroupReq_t *apsReq = (APS_AddGroupReq_t *) rGetMem();
  ZS_ApsAddGroupReq_t *rReq = (ZS_ApsAddGroupReq_t *) commandBuffer->commandFrame.payload;

  SYS_BYTE_MEMCPY(&apsReq->groupAddress,
                  GET_FIELD_PTR(rReq, ZS_ApsAddGroupReq_t, groupAddress),
                  sizeof (uint16_t));
  apsReq->endpoint = rReq->endpoint;

  APS_AddGroupReq(apsReq);
  rApsAddGroupConf(&apsReq->confirm);
}

static void rApsRemoveGroupConf(APS_RemoveGroupConf_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ApsRemoveGroupConf_t *rConfirm = (ZS_ApsRemoveGroupConf_t *) confBuffer->commandFrame.payload;
  APS_RemoveGroupReq_t *req = GET_STRUCT_BY_FIELD_POINTER(APS_RemoveGroupReq_t, confirm, conf);

  confBuffer->commandFrame.commandId = R_APSME_REMOVE_GROUP_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ApsRemoveGroupConf_t);
  rConfirm->status = conf->status;
  SYS_BYTE_MEMCPY(GET_FIELD_PTR(rConfirm, ZS_ApsRemoveGroupConf_t, groupAddress),
                                &req->groupAddress,
                                sizeof (uint16_t));
  rConfirm->endpoint = req->endpoint;

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rApsRemoveGroupRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  APS_RemoveGroupReq_t *apsReq = (APS_RemoveGroupReq_t *) rGetMem();
  ZS_ApsRemoveGroupReq_t *rReq = (ZS_ApsRemoveGroupReq_t *) commandBuffer->commandFrame.payload;

  SYS_BYTE_MEMCPY(&apsReq->groupAddress,
                  GET_FIELD_PTR(rReq, ZS_ApsRemoveGroupReq_t, groupAddress),
                  sizeof (uint16_t));
  apsReq->endpoint = rReq->endpoint;

  APS_RemoveGroupReq(apsReq);
  rApsRemoveGroupConf(&apsReq->confirm);
}

static void rApsRemoveAllGroupsConf(APS_RemoveAllGroupsConf_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ApsRemoveAllGroupsConf_t *rConfirm = (ZS_ApsRemoveAllGroupsConf_t *) confBuffer->commandFrame.payload;
  APS_RemoveAllGroupsReq_t *req = GET_STRUCT_BY_FIELD_POINTER(APS_RemoveAllGroupsReq_t, confirm, conf);

  confBuffer->commandFrame.commandId = R_APSME_REMOVE_ALL_GROUPS_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ApsRemoveAllGroupsConf_t);
  rConfirm->status = conf->status;
  rConfirm->endpoint = req->endpoint;

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rApsRemoveAllGroupsRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  APS_RemoveAllGroupsReq_t *apsReq = (APS_RemoveAllGroupsReq_t *) rGetMem();
  ZS_ApsRemoveAllGroupsReq_t *rReq = (ZS_ApsRemoveAllGroupsReq_t *) commandBuffer->commandFrame.payload;

  apsReq->endpoint = rReq->endpoint;

  APS_RemoveAllGroupsReq(apsReq);
  rApsRemoveAllGroupsConf(&apsReq->confirm);
}
#endif /* _APS_MULTICAST_ */

#ifdef _BINDING_
void rApsBindRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  APS_BindReq_t *apsReq = (APS_BindReq_t *) rGetMem();
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ApsBindConf_t *rConf = (ZS_ApsBindConf_t *) confBuffer->commandFrame.payload;
  ZS_ApsBindReq_t *rReq = (ZS_ApsBindReq_t *) commandBuffer->commandFrame.payload;

  apsReq->srcAddr = rReq->srcAddr;
  apsReq->srcEndpoint = rReq->srcEndpoint;
  apsReq->clusterId = rReq->clusterId;
  apsReq->dstAddrMode = (APS_AddrMode_t) rReq->dstAddrMode;
  if (APS_EXT_ADDRESS == apsReq->dstAddrMode)
  {
    apsReq->dst.unicast.extAddr = rReq->dstExtAddr;
    apsReq->dst.unicast.endpoint = rReq->dstEndpoint;
  }
  else
  {
    apsReq->dst.group = rReq->dstGroupAddr;
  }
  APS_BindReq(apsReq);

  rConf->status = apsReq->confirm.status;
  rConf->srcEndpoint = apsReq->srcEndpoint;
  rConf->srcAddr = apsReq->srcAddr;
  rConf->clusterId = apsReq->clusterId;
  rConf->dstAddrMode = apsReq->dstAddrMode;
  if (APS_EXT_ADDRESS == apsReq->dstAddrMode)
  {
    rConf->dstExtAddr = apsReq->dst.unicast.extAddr;
    rConf->dstEndpoint = apsReq->dst.unicast.endpoint;
  }
  else
  {
    rConf->dstGroupAddr = apsReq->dst.group;
  }

  confBuffer->commandFrame.commandId = R_APSME_BIND_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ApsBindConf_t);

#ifdef _APS_MULTICAST_
  if (APS_GROUP_ADDRESS == apsReq->dstAddrMode)
    confBuffer->commandFrame.length -= sizeof (uint64_t) + sizeof (uint8_t) - sizeof (uint16_t);
#endif /* _APS_MULTICAST_ */

  serialManager.write(confBuffer);
  rFreeMem(apsReq);

}

void rApsUnbindRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  APS_UnbindReq_t *apsReq = (APS_UnbindReq_t *) rGetMem();
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RApsUnbindConfirm_t *rConf = (RApsUnbindConfirm_t *) confBuffer->commandFrame.payload;
  RApsUnbindRequest_t *rReq = (RApsUnbindRequest_t *) commandBuffer->commandFrame.payload;

  apsReq->srcAddr = rReq->srcAddr;
  apsReq->srcEndpoint = rReq->srcEndpoint;
  apsReq->clusterId = rReq->clusterId;
  apsReq->dstAddrMode = (APS_AddrMode_t) rReq->dstAddrMode;
  if (APS_EXT_ADDRESS == apsReq->dstAddrMode)
  {
    apsReq->dst.unicast.extAddr = rReq->dstExtAddr;
    apsReq->dst.unicast.endpoint = rReq->dstEndpoint;
  }
  else
  {
    apsReq->dst.group = rReq->dstGroupAddr;
  }

  APS_UnbindReq(apsReq);

  rConf->status = apsReq->confirm.status;
  rConf->srcAddr = apsReq->srcAddr;
  rConf->clusterId = apsReq->clusterId;
  rConf->dstAddrMode = apsReq->dstAddrMode;
  if (APS_EXT_ADDRESS == apsReq->dstAddrMode)
  {
    rConf->dstExtAddr = apsReq->dst.unicast.extAddr;
    rConf->dstEndpoint = apsReq->dst.unicast.endpoint;
  }
  else
  {
    rConf->dstGroupAddr = apsReq->dst.group;
  }

  confBuffer->commandFrame.commandId = R_APSME_UNBIND_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ApsBindConf_t);

#ifdef _APS_MULTICAST_
  if (APS_GROUP_ADDRESS == apsReq->dstAddrMode)
    confBuffer->commandFrame.length -= sizeof (uint64_t) + sizeof (uint8_t) - sizeof (uint16_t);
#endif /* _APS_MULTICAST_ */

  serialManager.write(confBuffer);
  rFreeMem(apsReq);
}
#endif /* _BINDING_ */

static void rApsDataConf(APS_DataConf_t *conf)
{
  APS_DataReq_t *req = GET_STRUCT_BY_FIELD_POINTER(APS_DataReq_t, confirm, conf);
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();

  uint8_t *ptr = confBuffer->commandFrame.payload;

  confBuffer->commandFrame.commandId = R_APSDE_DATA_CONFIRM;

  //dstAddrMode
  *ptr = req->dstAddrMode;
  ptr += sizeof (uint8_t);

  switch (req->dstAddrMode)
  {
    case APS_EXT_ADDRESS:
      //*(uint64_t *) ptr = req->dstAddress.extAddress;
      SYS_BYTE_MEMCPY(ptr, &req->dstAddress.extAddress, sizeof (uint64_t));
      ptr += sizeof (uint64_t);

      //dstEndpoint
      *ptr = req->dstEndpoint;
      ptr += sizeof (uint8_t);
      break;

    case APS_SHORT_ADDRESS:
      //*(uint16_t *) ptr = req->dstAddress.shortAddress;
      SYS_BYTE_MEMCPY(ptr, &req->dstAddress.shortAddress, sizeof (uint16_t));
      ptr += sizeof (uint16_t);

      //dstEndpoint
      *ptr = req->dstEndpoint;
      ptr += sizeof (uint8_t);
      break;

#ifdef _APS_MULTICAST_
    case APS_GROUP_ADDRESS:
      //*(uint64_t *) ptr = req->dstAddress.groupAddress;
      SYS_BYTE_MEMCPY(ptr, &req->dstAddress.groupAddress, sizeof (uint16_t));
      ptr += sizeof (uint16_t);
      break;
#endif

    case APS_NO_ADDRESS:
      break;

    default:
      break;
  }

  //srcEndpoint
  *ptr = req->srcEndpoint;
  ptr += sizeof (uint8_t);

  *ptr = conf->status;
  ptr += sizeof (uint8_t);

  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + (ptr - confBuffer->commandFrame.payload);

  serialManager.write(confBuffer);

  rFreeMem(req->asdu);
  rFreeMem(conf);
}

void rApsDataRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  uint8_t *apsBuffer;
  APS_DataReq_t *req = (APS_DataReq_t *) rGetMem();

  uint8_t *ptr = commandBuffer->commandFrame.payload;

  apsBuffer = ((uint8_t *) rGetMem());

  if (!apsBuffer || !req)
    return;
  
  memset(req, 0, sizeof (APS_DataReq_t));

  req->APS_DataConf = rApsDataConf;

  //dstAddrMode
  req->dstAddrMode = (APS_AddrMode_t)*ptr;
  ptr++;

  //dstAddress
  if (APS_EXT_ADDRESS == req->dstAddrMode)
  {
    //req->dstAddress.extAddress = *(uint64_t *) ptr;
    SYS_BYTE_MEMCPY(&req->dstAddress.extAddress, ptr, sizeof (uint64_t));
    ptr += sizeof (uint64_t);
  }
  else
  {
    //req->dstAddress.shortAddress = *(uint16_t *) ptr;
    SYS_BYTE_MEMCPY(&req->dstAddress.shortAddress, ptr, sizeof (uint16_t));
    ptr += sizeof (uint16_t);
  }

  //dstEndpoint
  req->dstEndpoint = *ptr;
  ptr += sizeof (uint8_t);

  //profileId
  //req->profileId = *(uint16_t *) ptr;
  SYS_BYTE_MEMCPY(&req->profileId, ptr, sizeof (uint16_t));
  ptr += sizeof (uint16_t);

  //clusterId
  //req->clusterId = *(uint16_t *) ptr;
  SYS_BYTE_MEMCPY(&req->clusterId, ptr, sizeof (uint16_t));
  ptr += sizeof (uint16_t);

  //srcEndpoint
  req->srcEndpoint = *ptr;
  ptr++;

  //asduLength
  SYS_BYTE_MEMCPY(&req->asduLength, ptr, sizeof (uint16_t));
  ptr += sizeof (uint16_t);

  //asdu
  SYS_BYTE_MEMCPY(&apsBuffer[APS_ASDU_OFFSET], ptr, req->asduLength);
  req->asdu = &apsBuffer[APS_ASDU_OFFSET];
  ptr += req->asduLength;

  //txOptions
  req->txOptions = *(APS_TxOptions_t *) ptr;
  ptr += sizeof (uint8_t);

  //radius
  req->radius = *ptr;

  APS_DataReq(req);

}
#ifdef _GREENPOWER_SUPPORT_
void rApsDataRequestWithAliasProcess(ZS_CommandBuffer_t *commandBuffer)
{
  uint8_t *apsBuffer;
  APS_DataReq_t *req = (APS_DataReq_t *) rGetMem();

  uint8_t *ptr = commandBuffer->commandFrame.payload;

  apsBuffer = ((uint8_t *) rGetMem());

  if (!apsBuffer || !req)
    return;

  memset(req, 0, sizeof (APS_DataReq_t));

  req->APS_DataConf = rApsDataConf;

  //dstAddrMode
  req->dstAddrMode = *ptr;
  ptr++;

  //dstAddress
  if (APS_EXT_ADDRESS == req->dstAddrMode)
  {
    //req->dstAddress.extAddress = *(uint64_t *) ptr;
    SYS_BYTE_MEMCPY(&req->dstAddress.extAddress, ptr, sizeof (uint64_t));
    ptr += sizeof (uint64_t);
  }
  else
  {
    //req->dstAddress.shortAddress = *(uint16_t *) ptr;
    SYS_BYTE_MEMCPY(&req->dstAddress.shortAddress, ptr, sizeof (uint16_t));
    ptr += sizeof (uint16_t);
  }

  //dstEndpoint
  req->dstEndpoint = *ptr;
  ptr += sizeof (uint8_t);

  //profileId
  //req->profileId = *(uint16_t *) ptr;
  SYS_BYTE_MEMCPY(&req->profileId, ptr, sizeof (uint16_t));
  ptr += sizeof (uint16_t);

  //clusterId
  //req->clusterId = *(uint16_t *) ptr;
  SYS_BYTE_MEMCPY(&req->clusterId, ptr, sizeof (uint16_t));
  ptr += sizeof (uint16_t);

  //srcEndpoint
  req->srcEndpoint = *ptr;
  ptr++;

  //asduLength
  SYS_BYTE_MEMCPY(&req->asduLength, ptr, sizeof (uint16_t));
  ptr += sizeof (uint16_t);

  //asdu
  SYS_BYTE_MEMCPY(&apsBuffer[APS_ASDU_OFFSET], ptr, req->asduLength);
  req->asdu = &apsBuffer[APS_ASDU_OFFSET];
  ptr += req->asduLength;

  //txOptions
  req->txOptions = *(APS_TxOptions_t *) ptr;
  ptr += sizeof (uint8_t);

  //useAlias
  if (*ptr == 0x01)
    req->useAlias = true;
  else
    req->useAlias = false;
  ptr++;

  SYS_BYTE_MEMCPY(&req->aliasSrcAddr, ptr, sizeof (uint16_t));
  ptr += sizeof(ShortAddr_t);
  req->aliasSeqNumber = *ptr;
  ptr++;

  //radius
  req->radius = *ptr;

  APS_DataReq(req);

}

#endif //_GREENPOWER_SUPPORT_
void rApsGetRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RApsGetRequest_t *rReq = (RApsGetRequest_t *) commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RApsGetConfirm_t *rConfirm = (RApsGetConfirm_t *) confBuffer->commandFrame.payload;

  confBuffer->commandFrame.commandId = R_APSME_GET_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (RApsGetConfirm_t) - 1;
  rConfirm->attributeId = rReq->attributeId;
  rConfirm->status = APS_SUCCESS_STATUS;

  switch (rReq->attributeId)
  {
    case APS_AIB_NONMEMBER_RADIUS:
      confBuffer->commandFrame.length += sizeof(csAIB.nonMemberRadius);
      memcpy(rConfirm->attributeValue, &csAIB.nonMemberRadius, sizeof(csAIB.nonMemberRadius));
      break;
    default:
        rConfirm->status = APS_NOT_SUPPORTED_STATUS;
      break;
  }
  serialManager.write(confBuffer);
}


void rApsSetRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RApsSetRequest_t *rReq = (RApsSetRequest_t *) commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RApsSetConfirm_t *rConfirm = (RApsSetConfirm_t *) confBuffer->commandFrame.payload;

  confBuffer->commandFrame.commandId = R_APSME_SET_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RApsSetConfirm_t);
  rConfirm->attributeId = rReq->attributeId;
  rConfirm->status = APS_SUCCESS_STATUS;

  switch (rReq->attributeId)
  {
    case APS_AIB_NONMEMBER_RADIUS:
      memcpy(&csAIB.nonMemberRadius, rReq->attributeValue, sizeof(csAIB.nonMemberRadius));
      break;
#if defined _APS_FRAGMENTATION_
    case APS_AIB_FRAG_WINDOW_SIZE:
      memcpy(&csAIB.fragWindowSize, rReq->attributeValue, sizeof(csAIB.fragWindowSize));
      CS_WriteParameter(CS_APS_MAX_TRANSMISSION_WINDOW_SIZE_ID, &csAIB.fragWindowSize);
      break;
#if defined _CERTIFICATION_
    case APS_AIB_FRAG_TX_DROP_MASK:
      memcpy(&csAIB.txFragDropMask, rReq->attributeValue, sizeof(csAIB.txFragDropMask));
      break;
    case APS_AIB_FRAG_RX_DROP_MASK:
      memcpy(&csAIB.rxFragDropMask, rReq->attributeValue, sizeof(csAIB.rxFragDropMask));
      break;
#endif /* _CERTIFICATION_ */
#endif /* _APS_FRAGMENTATION_ */
    default:
      rConfirm->status = APS_NOT_SUPPORTED_STATUS;
      break;
  }
  serialManager.write(confBuffer);
}

#ifdef _SECURITY_
static void rApsTransportKeyConf(APS_TransportKeyConf_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ApsTransportKeyConf_t *rConf = (ZS_ApsTransportKeyConf_t *) confBuffer->commandFrame.payload;
  APS_TransportKeyReq_t *req = GET_STRUCT_BY_FIELD_POINTER(APS_TransportKeyReq_t, confirm, conf);

  rConf->destAddress = req->destAddress;
  rConf->keyType = req->keyType;
  rConf->status = conf->status;

  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ApsTransportKeyConf_t);
  confBuffer->commandFrame.commandId = R_APSME_TRANSPORT_KEY_CONFIRM;

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rApsTransportKeyRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  APS_TransportKeyReq_t *apsReq = (APS_TransportKeyReq_t *) rGetMem();
  ZS_ApsTransportKeyReq_t *rReq = (ZS_ApsTransportKeyReq_t *) commandBuffer->commandFrame.payload;

  apsReq->destAddress = rReq->destAddress;
  apsReq->keyType = (APS_TransportKeyType_t) rReq->keyType;
#if defined(__ICCAVR32__)
  /* FIXME: workaround for IAR AVR32 5.20.1.50092. */
  memcpy(&apsReq->transportKeyData,
    commandBuffer->commandFrame.payload + sizeof(rReq->destAddress) + sizeof(APS_TransportKeyType_t),
    sizeof(APS_ReqTransportKeyData_t));
#else
  apsReq->transportKeyData = rReq->transportKeyData;
#endif
  apsReq->APS_TransportKeyConf = rApsTransportKeyConf;

  APS_TransportKeyReq(apsReq);

}
#ifdef _LINK_SECURITY_
static void rApsRequestKeyConf(APS_RequestKeyConf_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ApsRequestKeyConf_t *rConf = (ZS_ApsRequestKeyConf_t *) confBuffer->commandFrame.payload;
  APS_RequestKeyReq_t *req = GET_STRUCT_BY_FIELD_POINTER(APS_RequestKeyReq_t, confirm, conf);

  rConf->destAddress = req->destAddress;
  rConf->keyType = req->keyType;
  rConf->partnerAddress = req->partnerAddress;
  rConf->status = conf->status;

  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ApsRequestKeyConf_t);
  confBuffer->commandFrame.commandId = R_APSME_REQUEST_KEY_CONFIRM;

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rApsRequestKeyRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  APS_RequestKeyReq_t *apsReq = (APS_RequestKeyReq_t *) rGetMem();
  ZS_ApsRequestKeyReq_t *rReq = (ZS_ApsRequestKeyReq_t *) commandBuffer->commandFrame.payload;

  apsReq->destAddress = rReq->destAddress;
  apsReq->keyType = (APS_RequestKeyType_t) rReq->keyType;
  apsReq->partnerAddress = rReq->partnerAddress;
  apsReq->APS_RequestKeyConf = rApsRequestKeyConf;

  APS_RequestKeyReq(apsReq);
}

void rApsGetOutSecurityCounterRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  ExtAddr_t extAddr;
  APS_KeyHandle_t keyHandle;
  RApsGetOutSecurityCounterReq_t *rReq =
    (RApsGetOutSecurityCounterReq_t *)commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RApsGetOutSecurityCounterConf_t *rConf =
    (RApsGetOutSecurityCounterConf_t *)confBuffer->commandFrame.payload;

  COPY_EXT_ADDR(extAddr, rReq->extAddr);
  keyHandle = APS_FindKeys(&extAddr);
  rConf->outCounter = APS_GetOutSecFrameCounter(keyHandle);

  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RApsGetOutSecurityCounterConf_t);
  confBuffer->commandFrame.commandId = R_APS_GET_OUT_SEC_COUNTER_CONFIRM;

  serialManager.write(confBuffer);
}
#endif /* _LINK_SECURITY_ */

static void rApsSwitchKeyConfirm(APS_SwitchKeyConf_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  ZS_ApsSwitchKeyConf_t *rConf = (ZS_ApsSwitchKeyConf_t *) confBuffer->commandFrame.payload;
  APS_SwitchKeyReq_t *req = GET_STRUCT_BY_FIELD_POINTER(APS_SwitchKeyReq_t, confirm, conf);

  rConf->destAddress = req->destAddress;
  rConf->keySeqNumber = req->keySeqNumber;
  rConf->status = conf->status;

  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (ZS_ApsSwitchKeyConf_t);
  confBuffer->commandFrame.commandId = R_APSME_SWITCH_KEY_CONFIRM;

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rApsSwitchKeyRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  APS_SwitchKeyReq_t *apsReq = (APS_SwitchKeyReq_t *) rGetMem();
  ZS_ApsSwitchKeyReq_t *rReq = (ZS_ApsSwitchKeyReq_t *) commandBuffer->commandFrame.payload;

  apsReq->destAddress = rReq->destAddress;
  apsReq->keySeqNumber = rReq->keySeqNumber;
  apsReq->APS_SwitchKeyConf = rApsSwitchKeyConfirm;

  APS_SwitchKeyReq(apsReq);
}

#endif /* _SECURITY_ */

void rApsDataInd(APS_DataInd_t *ind, uint8_t endpoint)
{
  ZS_CommandBuffer_t *commandBuffer = bufferAllocator.allocate();
  uint8_t *ptr;

  indCounter++;

  commandBuffer->commandFrame.commandId = R_APSDE_DATA_INDICATION;

  ptr = &commandBuffer->commandFrame.payload[0];

  //dstAddrMode
  *ptr = ind->dstAddrMode;
  ptr++;

  //dstAddress
#ifdef _APS_MULTICAST_
  if (APS_GROUP_ADDRESS == ind->dstAddrMode)
  {
    SYS_BYTE_MEMCPY(ptr, &ind->dstAddress.groupAddress, sizeof (uint16_t));
    ptr += sizeof (uint16_t);
  }
  else
#endif /* _APS_MULTICAST_ */
  if (APS_SHORT_ADDRESS == ind->dstAddrMode)
  {
    SYS_BYTE_MEMCPY(ptr, &ind->dstAddress.shortAddress, sizeof (uint16_t));
    ptr += sizeof (uint16_t);
  }
  else if (APS_EXT_ADDRESS == ind->dstAddrMode)
  {
    SYS_BYTE_MEMCPY(ptr, &ind->dstAddress.extAddress, sizeof (uint64_t));
    ptr += sizeof (uint64_t);
  }

  //dstEndpoint present
  SYS_BYTE_MEMCPY(ptr, &ind->dstEndpoint, sizeof (uint8_t));
  ptr++;

  //srcAddrMode
  *ptr = ind->srcAddrMode;
  ptr++;

  //ShortAddr
  SYS_BYTE_MEMCPY(ptr, &ind->srcAddress.shortAddress, sizeof (uint16_t));
  ptr += sizeof (uint16_t);

  //srcExtAddress
  if (APS_EXT_ADDRESS == ind->srcAddrMode)
    SYS_BYTE_MEMCPY(ptr, &ind->srcAddress.extAddress, sizeof (uint64_t));
  else
    memset(ptr, 0x00, sizeof(uint64_t));
  ptr += sizeof (uint64_t);

  //srcEndpoint;
  SYS_BYTE_MEMCPY(ptr, &ind->srcEndpoint, sizeof (uint8_t));
  ptr++;

  //profileId
  SYS_BYTE_MEMCPY(ptr, &ind->profileId, sizeof (uint16_t));
  ptr += sizeof (uint16_t);

  //clusterId
  SYS_BYTE_MEMCPY(ptr, &ind->clusterId, sizeof (uint16_t));
  ptr += sizeof (uint16_t);

  //asduLength
  SYS_BYTE_MEMCPY(ptr, &ind->asduLength, sizeof (uint16_t));
  ptr += sizeof (uint16_t);

  //asdu
  SYS_BYTE_MEMCPY(ptr, ind->asdu, ind->asduLength);
  ptr += ind->asduLength;

  //zero
  *ptr = 0;
  ptr++;

  //securityStatus
  *ptr = ind->securityStatus;
  ptr++;

  //PrevHopAddr
  SYS_BYTE_MEMCPY(ptr, &ind->prevHopAddr, sizeof (uint16_t));
  ptr += sizeof (uint16_t);

  commandBuffer->commandFrame.length = R_COMMAND_ID_SIZE + (ptr - &commandBuffer->commandFrame.payload[0]);

  serialManager.write(commandBuffer);

#ifdef _STACK_INTERNAL_TEST_FRAMEWORK_
  if (APS_ZDO_ENDPOINT == endpoint)
  {
    return;
  }
#endif

  switch (LE16_TO_CPU(ind->clusterId))
  {
    case CID_TRANSMIT_COUNTED_PACKETS:
      rCountedPacketReceivedProcess(ind, endpoint);
      break;

    case CID_RESET_PACKET_COUNT:
      rResetPacketCountProcess(ind, endpoint);
      break;

    case CID_RETRIEVE_PACKET_COUNT:
      rRetrievePacketCountProcess(ind, endpoint);
      break;

    case CID_BUFFER_TEST_REQUEST:
      rBufferTestRequestProcess(ind, endpoint);
      break;

    case CID_BUFFER_TEST_GROUP_REQUEST:
      rBufferTestGroupRequestProcess(ind, endpoint);
      break;
#if defined(_ROUTER_) || defined(_COORDINATOR_)
#if defined _NWK_MESH_ROUTING_ || defined _NWK_MANY_TO_ONE_ROUTING_
    case CID_ROUTE_DISCOVERY_REQUEST:
      rNwkRemotelyInitiatedRouteDiscoveryRequestProcess(ind, endpoint);
      break;
#endif /* _NWK_MESH_ROUTING_ or _NWK_MANY_TO_ONE_ROUTING_ */
#endif /* defined(_ROUTER_) || defined(_COORDINATOR_) */
    default:
      break;
  }
}

static void rApsStartConfirm(APS_StartConf_t *conf)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RApsStartConf_t *rConf = (RApsStartConf_t *) confirmBuffer->commandFrame.payload;

  if (NULL != confirmBuffer)
  {
    confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RApsStartConf_t);
    confirmBuffer->commandFrame.commandId = R_APSME_START_CONF;
    rConf->status = conf->status;
    serialManager.write(confirmBuffer);
  }

  rFreeMem(conf);
}

void rApsStartRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  APS_StartReq_t *req = rGetMem();

  if(NULL != req)
  {
    req->APS_StartConf = rApsStartConfirm;
    APS_StartReq(req);
  }

  commandBuffer->state = R_BUFFER_FREE_STATE;
}

static void rApsResetConfirm(APS_ResetConf_t *conf)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RApsResetConf_t *rConf = (RApsResetConf_t *) confirmBuffer->commandFrame.payload;

  if (NULL != confirmBuffer)
  {
    confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RApsResetConf_t);
    confirmBuffer->commandFrame.commandId = R_APSME_RESET_CONF;
    rConf->status = conf->status;
    serialManager.write(confirmBuffer);
  }

  rFreeMem(conf);
}

void rApsResetRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  APS_ResetReq_t *req = rGetMem();
  
  if(NULL != req)
  {
    req->APS_ResetConf = rApsResetConfirm;
    APS_ResetReq(req);
  }

  commandBuffer->state = R_BUFFER_FREE_STATE;
}

#if defined _CERTIFICATION_ && defined _LINK_SECURITY_
void rApsUpdateSecurityPolicyProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RApsUpdateSecurityPolicyReq_t *req = (RApsUpdateSecurityPolicyReq_t *)commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RApsUpdateSecurityPolicyConf_t *conf = (RApsUpdateSecurityPolicyConf_t *) confirmBuffer->commandFrame.payload;

  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (RApsUpdateSecurityPolicyConf_t);
  confirmBuffer->commandFrame.commandId = R_APS_UPDATE_SECURITY_POLICY_CONFIRM;

  APS_UpdateSecurityPolicy((APS_SecurityPolicyId_t)req->spid, (APS_SecurityPolicy_t)req->policy);
  conf->status = 0U;

  serialManager.write(confirmBuffer);
}
#endif /* _CERTIFICATION_ and _LINK_SECURITY_ */
/* eof rAps.c */
