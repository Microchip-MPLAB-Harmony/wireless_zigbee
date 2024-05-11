/*******************************************************************************
  APS TaskManager Header File

  Company
    Microchip Technology Inc.

  File Name
    apsTaskManager.h

  Summary
    Header file of APS task manager.

  Description
    This header file defines the APS task manager functionalities.
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

#if !defined _APS_TASK_MANAGER_H
#define  _APS_TASK_MANAGER_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <sysTypes.h>

/******************************************************************************
                                Types section
 ******************************************************************************/
/** Identifiers of APS task handlers. */
typedef enum  _ApsTaskID_t
{
  APS_TASK_STATE_MACHINE,
  APS_TASK_DATA,
  APS_TASK_SECURITY,
  APS_TASK_COMMAND_REQ,
  APS_TASK_AUTH_REQ,
  APS_TASK_SKKE_REQ,
  APS_TASK_SKKE_RESP,
  APS_TASK_TRANSPORT_KEY,
  APS_TASKS_SIZE
} ApsTaskID_t;

/** Bit array of APS task. If bit is '1' the task is posted. */
typedef uint8_t ApsTaskBitMask_t;

/** Type of iterator for task identifiers. */
typedef uint8_t ApsTaskIdIter_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/******************************************************************************
  \brief post APS task.

  \param taskID - identifier of APS task.
  \return None.
 ******************************************************************************/
APS_PRIVATE void apsPostTask(const ApsTaskID_t taskID);

/******************************************************************************
  \brief Reset the APS task manager.
 ******************************************************************************/
APS_PRIVATE void apsResetTaskManager(void);

#endif /* _APS_TASK_MANAGER_H */
/** eof apsTaskManager.h */

