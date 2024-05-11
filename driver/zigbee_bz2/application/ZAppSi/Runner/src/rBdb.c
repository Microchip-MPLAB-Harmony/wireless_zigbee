/**************************************************************************//**
  \file  rBdb.c

  \brief Bdb related commands Implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
#if (BDB_SUPPORT == 1)
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <bdb/include/bdb.h>
#include <bdb/include/bdbInstallCode.h>
#include <rTypes.h>
#include <rMem.h>
#include <ZAppSiIdentifiers.h>
#include <ZAppSiCommands.h>
#include <ZAppSiSerialManager.h>
#include <consts.h>
#include <systemenvironment/include/sysUtils.h>
#include <bufferallocator.h>
#include <pds/include/wlPdsMemIds.h>
#include <pds/include/bcPDS.h>

static void Callback_Commissioning(BDB_InvokeCommissioningConf_t *conf)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RBdbInvokeCommConfirm_t *rConf = (RBdbInvokeCommConfirm_t *) confirmBuffer->commandFrame.payload;

  if (NULL != confirmBuffer)
  {
    confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RBdbInvokeCommConfirm_t);
    confirmBuffer->commandFrame.commandId = R_BDB_INVOKE_COMMISSIONING_CONF;
    rConf->status = conf->status;
    serialManager.write(confirmBuffer);
  }
  rFreeMem(conf);
}

void rBdbInvokeCommissioningProcess(ZS_CommandBuffer_t *commandBuffer)
{
  BDB_InvokeCommissioningReq_t *bdbReq = (BDB_InvokeCommissioningReq_t *) rGetMem();
  RBdbInvokeCommReq_t *rReq = (RBdbInvokeCommReq_t *) commandBuffer->commandFrame.payload;
  
  bdbReq->mode = rReq->mode;
  bdbReq->initiatorReq = NULL;
  bdbReq->BDB_InvokeCommissioningConf = Callback_Commissioning;
  
#ifdef _ENABLE_PERSISTENT_SERVER_
  if (rReq->powerFailureProtection)
    PDS_StoreByEvents(BC_ALL_MEMORY_MEM_ID);
#endif /* _ENABLE_PERSISTENT_SERVER_ */
  BDB_InvokeCommissioning(bdbReq);
}

void myICCallback(InstallCode_Configuration_Status_t status)
{
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  RBdbSetInstallCodeConfirm_t *rConf = (RBdbSetInstallCodeConfirm_t *) confirmBuffer->commandFrame.payload;

  if (NULL != confirmBuffer)
  {
    confirmBuffer->commandFrame.length = R_COMMAND_ID_SIZE + sizeof(RBdbSetInstallCodeConfirm_t);
    confirmBuffer->commandFrame.commandId = R_BDB_SET_INSTALL_CODE_CONF;
    rConf->status = status;
    serialManager.write(confirmBuffer);
  }
}

void rBdbSetInstallCodeProcess(ZS_CommandBuffer_t *commandBuffer)
{
  uint64_t addr;
  uint8_t installCode[18];
  RBdbSetInstallCodeReq_t *rReq = (RBdbSetInstallCodeReq_t *) commandBuffer->commandFrame.payload;
  ZS_CommandBuffer_t *confirmBuffer = bufferAllocator.allocate();
  //RBdbSetInstallCodeConfirm_t *rConf = (RBdbSetInstallCodeConfirm_t *) confirmBuffer->commandFrame.payload;
  memcpy(&addr, &rReq->addr, sizeof(addr));
  memcpy(&installCode, &rReq->installCode, sizeof(installCode));
  
  BDB_ConfigureInstallCode(addr,installCode,myICCallback);
}

#endif //#if (BDB_SUPPORT == 1)
/* eof rBdb.c */
