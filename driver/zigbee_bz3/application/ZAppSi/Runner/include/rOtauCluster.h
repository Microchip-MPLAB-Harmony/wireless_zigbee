/**************************************************************************//**
  \file  rOtauCluster.h

  \brief Otau Cluster Interface

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal

 ******************************************************************************/
#ifndef _ROTAUCLUSTER_H
#define	_ROTAUCLUSTER_H
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <ZAppSiSerialManager.h>

/******************************************************************************
                   Prototypes section
 ******************************************************************************/
/***************************************************************************//**
\brief Starts otau discovery

\param[in] pointer to data buffer
*******************************************************************************/
void rOtauClientStart(ZS_CommandBuffer_t *commandBuffer);

/***************************************************************************//**
\brief Gets Otau's cluster

\param[out] returns Otau's server cluster
******************************************************************************/
ZCL_Cluster_t rGetOtauServerCluster(void);

#if APP_USE_OTAU == 1 && defined(_ZCL_SUPPORT_) 
/***************************************************************************//**
 \brief Gets Otau Cluster commands.

 \param

 \return - Otau cluster commands.
******************************************************************************/
ZCL_OtauClusterCommands_t *getOtauServerClusterCommands(void);

#endif
#endif	/* _ROTAUCLUSTER_H */

