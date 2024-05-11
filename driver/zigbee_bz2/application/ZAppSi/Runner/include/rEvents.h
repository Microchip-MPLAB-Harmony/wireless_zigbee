/**************************************************************************//**
  \file  rEvents.h

  \brief Events commands

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
#ifndef _REVENTS_H
#define _REVENTS_H
/******************************************************************************
                   Prototypes section
 ******************************************************************************/
void rInitEvents(void);

/**************************************************************************//**
  \brief System events management request handler.

  \param[in] commandBuffer - data to process

  \return None.
******************************************************************************/
void rSysEventMgmtProcess(ZS_CommandBuffer_t *commandBuffer);

#endif /* _REVENTS_H */

/* eof rEvents.h*/
