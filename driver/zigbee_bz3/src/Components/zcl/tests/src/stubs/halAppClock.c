/*******************************************************************************
  Hal App Clock Source File

  Company:
    Microchip Technology Inc.

  File Name:
    halAppClock.c

  Summary:
    Hal App Clock stub

  Description:
    This file contains Hal App Clock stub.
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


/******************************************************************************
                    Includes section
******************************************************************************/
#include <halAppClock.h>

/******************************************************************************
                    Local variables section
******************************************************************************/
static uint32_t appTime;

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Returns time of application timer.

\returns time in ms.
******************************************************************************/
uint32_t halGetTimeOfAppTimer(void)
{
  return appTime;
}

/**************************************************************************//**
\brief Sets time of application timer.

\param[in] time - time in ms.
******************************************************************************/
void halSetTimeOfAppTimer(uint32_t time)
{
  appTime = time;
}

// eof halAppClock.c
