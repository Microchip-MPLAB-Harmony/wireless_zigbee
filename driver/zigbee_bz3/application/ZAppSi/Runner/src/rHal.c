/**************************************************************************//**
  \file  rHal.c

  \brief HAL related commands Implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    13/02/2012  N. Fomin - Created.
 ******************************************************************************/
/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <rTypes.h>
#include <rMem.h>
#include <ZAppSiIdentifiers.h>
#include <bufferallocator.h>
#include <ZAppSiCommands.h>

/******************************************************************************
                             Implementations section
 ******************************************************************************/
static void rHalTimerFired(void)
{
  ZS_CommandBuffer_t *confBuffer = bufferAllocator.allocate();

  confBuffer->commandFrame.commandId = R_HAL_START_APP_TIMER_FIRED;
  confBuffer->commandFrame.length = R_COMMAND_ID_SIZE;

  serialManager.write(confBuffer);
}

void rHalStartAppTimerProcess(ZS_CommandBuffer_t *commandBuffer)
{
  HAL_AppTimer_t *timer = (HAL_AppTimer_t *) rGetMem();
  ZS_HalAppTimer_t *timerReq = (ZS_HalAppTimer_t *)commandBuffer->commandFrame.payload;

  timer->mode = timerReq->mode;
  timer->interval = timerReq->interval;
  timer->callback = rHalTimerFired;

  HAL_StartAppTimer(timer);
}

/* eof rHal.c */

