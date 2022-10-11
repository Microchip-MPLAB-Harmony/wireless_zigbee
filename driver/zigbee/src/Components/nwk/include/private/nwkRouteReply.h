/*******************************************************************************
  NWK Route Reply Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkRouteReply.h

  Summary:
    This file contains the Route reply command types and functions.

  Description:
    This file contains the Route reply command types and functions.
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

#if !defined _NWK_ROUTE_REPLY_H
#define _NWK_ROUTE_REPLY_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <private/nwkSystem.h>
#include <appFramework.h>
#include <nwkCommon.h>
#include <nldeData.h>
#include <private/nwkFrame.h>
#include <private/nwkRouteDiscoveryTable.h>

/******************************************************************************
                               Define(s) section
 ******************************************************************************/
#define NWK_ROUTE_REPLY_TX_PARAMETERS \
  {NWK_TX_DELAY_UNICAST_COMMAND, NULL, NULL, true}
/* Maximum amount of extended addresses in the route reply payload. */
#define NWK_MAX_RREPLY_EXT_ADDR_AMOUNT 2U

/******************************************************************************
                                Types section
 ******************************************************************************/
/** The options field of route reply command. ZigBee spec. r17, Figure 3.14. */
BEGIN_PACK
typedef struct PACK _NwkRouteReplyOptions_t
{
  LITTLE_ENDIAN_OCTET(5, (
    NwkBitField_t reserved1           : 4,
    /** If this field has value of 1 then the IEEE address of originator is
     * included in the payload of the route reply command. */
    NwkBitField_t extAddrOfOriginator : 1,
    /** If this field has value of 1 then the IEEE address of responder is
     * included in the payload of the route reply command. */
    NwkBitField_t extAddrOfResponder  : 1,
    /** This field shall have a value of 1 if and only if the command frame is
     * a reply to a request for a route to a multicast group. */
    NwkBitField_t multicast           : 1,
    NwkBitField_t reserved2           : 1
  ))
} NwkRouteReplyOptions_t;

/** The NWK payload of the route reply command. */
typedef struct PACK _NwkRouteReplyPayload_t
{
  /** The identifier of the route reply command. */
  NwkCommandIdField_t commandId;
  /** The format of the 8-bit command options field is shown in
   * ZigBee spec r17, Figure 3.14, page 319. */
  NwkRouteReplyOptions_t options;
  /** The route request identifier is the number of the route request to which
   * this frame is a reply. ZigBee spec r17, 3.4.2.3.2. */
  uint8_t routeRequestId;
  /** The network address of the originator of the route request command frame
   * to which this frame is a reply. ZigBee spec r17, 3.4.2.3.3, page 320. */
  ShortAddr_t shortAddrOfOriginator;
  /** The responder address field shall always be the same as the value
   * in the destination address field of the corresponding route request
   * command frame.*/
  ShortAddr_t shortAddrOfResponder;
  /** The path cost field is used to sum link cost as the route reply
   * command frame transits the network. */
  NwkPathCost_t pathCost;
  /** The first element contain the 64-bit address of the originator of
   * the route request command frame to which this frame is a reply.
   * The second element contain the 64-bit address of the destination of
   * the route request command frame to which this frame is a reply.*/
  ExtAddr_t extAddr[NWK_MAX_RREPLY_EXT_ADDR_AMOUNT];
} NwkRouteReplyPayload_t;
END_PACK

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
#if defined NWK_ROUTING_CAPACITY && defined _NWK_MESH_ROUTING_
/******************************************************************************
  \brief Action when command received.

  \param[in] payload - pointer to payload of route reply command.
  \param[in] header  - pointer to raw network header of route reply command.
  \param[in] parse   - parsed header fields.
  \return 'true' if continue processing of command packet otherwise 'false'.
******************************************************************************/
NWK_PRIVATE bool nwkRouteReplyFrameInd(const uint8_t *const payload,
  const NwkFrameHeader_t *const header, const NwkParseHeader_t *const parse);

/**************************************************************************//**
  \brief Prepare header and payload of the route reply command.

  \param[in] outPkt - pointer to output packet.
  \param[in] entry - pointer to a route discovery entry.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkPrepareRouteReplyTx(NwkOutputPacket_t *const outPkt,
  NwkRouteDiscoveryEntry_t *const entry);

#else /* NWK_ROUTING_CAPACITY */

#define nwkRouteReplyFrameInd NULL

#endif /* NWK_ROUTING_CAPACITY */
#endif /* _NWK_ROUTE_REPLY_H */
/** eof nwkRouteReply.h */

