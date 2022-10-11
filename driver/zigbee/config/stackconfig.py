############################################################################################################
########################               STACK CONFIGURATION                                   ###############
############################################################################################################

def customDeviceTypeCheckForBindingTable():
    if ((zigbeeDeviceType.getValue() == "ZIGBEE_CUSTOM")):
        return(25)
    else:
        return(14)

# Stack Device Type
global stackConfigDeviceType
stackConfigDeviceType = drvZigbeeComponent.createKeyValueSetSymbol("STACK_DEVICE_TYPE", stackConfigMenu)
stackConfigDeviceType.setLabel("Stack Device Type")
#stackConfigDeviceType.addKey("NONE", "NONE", "")
stackConfigDeviceType.addKey("COORDINATOR", "COORDINATOR", "COORDINATOR")
stackConfigDeviceType.addKey("ROUTER", "ROUTER", "ROUTER")
stackConfigDeviceType.addKey("ENDDEVICE", "ENDDEVICE", "ENDDEVICE")
stackConfigDeviceType.setDefaultValue(stackDeviceTypeSetCheck())
stackConfigDeviceType.setOutputMode("Value")
stackConfigDeviceType.setDisplayMode("Description")
stackConfigDeviceType.setDescription("Stack Device Type of the application")
stackConfigDeviceType.setDependencies(ciAsBridgeForstackDevTypeEvent, ["CI_AS_BRIDGE"])

# APS Key Pair Descriptor
stackConfigAPSKeyPairAmount = drvZigbeeComponent.createIntegerSymbol("CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT", stackConfigMenu)
stackConfigAPSKeyPairAmount.setLabel("Number of Key Pair Descriptors ")
stackConfigAPSKeyPairAmount.setDefaultValue(5)
stackConfigAPSKeyPairAmount.setMin(1)
stackConfigAPSKeyPairAmount.setMax(10)
stackConfigAPSKeyPairAmount.setVisible(stackMenuCheck())

# APS Binding Table
stackConfigBindingTableSize = drvZigbeeComponent.createIntegerSymbol("CS_APS_BINDING_TABLE_SIZE", stackConfigMenu)
stackConfigBindingTableSize.setLabel("Binding Table Size")
stackConfigBindingTableSize.setDefaultValue(customDeviceTypeCheckForBindingTable())
stackConfigBindingTableSize.setMin(1)
stackConfigBindingTableSize.setMax(30)
stackConfigBindingTableSize.setVisible(stackMenuCheck())

# Max Children Amount
stackConfigMaxChildren = drvZigbeeComponent.createIntegerSymbol("CS_MAX_CHILDREN_AMOUNT", stackConfigMenu)
stackConfigMaxChildren.setLabel("Maximum Children")
stackConfigMaxChildren.setDefaultValue(6)
stackConfigMaxChildren.setMin(1)
stackConfigMaxChildren.setMax(255)
stackConfigMaxChildren.setVisible(stackMenuCheck())

# Max Router Amount
stackConfigMaxRouter = drvZigbeeComponent.createIntegerSymbol("CS_MAX_CHILDREN_ROUTER_AMOUNT", stackConfigMenu)
stackConfigMaxRouter.setLabel("Maximum Routers")
stackConfigMaxRouter.setDefaultValue(2)
stackConfigMaxRouter.setMin(1)
stackConfigMaxRouter.setMax(255)
stackConfigMaxRouter.setVisible(stackMenuCheck())

# End device Sleep Period
stackConfigEndDeviceSleepPeriod = drvZigbeeComponent.createIntegerSymbol("CS_END_DEVICE_SLEEP_PERIOD", stackConfigMenu)
stackConfigEndDeviceSleepPeriod.setLabel("End device sleep period ")
stackConfigEndDeviceSleepPeriod.setDefaultValue(7000)
stackConfigEndDeviceSleepPeriod.setMin(1)
stackConfigEndDeviceSleepPeriod.setMax(0xFFFF)
stackConfigEndDeviceSleepPeriod.setVisible(stackMenuCheck())

# Neighbor Table Size
stackConfigNeighborTableSize = drvZigbeeComponent.createIntegerSymbol("CS_NEIB_TABLE_SIZE", stackConfigMenu)
stackConfigNeighborTableSize.setLabel("Neighbor Table Size")
stackConfigNeighborTableSize.setDefaultValue(5)
stackConfigNeighborTableSize.setMin(1)
stackConfigNeighborTableSize.setMax(10)
stackConfigNeighborTableSize.setVisible(stackMenuCheck())

# Route Table Size
stackConfigRouteTableSize= drvZigbeeComponent.createIntegerSymbol("CS_ROUTE_TABLE_SIZE", stackConfigMenu)
stackConfigRouteTableSize.setLabel("Routing Table Size")
stackConfigRouteTableSize.setDefaultValue(5)
stackConfigRouteTableSize.setMin(1)
stackConfigRouteTableSize.setMax(10)
stackConfigRouteTableSize.setVisible(stackMenuCheck())

# Address Map Table Size
stackConfigAddrMapTableSize = drvZigbeeComponent.createIntegerSymbol("CS_ADDRESS_MAP_TABLE_SIZE", stackConfigMenu)
stackConfigAddrMapTableSize.setLabel("Address Map Table Size")
stackConfigAddrMapTableSize.setDefaultValue(5)
stackConfigAddrMapTableSize.setMin(1)
stackConfigAddrMapTableSize.setMax(10)
stackConfigAddrMapTableSize.setVisible(stackMenuCheck())
