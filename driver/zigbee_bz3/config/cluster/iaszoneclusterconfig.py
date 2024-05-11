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

############################################################################################################
###########################################  IAS ZONE CLUSTER CONFIGURATION   ##############################
############################################################################################################

############################################################################################################
############################################# Function Definitions #########################################
############################################################################################################
def iasZoneClusterCsCheck(symbol, event):
    if (iasZoneCluster.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def iasZoneClusterEnableCheck(symbol, event):
    if (iasZoneCluster.getValue() == False):
        symbol.setEnabled(False)
    else:
        symbol.setEnabled(True)

def customIasZoneClusterEnableCheck(symbol, event):
    if ((zigbeeDeviceType.getValue() == 'ZIGBEE_CUSTOM') and (iasZoneCluster.getValue() == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def iasZoneClusterClientCheck(symbol, event):
    if ((iasZoneCluster.getValue() == False) or iasZoneClusterCS.getValue() == "SERVER"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def iasZoneClusterServerCheck(symbol, event):
    if ((iasZoneCluster.getValue() == False) or iasZoneClusterCS.getValue() == "CLIENT"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def iasZoneClusterHandling():

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
        iasZoneCluster.setVisible(False)
        iasZoneCluster.setValue(False)
    elif ((getDevice == "ZIGBEE_COMBINED_INTERFACE")):
        iasZoneCluster.setVisible(True)
        iasZoneCluster.setValue(True)
        iasZoneCluster.setReadOnly(True)
        iasZoneClusterCS.setValue("CLIENT")
        iasZoneClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_IAS_ACE")):
        iasZoneCluster.setVisible(True)
        iasZoneCluster.setValue(True)
        iasZoneCluster.setReadOnly(True)
        iasZoneClusterCS.setValue("SERVER")
        iasZoneClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_CUSTOM")):
        iasZoneCluster.setVisible(True)
        iasZoneCluster.setValue(False)
        iasZoneClusterCS.setValue("BOTH")
    else:
        iasZoneCluster.setVisible(False)

def iasZoneClusterServerAttributeCountUpdate(symbol, event):
    count = 0
    if (iasZoneClusterServerAttributeZoneState.getValue()):
        count += 1
    if (iasZoneClusterServerAttributeZoneType.getValue()):
        count += 1
    if (iasZoneClusterServerAttributeZoneStatus.getValue()):
        count += 1
    if (iasZoneClusterServerAttributeIASCIEAddress.getValue()):
        count += 1
    if (iasZoneClusterServerAttributeZoneID.getValue()):
        count += 1
    if (iasZoneClusterServerAttributeNumSensLevSupp.getValue()):
        count += 1
    if (iasZoneClusterServerAttributeCurrentZoneSensitivityLevel.getValue()):
        count += 1
    if (iasZoneClusterServerAttributeClusterRevision.getValue()):
        count += 1
    iasZoneClusterServerAttributeCount.setValue(count) 
    return count

def iasZoneClusterServerCommandCountUpdate(symbol, event):
    count = 0
    if (iasZoneClusterServerZoneEnrollResp.getValue()):
        count += 1
    if (iasZoneClusterServerNorOpMode.getValue()):
        count += 1
    if (iasZoneClusterServerTestMode.getValue()):
        count += 1
    if (iasZoneClusterServerZoneStatusChangeNotif.getValue()):
        count += 1
    if (iasZoneClusterServerZoneEnrollReq.getValue()):
        count += 1		
    iasZoneClusterServerCommandCount.setValue(count)
    return count

def iasZoneClusterClientAttributeCountUpdate(symbol, event):
    count = 0
    if (iasZoneClusterClientAttributeClusterRevision.getValue()):
        count += 1
    iasZoneClusterClientAttributeCount.setValue(count)
    return count

def iasZoneClusterClientCommandCountUpdate(symbol, event):
    count = 0
    if (iasZoneClusterClientZoneEnrollResp.getValue()):
        count += 1
    if (iasZoneClusterClientNorOpMode.getValue()):
        count += 1
    if (iasZoneClusterClientTestMode.getValue()):
        count += 1
    if (iasZoneClusterClientZoneStatusChangeNotif.getValue()):
        count += 1
    if (iasZoneClusterClientZoneEnrollReq.getValue()):
        count += 1	
    iasZoneClusterClientCommandCount.setValue(count)
    return count
############################################################################################################
##################################### Configuration Item Definitions #######################################
############################################################################################################

global iasZoneCluster
iasZoneCluster = drvZigbeeComponent.createBooleanSymbol("IASZONE_CLUSTER_ENABLE", clusterConfigMenu)
iasZoneCluster.setLabel("0x0500 IAS Zone Cluster")
iasZoneCluster.setDefaultValue(False)
iasZoneCluster.setVisible(False)
iasZoneCluster.setDescription("IAS ZONE CLUSTER- check the box to enable")
iasZoneCluster.setReadOnly(False)

global iasZoneClusterCS
iasZoneClusterCS = drvZigbeeComponent.createComboSymbol("IASZONE_CLUSTER_CS",  iasZoneCluster, ["CLIENT","SERVER", "BOTH"])
iasZoneClusterCS.setLabel("Supported Implementation")
iasZoneClusterCS.setDefaultValue("BOTH")
#iasZoneClusterCS.setVisible(False)
iasZoneClusterCS.setDescription("IAS ZONE Cluster Supported Implementation- Select the option")
iasZoneClusterCS.setDependencies(iasZoneClusterCsCheck,["IASZONE_CLUSTER_ENABLE"])

iasZoneClusterClientMenu = drvZigbeeComponent.createMenuSymbol("IASZONE_CLUSTER_CLIENT_MENU", iasZoneCluster)
iasZoneClusterClientMenu.setLabel("Client")
#iasZoneClusterClientMenu.setVisible(False)
iasZoneClusterClientMenu.setDescription("IAS ZONE CLUSTER CLIENT")
iasZoneClusterClientMenu.setDependencies(iasZoneClusterClientCheck,["IASZONE_CLUSTER_CS","IASZONE_CLUSTER_ENABLE"])

iasZoneClusterServerMenu = drvZigbeeComponent.createMenuSymbol("IASZONE_CLUSTER_SERVER_MENU", iasZoneCluster)
iasZoneClusterServerMenu.setLabel("Server")
#iasZoneClusterServerMenu.setVisible(False)
iasZoneClusterServerMenu.setDescription("IAS ZONE CLUSTER SERVER")
iasZoneClusterServerMenu.setDependencies(iasZoneClusterServerCheck,["IASZONE_CLUSTER_CS","IASZONE_CLUSTER_ENABLE"])

iasZoneClusterClientAttributes = drvZigbeeComponent.createMenuSymbol("IASZONE_CLUSTER_CLIENT__ATTRIBUTES_MENU", iasZoneClusterClientMenu)
iasZoneClusterClientAttributes.setLabel("Attributes")
#iasZoneClusterClientAttributes.setVisible(False)
iasZoneClusterClientAttributes.setDescription("IAS ZONE CLUSTER CLIENT ATTRIBUTES")
iasZoneClusterClientAttributes.setDependencies(iasZoneClusterClientCheck,["IASZONE_CLUSTER_CS"])

iasZoneClusterClientCommands = drvZigbeeComponent.createMenuSymbol("IASZONE_CLUSTER_CLIENT__COMMANDS_MENU", iasZoneClusterClientMenu)
iasZoneClusterClientCommands.setLabel("Commands")
#iasZoneClusterClientCommands.setVisible(False)
iasZoneClusterClientCommands.setDescription("IAS ZONE CLUSTER CLIENT COMMANDS")
iasZoneClusterClientCommands.setDependencies(iasZoneClusterClientCheck,["IASZONE_CLUSTER_CS"])

iasZoneClusterServerAttributes = drvZigbeeComponent.createMenuSymbol("IASZONE_CLUSTER_SERVER__ATTRIBUTES_MENU", iasZoneClusterServerMenu)
iasZoneClusterServerAttributes.setLabel("Attributes")
#iasZoneClusterServerAttributes.setVisible(False)
iasZoneClusterServerAttributes.setDescription("IAS ZONE CLUSTER SERVER ATTRIBUTES")
iasZoneClusterServerAttributes.setDependencies(iasZoneClusterServerCheck,["IASZONE_CLUSTER_CS"])

iasZoneClusterServerCommands = drvZigbeeComponent.createMenuSymbol("IASZONE_CLUSTER_SERVER__COMMANDS_MENU", iasZoneClusterServerMenu)
iasZoneClusterServerCommands.setLabel("Commands")
#iasZoneClusterServerCommands.setVisible(False)
iasZoneClusterServerCommands.setDescription("IAS ZONE CLUSTER SERVER COMMANDS")
iasZoneClusterServerCommands.setDependencies(iasZoneClusterServerCheck,["IASZONE_CLUSTER_CS"])

#################               Server Attributes                                 ###############

# Zone Information Attribute Set
global iasZoneClusterServerAttributeZoneState
iasZoneClusterServerAttributeZoneState = drvZigbeeComponent.createBooleanSymbol("IZC_ZONESTATE", iasZoneClusterServerAttributes)
iasZoneClusterServerAttributeZoneState.setLabel("0x0000 Zone State")
iasZoneClusterServerAttributeZoneState.setDefaultValue(True)
iasZoneClusterServerAttributeZoneState.setDescription("Zone State - check the box to enable")
iasZoneClusterServerAttributeZoneState.setReadOnly(True)

global iasZoneClusterServerAttributeZoneType
iasZoneClusterServerAttributeZoneType = drvZigbeeComponent.createBooleanSymbol("IZC_ZONETYPE", iasZoneClusterServerAttributes)
iasZoneClusterServerAttributeZoneType.setLabel("0x0001 Zone Type")
iasZoneClusterServerAttributeZoneType.setDefaultValue(True)
iasZoneClusterServerAttributeZoneType.setDescription("Zone Type - check the box to enable")
iasZoneClusterServerAttributeZoneType.setReadOnly(True)

global iasZoneClusterServerAttributeZoneStatus
iasZoneClusterServerAttributeZoneStatus = drvZigbeeComponent.createBooleanSymbol("IZC_ZONESTATUS", iasZoneClusterServerAttributes)
iasZoneClusterServerAttributeZoneStatus.setLabel("0x0002 Zone Status")
iasZoneClusterServerAttributeZoneStatus.setDefaultValue(True)
iasZoneClusterServerAttributeZoneStatus.setDescription("Zone Status - check the box to enable")
iasZoneClusterServerAttributeZoneStatus.setReadOnly(True)

# Zone Settings Attribute Set
global iasZoneClusterServerAttributeIASCIEAddress
iasZoneClusterServerAttributeIASCIEAddress = drvZigbeeComponent.createBooleanSymbol("IZC_IASCIEADDRESS", iasZoneClusterServerAttributes)
iasZoneClusterServerAttributeIASCIEAddress.setLabel("0x0010 IAS CIE address")
iasZoneClusterServerAttributeIASCIEAddress.setDefaultValue(True)
iasZoneClusterServerAttributeIASCIEAddress.setDescription("IAS CIE address - check the box to enable")
iasZoneClusterServerAttributeIASCIEAddress.setReadOnly(True)

global iasZoneClusterServerAttributeZoneID
iasZoneClusterServerAttributeZoneID = drvZigbeeComponent.createBooleanSymbol("IZC_ZONEID", iasZoneClusterServerAttributes)
iasZoneClusterServerAttributeZoneID.setLabel("0x0011 Zone ID")
iasZoneClusterServerAttributeZoneID.setDefaultValue(True)
iasZoneClusterServerAttributeZoneID.setDescription("Zone ID - check the box to enable")
iasZoneClusterServerAttributeZoneID.setReadOnly(True)

global iasZoneClusterServerAttributeNumSensLevSupp
iasZoneClusterServerAttributeNumSensLevSupp = drvZigbeeComponent.createBooleanSymbol("IZC_NUMOFZONESENSLEVELSUPPORTED", iasZoneClusterServerAttributes)
iasZoneClusterServerAttributeNumSensLevSupp.setLabel("0x0012 Number of Zone Sensitivity Levels Supported")
iasZoneClusterServerAttributeNumSensLevSupp.setDefaultValue(True)
iasZoneClusterServerAttributeNumSensLevSupp.setDescription("Number of Zone Sensitivity Levels Supported - check the box to enable")

global iasZoneClusterServerAttributeCurrentZoneSensitivityLevel
iasZoneClusterServerAttributeCurrentZoneSensitivityLevel  = drvZigbeeComponent.createBooleanSymbol("IZC_CURRENTZONESENSITIVITYLEVEL", iasZoneClusterServerAttributes)
iasZoneClusterServerAttributeCurrentZoneSensitivityLevel.setLabel("0x0013 Current Zone Sensitivity Level")
iasZoneClusterServerAttributeCurrentZoneSensitivityLevel.setDefaultValue(True)
iasZoneClusterServerAttributeCurrentZoneSensitivityLevel.setDescription("Current Zone Sensitivity Level - check the box to enable")

# Global Attributes
global iasZoneClusterServerAttributeClusterRevision
iasZoneClusterServerAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("IZC_CLUSTERREVISION", iasZoneClusterServerAttributes)
iasZoneClusterServerAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
iasZoneClusterServerAttributeClusterRevision.setDefaultValue(True)
iasZoneClusterServerAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
iasZoneClusterServerAttributeClusterRevision.setReadOnly(True)

global iasZoneClusterServerAttributeCount
iasZoneClusterServerAttributeCount = drvZigbeeComponent.createIntegerSymbol("IZC_SERVERATTRIBUTECOUNT", iasZoneClusterServerAttributes)
iasZoneClusterServerAttributeCount.setLabel("Attributes Count")
iasZoneClusterServerAttributeCount.setDefaultValue(iasZoneClusterServerAttributeCountUpdate(0,0))
iasZoneClusterServerAttributeCount.setVisible(True)
iasZoneClusterServerAttributeCount.setDescription("Attributes Count")
iasZoneClusterServerAttributeCount.setReadOnly(True)
iasZoneClusterServerAttributeCount.setDependencies(iasZoneClusterServerAttributeCountUpdate,["IZC_CLUSTERREVISION","IZC_CURRENTZONESENSITIVITYLEVEL", "IZC_NUMOFZONESENSLEVELSUPPORTED", "IZC_ZONEID", "IZC_IASCIEADDRESS","IZC_ZONESTATUS", "IZC_ZONETYPE","IZC_ZONESTATE"])

#################               Server Commands                                 ###############

# Commands received
global iasZoneClusterServerZoneEnrollResp
iasZoneClusterServerZoneEnrollResp = drvZigbeeComponent.createBooleanSymbol("IZC_ZONEENROLLRESP", iasZoneClusterServerCommands)
iasZoneClusterServerZoneEnrollResp.setLabel("0x00.Rx Zone Enroll Response")
iasZoneClusterServerZoneEnrollResp.setDefaultValue(True)
iasZoneClusterServerZoneEnrollResp.setDescription("Receive Zone Enroll Response - check the box to enable")
iasZoneClusterServerZoneEnrollResp.setReadOnly(True)

global iasZoneClusterServerNorOpMode
iasZoneClusterServerNorOpMode = drvZigbeeComponent.createBooleanSymbol("IZC_INITIATENORMALOPMODE", iasZoneClusterServerCommands)
iasZoneClusterServerNorOpMode.setLabel("0x01.Rx Initiate Normal Operation Mode")
iasZoneClusterServerNorOpMode.setDefaultValue(True)
iasZoneClusterServerNorOpMode.setDescription("Receive Initiate Normal Operation Mode - check the box to enable")

global iasZoneClusterServerTestMode
iasZoneClusterServerTestMode = drvZigbeeComponent.createBooleanSymbol("IZC_INITIATETESTMODE", iasZoneClusterServerCommands)
iasZoneClusterServerTestMode.setLabel("0x02.Rx Initiate Test Mode")
iasZoneClusterServerTestMode.setDefaultValue(True)
iasZoneClusterServerTestMode.setDescription("Receive Initiate Test Mode - check the box to enable")

# Commands generated
global iasZoneClusterServerZoneStatusChangeNotif
iasZoneClusterServerZoneStatusChangeNotif = drvZigbeeComponent.createBooleanSymbol("IZC_ZONESTATUSCHANGENOTIFICATION", iasZoneClusterServerCommands)
iasZoneClusterServerZoneStatusChangeNotif.setLabel("0x00.Tx Zone Status Change Notification")
iasZoneClusterServerZoneStatusChangeNotif.setDefaultValue(True)
iasZoneClusterServerZoneStatusChangeNotif.setDescription("Receive Zone Status Change Notification - check the box to enable")
iasZoneClusterServerZoneStatusChangeNotif.setReadOnly(True)

global iasZoneClusterServerZoneEnrollReq
iasZoneClusterServerZoneEnrollReq = drvZigbeeComponent.createBooleanSymbol("IZC_ZONEENROLLREQ", iasZoneClusterServerCommands)
iasZoneClusterServerZoneEnrollReq.setLabel("0x01.Tx Zone Enroll Request")
iasZoneClusterServerZoneEnrollReq.setDefaultValue(True)
iasZoneClusterServerZoneEnrollReq.setDescription("Receive Zone Enroll Request - check the box to enable")
iasZoneClusterServerZoneEnrollReq.setReadOnly(True)

global iasZoneClusterServerCommandCount
iasZoneClusterServerCommandCount = drvZigbeeComponent.createIntegerSymbol("IZC_SERVERCOMMANDCOUNT", iasZoneClusterServerCommands)
iasZoneClusterServerCommandCount.setLabel("Commands Count")
iasZoneClusterServerCommandCount.setDefaultValue(iasZoneClusterServerCommandCountUpdate(0,0))
iasZoneClusterServerCommandCount.setVisible(True)
iasZoneClusterServerCommandCount.setDescription("Commands Count")
iasZoneClusterServerCommandCount.setReadOnly(True)
iasZoneClusterServerCommandCount.setDependencies(iasZoneClusterServerCommandCountUpdate,["IZC_ZONEENROLLRESP", "IZC_INITIATENORMALOPMODE", "IZC_INITIATETESTMODE", "IZC_ZONESTATUSCHANGENOTIFICATION","IZC_ZONEENROLLREQ"])

#################               Client Attributes                                 ###############
global iasZoneClusterClientAttributeClusterRevision
iasZoneClusterClientAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("IZCC_CLUSTERREVISION", iasZoneClusterClientAttributes)
iasZoneClusterClientAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
iasZoneClusterClientAttributeClusterRevision.setDefaultValue(True)
iasZoneClusterClientAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
iasZoneClusterClientAttributeClusterRevision.setReadOnly(True)

global iasZoneClusterClientAttributeCount
iasZoneClusterClientAttributeCount = drvZigbeeComponent.createIntegerSymbol("IZCC_CLIENTATTRIBUTECOUNT", iasZoneClusterClientAttributes)
iasZoneClusterClientAttributeCount.setLabel("Attributes Count")
iasZoneClusterClientAttributeCount.setDefaultValue(iasZoneClusterClientAttributeCountUpdate(0,0))
iasZoneClusterClientAttributeCount.setVisible(True)
iasZoneClusterClientAttributeCount.setDescription("Attributes Count")
iasZoneClusterClientAttributeCount.setReadOnly(True)
iasZoneClusterClientAttributeCount.setDependencies(iasZoneClusterClientAttributeCountUpdate,["IZCC_CLUSTERREVISION"])

#################               Client Commands                                 ###############

# Commands generated
global iasZoneClusterClientZoneEnrollResp
iasZoneClusterClientZoneEnrollResp = drvZigbeeComponent.createBooleanSymbol("IZCC_ZONEENROLLRESP", iasZoneClusterClientCommands)
iasZoneClusterClientZoneEnrollResp.setLabel("0x00.Tx Zone Enroll Response")
iasZoneClusterClientZoneEnrollResp.setDefaultValue(True)
iasZoneClusterClientZoneEnrollResp.setDescription("Receive Zone Enroll Response - check the box to enable")
iasZoneClusterClientZoneEnrollResp.setReadOnly(True)

global iasZoneClusterClientNorOpMode
iasZoneClusterClientNorOpMode = drvZigbeeComponent.createBooleanSymbol("IZCC_INITIATENORMALOPMODE", iasZoneClusterClientCommands)
iasZoneClusterClientNorOpMode.setLabel("0x01.Tx Initiate Normal Operation Mode")
iasZoneClusterClientNorOpMode.setDefaultValue(True)
iasZoneClusterClientNorOpMode.setDescription("Receive Initiate Normal Operation Mode - check the box to enable")

global iasZoneClusterClientTestMode
iasZoneClusterClientTestMode = drvZigbeeComponent.createBooleanSymbol("IZCC_INITIATETESTMODE", iasZoneClusterClientCommands)
iasZoneClusterClientTestMode.setLabel("0x02.Tx Initiate Test Mode")
iasZoneClusterClientTestMode.setDefaultValue(True)
iasZoneClusterClientTestMode.setDescription("Receive Initiate Test Mode - check the box to enable")

# Commands received
global iasZoneClusterClientZoneStatusChangeNotif
iasZoneClusterClientZoneStatusChangeNotif = drvZigbeeComponent.createBooleanSymbol("IZCC_ZONESTATUSCHANGENOTIFICATION", iasZoneClusterClientCommands)
iasZoneClusterClientZoneStatusChangeNotif.setLabel("0x00.Rx Zone Status Change Notification")
iasZoneClusterClientZoneStatusChangeNotif.setDefaultValue(True)
iasZoneClusterClientZoneStatusChangeNotif.setDescription("Receive Zone Status Change Notification - check the box to enable")
iasZoneClusterClientZoneStatusChangeNotif.setReadOnly(True)

global iasZoneClusterClientZoneEnrollReq
iasZoneClusterClientZoneEnrollReq = drvZigbeeComponent.createBooleanSymbol("IZCC_ZONEENROLLREQ", iasZoneClusterClientCommands)
iasZoneClusterClientZoneEnrollReq.setLabel("0x01.Rx Zone Enroll Request")
iasZoneClusterClientZoneEnrollReq.setDefaultValue(True)
iasZoneClusterClientZoneEnrollReq.setDescription("Receive Zone Enroll Request - check the box to enable")
iasZoneClusterClientZoneEnrollReq.setReadOnly(True)

global iasZoneClusterClientCommandCount
iasZoneClusterClientCommandCount = drvZigbeeComponent.createIntegerSymbol("IZCC_CLIENTCOMMANDCOUNT", iasZoneClusterClientCommands)
iasZoneClusterClientCommandCount.setLabel("Commands Count")
iasZoneClusterClientCommandCount.setDefaultValue(iasZoneClusterClientCommandCountUpdate(0,0))
iasZoneClusterClientCommandCount.setVisible(True)
iasZoneClusterClientCommandCount.setDescription("Commands Count")
iasZoneClusterClientCommandCount.setReadOnly(True)
iasZoneClusterClientCommandCount.setDependencies(iasZoneClusterClientCommandCountUpdate,["IZCC_ZONEENROLLRESP", "IZCC_INITIATENORMALOPMODE", "IZCC_INITIATETESTMODE", "IZCC_ZONESTATUSCHANGENOTIFICATION","IZCC_ZONEENROLLREQ"])

############################################################################################################
# Default Values Settings based on device type
iasZoneClusterHandling()

############################################################################################################
##################################### FTL Files Definitions ################################################
############################################################################################################

# IAS ZONE CLUSTER Common header
iasZoneClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_IASZONE_CLUSTER_CONF", None)
iasZoneClusterConf.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/iaszone/zclIasZoneCluster.h.ftl")
iasZoneClusterConf.setOutputName("zclIasZoneCluster.h")
iasZoneClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
iasZoneClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
iasZoneClusterConf.setType("HEADER")
iasZoneClusterConf.setOverwrite(True)
iasZoneClusterConf.setMarkup(True)

# IAS ZONE CLUSTER - Combined Interface
iasZoneClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_IASZONE_CLUSTER_CONF_SRC_CI", None)
iasZoneClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/iaszone/ciIasZoneCluster.c.ftl")
iasZoneClusterConfSrc.setOutputName("ciIasZoneCluster.c")
iasZoneClusterConfSrc.setDestPath("/zigbee/z3device/combinedInterface")
iasZoneClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/combinedInterface/")
iasZoneClusterConfSrc.setType("SOURCE")
iasZoneClusterConfSrc.setOverwrite(True)
iasZoneClusterConfSrc.setMarkup(True)
iasZoneClusterConfSrc.setEnabled(checkDevTypeCombInterface)

# IAS ZONE CLUSTER - IAS ACE
iasZoneClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_IASZONE_CLUSTER_CONF_SRC_IASACE", None)
iasZoneClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/iaszone/iasACEZoneCluster.c.ftl")
iasZoneClusterConfSrc.setOutputName("iasACEZoneCluster.c")
iasZoneClusterConfSrc.setDestPath("/zigbee/z3device/ias_ace")
iasZoneClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/ias_ace/")
iasZoneClusterConfSrc.setType("SOURCE")
iasZoneClusterConfSrc.setOverwrite(True)
iasZoneClusterConfSrc.setMarkup(True)
iasZoneClusterConfSrc.setEnabled(checkDevTypeIasAce)

# IAS ZONE CLUSTER - Custom
iasZoneClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_IASZONE_CLUSTER_CONF_SRC_CUSTOM", None)
iasZoneClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/iaszone/customIasZoneCluster.c.ftl")
iasZoneClusterConfSrc.setOutputName("customIasZoneCluster.c")
iasZoneClusterConfSrc.setDestPath("/zigbee/z3device/custom")
iasZoneClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/custom/")
iasZoneClusterConfSrc.setType("SOURCE")
iasZoneClusterConfSrc.setOverwrite(True)
iasZoneClusterConfSrc.setMarkup(True)
iasZoneClusterConfSrc.setEnabled(checkDevTypeCustom and iasZoneCluster.getValue())
iasZoneClusterConfSrc.setDependencies(customIasZoneClusterEnableCheck,["IASZONE_CLUSTER_ENABLE"])
############################################################################################################
