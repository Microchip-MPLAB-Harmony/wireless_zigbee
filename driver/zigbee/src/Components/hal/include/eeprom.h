/*******************************************************************************
  HAL Eeprom Header File

  Company:
    Microchip Technology Inc.

  File Name:
    eeprom.h

  Summary:
    The header file describes the EEPROM interface.

  Description:
    The header file describes the EEPROM interface.
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

/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

#ifndef _EEPROM_H
#define _EEPROM_H

// \cond
/******************************************************************************
                   Includes section
******************************************************************************/
#include <sysTypes.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#if defined(AT91SAM7X256)
  #define EEPROM_DATA_MEMORY_SIZE 0x400u
#elif defined(ATMEGA1281) || defined(ATMEGA2561) || defined(ATMEGA1284) || defined(AT90USB1287) \
   || defined(ATXMEGA256A3) || defined(ATXMEGA256D3) || defined(ATMEGA128RFA1) || defined(AT91SAM3S4C) \
   || defined(AT91SAM4S16C)
  #define EEPROM_DATA_MEMORY_SIZE 0x1000u
#elif defined(ATSAMR21G18A) || defined(ATSAMR21E18A) || defined(ATSAMR21E19A)
   #if defined(HAL_USE_EEPROM_EMULATION)
      #if defined(HAL_2K)
        #define EEPROM_DATA_MEMORY_SIZE (2 * 1024)  // 2 KB
      #else // defined(HAL_4K)
        #define EEPROM_DATA_MEMORY_SIZE (4 * 1024) // 4KB
      #endif
   #else //! defined (HAL_USE_EEPROM_EMULATION)
     #define EEPROM_DATA_MEMORY_SIZE (4 * 1024) // 4KB
   #endif
#elif defined(ATMEGA256RFR2) || defined(ATMEGA2564RFR2)
  #define EEPROM_DATA_MEMORY_SIZE 0x2000u
#elif defined(ATXMEGA128A1) || defined(ATXMEGA128B1)
  #define EEPROM_DATA_MEMORY_SIZE 0x800u
#endif
// \endcond

/******************************************************************************
                   Types section
******************************************************************************/
/**************************************************************************//**
\brief eeprom access control structure
******************************************************************************/
typedef struct
{
  /** \brief EEPROM address */
  uint16_t address;
  /** \brief pointer to data memory */
  uint8_t *data;
  /** \brief number of bytes */
  uint16_t length;
} HAL_EepromParams_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/******************************************************************************
\brief Reads a number of bytes defined by HAL_EepromParams_t from the EEPROM.
\param[in]
  param - address of HAL_EepromParams_t structure. \n
  fields of structure set by user: \n
  address - eeprom address \n
  data - pointer to data memory \n
  length - number of bytes
\param[in]
  readDone - pointer to the function that will notify about reading completion;
             can be set to NULL
\return
  0 - success, \n
  -1 - the number of bytes to read is too large, \n
  -2 - the previous EEPROM request is not completed yet.
******************************************************************************/
int HAL_ReadEeprom(HAL_EepromParams_t *params, void (*readDone)());

/******************************************************************************
\brief Writes a number of bytes defined by HAL_EepromParams_t to EEPROM.
By writeDone parameter user can control if write operation will be asynchronous
or synchronous.
\param[in]
  param - address of HAL_EepromParams_t structure. \n
  fields of structure set by user: \n
  address - eeprom address \n
  data - pointer to data memory \n
  length - number of bytes
\param[in]
  writeDone - pointer to the function that will notify about writing completion;
              can be set to NULL \n
  Only for avr: \n
  if writeDone is NULL write operation will be synchronous.
\return
  0 - success, \n
  -1 - the number of bytes to write is too large, \n
  -2 - the previous EEPROM request is not completed yet.
******************************************************************************/
int HAL_WriteEeprom(HAL_EepromParams_t *params, void (*writeDone)());

/**************************************************************************//**
\brief Checks the eeprom state.

\return
  true  - eeprom is busy; \n
  false - eeprom is free;
******************************************************************************/
bool HAL_IsEepromBusy(void);

/**************************************************************************//**
\brief Stops current write operation.
******************************************************************************/
void HAL_StopWriteToEeprom(void);

#endif /*_EEPROM_H*/

//eof eeprom.h
