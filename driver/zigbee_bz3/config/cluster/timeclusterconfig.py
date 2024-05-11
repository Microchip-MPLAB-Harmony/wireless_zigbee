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
###########################################  TIME CLUSTER CONFIGURATION   #################################
############################################################################################################

############################################################################################################
############################################# Function Definitions #########################################
############################################################################################################
def timeClusterCsCheck(symbol, event):
    if (timeCluster.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def timeClusterEnableCheck(symbol, event):
    if (timeCluster.getValue() == False):
        symbol.setEnabled(False)
    else:
        symbol.setEnabled(True)

def customTimeClusterEnableCheck(symbol, event):
    if ((zigbeeDeviceType.getValue() == 'ZIGBEE_CUSTOM') and (timeCluster.getValue() == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def timeClusterClientCheck(symbol, event):
    if ((timeCluster.getValue() == False) or timeClusterCS.getValue() == "SERVER"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def timeClusterServerCheck(symbol, event):
    if ((timeCluster.getValue() == False) or timeClusterCS.getValue() == "CLIENT"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def timeClusterHandling():

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
        timeCluster.setVisible(False)
        timeCluster.setValue(False)
    elif ((getDevice == "ZIGBEE_COMBINED_INTERFACE")):
        timeCluster.setVisible(True)
        timeCluster.setValue(True)
        timeCluster.setReadOnly(True)
        timeClusterCS.setValue("SERVER")
        timeClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_THERMOSTAT")):
        timeCluster.setVisible(True)
        timeCluster.setValue(True)
        timeCluster.setReadOnly(True)
        timeClusterCS.setValue("CLIENT")
        timeClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_CUSTOM")):
        timeCluster.setVisible(True)
        timeCluster.setValue(True)
        timeClusterCS.setValue("BOTH")
    else:
        timeCluster.setVisible(False)

def timeClusterServerAttributeCountUpdate(symbol, event):
    count = 0
    if (timeClusterServerAttributeTime.getValue()):
        count += 1
    if (timeClusterServerAttributeTimeStatus.getValue()):
        count += 1
    if (timeClusterServerAttributeTimeZone.getValue()):
        count += 1
    if (timeClusterServerAttributeDstStart.getValue()):
        count += 1
    if (timeClusterServerAttributeDstEnd.getValue()):
        count += 1
    if (timeClusterServerAttributeDstShift.getValue()):
        count += 1
    if (timeClusterServerAttributeStandardTime.getValue()):
        count += 1
    if (timeClusterServerAttributeLocalTime.getValue()):
        count += 1
    if (timeClusterServerAttributeLastSetTime.getValue()):
        count += 1
    if (timeClusterServerAttributeValidUntilTime.getValue()):
        count += 1
    if (timeClusterServerAttributeClusterRevision.getValue()):
        count += 1
    timeClusterServerAttributeCount.setValue(count) 
    return count

def timeClusterClientAttributeCountUpdate(symbol, event):
    count = 0
    if (timeClusterClientAttributeClusterRevision.getValue()):
        count += 1
    timeClusterClientAttributeCount.setValue(count)
    return count
############################################################################################################
##################################### Configuration Item Definitions #######################################
############################################################################################################

global timeCluster
timeCluster = drvZigbeeComponent.createBooleanSymbol("TIME_CLUSTER_ENABLE", clusterConfigMenu)
timeCluster.setLabel("0x000A Time Cluster")
timeCluster.setDefaultValue(False)
timeCluster.setVisible(False)
timeCluster.setDescription("TIME CLUSTER- check the box to enable")
timeCluster.setReadOnly(False)

global timeClusterCS
timeClusterCS = drvZigbeeComponent.createComboSymbol("TIME_CLUSTER_CS",  timeCluster, ["CLIENT","SERVER", "BOTH"])
timeClusterCS.setLabel("Supported Implementation")
timeClusterCS.setDefaultValue("BOTH")
#timeClusterCS.setVisible(False)
timeClusterCS.setDescription("Time Cluster Supported Implementation- Select the option")
timeClusterCS.setDependencies(timeClusterCsCheck,["TIME_CLUSTER_ENABLE"])

timeClusterClientMenu = drvZigbeeComponent.createMenuSymbol("TIME_CLUSTER_CLIENT_MENU", timeCluster)
timeClusterClientMenu.setLabel("Client")
#timeClusterClientMenu.setVisible(False)
timeClusterClientMenu.setDescription("TIME CLUSTER CLIENT")
timeClusterClientMenu.setDependencies(timeClusterClientCheck,["TIME_CLUSTER_CS","TIME_CLUSTER_ENABLE"])

timeClusterServerMenu = drvZigbeeComponent.createMenuSymbol("TIME_CLUSTER_SERVER_MENU", timeCluster)
timeClusterServerMenu.setLabel("Server")
#timeClusterServerMenu.setVisible(False)
timeClusterServerMenu.setDescription("TIME CLUSTER SERVER")
timeClusterServerMenu.setDependencies(timeClusterServerCheck,["TIME_CLUSTER_CS","TIME_CLUSTER_ENABLE"])

timeClusterClientAttributes = drvZigbeeComponent.createMenuSymbol("TIME_CLUSTER_CLIENT__ATTRIBUTES_MENU", timeClusterClientMenu)
timeClusterClientAttributes.setLabel("Attributes")
#timeClusterClientAttributes.setVisible(False)
timeClusterClientAttributes.setDescription("TIME CLUSTER CLIENT ATTRIBUTES")
timeClusterClientAttributes.setDependencies(timeClusterClientCheck,["TIME_CLUSTER_CS"])

#timeClusterClientCommands = drvZigbeeComponent.createMenuSymbol("TIME_CLUSTER_CLIENT__COMMANDS_MENU", timeClusterClientMenu)
#timeClusterClientCommands.setLabel("Commands")
##timeClusterClientCommands.setVisible(False)
#timeClusterClientCommands.setDescription("TIME CLUSTER CLIENT COMMANDS")
#timeClusterClientCommands.setDependencies(timeClusterClientCheck,["TIME_CLUSTER_CS"])

timeClusterServerAttributes = drvZigbeeComponent.createMenuSymbol("TIME_CLUSTER_SERVER__ATTRIBUTES_MENU", timeClusterServerMenu)
timeClusterServerAttributes.setLabel("Attributes")
#timeClusterServerAttributes.setVisible(False)
timeClusterServerAttributes.setDescription("TIME CLUSTER SERVER ATTRIBUTES")
timeClusterServerAttributes.setDependencies(timeClusterServerCheck,["TIME_CLUSTER_CS"])

#timeClusterServerCommands = drvZigbeeComponent.createMenuSymbol("TIME_CLUSTER_SERVER__COMMANDS_MENU", timeClusterServerMenu)
#timeClusterServerCommands.setLabel("Commands")
##timeClusterServerCommands.setVisible(False)
#timeClusterServerCommands.setDescription("TIME CLUSTER SERVER COMMANDS")
#timeClusterServerCommands.setDependencies(timeClusterServerCheck,["TIME_CLUSTER_CS"])

#################               Server Attributes                                 ###############

global timeClusterServerAttributeTime
timeClusterServerAttributeTime = drvZigbeeComponent.createBooleanSymbol("TC_TIME", timeClusterServerAttributes)
timeClusterServerAttributeTime.setLabel("0x0000 Time")
timeClusterServerAttributeTime.setDefaultValue(True)
timeClusterServerAttributeTime.setDescription("Time  - check the box to enable")
timeClusterServerAttributeTime.setReadOnly(True)

global timeClusterServerAttributeTimeStatus
timeClusterServerAttributeTimeStatus  = drvZigbeeComponent.createBooleanSymbol("TC_TIMESTATUS", timeClusterServerAttributes)
timeClusterServerAttributeTimeStatus.setLabel("0x0001 TimeStatus")
timeClusterServerAttributeTimeStatus.setDefaultValue(True)
timeClusterServerAttributeTimeStatus.setDescription("TimeStatus - check the box to enable")
timeClusterServerAttributeTimeStatus.setReadOnly(True)

global timeClusterServerAttributeTimeZone
timeClusterServerAttributeTimeZone  = drvZigbeeComponent.createBooleanSymbol("TC_TIMEZONE", timeClusterServerAttributes)
timeClusterServerAttributeTimeZone.setLabel("0x0002 TimeZone")
timeClusterServerAttributeTimeZone.setDefaultValue(True)
timeClusterServerAttributeTimeZone.setDescription("TimeZone - check the box to enable")

global timeClusterServerAttributeDstStart
timeClusterServerAttributeDstStart  = drvZigbeeComponent.createBooleanSymbol("TC_DSTSTART", timeClusterServerAttributes)
timeClusterServerAttributeDstStart.setLabel("0x0003 DstStart")
timeClusterServerAttributeDstStart.setDefaultValue(True)
timeClusterServerAttributeDstStart.setDescription("DstStart  - check the box to enable")

global timeClusterServerAttributeDstEnd
timeClusterServerAttributeDstEnd  = drvZigbeeComponent.createBooleanSymbol("TC_DSTEND", timeClusterServerAttributes)
timeClusterServerAttributeDstEnd.setLabel("0x0004 DstEnd")
timeClusterServerAttributeDstEnd.setDefaultValue(True)
timeClusterServerAttributeDstEnd.setDescription("DstEnd  - check the box to enable")

global timeClusterServerAttributeDstShift
timeClusterServerAttributeDstShift  = drvZigbeeComponent.createBooleanSymbol("TC_DSTSHIFT", timeClusterServerAttributes)
timeClusterServerAttributeDstShift.setLabel("0x0005 DstShift")
timeClusterServerAttributeDstShift.setDefaultValue(True)
timeClusterServerAttributeDstShift.setDescription("DstShift  - check the box to enable")

global timeClusterServerAttributeStandardTime
timeClusterServerAttributeStandardTime   = drvZigbeeComponent.createBooleanSymbol("TC_STDTIME", timeClusterServerAttributes)
timeClusterServerAttributeStandardTime .setLabel("0x0006 StandardTime")
timeClusterServerAttributeStandardTime .setDefaultValue(True)
timeClusterServerAttributeStandardTime .setDescription("StandardTime - check the box to enable")

global timeClusterServerAttributeLocalTime
timeClusterServerAttributeLocalTime  = drvZigbeeComponent.createBooleanSymbol("TC_LOCALTIME", timeClusterServerAttributes)
timeClusterServerAttributeLocalTime.setLabel("0x0007 LocalTime")
timeClusterServerAttributeLocalTime.setDefaultValue(True)
timeClusterServerAttributeLocalTime.setDescription("LocalTime - check the box to enable")

global timeClusterServerAttributeLastSetTime
timeClusterServerAttributeLastSetTime  = drvZigbeeComponent.createBooleanSymbol("TC_LASTSETTIME", timeClusterServerAttributes)
timeClusterServerAttributeLastSetTime.setLabel("0x0008 LastSetTime")
timeClusterServerAttributeLastSetTime.setDefaultValue(True)
timeClusterServerAttributeLastSetTime.setDescription("LastSetTime - check the box to enable")

global timeClusterServerAttributeValidUntilTime
timeClusterServerAttributeValidUntilTime   = drvZigbeeComponent.createBooleanSymbol("TC_VALIDUNTILTIME", timeClusterServerAttributes)
timeClusterServerAttributeValidUntilTime .setLabel("0x0009 ValidUntilTime")
timeClusterServerAttributeValidUntilTime .setDefaultValue(True)
timeClusterServerAttributeValidUntilTime .setDescription("ValidUntilTime - check the box to enable")

global timeClusterServerAttributeClusterRevision
timeClusterServerAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("TC_CLUSTERREVISION", timeClusterServerAttributes)
timeClusterServerAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
timeClusterServerAttributeClusterRevision.setDefaultValue(True)
timeClusterServerAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
timeClusterServerAttributeClusterRevision.setReadOnly(True)

global timeClusterServerAttributeCount
timeClusterServerAttributeCount = drvZigbeeComponent.createIntegerSymbol("TC_SERVERATTRIBUTECOUNT", timeClusterServerAttributes)
timeClusterServerAttributeCount.setLabel("Attributes Count")
timeClusterServerAttributeCount.setDefaultValue(timeClusterServerAttributeCountUpdate(0,0))
timeClusterServerAttributeCount.setVisible(True)
timeClusterServerAttributeCount.setDescription("Attributes Count")
timeClusterServerAttributeCount.setReadOnly(True)
timeClusterServerAttributeCount.setDependencies(timeClusterServerAttributeCountUpdate,["TC_TIME","TC_TIMESTATUS","TC_TIMEZONE","TC_DSTSTART","TC_DSTEND","TC_DSTSHIFT","TC_STDTIME","TC_LOCALTIME","TC_LASTSETTIME","TC_VALIDUNTILTIME","TC_CLUSTERREVISION"])

#################               Server Commands                                 ###############

# Commands received
# The server receives no commands

# Commands generated
# The server generates no cluster specific commands.

#################               Client Attributes                                 ###############
global timeClusterClientAttributeClusterRevision
timeClusterClientAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("TCC_CLUSTERREVISION", timeClusterClientAttributes)
timeClusterClientAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
timeClusterClientAttributeClusterRevision.setDefaultValue(True)
timeClusterClientAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
timeClusterClientAttributeClusterRevision.setReadOnly(True)

global timeClusterClientAttributeCount
timeClusterClientAttributeCount = drvZigbeeComponent.createIntegerSymbol("TCC_CLIENTATTRIBUTECOUNT", timeClusterClientAttributes)
timeClusterClientAttributeCount.setLabel("Attributes Count")
timeClusterClientAttributeCount.setDefaultValue(timeClusterClientAttributeCountUpdate(0,0))
timeClusterClientAttributeCount.setVisible(True)
timeClusterClientAttributeCount.setDescription("Attributes Count")
timeClusterClientAttributeCount.setReadOnly(True)
timeClusterClientAttributeCount.setDependencies(timeClusterClientAttributeCountUpdate,["TCC_CLUSTERREVISION"])

#################               Client Commands                                 ###############

# Commands received
# The Client receives no commands

# Commands generated
# The Client generates no cluster specific commands.

############################################################################################################
# Default Values Settings based on device type
timeClusterHandling()

############################################################################################################
##################################### FTL Files Definitions ################################################
############################################################################################################

# TIME CLUSTER Common header
timeClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_TIME_CLUSTER_CONF", None)
timeClusterConf.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/time/zclTimeCluster.h.ftl")
timeClusterConf.setOutputName("zclTimeCluster.h")
timeClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
timeClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
timeClusterConf.setType("HEADER")
timeClusterConf.setOverwrite(True)
timeClusterConf.setMarkup(True)

# TIME CLUSTER - Combined Interface
timeClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_TIME_CLUSTER_CONF_SRC_CI", None)
timeClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/time/ciTimeCluster.c.ftl")
timeClusterConfSrc.setOutputName("ciTimeCluster.c")
timeClusterConfSrc.setDestPath("/zigbee/z3device/combinedInterface")
timeClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/combinedInterface/")
timeClusterConfSrc.setType("SOURCE")
timeClusterConfSrc.setOverwrite(True)
timeClusterConfSrc.setMarkup(True)
timeClusterConfSrc.setEnabled(checkDevTypeCombInterface)

# TIME CLUSTER - Thermostat
timeClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_TIME_CLUSTER_CONF_SRC_TH", None)
timeClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/time/thTimeCluster.c.ftl")
timeClusterConfSrc.setOutputName("thTimeCluster.c")
timeClusterConfSrc.setDestPath("/zigbee/z3device/thermostat")
timeClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/thermostat/")
timeClusterConfSrc.setType("SOURCE")
timeClusterConfSrc.setOverwrite(True)
timeClusterConfSrc.setMarkup(True)
timeClusterConfSrc.setEnabled(checkDevTypeThermostat)

# TIME CLUSTER - Custom
timeClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_TIME_CLUSTER_CONF_SRC_CUSTOM", None)
timeClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/time/customTimeCluster.c.ftl")
timeClusterConfSrc.setOutputName("customTimeCluster.c")
timeClusterConfSrc.setDestPath("/zigbee/z3device/custom")
timeClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/custom/")
timeClusterConfSrc.setType("SOURCE")
timeClusterConfSrc.setOverwrite(True)
timeClusterConfSrc.setMarkup(True)
timeClusterConfSrc.setEnabled(checkDevTypeCustom and timeCluster.getValue())
timeClusterConfSrc.setDependencies(customTimeClusterEnableCheck,["TIME_CLUSTER_ENABLE"])
############################################################################################################
