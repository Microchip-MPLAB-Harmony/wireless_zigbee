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
###########################################  ONOFF CLUSTER CONFIGURATION  ##################################
############################################################################################################

############################################################################################################
############################################# Function Definitions #########################################
############################################################################################################

def OnOffClusterCsCheck(symbol, event):
    if (OnOffCluster.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def OnOffClusterEnableCheck(symbol, event):
    if (OnOffCluster.getValue() == False):
        symbol.setEnabled(False)
    else:
        symbol.setEnabled(True)

def customOnOffClusterEnableCheck(symbol, event):
    if ((zigbeeDeviceType.getValue() == 'ZIGBEE_CUSTOM') and (OnOffCluster.getValue() == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def OnOffClusterClientCheck(symbol, event):
    if ((OnOffCluster.getValue() == False) or OnOffClusterCS.getValue() == "SERVER"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def OnOffClusterServerCheck(symbol, event):
    if ((OnOffCluster.getValue() == False) or OnOffClusterCS.getValue() == "CLIENT"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def onOffClusterHandling():

    getDevice = zigbeeDeviceType.getValue()

    if ((getDevice == "ZIGBEE_COLOR_SCENE_CONTROLLER")
        or (getDevice == "ZIGBEE_COMBINED_INTERFACE")
        or (getDevice == "ZIGBEE_CONTROL_BRIDGE")
        ):
        OnOffCluster.setVisible(True)
        OnOffCluster.setValue(True)
        OnOffCluster.setReadOnly(True)
        OnOffClusterCS.setValue("CLIENT")
        OnOffClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_MULTI_SENSOR") 
          or (getDevice == "ZIGBEE_THERMOSTAT")
          or (getDevice == "ZIGBEE_IAS_ACE")
          ):
        OnOffCluster.setVisible(False)
        OnOffCluster.setValue(False)
    elif ((getDevice == "ZIGBEE_ON_OFF_LIGHT")
            or (getDevice == "ZIGBEE_DIMMABLE_LIGHT")
            or (getDevice == "ZIGBEE_COLOR_LIGHT")
            or (getDevice == "ZIGBEE_EXTENDED_COLOR_LIGHT")
            or (getDevice == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")
        ):
        OnOffCluster.setVisible(True)
        OnOffCluster.setValue(True)
        OnOffCluster.setReadOnly(True)
        OnOffClusterCS.setValue("SERVER")
        OnOffClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_CUSTOM")):
        OnOffCluster.setVisible(True)
        OnOffCluster.setValue(True)
        OnOffClusterCS.setValue("BOTH")
    else:
        OnOffCluster.setVisible(False)

def OnOffClusterServerAttributeCountUpdate(symbol, event):
    count = 0
    if (OnOffClusterServerAttributeOnOff.getValue()):
        count += 1
    if (OnOffClusterServerAttributeGlobalSControl.getValue()):
        count += 1	
    if (OnOffClusterServerAttributeOnTime.getValue()):
        count += 1
    if (OnOffClusterServerAttributeOffWaitTime.getValue()):
        count += 1	
    if (OnOffClusterServerAttributeStartUpOnOff.getValue()):
        count += 1
    if (OnOffClusterServerAttributeClusterRevision.getValue()):
        count += 1
    OnOffClusterServerAttributeCount.setValue(count) 
    return count

def OnOffClusterServerCommandCountUpdate(symbol, event):
    count = 0
    if (OnOffClusterServerCmdOff.getValue()):
        count += 1
    if (OnOffClusterServerCmdOn.getValue()):
        count += 1	
    if (OnOffClusterServerCmdToggle.getValue()):
        count += 1
    if (OnOffClusterServerCmdOffWithEffect.getValue()):
        count += 1
    if (OnOffClusterServerCmdOnWithRecall.getValue()):
        count += 1
    if (OnOffClusterServerCmdOnWithTimedOff.getValue()):
        count += 1
    OnOffClusterServerCommandCount.setValue(count)
    return count

def OnOffClusterClientAttributeCountUpdate(symbol, event):
    count = 0
    if (OnOffClusterClientAttributeClusterRevision.getValue()):
        count += 1
    OnOffClusterClientAttributeCount.setValue(count)
    return count

def OnOffClusterClientCommandCountUpdate(symbol, event):
    count = 0
    if (OnOffClusterClientCmdOff.getValue()):
        count += 1
    if (OnOffClusterClientCmdOn.getValue()):
        count += 1
    if (OnOffClusterClientCmdToggle.getValue()):
        count += 1
    if (OnOffClusterClientCmdOffWithEffect.getValue()):
        count += 1
    if (OnOffClusterClientCmdOnWithRecall.getValue()):
        count += 1
    if (OnOffClusterClientCmdOnWithTimedOff.getValue()):
        count += 1
    OnOffClusterClientCommandCount.setValue(count)
    return count

def LevelControlClusterEnabledCheck(symbol, event):
    if (event["value"] == True):
        symbol.setValue(True)
        symbol.setVisible(True)
        symbol.setEnabled(True)

def ColorControlClusterEnabledCheck(symbol, event):
    if (event["value"] == True):
        symbol.setValue(True)
        symbol.setVisible(True)
        symbol.setEnabled(True)

############################################################################################################
##################################### Configuration Item Definitions #######################################
############################################################################################################

global OnOffCluster
OnOffCluster = drvZigbeeComponent.createBooleanSymbol("ONOFF_CLUSTER_ENABLE", clusterConfigMenu)
OnOffCluster.setLabel("0x0006 OnOff Cluster")
OnOffCluster.setDefaultValue(False)
OnOffCluster.setVisible(False)
OnOffCluster.setDescription("ONOFF CLUSTER- check the box to enable")
OnOffCluster.setDependencies(LevelControlClusterEnabledCheck,["LEVELCONTROL_CLUSTER_ENABLE"])
OnOffCluster.setDependencies(ColorControlClusterEnabledCheck,["COLORCONTROL_CLUSTER_ENABLE"])

global OnOffClusterCS
OnOffClusterCS = drvZigbeeComponent.createComboSymbol("ONOFF_CLUSTER_CS",  OnOffCluster, ["CLIENT","SERVER", "BOTH"])
OnOffClusterCS.setLabel("Supported Implementation")
OnOffClusterCS.setDefaultValue("")
OnOffClusterCS.setVisible(False)
OnOffClusterCS.setDescription("ONOFF CLUSTER Supported Implementation- check the box to enable")
OnOffClusterCS.setDependencies(OnOffClusterCsCheck,["ONOFF_CLUSTER_ENABLE"])

OnOffClusterClientMenu = drvZigbeeComponent.createMenuSymbol("ONOFF_CLUSTER_CLIENT_MENU", OnOffCluster)
OnOffClusterClientMenu.setLabel("Client")
OnOffClusterClientMenu.setVisible(False)
OnOffClusterClientMenu.setDescription("ONOFF CLUSTER CLIENT")
OnOffClusterClientMenu.setDependencies(OnOffClusterClientCheck,["ONOFF_CLUSTER_CS","ONOFF_CLUSTER_ENABLE"])

OnOffClusterServerMenu = drvZigbeeComponent.createMenuSymbol("ONOFF_CLUSTER_SERVER_MENU", OnOffCluster)
OnOffClusterServerMenu.setLabel("Server")
OnOffClusterServerMenu.setVisible(False)
OnOffClusterServerMenu.setDescription("ONOFF CLUSTER SERVER")
OnOffClusterServerMenu.setDependencies(OnOffClusterServerCheck,["ONOFF_CLUSTER_CS","ONOFF_CLUSTER_ENABLE"])

OnOffClusterClientAttributes = drvZigbeeComponent.createMenuSymbol("ONOFF_CLUSTER_CLIENT__ATTRIBUTES_MENU", OnOffClusterClientMenu)
OnOffClusterClientAttributes.setLabel("Attributes")
#OnOffClusterClientAttributes.setVisible(False)
OnOffClusterClientAttributes.setDescription("ONOFF CLUSTER CLIENT ATTRIBUTES")
OnOffClusterClientAttributes.setDependencies(OnOffClusterClientCheck,["ONOFF_CLUSTER_CS"])

OnOffClusterClientCommands = drvZigbeeComponent.createMenuSymbol("ONOFF_CLUSTER_CLIENT__COMMANDS_MENU", OnOffClusterClientMenu)
OnOffClusterClientCommands.setLabel("Commands")
#OnOffClusterClientCommands.setVisible(False)
OnOffClusterClientCommands.setDescription("ONOFF CLUSTER CLIENT COMMANDS")
OnOffClusterClientCommands.setDependencies(OnOffClusterClientCheck,["ONOFF_CLUSTER_CS"])

OnOffClusterServerAttributes = drvZigbeeComponent.createMenuSymbol("ONOFF_CLUSTER_SERVER__ATTRIBUTES_MENU", OnOffClusterServerMenu)
OnOffClusterServerAttributes.setLabel("Attributes")
#OnOffClusterServerAttributes.setVisible(False)
OnOffClusterServerAttributes.setDescription("ONOFF CLUSTER SERVER ATTRIBUTES")
OnOffClusterServerAttributes.setDependencies(OnOffClusterServerCheck,["ONOFF_CLUSTER_CS"])

OnOffClusterServerCommands = drvZigbeeComponent.createMenuSymbol("ONOFF_CLUSTER_SERVER__COMMANDS_MENU", OnOffClusterServerMenu)
OnOffClusterServerCommands.setLabel("Commands")
#OnOffClusterServerCommands.setVisible(False)
OnOffClusterServerCommands.setDescription("ONOFF CLUSTER SERVER COMMANDS")
OnOffClusterServerCommands.setDependencies(OnOffClusterServerCheck,["ONOFF_CLUSTER_CS"])

#################               Server Attributes                                 ###############

global OnOffClusterServerAttributeOnOff
OnOffClusterServerAttributeOnOff = drvZigbeeComponent.createBooleanSymbol("OC_ONOFF", OnOffClusterServerAttributes)
OnOffClusterServerAttributeOnOff.setLabel("0x0000 OnOff")
OnOffClusterServerAttributeOnOff.setDefaultValue(True)
OnOffClusterServerAttributeOnOff.setReadOnly(True)

global OnOffClusterServerAttributeGlobalSControl
OnOffClusterServerAttributeGlobalSControl = drvZigbeeComponent.createBooleanSymbol("OC_GLOBALSCENECONTROL", OnOffClusterServerAttributes)
OnOffClusterServerAttributeGlobalSControl.setLabel("0x4000 GlobalSceneControl")
OnOffClusterServerAttributeGlobalSControl.setDefaultValue(True)

global OnOffClusterServerAttributeOnTime
OnOffClusterServerAttributeOnTime = drvZigbeeComponent.createBooleanSymbol("OC_ONTIME", OnOffClusterServerAttributes)
OnOffClusterServerAttributeOnTime.setLabel("0x4001 OnTime")
OnOffClusterServerAttributeOnTime.setDefaultValue(True)

global OnOffClusterServerAttributeOffWaitTime
OnOffClusterServerAttributeOffWaitTime = drvZigbeeComponent.createBooleanSymbol("OC_OFFWAITTIME", OnOffClusterServerAttributes)
OnOffClusterServerAttributeOffWaitTime.setLabel("0x4002 OffWaitTime")
OnOffClusterServerAttributeOffWaitTime.setDefaultValue(True)

global OnOffClusterServerAttributeStartUpOnOff 
OnOffClusterServerAttributeStartUpOnOff = drvZigbeeComponent.createBooleanSymbol("OC_STARTUPONOFF", OnOffClusterServerAttributes)
OnOffClusterServerAttributeStartUpOnOff.setLabel("0x4003 StartUpOnOff")
OnOffClusterServerAttributeStartUpOnOff.setDefaultValue(True)

global OnOffClusterServerAttributeClusterRevision
OnOffClusterServerAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("OC_CLUSTERREVISION", OnOffClusterServerAttributes)
OnOffClusterServerAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
OnOffClusterServerAttributeClusterRevision.setDefaultValue(True)
OnOffClusterServerAttributeClusterRevision.setReadOnly(True)

global OnOffClusterServerAttributeCount
OnOffClusterServerAttributeCount = drvZigbeeComponent.createIntegerSymbol("OC_SERVERATTRIBUTECOUNT", OnOffClusterServerAttributes)
OnOffClusterServerAttributeCount.setLabel("Attributes Count")
OnOffClusterServerAttributeCount.setDefaultValue(OnOffClusterServerAttributeCountUpdate(0,0))
OnOffClusterServerAttributeCount.setVisible(True)
OnOffClusterServerAttributeCount.setDescription("Attributes Count")
OnOffClusterServerAttributeCount.setReadOnly(True)
OnOffClusterServerAttributeCount.setDependencies(OnOffClusterServerAttributeCountUpdate,["OC_CLUSTERREVISION","OC_STARTUPONOFF","OC_OFFWAITTIME","OC_ONTIME","OC_GLOBALSCENECONTROL","OC_ONOFF"])

#################               Server Commands                                 ###############

# Commands received
global OnOffClusterServerCmdOff
OnOffClusterServerCmdOff = drvZigbeeComponent.createBooleanSymbol("OC_OFF", OnOffClusterServerCommands)
OnOffClusterServerCmdOff.setLabel("0x00.Rx Off")
OnOffClusterServerCmdOff.setDefaultValue(True)
OnOffClusterServerCmdOff.setDescription("Receive Off command - check the box to enable")
OnOffClusterServerCmdOff.setReadOnly(True)

global OnOffClusterServerCmdOn
OnOffClusterServerCmdOn = drvZigbeeComponent.createBooleanSymbol("OC_ON", OnOffClusterServerCommands)
OnOffClusterServerCmdOn.setLabel("0x01.Rx On")
OnOffClusterServerCmdOn.setDefaultValue(True)
OnOffClusterServerCmdOn.setDescription("Receive On command - check the box to enable")
OnOffClusterServerCmdOn.setReadOnly(True)

global OnOffClusterServerCmdToggle
OnOffClusterServerCmdToggle = drvZigbeeComponent.createBooleanSymbol("OC_TOGGLE", OnOffClusterServerCommands)
OnOffClusterServerCmdToggle.setLabel("0x02.Rx Toggle")
OnOffClusterServerCmdToggle.setDefaultValue(True)
OnOffClusterServerCmdToggle.setDescription("Receive Toggle command - check the box to enable")
OnOffClusterServerCmdToggle.setReadOnly(True)

global OnOffClusterServerCmdOffWithEffect
OnOffClusterServerCmdOffWithEffect = drvZigbeeComponent.createBooleanSymbol("OC_OFFWITHEFFECT", OnOffClusterServerCommands)
OnOffClusterServerCmdOffWithEffect.setLabel("0x40.Rx Off with effect")
OnOffClusterServerCmdOffWithEffect.setDefaultValue(True)
OnOffClusterServerCmdOffWithEffect.setDescription("Receive Off with effect command - check the box to enable")

global OnOffClusterServerCmdOnWithRecall
OnOffClusterServerCmdOnWithRecall = drvZigbeeComponent.createBooleanSymbol("OC_ONWITHRECALL", OnOffClusterServerCommands)
OnOffClusterServerCmdOnWithRecall.setLabel("0x41.Rx On with recall global scene")
OnOffClusterServerCmdOnWithRecall.setDefaultValue(True)
OnOffClusterServerCmdOnWithRecall.setDescription("Receive On with recall global scene command - check the box to enable")

global OnOffClusterServerCmdOnWithTimedOff
OnOffClusterServerCmdOnWithTimedOff = drvZigbeeComponent.createBooleanSymbol("OC_ONWITHTIMEDOFF", OnOffClusterServerCommands)
OnOffClusterServerCmdOnWithTimedOff.setLabel("0x42.Rx On with timed off")
OnOffClusterServerCmdOnWithTimedOff.setDefaultValue(True)
OnOffClusterServerCmdOnWithTimedOff.setDescription("Receive On with timed off command - check the box to enable")

global OnOffClusterServerCommandCount
OnOffClusterServerCommandCount = drvZigbeeComponent.createIntegerSymbol("OC_SERVERCOMMANDCOUNT", OnOffClusterServerCommands)
OnOffClusterServerCommandCount.setLabel("Commands Count")
OnOffClusterServerCommandCount.setDefaultValue(OnOffClusterServerCommandCountUpdate(0,0))
OnOffClusterServerCommandCount.setVisible(True)
OnOffClusterServerCommandCount.setDescription("Commands Count")
OnOffClusterServerCommandCount.setReadOnly(True)
OnOffClusterServerCommandCount.setDependencies(OnOffClusterServerCommandCountUpdate, ["OC_ONWITHTIMEDOFF", "OC_ONWITHRECALL", "OC_OFFWITHEFFECT", "OC_TOGGLE", "OC_ON", "OC_OFF"])

#################               Client Attributes                               ###############

global OnOffClusterClientAttributeClusterRevision
OnOffClusterClientAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("OCC_CLUSTERREVISION", OnOffClusterClientAttributes)
OnOffClusterClientAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
OnOffClusterClientAttributeClusterRevision.setDefaultValue(True)
OnOffClusterClientAttributeClusterRevision.setReadOnly(True)

global OnOffClusterClientAttributeCount
OnOffClusterClientAttributeCount = drvZigbeeComponent.createIntegerSymbol("OCC_CLIENTATTRIBUTECOUNT", OnOffClusterClientAttributes)
OnOffClusterClientAttributeCount.setLabel("Attributes Count")
OnOffClusterClientAttributeCount.setDefaultValue(OnOffClusterClientAttributeCountUpdate(0,0))
OnOffClusterClientAttributeCount.setVisible(True)
OnOffClusterClientAttributeCount.setDescription("Attributes Count")
OnOffClusterClientAttributeCount.setReadOnly(True)
OnOffClusterClientAttributeCount.setDependencies(OnOffClusterClientAttributeCountUpdate,["OCC_CLUSTERREVISION"])

#################               Client Commands                                 ###############

# Commands generated
global OnOffClusterClientCmdOff
OnOffClusterClientCmdOff = drvZigbeeComponent.createBooleanSymbol("OCC_OFF", OnOffClusterClientCommands)
OnOffClusterClientCmdOff.setLabel("0x00.Tx Off")
OnOffClusterClientCmdOff.setDefaultValue(True)
OnOffClusterClientCmdOff.setDescription("Send Off command - check the box to enable")

global OnOffClusterClientCmdOn
OnOffClusterClientCmdOn = drvZigbeeComponent.createBooleanSymbol("OCC_ON", OnOffClusterClientCommands)
OnOffClusterClientCmdOn.setLabel("0x01.Tx On")
OnOffClusterClientCmdOn.setDefaultValue(True)
OnOffClusterClientCmdOn.setDescription("Send On command - check the box to enable")

global OnOffClusterClientCmdToggle
OnOffClusterClientCmdToggle = drvZigbeeComponent.createBooleanSymbol("OCC_TOGGLE", OnOffClusterClientCommands)
OnOffClusterClientCmdToggle.setLabel("0x02.Tx Toggle")
OnOffClusterClientCmdToggle.setDefaultValue(True)
OnOffClusterClientCmdToggle.setDescription("Send Toggle command - check the box to enable")

global OnOffClusterClientCmdOffWithEffect
OnOffClusterClientCmdOffWithEffect = drvZigbeeComponent.createBooleanSymbol("OCC_OFFWITHEFFECT", OnOffClusterClientCommands)
OnOffClusterClientCmdOffWithEffect.setLabel("0x40.Tx Off with effect")
OnOffClusterClientCmdOffWithEffect.setDefaultValue(True)
OnOffClusterClientCmdOffWithEffect.setDescription("Send Off with effect command - check the box to enable")

global OnOffClusterClientCmdOnWithRecall
OnOffClusterClientCmdOnWithRecall = drvZigbeeComponent.createBooleanSymbol("OCC_ONWITHRECALL", OnOffClusterClientCommands)
OnOffClusterClientCmdOnWithRecall.setLabel("0x41.Tx On with recall global scene")
OnOffClusterClientCmdOnWithRecall.setDefaultValue(True)
OnOffClusterClientCmdOnWithRecall.setDescription("Send On with recall global scene command - check the box to enable")

global OnOffClusterClientCmdOnWithTimedOff
OnOffClusterClientCmdOnWithTimedOff = drvZigbeeComponent.createBooleanSymbol("OCC_ONWITHTIMEDOFF", OnOffClusterClientCommands)
OnOffClusterClientCmdOnWithTimedOff.setLabel("0x42.Tx On with timed off")
OnOffClusterClientCmdOnWithTimedOff.setDefaultValue(True)
OnOffClusterClientCmdOnWithTimedOff.setDescription("Send On with timed off command - check the box to enable")

global OnOffClusterClientCommandCount
OnOffClusterClientCommandCount = drvZigbeeComponent.createIntegerSymbol("OCC_CLIENTCOMMANDCOUNT", OnOffClusterClientCommands)
OnOffClusterClientCommandCount.setLabel("Commands Count")
OnOffClusterClientCommandCount.setDefaultValue(OnOffClusterClientCommandCountUpdate(0,0))
OnOffClusterClientCommandCount.setVisible(True)
OnOffClusterClientCommandCount.setDescription("Commands Count")
OnOffClusterClientCommandCount.setReadOnly(True)
OnOffClusterClientCommandCount.setDependencies(OnOffClusterClientCommandCountUpdate,["OCC_ONWITHTIMEDOFF", "OCC_ONWITHRECALL", "OCC_OFFWITHEFFECT", "OCC_TOGGLE", "OCC_ON", "OCC_OFF"])

############################################################################################################
# Default Values Settings based on device type
onOffClusterHandling()

############################################################################################################
##################################### FTL Files Definitions ################################################
############################################################################################################

# ONOFF CLUSTER Common header
onOffClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_ONOFF_CLUSTER_CONF", None)
onOffClusterConf.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/onOff/zclOnOffCluster.h.ftl")
onOffClusterConf.setOutputName("zclOnOffCluster.h")
onOffClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
onOffClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
onOffClusterConf.setType("HEADER")
onOffClusterConf.setOverwrite(True)
onOffClusterConf.setMarkup(True)

onOffClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_ONOFF_CLUSTER_CONF2", None)
onOffClusterConf.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/onOff/zclZllOnOffCluster.h.ftl")
onOffClusterConf.setOutputName("zclZllOnOffCluster.h")
onOffClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
onOffClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
onOffClusterConf.setType("HEADER")
onOffClusterConf.setOverwrite(True)
onOffClusterConf.setMarkup(True)

onOffClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_ONOFFCLUSTER_CONF_SRC1", None)
onOffClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/onOff/onOffCluster.c.ftl")
onOffClusterConfSrc.setOutputName("onOffCluster.c")
onOffClusterConfSrc.setDestPath("/zigbee/z3device/clusters")
onOffClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/clusters/")
onOffClusterConfSrc.setType("SOURCE")
onOffClusterConfSrc.setOverwrite(True)
onOffClusterConfSrc.setMarkup(True)
onOffClusterConfSrc.setEnabled(OnOffCluster.getValue())
onOffClusterConfSrc.setDependencies(OnOffClusterEnableCheck,["ONOFF_CLUSTER_ENABLE"])

# ONOFF CLUSTER - Light
onOffClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_ONOFF_CLUSTER_CONF_SRC_LIGHT", None)
onOffClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/onOff/lightOnOffCluster.c.ftl")
onOffClusterConfSrc.setOutputName("lightOnOffCluster.c")
onOffClusterConfSrc.setDestPath("/zigbee/z3device/light")
onOffClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/light/")
onOffClusterConfSrc.setType("SOURCE")
onOffClusterConfSrc.setOverwrite(True)
onOffClusterConfSrc.setMarkup(True)
onOffClusterConfSrc.setEnabled(checkDevTypeLight)

# ONOFF CLUSTER - Custom
onOffClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_ONOFF_CLUSTER_CONF_SRC_CUSTOM", None)
onOffClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/onOff/customOnOffCluster.c.ftl")
onOffClusterConfSrc.setOutputName("customOnOffCluster.c")
onOffClusterConfSrc.setDestPath("/zigbee/z3device/custom")
onOffClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/custom/")
onOffClusterConfSrc.setType("SOURCE")
onOffClusterConfSrc.setOverwrite(True)
onOffClusterConfSrc.setMarkup(True)
onOffClusterConfSrc.setEnabled(checkDevTypeCustom and OnOffCluster.getValue())
onOffClusterConfSrc.setDependencies(customOnOffClusterEnableCheck,["ONOFF_CLUSTER_ENABLE"])

# ONOFF CLUSTER - Color Scene Controller
onOffClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_ONOFF_CLUSTER_CONF_SRC_CSC", None)
onOffClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/onOff/cscOnOffCluster.c.ftl")
onOffClusterConfSrc.setOutputName("cscOnOffCluster.c")
onOffClusterConfSrc.setDestPath("/zigbee/z3device/colorSceneController")
onOffClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/colorSceneController/")
onOffClusterConfSrc.setType("SOURCE")
onOffClusterConfSrc.setOverwrite(True)
onOffClusterConfSrc.setMarkup(True)
onOffClusterConfSrc.setEnabled(checkDevTypeRemote)

# ONOFF CLUSTER - Combined Interface
onOffClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_ONOFF_CLUSTER_CONF_SRC_CI", None)
onOffClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/onOff/ciOnOffCluster.c.ftl")
onOffClusterConfSrc.setOutputName("ciOnOffCluster.c")
onOffClusterConfSrc.setDestPath("/zigbee/z3device/combinedInterface")
onOffClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/combinedInterface/")
onOffClusterConfSrc.setType("SOURCE")
onOffClusterConfSrc.setOverwrite(True)
onOffClusterConfSrc.setMarkup(True)
onOffClusterConfSrc.setEnabled(checkDevTypeCombInterface)
############################################################################################################
