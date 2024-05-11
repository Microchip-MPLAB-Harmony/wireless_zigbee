/*******************************************************************************
 System Tasks File

  Company:
    Microchip Technology Inc.

  File Name:
    system_tasks.c

  Summary:
   This file contains source code necessary to maintain system's polled tasks.

  Description:
    This file contains source code necessary to maintain system's polled tasks.
    It implements the "SYS_Tasks" function that calls the individual "Tasks"
    functions for all polled MPLAB Harmony modules in the system.
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "FreeRTOS.h"
#include "task.h"

#include "zgb_api.h"

#define TASK_APP_STACK_SIZE (8 *1024 / sizeof(portSTACK_TYPE))
#define TASK_APP_PRIORITY (tskIDLE_PRIORITY + 2) // FreeRTOS Timer task is at priority 1

#define TASK_BLE_STACK_SIZE (512 / sizeof(portSTACK_TYPE))
#define TASK_BLE_PRIORITY (tskIDLE_PRIORITY + 3)


#define TASK_ZGB_STACK_SIZE (8 *1024 / sizeof(portSTACK_TYPE))
#define TASK_ZGB_PRIORITY (tskIDLE_PRIORITY + 3)

extern void APP_Task(void *p);

/*******************************************************************************
  Function:
    void SYS_Tasks(void)

  Remarks:
    See prototype in system_tasks.h.
*/

void SYS_Tasks(void)
{  
  if (xTaskCreate(zigbee_task, "ZGB", TASK_ZGB_STACK_SIZE, NULL, TASK_ZGB_PRIORITY, NULL) != pdPASS)
      while (1);

  if (xTaskCreate(APP_Task, "APP", TASK_APP_STACK_SIZE, NULL, TASK_APP_PRIORITY, NULL) != pdPASS)
      while (1);

  vTaskStartScheduler();
}