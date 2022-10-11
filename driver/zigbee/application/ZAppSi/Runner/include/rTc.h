/**************************************************************************//**
  \file  rTc.h

  \brief Trust Center related functions

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
#ifndef _RTC_H
#define	_RTC_H
/******************************************************************************
                   Prototypes section
 ******************************************************************************/
#ifdef _SECURITY_
void rTcKeyUpdateRequestProcess(ZS_CommandBuffer_t *commandBuffer);
void rTcRemoveDeviceRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#endif /* _SECURITY_ */

#endif /* _RTC_H */

/* eof rTc.h */
