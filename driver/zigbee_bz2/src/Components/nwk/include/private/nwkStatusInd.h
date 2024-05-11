/*******************************************************************************
  NWK Status Indication Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkStatusInd.h

  Summary:
    This file provides the interface to the NWK Status Indication Handling.

  Description:
    This file provides the interface to the NWK Status Indication Handling.
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

#if !defined _NWK_STATUS_IND_H
#define _NWK_STATUS_IND_H

/******************************************************************************
                             Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <nwkCommon.h>
#include <nlmeNwkStatus.h>
#include <private/nwkFrame.h>
#include <private/nwkRx.h>

/******************************************************************************
                          Inline functions section
 ******************************************************************************/
/**************************************************************************//**
  \brief Wrapper for NLME-NWK-STATUS indication primitive.

  \param[in] shortAddr - a network address of the device associated with
     the status information.
  \param[in] status - error code associated with the status indication.
  \return None.
 ******************************************************************************/
INLINE void nwkStatusIndicate(const ShortAddr_t shortAddr,
  const NWK_StatusIndErrorCodes_t status)
{
  NWK_NwkStatusInd_t ind;

  ind.shortAddress = shortAddr;
  ind.status = status;
  NWK_NwkStatusInd(&ind);
}

/******************************************************************************
                             Prototypes section
 ******************************************************************************/
#if defined(_ROUTER_) || defined(_COORDINATOR_)
/**************************************************************************//**
  \brief NWK status command has been received.

  \param[in] payload - pointer to status code field and destination address.
  \param[in] header - NWK header of the network status command.
  \param[in] parse - parsed NWK header.
  \return 'true' if continue processing of command packet otherwise 'false'.
 ******************************************************************************/
NWK_PRIVATE bool nwkStatusFrameInd(const uint8_t *const payload,
  const NwkFrameHeader_t *const header, const NwkParseHeader_t *const parse);

#else /* _ROUTER_ or _COORDINATOR_ */
#define nwkStatusFrameInd NULL
#endif /* _ROUTER_ or _COORDINATOR_ */

#if defined NWK_ROUTING_CAPACITY && defined _NWK_MANY_TO_ONE_ROUTING_
/**************************************************************************//**
  \brief Is it the input many-to-one network status.

  \param[in] inPkt - pointer to the input packet

  \return 'true' if the input packet is network status command with status code
           equal to many-to-one route error otherwise 'false'.
 ******************************************************************************/
NWK_PRIVATE
bool nwkIsManyToOneNetworkStatus(const NwkInputPacket_t *const inPkt);

#else
#define nwkIsManyToOneNetworkStatus(inPkt) false
#endif /* NWK_ROUTING_CAPACITY and _NWK_MANY_TO_ONE_ROUTING_ */
#endif /* _NWK_STATUS_IND_H */
/** eof nwkStatusInd.h */

