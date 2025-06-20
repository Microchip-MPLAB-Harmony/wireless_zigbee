/*******************************************************************************
 pdsDataServer Header File

  Company:
    Microchip Technology Inc.

  File Name:
    pds.h

  Summary:
    This file contains PDS Data Server functionalities.

  Description:
    This file contains PDS Data Server functionalities.

 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END


#ifndef _PERSISTDATASERVER_H
#define _PERSISTDATASERVER_H

/******************************************************************************
                              Description section
******************************************************************************/
/*
   - PERSISTENT DATA SERVER (PDS)
   User can specify parameters he(she) wants to backup in a non-volatile memory
   and restore in case of power failure. This service is provided by Persistent
   Data Server (PDS) module.
   The BitCloud (TM) stack also uses the same service for its internal structures.

   - FILE and FILE DESCRIPTOR
   Each item which user wants to backup in a non-volatile memory and restore in
   case of power failure is treated as a FILE - actual item value with associated
   service information, FILE DESCRIPTOR. Each file could be accessed by it's ID -
   a unique 16-bit value associated with a file. File descriptor keeps information
   about item's size and it's displacement in RAM and inside the NV storage.

   All file descriptors should be placed in a special segment inside the
   MCU Flash memory - [PDS_FF].
   The PDS_FILE_DESCR() macro is used to initialize descriptor and
   PDS_DECLARE_FILE() macro is used to place descriptor to required segment.

   - DIRECTORY and DIRECTORY DESCRIPTOR
   PDS is able to operate with separate files or with file lists - DIRECTORIES.
   Directory nesting is allowed. Each directory should be provided with
   DIRECTORY DESCRIPTOR which keeps information about associated items.
   Directories could be accessed by 16-bit ID, different from already associated
   with files.

   All directory descriptors should be placed in a special segment inside the
   MCU Flash memory - [PDS_FD].
   The PDS_DECLARE_DIR() macro is used to place a directory to required segment.
*/

/******************************************************************************
                              Includes section
******************************************************************************/
#include <stdbool.h>
/******************************************************************************
                              Defines section
******************************************************************************/

/*
  The following offsets CAN be used(OR'ed) to define the range and also to differentiate 
  the module specific IDs, so the same item ID will not be used across the stacks/modules.

  The IDs ranges are required to maintain the backward compatibility during an SW upgrade 
  with newly added item(s) in any module.

  Note: These offset were not used anywhere inside PDS implementation(Library). 
  This is purely to enable the application to use specific IDs across modules.

*/
#define PDS_MODULE_APP_OFFSET      (1 << 12)
#define PDS_MODULE_BT_OFFSET       (1 << 13)
#define PDS_MODULE_ZB_OFFSET       (1 << 14)
#define PDS_MODULE_RES_OFFSET      (1 << 15)

/* 
  Use this Directory mask on declaring directory item id's along with module specific offsets
  PDS_DECLARE_DIR
*/
#define  PDS_DIRECTORY_ID_MASK      0x0C00U // (Bit 11 and Bit 10)

/*! Type of PDS file or directory unique identifier. */
typedef uint16_t PDS_MemId_t;

/* Memory identifier record pointer */
typedef const PDS_MemId_t *PDS_MemIdRec_t;

typedef struct
{
  PDS_MemId_t       itemId;
  uint16_t          itemSize;
  void              *itemData;
  void              (*filler)(void);
  uint8_t           flags;
} ItemIdToMemoryMapping_t;

typedef struct
{
  PDS_MemIdRec_t list;
  uint16_t    filesCount;
  PDS_MemId_t memoryId;
} PDS_DirDescr_t;

typedef struct
{
  PDS_MemId_t id;
  void *data;
  uint16_t size;
  uint16_t oldSize;

}PDS_UpdateMemory_t;

typedef struct 
{
  PDS_MemId_t id;
  uint16_t    offset;
  uint16_t    size;
  uint8_t     *ramAddr;
}PDS_Operation_Offset_t;

/* Directory descriptor record pointer */
typedef const PDS_DirDescr_t *PDS_DirDescrRec_t;
typedef enum
{
  PDS_SUCCESS,            //!< Command completed successfully
} PDS_DataServerState_t;


