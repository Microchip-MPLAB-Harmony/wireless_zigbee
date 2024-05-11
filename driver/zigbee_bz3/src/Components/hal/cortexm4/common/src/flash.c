/**************************************************************************//**
  \file  flash.c

  \brief Implementation of flash access hardware-independent module.

  \author
      Microchip Corporation: http://ww.microchip.com \n
      Support email: support@microchip.com

    Copyright (c) 2008-2015, Microchip Corporation. All rights reserved.
    Licensed under Microchip's Limited License Agreement.

  \internal
    History:
      15/10/13 Agasthian - Created
      07/04/14 karthik.p_u - Modified
  Last change:
    $Id: flash.c 25824 2013-12-10 08:44:12Z mahendran.p $
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/
#if defined(HAL_USE_FLASH_ACCESS)
/******************************************************************************
                   Includes section
******************************************************************************/
#include <sysTypes.h>
#include <flash.h>
#include <sysUtils.h>
#include <halFlash.h>

/******************************************************************************
                   Definitions section
******************************************************************************/

/******************************************************************************
                   Local variables section
******************************************************************************/

/******************************************************************************
                   Prototypes section
******************************************************************************/

/******************************************************************************
                   Implementations section
******************************************************************************/

/**************************************************************************//**
  \brief Writes data to the page buffer.
  \param[in] startOffset - start position for writing within the page
  \param[in] length - data to write length in bytes
  \param[in] data - pointer to data to write
******************************************************************************/
void HAL_FillFlashPageBuffer(uint32_t startOffset, uint16_t length, uint8_t *data)
{
  halFillFlashPageBuffer(startOffset, length, data);
}

/**************************************************************************//**
  \brief Erases specified flash page.
  \param[in] pageStartAddress - address within the target page
******************************************************************************/
void HAL_EraseFlashPage(uint32_t pageStartAddress)
{
  halEraseFlashPage(pageStartAddress);
}
/**************************************************************************//**
  \brief Write the data of sepecified length into the flash
  \param[in] flashAddress - address within the flash
  \length[in] length - legth of the data to be written
  \data[in]  - data to be written into the flash
******************************************************************************/
void HAL_WriteFlash32BitData(uint32_t flashAddress, uint16_t length, uint8_t *data )
{
  halWriteFlash32BitData(flashAddress, length, data);
}
/**************************************************************************//**
  \brief Writes flash page buffer without erasing.
  \param[in] pageStartAddress - address within the target page
******************************************************************************/
void HAL_WriteFlashPage(uint32_t pageStartAddress)
{
  halWriteFlashPage(pageStartAddress);
}

#endif // defined(HAL_USE_FLASH_ACCESS)
// eof flash.c

