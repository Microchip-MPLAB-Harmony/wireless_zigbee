/**************************************************************************//**
  \file  rMac.c

  \brief Mac related commands Implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    29/03/2010  Max Gekk - Created.
 ******************************************************************************/
/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <systemenvironment/include/sysUtils.h>
#include <mac_phy/include/mac.h>
#include <rTypes.h>
#include <rMem.h>
#include <ZAppSiIdentifiers.h>
#include <bufferallocator.h>

/******************************************************************************
                             Implementations section
 ******************************************************************************/
static void rMacDataConf(MAC_DataConf_t *conf)
{
  MAC_DataReq_t *req = GET_PARENT_BY_FIELD(MAC_DataReq_t, confirm, conf);
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RMacDataConfirm_t *rawConf = (RMacDataConfirm_t *)confBuffer->commandFrame.payload;

  confBuffer->commandFrame.commandId = R_MAC_MCPS_DATA_CONFIRM;

  rawConf->msduHandle = req->msduHandle;
  rawConf->status = conf->status;

  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(*rawConf);

  serialManager.write(confBuffer);

  rFreeMem(req);
  rFreeMem(req->msdu);
}

void rMacDataRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  MAC_DataReq_t *req = (MAC_DataReq_t *) rGetMem();
  RMacDataRequest_t *rawReq = (RMacDataRequest_t *)commandBuffer->commandFrame.payload;

  req->srcAddrMode = (MAC_AddrMode_t)rawReq->srcAddrMode;
  req->dstAddrMode = (MAC_AddrMode_t)rawReq->dstAddrMode;
  req->dstPanId = rawReq->dstPanId;

  if (MAC_SHORT_ADDR_MODE == req->dstAddrMode)
    req->dstAddr.sh = rawReq->dstShortAddr;
  else if (MAC_EXT_ADDR_MODE == req->dstAddrMode)
    req->dstAddr.ext = rawReq->dstExtAddr;

  req->txOptions = (MAC_TxOptions_t)rawReq->txOptions;
  req->msduHandle = rawReq->msduHandle;

  req->msduLength = rawReq->msduLength;
  req->msdu = (uint8_t *)rGetMem();
  memcpy(req->msdu, rawReq->msdu, rawReq->msduLength);

  req->MAC_DataConf = rMacDataConf;
  MAC_DataReq(req);
}

static void rMacAccessRegisterConf(RF_RegAccessConf_t *conf)
{
  RF_RegAccessReq_t *req = GET_PARENT_BY_FIELD(RF_RegAccessReq_t, confirm, conf);
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RMacRegAccessConfirm_t *rawConf = (RMacRegAccessConfirm_t *)confBuffer->commandFrame.payload;

  confBuffer->commandFrame.commandId = R_MAC_WRITE_REGISTER_CONFIRM;

  rawConf->status = conf->status;
  rawConf->value = conf->value;

  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(*rawConf);

  serialManager.write(confBuffer);

  rFreeMem(req);
}

void rMacAccessRegisterRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RF_RegAccessReq_t *req = (RF_RegAccessReq_t *) rGetMem();
  RMacRegAccessRequest_t *rawReq = (RMacRegAccessRequest_t *)commandBuffer->commandFrame.payload;

  req->addr             = rawReq->address;
  req->value            = rawReq->value;
  req->RF_RegAccessConf = rMacAccessRegisterConf;

  if(rawReq->direction)
    RF_RegWriteReq(req);
  else
    RF_RegReadReq(req);
}

#if defined _MAC_BAN_NODE_
void rMacBanRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RMacBanRequest_t *req = (RMacBanRequest_t *) commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RMacBanConfirm_t *conf = (RMacBanConfirm_t *) confirmBuffer->commandFrame.payload;
  uint8_t rssiNotUsed = 0;

  MAC_BanNode(req->shortAddr, req->extAddr, req->cost, rssiNotUsed);
  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (RMacBanConfirm_t);
  confirmBuffer->commandFrame.commandId = R_MAC_BAN_CONFIRM;
  conf->status = MAC_SUCCESS_STATUS;
  serialManager.write(confirmBuffer);
}

void rMacBanAllRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  RMacBanAllRequest_t *req = (RMacBanAllRequest_t *) commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RMacBanAllConfirm_t *conf = (RMacBanAllConfirm_t *) confirmBuffer->commandFrame.payload;

  MAC_BanAllNodes(!!req->banAll);
  confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (RMacBanAllConfirm_t);
  confirmBuffer->commandFrame.commandId = R_MAC_BAN_ALL_CONFIRM;
  conf->status = MAC_SUCCESS_STATUS;
  serialManager.write(confirmBuffer);
}
#endif /* _MAC_BAN_NODE_ */
/** eof rMac.c */

