/*********************************************************************************************/
/**
\file  

\brief D_XNv Driver Interface

\author
    Microchip Corporation: http://ww.microchip.com \n
    Support email: support@microchip.com

  Copyright (c) 2018, Microchip Corporation. All rights reserved.
  Licensed under Microchip's Limited License Agreement.

\internal

$Id: D_XNv.h 24615 2013-02-27 05:14:24Z mahendranp $

***************************************************************************************************/

#ifndef D_XNV_H
#define D_XNV_H

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

#if defined BOOTLOADER
typedef uint8_t D_XNv_Size_t;
#else
typedef uint16_t D_XNv_Size_t;
#endif

/***************************************************************************************************
* EXPORTED MACROS AND CONSTANTS
***************************************************************************************************/

#if defined(TESTHARNESS)
#define D_XNV_SECTOR_SIZE             (4096uL)
#else
#define D_XNV_SECTOR_SIZE             (65536uL)
#endif

/***************************************************************************************************
* EXPORTED FUNCTIONS
***************************************************************************************************//**************************************************************************/
/**
  \brief Read bytes from the external NV.
        Note: offset+numberOfBytes must be <=0x10000 (meaning sector crossing is not permitted)

  \param[in] sector The sector to use (0..7)
  \param[in] offset The offset to start reading at pBuffer The start address of the buffer to store the read data to
            numberOfBytes The number of bytes to read

  \return None
 *****************************************************************************
*/
void D_XNv_Read(uint8_t sector, uint16_t offset, uint8_t *pBuffer, D_XNv_Size_t numberOfBytes);

/**************************************************************************/
/**
  \brief Write bytes to the external NV.
        Note: offset+numberOfBytes must be <=0x10000 (meaning sector crossing is not permitted)

  \param[in] sector The sector to use (0..7)
  \param[in] offset The offset to start writing to pBuffer The start address of the buffer that contains the data to write
  \param[in] numberOfBytes The number of bytes to write

  \return None
 *****************************************************************************
*/
void D_XNv_Write(uint8_t sector, uint16_t offset, const uint8_t *pBuffer, D_XNv_Size_t numberOfBytes);

/**************************************************************************/
/**
  \brief Erases a sector of the external NV.
        Note: The erase operation can take very long, depending on the actual chip that is used.
          Typical erase times are 600-1500 ms. This function will return immediately, however.
          The next request to D_XNv will first wait until the erase has finished.

  \param[in] sector The sector to use (0..7)

  \return None
 *****************************************************************************
*/
void D_XNv_EraseSector(uint8_t sector);

/**************************************************************************/
/**
  \brief Checks if the requested range is empty (containing all 0xFF).
        Note: A special case is when numberOfBytes==0, which requests to check 0x10000 bytes.
              Sector crossing is not permitted

  \param[in] sector The sector to use (0..7)
  \param[in] offset The start offset to check
  \param[in] numberOfBytes The number of bytes to check

  \return TRUE if the range is empty, FALSE otherwise.
 *****************************************************************************
*/
bool D_XNv_IsEmpty(uint8_t sector, uint16_t offset, D_XNv_Size_t numberOfBytes);

/**************************************************************************/
/**
  \brief Compare bytes with contents of the external NV.
        Note: offset+numberOfBytes must be <=0x10000 (meaning sector crossing is not permitted)

  \param[in] sector The sector to use (0..7)
  \param[in] offset The offset to start comparing with pBuffer The start address of the buffer that contains the data to compare with
            numberOfBytes The number of bytes to compare

  \return TRUE if the range is equal, FALSE otherwise.
 *****************************************************************************
*/
bool D_XNv_IsEqual(uint8_t sector, uint16_t offset, const uint8_t *pBuffer, D_XNv_Size_t numberOfBytes);

/***************************************************************************************************
* END OF C++ DECLARATION WRAPPER
***************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif // D_XNV_H
