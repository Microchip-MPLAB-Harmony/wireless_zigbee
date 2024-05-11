/*******************************************************************************
  TrustCentre Authentication Handler Header File

  Company:
    Microchip Technology Inc.

  File Name:
    tcAuthenticHandler.h

  Summary:
    This file contains the Trust Centre authentic routine declaration.

  Description:
    This file contains the Trust Centre authentic routine declaration.
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


#ifndef _TCAUTHENTICHANDLERH
#define _TCAUTHENTICHANDLERH

/******************************************************************************
                             Includes section.
******************************************************************************/
#include <aps.h>
#include <sysTypes.h>
#include <tcAuthentic.h>

/******************************************************************************
                             Types section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef struct
{
  TC_AuthenticObj_t *authenticObj;
  uint8_t           maxRequests;
} TcAuthenticHandlerMem_t;

/******************************************************************************
                             Functions prototypes section.
******************************************************************************/

/******************************************************************************
                             Functions prototypes section.
******************************************************************************/
/**************************************************************************//**
  \brief TBD.

  \param TBD.
  \return TBD.
******************************************************************************/
void tcUpdateDeviceIndToAuthenticHandler(APS_UpdateDeviceInd_t *indParam, const ShortAddr_t *parentShortAddr);


/**************************************************************************//**
  \brief TBD.

  \param TBD.
  \return TBD.
******************************************************************************/
void tcResetAuthenticHandler(void);

#endif //_TCAUTHENTICHANDLERH

// eof tcAuthenticHandler.h
