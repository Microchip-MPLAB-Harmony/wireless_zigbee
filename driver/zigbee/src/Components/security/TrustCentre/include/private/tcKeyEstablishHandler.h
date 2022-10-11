/*******************************************************************************
  TrustCentre Key Establishment Handler Header File

  Company:
    Microchip Technology Inc.

  File Name:
    tcKeyEstablishHandler.h

  Summary:
    This file contains the Trust Centre end to end key establishment routine declarations.

  Description:
    This file contains the Trust Centre end to end key establishment routine declarations.
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


#ifndef _TCKEYESTABLISHHANDLERH
#define _TCKEYESTABLISHHANDLERH

#ifdef _LINK_SECURITY_
/******************************************************************************
                             Includes section.
******************************************************************************/
#include <aps.h>
#include <sysTypes.h>
#include <tcKeyEstablish.h>
#include <sspHash.h>

/******************************************************************************
                             Definitions section.
******************************************************************************/


/******************************************************************************
                             Types section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef enum
{
  TC_KEY_ESTABLISH_OBJ_STATE_IDLE,
  TC_KEY_ESTABLISH_OBJ_STATE_TRANSPORT_KEY_POSTED,
  TC_KEY_ESTABLISH_OBJ_STATE_FIRST_TRANSPORT_KEY_EXECUTING,
  TC_KEY_ESTABLISH_OBJ_STATE_SECOND_TRANSPORT_KEY_EXECUTING,
  TC_KEY_OBJ_STATE_TCLK_TRANSPORT,
  TC_KEY_OBJ_STATE_HASH_KEY_KEY,
  TC_KEY_OBJ_STATE_CONFIRM_KEY,
} TcKeyEstablishHandlerObjState_t;

/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef struct
{
  TC_KeyEstablishObj_t *keyEstablishObj;
  uint8_t              maxRequests;
} TcKeyEstablishHandlerMem_t;

/**************************************************************************//**
  \brief Holds TCLK hash for TC and Device.
******************************************************************************/


/******************************************************************************
                             Functions prototypes section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.

  \param TBD.
  \return TBD.
******************************************************************************/
void tcKeyEstablishTaskHandler(void);

/**************************************************************************//**
  \brief TBD.

  \param TBD.
  \return TBD.
******************************************************************************/
void tcResetKeyEstablishHandler(void);


#endif // _LINK_SECURITY_

#endif //_TCKEYESTABLISHHANDLERH
// eof tcKeyEstablishHandler.h
