/*******************************************************************************
  NWK Route Request Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkRouteRequest.h

  Summary:
    This file contains the Interface of NWK route request commands.

  Description:
    This file contains the Interface of NWK route request commands.
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

#if !defined _NWK_ROUTE_REQUEST_H
#define _NWK_ROUTE_REQUEST_H

/******************************************************************************
                              Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <private/nwkSystem.h>
#include <appFramework.h>
#include <nldeData.h>
#include <private/nwkFrame.h>
#include <private/nwkRouteDiscoveryTable.h>

/******************************************************************************
                              Define(s) section
 ******************************************************************************/
/** Transmission parameters of route request command. */
#define NWK_INITIAL_ROUTE_REQ_TX_PARAMETERS \
  {NWK_TX_DELAY_INITIAL_ROUTE_REQUEST, NULL, nwkConfirmRouteRequestTx, true}
#define NWK_ROUTE_REQ_TX_PARAMETERS \
  {NWK_TX_DELAY_ROUTE_REQUEST, NULL, NULL, true}
#define NWK_INITIAL_MANYTOONE_ROUTE_REQ_TX_PARAMETERS \
  {NWK_TX_DELAY_INITIAL_MANYTOONE_ROUTE_REQUEST, NULL, nwkConfirmRouteRequestTx, true}
#define NWK_MANYTOONE_ROUTE_REQ_TX_PARAMETERS \
  {NWK_TX_DELAY_MANYTOONE_ROUTE_REQUEST, NULL, NULL, true}

/******************************************************************************
                                Types section
 ******************************************************************************/
/** Many-to-One field values. See ZigBee spec r18, 3.4.1.3.1.1, page 320. */
typedef enum _NwkRReqManyToOneFlag_t
{
  /** The route request is not a many-to-one route request. */
  NWK_RREQ_IS_NOT_MANY_TO_ONE = 0,
  /** The route request is a many-to-one route request and the sender supports
   * a route record table.*/
  NWK_RREQ_IS_MANY_TO_ONE = 1,
  /** The route request is a many-to-one route request and the sender does not
   * support a route record table. */
  NWK_RREQ_IS_MANY_TO_ONE_NO_RREC_TABLE = 2,
  NWK_RREQ_RESERVED_MANY_TO_ONE_FLAG = 3
} NwkRReqManyToOneFlag_t;

BEGIN_PACK
/** Route request command options field. ZigBee spec r18, 3.4.1.3.1, page 320.
 **/
typedef struct PACK _NwkRouteRequestOptions_t
{
  LITTLE_ENDIAN_OCTET(5, (
    NwkBitField_t reserved1 : 3,
    /** The many-to-one field shall have one of the non-reserved values shown
     * in ZigBee spec r18, Table 3.41 and type NwkRReqManyToOneFlag_t. */
    NwkBitField_t manyToOne : 2,
    /** The destination IEEE address field is a single-bit field. It shall have
     * a value of 1 if, and only if, the command frame contains the destination
     * IEEE address. ZigBee spec r18, 3.4.1.3.1.2, page 321. */
    NwkBitField_t dstExt    : 1,
    /** The multicast sub-field is a single-bit field. It shall have a value
     * of 1 if, and only if, the command frame is a request for a route
     * to a multicast group... ZigBee spec r18, 3.4.1.3.1.3, page 321. */
    NwkBitField_t multicast : 1,
    NwkBitField_t reserved2 : 1
  ))
} NwkRouteRequestOptions_t;
END_PACK

BEGIN_PACK
/** Route request command frame format. See ZigBee spec r18,
 * Figure 3.11, page 319. */
typedef struct PACK _NwkRouteRequestPayload_t
{
  /** The identifier of the route request command. */
  uint8_t commandId;
  /** Route request command options field. See NwkRouteRequestOptions_t. */
  NwkRouteRequestOptions_t options;
  /** The route request identifier is an 8-bit sequence number for route
   * requests and is incremented by 1 every time the NWK layer on a particular
   * device issues a route request. ZigBee spec r18, 3.4.1.3.2, page 321. */
  NwkRouteRequestId_t identifier;
  /** The destination address shall be 2 octets in length and represents
   * the intended destination of the route request command frame.
   * ZigBee spec r18, 3.4.1.3.3. */
  ShortAddr_t dstAddr;
  /** The path cost field is eight bits in length and is used to accumulate
   * routing cost information as a route request command frame moves through
   * the network. ZigBee spec r18, 3.4.1.3.4, page 321; sub-clause 3.6.3.5.2. */
  NwkPathCost_t pathCost;
  /** The destination IEEE address shall be 8 octets in length and represents
   * the IEEE address of the destination of the route request command frame.
   ** ZigBee spec r18, 3.4.1.3.5, page 321. */
  ExtAddr_t dstExtAddr;
} NwkRouteRequestPayload_t;
END_PACK

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
#if defined NWK_ROUTING_CAPACITY \
  && (defined _NWK_MESH_ROUTING_ || defined _NWK_MANY_TO_ONE_ROUTING_)
/**************************************************************************//**
  \brief Action when route request command received.

  \param[in] payload - pointer to payload of route request command.
  \param[in] header - pointer to raw network header of route request command.
  \param[in] parse - parsed header fields.

  \return 'true' if continue processing of command packet otherwise 'false'.
 ******************************************************************************/
NWK_PRIVATE bool nwkRouteRequestFrameInd(const uint8_t *const payload,
  const NwkFrameHeader_t *const header, const NwkParseHeader_t *const parse);

/**************************************************************************//**
  \brief Prepare header and payload of the route request command.

  \param[in] outPkt - pointer to output packet.
  \param[in] entry - pointer to a route discovery entry.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkPrepareRouteRequestTx(NwkOutputPacket_t *const outPkt,
  NwkRouteDiscoveryEntry_t *const entry);

#else /* NWK_ROUTING_CAPACITY and (_NWK_MESH_ROUTING_ or _NWK_MANY_TO_ONE_ROUTING_) */

#define nwkRouteRequestFrameInd NULL

#endif /* NWK_ROUTING_CAPACITY and (_NWK_MESH_ROUTING_ or _NWK_MANY_TO_ONE_ROUTING_) */
#endif /* _NWK_ROUTE_REQUEST_H */
/** eof nwkRouteRequest.h */

