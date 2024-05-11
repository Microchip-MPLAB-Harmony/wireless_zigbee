/*******************************************************************************
  TrustCentre Task Manager Header File

  Company:
    Microchip Technology Inc.

  File Name:
    tcTaskManager.h

  Summary:
    This file contains the Security Trust Centre task manager routine.

  Description:
    This file contains the Security Trust Centre task manager handler.
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


#ifndef _TCTASKMANAGER_H
#define _TCTASKMANAGER_H

/******************************************************************************
                            Includes section.
******************************************************************************/
#include <sysTypes.h>

/******************************************************************************
                             Types section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef enum
{
  //TC_TASK_RESET,
  TC_TASK_KEY_UPDATE,
#ifdef _LINK_SECURITY_
  TC_TASK_KEY_ESTABLISH,
#endif // _LINK_SECURITY_
  TC_TASK_REMOVE,
} tcTaskID_t;

/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef uint8_t TcTaskBitMask_t;

/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef struct
{
  TcTaskBitMask_t taskBitMask;
} TcTaskManagerMem_t;

/******************************************************************************
                        Functions prototypes section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.

  \param TBD.
  \return TBD.
******************************************************************************/
void tcPostTask(tcTaskID_t taskID);

/**************************************************************************//**
  \brief TBD.

  \param TBD.
  \return TBD.
******************************************************************************/
void tcResetTaskManager(void);

#endif // _TCTASKMANAGER_H

// eof tcTaskManager.h
