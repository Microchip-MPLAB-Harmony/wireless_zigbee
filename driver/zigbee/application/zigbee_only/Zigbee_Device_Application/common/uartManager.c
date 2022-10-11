/*******************************************************************************
  Uart Manager Source File

  Company:
    Microchip Technology Inc.

  File Name:
    uartManager.c

  Summary:
    This file contains the Uart Manager implementation.

  Description:
    This file contains the Uart Manager implementation.
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

#if (APP_DEVICE_EVENTS_LOGGING == 1) || (APP_ENABLE_CONSOLE == 1)

/*******************************************************************************
                             Includes section
*******************************************************************************/
#include <drv_usart.h>
#include <console.h>

/*******************************************************************************
                             Definition(s) section
*******************************************************************************/
#define USART_RX_BUFFER_LENGTH 150
/*******************************************************************************
                             Local variables section
*******************************************************************************/
_DRV_UART_AsyncDev_T *dev = &g_uartDev[0];

/*******************************************************************************
                             Prototypes section
*******************************************************************************/

/*******************************************************************************
                             Implementation section
*******************************************************************************/
/**************************************************************************//**
/brief Inits UART, register UART callbacks
*******************************************************************************/
void uartDrvInit(_DRV_UART_AsyncCb_T *console )
{

#if (CPU_CLK_HZ == 48000000 )
  DRV_UART0_Init(DRV_UART_48MHZ_115200,USART_RX_BUFFER_LENGTH, NULL);
#elif (CPU_CLK_HZ == 64000000 )
  DRV_UART0_Init(DRV_UART_64MHZ_115200,USART_RX_BUFFER_LENGTH, NULL);
#endif  

  DRV_UART_EventRegister(dev, console);
}

#endif // (APP_DEVICE_EVENTS_LOGGING == 1) || (APP_ENABLE_CONSOLE == 1)

// eof uartManager.c
