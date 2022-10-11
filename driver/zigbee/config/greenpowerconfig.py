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
