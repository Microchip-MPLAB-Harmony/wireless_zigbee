/**************************************************************************//**
  \file ledsExt.h

  \brief
    Additional LEDs interface.

  \author
    Microchip Corporation: http://ww.microchip.com \n
    Support email: support@microchip.com

  Copyright (c) 2008-2015, Microchip Corporation. All rights reserved.
  Licensed under Microchip's Limited License Agreement.

  \internal
    History:
    08/04/14 karthik.p_u - Created
******************************************************************************/
#ifndef _LEDS_EXTENSION_H
#define _LEDS_EXTENSION_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <sysTypes.h>

/******************************************************************************
                    Types section
******************************************************************************/
enum
{
  LED_1   = 0,
  LED_2   = 1,
  LED_3   = 2,
  LED_4   = 3,
  LED_5   = 4,
};

/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initialize LEDs.
******************************************************************************/
void BSP_LedsOpen(void);

/**************************************************************************//**
\brief Set brightness level
\param[in] level - new brightness level
******************************************************************************/
void BSP_SetLedBrightnessLevel(uint8_t level);

/**************************************************************************//**
\brief Set the color using Hue and Saturation as parameters
\param[in] level - a new brightness level
******************************************************************************/
void BSP_SetLedColorHS(uint16_t hue, uint8_t saturation);

/**************************************************************************//**
\brief Set the color using X and Y as parameters
\param[in] level - a new brightness level
******************************************************************************/
void BSP_SetLedColorXY(uint16_t x, uint16_t y);

#endif // _LEDS_EXTENSION_H

// eof leds.h
