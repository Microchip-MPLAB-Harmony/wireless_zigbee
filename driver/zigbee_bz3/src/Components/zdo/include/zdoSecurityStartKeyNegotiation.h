// DOM-IGNORE-BEGIN
/*******************************************************************************
  Zigbee device object security key negotiation method Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zdoSecurityStartKeyNegotiation.h

  Summary:
    This file contains the Implementation of zdo security start key negotiation request and response.

  Description:
    This file contains the Implementation of zdo security start key negotiation request and response.
 *******************************************************************************/


/*******************************************************************************
* Copyright (C) 2024 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _ZDO_SECURITY_START_KEY_NEGOTIATION_H_
#define _ZDO_SECURITY_START_KEY_NEGOTIATION_H_

#ifdef _ZIGBEE_REV_23_SUPPORT_
/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <systemenvironment/include/sysTypes.h>

/******************************************************************************
                                Types section
 ******************************************************************************/


/*****************************************************************************************************************
                                Prototypes section
 ****************************************************************************************************************/

/*************************************************************************************************************//**
  \brief ZDO Security Service Start Key Negotiation Response.

  \param[in] pApsKeyNegotiationReq - pointer to \ref APS_KeyNegotiationReq_t.

  \return None.
 ****************************************************************************************************************/
void ZDO_StartKeyNegotiationReq(APS_KeyNegotiationReq_t *pApsKeyNegotiationReq);

/**************************************************************************//**
  \brief Response function for Zdo security start key negotiation request

  \param[in] - None.

  \return None.
 ******************************************************************************/
void ZDO_SendKeyNegotiationResp(void);

/**************************************************************************//**
  \brief Set the callback function.
         This callback function invoked when the Key negotiation request is received.
  \param[in]  reqIndCb  - Callback function

  \return None.
 ******************************************************************************/
void ZDO_SetKeyNegotiationReqIndCb(void (*reqIndCb)(ExtAddr_t deviceExtAddr));

#endif /* _ZIGBEE_REV_23_SUPPORT_ */
#endif /*  _ZDO_SECURITY_START_KEY_NEGOTIATION_H_  */