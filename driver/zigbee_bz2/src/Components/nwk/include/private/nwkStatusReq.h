/*******************************************************************************
  NWK status Request Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkStatusReq.h

  Summary:
    This file contains the Interface of the network status sender.

  Description:
    This file contains the Interface of the network status sender.
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

#if !defined _NWK_STATUS_REQ_H
#define _NWK_STATUS_REQ_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <private/nwkConfig.h>
#include <sysQueue.h>
#include <nwkCommon.h>
#include <nldeData.h>
#include <private/nwkFrame.h>
#include <private/nwkRx.h>

/******************************************************************************
                              Definitions section
 ******************************************************************************/
/** Size of NWK status command payload:
 * - command id - 1 octet
 * - status code - 1 octet
 * - destination address - 2 octet */
#define NWK_STATUS_CMD_PAYLOAD_SIZE 4U
/** Constant parameters of network status transmission. */
#define NWK_UNICAST_STATUS_TX_PARAMETERS \
  {NWK_TX_DELAY_UNICAST_COMMAND, nwkPrepareNetworkStatusTx,\
  nwkConfirmNetworkStatusTx, true}
#define NWK_BROADCAST_STATUS_TX_PARAMETERS \
  {NWK_TX_DELAY_BROADCAST, nwkPrepareNetworkStatusTx, \
  nwkConfirmNetworkStatusTx, true}
#define NWK_MANY_TO_ONE_STATUS_TX_PARAMETERS \
  {NWK_TX_DELAY_UNICAST_COMMAND, nwkPrepareNetworkStatusTx, \
   nwkConfirmManyToOneNetworkStatusTx, false}
#define NWK_MANY_TO_ONE_TRANSIT_STATUS_TX_PARAMETERS \
  {NWK_TX_DELAY_UNICAST_COMMAND, nwkPrepareManayToOneNetworkStausTx,\
   nwkConfirmManyToOneNetworkStatusTx, false}

/******************************************************************************
                                Types section
 ******************************************************************************/
/** Confirmation parameters of NWK status command sending. */
typedef struct _NwkStatusConf_t
{
  /* Status of NWK status command sending.*/
  NWK_Status_t status;
} NwkStatusConf_t;

/** Type of NWK status request parameters. */
typedef struct _NwkStatusReq_t
{
  /** Service field - for internal needs. */
  struct
  {
    QueueElement_t qelem; /**< link used for queuing */
  } service;
  /** Callback for request to send of the NWK status command.*/
  void (* nwkStatusConf)(NwkStatusConf_t *conf);
  /** Target address for this network status command. */
  ShortAddr_t targetAddr;
  /** Destination address for this network status command. */
  ShortAddr_t dstAddr;
  /* Short address of next hop for this command. */
  ShortAddr_t nextHopAddr;
  /* Short address of previous hop of original packet. */
  ShortAddr_t prevHopAddr;
#if defined _GREENPOWER_SUPPORT_
  /* Alias usage by  for the current network status frame */
  bool useAlias;
  /* The source address to be used for this network staus cmd. If the UseAlias parameter 
     has a value of FALSE,  the AliasSrcAddr parameter is ignored.*/
  ShortAddr_t aliasSrcAddr;
  /* The sequence number to be used for this network staus cmd. If the UseAlias parameter
     has a value of FALSE, the AliasSeqNumb parameter is ignored.*/
  NwkSequenceNumber_t aliasSeqNumber;
#endif /*_GREENPOWER_SUPPORT_*/
  NwkStatusConf_t confirm;
  /** Value of status code field in network status frame. */
  NWK_StatusIndErrorCodes_t statusCode;
} NwkStatusReq_t;

/** Network status command frame format. ZigBee spec r17, figure 3.15. */
BEGIN_PACK
typedef struct PACK _NwkStatusCommandPayload_t
{
  /** Command frame identifier. */
  NwkCommandIdField_t commandId;
  /** Status code field. This field shall be set to one of the non-reserved
   * values shown in ZigBee spec r17, Table 3.42. */
  uint8_t statusCode;
  /** The destination address field is 2 octets in length and shall be present
   * if, and only if, the network status command frame is being sent in
   * response to a routing failure. In this case, it shall contain
   * the destination address from the data frame that encountered the failure.
   * ZigBee spec r17, 3.4.3.3.2, page 324. */
  ShortAddr_t dstAddr;
} NwkStatusCommandPayload_t;
END_PACK

/** Internal states of NWK status command sender. */
typedef enum _NwkStateOfStatusSender_t
{
  NWK_STATUS_SENDER_IDLE_STATE = 0x78,
  NWK_STATUS_SENDER_FIRST_STATE = 0x20,
  NWK_STATUS_SENDER_PREPARE_TX_STATE = NWK_STATUS_SENDER_FIRST_STATE,
  NWK_STATUS_SENDER_SEND_STATE = 0x21,
  NWK_STATUS_SENDER_LAST_STATE
} NwkStateOfStatusSender_t;

