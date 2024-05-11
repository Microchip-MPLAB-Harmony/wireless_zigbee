/*******************************************************************************
  APS TransportTrustKey Header File

  Company
    Microchip Technology Inc.

  File Name
    apsTransportTrustKey.h

  Summary
    Interface of transport key from the trust center.

  Description
    This header file defines the interface of transport key from the trust center.
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

#if !defined _APS_TRANSPORT_TRUST_KEY_H
#define _APS_TRANSPORT_TRUST_KEY_H

#if defined _SECURITY_ && defined _LINK_SECURITY_ 
/******************************************************************************
                                 Includes section
 ******************************************************************************/
#include <private/apsTransportKey.h>

/******************************************************************************
                                  Types section
 ******************************************************************************/
BEGIN_PACK
/** Type of Transport-Key Command Frame (see ZigBee spec r19, Figure 4.8
 * with trust center master or link key descriptor field (see Figure 4.9). */
typedef struct PACK _ApsTransportTrustKeyFrame_t
{
  /** Common part of APS transport key command frame. */
  ApsTransportKeyCommonFrame_t common;
  /** The key sub-field shall contain the master key that should be used to set
   * up link keys with the Trust Center or link key. */
  uint8_t key[SECURITY_KEY_SIZE];
  /** The destination address sub-field shall contain the address of the device
   * which should use this master or link key. ZigBee spec r19, page 480. */
  uint8_t destinationAddress[sizeof(ExtAddr_t)];
  /** The source address sub-field shall contain the address of the device (for
   * example, the Trust Center) which originally sent this master key.
   * See ZigBee Specification r19, 4.4.9.2.3.1, page 480. */
  uint8_t sourceAddress[sizeof(ExtAddr_t)];
} ApsTransportTrustKeyFrame_t;
END_PACK

/******************************************************************************
                                Prototypes section
 ******************************************************************************/
#if defined _TRUST_CENTRE_
/**************************************************************************//**
  \brief Checks specific parameters of Transport Trust Key request.

  \param[in] req - pointer to parameters of APSME-TRANSPORT-KEY.request.
  \return Pointer to function for preparing and sending APS Transport Key command.
 ******************************************************************************/
APS_PRIVATE ApsTransportKeyCommand_t
apsCheckTransportTrustKeyReq(APS_TransportKeyReq_t *const req);
#endif /* _TRUST_CENTRE_ */

/**************************************************************************//**
  \brief Process an incoming trust link or master key.

  \param[in] commandInd - pointer to received command descriptor.

  \return 'false' if structure commandInd->nwkDataInd is used otherwise 'true'.
 ******************************************************************************/
APS_PRIVATE bool apsTransportTrustKeyInd(const ApsCommandInd_t *const commandInd);

#else
#define apsTransportTrustKeyInd(commandInd) (true)
#endif /* _SECURITY_ and _LINK_SECURITY_ */

#if !(defined _SECURITY_ && defined _LINK_SECURITY_ && defined _TRUST_CENTRE_)

#define apsCheckTransportTrustKeyReq(req) NULL
#endif
#endif /* _APS_TRANSPORT_TRUST_KEY_H */
/* eof apsTransportTrustKey.h */
