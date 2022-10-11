/**************************************************************************//**
  \file  rSys.h

  \brief System related commands handlers

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
#ifndef _RSYS_H
#define _RSYS_H
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <ZAppSiSerialManager.h>
/******************************************************************************
                   Prototypes section
 ******************************************************************************/
void rSysGetRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rSysSetRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rSysSetDeviceTypeRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rSysStartRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rSysResetConfirm(ZS_CommandBuffer_t *commandBuffer);
void rSysResetRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rSysPowerOffRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rSysSleepWhenIdleProcess(ZS_CommandBuffer_t *commandBuffer);
void APL_TaskHandler(void);

void rSysAssertNotifyProcess(ZS_CommandBuffer_t *commandBuffer);
#endif /* _RSYS_H */

/* eof rSys.h */
