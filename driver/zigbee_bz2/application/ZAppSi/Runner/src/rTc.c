/**************************************************************************//**
  \file  rTc.c

  \brief Trust center commands Implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    14/09/2009  Daniil Kasyanov - Created.
 ******************************************************************************/
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <systemenvironment/include/sysUtils.h>
#include <aps/include/aps.h>
#include <rMem.h>
#include <rTypes.h>
#include <ZAppSiIdentifiers.h>
#include <bufferallocator.h>
#ifdef _SECURITY_
#include <security/trustcentre/include/tc.h>
#endif /* _SECURITY_ */
/******************************************************************************
                   Implementations section
 ******************************************************************************/
#ifdef _SECURITY_
static void rTcKeyUpdateConfirm(TC_KeyUpdateConf_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RTcKeyUpdateConfirm_t *rConf = (RTcKeyUpdateConfirm_t *) confBuffer->commandFrame.payload;

  confBuffer->commandFrame.commandId = R_APSME_UPDATE_DEVICE_REQUEST;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (RTcKeyUpdateConfirm_t);
  rConf->confStatus = conf->status;
  rConf->destAddress = 0x00LL;
  rConf->deviceAddress = 0x00LL;
  rConf->deviceShortAddress = 0x00L;
  rConf->status = 0x00;

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rTcKeyUpdateRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  TC_KeyUpdateReq_t *tcReq = (TC_KeyUpdateReq_t *) rGetMem();
  tcReq->TC_KeyUpdateConf = rTcKeyUpdateConfirm;

  (void)commandBuffer;

  TC_KeyUpdateReq(tcReq);


}

static void rTcRemoveDeviceConfirm(TC_RemoveDeviceConf_t *conf)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();
  RTcRemoveDeviceConfirm_t *rConf = (RTcRemoveDeviceConfirm_t *) confBuffer->commandFrame.payload;
  TC_RemoveDeviceReq_t *tcReq = GET_STRUCT_BY_FIELD_POINTER(TC_RemoveDeviceReq_t, confirm, conf);

  confBuffer->commandFrame.commandId = R_APSME_REMOVE_DEVICE_CONFIRM;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof (RTcRemoveDeviceConfirm_t);
  rConf->status = conf->status;
  rConf->childAddress = tcReq->deviceAddr;
  rConf->parentAddress = tcReq->parentAddr;

  serialManager.write(confBuffer);
  rFreeMem(conf);
}

void rTcRemoveDeviceRequestProcess(ZS_CommandBuffer_t *commandBuffer)
{
  TC_RemoveDeviceReq_t *tcReq = (TC_RemoveDeviceReq_t *) rGetMem();
  RTcRemoveDeviceRequest_t *rReq = (RTcRemoveDeviceRequest_t *) commandBuffer->commandFrame.payload;

  tcReq->deviceAddr = rReq->childAddress;
  tcReq->parentAddr = rReq->parentAddress;
  tcReq->TC_RemoveDeviceConf = rTcRemoveDeviceConfirm;

  TC_RemoveDeviceReq(tcReq);


}

#endif /* _SECURITY_ */

/* eof rTc.c */
