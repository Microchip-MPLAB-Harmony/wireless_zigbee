/*******************************************************************************
  ZAppSI Task Manager Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiTaskManager.h

  Summary:
    This file contains the ZAppSI task manager interface.

  Description:
    This file contains the ZAppSI task manager interface.
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


#ifndef ZSITASKMANAGER_H
#define ZSITASKMANAGER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <sysTypes.h>

/******************************************************************************
                    Types section
******************************************************************************/

/* ZAppSI task identifiers */
typedef enum _ZsiTaskId_t
{
  ZSI_INIT_TASK_ID,
  ZSI_SERIAL_TASK_ID,
  ZSI_DRIVER_TASK_ID,
  ZSI_TASKS_AMOUNT,
} ZsiTaskId_t;

/* ZAppSI posted task bit mask */
typedef uint8_t ZsiTaskBitMask_t;
/* ZAppSI task handler */
typedef void (*ZsiTaskHandler_t)(void);
/* ZAppSI Task Manager description */
typedef struct _ZsiTaskManager_t
{
  ZsiTaskBitMask_t pendingTasks;
} ZsiTaskManager_t;
/******************************************************************************
                    Prototypes section
******************************************************************************/
/******************************************************************************
  \brief Post ZAppSI component task.

  \param[in] taskId - component task identifier.

  \return None.
 ******************************************************************************/
void zsiPostTask(ZsiTaskId_t taskId);

/******************************************************************************
  \brief Task manager reset routine.
 ******************************************************************************/
void zsiResetTaskManager(void);

#endif /* ZSITASKMANAGER_H */
