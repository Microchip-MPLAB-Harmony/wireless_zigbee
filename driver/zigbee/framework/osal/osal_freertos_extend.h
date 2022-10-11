/*******************************************************************************
  Operating System Abstraction Layer Extention for FreeRTOS

  Company:
    Microchip Technology Inc.

  File Name:
    osal_freertos_extend.h

  Summary:
    OSAL FreeRTOS extention implementation interface file

  Description:
    Interface file to extend the support of FreeRTOS by OSAL
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

#ifndef _OSAL_FREERTOS_EXTEND_H
#define _OSAL_FREERTOS_EXTEND_H

#ifdef __cplusplus
extern "C" {
#endif
// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "osal_freertos.h"

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

/* declare default data type handles. Any RTOS port must define it's own copy of these */
typedef QueueHandle_t              OSAL_QUEUE_HANDLE_TYPE;

typedef QueueSetHandle_t           OSAL_QUEUE_SET_HANDLE_TYPE;

typedef QueueSetMemberHandle_t     OSAL_QUEUE_SET_MEMBER_HANDLE_TYPE;

// *****************************************************************************
/* OSAL Result type

  Summary:
    Enumerated type representing the general return value from OSAL functions.

  Description:
    This enum represents possible return types from OSAL functions.

  Remarks:
    These enum values are the possible return values from OSAL functions
    where a standard success/fail type response is required. The majority
    of OSAL functions will return this type with a few exceptions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Section: Interface Routines Group
// *****************************************************************************
// *****************************************************************************
OSAL_RESULT OSAL_QUEUE_Create(OSAL_QUEUE_HANDLE_TYPE *queID, uint32_t queueLength, uint32_t itemSize);
OSAL_RESULT OSAL_QUEUE_CreateSet(OSAL_QUEUE_SET_HANDLE_TYPE *queID, uint32_t queueLength);
OSAL_RESULT OSAL_QUEUE_AddToSet(OSAL_QUEUE_SET_MEMBER_HANDLE_TYPE *queSetMember, OSAL_QUEUE_SET_HANDLE_TYPE *queSetID);
OSAL_RESULT OSAL_QUEUE_SelectFromSet(OSAL_QUEUE_SET_MEMBER_HANDLE_TYPE *queSetMember, OSAL_QUEUE_SET_HANDLE_TYPE *queSetID, uint16_t waitMS);
OSAL_RESULT OSAL_QUEUE_Send(OSAL_QUEUE_HANDLE_TYPE *queID, void *itemToQueue, uint16_t waitMS);
OSAL_RESULT OSAL_QUEUE_SendISR(OSAL_QUEUE_HANDLE_TYPE *queID, void  *itemToQueue);
OSAL_RESULT OSAL_QUEUE_Receive(OSAL_QUEUE_HANDLE_TYPE *queID, void  *pBuffer, uint16_t waitMS);
OSAL_RESULT OSAL_QUEUE_IsFullISR(OSAL_QUEUE_HANDLE_TYPE *queID);

#ifdef __cplusplus
}
#endif

#endif // _OSAL_FREERTOS_EXTEND_H

/*******************************************************************************
 End of File
*/
