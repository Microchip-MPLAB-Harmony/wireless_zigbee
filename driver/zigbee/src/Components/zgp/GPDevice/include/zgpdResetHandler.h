// DOM-IGNORE-BEGIN
/*******************************************************************************
  Zigbee green power reset handler Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdResetHandler.h

  Summary:
    This file contains the zgpResetHandler header file.

  Description:
    This file contains the zgpResetHandler header file.
 *******************************************************************************/


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

// DOM-IGNORE-BEGIN
#ifndef _ZGPDRESETHANDLER_H
#define _ZGPDRESETHANDLER_H
// DOM-IGNORE-END

/******************************************************************************
                        Includes  section.
 ******************************************************************************/
 
#include <zgp/GPDevice/include/zgpdCommon.h>

/******************************************************************************
                        Types section.
 ******************************************************************************/
 
/******************************************************************************
                               ZGP reset Request
 ******************************************************************************/
 
typedef struct
{
  //! The result of the reset operation.
  ZGP_Status_t status;
}ZGP_ResetConf_t;

///* This will be used for ZGP data request*/
typedef struct _ZGP_ResetReq_t
{
    ZGP_Service_t service;
    //! MAC confirm callback function's pointer.
    void (*ZGP_ResetConf)(ZGP_ResetConf_t *conf);
    //! MCPS-DATA confirm parameters' structure.
    ZGP_ResetConf_t confirm;
}ZGP_ResetReq_t;

/******************************************************************************
                        Prototypes section.
 ******************************************************************************/ 

/**************************************************************************//**
  \brief zgp internal init handler 
  \param None
  \return None.
 ******************************************************************************/
void zgpInitHandler(void);

/**************************************************************************//**
  \brief zgp internal reset handler 
  \param None
  \return None.
 ******************************************************************************/
void zgpResetReqHandler(void);

/***************************************************************************//**
  \brief To raise ZGP reset Req
  \param reqParams - reset request parameters structure.
  \return None.
 ******************************************************************************/
void ZGP_ResetReq(ZGP_ResetReq_t *reqParams);

/***************************************************************************//**
  \brief set zgp channel.
  \param conf - confirm structure.
  \return None.
 ******************************************************************************/
void ZGP_SetChannel(uint8_t channel);

/***************************************************************************//**
  \brief get zgp channel.
  \param conf - confirm structure.
  \return None.
 ******************************************************************************/
void ZGP_GetChannel(uint8_t *channel);

#endif // _ZGPDDATAHANDLER_H

// eof zgpdResetHandler.h
