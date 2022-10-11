############################################################################################################
###########################################  FANCONTROL CLUSTER CONFIGURATION   ############################
############################################################################################################

############################################################################################################
############################################# Function Definitions #########################################
############################################################################################################
def fanControlClusterCsCheck(symbol, event):
    if (fanControlCluster.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def fanControlClusterEnableCheck(symbol, event):
    if (fanControlCluster.getValue() == False):
        symbol.setEnabled(False)
    else:
        symbol.setEnabled(True)

def customFanControlClusterEnableCheck(symbol, event):
    if ((zigbeeDeviceType.getValue() == 'ZIGBEE_CUSTOM') and (fanControlCluster.getValue() == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def fanControlClusterClientCheck(symbol, event):
    if ((fanControlCluster.getValue() == False) or fanControlClusterCS.getValue() == "SERVER"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def fanControlClusterServerCheck(symbol, event):
    if ((fanControlCluster.getValue() == False) or fanControlClusterCS.getValue() == "CLIENT"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def fanControlClusterHandling():

    getDevice = zigbeeDeviceType.getValue()

    if ((getDevice == "ZIGBEE_COLOR_SCENE_CONTROLLER")
        or (getDevice == "ZIGBEE_MULTI_SENSOR")
        or (getDevice == "ZIGBEE_CONTROL_BRIDGE")
        or (getDevice == "ZIGBEE_IAS_ACE")
        or (getDevice == "ZIGBEE_ON_OFF_LIGHT")
        or (getDevice == "ZIGBEE_DIMMABLE_LIGHT")
        or (getDevice == "ZIGBEE_COLOR_LIGHT")
        or (getDevice == "ZIGBEE_EXTENDED_COLOR_LIGHT")
        or (getDevice == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")
        ):
        fanControlCluster.setVisible(False)
        fanControlCluster.setValue(False)
    elif ((getDevice == "ZIGBEE_COMBINED_INTERFACE")):
        fanControlCluster.setVisible(True)
        fanControlCluster.setValue(True)
        fanControlCluster.setReadOnly(True)
        fanControlClusterCS.setValue("CLIENT")
        fanControlClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_THERMOSTAT")):
        fanControlCluster.setVisible(True)
        fanControlCluster.setValue(True)
        fanControlCluster.setReadOnly(True)
        fanControlClusterCS.setValue("BOTH")
        fanControlClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_CUSTOM")):
        fanControlCluster.setVisible(True)
        fanControlCluster.setValue(True)
        fanControlClusterCS.setValue("BOTH")
    else:
        fanControlCluster.setVisible(False)

def fanControlClusterServerAttributeCountUpdate(symbol, event):
    count = 0
    if (fanControlClusterServerAttributeFanMode.getValue()):
        count += 1
    if (fanControlClusterServerAttributeFanModeSequence.getValue()):
        count += 1
    if (fanControlClusterServerAttributeClusterRevision.getValue()):
        count += 1
    fanControlClusterServerAttributeCount.setValue(count) 
    return count

def fanControlClusterClientAttributeCountUpdate(symbol, event):
    count = 0
    if (fanControlClusterClientAttributeClusterRevision.getValue()):
        count += 1
    fanControlClusterClientAttributeCount.setValue(count)
    return count
############################################################################################################
##################################### Configuration Item Definitions #######################################
############################################################################################################

global fanControlCluster
fanControlCluster = drvZigbeeComponent.createBooleanSymbol("FANCONTROL_CLUSTER_ENABLE", clusterConfigMenu)
fanControlCluster.setLabel("0x0202 FanControl Cluster")
fanControlCluster.setDefaultValue(False)
fanControlCluster.setVisible(False)
fanControlCluster.setDescription("FANCONTROL CLUSTER- check the box to enable")
fanControlCluster.setReadOnly(False)

global fanControlClusterCS
fanControlClusterCS = drvZigbeeComponent.createComboSymbol("FANCONTROL_CLUSTER_CS",  fanControlCluster, ["CLIENT","SERVER", "BOTH"])
fanControlClusterCS.setLabel("Supported Implementation")
fanControlClusterCS.setDefaultValue("BOTH")
#fanControlClusterCS.setVisible(False)
fanControlClusterCS.setDescription("fanControl Cluster Supported Implementation- Select the option")
fanControlClusterCS.setDependencies(fanControlClusterCsCheck,["FANCONTROL_CLUSTER_ENABLE"])

fanControlClusterClientMenu = drvZigbeeComponent.createMenuSymbol("FANCONTROL_CLUSTER_CLIENT_MENU", fanControlCluster)
fanControlClusterClientMenu.setLabel("Client")
#fanControlClusterClientMenu.setVisible(False)
fanControlClusterClientMenu.setDescription("FANCONTROL CLUSTER CLIENT")
fanControlClusterClientMenu.setDependencies(fanControlClusterClientCheck,["FANCONTROL_CLUSTER_CS","FANCONTROL_CLUSTER_ENABLE"])

fanControlClusterServerMenu = drvZigbeeComponent.createMenuSymbol("FANCONTROL_CLUSTER_SERVER_MENU", fanControlCluster)
fanControlClusterServerMenu.setLabel("Server")
#fanControlClusterServerMenu.setVisible(False)
fanControlClusterServerMenu.setDescription("FANCONTROL CLUSTER SERVER")
fanControlClusterServerMenu.setDependencies(fanControlClusterServerCheck,["FANCONTROL_CLUSTER_CS","FANCONTROL_CLUSTER_ENABLE"])

fanControlClusterClientAttributes = drvZigbeeComponent.createMenuSymbol("FANCONTROL_CLUSTER_CLIENT__ATTRIBUTES_MENU", fanControlClusterClientMenu)
fanControlClusterClientAttributes.setLabel("Attributes")
#fanControlClusterClientAttributes.setVisible(False)
fanControlClusterClientAttributes.setDescription("FANCONTROL CLUSTER CLIENT ATTRIBUTES")
fanControlClusterClientAttributes.setDependencies(fanControlClusterClientCheck,["FANCONTROL_CLUSTER_CS"])

# fanControlClusterClientCommands = drvZigbeeComponent.createMenuSymbol("FANCONTROL_CLUSTER_CLIENT__COMMANDS_MENU", fanControlClusterClientMenu)
# fanControlClusterClientCommands.setLabel("Commands")
# #fanControlClusterClientCommands.setVisible(False)
# fanControlClusterClientCommands.setDescription("FANCONTROL CLUSTER CLIENT COMMANDS")
# fanControlClusterClientCommands.setDependencies(fanControlClusterClientCheck,["FANCONTROL_CLUSTER_CS"])

fanControlClusterServerAttributes = drvZigbeeComponent.createMenuSymbol("FANCONTROL_CLUSTER_SERVER__ATTRIBUTES_MENU", fanControlClusterServerMenu)
fanControlClusterServerAttributes.setLabel("Attributes")
#fanControlClusterServerAttributes.setVisible(False)
fanControlClusterServerAttributes.setDescription("FANCONTROL CLUSTER SERVER ATTRIBUTES")
fanControlClusterServerAttributes.setDependencies(fanControlClusterServerCheck,["FANCONTROL_CLUSTER_CS"])

# fanControlClusterServerCommands = drvZigbeeComponent.createMenuSymbol("FANCONTROL_CLUSTER_SERVER__COMMANDS_MENU", fanControlClusterServerMenu)
# fanControlClusterServerCommands.setLabel("Commands")
# #fanControlClusterServerCommands.setVisible(False)
# fanControlClusterServerCommands.setDescription("FANCONTROL CLUSTER SERVER COMMANDS")
# fanControlClusterServerCommands.setDependencies(fanControlClusterServerCheck,["FANCONTROL_CLUSTER_CS"])

#################               Server Attributes                                 ###############

global fanControlClusterServerAttributeFanMode
fanControlClusterServerAttributeFanMode = drvZigbeeComponent.createBooleanSymbol("FC_FANMODE", fanControlClusterServerAttributes)
fanControlClusterServerAttributeFanMode.setLabel("0x0000 FanMode")
fanControlClusterServerAttributeFanMode.setDefaultValue(True)
fanControlClusterServerAttributeFanMode.setDescription("FanMode - check the box to enable")
fanControlClusterServerAttributeFanMode.setReadOnly(True)

global fanControlClusterServerAttributeFanModeSequence
fanControlClusterServerAttributeFanModeSequence = drvZigbeeComponent.createBooleanSymbol("FC_FANMODESEQUENCE", fanControlClusterServerAttributes)
fanControlClusterServerAttributeFanModeSequence.setLabel("0x0001 FanModeSequence")
fanControlClusterServerAttributeFanModeSequence.setDefaultValue(True)
fanControlClusterServerAttributeFanModeSequence.setDescription("FanModeSequence - check the box to enable")
fanControlClusterServerAttributeFanModeSequence.setReadOnly(True)

global fanControlClusterServerAttributeClusterRevision
fanControlClusterServerAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("FC_CLUSTERREVISION", fanControlClusterServerAttributes)
fanControlClusterServerAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
fanControlClusterServerAttributeClusterRevision.setDefaultValue(True)
fanControlClusterServerAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
fanControlClusterServerAttributeClusterRevision.setReadOnly(True)

global fanControlClusterServerAttributeCount
fanControlClusterServerAttributeCount = drvZigbeeComponent.createIntegerSymbol("FCC_SERVERATTRIBUTECOUNT", fanControlClusterServerAttributes)
fanControlClusterServerAttributeCount.setLabel("Attributes Count")
fanControlClusterServerAttributeCount.setDefaultValue(fanControlClusterServerAttributeCountUpdate(0,0))
fanControlClusterServerAttributeCount.setVisible(True)
fanControlClusterServerAttributeCount.setDescription("Attributes Count")
fanControlClusterServerAttributeCount.setReadOnly(True)
fanControlClusterServerAttributeCount.setDependencies(fanControlClusterServerAttributeCountUpdate,["FC_FANMODE","FC_FANMODESEQUENCE","FC_CLUSTERREVISION"])


#################               Server Commands                                 ###############

# Commands received
# No cluster specific commands are received by the server.

# Commands generated
# No cluster specific commands are generated by the server.

#################               Client Attributes                                 ###############
global fanControlClusterClientAttributeClusterRevision
fanControlClusterClientAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("FCC_CLUSTERREVISION", fanControlClusterClientAttributes)
fanControlClusterClientAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
fanControlClusterClientAttributeClusterRevision.setDefaultValue(True)
fanControlClusterClientAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
fanControlClusterClientAttributeClusterRevision.setReadOnly(True)

global fanControlClusterClientAttributeCount
fanControlClusterClientAttributeCount = drvZigbeeComponent.createIntegerSymbol("FCC_CLIENTATTRIBUTECOUNT", fanControlClusterClientAttributes)
fanControlClusterClientAttributeCount.setLabel("Attributes Count")
fanControlClusterClientAttributeCount.setDefaultValue(fanControlClusterClientAttributeCountUpdate(0,0))
fanControlClusterClientAttributeCount.setVisible(True)
fanControlClusterClientAttributeCount.setDescription("Attributes Count")
fanControlClusterClientAttributeCount.setReadOnly(True)
fanControlClusterClientAttributeCount.setDependencies(fanControlClusterClientAttributeCountUpdate,["FCC_CLUSTERREVISION"])

#################               Client Commands                                 ###############

# Commands generated
# No cluster specific commands are generated by the client.

# Commands received
# No cluster specific commands are received by the client.

############################################################################################################
# Default Values Settings based on device type
fanControlClusterHandling()

############################################################################################################
##################################### FTL Files Definitions ################################################
############################################################################################################

# FANCONTROL CLUSTER Common header
fanControlClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_FANCONTROL_CLUSTER_CONF", None)
fanControlClusterConf.setSourcePath("/driver/zigbee/templates/cluster/fancontrol/zclFanControlCluster.h.ftl")
fanControlClusterConf.setOutputName("zclFanControlCluster.h")
fanControlClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
fanControlClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
fanControlClusterConf.setType("HEADER")
fanControlClusterConf.setOverwrite(True)
fanControlClusterConf.setMarkup(True)

# FANCONTROL CLUSTER - Combined Interface
fanControlClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_FANCONTROL_CLUSTER_CONF_SRC_CI", None)
fanControlClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/fancontrol/ciFanControlCluster.c.ftl")
fanControlClusterConfSrc.setOutputName("ciFanControlCluster.c")
fanControlClusterConfSrc.setDestPath("/zigbee/z3device/combinedInterface")
fanControlClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/combinedInterface/")
fanControlClusterConfSrc.setType("SOURCE")
fanControlClusterConfSrc.setOverwrite(True)
fanControlClusterConfSrc.setMarkup(True)
fanControlClusterConfSrc.setEnabled(checkDevTypeCombInterface)

# FANCONTROL CLUSTER - Thermostat
fanControlClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_FANCONTROL_CLUSTER_CONF_SRC_TH", None)
fanControlClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/fancontrol/thFanControlCluster.c.ftl")
fanControlClusterConfSrc.setOutputName("thFanControlCluster.c")
fanControlClusterConfSrc.setDestPath("/zigbee/z3device/thermostat")
fanControlClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/thermostat/")
fanControlClusterConfSrc.setType("SOURCE")
fanControlClusterConfSrc.setOverwrite(True)
fanControlClusterConfSrc.setMarkup(True)
fanControlClusterConfSrc.setEnabled(checkDevTypeThermostat)

# FANCONTROL CLUSTER - Custom
fanControlClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_FANCONTROL_CLUSTER_CONF_SRC_CUSTOM", None)
fanControlClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/fancontrol/customFanControlCluster.c.ftl")
fanControlClusterConfSrc.setOutputName("customFanControlCluster.c")
fanControlClusterConfSrc.setDestPath("/zigbee/z3device/custom")
fanControlClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/custom/")
fanControlClusterConfSrc.setType("SOURCE")
fanControlClusterConfSrc.setOverwrite(True)
fanControlClusterConfSrc.setMarkup(True)
fanControlClusterConfSrc.setEnabled(checkDevTypeCustom and fanControlCluster.getValue())
fanControlClusterConfSrc.setDependencies(customFanControlClusterEnableCheck,["FANCONTROL_CLUSTER_ENABLE"])
############################################################################################################
