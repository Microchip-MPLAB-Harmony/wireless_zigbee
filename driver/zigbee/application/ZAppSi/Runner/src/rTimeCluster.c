/**************************************************************************//**
  \file  rTimeCluster.c

  \brief Time Cluster Implementation

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
#include <zcl/include/zclTimeCluster.h>
#include <zcl/include/clusters.h>
#include <rZcl.h>
/*******************************************************************************
                   Static Variables section
 ******************************************************************************/
static ZCL_TimeClusterServerAttributes_t timeAttributes =
  { ZCL_DEFINE_TIME_CLUSTER_SERVER_ATTRIBUTES() };
/*******************************************************************************
                          Implementations section
 ******************************************************************************/
/***************************************************************************//**
\breif Timer callback function.

\param

\return
******************************************************************************/
void timeClusterTimerFired(void)
{
  timeAttributes.time.value++;
}
/***************************************************************************//**
\brief Returns current time in seconds since 1st Jaunary 2000.

\param

\return Current time in seconds since 1st Jaunary 2000.
******************************************************************************/
ZCL_UTCTime_t timeClusterGetCurrentUtcTime(void)
{
  return timeAttributes.time.value;
}
/***************************************************************************//**
\brief Gets Time cluster attributes.

\param

\return Time Cluster attributes.
******************************************************************************/
ZCL_TimeClusterServerAttributes_t *getTimeAttributes(void)
{
  return &timeAttributes;
}

#endif /* (ZCL_SUPPORT == 1) && (APP_REDUCED_OTAU_SERVER == 0) */

/* eof rTimeCluster.c */