#define NO_ITEM_FLAGS               0x00U
#define SIZE_MODIFICATION_ALLOWED   0x01U
#define ITEM_UNDER_SECURITY_CONTROL 0x02U

#define NO_FILE_MARKS 0U

#ifdef __GNUC__
extern uint32_t __pds_ff_start;
extern uint32_t __pds_ff_end;
extern uint32_t __pds_fd_start;
extern uint32_t __pds_fd_end;
#endif /* __GNUC__ */


#ifdef __IAR_SYSTEMS_ICC__
  /* Declaration to place object to PDS_FF (files) segment in MCU Flash */
  #define PDS_FF_OBJECT(object) \
    _Pragma("location=\"PDS_FF\"") __root PROGMEM_DECLARE (object)
  /* Declaration to place object to PDS_FD (directories) segment in MCU Flash */
  #define PDS_DECLARE_DIR(object) \
    _Pragma("location=\"PDS_FD\"") __root PROGMEM_DECLARE (object)
#elif __GNUC__
  #define PDS_FF_OBJECT(object) \
    __attribute__((__section__(".pds_ff"))) const object
  #define PDS_DECLARE_DIR(object) \
    __attribute__((__section__(".pds_fd"))) const object
#else
  #error "Unsupported compiler"
#endif

/*Linker file sections*/
#ifdef  __IAR_SYSTEMS_ICC__
#pragma segment="PDS_FF"
  #define PDS_FF_START       (ItemIdToMemoryMapping_t *) __sfb("PDS_FF")
  #define PDS_FF_END         (ItemIdToMemoryMapping_t *) __sfe("PDS_FF")
  #define PDS_FF_SIZE         __sfs("PDS_FF")
#pragma segment="PDS_FD"
  #define PDS_FD_START       (PDS_DirDescr_t *) __sfb("PDS_FD")
  #define PDS_FD_END         (PDS_DirDescr_t *) __sfe("PDS_FD")
  #define PDS_FD_SIZE        __sfs("PDS_FD")
#elif __GNUC__
  #define PDS_FF_START       (ItemIdToMemoryMapping_t *) &__pds_ff_start
  #define PDS_FF_END         (ItemIdToMemoryMapping_t *) &__pds_ff_end
  #define PDS_FF_SIZE        (&__pds_ff_end - &__pds_ff_start)
  #define PDS_FD_START       (PDS_DirDescrRec_t) &__pds_fd_start
  #define PDS_FD_END         (PDS_DirDescrRec_t) &__pds_fd_end
  #define PDS_FD_SIZE        (&__pds_fd_end - &__pds_fd_start)
#else
  #error "Unsupported compiler"
#endif

#define ITEM_ID_TO_MEM_MAPPING(item, size, pointer, func, flag) \
  {.itemId = item, .itemSize = size, .itemData = pointer, .filler = func, .flags = flag}

