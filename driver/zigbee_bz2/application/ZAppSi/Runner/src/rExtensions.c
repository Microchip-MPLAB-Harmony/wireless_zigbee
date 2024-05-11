/**************************************************************************//**
  \file  rExtensions.c

  \brief QA commands implementations

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
#include <rTypes.h>
#include <rMem.h>
#include <ZAppSiIdentifiers.h>
#include <systemenvironment/include/sysUtils.h>
#include <bufferallocator.h>
/******************************************************************************
                             Static Variable section
 ******************************************************************************/
static uint16_t packetsReceivedCounter = 0;
static uint16_t lastPacketReceivedCounter = 0xffff;

/*****************************************************************************
                              Prototypes section
******************************************************************************/
APS_DataReq_t *rMakeDataReqBasedOnInd(APS_DataInd_t *ind, ClusterId_t clusterId, uint8_t asduLength, uint8_t srcEndpoint);
/******************************************************************************
                            Implementations section
 ******************************************************************************/
#ifdef _APS_MULTICAST_
static void rAfDataConfirm(APS_DataConf_t *conf)
{
  APS_DataReq_t *req = GET_STRUCT_BY_FIELD_POINTER(APS_DataReq_t, confirm, conf);
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  bool sendCommand = true;

  union _RAfDataConfirm_t
  {
    RAfIndirectConfirm_t rAfIndirectConfirm;
    RAfDirectConfirm_t rAfDirectConfirm;
    RAfGroupConfirm_t rAfGroupConfirm;
  } *rAfDataConf = (union _RAfDataConfirm_t *) confBuffer->commandFrame.payload;

  switch (req->dstAddrMode)
  {
    case APS_NO_ADDRESS:
      confBuffer->commandFrame.commandId = R_AF_INDIRECT_CONFIRM;
      confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (RAfIndirectConfirm_t);
      rAfDataConf->rAfIndirectConfirm.srcEndpoint = req->srcEndpoint;
      rAfDataConf->rAfIndirectConfirm.status = conf->status;
      break;

    case APS_SHORT_ADDRESS:
      confBuffer->commandFrame.commandId = R_AF_DIRECT_CONFIRM;
      confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (RAfDirectConfirm_t);
      rAfDataConf->rAfDirectConfirm.dstShortAddress = req->dstAddress.shortAddress;
      rAfDataConf->rAfDirectConfirm.dstEndpoint = req->dstEndpoint;
      rAfDataConf->rAfDirectConfirm.srcEndpoint = req->srcEndpoint;
      rAfDataConf->rAfDirectConfirm.status = conf->status;
      break;

    case APS_GROUP_ADDRESS:
      confBuffer->commandFrame.commandId = R_AF_GROUP_CONFIRM;
      confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (RAfGroupConfirm_t);
      rAfDataConf->rAfGroupConfirm.groupAddress = req->dstAddress.shortAddress;
      rAfDataConf->rAfGroupConfirm.srcEndpoint = req->srcEndpoint;
      rAfDataConf->rAfGroupConfirm.status = conf->status;
      rAfDataConf->rAfGroupConfirm.afduHandle = 0x00;
      break;

    default:
      sendCommand = false;
      break;
  }

  if (true == sendCommand)
  {
    serialManager.write(confBuffer);
  }
  else
  {
    confBuffer->state = R_BUFFER_FREE_STATE;
  }
  rFreeMem(req->asdu);
  rFreeMem(conf);
}

void rAfDirectRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  uint8_t *apsBuffer;
  APS_DataReq_t *req;
  uint8_t *ptr = commandBuffer->commandFrame.payload;
  uint8_t predicatedLength = R_COMMAND_ID_SIZE + sizeof (RAfDirectRequest_t) - 1;

  predicatedLength += ((RAfDirectRequest_t *) ptr)->afduLength;

  if (predicatedLength == commandBuffer->commandFrame.length)
  {
    req = (APS_DataReq_t *) rGetMem();
    apsBuffer = ((uint8_t *) rGetMem());
    req->APS_DataConf = rAfDataConfirm;

    //dstAddrMode
    req->dstAddrMode = APS_SHORT_ADDRESS;

    //dstAddress
    req->dstAddress.shortAddress = *(uint16_t *) ptr;
    ptr += sizeof (uint16_t);

    //dstEndpoint
    req->dstEndpoint = *ptr;
    ptr++;

    //srcEndpoint
    req->srcEndpoint = *ptr;
    ptr++;

    //clusterId
    req->clusterId = *(uint16_t *) ptr;
    ptr += sizeof (uint16_t);

    //profileId
    req->profileId = R_TEST_PROFILE_DEFAULT;

    //asduLength
    req->asduLength = *ptr;
    ptr++;

    //asdu
    if (APS_MAX_ASDU_SIZE >= req->asduLength)
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

}

void rAfIndirectRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  uint8_t *apsBuffer;
  APS_DataReq_t *req;
  uint8_t *ptr = commandBuffer->commandFrame.payload;
  uint8_t predicatedLength = R_COMMAND_ID_SIZE + sizeof (RAfIndirectRequest_t) - 1;

  predicatedLength += ((RAfIndirectRequest_t *) ptr)->afduLength;

  if (predicatedLength == commandBuffer->commandFrame.length)
  {
    req = (APS_DataReq_t *) rGetMem();
    apsBuffer = ((uint8_t *) rGetMem());
    req->APS_DataConf = rAfDataConfirm;

    //dstAddrMode
    req->dstAddrMode = APS_NO_ADDRESS;

    //dstAddress
    //dstEndpoint

    //srcEndpoint
    req->srcEndpoint = *ptr;
    ptr++;

    //clusterId
    req->clusterId = *(uint16_t *) ptr;
    ptr += sizeof (uint16_t);

    //profileId
    req->profileId = R_TEST_PROFILE_DEFAULT;

    //asduLength
    req->asduLength = *ptr;
    ptr++;

    //asdu
    if (APS_MAX_ASDU_SIZE >= req->asduLength)
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

}

void rAfGroupRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  uint8_t *apsBuffer;
  APS_DataReq_t *req;
  uint8_t *ptr = commandBuffer->commandFrame.payload;
  uint8_t predicatedLength = R_COMMAND_ID_SIZE + sizeof (RAfGroupRequest_t) - 1;

  predicatedLength += ((RAfGroupRequest_t *) ptr)->afduLength;

  if (predicatedLength == commandBuffer->commandFrame.length)
  {
    req = (APS_DataReq_t *) rGetMem();
    apsBuffer = ((uint8_t *) rGetMem());
    req->APS_DataConf = rAfDataConfirm;

    //dstAddrMode
    req->dstAddrMode = APS_GROUP_ADDRESS;

    //dstAddress
    req->dstAddress.shortAddress = *(uint16_t *) ptr;
    ptr += sizeof (uint16_t);

    //dstEndpoint

    //srcEndpoint
    req->srcEndpoint = *ptr;
    ptr++;

    //clusterId
    req->clusterId = *(uint16_t *) ptr;
    ptr += sizeof (uint16_t);

    //profileId
    req->profileId = R_TEST_PROFILE_DEFAULT;

    //asduLength
    req->asduLength = *ptr;
    ptr++;

    //asdu
    if (APS_MAX_ASDU_SIZE >= req->asduLength)
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

}
#endif /* _APS_MULTICAST_ */

void rBufferTestGroupRequestProcess(APS_DataInd_t *ind, uint8_t endpoint)
{
  APS_DataReq_t *req;
  CidBufferTestGroupRequest_t *reqCommand;
  CidBufferTestGroupResponse_t *respCommand;
  uint8_t i;

  if (sizeof (CidBufferTestGroupRequest_t) == ind->asduLength)
  {
    reqCommand = (CidBufferTestGroupRequest_t *) ind->asdu;

    req = rMakeDataReqBasedOnInd(ind, CID_BUFFER_TEST_GROUP_RESPONSE, sizeof (CidBufferTestGroupResponse_t) + reqCommand->length - 1, endpoint);

    respCommand = (CidBufferTestGroupResponse_t *) req->asdu;
    respCommand->status = CID_SUCCESSFUL_BUFFER_TEST_STATUS;
    respCommand->length = reqCommand->length;
    //Test buffer prepare
    if (APS_MAX_ASDU_SIZE >= req->asduLength)
    {
      for (i = 0; i < reqCommand->length; i++)
        respCommand->octets[i] = i;
    }
    APS_DataReq(req);
  }
}

void rBufferTestRequestProcess(APS_DataInd_t *ind, uint8_t endpoint)
{
  APS_DataReq_t *req;
  CidBufferTestRequest_t *reqCommand;
  CidBufferTestResponse_t *respCommand;
  uint8_t i;

  //if (sizeof(CidBufferTestRequest_t) == ind->asduLength)
  if (0 != ind->asduLength)
  {
    reqCommand = (CidBufferTestRequest_t *) ind->asdu;

    req = rMakeDataReqBasedOnInd(ind, CID_BUFFER_TEST_RESPONSE, sizeof (CidBufferTestResponse_t) + reqCommand->length - 1, endpoint);

    respCommand = (CidBufferTestResponse_t *) req->asdu;
    respCommand->status = CID_SUCCESSFUL_BUFFER_TEST_STATUS;
    respCommand->length = reqCommand->length;

    //Test buffer prepare
    if (APS_MAX_ASDU_SIZE >= req->asduLength)
    {
      for (i = 0; i < reqCommand->length; i++)
        respCommand->octets[i] = i;
    }
    APS_DataReq(req);
  }
}

