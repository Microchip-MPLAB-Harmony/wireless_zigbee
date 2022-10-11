/**************************************************************************//**
  \file  rBACnetProtocolTunnelCluster.c

  \brief BACnet Protocol Tunnel Cluster Implementation

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
#include <zcl/include/zclBACnetProtocolTunnelCluster.h>
#include <zcl/include/clusters.h>
#include <rZcl.h>
/*******************************************************************************
                          Prototypes section
 ******************************************************************************/
static ZCL_Status_t transferNPDUCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_TransferNPDU_t *payload);
/*******************************************************************************
                        Static Variables section
 ******************************************************************************/
static ZCL_BACnetProtocolTunnelCommands_t bacNetProtocolTunnelCommands =
{
  ZCL_DEFINE_BACNET_PROTOCOL_CLUSTER_TUNNEL_CLUSTER_COMMANDS(transferNPDUCommandInd)
};
/*******************************************************************************
                          Implementations section
 ******************************************************************************/
/*******************************************************************************
 Transfer NPDU command handler.
  Parameters:
    addr - Source address.
    payloadLength - Length of payload.
    payload - Command payload.
  Return:
    Status.
*******************************************************************************/
static ZCL_Status_t transferNPDUCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_TransferNPDU_t *payload)
{
  return commandInd(addressing, payloadLength, (uint8_t *) payload);
}
/***************************************************************************//**
 \brief Gets BACNet Protocol Tunnel Cluster commands.

 \param

 \return - BACNet Protocol Tunnel cluster commands.
******************************************************************************/
ZCL_BACnetProtocolTunnelCommands_t *getBACNetProtocolTunnelCommands(void)
{
  return &bacNetProtocolTunnelCommands;
}

#endif /* ZCL_SUPPORT == 1 && (APP_REDUCED_OTAU_SERVER == 0) */

/* eof rBACnetProtocolTunnelCluster.c */
