/**************************************************************************//**
  \file  rGenericTunnelCluster.c

  \brief Generic Tunnel Cluster Implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    14/09/2009  Daniil Kasyanov - Created.
 ******************************************************************************/
#if defined(_ZCL_SUPPORT_) && (APP_REDUCED_OTAU_SERVER == 0)
/*******************************************************************************
                             Includes section
 ******************************************************************************/
#include <stdbool.h>
#include <zcl/include/zcl.h>
#include <zcl/include/zclGenericTunnelCluster.h>
#include <zcl/include/clusters.h>
#include <rZcl.h>
/*******************************************************************************
                             Prototypes section
 ******************************************************************************/
static ZCL_Status_t matchProtocolAddressCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_MatchProtocolAddress_t *payload);
static ZCL_Status_t matchProtocolAddressResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_MatchProtocolAddressResponse_t *paylaod);
static ZCL_Status_t advertiseProtocolAddressInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AdvertiseProtocolAddress_t *payload);
/*******************************************************************************
                           Static Variables section
 ******************************************************************************/
static ZCL_GenericTunnelClusterServerAttributes_t genericTunnelClusterServerAttributes =
{
  ZCL_DEFINE_GENERIC_TUNNEL_CLUSTER_SERVER_ATTRIBUTES()
};

static ZCL_GenericTunnelClusterCommands_t genericTunnelClusterCommands =
{
  ZCL_DEFINE_GENERIC_TUNNEL_CLUSTER_COMMANDS(matchProtocolAddressCommandInd, matchProtocolAddressResponseCommandInd, advertiseProtocolAddressInd)
};
/*******************************************************************************
                          Implementations section
 ******************************************************************************/
/*******************************************************************************
 Match protocol address command handler.
  Parameters:
    addr - Source address.
    payloadLength - Length of payload.
    payload - Command payload.
  Return:
    Status.
*******************************************************************************/
static ZCL_Status_t matchProtocolAddressCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_MatchProtocolAddress_t *payload)
{
  return commandInd(addressing, payloadLength, (uint8_t *) payload);
}
/*******************************************************************************
 Match protocol address response command handler.
  Parameters:
    addr - Source address.
    payloadLength - Length of payload.
    paylaod - Command payload.
  Return:
    Status.
*******************************************************************************/
static ZCL_Status_t matchProtocolAddressResponseCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_MatchProtocolAddressResponse_t *payload)
{
  return commandInd(addressing, payloadLength, (uint8_t *) payload);
}
/*******************************************************************************
 Advertise protocol address command handler.
  Parameters:
    addr - Source address.
    payloadLength - Length of payload.
    message - Command payload.
  Return:
    Status.
*******************************************************************************/
static ZCL_Status_t advertiseProtocolAddressInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AdvertiseProtocolAddress_t *payload)
{
  return commandInd(addressing, payloadLength, (uint8_t *) payload);
}
/***************************************************************************//**
 \brief Gets Generic Tunnel Cluster Server Attributes.

 \param

 \return - Generic Tunnel Cluster Server cluster attributes.
******************************************************************************/
ZCL_GenericTunnelClusterServerAttributes_t *getGenericTunnelClusterServerAttributes(void)
{
  return &genericTunnelClusterServerAttributes;
}
/***************************************************************************//**
 \brief Gets Generic Tunnel Cluster commands.

 \param

 \return - Generic Tunnel cluster commands.
******************************************************************************/
ZCL_GenericTunnelClusterCommands_t *getGenericTunnelClusterCommands(void)
{
  return &genericTunnelClusterCommands;
}
#endif /* (ZCL_SUPPORT == 1) && (APP_REDUCED_OTAU_SERVER == 0) */

/* eof rGenericTunnelCluster.c */
