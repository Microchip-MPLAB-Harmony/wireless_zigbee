/*******************************************************************************
  NWK Rx Security Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkRxSecurity.h

  Summary:
    This file comprises the Interface of security processing of incoming packets.

  Description:
    This file comprises the Interface of security processing of incoming packets..
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

#if !defined _NWK_RX_SECURITY_H
#define _NWK_RX_SECURITY_H

#if defined _SECURITY_
/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <nwkSecurity.h>

/******************************************************************************
                              Prototypes section
 ******************************************************************************/

/**************************************************************************//**
  \brief Get network key by key sequence number.

  \return Pointer to value of a network key.
 ******************************************************************************/
NWK_PRIVATE const uint8_t* NWK_GetKey(const NWK_KeySeqNum_t seqNum);

#endif /* _SECURITY_ */
#endif /* _NWK_RX_SECURITY_H */
/** eof nwkRxSecurity.h */

