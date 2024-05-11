/*******************************************************************************
  APS RequestKey Header File

  Company
    Microchip Technology Inc.

  File Name
    apsRequestKey.h

  Summary
    Private interface of APS Request Key.

  Description
    This header file defines the interface to the APS request key functions.
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

#if !defined _APS_REQUEST_KEY_H
#define _APS_REQUEST_KEY_H

#if defined _SECURITY_ && defined _LINK_SECURITY_ 
/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <apsmeTransportKey.h>
#include <private/apsCommand.h>

/******************************************************************************
                                 Types section
 ******************************************************************************/
BEGIN_PACK
/* Request-Key Command Frame Format. See ZigBee spec r19, Figure 4.14. */
typedef struct PACK _ApsRequestKeyFrame_t
{
  /** An APS header, which comprises frame control and addressing information. */
  ApduCommandHeader_t header;
  /*  The key type field shall be set to 1 when the network key is being
   * requested, shall be set to 2 when an application key is being requested.
   * See ZigBee spec r19, 4.4.9.5.2, page 483. */
  uint8_t keyType;
  /*  When the key type field is 2 (that is, an application key), the partner
   * address field shall contain the extended 64-bit address of the partner
   * device that shall be sent the key. See ZigBee spec r19, 4.4.9.5.3 */
  uint8_t partnerAddress[sizeof(ExtAddr_t)];
} ApsRequestKeyFrame_t;
END_PACK

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Reset the internal queue and variables of APS Request Key component.
 ******************************************************************************/
APS_PRIVATE void apsRequestKeyReset(void);

/**************************************************************************//**
  \brief Transport key has been received, indicate to the upper-layer.

  \param[in] transportKeyInd - pointer to parameters of received key.
  \return None.
 ******************************************************************************/
APS_PRIVATE void apsRequestedKeyReceived(APS_TransportKeyInd_t *transportKeyInd);

/**************************************************************************//**
  \brief Request key indication handler.

  \param[in] commandInd - pointer to received command descriptor.

  \return 'true' if NWK buffer with the command frame must be freed
          otherwise return 'false'.
 ******************************************************************************/
APS_PRIVATE bool apsRequestKeyInd(const ApsCommandInd_t *const commandInd);

#else
#define apsRequestKeyInd NULL
#define apsRequestedKeyReceived(transportKeyInd) ((void)0)
#endif /* _SECURITY_ and _LINK_SECURITY_ */

#endif /* _APS_REQUEST_KEY_H */
