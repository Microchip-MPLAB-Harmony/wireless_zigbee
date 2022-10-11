/*****************************************************************************//**
\file  halFlash.h

\brief  Declarations of flash access module.

\author
    Microchip Corporation: http://ww.microchip.com \n
    Support email: support@microchip.com

  Copyright (c) 2008-2015, Microchip Corporation. All rights reserved.
  Licensed under Microchip's Limited License Agreement.

\internal
  History:
    07/04/14 karthik.p_u - Created
**********************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/
#ifndef _HALFLASH_H
#define _HALFLASH_H

/******************************************************************************
                   Includes section
******************************************************************************/
#if defined(__ICCARM__)
#include <pic32cx1012bz25048_fpga.h>
#elif defined (__GNUC__)
#include <xc.h>
#endif

#include <flash.h>
#include <halTaskManager.h>
#include <eeprom.h>
#include <Core_cm4.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#define CMD_KEY                       0xA5
#define PAGE_SIZE                     64
#define NO_OF_PAGES_PER_ROW           4
#define NO_OF_HALF_WORDS_PER_PAGE     32
#define ROW_SIZE                      (256)
#define ROW_SIZE_IN_HALF_WORDS        (ROW_SIZE / 4) //each 32bit alighned
#define FLASH_MAIN_ADDRESS_SPACE      (0x00U)
#define FLASH_TOTAL_SIZE              (1024*1024) //KB
#define FLASH_TOTAL_PAGES             (FLASH_TOTAL_SIZE / ROW_SIZE)


#define EEPROM_DATA_MEMORY_SIZE (4 * 1024) // TODO: 4K

#define FLASH_EEPROM_PAGES         (EEPROM_DATA_MEMORY_SIZE / ROW_SIZE)       // Last 16 Pages
#define FLASH_EEPROM_BASE_PAGE     (FLASH_TOTAL_PAGES - FLASH_EEPROM_PAGES)
#define FLASH_EEPROM_BASE_ADDRESS  (FLASH_EEPROM_BASE_PAGE * ROW_SIZE)
#define FLASH_EEPROM_LOCK_REGION   15
#define FLASH_NO_OF_LOCKED_REGIONS 16

#define NVM_MEM        ((volatile uint16_t *)FLASH_MAIN_ADDRESS_SPACE)

//#define NVMCTRL_STATUS_MASK 0x11
/******************************************************************************
                   Types definition section
******************************************************************************/

typedef enum flash_cmd_tag {
  ERASE_ROW = 0x02,
  WRITE_PAGE = 0x04,
  ERASE_AUXILARYROW = 0x05,
  WRITE_AUXILARYPAGE = 0x06,
  LOCK_REGION = 0x40,
  UNLOCK_REGION = 0x41,
  SET_POWERREDUCTIONMODE = 0x42,
  CLEAR_POWERREDUCTIONMODE = 0x43,
  PAGE_BUFFERCLEAR = 0x44,
  SET_SECURITYBIT = 0x45,
  INVALID_ALLCACHE = 0x46
 } flash_cmd_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/

/**************************************************************************//**
  \brief Initializes the flash.
  \param[in] None
******************************************************************************/
void halInitFlash(void);

/**************************************************************************//**
  \brief Writes flash page buffer without erasing.
  \param[in] pageStartAddress - address within the target page
******************************************************************************/
void halWriteFlashPage(uint32_t pageStartAddress);

/**************************************************************************//**
  \brief Read fuse bits from NVM user row.
  \param[in] data - pointer to array
******************************************************************************/
void halReadFuseBits(uint32_t *data);

/**************************************************************************//**
  \brief Write fuse bits to NVM user row.
  \param[in] fusebits - pointer to array which has fuses value to be written
******************************************************************************/
void halWriteFuseBits(uint32_t *fusebits);

#if !defined(HAL_USE_EEPROM_EMULATION)
/**************************************************************************//**
  \brief Prepares single page for write, updates eeprom write request structure
  \param[in] eeprom - EEPROM write request structure
  \return prepared page number
******************************************************************************/
void halFlashWriteEepromPage(HAL_EepromParams_t *eeprom);
#endif

/**************************************************************************//**
  \brief Erases specified flash page.
  \param[in] pageStartAddress - address within the target page
******************************************************************************/
void halEraseFlashPage(uint32_t pageStartAddress);

/**************************************************************************//**
  \brief Writes data to the page buffer.
  \param[in] startOffset - start position for writing within the page
  \param[in] length - data to write length in bytes
  \param[in] data - pointer to data to write
******************************************************************************/
void halFillFlashPageBuffer(uint32_t startOffset, uint16_t length, uint8_t *data);
/******************************************************************************
  \brief Writes the data 32 bit wise in the flash without erasing.
  \param[in] pageStflashAddress - address within the flash
  \length[in] length - legth of the data to be written
  \dtat[in]  - data to be written into the flash
******************************************************************************/
void halWriteFlash32BitData(uint32_t flashAddress, uint16_t length, uint8_t *data );

/**************************************************************************//**
  \brief Reads byte from EEPROM.
  \param[in] address - address of a byte.
  \return read value.
******************************************************************************/
INLINE uint8_t halFlashRead(uint16_t address)
{
  return *(uint8_t *)(FLASH_EEPROM_BASE_ADDRESS + address);
}

#endif // _HALFLASH_H

//eof halFlash.h
