############################################################################################################
###########################################  IAS ACE CLUSTER CONFIGURATION   ##############################
############################################################################################################

############################################################################################################
############################################# Function Definitions #########################################
############################################################################################################
def iasACEClusterCsCheck(symbol, event):
    if (iasACECluster.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def iasACEClusterEnableCheck(symbol, event):
    if (iasACECluster.getValue() == False):
        symbol.setEnabled(False)
    else:
        symbol.setEnabled(True)

def customIasACEClusterEnableCheck(symbol, event):
    if ((zigbeeDeviceType.getValue() == 'ZIGBEE_CUSTOM') and (iasACECluster.getValue() == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def iasACEClusterClientCheck(symbol, event):
    if ((iasACECluster.getValue() == False) or iasACEClusterCS.getValue() == "SERVER"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def iasACEClusterServerCheck(symbol, event):
    if ((iasACECluster.getValue() == False) or iasACEClusterCS.getValue() == "CLIENT"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def iasACEClusterHandling():

    getDevice = zigbeeDeviceType.getValue()

    if ((getDevice == "ZIGBEE_COLOR_SCENE_CONTROLLER")
        or (getDevice == "ZIGBEE_MULTI_SENSOR")
        or (getDevice == "ZIGBEE_CONTROL_BRIDGE")
        or (getDevice == "ZIGBEE_THERMOSTAT")
        or (getDevice == "ZIGBEE_ON_OFF_LIGHT")
        or (getDevice == "ZIGBEE_DIMMABLE_LIGHT")
        or (getDevice == "ZIGBEE_COLOR_LIGHT")
        or (getDevice == "ZIGBEE_EXTENDED_COLOR_LIGHT")
        or (getDevice == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")
        ):
        iasACECluster.setVisible(False)
        iasACECluster.setValue(False)
    elif ((getDevice == "ZIGBEE_COMBINED_INTERFACE")):
        iasACECluster.setVisible(True)
        iasACECluster.setValue(True)
        iasACECluster.setReadOnly(True)
        iasACEClusterCS.setValue("SERVER")
        iasACEClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_IAS_ACE")):
        iasACECluster.setVisible(True)
        iasACECluster.setValue(True)
        iasACECluster.setReadOnly(True)
        iasACEClusterCS.setValue("CLIENT")
        iasACEClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_CUSTOM")):
        iasACECluster.setVisible(True)
        iasACECluster.setValue(False)
        iasACEClusterCS.setValue("BOTH")
    else:
        iasACECluster.setVisible(False)

def iasACEClusterServerAttributeCountUpdate(symbol, event):
    count = 0
    if (iasACEClusterServerAttributeClusterRevision.getValue()):
        count += 1
    iasACEClusterServerAttributeCount.setValue(count) 
    return count

def iasACEClusterServerCommandCountUpdate(symbol, event):
    count = 0
    if (iasACEClusterServerArm.getValue()):
        count += 1
    if (iasACEClusterServerBypass.getValue()):
        count += 1
    if (iasACEClusterServerEmergency.getValue()):
        count += 1
    if (iasACEClusterServerFire.getValue()):
        count += 1
    if (iasACEClusterServerPanic.getValue()):
        count += 1
    if (iasACEClusterServerGetZoneIDMap.getValue()):
        count += 1
    if (iasACEClusterServerGetZoneInfo.getValue()):
        count += 1
    if (iasACEClusterServerGetPanelStatus.getValue()):
        count += 1
    if (iasACEClusterServerGetBypassedZoneList.getValue()):
        count += 1
    if (iasACEClusterServerGetZoneStatus.getValue()):
        count += 1
    if (iasACEClusterServerArmResp.getValue()):
        count += 1
    if (iasACEClusterServerGetZoneIdMapResp.getValue()):
        count += 1
    if (iasACEClusterServerGetZoneInfoResp.getValue()):
        count += 1
    if (iasACEClusterServerZoneStatusChanged.getValue()):
        count += 1
    if (iasACEClusterServerPanelStatusChanged.getValue()):
        count += 1
    if (iasACEClusterServerGetPanelStatusResponse.getValue()):
        count += 1
    if (iasACEClusterServerSetBypassedZoneList.getValue()):
        count += 1
    if (iasACEClusterServerBypassResponse.getValue()):
        count += 1
    if (iasACEClusterServerGetZoneStatusResp.getValue()):
        count += 1		
    iasACEClusterServerCommandCount.setValue(count)
    return count

def iasACEClusterClientAttributeCountUpdate(symbol, event):
    count = 0
    if (iasACEClusterClientAttributeClusterRevision.getValue()):
        count += 1
    iasACEClusterClientAttributeCount.setValue(count)
    return count

def iasACEClusterClientCommandCountUpdate(symbol, event):
    count = 0
    if (iasACEClusterClientArm.getValue()):
        count += 1
    if (iasACEClusterClientBypass.getValue()):
        count += 1
    if (iasACEClusterClientEmergency.getValue()):
        count += 1
    if (iasACEClusterClientFire.getValue()):
        count += 1
    if (iasACEClusterClientPanic.getValue()):
        count += 1
    if (iasACEClusterClientGetZoneIDMap.getValue()):
        count += 1
    if (iasACEClusterClientGetZoneInfo.getValue()):
        count += 1
    if (iasACEClusterClientGetPanelStatus.getValue()):
        count += 1
    if (iasACEClusterClientGetBypassedZoneList.getValue()):
        count += 1
    if (iasACEClusterClientGetZoneStatus.getValue()):
        count += 1
    if (iasACEClusterClientArmResp.getValue()):
        count += 1
    if (iasACEClusterClientGetZoneIdMapResp.getValue()):
        count += 1
    if (iasACEClusterClientGetZoneInfoResp.getValue()):
        count += 1
    if (iasACEClusterClientZoneStatusChanged.getValue()):
        count += 1
    if (iasACEClusterClientPanelStatusChanged.getValue()):
        count += 1
    if (iasACEClusterClientGetPanelStatusResponse.getValue()):
        count += 1
    if (iasACEClusterClientSetBypassedZoneList.getValue()):
        count += 1
    if (iasACEClusterClientBypassResponse.getValue()):
        count += 1
    if (iasACEClusterClientGetZoneStatusResp.getValue()):
        count += 1	
    iasACEClusterClientCommandCount.setValue(count)
    return count
############################################################################################################
##################################### Configuration Item Definitions #######################################
############################################################################################################

global iasACECluster
iasACECluster = drvZigbeeComponent.createBooleanSymbol("IASACE_CLUSTER_ENABLE", clusterConfigMenu)
iasACECluster.setLabel("0x0501 IAS ACE Cluster")
iasACECluster.setDefaultValue(False)
iasACECluster.setVisible(False)
iasACECluster.setDescription("IAS ACE CLUSTER- check the box to enable")
iasACECluster.setReadOnly(False)

global iasACEClusterCS
iasACEClusterCS = drvZigbeeComponent.createComboSymbol("IASACE_CLUSTER_CS",  iasACECluster, ["CLIENT","SERVER", "BOTH"])
iasACEClusterCS.setLabel("Supported Implementation")
iasACEClusterCS.setDefaultValue("BOTH")
#iasACEClusterCS.setVisible(False)
iasACEClusterCS.setDescription("IAS ACE Cluster Supported Implementation- Select the option")
iasACEClusterCS.setDependencies(iasACEClusterCsCheck,["IASACE_CLUSTER_ENABLE"])

iasACEClusterClientMenu = drvZigbeeComponent.createMenuSymbol("IASACE_CLUSTER_CLIENT_MENU", iasACECluster)
iasACEClusterClientMenu.setLabel("Client")
#iasACEClusterClientMenu.setVisible(False)
iasACEClusterClientMenu.setDescription("IAS ACE CLUSTER CLIENT")
iasACEClusterClientMenu.setDependencies(iasACEClusterClientCheck,["IASACE_CLUSTER_CS","IASACE_CLUSTER_ENABLE"])

iasACEClusterServerMenu = drvZigbeeComponent.createMenuSymbol("IASACE_CLUSTER_SERVER_MENU", iasACECluster)
iasACEClusterServerMenu.setLabel("Server")
#iasACEClusterServerMenu.setVisible(False)
iasACEClusterServerMenu.setDescription("IAS ACE CLUSTER SERVER")
iasACEClusterServerMenu.setDependencies(iasACEClusterServerCheck,["IASACE_CLUSTER_CS","IASACE_CLUSTER_ENABLE"])

iasACEClusterClientAttributes = drvZigbeeComponent.createMenuSymbol("IASACE_CLUSTER_CLIENT__ATTRIBUTES_MENU", iasACEClusterClientMenu)
iasACEClusterClientAttributes.setLabel("Attributes")
#iasACEClusterClientAttributes.setVisible(False)
iasACEClusterClientAttributes.setDescription("IAS ACE CLUSTER CLIENT ATTRIBUTES")
iasACEClusterClientAttributes.setDependencies(iasACEClusterClientCheck,["IASACE_CLUSTER_CS"])

iasACEClusterClientCommands = drvZigbeeComponent.createMenuSymbol("IASACE_CLUSTER_CLIENT__COMMANDS_MENU", iasACEClusterClientMenu)
iasACEClusterClientCommands.setLabel("Commands")
#iasACEClusterClientCommands.setVisible(False)
iasACEClusterClientCommands.setDescription("IAS ACE CLUSTER CLIENT COMMANDS")
iasACEClusterClientCommands.setDependencies(iasACEClusterClientCheck,["IASACE_CLUSTER_CS"])

iasACEClusterServerAttributes = drvZigbeeComponent.createMenuSymbol("IASACE_CLUSTER_SERVER__ATTRIBUTES_MENU", iasACEClusterServerMenu)
iasACEClusterServerAttributes.setLabel("Attributes")
#iasACEClusterServerAttributes.setVisible(False)
iasACEClusterServerAttributes.setDescription("IAS ACE CLUSTER SERVER ATTRIBUTES")
iasACEClusterServerAttributes.setDependencies(iasACEClusterServerCheck,["IASACE_CLUSTER_CS"])

iasACEClusterServerCommands = drvZigbeeComponent.createMenuSymbol("IASACE_CLUSTER_SERVER__COMMANDS_MENU", iasACEClusterServerMenu)
iasACEClusterServerCommands.setLabel("Commands")
#iasACEClusterServerCommands.setVisible(False)
iasACEClusterServerCommands.setDescription("IAS ACE CLUSTER SERVER COMMANDS")
iasACEClusterServerCommands.setDependencies(iasACEClusterServerCheck,["IASACE_CLUSTER_CS"])

#################               Server Attributes                                 ###############

# Global Attributes
global iasACEClusterServerAttributeClusterRevision
iasACEClusterServerAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("IAC_CLUSTERREVISION", iasACEClusterServerAttributes)
iasACEClusterServerAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
iasACEClusterServerAttributeClusterRevision.setDefaultValue(True)
iasACEClusterServerAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
iasACEClusterServerAttributeClusterRevision.setReadOnly(True)

global iasACEClusterServerAttributeCount
iasACEClusterServerAttributeCount = drvZigbeeComponent.createIntegerSymbol("IAC_SERVERATTRIBUTECOUNT", iasACEClusterServerAttributes)
iasACEClusterServerAttributeCount.setLabel("Attributes Count")
iasACEClusterServerAttributeCount.setDefaultValue(iasACEClusterServerAttributeCountUpdate(0,0))
iasACEClusterServerAttributeCount.setVisible(True)
iasACEClusterServerAttributeCount.setDescription("Attributes Count")
iasACEClusterServerAttributeCount.setReadOnly(True)
iasACEClusterServerAttributeCount.setDependencies(iasACEClusterServerAttributeCountUpdate,["IAC_CLUSTERREVISION"])

#################               Server Commands                                 ###############

# Commands received
global iasACEClusterServerArm
iasACEClusterServerArm = drvZigbeeComponent.createBooleanSymbol("IAC_ARM", iasACEClusterServerCommands)
iasACEClusterServerArm.setLabel("0x00.Rx Arm")
iasACEClusterServerArm.setDefaultValue(True)
iasACEClusterServerArm.setDescription("Receive Arm - check the box to enable")
iasACEClusterServerArm.setReadOnly(True)

global iasACEClusterServerBypass
iasACEClusterServerBypass = drvZigbeeComponent.createBooleanSymbol("IAC_BYPASS", iasACEClusterServerCommands)
iasACEClusterServerBypass.setLabel("0x01.Rx Bypass")
iasACEClusterServerBypass.setDefaultValue(True)
iasACEClusterServerBypass.setDescription("Receive Bypass - check the box to enable")
iasACEClusterServerBypass.setReadOnly(True)

global iasACEClusterServerEmergency
iasACEClusterServerEmergency = drvZigbeeComponent.createBooleanSymbol("IAC_EMERGENCY", iasACEClusterServerCommands)
iasACEClusterServerEmergency.setLabel("0x02.Rx Emergency")
iasACEClusterServerEmergency.setDefaultValue(True)
iasACEClusterServerEmergency.setDescription("Receive Emergency - check the box to enable")
iasACEClusterServerEmergency.setReadOnly(True)

global iasACEClusterServerFire
iasACEClusterServerFire = drvZigbeeComponent.createBooleanSymbol("IAC_FIRE", iasACEClusterServerCommands)
iasACEClusterServerFire.setLabel("0x03.Rx Fire")
iasACEClusterServerFire.setDefaultValue(True)
iasACEClusterServerFire.setDescription("Receive Fire - check the box to enable")
iasACEClusterServerFire.setReadOnly(True)

global iasACEClusterServerPanic
iasACEClusterServerPanic = drvZigbeeComponent.createBooleanSymbol("IAC_PANIC", iasACEClusterServerCommands)
iasACEClusterServerPanic.setLabel("0x04.Rx Panic")
iasACEClusterServerPanic.setDefaultValue(True)
iasACEClusterServerPanic.setDescription("Receive Panic - check the box to enable")
iasACEClusterServerPanic.setReadOnly(True)

global iasACEClusterServerGetZoneIDMap
iasACEClusterServerGetZoneIDMap = drvZigbeeComponent.createBooleanSymbol("IAC_GETZONEIDMAP", iasACEClusterServerCommands)
iasACEClusterServerGetZoneIDMap.setLabel("0x05.Rx Get Zone ID Map")
iasACEClusterServerGetZoneIDMap.setDefaultValue(True)
iasACEClusterServerGetZoneIDMap.setDescription("Receive Get Zone ID Map - check the box to enable")
iasACEClusterServerGetZoneIDMap.setReadOnly(True)

global iasACEClusterServerGetZoneInfo
iasACEClusterServerGetZoneInfo = drvZigbeeComponent.createBooleanSymbol("IAC_GETZONEINFO", iasACEClusterServerCommands)
iasACEClusterServerGetZoneInfo.setLabel("0x06.Rx Get Zone Information")
iasACEClusterServerGetZoneInfo.setDefaultValue(True)
iasACEClusterServerGetZoneInfo.setDescription("Receive Get Zone Information - check the box to enable")
iasACEClusterServerGetZoneInfo.setReadOnly(True)

global iasACEClusterServerGetPanelStatus
iasACEClusterServerGetPanelStatus = drvZigbeeComponent.createBooleanSymbol("IAC_GETPANELSTATUS", iasACEClusterServerCommands)
iasACEClusterServerGetPanelStatus.setLabel("0x07.Rx Get Panel Status")
iasACEClusterServerGetPanelStatus.setDefaultValue(True)
iasACEClusterServerGetPanelStatus.setDescription("Receive Get Panel Status - check the box to enable")
iasACEClusterServerGetPanelStatus.setReadOnly(True)

global iasACEClusterServerGetBypassedZoneList
iasACEClusterServerGetBypassedZoneList = drvZigbeeComponent.createBooleanSymbol("IAC_GETBYPASSZONELIST", iasACEClusterServerCommands)
iasACEClusterServerGetBypassedZoneList.setLabel("0x08.Rx Get Bypassed Zone List")
iasACEClusterServerGetBypassedZoneList.setDefaultValue(True)
iasACEClusterServerGetBypassedZoneList.setDescription("Receive Get Bypassed Zone List - check the box to enable")
iasACEClusterServerGetBypassedZoneList.setReadOnly(True)

global iasACEClusterServerGetZoneStatus
iasACEClusterServerGetZoneStatus = drvZigbeeComponent.createBooleanSymbol("IAC_GETZONESTATUS", iasACEClusterServerCommands)
iasACEClusterServerGetZoneStatus.setLabel("0x09.Rx Get Zone Status")
iasACEClusterServerGetZoneStatus.setDefaultValue(True)
iasACEClusterServerGetZoneStatus.setDescription("Receive Get Zone Status - check the box to enable")
iasACEClusterServerGetZoneStatus.setReadOnly(True)

# Commands generated
global iasACEClusterServerArmResp
iasACEClusterServerArmResp = drvZigbeeComponent.createBooleanSymbol("IAC_ARMRESP", iasACEClusterServerCommands)
iasACEClusterServerArmResp.setLabel("0x00.Tx Arm Response")
iasACEClusterServerArmResp.setDefaultValue(True)
iasACEClusterServerArmResp.setDescription("Send Arm Response - check the box to enable")
iasACEClusterServerArmResp.setReadOnly(True)

global iasACEClusterServerGetZoneIdMapResp
iasACEClusterServerGetZoneIdMapResp = drvZigbeeComponent.createBooleanSymbol("IAC_GETZONEIDMAPRESP", iasACEClusterServerCommands)
iasACEClusterServerGetZoneIdMapResp.setLabel("0x01.Tx Get Zone ID Map Response")
iasACEClusterServerGetZoneIdMapResp.setDefaultValue(True)
iasACEClusterServerGetZoneIdMapResp.setDescription("Send Get Zone ID Map Response - check the box to enable")
iasACEClusterServerGetZoneIdMapResp.setReadOnly(True)

global iasACEClusterServerGetZoneInfoResp
iasACEClusterServerGetZoneInfoResp = drvZigbeeComponent.createBooleanSymbol("IAC_GETZONEINFORESP", iasACEClusterServerCommands)
iasACEClusterServerGetZoneInfoResp.setLabel("0x02.Tx Get Zone Information Response")
iasACEClusterServerGetZoneInfoResp.setDefaultValue(True)
iasACEClusterServerGetZoneInfoResp.setDescription("Send Get Zone Information Response - check the box to enable")
iasACEClusterServerGetZoneInfoResp.setReadOnly(True)

global iasACEClusterServerZoneStatusChanged
iasACEClusterServerZoneStatusChanged = drvZigbeeComponent.createBooleanSymbol("IAC_ZONESTATUSCHANGED", iasACEClusterServerCommands)
iasACEClusterServerZoneStatusChanged.setLabel("0x03.Tx Zone Status Changed")
iasACEClusterServerZoneStatusChanged.setDefaultValue(True)
iasACEClusterServerZoneStatusChanged.setDescription("Send Zone Status Changed - check the box to enable")
iasACEClusterServerZoneStatusChanged.setReadOnly(True)

global iasACEClusterServerPanelStatusChanged
iasACEClusterServerPanelStatusChanged = drvZigbeeComponent.createBooleanSymbol("IAC_PANELSTATUSCHANGED", iasACEClusterServerCommands)
iasACEClusterServerPanelStatusChanged.setLabel("0x04.Tx Panel Status Changed")
iasACEClusterServerPanelStatusChanged.setDefaultValue(True)
iasACEClusterServerPanelStatusChanged.setDescription("Send Panel Status Changed - check the box to enable")
iasACEClusterServerPanelStatusChanged.setReadOnly(True)

global iasACEClusterServerGetPanelStatusResponse
iasACEClusterServerGetPanelStatusResponse = drvZigbeeComponent.createBooleanSymbol("IAC_PANELSTATUSRESP", iasACEClusterServerCommands)
iasACEClusterServerGetPanelStatusResponse.setLabel("0x05.Tx Get Panel Status Response")
iasACEClusterServerGetPanelStatusResponse.setDefaultValue(True)
iasACEClusterServerGetPanelStatusResponse.setDescription("Send Get Panel Status Response - check the box to enable")
iasACEClusterServerGetPanelStatusResponse.setReadOnly(True)

global iasACEClusterServerSetBypassedZoneList
iasACEClusterServerSetBypassedZoneList = drvZigbeeComponent.createBooleanSymbol("IAC_SETBYPASSEDZONELIST", iasACEClusterServerCommands)
iasACEClusterServerSetBypassedZoneList.setLabel("0x06.Tx Set Bypassed Zone List")
iasACEClusterServerSetBypassedZoneList.setDefaultValue(True)
iasACEClusterServerSetBypassedZoneList.setDescription("Send Set Bypassed Zone List - check the box to enable")
iasACEClusterServerSetBypassedZoneList.setReadOnly(True)

global iasACEClusterServerBypassResponse
iasACEClusterServerBypassResponse = drvZigbeeComponent.createBooleanSymbol("IAC_BYPASSRESPONSE", iasACEClusterServerCommands)
iasACEClusterServerBypassResponse.setLabel("0x07.Tx Bypass Response")
iasACEClusterServerBypassResponse.setDefaultValue(True)
iasACEClusterServerBypassResponse.setDescription("Send Bypass Response - check the box to enable")
iasACEClusterServerBypassResponse.setReadOnly(True)

global iasACEClusterServerGetZoneStatusResp
iasACEClusterServerGetZoneStatusResp = drvZigbeeComponent.createBooleanSymbol("IAC_GETZONESTATUSRESP", iasACEClusterServerCommands)
iasACEClusterServerGetZoneStatusResp.setLabel("0x08.Tx Get Zone Status Response")
iasACEClusterServerGetZoneStatusResp.setDefaultValue(True)
iasACEClusterServerGetZoneStatusResp.setDescription("Send Get Zone Status Response - check the box to enable")
iasACEClusterServerGetZoneStatusResp.setReadOnly(True)

global iasACEClusterServerCommandCount
iasACEClusterServerCommandCount = drvZigbeeComponent.createIntegerSymbol("IAC_SERVERCOMMANDCOUNT", iasACEClusterServerCommands)
iasACEClusterServerCommandCount.setLabel("Commands Count")
iasACEClusterServerCommandCount.setDefaultValue(iasACEClusterServerCommandCountUpdate(0,0))
iasACEClusterServerCommandCount.setVisible(True)
iasACEClusterServerCommandCount.setDescription("Commands Count")
iasACEClusterServerCommandCount.setReadOnly(True)
iasACEClusterServerCommandCount.setDependencies(iasACEClusterServerCommandCountUpdate,["IAC_ARM", "IAC_BYPASS", "IAC_EMERGENCY", "IAC_FIRE","IAC_PANIC", "IAC_GETZONEIDMAP", "IAC_GETZONEINFO","IAC_GETPANELSTATUS","IAC_GETBYPASSZONELIST","IAC_GETZONESTATUS","IAC_ARMRESP", "IAC_GETZONEIDMAPRESP", "IAC_GETZONEINFORESP", "IAC_ZONESTATUSCHANGED","IAC_PANELSTATUSCHANGED", "IAC_PANELSTATUSRESP", "IAC_SETBYPASSEDZONELIST","IAC_BYPASSRESPONSE","IAC_GETZONESTATUSRESP"])


#################               Client Attributes                                 ###############
global iasACEClusterClientAttributeClusterRevision
iasACEClusterClientAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("IACC_CLUSTERREVISION", iasACEClusterClientAttributes)
iasACEClusterClientAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
iasACEClusterClientAttributeClusterRevision.setDefaultValue(True)
iasACEClusterClientAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
iasACEClusterClientAttributeClusterRevision.setReadOnly(True)

global iasACEClusterClientAttributeCount
iasACEClusterClientAttributeCount = drvZigbeeComponent.createIntegerSymbol("IACC_CLIENTATTRIBUTECOUNT", iasACEClusterClientAttributes)
iasACEClusterClientAttributeCount.setLabel("Attributes Count")
iasACEClusterClientAttributeCount.setDefaultValue(iasACEClusterClientAttributeCountUpdate(0,0))
iasACEClusterClientAttributeCount.setVisible(True)
iasACEClusterClientAttributeCount.setDescription("Attributes Count")
iasACEClusterClientAttributeCount.setReadOnly(True)
iasACEClusterClientAttributeCount.setDependencies(iasACEClusterClientAttributeCountUpdate,["IACC_CLUSTERREVISION"])

#################               Client Commands                                 ###############

# Commands generated
global iasACEClusterClientArm
iasACEClusterClientArm = drvZigbeeComponent.createBooleanSymbol("IACC_ARM", iasACEClusterClientCommands)
iasACEClusterClientArm.setLabel("0x00.Tx Arm")
iasACEClusterClientArm.setDefaultValue(True)
iasACEClusterClientArm.setDescription("Send Arm - check the box to enable")

global iasACEClusterClientBypass
iasACEClusterClientBypass = drvZigbeeComponent.createBooleanSymbol("IACC_BYPASS", iasACEClusterClientCommands)
iasACEClusterClientBypass.setLabel("0x01.Tx Bypass")
iasACEClusterClientBypass.setDefaultValue(True)
iasACEClusterClientBypass.setDescription("Send Bypass - check the box to enable")

global iasACEClusterClientEmergency
iasACEClusterClientEmergency = drvZigbeeComponent.createBooleanSymbol("IACC_EMERGENCY", iasACEClusterClientCommands)
iasACEClusterClientEmergency.setLabel("0x02.Tx Emergency")
iasACEClusterClientEmergency.setDefaultValue(True)
iasACEClusterClientEmergency.setDescription("Send Emergency - check the box to enable")

global iasACEClusterClientFire
iasACEClusterClientFire = drvZigbeeComponent.createBooleanSymbol("IACC_FIRE", iasACEClusterClientCommands)
iasACEClusterClientFire.setLabel("0x03.Tx Fire")
iasACEClusterClientFire.setDefaultValue(True)
iasACEClusterClientFire.setDescription("Send Fire - check the box to enable")

global iasACEClusterClientPanic
iasACEClusterClientPanic = drvZigbeeComponent.createBooleanSymbol("IACC_PANIC", iasACEClusterClientCommands)
iasACEClusterClientPanic.setLabel("0x04.Tx Panic")
iasACEClusterClientPanic.setDefaultValue(True)
iasACEClusterClientPanic.setDescription("Send Panic - check the box to enable")

global iasACEClusterClientGetZoneIDMap
iasACEClusterClientGetZoneIDMap = drvZigbeeComponent.createBooleanSymbol("IACC_GETZONEIDMAP", iasACEClusterClientCommands)
iasACEClusterClientGetZoneIDMap.setLabel("0x05.Tx Get Zone ID Map")
iasACEClusterClientGetZoneIDMap.setDefaultValue(True)
iasACEClusterClientGetZoneIDMap.setDescription("Send Get Zone ID Map - check the box to enable")

global iasACEClusterClientGetZoneInfo
iasACEClusterClientGetZoneInfo = drvZigbeeComponent.createBooleanSymbol("IACC_GETZONEINFO", iasACEClusterClientCommands)
iasACEClusterClientGetZoneInfo.setLabel("0x06.Tx Get Zone Information")
iasACEClusterClientGetZoneInfo.setDefaultValue(True)
iasACEClusterClientGetZoneInfo.setDescription("Send Get Zone Information - check the box to enable")

global iasACEClusterClientGetPanelStatus
iasACEClusterClientGetPanelStatus = drvZigbeeComponent.createBooleanSymbol("IACC_GETPANELSTATUS", iasACEClusterClientCommands)
iasACEClusterClientGetPanelStatus.setLabel("0x07.Tx Get Panel Status")
iasACEClusterClientGetPanelStatus.setDefaultValue(True)
iasACEClusterClientGetPanelStatus.setDescription("Send Get Panel Status - check the box to enable")

global iasACEClusterClientGetBypassedZoneList
iasACEClusterClientGetBypassedZoneList = drvZigbeeComponent.createBooleanSymbol("IACC_GETBYPASSZONELIST", iasACEClusterClientCommands)
iasACEClusterClientGetBypassedZoneList.setLabel("0x08.Tx Get Bypassed Zone List")
iasACEClusterClientGetBypassedZoneList.setDefaultValue(True)
iasACEClusterClientGetBypassedZoneList.setDescription("Send Get Bypassed Zone List - check the box to enable")

global iasACEClusterClientGetZoneStatus
iasACEClusterClientGetZoneStatus = drvZigbeeComponent.createBooleanSymbol("IACC_GETZONESTATUS", iasACEClusterClientCommands)
iasACEClusterClientGetZoneStatus.setLabel("0x09.Tx Get Zone Status")
iasACEClusterClientGetZoneStatus.setDefaultValue(True)
iasACEClusterClientGetZoneStatus.setDescription("Send Get Zone Status - check the box to enable")

# Commands received
global iasACEClusterClientArmResp
iasACEClusterClientArmResp = drvZigbeeComponent.createBooleanSymbol("IACC_ARMRESP", iasACEClusterClientCommands)
iasACEClusterClientArmResp.setLabel("0x00.Rx Arm Response")
iasACEClusterClientArmResp.setDefaultValue(True)
iasACEClusterClientArmResp.setDescription("Receive Arm Response - check the box to enable")

global iasACEClusterClientGetZoneIdMapResp
iasACEClusterClientGetZoneIdMapResp = drvZigbeeComponent.createBooleanSymbol("IACC_GETZONEIDMAPRESP", iasACEClusterClientCommands)
iasACEClusterClientGetZoneIdMapResp.setLabel("0x01.Rx Get Zone ID Map Response")
iasACEClusterClientGetZoneIdMapResp.setDefaultValue(True)
iasACEClusterClientGetZoneIdMapResp.setDescription("Receive Get Zone ID Map Response - check the box to enable")

global iasACEClusterClientGetZoneInfoResp
iasACEClusterClientGetZoneInfoResp = drvZigbeeComponent.createBooleanSymbol("IACC_GETZONEINFORESP", iasACEClusterClientCommands)
iasACEClusterClientGetZoneInfoResp.setLabel("0x02.Rx Get Zone Information Response")
iasACEClusterClientGetZoneInfoResp.setDefaultValue(True)
iasACEClusterClientGetZoneInfoResp.setDescription("Receive Get Zone Information Response - check the box to enable")

global iasACEClusterClientZoneStatusChanged
iasACEClusterClientZoneStatusChanged = drvZigbeeComponent.createBooleanSymbol("IACC_ZONESTATUSCHANGED", iasACEClusterClientCommands)
iasACEClusterClientZoneStatusChanged.setLabel("0x03.Rx Zone Status Changed")
iasACEClusterClientZoneStatusChanged.setDefaultValue(True)
iasACEClusterClientZoneStatusChanged.setDescription("Receive Zone Status Changed - check the box to enable")

global iasACEClusterClientPanelStatusChanged
iasACEClusterClientPanelStatusChanged = drvZigbeeComponent.createBooleanSymbol("IACC_PANELSTATUSCHANGED", iasACEClusterClientCommands)
iasACEClusterClientPanelStatusChanged.setLabel("0x04.Rx Panel Status Changed")
iasACEClusterClientPanelStatusChanged.setDefaultValue(True)
iasACEClusterClientPanelStatusChanged.setDescription("Receive Panel Status Changed - check the box to enable")

global iasACEClusterClientGetPanelStatusResponse
iasACEClusterClientGetPanelStatusResponse = drvZigbeeComponent.createBooleanSymbol("IACC_PANELSTATUSRESP", iasACEClusterClientCommands)
iasACEClusterClientGetPanelStatusResponse.setLabel("0x05.Rx Get Panel Status Response")
iasACEClusterClientGetPanelStatusResponse.setDefaultValue(True)
iasACEClusterClientGetPanelStatusResponse.setDescription("Receive Get Panel Status Response - check the box to enable")

global iasACEClusterClientSetBypassedZoneList
iasACEClusterClientSetBypassedZoneList = drvZigbeeComponent.createBooleanSymbol("IACC_SETBYPASSEDZONELIST", iasACEClusterClientCommands)
iasACEClusterClientSetBypassedZoneList.setLabel("0x06.Rx Set Bypassed Zone List")
iasACEClusterClientSetBypassedZoneList.setDefaultValue(True)
iasACEClusterClientSetBypassedZoneList.setDescription("Receive Set Bypassed Zone List - check the box to enable")

global iasACEClusterClientBypassResponse
iasACEClusterClientBypassResponse = drvZigbeeComponent.createBooleanSymbol("IACC_BYPASSRESPONSE", iasACEClusterClientCommands)
iasACEClusterClientBypassResponse.setLabel("0x07.Rx Bypass Response")
iasACEClusterClientBypassResponse.setDefaultValue(True)
iasACEClusterClientBypassResponse.setDescription("Receive Bypass Response - check the box to enable")

global iasACEClusterClientGetZoneStatusResp
iasACEClusterClientGetZoneStatusResp = drvZigbeeComponent.createBooleanSymbol("IACC_GETZONESTATUSRESP", iasACEClusterClientCommands)
iasACEClusterClientGetZoneStatusResp.setLabel("0x08.Rx Get Zone Status Response")
iasACEClusterClientGetZoneStatusResp.setDefaultValue(True)
iasACEClusterClientGetZoneStatusResp.setDescription("Receive Get Zone Status Response - check the box to enable")

global iasACEClusterClientCommandCount
iasACEClusterClientCommandCount = drvZigbeeComponent.createIntegerSymbol("IACC_CLIENTCOMMANDCOUNT", iasACEClusterClientCommands)
iasACEClusterClientCommandCount.setLabel("Commands Count")
iasACEClusterClientCommandCount.setDefaultValue(iasACEClusterClientCommandCountUpdate(0,0))
iasACEClusterClientCommandCount.setVisible(True)
iasACEClusterClientCommandCount.setDescription("Commands Count")
iasACEClusterClientCommandCount.setReadOnly(True)
iasACEClusterClientCommandCount.setDependencies(iasACEClusterClientCommandCountUpdate,["IACC_ARM", "IACC_BYPASS", "IACC_EMERGENCY", "IACC_FIRE","IACC_PANIC", "IACC_GETZONEIDMAP", "IACC_GETZONEINFO","IACC_GETPANELSTATUS","IACC_GETBYPASSZONELIST","IACC_GETZONESTATUS","IACC_ARMRESP", "IACC_GETZONEIDMAPRESP", "IACC_GETZONEINFORESP", "IACC_ZONESTATUSCHANGED","IACC_PANELSTATUSCHANGED", "IACC_PANELSTATUSRESP", "IACC_SETBYPASSEDZONELIST","IACC_BYPASSRESPONSE","IACC_GETZONESTATUSRESP"])

############################################################################################################
# Default Values Settings based on device type
iasACEClusterHandling()

############################################################################################################
##################################### FTL Files Definitions ################################################
############################################################################################################

# IAS ACE CLUSTER Common header
iasACEClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_IASACE_CLUSTER_CONF", None)
iasACEClusterConf.setSourcePath("/driver/zigbee/templates/cluster/iasace/zclIasACECluster.h.ftl")
iasACEClusterConf.setOutputName("zclIasACECluster.h")
iasACEClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
iasACEClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
iasACEClusterConf.setType("HEADER")
iasACEClusterConf.setOverwrite(True)
iasACEClusterConf.setMarkup(True)

# IAS ACE CLUSTER - Combined Interface
iasACEClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_IASACE_CLUSTER_CONF_SRC_CI", None)
iasACEClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/iasace/ciIasACECluster.c.ftl")
iasACEClusterConfSrc.setOutputName("ciIasACECluster.c")
iasACEClusterConfSrc.setDestPath("/zigbee/z3device/combinedInterface")
iasACEClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/combinedInterface/")
iasACEClusterConfSrc.setType("SOURCE")
iasACEClusterConfSrc.setOverwrite(True)
iasACEClusterConfSrc.setMarkup(True)
iasACEClusterConfSrc.setEnabled(checkDevTypeCombInterface)

# IAS ACE CLUSTER - IAS ACE
iasACEClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_IASACE_CLUSTER_CONF_SRC_IASACE", None)
iasACEClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/iasace/iasACEAceCluster.c.ftl")
iasACEClusterConfSrc.setOutputName("iasACEAceCluster.c")
iasACEClusterConfSrc.setDestPath("/zigbee/z3device/ias_ace")
iasACEClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/ias_ace/")
iasACEClusterConfSrc.setType("SOURCE")
iasACEClusterConfSrc.setOverwrite(True)
iasACEClusterConfSrc.setMarkup(True)
iasACEClusterConfSrc.setEnabled(checkDevTypeIasAce)

# IAS ACE CLUSTER - Custom
iasACEClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_IASACE_CLUSTER_CONF_SRC_CUSTOM", None)
iasACEClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/iasace/customIasACECluster.c.ftl")
iasACEClusterConfSrc.setOutputName("customIasACECluster.c")
iasACEClusterConfSrc.setDestPath("/zigbee/z3device/custom")
iasACEClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/custom/")
iasACEClusterConfSrc.setType("SOURCE")
iasACEClusterConfSrc.setOverwrite(True)
iasACEClusterConfSrc.setMarkup(True)
iasACEClusterConfSrc.setEnabled(checkDevTypeCustom and iasACECluster.getValue())
iasACEClusterConfSrc.setDependencies(customIasACEClusterEnableCheck,["IASACE_CLUSTER_ENABLE"])
############################################################################################################
