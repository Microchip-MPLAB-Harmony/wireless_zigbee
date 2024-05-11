/**************************************************************************//**
  \file  rBACnetProtocolTunnelCluster.h

  \brief BACnet Protocol Tunnel Cluster Interface

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    21/10/2009  Daniil Kasyanov - Created.
 ******************************************************************************/
#ifndef _RBACNETTUNNELPROTOCOLCLUSTER_H
#define	_RBACNETTUNNELPROTOCOLCLUSTER_H
/******************************************************************************
                   Includes section
 *****************************************************************************/
#include <zcl/include/zcl.h>
#include <zcl/include/zclBACnetProtocolTunnelCluster.h>
/******************************************************************************
                   Prototypes section
 ******************************************************************************/
/***************************************************************************//**
 \brief Gets BACNet Protocol Tunnel Cluster commands.

 \param

 \return - BACNet Protocol Tunnel cluster commands.
******************************************************************************/
ZCL_BACnetProtocolTunnelCommands_t *getBACNetProtocolTunnelCommands(void);

#endif	/* _RBACNETTUNNELPROTOCOL_H */

/* eof rBACnetProtocolTunnelCluster.h */
