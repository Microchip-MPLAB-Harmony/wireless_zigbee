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

def HandleConsoleDependencyCallback(symbol,event):

    print("HandleConsoleDependencyCallback",symbol,event)
    requiredComponent = ["drv_usart"]
    value = event["value"]
    # value = True
    symbolID = event["id"]
    global localComponent
    localComponent = symbol.getComponent()
    componentids = Database.getActiveComponentIDs()
    print("componentids",componentids)
    
    if value == True:
        if "drv_usart" not in componentids: 
            Database.activateComponents(requiredComponent)
        componentids = Database.getActiveComponentIDs()
        Database.connectDependencies([[zigbeeDeviceType.getValue(),'Zigbee_USART','drv_usart_0','drv_usart']])
        # Database.sendMessage("drv_usart", "DRV_USART_OPERATING_MODE_CONFIG", {"mode": "Asynchronous" ,"isReadOnly" : True ,"isLocked":True})
            
    elif value == False:
        if "drv_usart" in componentids: 
            Database.deactivateComponents(requiredComponent)
            print("componentids",componentids)



#Essential changes for each release
releaseVersion = "v5.0.0"
releaseYear    = "2020"
deviceNameBZ   = "PIC32CX1012BZ250XX"
Function       = "ZIGBEE CONFIGURATOR"


deviceNode = ATDF.getNode("/avr-tools-device-file/devices")
deviceChild = []
deviceChild = deviceNode.getChildren()
deviceName = deviceChild[0].getAttribute("series")
print(deviceName)

global getDeviceName
getDeviceName = drvZigbeeComponent.createStringSymbol("DEVICE_NAME", None)
getDeviceName.setDefaultValue(Variables.get("__PROCESSOR"))
#getDeviceName.setDefaultValue(deviceNameBZ)
getDeviceName.setVisible(True)
getDeviceName.setReadOnly(True)

#getreleaseVersion = drvZigbeeComponent.createStringSymbol("REL_VER", None)
#getreleaseVersion.setDefaultValue(releaseVersion)
#getreleaseVersion.setVisible(True)
#getreleaseVersion.setReadOnly(True)

#getreleaseYear = drvZigbeeComponent.createStringSymbol("REL_YEAR", None)
#getreleaseYear.setDefaultValue(releaseYear)
#getreleaseYear.setVisible(True)
#getreleaseYear.setReadOnly(True)

getStackComponent = drvZigbeeComponent.createStringSymbol("FUNCTIONALITY", None)
getStackComponent.setDefaultValue(Function)
getStackComponent.setVisible(True)
getStackComponent.setReadOnly(True)
# deep_sleep_devicetypes = ["ZIGBEE_MULTISENSOR"]
# if zigbeeDeviceType.getValue() in deep_sleep_devicetypes:
requiredComponent = ["drv_usart"]
componentids = Database.getActiveComponentIDs()
print("componentids",componentids)
if "drv_usart" not in componentids: 
    Database.activateComponents(requiredComponent)

global zigbeeConsole
zigbeeConsole = drvZigbeeComponent.createBooleanSymbol("ZIGBEE_CONSOLE",None)
zigbeeConsole.setDefaultValue(False)
zigbeeConsole.setVisible(True)
zigbeeConsole.setLabel("Enable Console")
zigbeeConsole.setDependencies(HandleConsoleDependencyCallback,["ZIGBEE_CONSOLE"])