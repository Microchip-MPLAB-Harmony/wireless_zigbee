/**************************************************************************//**
  \file  rMem.c

  \brief Memory Management function implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:

 ******************************************************************************/
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <rTypes.h>
#include <rDebug.h>
/******************************************************************************
                   Static variables section
 ******************************************************************************/
static RAppMem_t rMem;
/******************************************************************************
                   Implementations section
 ******************************************************************************/
void *rGetMem(void)
{
  uint8_t i;
  void *result = NULL;

  for (i = 0; i < R_MAX_ACTIVE_TRANSACTIONS_AMOUNT; i++)
  {
    if (false == rMem.buffers[i].busy)
    {
      rMem.buffers[i].busy = true;
      result = &rMem.buffers[i].stackReq; //busy + sizeof(bool);
      break;
    }
  }

  rAssert(result != NULL, R_DBG_NO_STACK_REQUESTS_AVAILABLE);

  return result;
}

void rFreeMem(void *buffer)
{
  uint8_t i;

  if ((((uint8_t *) buffer) > ((uint8_t *) rMem.buffers)))
  {
    i = (uint8_t) ((((uint8_t *) buffer) - ((uint8_t *) rMem.buffers)) / sizeof (RMemEntry_t));
    if (R_MAX_ACTIVE_TRANSACTIONS_AMOUNT > i)
    {
      rMem.buffers[i].busy = false;
    }
  }
}

void rInitMem(void)
{
  memset(&rMem, 0, sizeof (RAppMem_t));
}

/* eof rMem.c */
