"""*****************************************************************************
* Copyright (C) 2022 Microchip Technology Inc. and its subsidiaries.
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
*****************************************************************************"""

#####################################################################################################
#################               GREEN POWER CONFIGURATION                             ###############
#####################################################################################################
    # Green Power Device Type
global greenPowerConfigZGPDeviceType
greenPowerConfigZGPDeviceType = drvZigbeeComponent.createKeyValueSetSymbol("GP_DEVICE_TYPE", GreenPowerConfigMenu)
greenPowerConfigZGPDeviceType.setLabel("GP Device Type")
greenPowerConfigZGPDeviceType.addKey("NONE", "NONE", "None")
greenPowerConfigZGPDeviceType.addKey("COMBO_BASIC", "COMBO_BASIC", "COMBO_BASIC")
greenPowerConfigZGPDeviceType.addKey("PROXY_BASIC", "PROXY_BASIC", "PROXY_BASIC")
greenPowerConfigZGPDeviceType.setDefaultValue(0)
greenPowerConfigZGPDeviceType.setOutputMode("Value")
greenPowerConfigZGPDeviceType.setDisplayMode("Description")
greenPowerConfigZGPDeviceType.setDescription("Green Power Device Type of the application")

    # Disable Translation Table
greenPowerConfigTranslationTable = drvZigbeeComponent.createBooleanSymbol("DISABLE_TRANSLATION_TABLE", GreenPowerConfigMenu)
greenPowerConfigTranslationTable.setLabel("Disable Translation Table")
greenPowerConfigTranslationTable.setDefaultValue(False)
greenPowerConfigTranslationTable.setDescription("DISABLE_TRANSLATION_TABLE- check the box to enable")
greenPowerConfigTranslationTable.setVisible(gpMenuCheck())

    # Multi Sensor Suppport
greenPowerConfigMultiSensorSupport = drvZigbeeComponent.createBooleanSymbol("MULTI_SENSOR_SUPPORT", GreenPowerConfigMenu)
greenPowerConfigMultiSensorSupport.setLabel("Multi Sensor Support")
greenPowerConfigMultiSensorSupport.setDefaultValue(True)
greenPowerConfigMultiSensorSupport.setDescription("MULTI_SENSOR_SUPPORT- check the box to enable")
greenPowerConfigMultiSensorSupport.setVisible(gpMenuCheck())
getDevice = zigbeeDeviceType.getValue()
if ((getDevice != "ZIGBEE_COMBINED_INTERFACE")
    ):
    greenPowerConfigMultiSensorSupport.setDefaultValue(False)
    greenPowerConfigMultiSensorSupport.setReadOnly(True)
