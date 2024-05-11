/*******************************************************************************
  NWK Keys Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkKeys.h

  Summary:
    This file contains the NWK keys internal structure.

  Description:
    This file contains the NWK keys internal structure.
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

#if !defined _NWK_KEYS_H
#define _NWK_KEYS_H

#if defined _SECURITY_
/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <nwkSecurity.h>

/******************************************************************************
                               Types section
 ******************************************************************************/
/** NWK keys service structure */
typedef struct _NWK_Keys_t
{
  /** Total amount of NWK security keys. */
  NwkKeyAmount_t keyAmount;
  /** Set of network security material descriptors capable of maintaining
   * an active and alternate network key. */
  NWK_SecurityKey_t *key;
} NWK_Keys_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/

/**************************************************************************//**
  \brief Get key index by key sequence number.

  \param[in] seqNum - key sequence number.
  \return Index of key entry or NWK_INVALID_KEY_INDEX if entry isn't found.
 ******************************************************************************/
NWK_PRIVATE NwkKeyIndex_t nwkFindKeyIndex(const NWK_KeySeqNum_t seqNum);

#endif /* _SECURITY_ */
#endif /* _NWK_KEYS_H */
/** eof nwkKeys.h */

