/*******************************************************************************
  TrustCentre Key Update Handler Header File

  Company:
    Microchip Technology Inc.

  File Name:
    tcKeyUpdateHandler.h

  Summary:
    This file contains the Trust Centre key update routine declaration.

  Description:
    This file contains the Trust Centre key update routine declaration.
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


#ifndef _TCKEYUPDATEHANDLERH
#define _TCKEYUPDATEHANDLERH

/******************************************************************************
                        Includes section.
******************************************************************************/
#include <sysQueue.h>
#include <appTimer.h>
#include <aps.h>
#include <tc.h>


typedef struct
{
  QueueDescriptor_t reqQueueDescr;
  APS_KeyHandle_t  keyHandle;
  void              *currentReq;
  TC_KeyUpdateReq_t keyUpdateReq;
  union
  {
    APS_TransportKeyReq_t transportKeyReq;
    APS_SwitchKeyReq_t    switchKeyReq;
    HAL_AppTimer_t        keyUpdateTimer;
  };
} TcKeyUpdateHandlerMem_t;

/******************************************************************************
                        Functions prototypes section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.

  \param TBD.
  \return TBD.
******************************************************************************/
void tcKeyUpdateTaskHandler(void);

/**************************************************************************//**
  \brief TBD.

  \param TBD.
  \return TBD.
******************************************************************************/
void tcResetKeyUpdateHandler(void);

#endif //_TCKEYUPDATEHANDLERH
// eof tcKeyUpdateHandler.h
