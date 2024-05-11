/**************************************************************************//**
  \file  rAux.h

  \brief Auxiliary commands interface (commands that are not directly
    mapped to BitCloud API)

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    19.01.2010  A. Taradov - Created.
******************************************************************************/
#ifndef _RAUX_H
#define _RAUX_H

/******************************************************************************
                   Prototypes section
 ******************************************************************************/
#if defined(_SECURITY_) && defined _LINK_SECURITY_
void rAuxGetLinkKeyHashRequestProcess(ZS_CommandBuffer_t *commandBuffer);
#endif

#endif /* _RAUX_H */

// eof rAux.h