void rResetPacketCountProcess(APS_DataInd_t *ind, uint8_t endpoint)
{
  ind = ind;
  packetsReceivedCounter = 0;
  lastPacketReceivedCounter = 0xffff;
  endpoint = endpoint; //Warning prevention
}

void rCountedPacketReceivedProcess(APS_DataInd_t *ind, uint8_t endpoint)
{
  CidTransmitCountedPackets_t *command;
  uint16_t counter;

  if (sizeof (CidTransmitCountedPackets_t) <= ind->asduLength)
  {
    command = (CidTransmitCountedPackets_t *) ind->asdu;

    counter = command->counter;

    //Packet length check and duplicate rejection
    if ((command->length == (ind->asduLength - 1)) &&
            (lastPacketReceivedCounter != counter))
    {
      packetsReceivedCounter++;
      lastPacketReceivedCounter = counter;
    }
  }

  endpoint = endpoint; //Warning prevention
}

static void rCidCommandsDataConfirmHandler(APS_DataConf_t *conf)
{
  APS_DataReq_t *req = GET_STRUCT_BY_FIELD_POINTER(APS_DataReq_t, confirm, conf);

  union _resp
  {
    CidBufferTestResponse_t cidBufferTestResponse;
    CidBufferTestGroupResponse_t cidBufferTestGroupResponse;
  } *resp = (union _resp *) req->asdu;

  bool memFree = true;


  if (APS_SUCCESS_STATUS != conf->status)
  {

    switch (req->clusterId)
    {
      case CID_BUFFER_TEST_RESPONSE:
        if (CID_SUCCESSFUL_BUFFER_TEST_STATUS == resp->cidBufferTestResponse.status)
        {
          //Transmittion failure on first attempt
          resp->cidBufferTestResponse.status = CID_TRANSMITTION_FAILURE_ON_FIRST_ATTEMPT_STATUS;
          resp->cidBufferTestResponse.length = 0;
          req->asduLength = sizeof (CidBufferTestResponse_t) - 1;
          APS_DataReq(req);
          memFree = false;
        }
        break;

      case CID_BUFFER_TEST_GROUP_RESPONSE:
        if (CID_SUCCESSFUL_BUFFER_TEST_STATUS == resp->cidBufferTestGroupResponse.status)
        {
          //Transmittion failure on first attempt
          resp->cidBufferTestGroupResponse.status = CID_TRANSMITTION_FAILURE_ON_FIRST_ATTEMPT_STATUS;
          resp->cidBufferTestGroupResponse.length = 0;
          req->asduLength = sizeof (CidBufferTestGroupResponse_t) - 1;
          APS_DataReq(req);
          memFree = false;
        }
        break;

      default:
        break;
    }
  }

  if (true == memFree)
  {
    rFreeMem(req->asdu);
    rFreeMem(req);
  }
}

APS_DataReq_t *rMakeDataReqBasedOnInd(APS_DataInd_t *ind, ClusterId_t clusterId, uint8_t asduLength, uint8_t srcEndpoint)
{
  APS_DataReq_t *req = (APS_DataReq_t *) rGetMem();

  req->asdu = rGetMem();
  req->dstAddrMode = ind->srcAddrMode;

  if (APS_EXT_ADDRESS == req->dstAddrMode)
    COPY_EXT_ADDR_A(req->dstAddress.extAddress,ind->srcAddress.extAddress);
  else
    req->dstAddress.shortAddress = ind->srcAddress.shortAddress;

  req->dstEndpoint = ind->srcEndpoint;
  req->profileId = R_TEST_PROFILE_DEFAULT;
  req->clusterId = clusterId;
  req->srcEndpoint = srcEndpoint;
  req->asduLength = asduLength;
  req->asdu = ((RApsFrame_t *) req->asdu)->payload;
  req->APS_DataConf = rCidCommandsDataConfirmHandler;

#ifdef _LINK_SECURITY_
  req->txOptions.securityEnabledTransmission = 1;
#else
  req->txOptions.securityEnabledTransmission = 0;
#endif /* _LINK_SECURITY_ */

  req->txOptions.useNwkKey = 0;
  req->txOptions.acknowledgedTransmission = 0;
  req->txOptions.fragmentationPermitted = 0;
  req->txOptions.noRouteDiscovery = 0;
  req->radius = 0x00;

  req->APS_DataConf = rCidCommandsDataConfirmHandler;
  return req;
}

void rRetrievePacketCountProcess(APS_DataInd_t *ind, uint8_t endpoint)
{
  APS_DataReq_t *req;
  CidPacketCountResponse_t *command;

  if (0 == ind->asduLength) //There is no data in this command.
  {
    req = rMakeDataReqBasedOnInd(ind, CID_PACKET_COUNT_RESPONSE, sizeof (CidPacketCountResponse_t), endpoint);
    command = (CidPacketCountResponse_t *) req->asdu;
    command->packetCount = packetsReceivedCounter;
    APS_DataReq(req);
  }
}

/* eof rExtensions.c */
