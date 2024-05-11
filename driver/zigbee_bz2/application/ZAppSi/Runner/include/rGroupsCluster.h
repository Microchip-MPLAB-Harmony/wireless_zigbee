/**************************************************************************//**
  \file  rGroupsCluster.h

  \brief Groups Cluster Interface

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    20/08/2011  A. Razinkov - Created.
 ******************************************************************************/

#ifndef _RGROUPSCLUSTER_H
#define	_RGROUPSCLUSTER_H
/******************************************************************************
                   Includes section
 *****************************************************************************/
#include <zcl/include/zcl.h>
#include <zcl/include/zclGroupsCluster.h>
/******************************************************************************
                   Prototypes section
 ******************************************************************************/

/***************************************************************************//**
\brief Gets Groups Cluster commands.

\return Groups Cluster commands.
******************************************************************************/
ZCL_GroupsClusterCommands_t *getGroupsClusterCommands(void);

#endif	/* _RGROUPSCLUSTER_H */

/* eof  rGroupsCluster.h */
