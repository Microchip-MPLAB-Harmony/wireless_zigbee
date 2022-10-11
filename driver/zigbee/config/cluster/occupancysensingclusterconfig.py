############################################################################################################
###########################################  OCCUPANCYSENSING CLUSTER CONFIGURATION   ######################
############################################################################################################

############################################################################################################
############################################# Function Definitions #########################################
############################################################################################################
def occupancySensingClusterCsCheck(symbol, event):
    if (occupancySensingCluster.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def occupancySensingClusterEnableCheck(symbol, event):
    if (occupancySensingCluster.getValue() == False):
        symbol.setEnabled(False)
    else:
        symbol.setEnabled(True)

def customOccupancySensingClusterEnableCheck(symbol, event):
    if ((zigbeeDeviceType.getValue() == 'ZIGBEE_CUSTOM') and (occupancySensingCluster.getValue() == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def occupancySensingClusterClientCheck(symbol, event):
    if ((occupancySensingCluster.getValue() == False) or occupancySensingClusterCS.getValue() == "SERVER"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def occupancySensingClusterServerCheck(symbol, event):
    if ((occupancySensingCluster.getValue() == False) or occupancySensingClusterCS.getValue() == "CLIENT"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def occupancySensingClusterHandling():

    getDevice = zigbeeDeviceType.getValue()

    if ((getDevice == "ZIGBEE_COLOR_SCENE_CONTROLLER")
        or (getDevice == "ZIGBEE_CONTROL_BRIDGE")
        or (getDevice == "ZIGBEE_IAS_ACE")
        or (getDevice == "ZIGBEE_ON_OFF_LIGHT")
        or (getDevice == "ZIGBEE_DIMMABLE_LIGHT")
        or (getDevice == "ZIGBEE_COLOR_LIGHT")
        or (getDevice == "ZIGBEE_EXTENDED_COLOR_LIGHT")
        or (getDevice == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")
        ):
        occupancySensingCluster.setVisible(False)
        occupancySensingCluster.setValue(False)
    elif ((getDevice == "ZIGBEE_COMBINED_INTERFACE")):
        occupancySensingCluster.setVisible(True)
        occupancySensingCluster.setValue(True)
        occupancySensingCluster.setReadOnly(True)
        occupancySensingClusterCS.setValue("CLIENT")
        occupancySensingClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_MULTI_SENSOR")):
        occupancySensingCluster.setVisible(True)
        occupancySensingCluster.setValue(True)
        occupancySensingCluster.setReadOnly(True)
        occupancySensingClusterCS.setValue("SERVER")
        occupancySensingClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_THERMOSTAT")):
        occupancySensingCluster.setVisible(True)
        occupancySensingCluster.setValue(True)
        occupancySensingCluster.setReadOnly(True)
        occupancySensingClusterCS.setValue("BOTH")
        occupancySensingClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_CUSTOM")):
        occupancySensingCluster.setVisible(True)
        occupancySensingCluster.setValue(True)
        occupancySensingClusterCS.setValue("BOTH")
    else:
        occupancySensingCluster.setVisible(False)

def occupancySensingClusterServerAttributeCountUpdate(symbol, event):
    count = 0
    if (occupancySensingClusterServerAttributeOccupancy.getValue()):
        count += 1
    if (occupancySensingClusterServerAttributeOccupancySensingType.getValue()):
        count += 1
    if (occupancySensingClusterServerAttributeOSensingTypeBitmap.getValue()):
        count += 1
    if (occupancySensingClusterServerAttributePIROToUDelay.getValue()):
        count += 1
    if (occupancySensingClusterServerAttributePIRUToUDelay.getValue()):
        count += 1
    if (occupancySensingClusterServerAttributePIRUToOThershold.getValue()):
        count += 1
    if (occupancySensingClusterServerAttributeUltOccToUnOccDelay.getValue()):
        count += 1
    if (occupancySensingClusterServerAttributeUltUnOccToOccDelay.getValue()):
        count += 1
    if (occupancySensingClusterServerAttributeUltUnOccToOccTher.getValue()):
        count += 1
    if (occupancySensingClusterServerAttributePhyContOccToUnOccDelay.getValue()):
        count += 1
    if (occupancySensingClusterServerAttributePhyContUnOccToOccDelay.getValue()):
        count += 1
    if (occupancySensingClusterServerAttributePhyContUnOccToOccThers.getValue()):
        count += 1
    if (occupancySensingClusterServerAttributeClusterRevision.getValue()):
        count += 1
    occupancySensingClusterServerAttributeCount.setValue(count) 
    return count

def occupancySensingClusterClientAttributeCountUpdate(symbol, event):
    count = 0
    if (occupancySensingClusterClientAttributeClusterRevision.getValue()):
        count += 1
    occupancySensingClusterClientAttributeCount.setValue(count)
    return count
############################################################################################################
##################################### Configuration Item Definitions #######################################
############################################################################################################

global occupancySensingCluster
occupancySensingCluster = drvZigbeeComponent.createBooleanSymbol("OCCUPANCYSENSING_CLUSTER_ENABLE", clusterConfigMenu)
occupancySensingCluster.setLabel("0x0406 Occupancy Sensing Cluster")
occupancySensingCluster.setDefaultValue(False)
occupancySensingCluster.setVisible(False)
occupancySensingCluster.setDescription("OCCUPANCYSENSING CLUSTER- check the box to enable")
occupancySensingCluster.setReadOnly(False)

global occupancySensingClusterCS
occupancySensingClusterCS = drvZigbeeComponent.createComboSymbol("OCCUPANCYSENSING_CLUSTER_CS",  occupancySensingCluster, ["CLIENT","SERVER", "BOTH"])
occupancySensingClusterCS.setLabel("Supported Implementation")
occupancySensingClusterCS.setDefaultValue("BOTH")
#occupancySensingClusterCS.setVisible(False)
occupancySensingClusterCS.setDescription("occupancySensing Cluster Supported Implementation- Select the option")
occupancySensingClusterCS.setDependencies(occupancySensingClusterCsCheck,["OCCUPANCYSENSING_CLUSTER_ENABLE"])

occupancySensingClusterClientMenu = drvZigbeeComponent.createMenuSymbol("OCCUPANCYSENSING_CLUSTER_CLIENT_MENU", occupancySensingCluster)
occupancySensingClusterClientMenu.setLabel("Client")
#occupancySensingClusterClientMenu.setVisible(False)
occupancySensingClusterClientMenu.setDescription("OCCUPANCYSENSING CLUSTER CLIENT")
occupancySensingClusterClientMenu.setDependencies(occupancySensingClusterClientCheck,["OCCUPANCYSENSING_CLUSTER_CS","OCCUPANCYSENSING_CLUSTER_ENABLE"])

occupancySensingClusterServerMenu = drvZigbeeComponent.createMenuSymbol("OCCUPANCYSENSING_CLUSTER_SERVER_MENU", occupancySensingCluster)
occupancySensingClusterServerMenu.setLabel("Server")
#occupancySensingClusterServerMenu.setVisible(False)
occupancySensingClusterServerMenu.setDescription("OCCUPANCYSENSING CLUSTER SERVER")
occupancySensingClusterServerMenu.setDependencies(occupancySensingClusterServerCheck,["OCCUPANCYSENSING_CLUSTER_CS","OCCUPANCYSENSING_CLUSTER_ENABLE"])

occupancySensingClusterClientAttributes = drvZigbeeComponent.createMenuSymbol("OCCUPANCYSENSING_CLUSTER_CLIENT__ATTRIBUTES_MENU", occupancySensingClusterClientMenu)
occupancySensingClusterClientAttributes.setLabel("Attributes")
#occupancySensingClusterClientAttributes.setVisible(False)
occupancySensingClusterClientAttributes.setDescription("OCCUPANCYSENSING CLUSTER CLIENT ATTRIBUTES")
occupancySensingClusterClientAttributes.setDependencies(occupancySensingClusterClientCheck,["OCCUPANCYSENSING_CLUSTER_CS"])

# occupancySensingClusterClientCommands = drvZigbeeComponent.createMenuSymbol("OCCUPANCYSENSING_CLUSTER_CLIENT__COMMANDS_MENU", occupancySensingClusterClientMenu)
# occupancySensingClusterClientCommands.setLabel("Commands")
# #occupancySensingClusterClientCommands.setVisible(False)
# occupancySensingClusterClientCommands.setDescription("OCCUPANCYSENSING CLUSTER CLIENT COMMANDS")
# occupancySensingClusterClientCommands.setDependencies(occupancySensingClusterClientCheck,["OCCUPANCYSENSING_CLUSTER_CS"])

occupancySensingClusterServerAttributes = drvZigbeeComponent.createMenuSymbol("OCCUPANCYSENSING_CLUSTER_SERVER__ATTRIBUTES_MENU", occupancySensingClusterServerMenu)
occupancySensingClusterServerAttributes.setLabel("Attributes")
#occupancySensingClusterServerAttributes.setVisible(False)
occupancySensingClusterServerAttributes.setDescription("OCCUPANCYSENSING CLUSTER SERVER ATTRIBUTES")
occupancySensingClusterServerAttributes.setDependencies(occupancySensingClusterServerCheck,["OCCUPANCYSENSING_CLUSTER_CS"])

# occupancySensingClusterServerCommands = drvZigbeeComponent.createMenuSymbol("OCCUPANCYSENSING_CLUSTER_SERVER__COMMANDS_MENU", occupancySensingClusterServerMenu)
# occupancySensingClusterServerCommands.setLabel("Commands")
# #occupancySensingClusterServerCommands.setVisible(False)
# occupancySensingClusterServerCommands.setDescription("OCCUPANCYSENSING CLUSTER SERVER COMMANDS")
# occupancySensingClusterServerCommands.setDependencies(occupancySensingClusterServerCheck,["OCCUPANCYSENSING_CLUSTER_CS"])

#################               Server Attributes                                 ###############

global occupancySensingClusterServerAttributeOccupancy
occupancySensingClusterServerAttributeOccupancy = drvZigbeeComponent.createBooleanSymbol("OC_OCCUPANCY", occupancySensingClusterServerAttributes)
occupancySensingClusterServerAttributeOccupancy.setLabel("0x0000 Occupancy")
occupancySensingClusterServerAttributeOccupancy.setDefaultValue(True)
occupancySensingClusterServerAttributeOccupancy.setDescription("Occupancy - check the box to enable")
occupancySensingClusterServerAttributeOccupancy.setReadOnly(True)

global occupancySensingClusterServerAttributeOccupancySensingType
occupancySensingClusterServerAttributeOccupancySensingType = drvZigbeeComponent.createBooleanSymbol("OC_OCCUPANCYSENSINGTYPE", occupancySensingClusterServerAttributes)
occupancySensingClusterServerAttributeOccupancySensingType.setLabel("0x0001 OccupancySensingType")
occupancySensingClusterServerAttributeOccupancySensingType.setDefaultValue(True)
occupancySensingClusterServerAttributeOccupancySensingType.setDescription("OccupancySensingType - check the box to enable")
occupancySensingClusterServerAttributeOccupancySensingType.setReadOnly(True)

global occupancySensingClusterServerAttributeOSensingTypeBitmap
occupancySensingClusterServerAttributeOSensingTypeBitmap = drvZigbeeComponent.createBooleanSymbol("OC_OCCUPANCYSENSINGTYPEBITMAP", occupancySensingClusterServerAttributes)
occupancySensingClusterServerAttributeOSensingTypeBitmap.setLabel("0x0002 OccupancySensingTypeBitmap")
occupancySensingClusterServerAttributeOSensingTypeBitmap.setDefaultValue(True)
occupancySensingClusterServerAttributeOSensingTypeBitmap.setDescription("OccupancySensingTypeBitmap - check the box to enable")
occupancySensingClusterServerAttributeOSensingTypeBitmap.setReadOnly(True)

global occupancySensingClusterServerAttributePIROToUDelay
occupancySensingClusterServerAttributePIROToUDelay = drvZigbeeComponent.createBooleanSymbol("OC_PIROCCUPIEDTOUNOCCUPIEDDELAY", occupancySensingClusterServerAttributes)
occupancySensingClusterServerAttributePIROToUDelay.setLabel("0x0010 PIROccupiedToUnoccupiedDelay")
occupancySensingClusterServerAttributePIROToUDelay.setDefaultValue(True)
occupancySensingClusterServerAttributePIROToUDelay.setDescription("PIROccupiedToUnoccupiedDelay - check the box to enable")

global occupancySensingClusterServerAttributePIRUToUDelay
occupancySensingClusterServerAttributePIRUToUDelay = drvZigbeeComponent.createBooleanSymbol("OC_PIRUNOCCUPIEDTOOCCUPIEDDELAY", occupancySensingClusterServerAttributes)
occupancySensingClusterServerAttributePIRUToUDelay.setLabel("0x0011 PIRUnoccupiedToOccupiedDelay")
occupancySensingClusterServerAttributePIRUToUDelay.setDefaultValue(True)
occupancySensingClusterServerAttributePIRUToUDelay.setDescription("PIRUnoccupiedToOccupiedDelay - check the box to enable")

global occupancySensingClusterServerAttributePIRUToOThershold
occupancySensingClusterServerAttributePIRUToOThershold = drvZigbeeComponent.createBooleanSymbol("OC_PIRUNOCCUPIEDTOOCCUPIEDTHERSHOLD", occupancySensingClusterServerAttributes)
occupancySensingClusterServerAttributePIRUToOThershold.setLabel("0x0012 PIRUnoccupiedToOccupiedThreshold")
occupancySensingClusterServerAttributePIRUToOThershold.setDefaultValue(True)
occupancySensingClusterServerAttributePIRUToOThershold.setDescription("PIRUnoccupiedToOccupiedThreshold - check the box to enable")

global occupancySensingClusterServerAttributeUltOccToUnOccDelay
occupancySensingClusterServerAttributeUltOccToUnOccDelay = drvZigbeeComponent.createBooleanSymbol("OC_ULTRASONICEOCCUPIEDTOUNOCCUPIEDDELAY", occupancySensingClusterServerAttributes)
occupancySensingClusterServerAttributeUltOccToUnOccDelay.setLabel("0x0020 UltrasonicOccupiedToUnoccupiedDelay")
occupancySensingClusterServerAttributeUltOccToUnOccDelay.setDefaultValue(True)
occupancySensingClusterServerAttributeUltOccToUnOccDelay.setDescription("UltrasonicOccupiedToUnoccupiedDelay - check the box to enable")

global occupancySensingClusterServerAttributeUltUnOccToOccDelay
occupancySensingClusterServerAttributeUltUnOccToOccDelay = drvZigbeeComponent.createBooleanSymbol("OC_ULTRASONICEUNOCCUPIEDTOOCCUPIEDDELAY", occupancySensingClusterServerAttributes)
occupancySensingClusterServerAttributeUltUnOccToOccDelay.setLabel("0x0021 UltrasonicUnoccupiedToOccupiedDelay")
occupancySensingClusterServerAttributeUltUnOccToOccDelay.setDefaultValue(True)
occupancySensingClusterServerAttributeUltUnOccToOccDelay.setDescription("UltrasonicUnoccupiedToOccupiedDelay - check the box to enable")

global occupancySensingClusterServerAttributeUltUnOccToOccTher
occupancySensingClusterServerAttributeUltUnOccToOccTher = drvZigbeeComponent.createBooleanSymbol("OC_ULTRASONICEUNOCCUPIEDTOOCCUPIEDTHERSHOLD", occupancySensingClusterServerAttributes)
occupancySensingClusterServerAttributeUltUnOccToOccTher.setLabel("0x0022 UltrasonicUnoccupiedToOccupiedThreshold")
occupancySensingClusterServerAttributeUltUnOccToOccTher.setDefaultValue(True)
occupancySensingClusterServerAttributeUltUnOccToOccTher.setDescription("UltrasonicUnoccupiedToOccupiedThreshold - check the box to enable")

global occupancySensingClusterServerAttributePhyContOccToUnOccDelay
occupancySensingClusterServerAttributePhyContOccToUnOccDelay = drvZigbeeComponent.createBooleanSymbol("OC_PHYCONTACTTOOCCUPIEDTOUNOCCUPIEDDELAY", occupancySensingClusterServerAttributes)
occupancySensingClusterServerAttributePhyContOccToUnOccDelay.setLabel("0x0030 PhysicalContactOccupiedTo-UnoccupiedDelay")
occupancySensingClusterServerAttributePhyContOccToUnOccDelay.setDefaultValue(True)
occupancySensingClusterServerAttributePhyContOccToUnOccDelay.setDescription("PhysicalContactOccupiedTo-UnoccupiedDelay - check the box to enable")

global occupancySensingClusterServerAttributePhyContUnOccToOccDelay
occupancySensingClusterServerAttributePhyContUnOccToOccDelay = drvZigbeeComponent.createBooleanSymbol("OC_PHYCONTACTTOUNOCCUPIEDTOOCCUPIEDDELAY", occupancySensingClusterServerAttributes)
occupancySensingClusterServerAttributePhyContUnOccToOccDelay.setLabel("0x0031 PhysicalContactUnoccupiedTo-OccupiedDelay")
occupancySensingClusterServerAttributePhyContUnOccToOccDelay.setDefaultValue(True)
occupancySensingClusterServerAttributePhyContUnOccToOccDelay.setDescription("PhysicalContactUnoccupiedTo-OccupiedDelay - check the box to enable")

global occupancySensingClusterServerAttributePhyContUnOccToOccThers
occupancySensingClusterServerAttributePhyContUnOccToOccThers = drvZigbeeComponent.createBooleanSymbol("OC_PHYCONTACTTOUNOCCUPIEDTOOCCUPIEDTHERSHOLD", occupancySensingClusterServerAttributes)
occupancySensingClusterServerAttributePhyContUnOccToOccThers.setLabel("0x0032 PhysicalContactUnoccupiedTo-OccupiedThreshold")
occupancySensingClusterServerAttributePhyContUnOccToOccThers.setDefaultValue(True)
occupancySensingClusterServerAttributePhyContUnOccToOccThers.setDescription("PhysicalContactUnoccupiedTo-OccupiedThreshold - check the box to enable")

global occupancySensingClusterServerAttributeClusterRevision
occupancySensingClusterServerAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("OSC_CLUSTERREVISION", occupancySensingClusterServerAttributes)
occupancySensingClusterServerAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
occupancySensingClusterServerAttributeClusterRevision.setDefaultValue(True)
occupancySensingClusterServerAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
occupancySensingClusterServerAttributeClusterRevision.setReadOnly(True)

global occupancySensingClusterServerAttributeCount
occupancySensingClusterServerAttributeCount = drvZigbeeComponent.createIntegerSymbol("OSC_SERVERATTRIBUTECOUNT", occupancySensingClusterServerAttributes)
occupancySensingClusterServerAttributeCount.setLabel("Attributes Count")
occupancySensingClusterServerAttributeCount.setDefaultValue(occupancySensingClusterServerAttributeCountUpdate(0,0))
occupancySensingClusterServerAttributeCount.setVisible(True)
occupancySensingClusterServerAttributeCount.setDescription("Attributes Count")
occupancySensingClusterServerAttributeCount.setReadOnly(True)
occupancySensingClusterServerAttributeCount.setDependencies(occupancySensingClusterServerAttributeCountUpdate,["OSC_CLUSTERREVISION","OC_PHYCONTACTTOUNOCCUPIEDTOOCCUPIEDTHERSHOLD","OC_PHYCONTACTTOUNOCCUPIEDTOOCCUPIEDDELAY","OC_PHYCONTACTTOOCCUPIEDTOUNOCCUPIEDDELAY","OC_ULTRASONICEUNOCCUPIEDTOOCCUPIEDTHERSHOLD","OC_ULTRASONICEUNOCCUPIEDTOOCCUPIEDDELAY","OC_ULTRASONICEOCCUPIEDTOUNOCCUPIEDDELAY","OC_PIRUNOCCUPIEDTOOCCUPIEDTHERSHOLD","OC_PIRUNOCCUPIEDTOOCCUPIEDDELAY","OC_PIROCCUPIEDTOUNOCCUPIEDDELAY","OC_OCCUPANCYSENSINGTYPEBITMAP","OC_OCCUPANCYSENSINGTYPE","OC_OCCUPANCY"])
#################               Server Commands                                 ###############

# Commands received
# No cluster specific commands are received by the server.

# Commands generated
# No cluster specific commands are generated by the server.

#################               Client Attributes                                 ###############
global occupancySensingClusterClientAttributeClusterRevision
occupancySensingClusterClientAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("OSCC_CLUSTERREVISION", occupancySensingClusterClientAttributes)
occupancySensingClusterClientAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
occupancySensingClusterClientAttributeClusterRevision.setDefaultValue(True)
occupancySensingClusterClientAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
occupancySensingClusterClientAttributeClusterRevision.setReadOnly(True)

global occupancySensingClusterClientAttributeCount
occupancySensingClusterClientAttributeCount = drvZigbeeComponent.createIntegerSymbol("OSCC_CLIENTATTRIBUTECOUNT", occupancySensingClusterClientAttributes)
occupancySensingClusterClientAttributeCount.setLabel("Attributes Count")
occupancySensingClusterClientAttributeCount.setDefaultValue(occupancySensingClusterClientAttributeCountUpdate(0,0))
occupancySensingClusterClientAttributeCount.setVisible(True)
occupancySensingClusterClientAttributeCount.setDescription("Attributes Count")
occupancySensingClusterClientAttributeCount.setReadOnly(True)
occupancySensingClusterClientAttributeCount.setDependencies(occupancySensingClusterClientAttributeCountUpdate,["OSCC_CLUSTERREVISION"])

#################               Client Commands                                 ###############

# Commands generated
# No cluster specific commands are generated by the client.

# Commands received
# No cluster specific commands are received by the client.

############################################################################################################
# Default Values Settings based on device type
occupancySensingClusterHandling()

############################################################################################################
##################################### FTL Files Definitions ################################################
############################################################################################################

# OCCUPANCYSENSING CLUSTER Common header
occupancySensingClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_OCCUPANCYSENSING_CLUSTER_CONF", None)
occupancySensingClusterConf.setSourcePath("/driver/zigbee/templates/cluster/occupancysensing/zcloccupancysensingcluster.h.ftl")
occupancySensingClusterConf.setOutputName("zcloccupancysensingcluster.h")
occupancySensingClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
occupancySensingClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
occupancySensingClusterConf.setType("HEADER")
occupancySensingClusterConf.setOverwrite(True)
occupancySensingClusterConf.setMarkup(True)

# OCCUPANCYSENSING CLUSTER - Combined Interface
occupancySensingClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_OCCUPANCYSENSING_CLUSTER_CONF_SRC_CI", None)
occupancySensingClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/occupancysensing/ciOccupancySensingCluster.c.ftl")
occupancySensingClusterConfSrc.setOutputName("ciOccupancySensingCluster.c")
occupancySensingClusterConfSrc.setDestPath("/zigbee/z3device/combinedInterface")
occupancySensingClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/combinedInterface/")
occupancySensingClusterConfSrc.setType("SOURCE")
occupancySensingClusterConfSrc.setOverwrite(True)
occupancySensingClusterConfSrc.setMarkup(True)
occupancySensingClusterConfSrc.setEnabled(checkDevTypeCombInterface)

# OCCUPANCYSENSING CLUSTER - Multi Sensor
occupancySensingClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_OCCUPANCYSENSING_CLUSTER_CONF_SRC_MS", None)
occupancySensingClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/occupancysensing/osOccupancySensingCluster.c.ftl")
occupancySensingClusterConfSrc.setOutputName("osOccupancySensingCluster.c")
occupancySensingClusterConfSrc.setDestPath("/zigbee/z3device/multiSensor")
occupancySensingClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/multiSensor/")
occupancySensingClusterConfSrc.setType("SOURCE")
occupancySensingClusterConfSrc.setOverwrite(True)
occupancySensingClusterConfSrc.setMarkup(True)
occupancySensingClusterConfSrc.setEnabled(checkDevTypeMultiSensor)

# OCCUPANCYSENSING CLUSTER - Thermostat
occupancySensingClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_OCCUPANCYSENSING_CLUSTER_CONF_SRC_TH", None)
occupancySensingClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/occupancysensing/thOccupancySensingCluster.c.ftl")
occupancySensingClusterConfSrc.setOutputName("thOccupancySensingCluster.c")
occupancySensingClusterConfSrc.setDestPath("/zigbee/z3device/thermostat")
occupancySensingClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/thermostat/")
occupancySensingClusterConfSrc.setType("SOURCE")
occupancySensingClusterConfSrc.setOverwrite(True)
occupancySensingClusterConfSrc.setMarkup(True)
occupancySensingClusterConfSrc.setEnabled(checkDevTypeThermostat)

# OCCUPANCYSENSING CLUSTER - Custom
occupancySensingClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_OCCUPANCYSENSING_CLUSTER_CONF_SRC_CUSTOM", None)
occupancySensingClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/occupancysensing/customOccupancySensingCluster.c.ftl")
occupancySensingClusterConfSrc.setOutputName("customOccupancySensingCluster.c")
occupancySensingClusterConfSrc.setDestPath("/zigbee/z3device/custom")
occupancySensingClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/custom/")
occupancySensingClusterConfSrc.setType("SOURCE")
occupancySensingClusterConfSrc.setOverwrite(True)
occupancySensingClusterConfSrc.setMarkup(True)
occupancySensingClusterConfSrc.setEnabled(checkDevTypeCustom and occupancySensingCluster.getValue())
occupancySensingClusterConfSrc.setDependencies(customOccupancySensingClusterEnableCheck,["OCCUPANCYSENSING_CLUSTER_ENABLE"])
############################################################################################################
