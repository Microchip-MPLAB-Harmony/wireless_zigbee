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

print('Load Module: Harmony Wireless Zigbee Driver (Devices and Stack Libraries)')

## Zigbee Devices 
DevColorSceneController  = Module.CreateComponent('ZIGBEE_COLOR_SCENE_CONTROLLER', 'Color Scene Controller', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevColorSceneController.setDisplayType('Zigbee Device')
DevColorSceneController.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
DevColorSceneController.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevColorSceneController.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
DevColorSceneController.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevColorSceneController.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
DevColorSceneController.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
DevColorSceneController.addCapability("BLE_ZIGBEE_PROV_Capability", "BZ_PROV", "BLE ZigBee Commisioning", False)
#DevColorSceneController.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)

DevMultiSensor           = Module.CreateComponent('ZIGBEE_MULTI_SENSOR', 'Multi Sensor', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevMultiSensor.setDisplayType('Zigbee Device')
DevMultiSensor.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
DevMultiSensor.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevMultiSensor.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
DevMultiSensor.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevMultiSensor.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
DevMultiSensor.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
DevMultiSensor.addCapability("BLE_ZIGBEE_PROV_Capability", "BZ_PROV", "BLE ZigBee Commisioning", False)
#DevMultiSensor.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)

DevCombinedInterface     = Module.CreateComponent('ZIGBEE_COMBINED_INTERFACE', 'Combined Interface', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevCombinedInterface.setDisplayType('Zigbee Device')
DevCombinedInterface.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
DevCombinedInterface.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevCombinedInterface.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
DevCombinedInterface.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevCombinedInterface.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
DevCombinedInterface.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
#DevCombinedInterface.addCapability("BLE_ZIGBEE_PROV_Capability", "BZ_PROV", "BLE ZigBee Commisioning", False)
#DevCombinedInterface.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)

DevThermostat            = Module.CreateComponent('ZIGBEE_THERMOSTAT', 'Thermostat', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevThermostat.setDisplayType('Zigbee Device')
DevThermostat.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
DevThermostat.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevThermostat.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
DevThermostat.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevThermostat.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
DevThermostat.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
DevThermostat.addCapability("BLE_ZIGBEE_PROV_Capability", "BZ_PROV", "BLE ZigBee Commisioning", False)
#DevThermostat.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)

DevIASACE                = Module.CreateComponent('ZIGBEE_IAS_ACE', 'IAS ACE', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevIASACE.setDisplayType('Zigbee Device')
DevIASACE.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
DevIASACE.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevIASACE.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
DevIASACE.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevIASACE.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
DevIASACE.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
DevIASACE.addCapability("BLE_ZIGBEE_PROV_Capability", "BZ_PROV", "BLE ZigBee Commisioning", False)
#DevIASACE.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)

DevOnOffLight            = Module.CreateComponent('ZIGBEE_ON_OFF_LIGHT', 'OnOff Light', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevOnOffLight.setDisplayType('Zigbee Device')
DevOnOffLight.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
DevOnOffLight.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevOnOffLight.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
DevOnOffLight.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevOnOffLight.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
DevOnOffLight.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
DevOnOffLight.addCapability("BLE_ZIGBEE_PROV_Capability", "BZ_PROV", "BLE ZigBee Commisioning", False)
#DevOnOffLight.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)

DevDimmableLight         = Module.CreateComponent('ZIGBEE_DIMMABLE_LIGHT', 'Dimmable Light', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevDimmableLight.setDisplayType('Zigbee Device')
DevDimmableLight.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
DevDimmableLight.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevDimmableLight.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
DevDimmableLight.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevDimmableLight.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
DevDimmableLight.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
DevDimmableLight.addCapability("BLE_ZIGBEE_PROV_Capability", "BZ_PROV", "BLE ZigBee Commisioning", False)
#DevDimmableLight.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)

DevColorLight            = Module.CreateComponent('ZIGBEE_COLOR_LIGHT', 'Color Light', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevColorLight.setDisplayType('Zigbee Device')
DevColorLight.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
DevColorLight.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevColorLight.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
DevColorLight.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevColorLight.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
DevColorLight.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
DevColorLight.addCapability("BLE_ZIGBEE_PROV_Capability", "BZ_PROV", "BLE ZigBee Commisioning", False)
#DevColorLight.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)

DevExtendedColorLight    = Module.CreateComponent('ZIGBEE_EXTENDED_COLOR_LIGHT', 'Extended Color Light', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevExtendedColorLight.setDisplayType('Zigbee Device')
DevExtendedColorLight.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
DevExtendedColorLight.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevExtendedColorLight.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
DevExtendedColorLight.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
#DevExtendedColorLight.addDependency("ZIGBEE_CONSOLEComponent", "Zigbee_Console", None, False, False)
DevExtendedColorLight.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
DevExtendedColorLight.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
DevExtendedColorLight.addCapability("BLE_ZIGBEE_PROV_Capability", "BZ_PROV", "BLE ZigBee Commisioning", False)
#DevExtendedColorLight.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)

DevTemperatureColorLight = Module.CreateComponent('ZIGBEE_TEMPERATURE_COLOR_LIGHT', 'Temperature Color Light', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevTemperatureColorLight.setDisplayType('Zigbee Device')
DevTemperatureColorLight.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
DevTemperatureColorLight.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevTemperatureColorLight.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
DevTemperatureColorLight.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevTemperatureColorLight.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
DevTemperatureColorLight.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
DevTemperatureColorLight.addCapability("BLE_ZIGBEE_PROV_Capability", "BZ_PROV", "BLE ZigBee Commisioning", False)
#DevTemperatureColorLight.addDependency('PIC32CX_BZ2_BOOTLOADER_SERVICES', 'PIC32CX_BZ_BOOTLOADER_SERVICES', 'Bootloader Services', False, False)

DevCustomDevice          = Module.CreateComponent('ZIGBEE_CUSTOM', 'Custom Device', 'Wireless/Drivers/Zigbee/Device Types', 'driver/zigbee/config/drv_zigbee_lib.py')
DevCustomDevice.setDisplayType('Zigbee Device')
DevCustomDevice.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
DevCustomDevice.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
DevCustomDevice.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
DevCustomDevice.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
DevCustomDevice.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
DevCustomDevice.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
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

# ZAppSIRunnerApplication    = Module.CreateComponent('ZIGBEE_ZAPPSI', 'ZAppSI', 'Wireless/Drivers/Zigbee/Test', 'driver/zigbee/config/drv_zappsi.py')
# ZAppSIRunnerApplication.setDisplayType('ZigBee Application Serial Interface')
# ZAppSIRunnerApplication.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
# ZAppSIRunnerApplication.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
# ZAppSIRunnerApplication.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
# ZAppSIRunnerApplication.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
# ZAppSIRunnerApplication.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
# ZAppSIRunnerApplication.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)

# MACWSNTester = Module.CreateComponent('ZIGBEE_MACWSNTESTER', 'MAC Tester', 'Wireless/Drivers/Zigbee/MAC Apps', 'driver/zigbee/config/drv_mac_tester.py')
# MACWSNTester.setDisplayType('Zigbee Service')
# MACWSNTester.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
# MACWSNTester.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
# MACWSNTester.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
# MACWSNTester.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
# MACWSNTester.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
# MACWSNTester.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)

# GreenPowerDevSensor = Module.CreateComponent('ZIGBEE_GPD_SENSOR', 'Green Power Device-Sensor', 'Wireless/Drivers/Zigbee/MAC Apps', 'driver/zigbee/config/drv_zgpd.py')
# GreenPowerDevSensor.setDisplayType('Zigbee Green Power Device')
# GreenPowerDevSensor.addDependency('PIC32CX_BZ2_DevSupport_Dependency', 'Device_Support', None, True, True)
# GreenPowerDevSensor.addDependency('PDS_Module', 'PDS_SubSystem', None, True, True)
# GreenPowerDevSensor.addDependency("Zigbee_CRYPTO", "LIB_CRYPTO", None, True, True)
# GreenPowerDevSensor.addDependency('TCC2_PWM_Zigbee', 'PWM', 'Zigbee Timer', False, True)
# GreenPowerDevSensor.addDependency("Zigbee_USART", "DRV_USART", 'Zigbee Console', False, False)
# GreenPowerDevSensor.addDependency("Zigbee_WolfCrypt_Dependency", "LIB_WOLFCRYPT", None, False, True)
