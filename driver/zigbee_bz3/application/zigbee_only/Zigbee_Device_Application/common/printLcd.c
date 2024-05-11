/*******************************************************************************
  Print LCD Source File

  Company:
    Microchip Technology Inc.

  File Name:
    printLcd.c

  Summary:
    This file contains the Print LCD Implementation

  Description:
    This file contains the Print LCD Implementation
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

#if(BSP_SUPPORT == BOARD_SAMR21_ZLLEK))

#if APP_DEVICE_EVENTS_LOGGING == 1

/******************************************************************************
                    Includes section
******************************************************************************/
#include <z3Device.h>
#include <printLcd.h>
#include <sysTypes.h>
#include <appTimer.h>
#if defined(BOARD_MEGARF) || defined(BOARD_SAMR21)
#include <lcdExt.h>
#endif
#include <stdarg.h>
#include <stdio.h>

/******************************************************************************
                    Local variables section
******************************************************************************/
static HAL_AppTimer_t timer;

/******************************************************************************
                    Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Clear the LCD information line
******************************************************************************/
static void clearLine(void)
{
  const char clean[] = "                     ";

  LCD_PRINT(0, 3, clean);
  (void)clean;
}

/**************************************************************************//**
\brief Print a formatted string on the LCD for 10 seconds
******************************************************************************/
void dbgLcdMsg(const char *format, ...)
{
  uint8_t str[21];
  char *ptr = (char *)str;
  va_list ap;

  va_start(ap, format);
  vsnprintf(ptr, sizeof(str), format, ap);
  va_end(ap);
  clearLine();
  LCD_PRINT(0, 3, ptr);

  HAL_StopAppTimer(&timer);
  timer.mode = TIMER_ONE_SHOT_MODE;
  timer.interval = 5000;
  timer.callback = clearLine;
  HAL_StartAppTimer(&timer);
}

#endif // APP_DEVICE_EVENTS_LOGGING == 1
#endif // (BSP_SUPPORT == BOARD_SAMR21_ZLLEK))
// eof printLcd.c
