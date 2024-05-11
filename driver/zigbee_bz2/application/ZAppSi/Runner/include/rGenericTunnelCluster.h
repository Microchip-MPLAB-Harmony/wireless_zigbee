/**************************************************************************//**
  \file  rGenerictTunnelCluster.h

  \brief Generic Tunnel Cluster Interface

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    21/10/2009  Daniil Kasyanov - Created.
 ******************************************************************************/
#ifndef _RGENERICTUNNELCLUSTER_H
#define	_RGENERICTUNNELCLUSTER_H
/******************************************************************************
                   Includes section
 *****************************************************************************/
#include <zcl/include/zcl.h>
#include <zcl/include/zclGenericTunnelCluster.h>
/******************************************************************************
                   Prototypes section
 ******************************************************************************/
/***************************************************************************//**
 \brief Gets Generic Tunnel Cluster Server Attributes.

 \param

 \return - Generic Tunnel Cluster Server cluster attributes.
******************************************************************************/
ZCL_GenericTunnelClusterServerAttributes_t *getGenericTunnelClusterServerAttributes(void);
/***************************************************************************//**
 \brief Gets Generic Tunnel Cluster commands.

 \param

 \return - Generic Tunnel cluster commands.
******************************************************************************/
ZCL_GenericTunnelClusterCommands_t *getGenericTunnelClusterCommands(void);

#endif	/* _RGENERICTUNNELCLUSTER_H */

/* eof rGenerictTunnelCluster.h */
