/*******************************************************************************
  ZCL Tests Source File

  Company:
    Microchip Technology Inc.

  File Name:
    zclForTests.c

  Summary:
    File zcl.c with tests extensions.

  Description:
    This File zcl.c contains tests extensions.
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
#include <zclUnitTesting.h>
#include <zcl.c>

/******************************************************************************
                    Implementation section
******************************************************************************/
/*************************************************************************//**
\brief Starts wait response timer. Only for testing purposes.
*****************************************************************************/
void ZCL_StartWaitResponseTimer(ZclMmBufferDescriptor_t *descriptor)
{
  zclStartWaitResponseTimer(descriptor);
}

/*************************************************************************//**
\brief Returns wait response timer. Only for testing purposes.
*****************************************************************************/
SYS_Timer_t* ZCL_GetWaitTimer(void)
{
  return &zclModuleMem.waitTimer;
}

/*************************************************************************//**
\brief Returns report timer. Only for testing purposes.
*****************************************************************************/
SYS_Timer_t* ZCL_GetReportTimer(void)
{
  return &zclModuleMem.reportTimer;
}

/*************************************************************************//**
\brief Calls wait response timer callback. Only for testing purposes.
*****************************************************************************/
void ZCL_WaitTimerFired(void)
{
  zclWaitTimerFired();
}

/*************************************************************************//**
\brief Calls report response timer callback. Only for testing purposes.
*****************************************************************************/
void ZCL_ReportTimerFired(void)
{
  zclReportTimerFired();
}

/*************************************************************************//**
\brief Calls zcLExecuteRequest. Only for testing purposes.
*****************************************************************************/
void ZCL_ExecuteRequest(ZCL_Request_t *req, ZclMmBuffer_t *buf)
{
  zclExecuteRequest(req, buf);
}

// eof zclForTests.c
