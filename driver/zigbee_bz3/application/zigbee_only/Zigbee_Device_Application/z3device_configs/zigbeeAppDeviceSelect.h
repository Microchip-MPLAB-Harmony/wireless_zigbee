/*******************************************************************************
  Zigbee AppDeviceSeelect Configuration Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zigbeeAppDeviceSelect.h

  Summary:
    This file contains the Zigbee AppDeviceSeelect configurations.

  Description:
    This file contains the Zigbee AppDeviceSeelect configurations.
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

/************************************************************
zigbeeAppDeviceSelect.h
************************************************************/
#ifndef _Z3_DEVICETYPE_CONFIG_H_
#define _Z3_DEVICETYPE_CONFIG_H_

/* Application Device Types Definitions - Do Not Change */
#define APP_DEVICE_TYPE_COLOR_SCENE_CONTROLLER  1
#define APP_DEVICE_TYPE_MULTI_SENSOR            2
#define APP_DEVICE_TYPE_COMBINED_INTERFACE      3
#define APP_DEVICE_TYPE_THERMOSTAT              4
#define APP_DEVICE_TYPE_IAS_ACE                 5
#define APP_DEVICE_TYPE_ON_OFF_LIGHT            10
#define APP_DEVICE_TYPE_DIMMABLE_LIGHT          11
#define APP_DEVICE_TYPE_COLOR_LIGHT             12
#define APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT    13
#define APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT 14

#define APP_ZGP_DEVICE_TYPE_NONE                0
#define APP_ZGP_DEVICE_TYPE_PROXY_BASIC         1
#define APP_ZGP_DEVICE_TYPE_COMBO_BASIC         2

/*Select Light device type*/
//#define APP_Z3_DEVICE_TYPE            APP_DEVICE_TYPE_DIMMABLE_LIGHT
//#define APP_Z3_DEVICE_TYPE            APP_DEVICE_TYPE_COLOR_LIGHT
#define APP_Z3_DEVICE_TYPE              APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
//#define APP_Z3_DEVICE_TYPE            APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
//#define APP_Z3_DEVICE_TYPE            APP_DEVICE_TYPE_ON_OFF_LIGHT

//#define APP_Z3_DEVICE_TYPE            APP_DEVICE_TYPE_THERMOSTAT

//#define APP_Z3_DEVICE_TYPE            APP_DEVICE_TYPE_COMBINED_INTERFACE

/* End Device types*/
//#define APP_Z3_DEVICE_TYPE            APP_DEVICE_TYPE_IAS_ACE
//#define APP_Z3_DEVICE_TYPE            APP_DEVICE_TYPE_COLOR_SCENE_CONTROLLER
//#define APP_Z3_DEVICE_TYPE            APP_DEVICE_TYPE_MULTI_SENSOR

//To Configure CombinedInterface as Router
#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_COMBINED_INTERFACE)
//#define COMBINED_INTERFACE_ROUTER
#endif

#define CS_UID 0xbee //Unique Identifier (UID) determining the device extended address

#ifndef CPU_CLK_HZ
#define CPU_CLK_HZ              64000000  // Core Clock
// #define CPU_CLK_HZ              48000000  // Core Clock
#endif

#endif
