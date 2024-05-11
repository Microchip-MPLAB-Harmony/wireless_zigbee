/*********************************************************************************************/
/**
\file  

\brief S_XNv External Nv Interface

\author
    Microchip Corporation: http://ww.microchip.com \n
    Support email: support@microchip.com

  Copyright (c) 2018, Microchip Corporation. All rights reserved.
  Licensed under Microchip's Limited License Agreement.

\internal

$Id: S_XNv.h 24615 2013-02-27 05:14:24Z mahendranp $

***************************************************************************************************/

#ifndef S_XNV_H
#define S_XNV_H

/***************************************************************************************************
* INCLUDE FILES
***************************************************************************************************/

#include "infrastructure/N_Types/include/N_Types.h"

/***************************************************************************************************
* C++ DECLARATION WRAPPER
***************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************************************
* EXPORTED TYPES
***************************************************************************************************/

/** Identifier type to an item in Flash. Valid range is 1..32767. */
typedef uint16_t S_XNv_ItemId_t;

/** Return value type of most S_XNv functions. */
typedef enum S_XNv_ReturnValue_t
{
    /** The operation succeeded. */
    S_XNv_ReturnValue_Ok,

    /** Unable to write to flash. */
    S_XNv_ReturnValue_Failure,

    /** The item didn't exist but was successfully created and initialised. No error. */
    S_XNv_ReturnValue_DidNotExist,

    /** The item that was attempted to access doesn't exist. */
    S_XNv_ReturnValue_DoesNotExist,

    /** An attempt was made to read or write beyond the length of the item. */
    S_XNv_ReturnValue_BeyondEnd,

    /** The power supply voltage was too low to reliably perform the requested operation. The operation has not been executed. */
    S_XNv_ReturnValue_PowerSupplyTooLow,

} S_XNv_ReturnValue_t;

/** Function type used to check the external NV's power supply.
    Should only return TRUE if the power supply is high enough to reliably perform a write or erase operation.
*/
typedef bool (*S_XNv_PowerSupplyCheckingFunction_t)(void);

/***************************************************************************************************
* EXPORTED MACROS AND CONSTANTS
***************************************************************************************************/


/***************************************************************************************************
* EXPORTED FUNCTIONS
***************************************************************************************************/
/**************************************************************************//**
  \brief Initializes an item with default data, but only if it doesn't exit yet.
         If the item doesn't exist, it is written with the given default data and the status code
    S_XNv_ReturnValue_DidNotExist is returned. Otherwise, the default data is not used, the item
    is kept as it was but read into pDefaultData, and S_XNv_ReturnValue_Ok is returned.
    If NULL is passed for pDefaultData, and the item doesn't exist all data is initialized to 0xFF.
	Note: pDefaultData must not point to constant data.

  \param id The item to initialize.
  \param itemLength The length of the item.
  \param pDefaultData Buffer to 'itemLength' bytes, or NULL.
  
  \return S_XNv_ReturnValue_Ok, S_XNv_ReturnValue_DidNotExist or S_XNv_ReturnValue_PowerSupplyTooLow..
 *****************************************************************************/
S_XNv_ReturnValue_t S_XNv_ItemInit(S_XNv_ItemId_t id, uint16_t itemLength, void* pDefaultData);

/**************************************************************************//**
  \brief Writes an item. If any of the bytes fall outside the item length as passed during S_XNv_ItemInit(), the whole
    write operation does not occur and S_XNv_ReturnValue_BeyondEnd is returned.

  \param id The item to write.
  \param offset The offset in the item to start writing to.
  \param dataLength The length of the data to write.
  \param pData Pointer to 'dataLength' bytes to write.
  
  \return S_XNv_ReturnValue_Ok, S_XNv_ReturnValue_DoesNotExist, S_XNv_ReturnValue_BeyondEnd or S_XNv_ReturnValue_PowerSupplyTooLow.

 *****************************************************************************/
S_XNv_ReturnValue_t S_XNv_Write(S_XNv_ItemId_t id, uint16_t offset, uint16_t dataLength, void* pData);

/**************************************************************************//**
  \brief Reads an item. If any of the bytes fall outside the item length as passed during S_XNv_ItemInit(), the whole
    read operation does not occur and S_XNv_ReturnValue_BeyondEnd is returned.

  \param id The item to read.
  \param offset The offset in the item to start reading from.
  \param dataLength The length of the data to read.
  \param  pData Pointer to a buffer where the read bytes are to be written to.
  
  \return S_XNv_ReturnValue_Ok, S_XNv_ReturnValue_DoesntExist or S_XNv_ReturnValue_BeyondEnd.

 *****************************************************************************/
S_XNv_ReturnValue_t S_XNv_Read(S_XNv_ItemId_t id, uint16_t offset, uint16_t dataLength, void* pData);

/**************************************************************************//**
  \brief Returns the item length of an item.

  \param id The item to get the length from.
  
  \return The length of the item, in bytes, as passed during S_XNv_ItemInit(), or 0 if the item doesn't exist.

 *****************************************************************************/
uint16_t S_XNv_ItemLength(S_XNv_ItemId_t id);

/**************************************************************************//**
  \brief Deletes an item from non-volatile storage.

  \param id The item to delete.
  
  \return S_XNv_ReturnValue_Ok, S_XNv_ReturnValue_DoesntExist or S_XNv_ReturnValue_PowerSupplyTooLow.

 *****************************************************************************/
S_XNv_ReturnValue_t S_XNv_Delete(S_XNv_ItemId_t id);

/**************************************************************************//**
  \brief Erases all items (optionally except the persistent ones) from non-volatile storage.
         The persistent items should typically never be erased in an application!

  \param includingPersistentItems Whether to also erase the peristent items.
  
  \return S_XNv_ReturnValue_Ok or S_XNv_ReturnValue_PowerSupplyTooLow.

 *****************************************************************************/
S_XNv_ReturnValue_t S_XNv_EraseAll(bool includingPersistentItems);

/**************************************************************************//**
  \brief Sets a function to check the power supply. If the power supply checking function is not set,
         the default is to assume that the power supply is always high enough. This is not suitable for
  		 typical applications.When this function is called again,

  \param pf A pointer to a function that S_XNv uses to check the power supply.
  
  \return None

 *****************************************************************************/
void S_XNv_SetPowerSupplyCheckingFunction(S_XNv_PowerSupplyCheckingFunction_t pf);

/**************************************************************************//**
  \brief Checks the item is available or not.

  \param id The item to check
  
  \return true if item is available, false if not.

 *****************************************************************************/
bool S_XNv_IsItemAvailable_Impl(S_XNv_ItemId_t id);

/**************************************************************************//**
  \brief Initiates the compatc Sector Operation This is for application control for Item upgrade
  
  \return none

 *****************************************************************************/
void S_XNv_CompactSector(void);

/***************************************************************************************************
* END OF C++ DECLARATION WRAPPER
***************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif // S_XNV_H
