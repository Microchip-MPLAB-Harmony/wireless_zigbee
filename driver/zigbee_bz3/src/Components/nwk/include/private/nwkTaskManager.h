/*******************************************************************************
  NWK Task Manager Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_adv.hnwkTaskManager.h

  Summary:
    This file defines the interface to the NWK Task Handling mechanism.

  Description:
    This file defines the interface to the NWK Task Handling mechanism.
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

#if !defined _NWK_TASK_MANAGER_H
#define _NWK_TASK_MANAGER_H

/******************************************************************************
                             Includes section
 ******************************************************************************/
#include <sysTypes.h>

/******************************************************************************
                                Types section
 ******************************************************************************/
/** Identifiers of NWK task handlers. */
typedef enum _NwkTaskID_t
{
  NWK_TASK_RESET,
  NWK_TASK_SYNC,
  NWK_TASK_ADDR_CONFLICT,
  NWK_TASK_TX,
  NWK_TASK_ROUTE_DISCOVERY,
  NWK_TASK_ROUTE_DISCOVERY_TABLE,
  NWK_TASK_START_ROUTER,
  NWK_TASK_PERMIT_JOINING,
  NWK_TASK_DISCOVERY_REQ,
  NWK_TASK_FORMATION_REQ,
  NWK_TASK_JOIN_REQ,
  NWK_TASK_JOIN_IND,
  NWK_TASK_LEAVE,
  NWK_TASK_EDSCAN,
  NWK_TASK_DATA_CONF,
  NWK_TASK_LOOPBACK,
  NWK_TASK_ROUTE_RECORD,
  NWK_TASK_DIRECT_JOIN,
  NWK_TASK_ORPHAN,
  NWK_TASK_SILENT_JOIN,
  NWK_TASK_MANYTOONE,
  NWK_TASK_ALLOC_DATA_REQ,
  NWK_TASK_ENDDEVICE_TIMEOUT_REQ,
  NWK_TASK_ENDDEVICE_TIMEOUT_IND,
  NWK_TASKS_SIZE
} NwkTaskID_t;

/** Bit array of NWK task. If bit is '1' the task is posted. */
typedef uint32_t NwkTaskBitMask_t;

/** Type of iterator for task identifiers. */
typedef uint8_t NwkTaskIdIter_t;

typedef struct _NwkTaskManager_t
{
  NwkTaskBitMask_t bitMap;
  NwkTaskIdIter_t current;
} NwkTaskManager_t;

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/******************************************************************************
  \brief post NWK task.

  \param taskID - identifier of NWK task.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkPostTask(const NwkTaskID_t taskID);

/******************************************************************************
  \brief Cancel NWK task.

  \param[in] mask - bit mask of NWK task dentifier.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkClearTaskBit(const NwkTaskBitMask_t mask);

/******************************************************************************
  \brief Reset the task manager.
 ******************************************************************************/
NWK_PRIVATE void nwkResetTaskManager(void);

#endif /* _NWK_TASK_MANAGER_H */
/** eof nwkTaskManager.h */

