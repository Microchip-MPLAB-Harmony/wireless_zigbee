/**************************************************************************//**
  \file  rHal.h

  \brief HAL related commands handlers

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    13/02/2012 N. Fomin - Created.
 ******************************************************************************/
#ifndef _RHAL_H
#define _RHAL_H
/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <ZAppSiSerialManager.h>

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
void rHalStartAppTimerProcess(ZS_CommandBuffer_t *commandBuffer);

#endif /* _RHAL_H */
/* eof rHal.h */

