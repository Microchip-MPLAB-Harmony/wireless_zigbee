/**************************************************************************//**
  \file  rBdb.h

  \brief Bdb releated command handlers

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
#ifndef _RBDB_H
#define _RBDB_H
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <ZAppSiSerialManager.h>

#if (BDB_SUPPORT == 1)
/******************************************************************************
                   Prototypes section
 ******************************************************************************/
void rBdbInvokeCommissioningProcess(ZS_CommandBuffer_t *commandBuffer);
void rBdbSetInstallCodeProcess(ZS_CommandBuffer_t *commandBuffer);
#endif
#endif /* _RBDB_H */

/* eof rBdb.h */
