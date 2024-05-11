/*******************************************************************************
  Application zgb initialisation

  Company:
    Microchip Technology Inc.

  File Name:
    zgb_init.c

  Summary:
    This file contains the zgb initialisation implemantation.

  Description:
    This file contains the zgb initialisation implemantation.
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

#include <RF231_RF212/PHY/include/phyPic32cx.h>
#include <halAppClock.h>
//#include <calibration.h>
#include <z3device/stack_interface/zgb_api.h>
#include <drv_usart.h>
#include <framework_defs.h>
#include <console.h>
#include <halAes.h>

#ifdef __XC32__
#include <xc.h>
#endif

ZB_AppGenericCallBack fnAppGenericCB;

bool PHY_Init(void);
extern void consoleRx(_DRV_UART_AsyncDev_T *dev, uint8_t data);

// Queue Pointer received from Application
extern OSAL_QUEUE_HANDLE_TYPE apiRequestQueueHandle; 

/******************************************************************************
Performs start up HAL initialization.
******************************************************************************/
void ZB_HAL_Init(void)
{
#if defined(_HAL_HW_AES_)
  halAesInit();
#endif
#if defined(_STATS_ENABLED_)
  halFillStack();
#endif
}

/*******************************************************************************
  Function:
    void zigbee_init(uint32_t *sram_vector_table)

  Remarks:
    See prototype in zigbee_task.h.
******************************************************************************/
void zigbee_init(uint32_t *sram_vector_table, 
                 OSAL_API_LIST_TYPE *osal_api_list, 
                 OSAL_QUEUE_HANDLE_TYPE *zigbeeRequestQueueHandle,
                 ZB_AppGenericCallBack app_callback)
{
  zos = osal_api_list;   // Store the OSAL functions to local pointer
  apiRequestQueueHandle = *zigbeeRequestQueueHandle;    // API Request queue from application task
  fnAppGenericCB = app_callback; // Generic callback pointer to Application
  
  ZB_HAL_Init();
#if APP_ENABLE_CONSOLE == 1
  _DRV_UART_AsyncCb_T console;
  console.rx_done_cb = &consoleRx;
  console.tx_done_cb = NULL;
  console.error_cb = NULL;
  uartDrvInit(&console);
#endif
  SYS_InitLog(); // It initializes the system logger
  
  if (!PHY_Init())     // It must be after ZB_HAL_Init()
  {
    //while(1);   // ERROR , Should not hang here
  }
}





