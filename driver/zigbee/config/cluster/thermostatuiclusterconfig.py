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
#####################################  THERMOSTAT USER INTERFACE CLUSTER CONFIGURATION   ###################
############################################################################################################

############################################################################################################
############################################# Function Definitions #########################################
############################################################################################################
def thermostatUIClusterCsCheck(symbol, event):
    if (thermostatUICluster.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def thermostatUIClusterEnableCheck(symbol, event):
    if (thermostatUICluster.getValue() == False):
        symbol.setEnabled(False)
    else:
        symbol.setEnabled(True)

def customThermostatUIClusterEnableCheck(symbol, event):
    if ((zigbeeDeviceType.getValue() == 'ZIGBEE_CUSTOM') and (thermostatUICluster.getValue() == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def thermostatUIClusterClientCheck(symbol, event):
    if ((thermostatUICluster.getValue() == False) or thermostatUIClusterCS.getValue() == "SERVER"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def thermostatUIClusterServerCheck(symbol, event):
    if ((thermostatUICluster.getValue() == False) or thermostatUIClusterCS.getValue() == "CLIENT"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def thermostatUIClusterHandling():

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
        thermostatUICluster.setVisible(False)
        thermostatUICluster.setValue(False)
    elif ((getDevice == "ZIGBEE_COMBINED_INTERFACE")):
        thermostatUICluster.setVisible(True)
        thermostatUICluster.setValue(True)
        thermostatUICluster.setReadOnly(True)
        thermostatUIClusterCS.setValue("CLIENT")
        thermostatUIClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_THERMOSTAT")):
        thermostatUICluster.setVisible(True)
        thermostatUICluster.setValue(True)
        thermostatUICluster.setReadOnly(True)
        thermostatUIClusterCS.setValue("SERVER")
        thermostatUIClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_CUSTOM")):
        thermostatUICluster.setVisible(True)
        thermostatUICluster.setValue(False)
        thermostatUIClusterCS.setValue("BOTH")
    else:
        thermostatUICluster.setVisible(False)

def thermostatUIClusterServerAttributeCountUpdate(symbol, event):
    count = 0
    if (thermostatUIClusterServerAttributeTemperatureDisplayMode.getValue()):
        count += 1
    if (thermostatUIClusterServerAttributeKeypadLockout.getValue()):
        count += 1
    if (thermostatUIClusterServerAttributeScheduleProgrammingVisibility.getValue()):
        count += 1
    if (thermostatUIClusterServerAttributeClusterRevision.getValue()):
        count += 1
    thermostatUIClusterServerAttributeCount.setValue(count) 
    return count

def thermostatUIClusterClientAttributeCountUpdate(symbol, event):
    count = 0
    if (thermostatUIClusterClientAttributeClusterRevision.getValue()):
        count += 1
    thermostatUIClusterClientAttributeCount.setValue(count)
    return count
############################################################################################################
##################################### Configuration Item Definitions #######################################
############################################################################################################

global thermostatUICluster
thermostatUICluster = drvZigbeeComponent.createBooleanSymbol("THERMOSTATUI_CLUSTER_ENABLE", clusterConfigMenu)
thermostatUICluster.setLabel("0x0204 Thermostat User Interface Configuration Cluster")
thermostatUICluster.setDefaultValue(False)
thermostatUICluster.setVisible(False)
thermostatUICluster.setDescription("THERMOSTAT UI CLUSTER- check the box to enable")
thermostatUICluster.setReadOnly(False)

global thermostatUIClusterCS
thermostatUIClusterCS = drvZigbeeComponent.createComboSymbol("THERMOSTATUI_CLUSTER_CS",  thermostatUICluster, ["CLIENT","SERVER", "BOTH"])
thermostatUIClusterCS.setLabel("Supported Implementation")
thermostatUIClusterCS.setDefaultValue("BOTH")
#thermostatUIClusterCS.setVisible(False)
thermostatUIClusterCS.setDescription("Thermostat UI Cluster Supported Implementation- Select the option")
thermostatUIClusterCS.setDependencies(thermostatUIClusterCsCheck,["THERMOSTATUI_CLUSTER_ENABLE"])

thermostatUIClusterClientMenu = drvZigbeeComponent.createMenuSymbol("THERMOSTATUI_CLUSTER_CLIENT_MENU", thermostatUICluster)
thermostatUIClusterClientMenu.setLabel("Client")
#thermostatUIClusterClientMenu.setVisible(False)
thermostatUIClusterClientMenu.setDescription("THERMOSTAT UI CLUSTER CLIENT")
thermostatUIClusterClientMenu.setDependencies(thermostatUIClusterClientCheck,["THERMOSTATUI_CLUSTER_CS","THERMOSTATUI_CLUSTER_ENABLE"])

thermostatUIClusterServerMenu = drvZigbeeComponent.createMenuSymbol("THERMOSTATUI_CLUSTER_SERVER_MENU", thermostatUICluster)
thermostatUIClusterServerMenu.setLabel("Server")
#thermostatUIClusterServerMenu.setVisible(False)
thermostatUIClusterServerMenu.setDescription("THERMOSTAT UI CLUSTER SERVER")
thermostatUIClusterServerMenu.setDependencies(thermostatUIClusterServerCheck,["THERMOSTATUI_CLUSTER_CS","THERMOSTATUI_CLUSTER_ENABLE"])

thermostatUIClusterClientAttributes = drvZigbeeComponent.createMenuSymbol("THERMOSTATUI_CLUSTER_CLIENT__ATTRIBUTES_MENU", thermostatUIClusterClientMenu)
thermostatUIClusterClientAttributes.setLabel("Attributes")
#thermostatUIClusterClientAttributes.setVisible(False)
thermostatUIClusterClientAttributes.setDescription("THERMOSTAT UI CLUSTER CLIENT ATTRIBUTES")
thermostatUIClusterClientAttributes.setDependencies(thermostatUIClusterClientCheck,["THERMOSTATUI_CLUSTER_CS"])

# thermostatUIClusterClientCommands = drvZigbeeComponent.createMenuSymbol("THERMOSTATUI_CLUSTER_CLIENT__COMMANDS_MENU", thermostatUIClusterClientMenu)
# thermostatUIClusterClientCommands.setLabel("Commands")
# #thermostatUIClusterClientCommands.setVisible(False)
# thermostatUIClusterClientCommands.setDescription("THERMOSTAT UI CLUSTER CLIENT COMMANDS")
# thermostatUIClusterClientCommands.setDependencies(thermostatUIClusterClientCheck,["THERMOSTATUI_CLUSTER_CS"])

thermostatUIClusterServerAttributes = drvZigbeeComponent.createMenuSymbol("THERMOSTATUI_CLUSTER_SERVER__ATTRIBUTES_MENU", thermostatUIClusterServerMenu)
thermostatUIClusterServerAttributes.setLabel("Attributes")
# #thermostatUIClusterServerAttributes.setVisible(False)
thermostatUIClusterServerAttributes.setDescription("THERMOSTAT UI CLUSTER SERVER ATTRIBUTES")
thermostatUIClusterServerAttributes.setDependencies(thermostatUIClusterServerCheck,["THERMOSTATUI_CLUSTER_CS"])

# thermostatUIClusterServerCommands = drvZigbeeComponent.createMenuSymbol("THERMOSTATUI_CLUSTER_SERVER__COMMANDS_MENU", thermostatUIClusterServerMenu)
# thermostatUIClusterServerCommands.setLabel("Commands")
# #thermostatUIClusterServerCommands.setVisible(False)
# thermostatUIClusterServerCommands.setDescription("THERMOSTAT UI CLUSTER SERVER COMMANDS")
# thermostatUIClusterServerCommands.setDependencies(thermostatUIClusterServerCheck,["THERMOSTATUI_CLUSTER_CS"])

#################               Server Attributes                                 ###############

## Thermostat UI Information Attribute Set
global thermostatUIClusterServerAttributeTemperatureDisplayMode
thermostatUIClusterServerAttributeTemperatureDisplayMode = drvZigbeeComponent.createBooleanSymbol("TUIC_TEMPDISPLAYMODE", thermostatUIClusterServerAttributes)
thermostatUIClusterServerAttributeTemperatureDisplayMode.setLabel("0x0000 TemperatureDisplayMode")
thermostatUIClusterServerAttributeTemperatureDisplayMode.setDefaultValue(True)
thermostatUIClusterServerAttributeTemperatureDisplayMode.setDescription("TemperatureDisplayMode - check the box to enable")
thermostatUIClusterServerAttributeTemperatureDisplayMode.setReadOnly(True)

global thermostatUIClusterServerAttributeKeypadLockout
thermostatUIClusterServerAttributeKeypadLockout = drvZigbeeComponent.createBooleanSymbol("TUIC_KEYPADLOCKOUT", thermostatUIClusterServerAttributes)
thermostatUIClusterServerAttributeKeypadLockout.setLabel("0x0001 KeypadLockout")
thermostatUIClusterServerAttributeKeypadLockout.setDefaultValue(True)
thermostatUIClusterServerAttributeKeypadLockout.setDescription("KeypadLockout - check the box to enable")
thermostatUIClusterServerAttributeKeypadLockout.setReadOnly(True)

global thermostatUIClusterServerAttributeScheduleProgrammingVisibility
thermostatUIClusterServerAttributeScheduleProgrammingVisibility = drvZigbeeComponent.createBooleanSymbol("TUIC_SCHEDULEPROGRAMVISIBILITY", thermostatUIClusterServerAttributes)
thermostatUIClusterServerAttributeScheduleProgrammingVisibility.setLabel("0x0002 ScheduleProgrammingVisibility")
thermostatUIClusterServerAttributeScheduleProgrammingVisibility.setDefaultValue(True)
thermostatUIClusterServerAttributeScheduleProgrammingVisibility.setDescription("ScheduleProgrammingVisibility - check the box to enable")

## Global attributes
global thermostatUIClusterServerAttributeClusterRevision
thermostatUIClusterServerAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("TUIC_CLUSTERREVISION", thermostatUIClusterServerAttributes)
thermostatUIClusterServerAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
thermostatUIClusterServerAttributeClusterRevision.setDefaultValue(True)
thermostatUIClusterServerAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
thermostatUIClusterServerAttributeClusterRevision.setReadOnly(True)

global thermostatUIClusterServerAttributeCount
thermostatUIClusterServerAttributeCount = drvZigbeeComponent.createIntegerSymbol("TUIC_SERVERATTRIBUTECOUNT", thermostatUIClusterServerAttributes)
thermostatUIClusterServerAttributeCount.setLabel("Attributes Count")
thermostatUIClusterServerAttributeCount.setDefaultValue(thermostatUIClusterServerAttributeCountUpdate(0,0))
thermostatUIClusterServerAttributeCount.setVisible(True)
thermostatUIClusterServerAttributeCount.setDescription("Attributes Count")
thermostatUIClusterServerAttributeCount.setReadOnly(True)
thermostatUIClusterServerAttributeCount.setDependencies(thermostatUIClusterServerAttributeCountUpdate,["TUIC_TEMPDISPLAYMODE","TUIC_KEYPADLOCKOUT","TUIC_SCHEDULEPROGRAMVISIBILITY","TUIC_CLUSTERREVISION"])
#################               Server Commands                                 ###############

# Commands received
# There are no server Specific commands received

# Commands generated
# There are no server Specific commands generated

#################               Client Attributes                                 ###############
global thermostatUIClusterClientAttributeClusterRevision
thermostatUIClusterClientAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("TUICC_CLUSTERREVISION", thermostatUIClusterClientAttributes)
thermostatUIClusterClientAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
thermostatUIClusterClientAttributeClusterRevision.setDefaultValue(True)
thermostatUIClusterClientAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
thermostatUIClusterClientAttributeClusterRevision.setReadOnly(True)

global thermostatUIClusterClientAttributeCount
thermostatUIClusterClientAttributeCount = drvZigbeeComponent.createIntegerSymbol("TUICC_CLIENTATTRIBUTECOUNT", thermostatUIClusterClientAttributes)
thermostatUIClusterClientAttributeCount.setLabel("Attributes Count")
thermostatUIClusterClientAttributeCount.setDefaultValue(thermostatUIClusterClientAttributeCountUpdate(0,0))
thermostatUIClusterClientAttributeCount.setVisible(True)
thermostatUIClusterClientAttributeCount.setDescription("Attributes Count")
thermostatUIClusterClientAttributeCount.setReadOnly(True)
thermostatUIClusterClientAttributeCount.setDependencies(thermostatUIClusterClientAttributeCountUpdate,["TUICC_CLUSTERREVISION"])

#################               Client Commands                                 ###############

# Commands generated
# There are no client Specific commands generated

# Commands received
# There are no client Specific commands received


############################################################################################################
# Default Values Settings based on device type
thermostatUIClusterHandling()

############################################################################################################
##################################### FTL Files Definitions ################################################
############################################################################################################

# THERMOSTAT UI CLUSTER Common header
thermostatUIClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_THERMOSTATUI_CLUSTER_CONF", None)
thermostatUIClusterConf.setSourcePath("/driver/zigbee/templates/cluster/thermostatuiconfig/zclThermostatUiConfCluster.h.ftl")
thermostatUIClusterConf.setOutputName("zclThermostatUiConfCluster.h")
thermostatUIClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
thermostatUIClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
thermostatUIClusterConf.setType("HEADER")
thermostatUIClusterConf.setOverwrite(True)
thermostatUIClusterConf.setMarkup(True)

# THERMOSTAT UI CLUSTER - Combined Interface
thermostatClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_THERMOSTATUI_CLUSTER_CONF_SRC_CI", None)
thermostatClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/thermostatuiconfig/ciThermostatUiConfCluster.c.ftl")
thermostatClusterConfSrc.setOutputName("ciThermostatUiConfCluster.c")
thermostatClusterConfSrc.setDestPath("/zigbee/z3device/combinedInterface")
thermostatClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/combinedInterface/")
thermostatClusterConfSrc.setType("SOURCE")
thermostatClusterConfSrc.setOverwrite(True)
thermostatClusterConfSrc.setMarkup(True)
thermostatClusterConfSrc.setEnabled(checkDevTypeCombInterface)

# THERMOSTAT UI CLUSTER - Thermostat
thermostatClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_THERMOSTATUI_CLUSTER_CONF_SRC_TH", None)
thermostatClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/thermostatuiconfig/thThermostatUiConfCluster.c.ftl")
thermostatClusterConfSrc.setOutputName("thThermostatUiConfCluster.c")
thermostatClusterConfSrc.setDestPath("/zigbee/z3device/thermostat")
thermostatClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/thermostat/")
thermostatClusterConfSrc.setType("SOURCE")
thermostatClusterConfSrc.setOverwrite(True)
thermostatClusterConfSrc.setMarkup(True)
thermostatClusterConfSrc.setEnabled(checkDevTypeThermostat)

# THERMOSTAT UI CLUSTER - Custom
thermostatClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_THERMOSTATUI_CLUSTER_CONF_SRC_CUSTOM", None)
thermostatClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/thermostatuiconfig/customThermostatUiConfCluster.c.ftl")
thermostatClusterConfSrc.setOutputName("customThermostatUiConfCluster.c")
thermostatClusterConfSrc.setDestPath("/zigbee/z3device/custom")
thermostatClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/custom/")
thermostatClusterConfSrc.setType("SOURCE")
thermostatClusterConfSrc.setOverwrite(True)
thermostatClusterConfSrc.setMarkup(True)
thermostatClusterConfSrc.setEnabled(checkDevTypeCustom and thermostatUICluster.getValue())
thermostatClusterConfSrc.setDependencies(customThermostatUIClusterEnableCheck,["THERMOSTATUI_CLUSTER_ENABLE"])
############################################################################################################
