/*****************************************************************************
  \file parser.h

  \brief Parser API file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  History:
    22/09/09 A. Kostyukov - Created
*****************************************************************************/

#ifndef PARSER_H_
#define PARSER_H_
#include <ZAppSiSerialManager.h>
#include <ZAppSiIdentifiers.h>
/***************************************************************************//**
 \brief Incoming frames parsing function
 The main parse function. Function parses the commandFrame parameter and
 invokes the corresponding function.

 \param[in] commandFrame - pointer to incoming frame
 \return nothing
 ******************************************************************************/
void parse(ZS_CommandBuffer_t *commandFrame);
/***************************************************************************//**
\brief Set parameters for incoming confirmation identification

This function allows to composer define what type of confirm parser should
wait.

\param[in] id - expected confirmation id
\param[in] cb - confirmation callback

\return nothing
******************************************************************************/
void setAwaitingReq(CommandID_t id, void *conf);

#endif /* PARSER_H_ */