/** Internal variables of the NWK status command sender. */
typedef struct _NwkStatusSender_t
{
  /** Queue of requests to send NWK status command. */
  QueueDescriptor_t queue;
  /** The request to send the route error status command. */
  NwkStatusReq_t routeError;
  /** Current state of NWK status sender. */
  NwkStateOfStatusSender_t state;
  /** Route error command is sent. */
  bool routeErrorBusy;
} NwkStatusSender_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
#if defined _ROUTER_ || defined _COORDINATOR_
#if defined _RESOLVE_ADDR_CONFLICT_ || defined _NWK_MANY_TO_ONE_ROUTING_ ||\
  defined _NWK_SOURCE_ROUTING_ || defined _NWK_MESH_ROUTING_
/**************************************************************************//**
  \brief Request to send a network status command.

  \param[in] req - request information: statusCode, destination address and etc.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkStatusReq(NwkStatusReq_t *const req);
#endif

/**************************************************************************//**
  \brief Reset NWK status sender.
 ******************************************************************************/
NWK_PRIVATE void nwkResetStatusSender(void);

#if defined _NWK_SOURCE_ROUTING_ || defined _NWK_MESH_ROUTING_
/**************************************************************************//**
  \brief Send the status command with status code NWK_NO_ROUTE_AVAILABLE.

  \param[in] srcAddr - source address of route path.
  \param[in] dstAddr - destination address of route path.
  \param[in] statusCode - status code for network status command frame.
  \param[in] prevHopAddr - short address of previous hop of data frame

  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkSendRouteErrorStatus(const ShortAddr_t srcAddr,
  const ShortAddr_t dstAddr, const ShortAddr_t prevHopAddr,
  const NWK_StatusIndErrorCodes_t statusCode);
#endif /* _NWK_SOURCE_ROUTING_ or _NWK_MESH_ROUTING_*/

/**************************************************************************//**
  \brief Prepare header and payload of the network status command.

  \param[in] outPkt - pointer to output packet.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkPrepareNetworkStatusTx(NwkOutputPacket_t *const outPkt);

/**************************************************************************//**
  \brief Confirmation of network status command transmission.

  \param[in] outPkt - pointer to output packet.
  \param[in] status - network status of status command transmission.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkConfirmNetworkStatusTx(NwkOutputPacket_t *const outPkt,
  const NWK_Status_t status);

#if defined _NWK_MANY_TO_ONE_ROUTING_
/**************************************************************************//**
  \brief Send the many-to-one route error status command.

  \param[in] srcAddr - the source address of the data frame
  \param[in] concAddr - short address of concentrator
  \param[in] prevHopAddr - short address of previous hop of data frame
  \param[in] nextHopAddr - short address of failure next hop

  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkSendManyToOneRouteErrorStatus(const ShortAddr_t srcAddr,
  const ShortAddr_t concAddr, const ShortAddr_t prevHopAddr,
  const ShortAddr_t nextHopAddr);
#endif /* _NWK_MANY_TO_ONE_ROUTING_ */

#else /* _ROUTER_ or _COORDINATOR_ */

#define nwkResetStatusSender() (void)0
#define nwkPrepareNetworkStatusTx NULL
#define nwkConfirmNetworkStatusTx NULL

INLINE void nwkSendRouteErrorStatus(const ShortAddr_t srcAddr,
  const ShortAddr_t dstAddr, const bool multicast)
{
  (void)srcAddr, (void)dstAddr, (void)multicast;
}

#endif /* _ROUTER_ or _COORDINATOR_ */

#if defined NWK_ROUTING_CAPACITY && defined _NWK_MANY_TO_ONE_ROUTING_
/**************************************************************************//**
  \brief Preparation fuction of of sending NWK status command with many-to-one error in transit.

  \param[in] outPkt - pointer to output packet
  \param[in] status - status of sending

  \return None.
 ******************************************************************************/
NWK_PRIVATE
void nwkPrepareManayToOneNetworkStausTx(NwkOutputPacket_t *const outPkt);

/**************************************************************************//**
  \brief Confirmation of sending NWK status command with many-to-one error.

  \param[in] outPkt - pointer to output packet
  \param[in] status - status of sending

  \return None.
 ******************************************************************************/
NWK_PRIVATE
void nwkConfirmManyToOneNetworkStatusTx(NwkOutputPacket_t *const outPkt,
  const NWK_Status_t status);

#else
#define nwkPrepareManayToOneNetworkStausTx NULL
#define nwkConfirmManyToOneNetworkStatusTx NULL
#endif /* NWK_ROUTING_CAPACITY and _NWK_MANY_TO_ONE_ROUTING_ */
#endif /* _NWK_STATUS_REQ_H */
/** nwkStatusReq.h */

