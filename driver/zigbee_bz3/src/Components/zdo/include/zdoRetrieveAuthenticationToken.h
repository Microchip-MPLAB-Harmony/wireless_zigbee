// DOM-IGNORE-BEGIN
/*******************************************************************************
  Zigbee device object retrieve authentication token method Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zdoRetrieveAuthenticationToken.h

  Summary:
    This file contains the Implementation of zdo retrieve authentication token 
  request and response.

  Description:
    This file contains the Implementation of zdo retrieve authentication token 
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

#ifndef ZDO_RETRIEVE_AUTHENTICATION_TOKEN_H
#define ZDO_RETRIEVE_AUTHENTICATION_TOKEN_H

#ifdef _ZIGBEE_REV_23_SUPPORT_
/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <systemenvironment/include/sysTypes.h>

/******************************************************************************
                                Types section
 ******************************************************************************/

/******************************************************************************
                        Prototypes section
 ******************************************************************************/

/*******************************************************************************
\brief Sends the Secrity Retrieve Authentication token request

\param[in] tokenIdType - Tlv tag id for the type of authentication token
\param[in] callback - Callback function from response

\return None.
*****************************************************************************/
void ZDO_SendRetrieveAuthenticationTokenReq(uint8_t tokenIdType, void (*callback)(void));

#endif /* _ZIGBEE_REV_23_SUPPORT_ */
#endif /*  ZDO_RETRIEVE_AUTHENTICATION_TOKEN_H  */