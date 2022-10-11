/*******************************************************************************
  APS VerifyKey Header File

  Company
    Microchip Technology Inc.

  File Name
    apsVerifyKey.h

  Summary
    Private interface of APS Verify Key.

  Description
    This header file defines the interface to the APS verify key and confirm key functions.
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

#if !defined _APS_VERIFY_KEY_H
#define _APS_VERIFY_KEY_H

#if defined _SECURITY_ && defined _LINK_SECURITY_ 
/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <private/apsCommand.h>
#include <apsmeVerifyKey.h>

/******************************************************************************
                                 Types section
 ******************************************************************************/
BEGIN_PACK
/* Verify-Key Command Frame Format. See ZigBee spec r21. */
typedef struct PACK _ApsVerifyKeyFrame_t
{
  /** An APS header, which comprises frame control and addressing information. */
  ApduCommandHeader_t header;
  /*  The key type field shall be set to 4 when the Trust Center Link Key is being
   * verified. In r21 spec, only TCLK verification is supported. */
  uint8_t keyType;
  /*  Address of the destination device (IEEE address of the Trust Center), who
   * will verify the TCLK */
  uint8_t destAddress[sizeof(ExtAddr_t)];
  /* Hash value of TCLK from initiator */
  uint8_t hashValue[SECURITY_KEY_SIZE];
} ApsVerifyKeyFrame_t;
END_PACK

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Reset the internal queue and variables of APS Verify Key component.
 ******************************************************************************/
APS_PRIVATE void apsVerifyKeyReset(void);

/**************************************************************************//**
  \brief Transport key has been received, indicate to the upper-layer.

  \param[in] transportKeyInd - pointer to parameters of received key.
  \return None.
 ******************************************************************************/
APS_PRIVATE void apsConfirmKeyReceived(APS_ConfirmKeyInd_t *confirmKeyInd);

/**************************************************************************//**
  \brief Confirm key indication handler.

  \param[in] commandInd - pointer to received command descriptor.

  \return 'true' if NWK buffer with the command frame must be freed
          otherwise return 'false'.
 ******************************************************************************/
APS_PRIVATE bool apsConfirmKeyInd(const ApsCommandInd_t *const commandInd);

#else
//#define apsVerifyKeyInd NULL
#define apsConfirmKeyReceived(confirmKeyInd) ((void)0)
#define apsConfirmKeyInd(commandInd) ((void)0)
#endif /* _SECURITY_ and _LINK_SECURITY_ */

#endif /* _APS_VERIFY_KEY_H */
