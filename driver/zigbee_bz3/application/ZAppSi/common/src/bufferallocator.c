/*****************************************************************************
  \file bufferallocator.c

  \brief Memory manager implementation file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  History:
    19/08/09 A. Kostyukov - Created
*****************************************************************************/
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <bufferallocator.h>

/******************************************************************************
                   Static functions prototypes section
 ******************************************************************************/
static void *allocate(void);
static void free(void *ptr);
/*****************************************************************************
                              Global variables section
******************************************************************************/
BufferAllocator_t bufferAllocator =
{
  .slot_state = {SLOT_FREE},
  .free = free,
  .allocate = allocate,
  .counter = 0
};
/******************************************************************************

                           Implementations section

 ******************************************************************************/

/***************************************************************************//**
\brief Init allocators buffers
\param none
\return none
******************************************************************************/
void openBufferAllocator()
{
  int i = 0;
  for (i = 0; i < BA_MEMORY_SLOTS_MAX; i++)
  {
    bufferAllocator.slot_state[i] = SLOT_FREE;
  }
}

static void *allocate(void)
{
  int i = 0;
 // void *res = 0;

  for (i = 0; i < BA_MEMORY_SLOTS_MAX; ++i)
  {
    if (SLOT_FREE == bufferAllocator.slot_state[i])
    {
      bufferAllocator.slot_state[i] = SLOT_BUSY;
      bufferAllocator.counter++;
      return bufferAllocator.pool[i];
    }
  }
  return NULL;
}
static void free(void *ptr)
{
  int i = 0;

  for (i = 0; i < BA_MEMORY_SLOTS_MAX; ++i)
  {
    if ((ptr == bufferAllocator.pool[i]))
    {
      halAssert((bufferAllocator.slot_state[i] == SLOT_BUSY), DBG_BUFFER_ALLOCATOR_DBL_FREE);
      bufferAllocator.slot_state[i] = SLOT_FREE;
      bufferAllocator.counter--;
      //memset(ptr, 0, BA_MEMORY_SLOTS_MAX);
      break;
    }
  }
}
/* eof bufferallocator.c */
