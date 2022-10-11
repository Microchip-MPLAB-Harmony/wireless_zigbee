/*******************************************************************************
  ZLL Low Power Header File

  Company:
    Microchip Technology Inc.

  File Name:
    N_LowPower.h

  Summary:
    This file contains the ZLL Low Power functions.

  Description:
    This file contains the ZLL Low Power functions.
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


#ifndef N_LOWPOWER_H
#define N_LOWPOWER_H

/***************************************************************************************************
* INCLUDE FILES
***************************************************************************************************/

#include "infrastructure/N_Types/include/N_Types.h"

/***************************************************************************************************
* C++ DECLARATION WRAPPER
***************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************************************
* EXPORTED TYPES
***************************************************************************************************/

typedef enum N_LowPower_SleepMode_t
{
    N_LowPower_SleepMode_AllowSleep,
    N_LowPower_SleepMode_KeepAwake,
} N_LowPower_SleepMode_t;

typedef enum N_LowPower_SleepStatus_t
{
    N_LowPower_SleepStatus_EnterSleep,
    N_LowPower_SleepStatus_LeaveSleep,
} N_LowPower_SleepStatus_t;

typedef enum N_LowPower_SleepLevel_t
{
    N_LowPower_SleepLevel_Timed,    //< sleep with timer running to wake up
    N_LowPower_SleepLevel_Deep,     //< sleep until interrupted, no timer running
} N_LowPower_SleepLevel_t;

/** Type of the callback function used in subscriptions to this component.
    \param status Enum indicating whether the device is going to sleep or waking up

    Called just before the device goes to sleep or just after it wakes up.
    It is not possible to influence the decision to go to sleep from the
    callback.
*/
typedef void (*N_LowPower_Callback_t)(N_LowPower_SleepStatus_t status, N_LowPower_SleepLevel_t level);

/***************************************************************************************************
* EXPORTED MACROS AND CONSTANTS
***************************************************************************************************/


/***************************************************************************************************
* EXPORTED FUNCTIONS
***************************************************************************************************/
/**************************************************************************//**
  \brief Subscribe for notifications from this component.

  \param pCallback The callback to subscribe

  \return None.
 *****************************************************************************/
void N_LowPower_Subscribe(N_LowPower_Callback_t pCallback);

/**************************************************************************//**
  \brief Set the sleep mode. The mode after startup is "allow sleep".

  \param mode The mode (allow sleep, keep awake)

  \return None.
 *****************************************************************************/
void N_LowPower_SetSleepMode(N_LowPower_SleepMode_t mode);

/***************************************************************************************************
* END OF C++ DECLARATION WRAPPER
***************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif // N_LOWPOWER_H
