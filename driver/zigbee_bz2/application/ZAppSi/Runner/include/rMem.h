/**************************************************************************//**
  \file  rMem.h

  \brief Memory Manager

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
#ifndef _RMEM_H
#define	_RMEM_H
/******************************************************************************
                   Prototypes section
******************************************************************************/
void rInitMem(void);
void *rGetMem(void);
void rFreeMem(void *buffer);

#endif	/* _RMEM_H */

/* eof rMem.h */
