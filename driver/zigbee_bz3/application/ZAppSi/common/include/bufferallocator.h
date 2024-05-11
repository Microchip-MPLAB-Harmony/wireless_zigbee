/*****************************************************************************
  \file bufferallocator.h

  \brief Memory manager A file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  History:
    19/08/09 A. Kostyukov - Created
*****************************************************************************/
#ifndef _BUFFERALLOCATOR_H
#define _BUFFERALLOCATOR_H
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <consts.h>
#include <ZAppSiSerialManager.h>
/******************************************************************************
                             Definitions section
 ******************************************************************************/

#ifndef BA_MEMORY_SLOTS_MAX
#define BA_MEMORY_SLOTS_MAX 5
#endif

#ifndef BA_MEMORY_SLOT_SIZE
#define BA_MEMORY_SLOT_SIZE 100
#endif

#define DBG_BUFFER_ALLOCATOR_DBL_FREE   0x0101U
#define DBG_BUFFER_ALLOCATOR_BAD_PTR    0x0102U
// memory slot size should be dependant on APS_MAX_PAYLOAD size
// and if fragmentation is enabled or disabled.
/******************************************************************************
                   Types section
 ******************************************************************************/

typedef enum
{
    SLOT_FREE,
    SLOT_BUSY
} SlotState_t;

typedef struct
{
    unsigned char pool[BA_MEMORY_SLOTS_MAX][sizeof(ZS_CommandBuffer_t)];
    unsigned int slot_state[BA_MEMORY_SLOTS_MAX];
    unsigned int counter;
    void *(*allocate)();
    void (*free)(void *ptr);
} BufferAllocator_t;

/******************************************************************************
                   Prototypes section
 ******************************************************************************/
extern BufferAllocator_t bufferAllocator;

/***************************************************************************//**
\brief Static callback for adapter assert
\param condition[in] - condition for assert
\param code[in] - assert code
\return none
******************************************************************************/
void adapterAssert(bool condition, uint16_t code);

/***************************************************************************//**
\brief Init allocators buffers
\param none
\return none
******************************************************************************/
void openBufferAllocator();

#endif
