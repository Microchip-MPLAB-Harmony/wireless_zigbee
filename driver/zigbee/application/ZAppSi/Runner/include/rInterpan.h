/**************************************************************************//**
  \file  rInterpan.h

  \brief Inter-PAN releated command handlers

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
#ifndef _RINTERPAN_H
#define _RINTERPAN_H
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <ZAppSiSerialManager.h>
/******************************************************************************
                   Prototypes section
 ******************************************************************************/
#ifdef _INTERPAN_
void rIntrpDataReq(ZS_CommandBuffer_t *commandBuffer);
void rInitInterpan(void);
#endif /* _INTERPAN_ */

#endif /* _RINTERPAN_H */

/* eof rInterpan.h */
