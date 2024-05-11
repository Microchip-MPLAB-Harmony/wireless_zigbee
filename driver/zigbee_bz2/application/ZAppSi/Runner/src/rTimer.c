/**************************************************************************//**
  \file  rTimer.c

  \brief Timer Implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
#include <rTimer.h>
/*******************************************************************************
                          Implementations section
 ******************************************************************************/
/*****************************************************************************
  Start the R Application Timer
  Parameters: appTimer - timer pointer will be started
  Returns:    None
*****************************************************************************/
void rStartAppTimer(RAppTimer_t *appTimer)
{
  if (R_TIMER_STOPPED == appTimer->status)
  {
    appTimer->status = R_TIMER_STARTED;
    HAL_StartAppTimer(&appTimer->timer);
  }
}
/*****************************************************************************
  Stop the R Application Timer
  Parameters: appTimer - timer pointer will be stopped
  Returns:    None
*****************************************************************************/
void rStopAppTimer(RAppTimer_t *appTimer)
{
  if (R_TIMER_STARTED == appTimer->status)
  {
    appTimer->status = R_TIMER_STOPPED;
    HAL_StopAppTimer(&appTimer->timer);
  }
}
/*****************************************************************************
  Initialize the R Application Timer
  Parameters: appTimer - timer pointer will be initialized
              mode - timer mode:  TIMER_ONE_SHOT_MODE
                                  TIMER_REPEAT_MODE
              interval - timer interval (milliseconds)
              handler - timer handler function pointer
  Returns:    None
*****************************************************************************/
void rInitAppTimer(RAppTimer_t *appTimer, TimerMode_t mode, uint32_t interval, void (*handler)(void))
{
  rStopAppTimer(appTimer);

  appTimer->status = R_TIMER_STOPPED;
  appTimer->timer.mode = mode;
  appTimer->timer.interval = interval;
  appTimer->timer.callback = handler;
}

/* eof rTimer.c */
