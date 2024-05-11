/**************************************************************************//**
  \file  rTimer.h

  \brief Timer related types and functions

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
#ifndef _RTIMER_H
#define _RTIMER_H
/*****************************************************************************
                              Includes section
******************************************************************************/
#include <hal/include/appTimer.h>
/*****************************************************************************
                              Types section
******************************************************************************/
typedef enum
{
  R_TIMER_STOPPED =           0x00,
  R_TIMER_STARTED =           0x01
} RAppTimerStatus_t;

typedef struct
{
  RAppTimerStatus_t status;
  HAL_AppTimer_t timer;
} RAppTimer_t;
/*****************************************************************************
                              Prototypes section
******************************************************************************/
/*****************************************************************************
  Start the R Application Timer
  Parameters: appTimer - timer pointer will be started
  Returns:    None
*****************************************************************************/
void rStartAppTimer(RAppTimer_t *appTimer);
/*****************************************************************************
  Stop the R Application Timer
  Parameters: appTimer - timer pointer will be stopped
  Returns:    None
*****************************************************************************/
void rStopAppTimer(RAppTimer_t *appTimer);
/*****************************************************************************
  Initialize the R Application Timer
  Parameters: appTimer - timer pointer will be initialized
              mode - timer mode:  TIMER_ONE_SHOT_MODE
                                  TIMER_REPEAT_MODE
              interval - timer interval (milliseconds)
              handler - timer handler function pointer
  Returns:    None
*****************************************************************************/
void rInitAppTimer(RAppTimer_t *appTimer, TimerMode_t mode, uint32_t interval, void (*handler)(void));

#endif  /* _RTIMER_H */

/* eof rTimer.h */
