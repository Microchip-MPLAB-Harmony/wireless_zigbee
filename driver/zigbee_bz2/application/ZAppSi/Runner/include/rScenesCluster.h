/**************************************************************************//**
  \file  rScenesCluster.h

  \brief Scenes Cluster interface

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    20/08/2011  A. Razinkov - Created.
 ******************************************************************************/

#ifndef _RSCENESCLUSTER_H
#define	_RSCENESCLUSTER_H
/******************************************************************************
                   Includes section
 *****************************************************************************/
#include <zcl/include/zcl.h>
#include <zcl/include/zclScenesCluster.h>
/******************************************************************************
                   Prototypes section
 ******************************************************************************/

/***************************************************************************//**
\brief Gets Scenes Cluster commands.

\return Scenes Cluster commands.
******************************************************************************/
ZCL_ScenesClusterCommands_t *getScenesClusterCommands(void);

#endif	/* _RSCENESCLUSTER_H */

/* eof  rScenesCluster.h */
