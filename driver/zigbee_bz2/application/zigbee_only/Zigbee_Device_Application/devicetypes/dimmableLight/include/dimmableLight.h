/*******************************************************************************
  Dimmable Light Header File

  Company:
    Microchip Technology Inc.

  File Name:
   dimmableLight.h

  Summary:
    This file contains the Dimmable Light interface.

  Description:
    This file contains the Dimmable Light interface.
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

#ifndef _DIMMABLELIGHT_H
#define _DIMMABLELIGHT_H

/******************************************************************************
                    Includes section
******************************************************************************/
/******************************************************************************
                    Definitions section
******************************************************************************/
#if APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_ON_OFF_LIGHT
  #define APP_DEVICE_ID ZLL_ON_OFF_LIGHT_DEVICE_ID
#elif APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_DIMMABLE_LIGHT
  #define APP_DEVICE_ID ZLL_DIMMABLE_LIGHT_DEVICE_ID
#elif APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_LIGHT
  #define APP_DEVICE_ID ZLL_COLOR_LIGHT_DEVICE_ID
#elif APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
  #define APP_DEVICE_ID ZLL_EXTENDED_COLOR_LIGHT_DEVICE_ID
#elif APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
  #define APP_DEVICE_ID ZLL_TEMPERATURE_COLOR_LIGHT_DEVICE_ID
#elif APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_REMOTE
  #define APP_DEVICE_ID ZLL_COLOR_REMOTE_DEVICE_ID
#elif APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_BRIDGE
  #define APP_DEVICE_ID ZLL_CONTROL_BRIDGE_DEVICE_ID
#else
  #error Specified device type is not supported
#endif /* APP_Z3_DEVICE_TYPE */

/******************************************************************************
                             Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Device initialization routine
******************************************************************************/
void dlDeviceInit(void);

/**************************************************************************//**
\brief Device common task handler
******************************************************************************/
void dlDeviceTaskHandler(void);


/******************************************************************************
                    Externals
******************************************************************************/

#endif // _DIMMABLELIGHT_H

// eof dimmableLight.h
