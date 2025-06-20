/*******************************************************************************
  Zigbee green power device manager Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdManager.h

  Summary:
    This file contains the Main MAC layer requests manager header file.

  Description:
    This file contains the Main MAC layer requests manager header file.

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

#ifndef ZGPDMANAGER_H
#define ZGPDMANAGER_H
/******************************************************************************
                        Includes  section.
******************************************************************************/
/******************************************************************************
                        Types section.
******************************************************************************/
/** Identifiers of ZGP task handlers. */
typedef enum _ZgpTaskID_t
{
  ZGP_TASK_INIT_ID,
  ZGP_TASK_RESET_REQ_ID,
  ZGP_TASK_DATA_REQ_ID,
  ZGP_TASK_CHANNEL_REQ_ID,
  ZGP_TASK_COMMISSIONING_ID,
  ZGP_TASKS_SIZE
} ZgpTaskID_t;

/** Bit array of ZGP task. If bit is '1' the task is posted. */
typedef uint32_t ZgpTaskBitMask_t;

/** Type of iterator for task identifiers. */
typedef uint8_t ZgpTaskIdIter_t;

/******************************************************************************
  Status of current operation which could be returned from particular handler.
******************************************************************************/
typedef enum
{
    ZGP_SUCCESS_HNDLR_RESULT,
    ZGP_IN_PROGRESS_HNDLR_RESULT,
}ZgpHandlerResult_t;

/******************************************************************************
                        Prototypes section.
******************************************************************************/
void zgpPostTask(const ZgpTaskID_t taskID);
/**************************************************************************//**
  \brief zgp Main task handler 
  \param none
  \return none.
******************************************************************************/
void ZGP_TaskHandler(void);
void zgpSendConfToUpperLayer(void *request);
bool zgpPutReqInQueue(void *request);
#endif //ZGPDMANAGER_H

// eof zgpdManager.h
