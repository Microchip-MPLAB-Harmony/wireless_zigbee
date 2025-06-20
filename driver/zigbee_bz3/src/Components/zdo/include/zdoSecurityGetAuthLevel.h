// DOM-IGNORE-BEGIN
/*******************************************************************************
  Zigbee device object Security Get Authentication Level Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zdoSecurityGetAuthLevel.h

  Summary:
    This file contains the Implementation of zdo security authentication level 
  request and response.

  Description:
    This file contains the Implementation of zdo security authentication level 
  request and response.
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

#ifndef  ZDO_SECURITY_GET_AUTHENTICATION_LEVEL_H_
#define  ZDO_SECURITY_GET_AUTHENTICATION_LEVEL_H_

#ifdef _ZIGBEE_REV_23_SUPPORT_
/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <systemenvironment/include/sysTypes.h>

/******************************************************************************
                                Definitions section
 ******************************************************************************/

/******************************************************************************
                                Types section
 ******************************************************************************/

/*****************************************************************************************************************
                                Prototypes section
 ****************************************************************************************************************/
/**************************************************************************//**
\brief Sends the Security Authenticaton Level Request.
\description This request and response are used to query and determine  
             authentication level with trust center about a 3rd party.

\param[in] targetAddrTlv - 3rd party Extended (64-bit) address.

\return None.
******************************************************************************/
void ZDO_GetAuthLevelReq(ExtAddr_t destAddr);

#endif /* _ZIGBEE_REV_23_SUPPORT_ */
#endif /*  ZDO_SECURITY_GET_AUTHENTICATION_LEVEL_H_  */
