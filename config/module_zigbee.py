# coding: utf-8
##############################################################################
# Copyright (C) 2019-2020 Microchip Technology Inc. and its subsidiaries.
#
# Subject to your compliance with these terms, you may use Microchip software
# and any derivatives exclusively with Microchip products. It is your
# responsibility to comply with third party license terms applicable to your
# use of third party software (including open source software) that may
# accompany Microchip software.
#
# THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
# EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
# WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
# PARTICULAR PURPOSE.
#
# IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
# INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
# WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
# BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
# FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
# ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
# THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
##############################################################################

pic32cx_bz2_family = {'PIC32CX1012BZ25048',
                      'PIC32CX1012BZ25032',
                      'PIC32CX1012BZ24032',
                      'WBZ451',
                      'WBZ450',
                      }

pic32cx_bz3_family = {'PIC32CX5109BZ31048',
                      'PIC32CX5109BZ31032',
                      'WBZ351',
                      'WBZ350',
                      }
print('Load Module: Harmony Wireless Zigbee Driver (Devices and Stack Libraries)')
global deviceName
deviceName = Variables.get("__PROCESSOR")

## Zigbee Devices 
DevColorSceneController  = Module.CreateComponent('ZIGBEE_COLOR_SCENE_CONTROLLER', 'Color Scene Controller', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevColorSceneController.setDisplayType('Zigbee Device')
DevColorSceneController.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevColorSceneController.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevColorSceneController.addDependency('TC0_TMR_Zigbee', 'TMR', 'Zigbee Timer', False, True)
DevColorSceneController.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
if (deviceName in pic32cx_bz2_family):
    DevColorSceneController.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
    DevColorSceneController.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
    DevColorSceneController.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
    DevColorSceneController.addDependency('PIC32CX_BZ2_OTA_SERVICES', 'PIC32CX_BZ_OTA_SERVICES', 'OTA Services', False, False)
    DevColorSceneController.addCapability("BLE_ZIGBEE_PROV_Capability", "BZ_PROV", "BLE ZigBee Commisioning", False)
elif (deviceName in pic32cx_bz3_family):
    DevColorSceneController.addDependency('PIC32CX_BZ3_DevSupport_Dependency', 'Device_Support', None, True, True)

#DevColorSceneController.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)


DevMultiSensor           = Module.CreateComponent('ZIGBEE_MULTI_SENSOR', 'Multi Sensor', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevMultiSensor.setDisplayType('Zigbee Device')
DevMultiSensor.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevMultiSensor.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevMultiSensor.addDependency('TC0_TMR_Zigbee', 'TMR', 'Zigbee Timer', False, True)
DevMultiSensor.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
if (deviceName in pic32cx_bz2_family):
    DevMultiSensor.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
    DevMultiSensor.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
    DevMultiSensor.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
    DevMultiSensor.addDependency('PIC32CX_BZ2_OTA_SERVICES', 'PIC32CX_BZ_OTA_SERVICES', 'OTA Services', False, False)
    DevMultiSensor.addCapability("BLE_ZIGBEE_PROV_Capability", "BZ_PROV", "BLE ZigBee Commisioning", False)
elif (deviceName in pic32cx_bz3_family):
    DevMultiSensor.addDependency('PIC32CX_BZ3_DevSupport_Dependency', 'Device_Support', None, True, True)

#DevMultiSensor.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)


DevCombinedInterface     = Module.CreateComponent('ZIGBEE_COMBINED_INTERFACE', 'Combined Interface', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevCombinedInterface.setDisplayType('Zigbee Device')
DevCombinedInterface.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevCombinedInterface.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevCombinedInterface.addDependency('TC0_TMR_Zigbee', 'TMR', 'Zigbee Timer', False, True)
DevCombinedInterface.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
if (deviceName in pic32cx_bz2_family):
    DevCombinedInterface.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
    DevCombinedInterface.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
    DevCombinedInterface.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
    DevCombinedInterface.addDependency('PIC32CX_BZ2_OTA_SERVICES', 'PIC32CX_BZ_OTA_SERVICES', 'OTA Services', False, False)
elif (deviceName in pic32cx_bz3_family):
    DevCombinedInterface.addDependency('PIC32CX_BZ3_DevSupport_Dependency', 'Device_Support', None, True, True)
#DevCombinedInterface.addCapability("BLE_ZIGBEE_PROV_Capability", "BZ_PROV", "BLE ZigBee Commisioning", False)
#DevCombinedInterface.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)


DevThermostat            = Module.CreateComponent('ZIGBEE_THERMOSTAT', 'Thermostat', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevThermostat.setDisplayType('Zigbee Device')
DevThermostat.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevThermostat.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevThermostat.addDependency('TC0_TMR_Zigbee', 'TMR', 'Zigbee Timer', False, True)
DevThermostat.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
if (deviceName in pic32cx_bz2_family):
    DevThermostat.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
    DevThermostat.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
    DevThermostat.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
    DevThermostat.addDependency('PIC32CX_BZ2_OTA_SERVICES', 'PIC32CX_BZ_OTA_SERVICES', 'OTA Services', False, False)
    DevThermostat.addCapability("BLE_ZIGBEE_PROV_Capability", "BZ_PROV", "BLE ZigBee Commisioning", False)
elif (deviceName in pic32cx_bz3_family):
    DevThermostat.addDependency('PIC32CX_BZ3_DevSupport_Dependency', 'Device_Support', None, True, True)

#DevThermostat.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)


DevIASACE                = Module.CreateComponent('ZIGBEE_IAS_ACE', 'IAS ACE', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevIASACE.setDisplayType('Zigbee Device')
DevIASACE.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevIASACE.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevIASACE.addDependency('TC0_TMR_Zigbee', 'TMR', 'Zigbee Timer', False, True)
DevIASACE.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
if (deviceName in pic32cx_bz2_family):
    DevIASACE.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
    DevIASACE.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
    DevIASACE.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
    DevIASACE.addDependency('PIC32CX_BZ2_OTA_SERVICES', 'PIC32CX_BZ_OTA_SERVICES', 'OTA Services', False, False)
    DevIASACE.addCapability("BLE_ZIGBEE_PROV_Capability", "BZ_PROV", "BLE ZigBee Commisioning", False)
elif (deviceName in pic32cx_bz3_family):
    DevIASACE.addDependency('PIC32CX_BZ3_DevSupport_Dependency', 'Device_Support', None, True, True)

#DevIASACE.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)


DevOnOffLight            = Module.CreateComponent('ZIGBEE_ON_OFF_LIGHT', 'OnOff Light', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevOnOffLight.setDisplayType('Zigbee Device')
DevOnOffLight.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevOnOffLight.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevOnOffLight.addDependency('TC0_TMR_Zigbee', 'TMR', 'Zigbee Timer', False, True)
DevOnOffLight.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
if (deviceName in pic32cx_bz2_family):
    DevOnOffLight.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
    DevOnOffLight.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
    DevOnOffLight.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
    DevOnOffLight.addDependency('PIC32CX_BZ2_OTA_SERVICES', 'PIC32CX_BZ_OTA_SERVICES', 'OTA Services', False, False)
    DevOnOffLight.addCapability("BLE_ZIGBEE_PROV_Capability", "BZ_PROV", "BLE ZigBee Commisioning", False)
elif (deviceName in pic32cx_bz3_family):
    DevOnOffLight.addDependency('PIC32CX_BZ3_DevSupport_Dependency', 'Device_Support', None, True, True)

#DevOnOffLight.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)


DevDimmableLight         = Module.CreateComponent('ZIGBEE_DIMMABLE_LIGHT', 'Dimmable Light', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevDimmableLight.setDisplayType('Zigbee Device')
DevDimmableLight.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevDimmableLight.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevDimmableLight.addDependency('TC0_TMR_Zigbee', 'TMR', 'Zigbee Timer', False, True)
DevDimmableLight.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
if (deviceName in pic32cx_bz2_family):
    DevDimmableLight.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
    DevDimmableLight.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
    DevDimmableLight.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
    DevDimmableLight.addDependency('PIC32CX_BZ2_OTA_SERVICES', 'PIC32CX_BZ_OTA_SERVICES', 'OTA Services', False, False)
    DevDimmableLight.addCapability("BLE_ZIGBEE_PROV_Capability", "BZ_PROV", "BLE ZigBee Commisioning", False)
elif (deviceName in pic32cx_bz3_family):
    DevDimmableLight.addDependency('PIC32CX_BZ3_DevSupport_Dependency', 'Device_Support', None, True, True)

#DevDimmableLight.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)


DevColorLight            = Module.CreateComponent('ZIGBEE_COLOR_LIGHT', 'Color Light', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevColorLight.setDisplayType('Zigbee Device')
DevColorLight.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevColorLight.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevColorLight.addDependency('TC0_TMR_Zigbee', 'TMR', 'Zigbee Timer', False, True)
DevColorLight.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
if (deviceName in pic32cx_bz2_family):
    DevColorLight.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
    DevColorLight.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
    DevColorLight.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
    DevColorLight.addDependency('PIC32CX_BZ2_OTA_SERVICES', 'PIC32CX_BZ_OTA_SERVICES', 'OTA Services', False, False)
    DevColorLight.addCapability("BLE_ZIGBEE_PROV_Capability", "BZ_PROV", "BLE ZigBee Commisioning", False)
elif (deviceName in pic32cx_bz3_family):
    DevColorLight.addDependency('PIC32CX_BZ3_DevSupport_Dependency', 'Device_Support', None, True, True)

#DevColorLight.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)


DevExtendedColorLight    = Module.CreateComponent('ZIGBEE_EXTENDED_COLOR_LIGHT', 'Extended Color Light', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevExtendedColorLight.setDisplayType('Zigbee Device')
DevExtendedColorLight.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevExtendedColorLight.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevExtendedColorLight.addDependency('TC0_TMR_Zigbee', 'TMR', 'Zigbee Timer', False, True)
DevExtendedColorLight.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
if (deviceName in pic32cx_bz2_family):
    DevExtendedColorLight.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
    DevExtendedColorLight.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
    DevExtendedColorLight.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
    DevExtendedColorLight.addDependency('PIC32CX_BZ2_OTA_SERVICES', 'PIC32CX_BZ_OTA_SERVICES', 'OTA Services', False, False)
    DevExtendedColorLight.addCapability("BLE_ZIGBEE_PROV_Capability", "BZ_PROV", "BLE ZigBee Commisioning", False)
elif (deviceName in pic32cx_bz3_family):
    DevExtendedColorLight.addDependency('PIC32CX_BZ3_DevSupport_Dependency', 'Device_Support', None, True, True)

#DevExtendedColorLight.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)


DevTemperatureColorLight = Module.CreateComponent('ZIGBEE_TEMPERATURE_COLOR_LIGHT', 'Temperature Color Light', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevTemperatureColorLight.setDisplayType('Zigbee Device')
DevTemperatureColorLight.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevTemperatureColorLight.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevTemperatureColorLight.addDependency('TC0_TMR_Zigbee', 'TMR', 'Zigbee Timer', False, True)
DevTemperatureColorLight.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
if (deviceName in pic32cx_bz2_family):
    DevTemperatureColorLight.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
    DevTemperatureColorLight.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
    DevTemperatureColorLight.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
    DevTemperatureColorLight.addDependency('PIC32CX_BZ2_OTA_SERVICES', 'PIC32CX_BZ_OTA_SERVICES', 'OTA Services', False, False)
    DevTemperatureColorLight.addCapability("BLE_ZIGBEE_PROV_Capability", "BZ_PROV", "BLE ZigBee Commisioning", False)
elif (deviceName in pic32cx_bz3_family):
    DevTemperatureColorLight.addDependency('PIC32CX_BZ3_DevSupport_Dependency', 'Device_Support', None, True, True)

#DevTemperatureColorLight.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)


DevCustomDevice          = Module.CreateComponent('ZIGBEE_CUSTOM', 'Custom Device', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevCustomDevice.setDisplayType('Zigbee Device')
DevCustomDevice.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevCustomDevice.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevCustomDevice.addDependency('TC0_TMR_Zigbee', 'TMR', 'Zigbee Timer', False, True)
DevCustomDevice.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
if (deviceName in pic32cx_bz2_family):
    DevCustomDevice.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
    DevCustomDevice.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
    DevCustomDevice.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
    DevCustomDevice.addDependency('PIC32CX_BZ2_OTA_SERVICES', 'PIC32CX_BZ_OTA_SERVICES', 'OTA Services', False, False)
elif (deviceName in pic32cx_bz3_family):
    DevCustomDevice.addDependency('PIC32CX_BZ3_DevSupport_Dependency', 'Device_Support', None, True, True)

#DevCustomDevice.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)


## Zigbee Stack Libraries
#LibSuperSet = Module.CreateComponent('SUPERSET_LIB', 'SuperSet', 'Wireless/ZIGBEE/StackLibrary', 'driver/zigbee/config/drv_zigbee_lib.py')
#LibSuperSet.addCapability('Zigbee_Stack_Lib', 'Zigbee_Stack_Lib')
#LibSuperSet.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)

#LibCoordinator = Module.CreateComponent('COORDINATOR_LIB', 'Coordinator', 'Wireless/ZIGBEE/StackLibrary', 'driver/zigbee/config/drv_stack.py')
#LibCoordinator.addCapability('StackLib_Coordinator', 'StackLib_Coordinator')
#LibCoordinator.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)

#LibRouter = Module.CreateComponent('ROUTER_LIB', 'Router', 'Wireless/ZIGBEE/StackLibrary', 'driver/zigbee/config/drv_stack.py')
#LibRouter.addCapability('StackLib_Router', 'StackLib_Router')
#LibRouter.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)

#LibEndDevice = Module.CreateComponent('ENDDEVICE_LIB', 'EndDevice', 'Wireless/ZIGBEE/StackLibrary', 'driver/zigbee/config/drv_stack.py')
#LibEndDevice.addCapability('StackLib_EndDevice', 'StackLib_EndDevice')
#LibEndDevice.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)


# ZAppSIRunnerApplication = Module.CreateComponent('ZIGBEE_ZAPPSI', 'ZAppSI', 'Wireless/Drivers/Zigbee/Test', 'driver/zigbee/config/drv_zappsi.py')
# ZAppSIRunnerApplication.setDisplayType('ZigBee Application Serial Interface')
# ZAppSIRunnerApplication.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
# ZAppSIRunnerApplication.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
# ZAppSIRunnerApplication.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
# if (deviceName in pic32cx_bz2_family):
    # ZAppSIRunnerApplication.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
    # ZAppSIRunnerApplication.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
    # ZAppSIRunnerApplication.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
# elif (deviceName in pic32cx_bz3_family):
    # ZAppSIRunnerApplication.addDependency('PIC32CX_BZ3_DevSupport_Dependency', 'Device_Support', None, True, True)

# MACWSNTester = Module.CreateComponent('ZIGBEE_MACWSNTESTER', 'MAC Tester', 'Wireless/Drivers/Zigbee/MAC Apps', 'driver/zigbee/config/drv_mac_tester.py')
# MACWSNTester.setDisplayType('Zigbee Service')
# MACWSNTester.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
# MACWSNTester.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
# MACWSNTester.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
# if (deviceName in pic32cx_bz2_family):
    # MACWSNTester.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
    # MACWSNTester.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
    # MACWSNTester.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
# elif (deviceName in pic32cx_bz3_family):
    # MACWSNTester.addDependency('PIC32CX_BZ3_DevSupport_Dependency', 'Device_Support', None, True, True)
    
# GreenPowerDevSensor = Module.CreateComponent('ZIGBEE_GPD_SENSOR', 'Green Power Device-Sensor', 'Wireless/Drivers/Zigbee/MAC Apps', 'driver/zigbee/config/drv_zgpd.py')
# GreenPowerDevSensor.setDisplayType('Zigbee Green Power Device')
# GreenPowerDevSensor.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
# GreenPowerDevSensor.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
# GreenPowerDevSensor.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
# if (deviceName in pic32cx_bz2_family):
    # GreenPowerDevSensor.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
    # GreenPowerDevSensor.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
    # GreenPowerDevSensor.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
# elif (deviceName in pic32cx_bz3_family):
    # GreenPowerDevSensor.addDependency('PIC32CX_BZ3_DevSupport_Dependency', 'Device_Support', None, True, True)
