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
###########################################  LEVELCONTROL CLUSTER CONFIGURATION  ###########################
############################################################################################################

############################################################################################################
############################################# Function Definitions #########################################
############################################################################################################

def LevelControlClusterCsCheck(symbol, event):
    if (LevelControlCluster.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def LevelControlClusterEnableCheck(symbol, event):
    if (LevelControlCluster.getValue() == False):
        symbol.setEnabled(False)
    else:
        symbol.setEnabled(True)

def customLevelControlClusterEnableCheck(symbol, event):
    if ((zigbeeDeviceType.getValue() == 'ZIGBEE_CUSTOM') and (LevelControlCluster.getValue() == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def LevelControlClusterClientCheck(symbol, event):
    if ((LevelControlCluster.getValue() == False) or LevelControlClusterCS.getValue() == "SERVER"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def LevelControlClusterServerCheck(symbol, event):
    if ((LevelControlCluster.getValue() == False) or LevelControlClusterCS.getValue() == "CLIENT"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def levelControlClusterHandling():

    getDevice = zigbeeDeviceType.getValue()

    if ((getDevice == "ZIGBEE_COLOR_SCENE_CONTROLLER")
        or (getDevice == "ZIGBEE_COMBINED_INTERFACE")
        or (getDevice == "ZIGBEE_CONTROL_BRIDGE")):
        LevelControlCluster.setVisible(True)
        LevelControlCluster.setValue(True)
        LevelControlCluster.setReadOnly(True)
        LevelControlClusterCS.setValue("CLIENT")
        LevelControlClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_MULTI_SENSOR")
           or (getDevice == "ZIGBEE_THERMOSTAT")
           or (getDevice == "ZIGBEE_IAS_ACE")
           or (getDevice == "ZIGBEE_ON_OFF_LIGHT")
           ):
        LevelControlCluster.setVisible(False)
        LevelControlCluster.setValue(False)
    elif ((getDevice == "ZIGBEE_DIMMABLE_LIGHT")
           or (getDevice == "ZIGBEE_COLOR_LIGHT")
           or (getDevice == "ZIGBEE_EXTENDED_COLOR_LIGHT")
           or (getDevice == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")
           ):
        LevelControlCluster.setVisible(True)
        LevelControlCluster.setValue(True)
        LevelControlCluster.setReadOnly(True)
        LevelControlClusterCS.setValue("SERVER")
        LevelControlClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_CUSTOM")):
        LevelControlCluster.setVisible(True)
        LevelControlCluster.setValue(True)
        LevelControlClusterCS.setValue("BOTH")
    else:
        LevelControlCluster.setVisible(False)

def LevelCtrlClusterServerAttributeCountUpdate(symbol, event):
    count = 0
    if (LevelCtrlClusterServerAttributeCurrentLevel.getValue()):
        count += 1
    if (LevelCtrlClusterServerAttributeRemainingTime.getValue()):
        count += 1
    if (LevelCtrlClusterServerAttributeOptions.getValue()):
        count += 1
    # if (LevelCtrlClusterServerAttributeOnOffTransitionTime.getValue()):
        # count += 1
    # if (LevelCtrlClusterServerAttributeOnLevel.getValue()):
        # count += 1
    # if (LevelCtrlClusterServerAttributeOnTransitionTime.getValue()):
        # count += 1
    # if (LevelCtrlClusterServerAttributeOffTransitionTime.getValue()):
        # count += 1
    # if (LevelCtrlClusterServerAttributeOffDefaultMoveRate.getValue()):
        # count += 1
    if (LevelCtrlClusterServerAttributeStartUpCurrentLevel.getValue()):
        count += 1
    if (LevelCtrlClusterServerAttributeClusterRevision.getValue()):
        count += 1
    LevelCtrlClusterServerAttributeCount.setValue(count) 
    return count

def LevelCtrlClusterServerCommandCountUpdate(symbol, event):
    count = 0
    if (LevelCtrlClusterServerCmdMoveToLevel.getValue()):
        count += 1
    if (LevelCtrlClusterServerCmdMove.getValue()):
        count += 1
    if (LevelCtrlClusterServerCmdStep.getValue()):
        count += 1
    if (LevelCtrlClusterServerCmdStop.getValue()):
        count += 1	
    if (LevelCtrlClusterServerCmdMoveToLevelWithONOFF.getValue()):
        count += 1
    if (LevelCtrlClusterServerCmdMoveWithONOFF.getValue()):
        count += 1
    if (LevelCtrlClusterServerCmdStepWithONOFF.getValue()):
        count += 1
    if (LevelCtrlClusterServerCmdStopWithONOFF.getValue()):
        count += 1
    LevelCtrlClusterServerCommandCount.setValue(count)
    return count

def LevelCtrlClusterClientAttributeCountUpdate(symbol, event):
    count = 0
    if (LevelCtrlClusterClientAttributeClusterRevision.getValue()):
        count += 1
    LevelCtrlClusterClientAttributeCount.setValue(count)
    return count

def LevelCtrlClusterClientCommandCountUpdate(symbol, event):
    count = 0
    if (LevelCtrlClusterClientCmdMoveToLevel.getValue()):
        count += 1
    if (LevelCtrlClusterClientCmdMove.getValue()):
        count += 1
    if (LevelCtrlClusterClientCmdStep.getValue()):
        count += 1
    if (LevelCtrlClusterClientCmdStop.getValue()):
        count += 1	
    if (LevelCtrlClusterClientCmdMoveToLevelWithONOFF.getValue()):
        count += 1
    if (LevelCtrlClusterClientCmdMoveWithONOFF.getValue()):
        count += 1
    if (LevelCtrlClusterClientCmdStepWithONOFF.getValue()):
        count += 1
    if (LevelCtrlClusterClientCmdStopWithONOFF.getValue()):
        count += 1
    LevelCtrlClusterClientCommandCount.setValue(count)
    return count
############################################################################################################
##################################### Configuration Item Definitions #######################################
############################################################################################################

global LevelControlCluster
LevelControlCluster = drvZigbeeComponent.createBooleanSymbol("LEVELCONTROL_CLUSTER_ENABLE", clusterConfigMenu)
LevelControlCluster.setLabel("0x0008 Level Control Cluster")
LevelControlCluster.setDefaultValue(False)
LevelControlCluster.setVisible(False)
LevelControlCluster.setDescription("LEVELCONTROL CLUSTER- check the box to enable")

global LevelControlClusterCS
LevelControlClusterCS = drvZigbeeComponent.createComboSymbol("LEVELCONTROL_CLUSTER_CS",  LevelControlCluster, ["CLIENT","SERVER", "BOTH"])
LevelControlClusterCS.setLabel("Supported Implementation")
LevelControlClusterCS.setDefaultValue("")
LevelControlClusterCS.setVisible(False)
LevelControlClusterCS.setDescription("LEVELCONTROL CLUSTER Supported Implementation- check the box to enable")
LevelControlClusterCS.setDependencies(LevelControlClusterCsCheck,["LEVELCONTROL_CLUSTER_ENABLE"])

LevelControlClusterClientMenu = drvZigbeeComponent.createMenuSymbol("LEVELCONTROL_CLUSTER_CLIENT_MENU", LevelControlCluster)
LevelControlClusterClientMenu.setLabel("Client")
LevelControlClusterClientMenu.setVisible(False)
LevelControlClusterClientMenu.setDescription("LEVELCONTROL CLUSTER CLIENT")
LevelControlClusterClientMenu.setDependencies(LevelControlClusterClientCheck,["LEVELCONTROL_CLUSTER_CS","LEVELCONTROL_CLUSTER_ENABLE"])

LevelControlClusterServerMenu = drvZigbeeComponent.createMenuSymbol("LEVELCONTROL_CLUSTER_SERVER_MENU", LevelControlCluster)
LevelControlClusterServerMenu.setLabel("Server")
LevelControlClusterServerMenu.setVisible(False)
LevelControlClusterServerMenu.setDescription("LEVELCONTROL CLUSTER SERVER")
LevelControlClusterServerMenu.setDependencies(LevelControlClusterServerCheck,["LEVELCONTROL_CLUSTER_CS","LEVELCONTROL_CLUSTER_ENABLE"])

LevelControlClusterClientAttributes = drvZigbeeComponent.createMenuSymbol("LEVELCONTROL_CLUSTER_CLIENT__ATTRIBUTES_MENU", LevelControlClusterClientMenu)
LevelControlClusterClientAttributes.setLabel("Attributes")
#LevelControlClusterClientAttributes.setVisible(False)
LevelControlClusterClientAttributes.setDescription("LEVELCONTROL CLUSTER CLIENT ATTRIBUTES")
LevelControlClusterClientAttributes.setDependencies(LevelControlClusterClientCheck,["LEVELCONTROL_CLUSTER_CS"])

LevelControlClusterClientCommands = drvZigbeeComponent.createMenuSymbol("LEVELCONTROL_CLUSTER_CLIENT__COMMANDS_MENU", LevelControlClusterClientMenu)
LevelControlClusterClientCommands.setLabel("Commands")
#LevelControlClusterClientCommands.setVisible(False)
LevelControlClusterClientCommands.setDescription("LEVELCONTROL CLUSTER CLIENT COMMANDS")
LevelControlClusterClientCommands.setDependencies(LevelControlClusterClientCheck,["LEVELCONTROL_CLUSTER_CS"])

LevelControlClusterServerAttributes = drvZigbeeComponent.createMenuSymbol("LEVELCONTROL_CLUSTER_SERVER__ATTRIBUTES_MENU", LevelControlClusterServerMenu)
LevelControlClusterServerAttributes.setLabel("Attributes")
#LevelControlClusterServerAttributes.setVisible(False)
LevelControlClusterServerAttributes.setDescription("LEVELCONTROL CLUSTER SERVER ATTRIBUTES")
LevelControlClusterServerAttributes.setDependencies(LevelControlClusterServerCheck,["LEVELCONTROL_CLUSTER_CS"])

LevelControlClusterServerCommands = drvZigbeeComponent.createMenuSymbol("LEVELCONTROL_CLUSTER_SERVER__COMMANDS_MENU", LevelControlClusterServerMenu)
LevelControlClusterServerCommands.setLabel("Commands")
#LevelControlClusterServerCommands.setVisible(False)
LevelControlClusterServerCommands.setDescription("LEVELCONTROL CLUSTER SERVER COMMANDS")
LevelControlClusterServerCommands.setDependencies(LevelControlClusterServerCheck,["LEVELCONTROL_CLUSTER_CS"])

#################               Server Attributes                                 ###############

global LevelCtrlClusterServerAttributeCurrentLevel
LevelCtrlClusterServerAttributeCurrentLevel = drvZigbeeComponent.createBooleanSymbol("LC_CURRENTLEVEL", LevelControlClusterServerAttributes)
LevelCtrlClusterServerAttributeCurrentLevel.setLabel("0x0000 CurrentLevel")
LevelCtrlClusterServerAttributeCurrentLevel.setDefaultValue(True)
LevelCtrlClusterServerAttributeCurrentLevel.setReadOnly(True)

global LevelCtrlClusterServerAttributeRemainingTime
LevelCtrlClusterServerAttributeRemainingTime = drvZigbeeComponent.createBooleanSymbol("LC_REMAININGTIME", LevelControlClusterServerAttributes)
LevelCtrlClusterServerAttributeRemainingTime.setLabel("0x0001 RemainingTime")
LevelCtrlClusterServerAttributeRemainingTime.setDefaultValue(True)

global LevelCtrlClusterServerAttributeOptions
LevelCtrlClusterServerAttributeOptions = drvZigbeeComponent.createBooleanSymbol("LC_OPTIONS", LevelControlClusterServerAttributes)
LevelCtrlClusterServerAttributeOptions.setLabel("0x000F Options")
LevelCtrlClusterServerAttributeOptions.setDefaultValue(True)
LevelCtrlClusterServerAttributeOptions.setReadOnly(True)

global LevelCtrlClusterServerAttributeOnOffTransitionTime
LevelCtrlClusterServerAttributeOnOffTransitionTime = drvZigbeeComponent.createBooleanSymbol("LC_ONOFFTRANSITIONTIME", LevelControlClusterServerAttributes)
LevelCtrlClusterServerAttributeOnOffTransitionTime.setLabel("0x0010 OnOffTransitionTime")
LevelCtrlClusterServerAttributeOnOffTransitionTime.setDefaultValue(True)

global LevelCtrlClusterServerAttributeOnLevel
LevelCtrlClusterServerAttributeOnLevel = drvZigbeeComponent.createBooleanSymbol("LC_ONLEVEL", LevelControlClusterServerAttributes)
LevelCtrlClusterServerAttributeOnLevel.setLabel("0x0011 OnLevel")
LevelCtrlClusterServerAttributeOnLevel.setDefaultValue(True)

# global LevelCtrlClusterServerAttributeOnTransitionTime
# LevelCtrlClusterServerAttributeOnTransitionTime = drvZigbeeComponent.createBooleanSymbol("LC_ONTRANSITIONTIME", LevelControlClusterServerAttributes)
# LevelCtrlClusterServerAttributeOnTransitionTime.setLabel("0x0012 OnTransitionTime")
# LevelCtrlClusterServerAttributeOnTransitionTime.setDefaultValue(True)

# global LevelCtrlClusterServerAttributeOffTransitionTime
# LevelCtrlClusterServerAttributeOffTransitionTime = drvZigbeeComponent.createBooleanSymbol("LC_OFFTRANSITIONTIME", LevelControlClusterServerAttributes)
# LevelCtrlClusterServerAttributeOffTransitionTime.setLabel("0x0013 OffTransitionTime")
# LevelCtrlClusterServerAttributeOffTransitionTime.setDefaultValue(True)

# global LevelCtrlClusterServerAttributeOffDefaultMoveRate
# LevelCtrlClusterServerAttributeOffDefaultMoveRate = drvZigbeeComponent.createBooleanSymbol("LC_DEFAULTMOVERATE", LevelControlClusterServerAttributes)
# LevelCtrlClusterServerAttributeOffDefaultMoveRate.setLabel("0x0014 DefaultMoveRate")
# LevelCtrlClusterServerAttributeOffDefaultMoveRate.setDefaultValue(True)

global LevelCtrlClusterServerAttributeStartUpCurrentLevel
LevelCtrlClusterServerAttributeStartUpCurrentLevel = drvZigbeeComponent.createBooleanSymbol("LC_STARTUPCURRENTLEVEL", LevelControlClusterServerAttributes)
LevelCtrlClusterServerAttributeStartUpCurrentLevel.setLabel("0x4000 StartUpCurrentLevel")
LevelCtrlClusterServerAttributeStartUpCurrentLevel.setDefaultValue(True)

global LevelCtrlClusterServerAttributeClusterRevision
LevelCtrlClusterServerAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("LC_CLUSTERREVISION", LevelControlClusterServerAttributes)
LevelCtrlClusterServerAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
LevelCtrlClusterServerAttributeClusterRevision.setDefaultValue(True)
LevelCtrlClusterServerAttributeClusterRevision.setReadOnly(True)

global LevelCtrlClusterServerAttributeCount
LevelCtrlClusterServerAttributeCount = drvZigbeeComponent.createIntegerSymbol("LC_SERVERATTRIBUTECOUNT", LevelControlClusterServerAttributes)
LevelCtrlClusterServerAttributeCount.setLabel("Attributes Count")
LevelCtrlClusterServerAttributeCount.setDefaultValue(LevelCtrlClusterServerAttributeCountUpdate(0,0))
LevelCtrlClusterServerAttributeCount.setVisible(True)
LevelCtrlClusterServerAttributeCount.setDescription("Attributes Count")
LevelCtrlClusterServerAttributeCount.setReadOnly(True)
LevelCtrlClusterServerAttributeCount.setDependencies(LevelCtrlClusterServerAttributeCountUpdate,["LC_CURRENTLEVEL","LC_REMAININGTIME","LC_OPTIONS","LC_STARTUPCURRENTLEVEL","LC_CLUSTERREVISION"])
#################               Server Commands                                 ###############

# Commands received
global LevelCtrlClusterServerCmdMoveToLevel
LevelCtrlClusterServerCmdMoveToLevel = drvZigbeeComponent.createBooleanSymbol("LC_MOVETOLEVEL", LevelControlClusterServerCommands)
LevelCtrlClusterServerCmdMoveToLevel.setLabel("0x00.Rx Move to level")
LevelCtrlClusterServerCmdMoveToLevel.setDefaultValue(True)
LevelCtrlClusterServerCmdMoveToLevel.setDescription("Receive Move to level command - check the box to enable")
LevelCtrlClusterServerCmdMoveToLevel.setReadOnly(True)

global LevelCtrlClusterServerCmdMove
LevelCtrlClusterServerCmdMove = drvZigbeeComponent.createBooleanSymbol("LC_MOVE", LevelControlClusterServerCommands)
LevelCtrlClusterServerCmdMove.setLabel("0x01.Rx Move")
LevelCtrlClusterServerCmdMove.setDefaultValue(True)
LevelCtrlClusterServerCmdMove.setDescription("Receive Move command - check the box to enable")
LevelCtrlClusterServerCmdMove.setReadOnly(True)

global LevelCtrlClusterServerCmdStep
LevelCtrlClusterServerCmdStep = drvZigbeeComponent.createBooleanSymbol("LC_STEP", LevelControlClusterServerCommands)
LevelCtrlClusterServerCmdStep.setLabel("0x02.Rx Step")
LevelCtrlClusterServerCmdStep.setDefaultValue(True)
LevelCtrlClusterServerCmdStep.setDescription("Receive Step command - check the box to enable")
LevelCtrlClusterServerCmdStep.setReadOnly(True)

global LevelCtrlClusterServerCmdStop
LevelCtrlClusterServerCmdStop = drvZigbeeComponent.createBooleanSymbol("LC_STOP", LevelControlClusterServerCommands)
LevelCtrlClusterServerCmdStop.setLabel("0x03.Rx Stop")
LevelCtrlClusterServerCmdStop.setDefaultValue(True)
LevelCtrlClusterServerCmdStop.setDescription("Receive Stop command - check the box to enable")
LevelCtrlClusterServerCmdStop.setReadOnly(True)

global LevelCtrlClusterServerCmdMoveToLevelWithONOFF
LevelCtrlClusterServerCmdMoveToLevelWithONOFF = drvZigbeeComponent.createBooleanSymbol("LC_MOVETOLEVELWITHONOFF", LevelControlClusterServerCommands)
LevelCtrlClusterServerCmdMoveToLevelWithONOFF.setLabel("0x04.Rx Move to level (with on/off)")
LevelCtrlClusterServerCmdMoveToLevelWithONOFF.setDefaultValue(True)
LevelCtrlClusterServerCmdMoveToLevelWithONOFF.setDescription("Receive Move to level (with on/off) command - check the box to enable")
LevelCtrlClusterServerCmdMoveToLevelWithONOFF.setReadOnly(True)

global LevelCtrlClusterServerCmdMoveWithONOFF
LevelCtrlClusterServerCmdMoveWithONOFF = drvZigbeeComponent.createBooleanSymbol("LC_MOVEWITHONOFF", LevelControlClusterServerCommands)
LevelCtrlClusterServerCmdMoveWithONOFF.setLabel("0x05.Rx Move (with on/off)")
LevelCtrlClusterServerCmdMoveWithONOFF.setDefaultValue(True)
LevelCtrlClusterServerCmdMoveWithONOFF.setDescription("Receive Move (with on/off) command - check the box to enable")
LevelCtrlClusterServerCmdMoveWithONOFF.setReadOnly(True)

global LevelCtrlClusterServerCmdStepWithONOFF
LevelCtrlClusterServerCmdStepWithONOFF = drvZigbeeComponent.createBooleanSymbol("LC_STEPWITHONOFF", LevelControlClusterServerCommands)
LevelCtrlClusterServerCmdStepWithONOFF.setLabel("0x06.Rx Step (with on/off)")
LevelCtrlClusterServerCmdStepWithONOFF.setDefaultValue(True)
LevelCtrlClusterServerCmdStepWithONOFF.setDescription("Receive Step (with on/off) command - check the box to enable")
LevelCtrlClusterServerCmdStepWithONOFF.setReadOnly(True)

global LevelCtrlClusterServerCmdStopWithONOFF
LevelCtrlClusterServerCmdStopWithONOFF = drvZigbeeComponent.createBooleanSymbol("LC_STOPWITHONOFF", LevelControlClusterServerCommands)
LevelCtrlClusterServerCmdStopWithONOFF.setLabel("0x07.Rx Stop (with on/off)")
LevelCtrlClusterServerCmdStopWithONOFF.setDefaultValue(True)
LevelCtrlClusterServerCmdStopWithONOFF.setDescription("Receive Stop (with on/off) command - check the box to enable")
LevelCtrlClusterServerCmdStopWithONOFF.setReadOnly(True)

global LevelCtrlClusterServerCommandCount
LevelCtrlClusterServerCommandCount = drvZigbeeComponent.createIntegerSymbol("LC_SERVERCOMMANDCOUNT", LevelControlClusterServerCommands)
LevelCtrlClusterServerCommandCount.setLabel("Commands Count")
LevelCtrlClusterServerCommandCount.setDefaultValue(LevelCtrlClusterServerCommandCountUpdate(0,0))
LevelCtrlClusterServerCommandCount.setVisible(True)
LevelCtrlClusterServerCommandCount.setDescription("Commands Count")
LevelCtrlClusterServerCommandCount.setReadOnly(True)
LevelCtrlClusterServerCommandCount.setDependencies(LevelCtrlClusterServerCommandCountUpdate, ["LC_MOVETOLEVEL","LC_MOVE","LC_STEP","LC_STOP","LC_MOVETOLEVELWITHONOFF","LC_MOVEWITHONOFF","LC_STEPWITHONOFF","LC_STOPWITHONOFF"])

#################               Client Attributes                               ###############

global LevelCtrlClusterClientAttributeClusterRevision
LevelCtrlClusterClientAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("LCC_CLUSTERREVISION", LevelControlClusterClientAttributes)
LevelCtrlClusterClientAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
LevelCtrlClusterClientAttributeClusterRevision.setDefaultValue(True)
LevelCtrlClusterClientAttributeClusterRevision.setReadOnly(True)

global LevelCtrlClusterClientAttributeCount
LevelCtrlClusterClientAttributeCount = drvZigbeeComponent.createIntegerSymbol("LCC_CLIENTATTRIBUTECOUNT", LevelControlClusterClientAttributes)
LevelCtrlClusterClientAttributeCount.setLabel("Attributes Count")
LevelCtrlClusterClientAttributeCount.setDefaultValue(LevelCtrlClusterClientAttributeCountUpdate(0,0))
LevelCtrlClusterClientAttributeCount.setVisible(True)
LevelCtrlClusterClientAttributeCount.setDescription("Attributes Count")
LevelCtrlClusterClientAttributeCount.setReadOnly(True)
LevelCtrlClusterClientAttributeCount.setDependencies(LevelCtrlClusterClientAttributeCountUpdate,["LCC_CLUSTERREVISION"])

#################               Client Commands                                 ###############

# Commands generated
global LevelCtrlClusterClientCmdMoveToLevel
LevelCtrlClusterClientCmdMoveToLevel = drvZigbeeComponent.createBooleanSymbol("LCC_MOVETOLEVEL", LevelControlClusterClientCommands)
LevelCtrlClusterClientCmdMoveToLevel.setLabel("0x00.Tx Move to level")
LevelCtrlClusterClientCmdMoveToLevel.setDefaultValue(True)
LevelCtrlClusterClientCmdMoveToLevel.setDescription("Send Move to level command - check the box to enable")

global LevelCtrlClusterClientCmdMove
LevelCtrlClusterClientCmdMove = drvZigbeeComponent.createBooleanSymbol("LCC_MOVE", LevelControlClusterClientCommands)
LevelCtrlClusterClientCmdMove.setLabel("0x01.Tx Move")
LevelCtrlClusterClientCmdMove.setDefaultValue(True)
LevelCtrlClusterClientCmdMove.setDescription("Send Move command - check the box to enable")

global LevelCtrlClusterClientCmdStep
LevelCtrlClusterClientCmdStep = drvZigbeeComponent.createBooleanSymbol("LCC_STEP", LevelControlClusterClientCommands)
LevelCtrlClusterClientCmdStep.setLabel("0x02.Tx Step")
LevelCtrlClusterClientCmdStep.setDefaultValue(True)
LevelCtrlClusterClientCmdStep.setDescription("Send Step command - check the box to enable")

global LevelCtrlClusterClientCmdStop
LevelCtrlClusterClientCmdStop = drvZigbeeComponent.createBooleanSymbol("LCC_STOP", LevelControlClusterClientCommands)
LevelCtrlClusterClientCmdStop.setLabel("0x03.Tx Stop")
LevelCtrlClusterClientCmdStop.setDefaultValue(True)
LevelCtrlClusterClientCmdStop.setDescription("Send Stop command - check the box to enable")

global LevelCtrlClusterClientCmdMoveToLevelWithONOFF
LevelCtrlClusterClientCmdMoveToLevelWithONOFF = drvZigbeeComponent.createBooleanSymbol("LCC_MOVETOLEVELWITHONOFF", LevelControlClusterClientCommands)
LevelCtrlClusterClientCmdMoveToLevelWithONOFF.setLabel("0x04.Tx Move to level (with on/off)")
LevelCtrlClusterClientCmdMoveToLevelWithONOFF.setDefaultValue(True)
LevelCtrlClusterClientCmdMoveToLevelWithONOFF.setDescription("Send Move to level (with on/off) command - check the box to enable")

global LevelCtrlClusterClientCmdMoveWithONOFF
LevelCtrlClusterClientCmdMoveWithONOFF = drvZigbeeComponent.createBooleanSymbol("LCC_MOVEWITHONOFF", LevelControlClusterClientCommands)
LevelCtrlClusterClientCmdMoveWithONOFF.setLabel("0x05.Tx Move (with on/off)")
LevelCtrlClusterClientCmdMoveWithONOFF.setDefaultValue(True)
LevelCtrlClusterClientCmdMoveWithONOFF.setDescription("Send Move (with on/off) command - check the box to enable")

global LevelCtrlClusterClientCmdStepWithONOFF
LevelCtrlClusterClientCmdStepWithONOFF = drvZigbeeComponent.createBooleanSymbol("LCC_STEPWITHONOFF", LevelControlClusterClientCommands)
LevelCtrlClusterClientCmdStepWithONOFF.setLabel("0x06.Tx Step (with on/off)")
LevelCtrlClusterClientCmdStepWithONOFF.setDefaultValue(True)
LevelCtrlClusterClientCmdStepWithONOFF.setDescription("Send Step (with on/off) command - check the box to enable")

global LevelCtrlClusterClientCmdStopWithONOFF
LevelCtrlClusterClientCmdStopWithONOFF = drvZigbeeComponent.createBooleanSymbol("LCC_STOPWITHONOFF", LevelControlClusterClientCommands)
LevelCtrlClusterClientCmdStopWithONOFF.setLabel("0x07.Tx Stop (with on/off)")
LevelCtrlClusterClientCmdStopWithONOFF.setDefaultValue(True)
LevelCtrlClusterClientCmdStopWithONOFF.setDescription("Send Stop (with on/off) command - check the box to enable")

global LevelCtrlClusterClientCommandCount
LevelCtrlClusterClientCommandCount = drvZigbeeComponent.createIntegerSymbol("LCC_CLIENTCOMMANDCOUNT", LevelControlClusterClientCommands)
LevelCtrlClusterClientCommandCount.setLabel("Commands Count")
LevelCtrlClusterClientCommandCount.setDefaultValue(LevelCtrlClusterClientCommandCountUpdate(0,0))
LevelCtrlClusterClientCommandCount.setVisible(True)
LevelCtrlClusterClientCommandCount.setDescription("Commands Count")
LevelCtrlClusterClientCommandCount.setReadOnly(True)
LevelCtrlClusterClientCommandCount.setDependencies(LevelCtrlClusterClientCommandCountUpdate,["LCC_STOPWITHONOFF", "LCC_STEPWITHONOFF", "LCC_MOVEWITHONOFF", "LCC_MOVETOLEVELWITHONOFF", "LCC_STOP", "LCC_STEP", "LCC_MOVE", "LCC_MOVETOLEVEL"])

############################################################################################################
# Default Values Settings based on device type
levelControlClusterHandling()

############################################################################################################
##################################### FTL Files Definitions ################################################
############################################################################################################

# LevelControl CLUSTER Common header
levelControlClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_LEVELCONTROL_CLUSTER_CONF", None)
levelControlClusterConf.setSourcePath("/driver/zigbee/templates/cluster/levelControl/zclLevelControlCluster.h.ftl")
levelControlClusterConf.setOutputName("zclLevelControlCluster.h")
levelControlClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
levelControlClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
levelControlClusterConf.setType("HEADER")
levelControlClusterConf.setOverwrite(True)
levelControlClusterConf.setMarkup(True)

levelControlClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_LEVELCONTROL_CLUSTER_CONF2", None)
levelControlClusterConf.setSourcePath("/driver/zigbee/templates/cluster/levelControl/zclZllLevelControlCluster.h.ftl")
levelControlClusterConf.setOutputName("zclZllLevelControlCluster.h")
levelControlClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
levelControlClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
levelControlClusterConf.setType("HEADER")
levelControlClusterConf.setOverwrite(True)
levelControlClusterConf.setMarkup(True)

levelControlClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_LEVELCLUSTER_CONF_SRC1", None)
levelControlClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/levelControl/levelControlCluster.c.ftl")
levelControlClusterConfSrc.setOutputName("levelControlCluster.c")
levelControlClusterConfSrc.setDestPath("/zigbee/z3device/clusters")
levelControlClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/clusters/")
levelControlClusterConfSrc.setType("SOURCE")
levelControlClusterConfSrc.setOverwrite(True)
levelControlClusterConfSrc.setMarkup(True)
levelControlClusterConfSrc.setEnabled(LevelControlCluster.getValue())
levelControlClusterConfSrc.setDependencies(LevelControlClusterEnableCheck,["LEVELCONTROL_CLUSTER_ENABLE"])

# LEVELCONTROL CLUSTER - Light
levelControlClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_LEVELCONTROL_CLUSTER_CONF_SRC_LIGHT", None)
levelControlClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/levelControl/lightLevelControlCluster.c.ftl")
levelControlClusterConfSrc.setOutputName("lightLevelControlCluster.c")
levelControlClusterConfSrc.setDestPath("/zigbee/z3device/light")
levelControlClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/light/")
levelControlClusterConfSrc.setType("SOURCE")
levelControlClusterConfSrc.setOverwrite(True)
levelControlClusterConfSrc.setMarkup(True)
levelControlClusterConfSrc.setEnabled(checkDevTypeLight)

# LEVELCONTROL CLUSTER - Custom
levelControlClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_LEVELCONTROL_CLUSTER_CONF_SRC_CUSTOM", None)
levelControlClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/levelControl/customLevelControlCluster.c.ftl")
levelControlClusterConfSrc.setOutputName("customLevelControlCluster.c")
levelControlClusterConfSrc.setDestPath("/zigbee/z3device/custom")
levelControlClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/custom/")
levelControlClusterConfSrc.setType("SOURCE")
levelControlClusterConfSrc.setOverwrite(True)
levelControlClusterConfSrc.setMarkup(True)
levelControlClusterConfSrc.setEnabled(checkDevTypeCustom and LevelControlCluster.getValue())
levelControlClusterConfSrc.setDependencies(customLevelControlClusterEnableCheck,["LEVELCONTROL_CLUSTER_ENABLE"])

# LEVELCONTROL CLUSTER - Color Scene Controller
levelControlClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_LEVELCONTROL_CLUSTER_CONF_SRC_CSC", None)
levelControlClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/levelControl/cscLevelControlCluster.c.ftl")
levelControlClusterConfSrc.setOutputName("cscLevelControlCluster.c")
levelControlClusterConfSrc.setDestPath("/zigbee/z3device/colorSceneController")
levelControlClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/colorSceneController/")
levelControlClusterConfSrc.setType("SOURCE")
levelControlClusterConfSrc.setOverwrite(True)
levelControlClusterConfSrc.setMarkup(True)
levelControlClusterConfSrc.setEnabled(checkDevTypeRemote)

# LEVELCONTROL CLUSTER - Combined Interface
levelControlClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_LEVELCONTROL_CLUSTER_CONF_SRC_CI", None)
levelControlClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/levelControl/ciLevelControlCluster.c.ftl")
levelControlClusterConfSrc.setOutputName("ciLevelControlCluster.c")
levelControlClusterConfSrc.setDestPath("/zigbee/z3device/combinedInterface")
levelControlClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/combinedInterface/")
levelControlClusterConfSrc.setType("SOURCE")
levelControlClusterConfSrc.setOverwrite(True)
levelControlClusterConfSrc.setMarkup(True)
levelControlClusterConfSrc.setEnabled(checkDevTypeCombInterface)
############################################################################################################
