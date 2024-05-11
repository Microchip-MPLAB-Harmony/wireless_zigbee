/*******************************************************************************
  NWK Tx Security Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkTxSecurity.h

  Summary:
    This file provides the Interface to the NWK layer Transmission Security.

  Description:
    This file provides the Interface to the NWK layer Transmission Security.
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

#if !defined _NWK_TX_SECURITY_H
#define _NWK_TX_SECURITY_H

#if defined _SECURITY_
/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <mac.h>
#include <sspSfp.h>
#include <private/nwkTx.h>

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Check of that enciphering for a proceeding network packet is required.

  \param[in] outPkt - pointer to a network output packet.
  \return 'true' if encrypting is required otherwise 'false'
 ******************************************************************************/
NWK_PRIVATE bool nwkIsEncryptionRequired(NwkOutputPacket_t *const outPkt);

/**************************************************************************//**
  \brief Request to encrypt an output network packet.

  \param[in] encryptReq - encrypt frame primitive's parameters structure.
  \param[in] macDataReq - MCPS-DATA request primitive's parameters structure.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkEncryptOutputPacket(SSP_EncryptFrameReq_t *const encryptReq,
  const MAC_DataReq_t *const macDataReq);

/**************************************************************************//**
  \brief Is decrypting of output packet required?

  \param[in] outPkt - pointer to an output packet.
  \return 'true' if decrypting is required otherwise 'false'.
 ******************************************************************************/
NWK_PRIVATE bool nwkIsDecryptionRequired(NwkOutputPacket_t *const outPkt);

/**************************************************************************//**
  \brief Request to decrypt an output network packet.

  \param[in] decryptReq - decrypt frame primitive's parameters structure.
  \param[in] macDataReq - MCPS-DATA request primitive's parameters structure.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkDecryptOutputPacket(SSP_DecryptFrameReq_t *const decryptReq,
  const MAC_DataReq_t *const macDataReq);

#else /* _SECURITY_ */

#define nwkIsEncryptionRequired(outPkt) false
#define nwkIsDecryptionRequired(outPkt) false

#endif /* _SECURITY_ */
#endif /* _NWK_TX_SECURITY_H */
/** eof nwkTxSecurity.h */

