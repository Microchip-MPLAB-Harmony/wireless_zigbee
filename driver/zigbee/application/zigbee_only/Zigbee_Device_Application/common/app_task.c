/*******************************************************************************
  Application Task Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_task.c

  Summary:
    This file contains the Application task functions

  Description:
    This file contains the Application task functions
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

#include <z3device/stack_interface/zgb_api.h>
#include <z3device/stack_interface/bdb/include/bdb_api.h>
#include <z3device/stack_interface/zcl/include/zcl_api.h>
#include <z3device/stack_interface/configServer/include/cs_api.h>
#include <z3device/stack_interface/nwk/include/nwk_api.h>
#include <z3device/stack_interface/bdb/include/BDB_Unpack.h>
#include <configserver/include/configserver.h>
#include <aps/include/apsCommon.h>
#include <zcl/include/zclAttributes.h>
#include <z3device/common/include/z3Device.h>
#include <zcl/include/clusters.h>
#include <pds/include/wlPdsMemIds.h>
#include "app_task.h"

OSAL_QUEUE_HANDLE_TYPE g_appQueue;

void APP_Task(void *p)
{
  APP_Msg_T    appMsg[1];
  APP_Msg_T   *p_appMsg;
  p_appMsg=appMsg;
  (void) p;

  while (1)
  {
    if (OSAL_QUEUE_Receive(&g_appQueue, &appMsg, OSAL_WAIT_FOREVER))
    {
        if(p_appMsg->msgId == APP_MSG_ZB_STACK_EVT)
        {
            process_ZB_evt();
        }
//        else if( p_appMsg->msgId == APP_MSG_BLE_STACK_EVT)
//        {
//            process_BLE_evt((STACK_Event_T *)p_appMsg->msgData);
//        }
#if APP_ENABLE_CONSOLE == 1
        else if( p_appMsg->msgId == APP_MSG_UART_CMD_READY)
        {
            process_UART_evt((char*)(p_appMsg->msgData));
        }
#endif
    }
  }
}
