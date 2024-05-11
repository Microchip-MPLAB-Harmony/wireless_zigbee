/*******************************************************************************
  APS ConfirmKey Header File

  Company
    Microchip Technology Inc.

  File Name
    apsConfirmKey.h

  Summary
    Private interface of APS Confirm Key.

  Description
    This header file defines the private interface to the APS Confirm Key functions.
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

#if !defined _APS_CONFIRM_KEY_H
#define _APS_CONFIRM_KEY_H

#if defined _SECURITY_ && defined _LINK_SECURITY_ 
/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <private/apsCommand.h>
#include <apsmeConfirmKey.h>

/******************************************************************************
                                 Types section
 ******************************************************************************/
BEGIN_PACK
/* Confirm-Key Command Frame Format. See ZigBee spec r21. */
typedef struct PACK _ApsConfirmKeyFrame_t
{
  /** An APS header, which comprises frame control and addressing information. */
  ApduCommandHeader_t header;
  /* The status of key verification done */
  uint8_t status;
  /*  The key type field shall be set to 4 when the Trust Center Link Key is being
   * confirm. In r21 spec, only TCLK verification is supported. */
  uint8_t keyType;
  /*  Address of the destination device (IEEE address of the Trust Center), who
   * requested the TCLK verification */
  uint8_t destAddress[sizeof(ExtAddr_t)];
} ApsConfirmKeyFrame_t;
END_PACK

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Reset the internal queue and variables of APS Confirm Key component.
 ******************************************************************************/
APS_PRIVATE void apsConfirmKeyReset(void);

/**************************************************************************//**
  \brief Verify key indication handler.

  \param[in] commandInd - pointer to received command descriptor.

  \return 'true' if NWK buffer with the command frame must be freed
          otherwise return 'false'.
 ******************************************************************************/
APS_PRIVATE bool apsVerifyKeyInd(const ApsCommandInd_t *const commandInd);

/**************************************************************************//**
  \brief Reset the internal queue and variables of APS Confirm Key component.
 ******************************************************************************/
APS_PRIVATE void apsConfirmKeyReset(void);


#else
//#define apsVerifyKeyInd NULL
#define apsConfirmKeyReceived(confirmKeyInd) ((void)0)
#define apsVerifyKeyInd(commandInd) ((void)0)
#endif /* _SECURITY_ and _LINK_SECURITY_ */

#endif /* _APS_VERIFY_KEY_H */
