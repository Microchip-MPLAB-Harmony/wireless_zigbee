/**************************************************************************//**
  \file  rInterpan.c

  \brief Inter-PAN related commands Implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    19/05/14  karthik.p_u - Modified
 ******************************************************************************/
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <aps/include/aps.h>
#include <rNwk.h>
#include <rTypes.h>
#include <rMem.h>
#include <rExtensions.h>
#include <ZAppSiIdentifiers.h>
#include <ZAppSiCommands.h>
#include <consts.h>
#include <systemenvironment/include/sysUtils.h>
#include <bufferallocator.h>
/******************************************************************************
                             Static variables section
 ******************************************************************************/
/******************************************************************************
                             Implementations section
 ******************************************************************************/
#ifdef _INTERPAN_
void rIntrpDataConf(INTRP_DataConf_t* conf)
{
  INTRP_DataReq_t *req = GET_STRUCT_BY_FIELD_POINTER(INTRP_DataReq_t, confirm, conf);
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  confBuffer->commandFrame.commandId = R_INTRP_DATA_CONF;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(ZS_IntrpDataConf_t);
  ZS_IntrpDataConf_t* confData =
    (ZS_IntrpDataConf_t*)confBuffer->commandFrame.payload;
  confData->asduHandle = conf->asduHandle;
  confData->status = conf->status;

  serialManager.write(confBuffer);

  rFreeMem(req->asdu);
  rFreeMem(conf);

}

void rIntrpDataReq(ZS_CommandBuffer_t *commandBuffer)
{
  uint8_t* buf = (uint8_t *)rGetMem();
  INTRP_DataReq_t *req = (INTRP_DataReq_t *) rGetMem();
  ZS_IntrpDataReq_t *rReq = (ZS_IntrpDataReq_t *) commandBuffer->commandFrame.payload;
  req->asdu = &buf[APS_ASDU_OFFSET];
  memcpy(req->asdu,rReq->asdu,rReq->asduLength);
  req->dstPANID = rReq->dstPANID;
  req->dstAddrMode = (APS_AddrMode_t)rReq->dstAddrMode;
  req->dstAddress = rReq->dstAddress;
  req->clusterId = rReq->clusterId;
  req->profileId = rReq->profileId;
  req->asduHandle = rReq->asduHandle;
  req->asduLength = rReq->asduLength;
  req->INTRP_DataConf = rIntrpDataConf;
  req->txOptions = rReq->txOptions;

  INTRP_DataReq(req);

}
#if (BDB_SUPPORT != 1)
void INTRP_DataInd(INTRP_DataInd_t *ind)
{
  ZS_CommandBuffer_t *indBuffer = bufferAllocator.allocate();
  indBuffer->commandFrame.commandId = R_INTRP_DATA_IND;
  ZS_IntrpDataInd_t* indData =
    (ZS_IntrpDataInd_t*)indBuffer->commandFrame.payload;
  indData->srcPANID = ind->srcPANID;
  indData->srcAddress = ind->srcAddress;
  indData->dstAddrMode = ind->dstAddrMode;
  indData->dstPANID = ind->dstPANID;
  indData->dstAddress = ind->dstAddress;
  indData->profileId = ind->profileId;
  indData->clusterId = ind->clusterId;
  indData->lqi = ind->lqi;
  indData->asduLength = ind->asduLength;
  memcpy((uint8_t*)indData + sizeof(ZS_IntrpDataInd_t), ind->asdu, ind->asduLength);
  indBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(ZS_IntrpDataInd_t) +
    ind->asduLength;

  serialManager.write(indBuffer);

}
#endif

void rInitInterpan(void)
{
  INTRP_DataIndRegisterCallback(INTRP_DataInd);
}

#endif //_INTERPAN_
/* eof rInterpan.c */
