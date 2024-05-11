/**************************************************************************//**
  \file  rParser.h

  \brief Defines Parser functions

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
#ifndef _RPARSER_H
#define _RPARSER_H
/******************************************************************************
                   Includes section
******************************************************************************/
#include <rTypes.h>
#include <zdo/include/zdo.h>
#include <ZAppSiCommands.h>
/******************************************************************************
                   External variables section
******************************************************************************/
extern uint16_t lastCommandId;
/******************************************************************************
                   Prototypes section
******************************************************************************/
void rParserTaskHandler(void);
void rCommandReceivedHandler(ZS_CommandBuffer_t *commandBuffer);

/***************************************************************************//**
\brief Assigned handler for incoming frames.
\param[in] commandBuffer - incoming buffer
\return none
******************************************************************************/
void incomingFrameHandler(ZS_CommandBuffer_t *commandBuffer);

#endif  /* _RPARSER_H */

/* eof rParser.h */
