############################################################################################################
###########################################  IDENTIFY CLUSTER CONFIGURATION   #################################
############################################################################################################

############################################################################################################
############################################# Function Definitions #########################################
############################################################################################################
def identifyclusterCsCheck(symbol, event):
    if (IdentifyCluster.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def identifyclusterClientCheck(symbol, event):
    if ((IdentifyCluster.getValue() == False) or IdentifyClusterCS.getValue() == "SERVER"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def identifyclusterServerCheck(symbol, event):
    if ((IdentifyCluster.getValue() == False) or IdentifyClusterCS.getValue() == "CLIENT"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def identifyClusterHandling():

    getDevice = zigbeeDeviceType.getValue()

    if ((getDevice == "ZIGBEE_COLOR_SCENE_CONTROLLER")
        or (getDevice == "ZIGBEE_COMBINED_INTERFACE")
        or (getDevice == "ZIGBEE_CONTROL_BRIDGE")
        or (getDevice == "ZIGBEE_THERMOSTAT")
        or (getDevice == "ZIGBEE_IAS_ACE")
        or (getDevice == "ZIGBEE_ON_OFF_LIGHT")
        or (getDevice == "ZIGBEE_COLOR_LIGHT")
        or (getDevice == "ZIGBEE_DIMMABLE_LIGHT")
        or (getDevice == "ZIGBEE_EXTENDED_COLOR_LIGHT")
        or (getDevice == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")
        or (getDevice == "ZIGBEE_MULTI_SENSOR")
        ):
        IdentifyCluster.setVisible(True)
        IdentifyCluster.setValue(True)
        IdentifyCluster.setReadOnly(True)
        IdentifyClusterCS.setValue("BOTH")
        IdentifyClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_CUSTOM")):
        IdentifyCluster.setVisible(True)
        IdentifyCluster.setValue(True)
        IdentifyCluster.setReadOnly(True)
        IdentifyClusterCS.setValue("BOTH")
        IdentifyClusterCS.setReadOnly(True)
    else:
        IdentifyCluster.setVisible(False)

def IdentifyClusterServerAttributeCountUpdate(symbol, event):
    count = 0
    if (IdentifyClusterServerAttributeIdentifyTime.getValue()):
        count += 1
    if (IdentifyClusterServerAttributeClusterRevision.getValue()):
        count += 1
    IdentifyClusterServerAttributeCount.setValue(count) 
    return count

def IdentifyClusterServerCommandCountUpdate(symbol, event):
    count = 0
    if (IdentifyClusterServerCommandsIdentify.getValue()):
        count += 1
    if (IdentifyClusterServerCommandsIdentifyQuery.getValue()):
        count += 1
    if (IdentifyClusterServerCommandsTriggerEffect.getValue()):
        count += 1
    if (IdentifyClusterServerCommandsIdentifyQueryresp.getValue()):
        count += 1
    IdentifyClusterServerCommandCount.setValue(count)
    return count

def IdentifyClusterClientAttributeCountUpdate(symbol, event):
    count = 0
    if (IdentifyClusterClientAttributeClusterRevision.getValue()):
        count += 1
    IdentifyClusterClientAttributeCount.setValue(count)
    return count

def IdentifyClusterClientCommandCountUpdate(symbol, event):
    count = 0
    if (IdentifyClusterClientCommandsIdentifyQueryresp.getValue()):
        count += 1
    if (IdentifyClusterClientCommandsIdentify.getValue()):
        count += 1
    if (IdentifyClusterClientCommandsIdentifyQuery.getValue()):
        count += 1
    if (IdentifyClusterClientCommandsTriggerEffect.getValue()):
        count += 1
    IdentifyClusterClientCommandCount.setValue(count)
    return count
############################################################################################################
##################################### Configuration Item Definitions #######################################
############################################################################################################

global IdentifyCluster
IdentifyCluster = drvZigbeeComponent.createBooleanSymbol("IDENTIFY_CLUSTER_ENABLE", clusterConfigMenu)
IdentifyCluster.setLabel("0x0003 Identify Cluster")
IdentifyCluster.setDefaultValue(False)
IdentifyCluster.setVisible(False)
IdentifyCluster.setDescription("IDENTIFY CLUSTER- check the box to enable")
IdentifyCluster.setReadOnly(False)

global IdentifyClusterCS
IdentifyClusterCS = drvZigbeeComponent.createComboSymbol("IDENTIFY_CLUSTER_CS",  IdentifyCluster, ["CLIENT","SERVER", "BOTH"])
IdentifyClusterCS.setLabel("Supported Implementation")
IdentifyClusterCS.setDefaultValue("BOTH")
#IdentifyClusterCS.setVisible(False)
IdentifyClusterCS.setDescription("IDENTIFY CLUSTER Supported Implementation- - Select the option")
IdentifyClusterCS.setDependencies(identifyclusterCsCheck,["IDENTIFY_CLUSTER_ENABLE"])

IdentifyClusterClientMenu = drvZigbeeComponent.createMenuSymbol("IDENTIFY_CLUSTER_CLIENT_MENU", IdentifyCluster)
IdentifyClusterClientMenu.setLabel("Client")
#IdentifyClusterClientMenu.setVisible(False)
IdentifyClusterClientMenu.setDescription("IDENTIFY CLUSTER CLIENT")
IdentifyClusterClientMenu.setDependencies(identifyclusterClientCheck,["IDENTIFY_CLUSTER_CS","IDENTIFY_CLUSTER_ENABLE"])

IdentifyClusterServerMenu = drvZigbeeComponent.createMenuSymbol("IDENTIFY_CLUSTER_SERVER_MENU", IdentifyCluster)
IdentifyClusterServerMenu.setLabel("Server")
#IdentifyClusterServerMenu.setVisible(False)
IdentifyClusterServerMenu.setDescription("IDENTIFY CLUSTER SERVER")
IdentifyClusterServerMenu.setDependencies(identifyclusterServerCheck,["IDENTIFY_CLUSTER_CS","IDENTIFY_CLUSTER_ENABLE"])

IdentifyClusterClientAttributes = drvZigbeeComponent.createMenuSymbol("IDENTIFY_CLUSTER_CLIENT__ATTRIBUTES_MENU", IdentifyClusterClientMenu)
IdentifyClusterClientAttributes.setLabel("Attributes")
#IdentifyClusterClientAttributes.setVisible(False)
IdentifyClusterClientAttributes.setDescription("IDENTIFY CLUSTER CLIENT ATTRIBUTES")
IdentifyClusterClientAttributes.setDependencies(identifyclusterClientCheck,["IDENTIFY_CLUSTER_CS"])

IdentifyClusterClientCommands = drvZigbeeComponent.createMenuSymbol("IDENTIFY_CLUSTER_CLIENT__COMMANDS_MENU", IdentifyClusterClientMenu)
IdentifyClusterClientCommands.setLabel("Commands")
#IdentifyClusterClientCommands.setVisible(False)
IdentifyClusterClientCommands.setDescription("IDENTIFY CLUSTER CLIENT COMMANDS")
IdentifyClusterClientCommands.setDependencies(identifyclusterClientCheck,["IDENTIFY_CLUSTER_CS"])

IdentifyClusterServerAttributes = drvZigbeeComponent.createMenuSymbol("IDENTIFY_CLUSTER_SERVER__ATTRIBUTES_MENU", IdentifyClusterServerMenu)
IdentifyClusterServerAttributes.setLabel("Attributes")
#IdentifyClusterServerAttributes.setVisible(False)
IdentifyClusterServerAttributes.setDescription("IDENTIFY CLUSTER SERVER ATTRIBUTES")
IdentifyClusterServerAttributes.setDependencies(identifyclusterServerCheck,["IDENTIFY_CLUSTER_CS"])

IdentifyClusterServerCommands = drvZigbeeComponent.createMenuSymbol("IDENTIFY_CLUSTER_SERVER__COMMANDS_MENU", IdentifyClusterServerMenu)
IdentifyClusterServerCommands.setLabel("Commands")
#IdentifyClusterServerCommands.setVisible(False)
IdentifyClusterServerCommands.setDescription("IDENTIFY CLUSTER SERVER COMMANDS")
IdentifyClusterServerCommands.setDependencies(identifyclusterServerCheck,["IDENTIFY_CLUSTER_CS"])

#################               Server Attributes                                 ###############

global IdentifyClusterServerAttributeIdentifyTime
IdentifyClusterServerAttributeIdentifyTime = drvZigbeeComponent.createBooleanSymbol("IC_IDENTIFYTIME", IdentifyClusterServerAttributes)
IdentifyClusterServerAttributeIdentifyTime.setLabel("0x0000 IdentifyTime")
IdentifyClusterServerAttributeIdentifyTime.setDefaultValue(True)
IdentifyClusterServerAttributeIdentifyTime.setReadOnly(True)

global IdentifyClusterServerAttributeClusterRevision
IdentifyClusterServerAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("ICS_CLUSTERREVISION", IdentifyClusterServerAttributes)
IdentifyClusterServerAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
IdentifyClusterServerAttributeClusterRevision.setDefaultValue(True)
IdentifyClusterServerAttributeClusterRevision.setReadOnly(True)

global IdentifyClusterServerAttributeCount
IdentifyClusterServerAttributeCount = drvZigbeeComponent.createIntegerSymbol("IC_SERVERATTRIBUTECOUNT", IdentifyClusterServerAttributes)
IdentifyClusterServerAttributeCount.setLabel("Attributes Count")
IdentifyClusterServerAttributeCount.setDefaultValue(IdentifyClusterServerAttributeCountUpdate(0,0))
IdentifyClusterServerAttributeCount.setVisible(True)
IdentifyClusterServerAttributeCount.setDescription("Attributes Count")
IdentifyClusterServerAttributeCount.setReadOnly(True)
IdentifyClusterServerAttributeCount.setDependencies(IdentifyClusterServerAttributeCountUpdate,["IC_IDENTIFYTIME","ICS_CLUSTERREVISION"])

#################               Server Commands                                 ###############

global IdentifyClusterServerCommandsIdentify
IdentifyClusterServerCommandsIdentify = drvZigbeeComponent.createBooleanSymbol("IC_IDENTIFYCMD", IdentifyClusterServerCommands)
IdentifyClusterServerCommandsIdentify.setLabel("0x00.Rx Identify")
IdentifyClusterServerCommandsIdentify.setDefaultValue(True)
IdentifyClusterServerCommandsIdentify.setDescription("Receive Identify command - check the box to enable")
IdentifyClusterServerCommandsIdentify.setReadOnly(True)

global IdentifyClusterServerCommandsIdentifyQuery
IdentifyClusterServerCommandsIdentifyQuery = drvZigbeeComponent.createBooleanSymbol("IC_IDENTIFYQUERYCMD", IdentifyClusterServerCommands)
IdentifyClusterServerCommandsIdentifyQuery.setLabel("0x01.Rx Identify query")
IdentifyClusterServerCommandsIdentifyQuery.setDefaultValue(True)
IdentifyClusterServerCommandsIdentifyQuery.setDescription("Receive Identify Query command - check the box to enable")
IdentifyClusterServerCommandsIdentifyQuery.setReadOnly(True)

global IdentifyClusterServerCommandsTriggerEffect
IdentifyClusterServerCommandsTriggerEffect = drvZigbeeComponent.createBooleanSymbol("IC_TRIGGEREFFECT", IdentifyClusterServerCommands)
IdentifyClusterServerCommandsTriggerEffect.setLabel("0x40.Rx Trigger effect")
IdentifyClusterServerCommandsTriggerEffect.setDefaultValue(True)
IdentifyClusterServerCommandsTriggerEffect.setDescription("Receive Trigger Effec - check the box to enable")

global IdentifyClusterServerCommandsIdentifyQueryresp
IdentifyClusterServerCommandsIdentifyQueryresp = drvZigbeeComponent.createBooleanSymbol("IC_IDENTIFYQUERYRESCMD", IdentifyClusterServerCommands)
IdentifyClusterServerCommandsIdentifyQueryresp.setLabel("0x00.Tx Identify query response")
IdentifyClusterServerCommandsIdentifyQueryresp.setDefaultValue(True)
IdentifyClusterServerCommandsIdentifyQueryresp.setDescription("sends Identify Query response command - check the box to enable")
IdentifyClusterServerCommandsIdentifyQueryresp.setReadOnly(True)
IdentifyClusterServerCommandsIdentifyQuery.setReadOnly(True)

global IdentifyClusterServerCommandCount
IdentifyClusterServerCommandCount = drvZigbeeComponent.createIntegerSymbol("IC_SERVERCOMMANDCOUNT", IdentifyClusterServerCommands)
IdentifyClusterServerCommandCount.setLabel("Commands Count")
IdentifyClusterServerCommandCount.setDefaultValue(IdentifyClusterServerCommandCountUpdate(0,0))
IdentifyClusterServerCommandCount.setVisible(True)
IdentifyClusterServerCommandCount.setDescription("Commands Count")
IdentifyClusterServerCommandCount.setReadOnly(True)
IdentifyClusterServerCommandCount.setDependencies(IdentifyClusterServerCommandCountUpdate, ["IC_IDENTIFYCMD", "IC_IDENTIFYQUERYCMD", "IC_TRIGGEREFFECT", "IC_IDENTIFYQUERYRESCMD"])

#################               Client Attributes                                 ###############
global IdentifyClusterClientAttributeClusterRevision
IdentifyClusterClientAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("ICC_CLUSTERREVISION", IdentifyClusterClientAttributes)
IdentifyClusterClientAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
IdentifyClusterClientAttributeClusterRevision.setDefaultValue(True)
IdentifyClusterClientAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
IdentifyClusterClientAttributeClusterRevision.setReadOnly(True)

global IdentifyClusterClientAttributeCount
IdentifyClusterClientAttributeCount = drvZigbeeComponent.createIntegerSymbol("ICC_CLIENTATTRIBUTECOUNT", IdentifyClusterClientAttributes)
IdentifyClusterClientAttributeCount.setLabel("Attributes Count")
IdentifyClusterClientAttributeCount.setDefaultValue(IdentifyClusterClientAttributeCountUpdate(0,0))
IdentifyClusterClientAttributeCount.setVisible(True)
IdentifyClusterClientAttributeCount.setDescription("Attributes Count")
IdentifyClusterClientAttributeCount.setReadOnly(True)
IdentifyClusterClientAttributeCount.setDependencies(IdentifyClusterClientAttributeCountUpdate,["ICC_CLUSTERREVISION"])

#################               Client Commands                                 ###############

global IdentifyClusterClientCommandsIdentifyQueryresp
IdentifyClusterClientCommandsIdentifyQueryresp = drvZigbeeComponent.createBooleanSymbol("ICC_IDENTIFYQUERYRESCMD", IdentifyClusterClientCommands)
IdentifyClusterClientCommandsIdentifyQueryresp.setLabel("0x00.Rx Identify query response")
IdentifyClusterClientCommandsIdentifyQueryresp.setDefaultValue(True)
IdentifyClusterClientCommandsIdentifyQueryresp.setDescription("Receives Identify Query response command - check the box to enable")
IdentifyClusterClientCommandsIdentifyQueryresp.setReadOnly(True)

global IdentifyClusterClientCommandsIdentify
IdentifyClusterClientCommandsIdentify = drvZigbeeComponent.createBooleanSymbol("ICC_IDENTIFYCMD", IdentifyClusterClientCommands)
IdentifyClusterClientCommandsIdentify.setLabel("0x00.Tx Identify")
IdentifyClusterClientCommandsIdentify.setDefaultValue(True)
IdentifyClusterClientCommandsIdentify.setDescription("Send Identify command - check the box to enable")
IdentifyClusterClientCommandsIdentify.setReadOnly(True)# Needed for BDB Finding and Binding

global IdentifyClusterClientCommandsIdentifyQuery
IdentifyClusterClientCommandsIdentifyQuery = drvZigbeeComponent.createBooleanSymbol("ICC_IDENTIFYQUERYCMD", IdentifyClusterClientCommands)
IdentifyClusterClientCommandsIdentifyQuery.setLabel("0x01.Tx Identify query")
IdentifyClusterClientCommandsIdentifyQuery.setDefaultValue(True)
IdentifyClusterClientCommandsIdentifyQuery.setDescription("Send Identify Query command - check the box to enable")
IdentifyClusterClientCommandsIdentifyQuery.setReadOnly(True)# Needed for BDB Finding and Binding

global IdentifyClusterClientCommandsTriggerEffect
IdentifyClusterClientCommandsTriggerEffect = drvZigbeeComponent.createBooleanSymbol("ICC_TRIGGEREFFECT", IdentifyClusterClientCommands)
IdentifyClusterClientCommandsTriggerEffect.setLabel("0x40.Tx Trigger effect")
IdentifyClusterClientCommandsTriggerEffect.setDefaultValue(True)
IdentifyClusterClientCommandsTriggerEffect.setDescription("Send Trigger Effect - check the box to enable")
IdentifyClusterClientCommandsTriggerEffect.setReadOnly(True)# Needed for BDB Finding and Binding

global IdentifyClusterClientCommandCount
IdentifyClusterClientCommandCount = drvZigbeeComponent.createIntegerSymbol("ICC_CLIENTCOMMANDCOUNT", IdentifyClusterClientCommands)
IdentifyClusterClientCommandCount.setLabel("Commands Count")
IdentifyClusterClientCommandCount.setDefaultValue(IdentifyClusterClientCommandCountUpdate(0,0))
IdentifyClusterClientCommandCount.setVisible(True)
IdentifyClusterClientCommandCount.setDescription("Commands Count")
IdentifyClusterClientCommandCount.setReadOnly(True)
IdentifyClusterClientCommandCount.setDependencies(IdentifyClusterClientCommandCountUpdate,["ICC_IDENTIFYQUERYRESCMD", "ICC_IDENTIFYCMD", "ICC_IDENTIFYQUERYCMD", "ICC_TRIGGEREFFECT"])

############################################################################################################
# Default Values Settings based on device type
identifyClusterHandling()

############################################################################################################
##################################### FTL Files Definitions ################################################
############################################################################################################

# IDENTIFY CLUSTER Common header
identifyClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_IDENTIFY_CLUSTER_CONF", None)
identifyClusterConf.setSourcePath("/driver/zigbee/templates/cluster/identify/zclIdentifyCluster.h.ftl")
identifyClusterConf.setOutputName("zclIdentifyCluster.h")
identifyClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
identifyClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
identifyClusterConf.setType("HEADER")
identifyClusterConf.setOverwrite(True)
identifyClusterConf.setMarkup(True)

identifyClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_IDENTIFY_CLUSTER_CONF2", None)
identifyClusterConf.setSourcePath("/driver/zigbee/templates/cluster/identify/zclZllIdentifyCluster.h.ftl")
identifyClusterConf.setOutputName("zclZllIdentifyCluster.h")
identifyClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
identifyClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
identifyClusterConf.setType("HEADER")
identifyClusterConf.setOverwrite(True)
identifyClusterConf.setMarkup(True)

identifyClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_IDENTIFY_CLUSTER_CONF_SRC1", None)
identifyClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/identify/identifyCluster.c.ftl")
identifyClusterConfSrc.setOutputName("identifyCluster.c")
identifyClusterConfSrc.setDestPath("/zigbee/z3device/clusters")
identifyClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/clusters/")
identifyClusterConfSrc.setType("SOURCE")
identifyClusterConfSrc.setOverwrite(True)
identifyClusterConfSrc.setMarkup(True)

# IDENTIFY CLUSTER - Light
identifyClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_IDENTIFY_CLUSTER_CONF_SRC_LIGHT", None)
identifyClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/identify/lightIdentifyCluster.c.ftl")
identifyClusterConfSrc.setOutputName("lightIdentifyCluster.c")
identifyClusterConfSrc.setDestPath("/zigbee/z3device/light")
identifyClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/light/")
identifyClusterConfSrc.setType("SOURCE")
identifyClusterConfSrc.setOverwrite(True)
identifyClusterConfSrc.setMarkup(True)
identifyClusterConfSrc.setEnabled(checkDevTypeLight)

# IDENTIFY CLUSTER - Custom
identifyClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_IDENTIFY_CLUSTER_CONF_SRC_CUSTOM", None)
identifyClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/identify/customIdentifyCluster.c.ftl")
identifyClusterConfSrc.setOutputName("customIdentifyCluster.c")
identifyClusterConfSrc.setDestPath("/zigbee/z3device/custom")
identifyClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/custom/")
identifyClusterConfSrc.setType("SOURCE")
identifyClusterConfSrc.setOverwrite(True)
identifyClusterConfSrc.setMarkup(True)
identifyClusterConfSrc.setEnabled(checkDevTypeCustom and IdentifyCluster.getValue())

# IDENTIFY CLUSTER - Color Scene Controller
identifyClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_IDENTIFY_CLUSTER_CONF_SRC_CSC", None)
identifyClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/identify/cscIdentifyCluster.c.ftl")
identifyClusterConfSrc.setOutputName("cscIdentifyCluster.c")
identifyClusterConfSrc.setDestPath("/zigbee/z3device/colorSceneController")
identifyClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/colorSceneController/")
identifyClusterConfSrc.setType("SOURCE")
identifyClusterConfSrc.setOverwrite(True)
identifyClusterConfSrc.setMarkup(True)
identifyClusterConfSrc.setEnabled(checkDevTypeRemote)

# IDENTIFY CLUSTER - Combined Interface
identifyClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_IDENTIFY_CLUSTER_CONF_SRC_CI", None)
identifyClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/identify/ciIdentifyCluster.c.ftl")
identifyClusterConfSrc.setOutputName("ciIdentifyCluster.c")
identifyClusterConfSrc.setDestPath("/zigbee/z3device/combinedInterface")
identifyClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/combinedInterface/")
identifyClusterConfSrc.setType("SOURCE")
identifyClusterConfSrc.setOverwrite(True)
identifyClusterConfSrc.setMarkup(True)
identifyClusterConfSrc.setEnabled(checkDevTypeCombInterface)

# IDENTIFY CLUSTER - IAS ACE
identifyClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_IDENTIFY_CLUSTER_CONF_SRC_IAS", None)
identifyClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/identify/iasACEIdentifyCluster.c.ftl")
identifyClusterConfSrc.setOutputName("iasACEIdentifyCluster.c")
identifyClusterConfSrc.setDestPath("/zigbee/z3device/ias_ace")
identifyClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/ias_ace/")
identifyClusterConfSrc.setType("SOURCE")
identifyClusterConfSrc.setOverwrite(True)
identifyClusterConfSrc.setMarkup(True)
identifyClusterConfSrc.setEnabled(checkDevTypeIasAce)

# IDENTIFY CLUSTER - Multi Sensor
# IDENTIFY CLUSTER - Humidity Sensor
identifyClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_IDENTIFY_CLUSTER_CONF_SRC_HS", None)
identifyClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/identify/hsIdentifyCluster.c.ftl")
identifyClusterConfSrc.setOutputName("hsIdentifyCluster.c")
identifyClusterConfSrc.setDestPath("/zigbee/z3device/multiSensor")
identifyClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/multiSensor/")
identifyClusterConfSrc.setType("SOURCE")
identifyClusterConfSrc.setOverwrite(True)
identifyClusterConfSrc.setMarkup(True)
identifyClusterConfSrc.setEnabled(checkDevTypeMultiSensor)

# IDENTIFY CLUSTER - Occupancy Sensor
identifyClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_IDENTIFY_CLUSTER_CONF_SRC_OS", None)
identifyClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/identify/osIdentifyCluster.c.ftl")
identifyClusterConfSrc.setOutputName("osIdentifyCluster.c")
identifyClusterConfSrc.setDestPath("/zigbee/z3device/multiSensor")
identifyClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/multiSensor/")
identifyClusterConfSrc.setType("SOURCE")
identifyClusterConfSrc.setOverwrite(True)
identifyClusterConfSrc.setMarkup(True)
identifyClusterConfSrc.setEnabled(checkDevTypeMultiSensor)

# IDENTIFY CLUSTER - Temperature Sensor
identifyClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_IDENTIFY_CLUSTER_CONF_SRC_TS", None)
identifyClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/identify/tsIdentifyCluster.c.ftl")
identifyClusterConfSrc.setOutputName("tsIdentifyCluster.c")
identifyClusterConfSrc.setDestPath("/zigbee/z3device/multiSensor")
identifyClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/multiSensor/")
identifyClusterConfSrc.setType("SOURCE")
identifyClusterConfSrc.setOverwrite(True)
identifyClusterConfSrc.setMarkup(True)
identifyClusterConfSrc.setEnabled(checkDevTypeMultiSensor)

# IDENTIFY CLUSTER - Thermostat
identifyClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_IDENTIFY_CLUSTER_CONF_SRC_TH", None)
identifyClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/identify/thIdentifyCluster.c.ftl")
identifyClusterConfSrc.setOutputName("thIdentifyCluster.c")
identifyClusterConfSrc.setDestPath("/zigbee/z3device/thermostat")
identifyClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/thermostat/")
identifyClusterConfSrc.setType("SOURCE")
identifyClusterConfSrc.setOverwrite(True)
identifyClusterConfSrc.setMarkup(True)
identifyClusterConfSrc.setEnabled(checkDevTypeThermostat)

############################################################################################################
