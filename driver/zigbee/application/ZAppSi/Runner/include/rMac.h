/**************************************************************************//**
  \file  rMac.h

  \brief Mac Related commands handlers

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    29/03/2010 Max Gekk - Created.
 ******************************************************************************/
#ifndef _RMAC_H
#define _RMAC_H
/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <ZAppSiSerialManager.h>

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
void rMacBanRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rMacBanAllRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rMacDataRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rMacAccessRegisterRequestProcess(ZS_CommandBuffer_t *commandBuffer);

#endif /* _RMAC_H */
/* eof rMac.h */

