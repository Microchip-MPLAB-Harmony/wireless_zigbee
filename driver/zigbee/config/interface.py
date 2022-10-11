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