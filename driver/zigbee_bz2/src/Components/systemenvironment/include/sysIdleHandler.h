/*******************************************************************************
  System idle handler Header File

  Company:
    Microchip Technology Inc.

  File Name:
    sysIdleHandler.h

  Summary:
    Definitions and function prototypes for system idle handler.

  Description:
    Definitions and function prototypes for system idle handler.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef SYS_IDLE_HANDLER_H_
#define SYS_IDLE_HANDLER_H_
/******************************************************************************
                   Prototypes section
******************************************************************************/
void SYS_IdleHandler(void);

#if defined(_SLEEP_WHEN_IDLE_)
/**************************************************************************//**
  \brief Enables sleep when a device is idle.
  It is disabled by default. If this is enabled, an end device automatically
  tries to go to sleep mode when there are no pending tasks and wakes up on
  expiration of CS_SLEEP_PERIOD or any application timer.
  The sleep period is equal to the minimum value between the rest of
  CS_SLEEP_PERIOD (CS_SLEEP_PERIOD minus time from the last poll)
  and the shortest time to fire of all application timers.
  If an end device wakes up on expiration of CS_SLEEP_PERIOD it polls
  its parent, otherwise it doesn't.
  Also, an end device can be wakep up by external interrupts. Application
  must be subscribed to event HAL_EVENT_WAKING_UP and call ZDO_WakeUpReq()
  in callback function.
  When the stack tries to go to sleep mode, it raises two events -
  BC_EVENT_BUSY_REQUEST and BC_EVENT_POLL_REQUEST allowing application to
  control sleep.
******************************************************************************/
void SYS_EnableSleepWhenIdle(void);

/**************************************************************************//**
  \brief Disables sleep when a device is idle.
******************************************************************************/
void SYS_DisableSleepWhenIdle(void);

/**************************************************************************//**
  \brief Returns true if sleep when idle is enabled. False otherwise.
******************************************************************************/
bool SYS_IsSleepWhenIdleEnabled(void);

#endif /* _SLEEP_WHEN_IDLE_ */

#endif /* SYS_IDLE_HANDLER_H_ */
// eof sysIdleHandler.c