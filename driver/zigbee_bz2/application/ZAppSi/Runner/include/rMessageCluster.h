/**************************************************************************//**
  \file  rMessageCluster.h

  \brief Message Cluster Interface

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    14/09/2009  Daniil Kasyanov - Created.
 ******************************************************************************/
#ifndef _RMESSAGECLUSTER_H
#define	_RMESSAGECLUSTER_H
/******************************************************************************
                   Includes section
 *****************************************************************************/
#include <zcl/include/zcl.h>
#include <zclMessagingCluster.h>
/******************************************************************************
                   Prototypes section
 ******************************************************************************/
/***************************************************************************//**
\brief Saves Display Message. The saved message returns in response to Get Last
Message Command.

\param[in] request - that contains message's payload.

\return
******************************************************************************/
void saveMessageCommand(ZCL_Request_t *request);
/***************************************************************************//**
\brief Gets Messaging Cluster Commands.

\param

\return Message Cluster Commands.
******************************************************************************/
MessagingClusterCommands_t *getMessagingCommands(void);
/***************************************************************************//**
\brief Cancels Message.

\param[in] request - that contains message's payload.

\return
******************************************************************************/
void cancelMessageCommand(ZCL_Request_t *request);

#endif	/* _RMESSAGECLUSTER_H */

/* eof rMessageCluster.h */