/* To declare an PDS item in the application/stacks */
#define PDS_DECLARE_ITEM(item, size, pointer, func, flag) \
  PDS_FF_OBJECT(ItemIdToMemoryMapping_t pds_ff_##item) = \
    ITEM_ID_TO_MEM_MAPPING(item, size, pointer, func, flag);

#ifndef FILE_TO_ITEM_MAPPING
  #define FILE_TO_ITEM_MAPPING
#endif

#ifdef FILE_TO_ITEM_MAPPING
#define PDS_DECLARE_FILE(id, dataSize, ramAddr, fileMarks) \
        PDS_DECLARE_ITEM(id, dataSize, ramAddr, NULL, 0x00)
#else
#define PDS_DECLARE_FILE(id, dataSize, ramAddr, fileMarks)
#endif

//! \cond internal
/**************************************************************************//**
\brief Persistent Data Server initialization routine.
\param[in] - maxItems -
                 Total number of individual PDS items used in the entire system
\param[in] - maxDirectories -
                 Total number of PDS directories used in the entire system

******************************************************************************/
void PDS_Init(PDS_MemId_t maxItems, PDS_MemId_t maxDirectories);

//! \endcond

/******************************************************************************
\brief PDS item initialization routine
Initializes an item with default data if it doesn't exist yet, 
or reads it when it does exist.

******************************************************************************/
void PDS_InitItems(uint16_t memIdStart, uint16_t memIdEnd);


/**************************************************************************//**
\brief Restores data from non-volatile storage.

\ingroup PDS

PDS files not included in the current build configuration will be ignored.
Restoring process will be performed only if all files, expected for actual
configuration, are presented in NV storage.

\param[in] memoryId - an identifier of PDS file or directory to be restored
                      from non-volatile memory.

\return true, if all expected files have been restored, false - otherwise.
******************************************************************************/
bool PDS_Restore(PDS_MemId_t memoryId);

/**************************************************************************//**
\brief Stores data in non-volatile memory in background, not blocking other
       processes.

\ingroup PDS

All PDS files which are absent in the current build configuration will be ignored.

\param[in] memoryId - an identifier of PDS file or directory to be stored
                      in non-volatile memory.

\return True, if storing process has begun, false - otherwise.
******************************************************************************/
bool PDS_Store(PDS_MemId_t memoryId);

/**************************************************************************//**
\brief Deletes data from non-volatile storage except the Persistent items
       depending on the parameter passed.

\param[in] includingPersistentItems - deletes Persistent items if TRUE
                                      deletes all other items except Persistent 
                                      items if FALSE

\return PDS_DataServerState_t - status of PDS DeleteAll
******************************************************************************/
PDS_DataServerState_t PDS_DeleteAll(bool includingPersistentItems);

/**************************************************************************//**
\brief Extempts the item from the Delete All command. Makes the item
		double persistent

\param[in] PDS_MemId_t - Item ID to be exempted

\return bool - True - Success; False - Failure
******************************************************************************/
bool PDS_AddItemExcpetionFromDeleteAll (PDS_MemId_t itemID);

/*****************************************************************************//**
\brief Removes specified file records from NV Storage

\ingroup PDS

\param[in] memoryId - an identifier of PDS file or directory to be removed
                      from NV memory.

\return - PDS state as an operation result.
******************************************************************************/
PDS_DataServerState_t PDS_Delete(PDS_MemId_t memoryId);


/**************************************************************************//**
\brief Checks if the specified PDS file or directory can be restored
       from non-volatile memory

\ingroup PDS

PDS files not included in the current build configuration will be ignored.

\param[in] memoryId - an identifier of PDS file or directory to be checked.

\return true, if the specified memory can be restored; false - otherwise.
******************************************************************************/
bool PDS_IsAbleToRestore(PDS_MemId_t memoryId);

/**************************************************************************//**
\brief Checks if the specified PDS file or directory can be stored
       in non-volatile memory

\ingroup PDS

\param[in] memoryId - an identifier of PDS file or directory to be checked.

\return true, if the specified memory can be stored; false - otherwise.
******************************************************************************/
bool PDS_IsAbleToStore(PDS_MemId_t memoryId);

/******************************************************************************
\brief To register the callback for the Item Write completion

\param[in] pdsModuleOffset            - Module OFFSET;
\param[in] callbackFn    -   pointer to callback functions;

returns : none
******************************************************************************/

void PDS_RegisterWriteCompleteCallback (void (*callbackFn)(PDS_MemId_t));

/******************************************************************************
\brief To register the callback for the Item update memory.
Updates BC parameters after restoring taking into account possible size


\param[in] PDS_UpdateMemory_t            - PDS_UpdateMemory_t;
\param[in] callbackFn    -   pointer to callback functions;

returns : none

******************************************************************************/

void PDS_RegisterUpdateMemoryCallback (bool (*callbackFn)(PDS_UpdateMemory_t *));

/******************************************************************************
\brief PDS store item handler

Actual flash write operation of a particular Item ID
Can be called when system is Idle or when necessary

\param[in] - Item ID to be written in to flash
******************************************************************************/
void PDS_StoreItemTaskHandler(void);

/******************************************************************************
\brief To get the item descriptor for the given item ID

\param[in] memoryId            - item id;
\param[in] itemDescrToGet    - pointer to item descriptor to be loaded;

returns true if descriptor is found out for the given item ID, false - otherwise
******************************************************************************/
bool PDS_GetItemDescr(PDS_MemId_t memoryId, 
                                      ItemIdToMemoryMapping_t *itemDescrToGet );

#endif  //#ifndef _PERSISTDATASERVER_H

