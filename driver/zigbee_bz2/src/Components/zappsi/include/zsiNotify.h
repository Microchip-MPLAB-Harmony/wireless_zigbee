/*******************************************************************************
  ZAppSI Notify Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiNotify.h

  Summary:
    This file contains the Functions for raising ZSI notifications.

  Description:
    This file contains the Functions for raising ZSI notifications.
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


#ifndef ZSI_NOTIFY_H
#define ZSI_NOTIFY_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <sysTypes.h>

/******************************************************************************
                                 Types section
 ******************************************************************************/
typedef enum
{
  ZSI_LOST_SYNCHRONIZATION = 0x00,
}ZSI_Status_t;

typedef struct _ZSI_UpdateNotf_t
{
  ZSI_Status_t status;
}ZSI_UpdateNotf_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/**************************************************************************//**
\brief Indicates zsi status update.
******************************************************************************/
void ZSI_StatusUpdateNotf(ZSI_UpdateNotf_t *notf);

/**************************************************************************//**
\brief Subscribe legacy ZSI notifications to events.
******************************************************************************/
void zsiInitNotifications(void);

#endif // ZSI_NOTIFY_H
// eof zsiNotify.h
