/*******************************************************************************
  Zigbee Cluster Library Task Manager Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zclTaskManager.h

  Summary:
    The header file describes the public interface of ZCL Task Manager.

  Description:
    The file describes the public interface and types of ZCL Task Manager
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


#ifndef _ZCLTASKMANAGER_H
#define _ZCLTASKMANAGER_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <systemenvironment/include/sysTypes.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/

/******************************************************************************
                   Types section
******************************************************************************/
/** Identifiers of ZCL task handlers. */
typedef enum _ZclTaskId_t
{
  ZCL_SUBTASK_ID,
  ZCL_PARSER_TASK_ID,
  ZCL_SECURITY_TASK_ID,
  ZCL_TASKS_SIZE
} ZclTaskId_t;

/** Bit array of ZCL task. If bit is '1' the task is posted. */
typedef uint8_t ZclTaskBitMask_t;

/** Type of iterator for task identifiers. */
typedef uint8_t ZclTaskIdIter_t;

/******************************************************************************
                   External variables section
******************************************************************************/

/******************************************************************************
                   Prototypes section
******************************************************************************/
/*************************************************************************//**
  \brief ZCL Task Manager post task function
  \param[in] taskId - Determines the task Id to be posted (ZclTaskId_t should be used)
*****************************************************************************/
void zclPostTask(ZclTaskId_t taskId);

/*************************************************************************//**
  \brief Task Manager task handler function
*****************************************************************************/
void ZCL_TaskHandler(void);

#endif  //#ifndef _ZCLTASKMANAGER_H

//eof zclTaskManager.h
