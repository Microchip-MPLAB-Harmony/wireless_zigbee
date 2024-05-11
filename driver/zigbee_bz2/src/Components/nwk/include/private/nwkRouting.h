/*******************************************************************************
  NWK Routing Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkRouting.h

  Summary:
    This file provides the Interface to the NWK Routing Mechanism.

  Description:
    This file provides the Interface to the NWK Routing Mechanism.
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

#if !defined _NWK_ROUTING_H
#define _NWK_ROUTING_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <appFramework.h>
#include <nldeData.h>

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Getting MAC short address of next hop by destination network address.

  \param[in] dstAddr - destination network address.
  \param[in] srcAddr - short address of node for that a next hop is searched.
  \param[in] prevHopAddr - address of previous hop.
  \param[in] isMulticast - 'true' if destination address is multicast group.
  \param[in] isMulticastMember - 'true' if destination address is multicast
                                 member address.
  \param[in] nextHop - pointer to short address of next hop node
                       or MAC_NO_SHORT_ADDR.
  \param[in] hops - number of hops that is equal to CS_MAX_NETWORK_DEPTH * 2.
                   It is not read in function to avoid unnecessary reading of
                   CS_MAX_NETWORK_DEPTH when not implementing routing of packet
                   from upper layer.

  \return Routing method used for searching the next hop node.
 ******************************************************************************/
NWK_PRIVATE NwkRouting_t nwkGetNextHop(const ShortAddr_t dstAddr,
  const ShortAddr_t srcAddr, const ShortAddr_t prevHopAddr,
  const bool isMulticast, const bool isMulticastMember,
  ShortAddr_t *const nextHop, NwkRadius_t hops);

/**************************************************************************//**
  \brief Process routing result.

     Update link state, the routing table and indicate to upper layer..

  \param[in] outPkt - pointer to output packet.
  \param[in] nwkStatus - status of transmission.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkRoutingIsCompleted(const NwkOutputPacket_t *const outPkt,
  const NWK_Status_t nwkStatus);

/**************************************************************************//**
  \brief Remove entries from the routing table and route cache with the address.

    Free entries with the next hop which is equal to the short address or an
  entry with destination that is equal to the passed address.
    Remove all route records from the route cache that include the short address.

  \param[in] shortAddr - the short address of device which is removed from
                         the routing table and the route cache.

  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkDeleteRoute(const ShortAddr_t shortAddr);

#endif /* _NWK_ROUTING_H */
/** eof nwkRouting.h */

