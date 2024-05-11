/**************************************************************************//**
  \file  rPriceCluster.h

  \brief Runner Price Cluster implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    14/09/2009  Andrey Kostyukov - Created.
 ******************************************************************************/
#ifndef _RPRICE_CLUSTER_H
#define _RPRICE_CLUSTER_H
/******************************************************************************
                        Includes section.
 ******************************************************************************/
#include <zcl/include/zclPriceCluster.h>
#include <rParser.h>
/******************************************************************************
                        Prototypes section.
 ******************************************************************************/
/**//**
 * \brief Function gives access to Price cluster commands descriptor.

This function is used to get access to Price cluster commands descriptor when
ZCL starts.
This function is not intended for use in other cases.

\param none
\return pointer to command descriptor
 */
ZCL_PriceClusterCommands_t* getPriceCommands(void);
/**//**
 * \brief Set autorespone payload from given command frame.

This function is called on capturing configuration command frame.
Input frame is checked if it is publish price commands is in payload. If
publish price has come then set auto response payload to input payload.

\param frame[in] - input command frame
\return none
 */
void setPriceAutoResponse(ZS_CommandFrame_t* frame);

#endif /* _RPRICE_CLUSTER_H */

/* eof rPriceCluster.h */
