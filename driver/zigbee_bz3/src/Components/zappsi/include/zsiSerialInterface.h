/*******************************************************************************
  ZAppSI Serial Interface Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiSerialController.h

  Summary:
    This file contains the Defines to abstract serial interfaces.

  Description:
    This file contains the Defines to abstract serial interfaces.
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


#ifndef ZSISERIALINTERFACE_H
#define ZSISERIALINTERFACE_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <rs232Controller.h>
#if APP_ZAPPSI_INTERFACE == APP_INTERFACE_USBFIFO
  #include <usbFifoUsart.h>
#endif // APP_INTERFACE_USBFIFO

#if APP_ZAPPSI_INTERFACE == APP_INTERFACE_USART
  #include <usart.h>
#endif // APP_INTERFACE_USART

/******************************************************************************
                    Defines section
******************************************************************************/
#if APP_ZAPPSI_INTERFACE == APP_INTERFACE_USART
  INLINE int OPEN_ZAPPSI_INTERFACE(HAL_UsartDescriptor_t *descriptor)\
  {\
    BSP_EnableRs232();
    return HAL_OpenUsart(descriptor);\
  }
  INLINE int CLOSE_ZAPPSI_INTERFACE(HAL_UsartDescriptor_t *descriptor)\
  {\
    BSP_DisableRs232();
    return HAL_CloseUsart(descriptor);\
  }
  #define WRITE_ZAPPSI_INTERFACE           HAL_WriteUsart
  #define READ_ZAPPSI_INTERFACE            HAL_ReadUsart
  #define ZAPPSI_INTERFACE_TASK            HAL_TASK_USART
  #define HOLD_ADDITIONAL_ZAPPSI_INTERFACE_TASKS(TTY)  HAL_HoldOnOthersUsartTasks(TTY)
  #define RELEASE_ADDITIONAL_ZAPPSI_INTERFACE_TASKS()  HAL_ReleaseAllHeldUsartTasks()
#endif // APP_INTERFACE_USART

#if APP_ZAPPSI_INTERFACE == APP_INTERFACE_USBFIFO
  #define OPEN_ZAPPSI_INTERFACE            USBFIFO_OpenUsart
  #define CLOSE_ZAPPSI_INTERFACE           USBFIFO_CloseUsart
  #define WRITE_ZAPPSI_INTERFACE           USBFIFO_WriteUsart
  #define READ_ZAPPSI_INTERFACE            USBFIFO_ReadUsart
  #define ZAPPSI_INTERFACE_TASK            HAL_EXT_HANDLER
  #define HOLD_ADDITIONAL_ZAPPSI_INTERFACE_TASKS(TTY)
  #define RELEASE_ADDITIONAL_ZAPPSI_INTERFACE_TASKS()
#endif // APP_INTERFACE_USBFIFO
#endif // ZSISERIALINTERFACE_H

// eof zsiSerialInterface.h
