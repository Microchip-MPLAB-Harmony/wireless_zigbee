/**************************************************************************//**
  \file  reccAux.c

  \brief Certicom auxilary functions implementations commands Implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
#if CERTICOM_SUPPORT == 1
/*****************************************************************************
                              Includes section
******************************************************************************/
#include "genericEcc.h"
/*****************************************************************************
                              Definitions section
******************************************************************************/
#define YIELD_LEVEL 0
/*****************************************************************************
                              Global variables section
******************************************************************************/
/******************************************************************************
                              Implementations section
 ******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
//
//      yield()
//      This should be replaced for user defined processing.
//      A yield level of 0 will not yield.
//      A yield level of 1 will yield the most.
//      A yield level of 10 will yield the least.
///////////////////////////////////////////////////////////////////////////////
int yield(void)
{
  return MCE_SUCCESS;
}

#endif /* CERTICOM_SUPPORT == 1 */


/* eof eccAux.c */
