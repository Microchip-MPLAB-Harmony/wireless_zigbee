/**************************************************************************//**
  \file  rIdentifyCluster.h

  \brief Identify Cluster Interface

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    14/09/2009  Daniil Kasyanov - Created.
 ******************************************************************************/
#ifndef _RIDENTIFYCLUSTER_H
#define	_RIDENTIFYCLUSTER_H
/******************************************************************************
                   Includes section
 *****************************************************************************/
#include <zcl/include/zcl.h>
#include <zclIdentifyCluster.h>
/******************************************************************************
                   Prototypes section
 ******************************************************************************/
/***************************************************************************//**
\brief Timer callback function

\param

\return
******************************************************************************/
void identifyClusterTimerFired(void);
/***************************************************************************//**
 \brief Gets Identify Cluster Server Attributes.

 \param

 \return - Idetnfiy cluster attributes.
******************************************************************************/
ZCL_IdentifyClusterAttributes_t *getIdentifyClusterServerAttributes(void);
/***************************************************************************//**
\brief Gets Identify Cluster Server Commands.

\param

\return - Identify cluster commands.
******************************************************************************/
ZCL_IdentifyClusterCommands_t *getIdentifyClusterServerCommands(void);

#endif	/* _RIDENTIFYCLUSTER_H */

/* eof  rIdentifyCluster.h */
