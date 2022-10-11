/**************************************************************************//**
  \file  rTimeCluster.h

  \brief Time Cluster Interface

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    14/09/2009  Daniil Kasyanov - Created.
 ******************************************************************************/
#ifndef _RTIMECLUSTER_H
#define	_RTIMECLUSTER_H
/******************************************************************************
                   Includes section
 *****************************************************************************/
#include <zcl/include/zcl.h>
#include <zcl/include/zclTimeCluster.h>
/******************************************************************************
                   Prototypes section
 ******************************************************************************/
/***************************************************************************//**
\breif Timer callback function.

\param

\return
******************************************************************************/
void timeClusterTimerFired(void);
/***************************************************************************//**
\brief Returns current time in seconds since 1st Jaunary 2000.

\param

\return Current time in seconds since 1st Jaunary 2000.
******************************************************************************/
ZCL_UTCTime_t timeClusterGetCurrentUtcTime(void);
/***************************************************************************//**
\brief Gets Time cluster attributes.

\param

\return Time Cluster attributes.
******************************************************************************/
ZCL_TimeClusterServerAttributes_t *getTimeAttributes(void);

#endif	/* _RTIMECLUSTER_H */

/* eof  rTimeCluster.h */
