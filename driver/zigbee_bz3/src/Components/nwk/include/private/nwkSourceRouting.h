/*******************************************************************************
  NWK Source Routing Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkSourceRouting.h

  Summary:
    This file contains the Interface of source routing functionality.

  Description:
    This file contains the Interface of source routing functionality.
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

/**//**
 *  Source routing allows a sender of a packet to completely specify
 * the route the packet takes through the network.
 **/
#if !defined _NWK_SOURCE_ROUTING_H
#define _NWK_SOURCE_ROUTING_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <nwkCommon.h>
#include <nldeData.h>
#include <private/nwkDataReq.h>
#include <private/nwkFrame.h>

/******************************************************************************
                               Define(s) section
 ******************************************************************************/
#define NWK_SOURCE_ROUTE_TX_PARAMETERS \
  {NWK_TX_DELAY_UNICAST_DATA, nwkPrepareSourceRouteTx, nwkConfirmDataTx, false}
#define NWK_SOURCE_ROUTE_TRANSIT_TX_PARAMETERS \
  {NWK_TX_DELAY_UNICAST_DATA, nwkPrepareTransitSourceRouteTx, \
   nwkConfirmTransitSoureRouteTx, true}

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
#if defined NWK_ROUTING_CAPACITY \
  && defined _NWK_SOURCE_ROUTING_ && defined _NWK_CONCENTRATOR_
/**************************************************************************//**
  \brief Try to use the source routing, and write the source route subframe.

    Initialize of transmission identifier if source route is used.

  \param[in] req - pointer to NLDE-Data request's parameters.
  \param[in] nwkHeaderLength - pointer to current maximum length of NWK header.

  \return 'true' if the source route subframe is present otherwise 'false'.
 ******************************************************************************/
NWK_PRIVATE bool nwkUseSourceRouting(NWK_DataReq_t *const req,
  NwkLength_t *const nwkHeaderLength);

/**************************************************************************//**
  \brief Prepare an initial source route packet.

  \param[in] outPkt - pointer to output packet.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkPrepareSourceRouteTx(NwkOutputPacket_t *const outPkt);

#else /* NWK_ROUTING_CAPACITY and _NWK_SOURCE_ROUTING_ and _NWK_CONCENTRATOR_ */

#define nwkUseSourceRouting(req, nwkHeaderLength) false
#define nwkPrepareSourceRouteTx NULL

#endif /* NWK_ROUTING_CAPACITY and _NWK_SOURCE_ROUTING_ and _NWK_CONCENTRATOR_ */

#if defined NWK_ROUTING_CAPACITY && defined _NWK_SOURCE_ROUTING_
/**************************************************************************//**
  \brief Decrement the relay index sub-field by 1, and relay the frame to
    the address immediately prior to its own address in the relay list.

  \param[in] outPkt - pointer to output packet.
  \return None.
 ******************************************************************************/
NWK_PRIVATE
void nwkPrepareTransitSourceRouteTx(NwkOutputPacket_t *const outPkt);

/**************************************************************************//**
  \brief Confirmation of source route packet transmission.

    If status isn't NWK_SUCCESS_STATUS then send back NWK status command with
    code 0x0B (NWK_SOURCE_ROUTE_FAILURE).

  \param[in] outPkt - pointer to output packet.
  \param[in] status - NWK status of source route packet transmission.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkConfirmTransitSoureRouteTx(NwkOutputPacket_t *const outPkt,
  const NWK_Status_t status);

/**************************************************************************//**
  \brief A data packet has been received for this node.

   Update the source route information about a concentrator.

  \param[in] nwkHeader - pointer to the raw NWK header of a source route packet.
  \return None.
 ******************************************************************************/
/* As continuation to the CCB 1487,
     if is a source routed frame, it is better not to update routeRequired field as false
     so that route record will be sent even for a reply to a (first)source routed packet 
    (after mto rreq), So there could be a probability of getting a better and optimal route
NWK_PRIVATE void nwkUpdateSourceRouteInfo(const NwkFrameHeader_t *const nwkHeader); */

#else /* NWK_ROUTING_CAPACITY and _NWK_SOURCE_ROUTING_ */
#define nwkPrepareTransitSourceRouteTx NULL
#define nwkConfirmTransitSoureRouteTx NULL
//#define nwkUpdateSourceRouteInfo(nwkHeader) (void)0
#endif /* NWK_ROUTING_CAPACITY and _NWK_SOURCE_ROUTING_ */

#endif /* _NWK_SOURCE_ROUTING_H */
/** eof nwkSourceRouting.h */

