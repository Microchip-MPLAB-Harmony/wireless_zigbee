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
###########################################  SCENES CLUSTER CONFIGURATION  #################################
############################################################################################################

############################################################################################################
############################################# Function Definitions #########################################
############################################################################################################

def ScenesClusterCsCheck(symbol, event):
    if (ScenesCluster.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def ScenesClusterEnableCheck(symbol, event):
    if (ScenesCluster.getValue() == False):
        symbol.setEnabled(False)
    else:
        symbol.setEnabled(True)

def customScenesClusterEnableCheck(symbol, event):
    if ((zigbeeDeviceType.getValue() == 'ZIGBEE_CUSTOM') and (ScenesCluster.getValue() == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def ScenesClusterClientCheck(symbol, event):
    if ((ScenesCluster.getValue() == False) or ScenesClusterCS.getValue() == "SERVER"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def ScenesClusterServerCheck(symbol, event):
    if ((ScenesCluster.getValue() == False) or ScenesClusterCS.getValue() == "CLIENT"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def scenesClusterHandling():

    getDevice = zigbeeDeviceType.getValue()

    if ((getDevice == "ZIGBEE_COLOR_SCENE_CONTROLLER")
        or (getDevice == "ZIGBEE_COMBINED_INTERFACE")
        or (getDevice == "ZIGBEE_CONTROL_BRIDGE")
        ):
        ScenesCluster.setVisible(True)
        ScenesCluster.setValue(True)
        ScenesCluster.setReadOnly(True)
        ScenesClusterCS.setValue("CLIENT")
        ScenesClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_MULTI_SENSOR")
            or (getDevice == "IAS_ACE")
        ):
        ScenesCluster.setVisible(False)
        ScenesCluster.setValue(False)
    elif ((getDevice == "ZIGBEE_THERMOSTAT")
            or (getDevice == "ZIGBEE_ON_OFF_LIGHT")
            or (getDevice == "ZIGBEE_DIMMABLE_LIGHT")
            or (getDevice == "ZIGBEE_COLOR_LIGHT")
            or (getDevice == "ZIGBEE_EXTENDED_COLOR_LIGHT")
            or (getDevice == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")
        ):
        ScenesCluster.setVisible(True)
        ScenesCluster.setValue(True)
        ScenesCluster.setReadOnly(True)
        ScenesClusterCS.setValue("SERVER")
        ScenesClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_CUSTOM")):
        ScenesCluster.setVisible(True)
        ScenesCluster.setValue(True)
        ScenesClusterCS.setValue("BOTH")
    else:
        ScenesCluster.setVisible(False)

def ScenesClusterServerAttributeCountUpdate(symbol, event):
    count = 0
    if (ScenesClusterServerAttributeSceneCount.getValue()):
        count += 1
    if (ScenesClusterServerAttributeCurrentScene.getValue()):
        count += 1
    if (ScenesClusterServerAttributeCurrentGroup.getValue()):
        count += 1
    if (ScenesClusterServerAttributeSceneValid.getValue()):
        count += 1
    if (ScenesClusterServerAttributeNameSupport.getValue()):
        count += 1
    if (ScenesClusterServerAttributeClusterRevision.getValue()):
        count += 1
    ScenesClusterServerAttributeCount.setValue(count) 
    return count

def ScenesClusterServerCommandCountUpdate(symbol, event):
    count = 0
    if (ScenesClusterServerAddScene.getValue()):
        count += 1
    if (ScenesClusterServerCommandsViewScene.getValue()):
        count += 1
    if (ScenesClusterServerCommandsRemoveScene.getValue()):
        count += 1
    if (ScenesClusterServerCommandsRemoveAllScene.getValue()):
        count += 1
    if (ScenesClusterServerCommandsStoreScene.getValue()):
        count += 1
    if (ScenesClusterServerCommandsRecallScene.getValue()):
        count += 1
    if (ScenesClusterServerCommandsSceneMembership.getValue()):
        count += 1
    if (ScenesClusterServerEnhancedAddScene.getValue()):
        count += 1
    if (ScenesClusterServerCommandsEnhancedViewScene.getValue()):
        count += 1
    if (ScenesClusterServerCommandsCopyScene.getValue()):
        count += 1	
    if (ScenesClusterServerAddSceneResp.getValue()):
        count += 1
    if (ScenesClusterServerCommandsViewSceneResp.getValue()):
        count += 1
    if (ScenesClusterServerCommandsRemoveSceneResp.getValue()):
        count += 1
    if (ScenesClusterServerCommandsRemoveAllSceneResp.getValue()):
        count += 1
    if (ScenesClusterServerCommandsStoreSceneResp.getValue()):
        count += 1
    # if (ScenesClusterServerCommandsRecallSceneResp.getValue()):
        # count += 1
    if (ScenesClusterServerCommandsSceneMembershipResp.getValue()):
        count += 1
    if (ScenesClusterServerEnhancedAddSceneResp.getValue()):
        count += 1
    if (ScenesClusterServerCommandsEnhancedViewSceneResp.getValue()):
        count += 1
    if (ScenesClusterServerCommandsCopySceneResp.getValue()):
        count += 1
    ScenesClusterServerCommandCount.setValue(count)
    return count

def ScenesClusterClientAttributeCountUpdate(symbol, event):
    count = 0
    if (ScenesClusterClientAttributeClusterRevision.getValue()):
        count += 1
    ScenesClusterClientAttributeCount.setValue(count)
    return count

def ScenesClusterClientCommandCountUpdate(symbol, event):
    count = 0
    if (ScenesClusterClientAddSceneResp.getValue()):
        count += 1
    if (ScenesClusterClientCommandsViewSceneResp.getValue()):
        count += 1
    if (ScenesClusterClientCommandsRemoveSceneResp.getValue()):
        count += 1	
    if (ScenesClusterClientCommandsRemoveAllSceneResp.getValue()):
        count += 1
    if (ScenesClusterClientCommandsStoreSceneResp.getValue()):
        count += 1        
    if (ScenesClusterClientCommandsRecallSceneResp.getValue()):
        count += 1
    if (ScenesClusterClientCommandsSceneMembershipResp.getValue()):
        count += 1
    if (ScenesClusterClientEnhancedAddSceneResp.getValue()):
        count += 1
    if (ScenesClusterClientCommandsEnhancedViewSceneResp.getValue()):
        count += 1
    if (ScenesClusterClientCommandsCopySceneResp.getValue()):
        count += 1	
    if (ScenesClusterClientAddScene.getValue()):
        count += 1
    if (ScenesClusterClientCommandsViewScene.getValue()):
        count += 1
    if (ScenesClusterClientCommandsRemoveScene.getValue()):
        count += 1
    if (ScenesClusterClientCommandsRemoveAllScene.getValue()):
        count += 1
    if (ScenesClusterClientCommandsStoreScene.getValue()):
        count += 1
    if (ScenesClusterClientCommandsRecallScene.getValue()):
        count += 1
    if (ScenesClusterClientCommandsSceneMembership.getValue()):
        count += 1
    if (ScenesClusterClientEnhancedAddScene.getValue()):
        count += 1
    if (ScenesClusterClientCommandsEnhancedViewScene.getValue()):
        count += 1
    if (ScenesClusterClientCommandsCopyScene.getValue()):
        count += 1
    ScenesClusterClientCommandCount.setValue(count)
    return count
############################################################################################################
##################################### Configuration Item Definitions #######################################
############################################################################################################

global ScenesCluster
ScenesCluster = drvZigbeeComponent.createBooleanSymbol("SCENES_CLUSTER_ENABLE", clusterConfigMenu)
ScenesCluster.setLabel("0x0005 Scenes Cluster")
ScenesCluster.setDefaultValue(False)
ScenesCluster.setVisible(False)
ScenesCluster.setDescription("SCENES CLUSTER- check the box to enable")

global ScenesClusterCS
ScenesClusterCS = drvZigbeeComponent.createComboSymbol("SCENES_CLUSTER_CS",  ScenesCluster, ["CLIENT","SERVER", "BOTH"])
ScenesClusterCS.setLabel("Supported Implementation")
ScenesClusterCS.setDefaultValue("")
ScenesClusterCS.setVisible(False)
ScenesClusterCS.setDescription("SCENES CLUSTER Supported Implementation- check the box to enable")
ScenesClusterCS.setDependencies(ScenesClusterCsCheck,["SCENES_CLUSTER_ENABLE"])

ScenesClusterClientMenu = drvZigbeeComponent.createMenuSymbol("SCENES_CLUSTER_CLIENT_MENU", ScenesCluster)
ScenesClusterClientMenu.setLabel("Client")
ScenesClusterClientMenu.setVisible(False)
ScenesClusterClientMenu.setDescription("SCENES CLUSTER CLIENT")
ScenesClusterClientMenu.setDependencies(ScenesClusterClientCheck,["SCENES_CLUSTER_CS","SCENES_CLUSTER_ENABLE"])

ScenesClusterServerMenu = drvZigbeeComponent.createMenuSymbol("SCENES_CLUSTER_SERVER_MENU", ScenesCluster)
ScenesClusterServerMenu.setLabel("Server")
ScenesClusterServerMenu.setVisible(False)
ScenesClusterServerMenu.setDescription("SCENES CLUSTER SERVER")
ScenesClusterServerMenu.setDependencies(ScenesClusterServerCheck,["SCENES_CLUSTER_CS","SCENES_CLUSTER_ENABLE"])

ScenesClusterClientAttributes = drvZigbeeComponent.createMenuSymbol("SCENES_CLUSTER_CLIENT__ATTRIBUTES_MENU", ScenesClusterClientMenu)
ScenesClusterClientAttributes.setLabel("Attributes")
#ScenesClusterClientAttributes.setVisible(False)
ScenesClusterClientAttributes.setDescription("SCENES CLUSTER CLIENT ATTRIBUTES")
ScenesClusterClientAttributes.setDependencies(ScenesClusterClientCheck,["SCENES_CLUSTER_CS"])

ScenesClusterClientCommands = drvZigbeeComponent.createMenuSymbol("SCENES_CLUSTER_CLIENT__COMMANDS_MENU", ScenesClusterClientMenu)
ScenesClusterClientCommands.setLabel("Commands")
#ScenesClusterClientCommands.setVisible(False)
ScenesClusterClientCommands.setDescription("SCENES CLUSTER CLIENT COMMANDS")
ScenesClusterClientCommands.setDependencies(ScenesClusterClientCheck,["SCENES_CLUSTER_CS"])

ScenesClusterServerAttributes = drvZigbeeComponent.createMenuSymbol("SCENES_CLUSTER_SERVER__ATTRIBUTES_MENU", ScenesClusterServerMenu)
ScenesClusterServerAttributes.setLabel("Attributes")
#ScenesClusterServerAttributes.setVisible(False)
ScenesClusterServerAttributes.setDescription("SCENES CLUSTER SERVER ATTRIBUTES")
ScenesClusterServerAttributes.setDependencies(ScenesClusterServerCheck,["SCENES_CLUSTER_CS"])

ScenesClusterServerCommands = drvZigbeeComponent.createMenuSymbol("SCENES_CLUSTER_SERVER__COMMANDS_MENU", ScenesClusterServerMenu)
ScenesClusterServerCommands.setLabel("Commands")
#ScenesClusterServerCommands.setVisible(False)
ScenesClusterServerCommands.setDescription("SCENES CLUSTER SERVER COMMANDS")
ScenesClusterServerCommands.setDependencies(ScenesClusterServerCheck,["SCENES_CLUSTER_CS"])

#################               Server Attributes                                 ###############

global ScenesClusterServerAttributeSceneCount
ScenesClusterServerAttributeSceneCount = drvZigbeeComponent.createBooleanSymbol("SC_SCENECOUNT", ScenesClusterServerAttributes)
ScenesClusterServerAttributeSceneCount.setLabel("0x0000 SceneCount")
ScenesClusterServerAttributeSceneCount.setDefaultValue(True)
ScenesClusterServerAttributeSceneCount.setReadOnly(True)

global ScenesClusterServerAttributeCurrentScene
ScenesClusterServerAttributeCurrentScene = drvZigbeeComponent.createBooleanSymbol("SC_CURRENTSCENE", ScenesClusterServerAttributes)
ScenesClusterServerAttributeCurrentScene.setLabel("0x0001 CurrentScene")
ScenesClusterServerAttributeCurrentScene.setDefaultValue(True)
ScenesClusterServerAttributeCurrentScene.setReadOnly(True)

global ScenesClusterServerAttributeCurrentGroup
ScenesClusterServerAttributeCurrentGroup = drvZigbeeComponent.createBooleanSymbol("SC_CURRENTGROUP", ScenesClusterServerAttributes)
ScenesClusterServerAttributeCurrentGroup.setLabel("0x0002 CurrentGroup")
ScenesClusterServerAttributeCurrentGroup.setDefaultValue(True)
ScenesClusterServerAttributeCurrentGroup.setReadOnly(True)

global ScenesClusterServerAttributeSceneValid
ScenesClusterServerAttributeSceneValid= drvZigbeeComponent.createBooleanSymbol("SC_SCENEVALID", ScenesClusterServerAttributes)
ScenesClusterServerAttributeSceneValid.setLabel("0x0003 SceneValid")
ScenesClusterServerAttributeSceneValid.setDefaultValue(True)
ScenesClusterServerAttributeSceneValid.setReadOnly(True)

global ScenesClusterServerAttributeNameSupport
ScenesClusterServerAttributeNameSupport= drvZigbeeComponent.createBooleanSymbol("SC_SSNAMESUPPORT", ScenesClusterServerAttributes)
ScenesClusterServerAttributeNameSupport.setLabel("0x0004 NameSupport")
ScenesClusterServerAttributeNameSupport.setDefaultValue(True)
ScenesClusterServerAttributeNameSupport.setReadOnly(True)

# ScenesClusterServerAttributeLastConfiguredBy = drvZigbeeComponent.createBooleanSymbol("SC_SSLASTCONF", ScenesClusterServerAttributes)
# ScenesClusterServerAttributeLastConfiguredBy.setLabel("0x0005 LastConfiguredBy")
# ScenesClusterServerAttributeLastConfiguredBy.setDefaultValue(True)

global ScenesClusterServerAttributeClusterRevision
ScenesClusterServerAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("SCS_CLUSTERREVISION", ScenesClusterServerAttributes)
ScenesClusterServerAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
ScenesClusterServerAttributeClusterRevision.setDefaultValue(True)
ScenesClusterServerAttributeClusterRevision.setReadOnly(True)

global ScenesClusterServerAttributeCount
ScenesClusterServerAttributeCount = drvZigbeeComponent.createIntegerSymbol("SC_SERVERATTRIBUTECOUNT", ScenesClusterServerAttributes)
ScenesClusterServerAttributeCount.setLabel("Attributes Count")
ScenesClusterServerAttributeCount.setDefaultValue(ScenesClusterServerAttributeCountUpdate(0,0))
ScenesClusterServerAttributeCount.setVisible(True)
ScenesClusterServerAttributeCount.setDescription("Attributes Count")
ScenesClusterServerAttributeCount.setReadOnly(True)
ScenesClusterServerAttributeCount.setDependencies(ScenesClusterServerAttributeCountUpdate,["SCS_CLUSTERREVISION", "SC_SSNAMESUPPORT", "SC_SCENEVALID", "SC_CURRENTGROUP", "SC_CURRENTSCENE", "SC_SCENECOUNT"])

#################               Server Commands                                 ###############

# Commands received
global ScenesClusterServerAddScene
ScenesClusterServerAddScene = drvZigbeeComponent.createBooleanSymbol("SC_ADDSCENE", ScenesClusterServerCommands)
ScenesClusterServerAddScene.setLabel("0x00.Rx Add scene")
ScenesClusterServerAddScene.setDefaultValue(True)
ScenesClusterServerAddScene.setDescription("Receive Add scene command - check the box to enable")
ScenesClusterServerAddScene.setReadOnly(True)

global ScenesClusterServerCommandsViewScene
ScenesClusterServerCommandsViewScene = drvZigbeeComponent.createBooleanSymbol("SC_VIEWSCENE", ScenesClusterServerCommands)
ScenesClusterServerCommandsViewScene.setLabel("0x01.Rx View scene")
ScenesClusterServerCommandsViewScene.setDefaultValue(True)
ScenesClusterServerCommandsViewScene.setDescription("Receive View scene command - check the box to enable")
ScenesClusterServerCommandsViewScene.setReadOnly(True)

global ScenesClusterServerCommandsRemoveScene
ScenesClusterServerCommandsRemoveScene = drvZigbeeComponent.createBooleanSymbol("SC_REMOVESCENE", ScenesClusterServerCommands)
ScenesClusterServerCommandsRemoveScene.setLabel("0x02.Rx Remove scene")
ScenesClusterServerCommandsRemoveScene.setDefaultValue(True)
ScenesClusterServerCommandsRemoveScene.setDescription("Receive Remove scene command - check the box to enable")
ScenesClusterServerCommandsRemoveScene.setReadOnly(True)

global ScenesClusterServerCommandsRemoveAllScene
ScenesClusterServerCommandsRemoveAllScene = drvZigbeeComponent.createBooleanSymbol("SC_REMOVESCENEALL", ScenesClusterServerCommands)
ScenesClusterServerCommandsRemoveAllScene.setLabel("0x03.Rx Remove all scenes")
ScenesClusterServerCommandsRemoveAllScene.setDefaultValue(True)
ScenesClusterServerCommandsRemoveAllScene.setDescription("Receive Remove allscenes command - check the box to enable")
ScenesClusterServerCommandsRemoveAllScene.setReadOnly(True)

global ScenesClusterServerCommandsStoreScene
ScenesClusterServerCommandsStoreScene = drvZigbeeComponent.createBooleanSymbol("SC_STORESCENE", ScenesClusterServerCommands)
ScenesClusterServerCommandsStoreScene.setLabel("0x04.Rx Store scene")
ScenesClusterServerCommandsStoreScene.setDefaultValue(True)
ScenesClusterServerCommandsStoreScene.setDescription("Receive Store scene command - check the box to enable")
ScenesClusterServerCommandsStoreScene.setReadOnly(True)

global ScenesClusterServerCommandsRecallScene
ScenesClusterServerCommandsRecallScene = drvZigbeeComponent.createBooleanSymbol("SC_RECALLSCENE", ScenesClusterServerCommands)
ScenesClusterServerCommandsRecallScene.setLabel("0x05.Rx Recall scene")
ScenesClusterServerCommandsRecallScene.setDefaultValue(True)
ScenesClusterServerCommandsRecallScene.setDescription("Receive Recall scene command - check the box to enable")
ScenesClusterServerCommandsRecallScene.setReadOnly(True)

global ScenesClusterServerCommandsSceneMembership
ScenesClusterServerCommandsSceneMembership = drvZigbeeComponent.createBooleanSymbol("SC_SCENEMEM", ScenesClusterServerCommands)
ScenesClusterServerCommandsSceneMembership.setLabel("0x06.Rx Get scene membership")
ScenesClusterServerCommandsSceneMembership.setDefaultValue(True)
ScenesClusterServerCommandsSceneMembership.setDescription("Receive Get scene membership- check the box to enable")
ScenesClusterServerCommandsSceneMembership.setReadOnly(True)

global ScenesClusterServerEnhancedAddScene
ScenesClusterServerEnhancedAddScene = drvZigbeeComponent.createBooleanSymbol("SC_ENHANCEDADDSCENE", ScenesClusterServerCommands)
ScenesClusterServerEnhancedAddScene.setLabel("0x40.Rx Enhanced add scene")
ScenesClusterServerEnhancedAddScene.setDefaultValue(True)
ScenesClusterServerEnhancedAddScene.setDescription("Receive Enhanced add scene command - check the box to enable")

global ScenesClusterServerCommandsEnhancedViewScene
ScenesClusterServerCommandsEnhancedViewScene = drvZigbeeComponent.createBooleanSymbol("SC_ENHANCEDVIEWSCENE", ScenesClusterServerCommands)
ScenesClusterServerCommandsEnhancedViewScene.setLabel("0x41.Rx Enhanced view scene")
ScenesClusterServerCommandsEnhancedViewScene.setDefaultValue(True)
ScenesClusterServerCommandsEnhancedViewScene.setDescription("Receive Enhanced view scene command - check the box to enable")

global ScenesClusterServerCommandsCopyScene
ScenesClusterServerCommandsCopyScene = drvZigbeeComponent.createBooleanSymbol("SC_COPYSCENE", ScenesClusterServerCommands)
ScenesClusterServerCommandsCopyScene.setLabel("0x42.Rx Copy scene")
ScenesClusterServerCommandsCopyScene.setDefaultValue(True)
ScenesClusterServerCommandsCopyScene.setDescription("Receive Copy scene command - check the box to enable")

# Commands generated
global ScenesClusterServerAddSceneResp
ScenesClusterServerAddSceneResp = drvZigbeeComponent.createBooleanSymbol("SC_ADDSCENERESP", ScenesClusterServerCommands)
ScenesClusterServerAddSceneResp.setLabel("0x00.Tx Add scene response")
ScenesClusterServerAddSceneResp.setDefaultValue(True)
ScenesClusterServerAddSceneResp.setDescription("Send Add scene response command - check the box to enable")
ScenesClusterServerAddSceneResp.setReadOnly(True)

global ScenesClusterServerCommandsViewSceneResp
ScenesClusterServerCommandsViewSceneResp = drvZigbeeComponent.createBooleanSymbol("SC_VIEWSCENERES", ScenesClusterServerCommands)
ScenesClusterServerCommandsViewSceneResp.setLabel("0x01.Tx View scene response")
ScenesClusterServerCommandsViewSceneResp.setDefaultValue(True)
ScenesClusterServerCommandsViewSceneResp.setDescription("Send View scene response command - check the box to enable")
ScenesClusterServerCommandsViewSceneResp.setReadOnly(True)

global ScenesClusterServerCommandsRemoveSceneResp
ScenesClusterServerCommandsRemoveSceneResp = drvZigbeeComponent.createBooleanSymbol("SC_REMOVESCENERES", ScenesClusterServerCommands)
ScenesClusterServerCommandsRemoveSceneResp.setLabel("0x02.Tx Remove scene response")
ScenesClusterServerCommandsRemoveSceneResp.setDefaultValue(True)
ScenesClusterServerCommandsRemoveSceneResp.setDescription("Send Remove scene response command - check the box to enable")
ScenesClusterServerCommandsRemoveSceneResp.setReadOnly(True)

global ScenesClusterServerCommandsRemoveAllSceneResp
ScenesClusterServerCommandsRemoveAllSceneResp = drvZigbeeComponent.createBooleanSymbol("SC_REMOVESCENEALLRES", ScenesClusterServerCommands)
ScenesClusterServerCommandsRemoveAllSceneResp.setLabel("0x03.Tx Remove all scenes response")
ScenesClusterServerCommandsRemoveAllSceneResp.setDefaultValue(True)
ScenesClusterServerCommandsRemoveAllSceneResp.setDescription("Send Remove allscenes response command - check the box to enable")
ScenesClusterServerCommandsRemoveAllSceneResp.setReadOnly(True)

global ScenesClusterServerCommandsStoreSceneResp
ScenesClusterServerCommandsStoreSceneResp = drvZigbeeComponent.createBooleanSymbol("SC_STORESCENERES", ScenesClusterServerCommands)
ScenesClusterServerCommandsStoreSceneResp.setLabel("0x04.Tx Store scene response")
ScenesClusterServerCommandsStoreSceneResp.setDefaultValue(True)
ScenesClusterServerCommandsStoreSceneResp.setDescription("Send Store scene response command - check the box to enable")
ScenesClusterServerCommandsStoreSceneResp.setReadOnly(True)

# global ScenesClusterServerCommandsRecallSceneResp
# ScenesClusterServerCommandsRecallSceneResp = drvZigbeeComponent.createBooleanSymbol("SC_RECALLSCENERES", ScenesClusterServerCommands)
# ScenesClusterServerCommandsRecallSceneResp.setLabel("0x05.Tx Recall scene response")
# ScenesClusterServerCommandsRecallSceneResp.setDefaultValue(True)
# ScenesClusterServerCommandsRecallSceneResp.setDescription("Send Recall scene command - check the box to enable")
# ScenesClusterServerCommandsRecallSceneResp.setReadOnly(True)

global ScenesClusterServerCommandsSceneMembershipResp
ScenesClusterServerCommandsSceneMembershipResp = drvZigbeeComponent.createBooleanSymbol("SC_SCENEMEMRES", ScenesClusterServerCommands)
ScenesClusterServerCommandsSceneMembershipResp.setLabel("0x06.Tx Get scene membership response")
ScenesClusterServerCommandsSceneMembershipResp.setDefaultValue(True)
ScenesClusterServerCommandsSceneMembershipResp.setDescription("Send Get scene membership response- check the box to enable")
ScenesClusterServerCommandsSceneMembershipResp.setReadOnly(True)

global ScenesClusterServerEnhancedAddSceneResp
ScenesClusterServerEnhancedAddSceneResp = drvZigbeeComponent.createBooleanSymbol("SC_ENHANCEDADDSCENERES", ScenesClusterServerCommands)
ScenesClusterServerEnhancedAddSceneResp.setLabel("0x40.Tx Enhanced add scene response")
ScenesClusterServerEnhancedAddSceneResp.setDefaultValue(True)
ScenesClusterServerEnhancedAddSceneResp.setDescription("Send Enhanced add scene response command - check the box to enable")

global ScenesClusterServerCommandsEnhancedViewSceneResp
ScenesClusterServerCommandsEnhancedViewSceneResp = drvZigbeeComponent.createBooleanSymbol("SC_ENHANCEDVIEWSCENERES", ScenesClusterServerCommands)
ScenesClusterServerCommandsEnhancedViewSceneResp.setLabel("0x41.Tx Enhanced view scene response")
ScenesClusterServerCommandsEnhancedViewSceneResp.setDefaultValue(True)
ScenesClusterServerCommandsEnhancedViewSceneResp.setDescription("Send Enhanced view scene response command - check the box to enable")

global ScenesClusterServerCommandsCopySceneResp
ScenesClusterServerCommandsCopySceneResp = drvZigbeeComponent.createBooleanSymbol("SC_COPYSCENERES", ScenesClusterServerCommands)
ScenesClusterServerCommandsCopySceneResp.setLabel("0x42.Tx Copy scene response")
ScenesClusterServerCommandsCopySceneResp.setDefaultValue(True)
ScenesClusterServerCommandsCopySceneResp.setDescription("Send Copy scene response command - check the box to enable")

global ScenesClusterServerCommandCount
ScenesClusterServerCommandCount = drvZigbeeComponent.createIntegerSymbol("SC_SERVERCOMMANDCOUNT", ScenesClusterServerCommands)
ScenesClusterServerCommandCount.setLabel("Commands Count")
ScenesClusterServerCommandCount.setDefaultValue(ScenesClusterServerCommandCountUpdate(0,0))
ScenesClusterServerCommandCount.setVisible(True)
ScenesClusterServerCommandCount.setDescription("Commands Count")
ScenesClusterServerCommandCount.setReadOnly(True)
ScenesClusterServerCommandCount.setDependencies(ScenesClusterServerCommandCountUpdate, ["SC_COPYSCENE", "SC_ENHANCEDVIEWSCENE", "SC_ENHANCEDADDSCENE", "SC_SCENEMEM", "SC_RECALLSCENE", "SC_STORESCENE", "SC_REMOVESCENEALL", "SC_REMOVESCENE", "SC_VIEWSCENE", "SC_ADDSCENE", "SC_COPYSCENERES", "SC_ENHANCEDVIEWSCENERES", "SC_ENHANCEDADDSCENERES", "SC_SCENEMEMRES", "SC_RECALLSCENERES", "SC_STORESCENERES", "SC_REMOVESCENEALLRES", "SC_REMOVESCENERES", "SC_VIEWSCENERES", "SC_ADDSCENERESP", "SC_ENHANCEDADDSCENE"])

#################               Client Attributes                                 ###############

global ScenesClusterClientAttributeClusterRevision
ScenesClusterClientAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("SCC_CLUSTERREVISION", ScenesClusterClientAttributes)
ScenesClusterClientAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
ScenesClusterClientAttributeClusterRevision.setDefaultValue(True)
ScenesClusterClientAttributeClusterRevision.setReadOnly(True)

global ScenesClusterClientAttributeCount
ScenesClusterClientAttributeCount = drvZigbeeComponent.createIntegerSymbol("SCC_CLIENTATTRIBUTECOUNT", ScenesClusterClientAttributes)
ScenesClusterClientAttributeCount.setLabel("Attributes Count")
ScenesClusterClientAttributeCount.setDefaultValue(ScenesClusterClientAttributeCountUpdate(0,0))
ScenesClusterClientAttributeCount.setVisible(True)
ScenesClusterClientAttributeCount.setDescription("Attributes Count")
ScenesClusterClientAttributeCount.setReadOnly(True)
ScenesClusterClientAttributeCount.setDependencies(ScenesClusterClientAttributeCountUpdate,["SCC_CLUSTERREVISION"])

#################               Client Commands                                 ###############

# Commands received
global ScenesClusterClientAddSceneResp
ScenesClusterClientAddSceneResp = drvZigbeeComponent.createBooleanSymbol("SCC_ADDSCENERESP", ScenesClusterClientCommands)
ScenesClusterClientAddSceneResp.setLabel("0x00.Rx Add scene response")
ScenesClusterClientAddSceneResp.setDefaultValue(True)
ScenesClusterClientAddSceneResp.setDescription("Receive Add scene response command - check the box to enable")
ScenesClusterClientAddSceneResp.setReadOnly(True)

global ScenesClusterClientCommandsViewSceneResp
ScenesClusterClientCommandsViewSceneResp = drvZigbeeComponent.createBooleanSymbol("SCC_VIEWSCENERES", ScenesClusterClientCommands)
ScenesClusterClientCommandsViewSceneResp.setLabel("0x01.Rx View scene response")
ScenesClusterClientCommandsViewSceneResp.setDefaultValue(True)
ScenesClusterClientCommandsViewSceneResp.setDescription("Receive View scene response command - check the box to enable")
ScenesClusterClientCommandsViewSceneResp.setReadOnly(True)

global ScenesClusterClientCommandsRemoveSceneResp
ScenesClusterClientCommandsRemoveSceneResp = drvZigbeeComponent.createBooleanSymbol("SCC_REMOVESCENERES", ScenesClusterClientCommands)
ScenesClusterClientCommandsRemoveSceneResp.setLabel("0x02.Rx Remove scene response")
ScenesClusterClientCommandsRemoveSceneResp.setDefaultValue(True)
ScenesClusterClientCommandsRemoveSceneResp.setDescription("Receive Remove scene response command - check the box to enable")
ScenesClusterClientCommandsRemoveSceneResp.setReadOnly(True)

global ScenesClusterClientCommandsRemoveAllSceneResp
ScenesClusterClientCommandsRemoveAllSceneResp = drvZigbeeComponent.createBooleanSymbol("SCC_REMOVESCENEALLRES", ScenesClusterClientCommands)
ScenesClusterClientCommandsRemoveAllSceneResp.setLabel("0x03.Rx Remove all scenes response")
ScenesClusterClientCommandsRemoveAllSceneResp.setDefaultValue(True)
ScenesClusterClientCommandsRemoveAllSceneResp.setDescription("Receive Remove allscenes response command - check the box to enable")
ScenesClusterClientCommandsRemoveAllSceneResp.setReadOnly(True)

global ScenesClusterClientCommandsStoreSceneResp
ScenesClusterClientCommandsStoreSceneResp = drvZigbeeComponent.createBooleanSymbol("SCC_STORESCENERES", ScenesClusterClientCommands)
ScenesClusterClientCommandsStoreSceneResp.setLabel("0x04.Rx Store scene response")
ScenesClusterClientCommandsStoreSceneResp.setDefaultValue(True)
ScenesClusterClientCommandsStoreSceneResp.setDescription("Receive Store scene response command - check the box to enable")
ScenesClusterClientCommandsStoreSceneResp.setReadOnly(True)

global ScenesClusterClientCommandsRecallSceneResp
ScenesClusterClientCommandsRecallSceneResp = drvZigbeeComponent.createBooleanSymbol("SCC_RECALLSCENERES", ScenesClusterClientCommands)
ScenesClusterClientCommandsRecallSceneResp.setLabel("0x05.Rx Recall scene response")
ScenesClusterClientCommandsRecallSceneResp.setDefaultValue(True)
ScenesClusterClientCommandsRecallSceneResp.setDescription("Receive Recall scene command - check the box to enable")
ScenesClusterClientCommandsRecallSceneResp.setReadOnly(True)

global ScenesClusterClientCommandsSceneMembershipResp
ScenesClusterClientCommandsSceneMembershipResp = drvZigbeeComponent.createBooleanSymbol("SCC_SCENEMEMRES", ScenesClusterClientCommands)
ScenesClusterClientCommandsSceneMembershipResp.setLabel("0x06.Rx Get scene membership response")
ScenesClusterClientCommandsSceneMembershipResp.setDefaultValue(True)
ScenesClusterClientCommandsSceneMembershipResp.setDescription("Receive Get scene membership response- check the box to enable")
ScenesClusterClientCommandsSceneMembershipResp.setReadOnly(True)

global ScenesClusterClientEnhancedAddSceneResp
ScenesClusterClientEnhancedAddSceneResp = drvZigbeeComponent.createBooleanSymbol("SCC_ENHANCEDADDSCENERES", ScenesClusterClientCommands)
ScenesClusterClientEnhancedAddSceneResp.setLabel("0x40.Rx Enhanced add scene response")
ScenesClusterClientEnhancedAddSceneResp.setDefaultValue(True)
ScenesClusterClientEnhancedAddSceneResp.setDescription("Receive Enhanced add scene response command - check the box to enable")
ScenesClusterClientEnhancedAddSceneResp.setReadOnly(True)

global ScenesClusterClientCommandsEnhancedViewSceneResp
ScenesClusterClientCommandsEnhancedViewSceneResp = drvZigbeeComponent.createBooleanSymbol("SCC_ENHANCEDVIEWSCENERES", ScenesClusterClientCommands)
ScenesClusterClientCommandsEnhancedViewSceneResp.setLabel("0x41.Rx Enhanced view scene response")
ScenesClusterClientCommandsEnhancedViewSceneResp.setDefaultValue(True)
ScenesClusterClientCommandsEnhancedViewSceneResp.setDescription("Receive Enhanced view scene response command - check the box to enable")
ScenesClusterClientCommandsEnhancedViewSceneResp.setReadOnly(True)

global ScenesClusterClientCommandsCopySceneResp
ScenesClusterClientCommandsCopySceneResp = drvZigbeeComponent.createBooleanSymbol("SCC_COPYSCENERES", ScenesClusterClientCommands)
ScenesClusterClientCommandsCopySceneResp.setLabel("0x42.Rx Copy scene response")
ScenesClusterClientCommandsCopySceneResp.setDefaultValue(True)
ScenesClusterClientCommandsCopySceneResp.setDescription("Receive Copy scene response command - check the box to enable")
ScenesClusterClientCommandsCopySceneResp.setReadOnly(True)

# Commands generated
global ScenesClusterClientAddScene
ScenesClusterClientAddScene = drvZigbeeComponent.createBooleanSymbol("SCC_ADDSCENE", ScenesClusterClientCommands)
ScenesClusterClientAddScene.setLabel("0x00.Tx Add scene")
ScenesClusterClientAddScene.setDefaultValue(True)
ScenesClusterClientAddScene.setDescription("Send Add scene command - check the box to enable")

global ScenesClusterClientCommandsViewScene
ScenesClusterClientCommandsViewScene = drvZigbeeComponent.createBooleanSymbol("SCC_VIEWSCENE", ScenesClusterClientCommands)
ScenesClusterClientCommandsViewScene.setLabel("0x01.Tx View scene")
ScenesClusterClientCommandsViewScene.setDefaultValue(True)
ScenesClusterClientCommandsViewScene.setDescription("Send View scene command - check the box to enable")

global ScenesClusterClientCommandsRemoveScene
ScenesClusterClientCommandsRemoveScene = drvZigbeeComponent.createBooleanSymbol("SCC_REMOVESCENE", ScenesClusterClientCommands)
ScenesClusterClientCommandsRemoveScene.setLabel("0x02.Tx Remove scene")
ScenesClusterClientCommandsRemoveScene.setDefaultValue(True)
ScenesClusterClientCommandsRemoveScene.setDescription("Send Remove scene command - check the box to enable")

global ScenesClusterClientCommandsRemoveAllScene
ScenesClusterClientCommandsRemoveAllScene = drvZigbeeComponent.createBooleanSymbol("SCC_REMOVESCENEALL", ScenesClusterClientCommands)
ScenesClusterClientCommandsRemoveAllScene.setLabel("0x03.Tx Remove all scenes")
ScenesClusterClientCommandsRemoveAllScene.setDefaultValue(True)
ScenesClusterClientCommandsRemoveAllScene.setDescription("Send Remove allscenes command - check the box to enable")

global ScenesClusterClientCommandsStoreScene
ScenesClusterClientCommandsStoreScene = drvZigbeeComponent.createBooleanSymbol("SCC_STORESCENE", ScenesClusterClientCommands)
ScenesClusterClientCommandsStoreScene.setLabel("0x04.Tx Store scene")
ScenesClusterClientCommandsStoreScene.setDefaultValue(True)
ScenesClusterClientCommandsStoreScene.setDescription("Send Store scene command - check the box to enable")

global ScenesClusterClientCommandsRecallScene
ScenesClusterClientCommandsRecallScene = drvZigbeeComponent.createBooleanSymbol("SCC_RECALLSCENE", ScenesClusterClientCommands)
ScenesClusterClientCommandsRecallScene.setLabel("0x05.Tx Recall scene")
ScenesClusterClientCommandsRecallScene.setDefaultValue(True)
ScenesClusterClientCommandsRecallScene.setDescription("Send Recall scene command - check the box to enable")

global ScenesClusterClientCommandsSceneMembership
ScenesClusterClientCommandsSceneMembership = drvZigbeeComponent.createBooleanSymbol("SCC_SCENEMEM", ScenesClusterClientCommands)
ScenesClusterClientCommandsSceneMembership.setLabel("0x06.Tx Get scene membership")
ScenesClusterClientCommandsSceneMembership.setDefaultValue(True)
ScenesClusterClientCommandsSceneMembership.setDescription("Send Get scene membership- check the box to enable")

global ScenesClusterClientEnhancedAddScene
ScenesClusterClientEnhancedAddScene = drvZigbeeComponent.createBooleanSymbol("SCC_ENHANCEDADDSCENE", ScenesClusterClientCommands)
ScenesClusterClientEnhancedAddScene.setLabel("0x40.Tx Enhanced add scene")
ScenesClusterClientEnhancedAddScene.setDefaultValue(True)
ScenesClusterClientEnhancedAddScene.setDescription("Send Enhanced add scene command - check the box to enable")

global ScenesClusterClientCommandsEnhancedViewScene
ScenesClusterClientCommandsEnhancedViewScene = drvZigbeeComponent.createBooleanSymbol("SCC_ENHANCEDVIEWSCENE", ScenesClusterClientCommands)
ScenesClusterClientCommandsEnhancedViewScene.setLabel("0x41.Tx Enhanced view scene")
ScenesClusterClientCommandsEnhancedViewScene.setDefaultValue(True)
ScenesClusterClientCommandsEnhancedViewScene.setDescription("Send Enhanced view scene command - check the box to enable")

global ScenesClusterClientCommandsCopyScene
ScenesClusterClientCommandsCopyScene = drvZigbeeComponent.createBooleanSymbol("SCC_COPYSCENE", ScenesClusterClientCommands)
ScenesClusterClientCommandsCopyScene.setLabel("0x42.Tx Copy scene")
ScenesClusterClientCommandsCopyScene.setDefaultValue(True)
ScenesClusterClientCommandsCopyScene.setDescription("Send Copy scene command - check the box to enable")

global ScenesClusterClientCommandCount
ScenesClusterClientCommandCount = drvZigbeeComponent.createIntegerSymbol("SCC_CLIENTCOMMANDCOUNT", ScenesClusterClientCommands)
ScenesClusterClientCommandCount.setLabel("Commands Count")
ScenesClusterClientCommandCount.setDefaultValue(ScenesClusterClientCommandCountUpdate(0,0))
ScenesClusterClientCommandCount.setVisible(True)
ScenesClusterClientCommandCount.setDescription("Commands Count")
ScenesClusterClientCommandCount.setReadOnly(True)
ScenesClusterClientCommandCount.setDependencies(ScenesClusterClientCommandCountUpdate,["SCC_COPYSCENE", "SCC_ENHANCEDVIEWSCENE", "SCC_ENHANCEDADDSCENE", "SCC_SCENEMEM", "SCC_RECALLSCENE", "SCC_STORESCENE", "SCC_REMOVESCENEALL", "SCC_REMOVESCENE", "SCC_VIEWSCENE", "SCC_ADDSCENE", "SCC_COPYSCENERES", "SCC_ENHANCEDVIEWSCENERES", "SCC_ENHANCEDADDSCENERES", "SCC_SCENEMEMRES", "SCC_RECALLSCENERES", "SCC_STORESCENERES", "SCC_REMOVESCENEALLRES", "SCC_REMOVESCENERES", "SCC_VIEWSCENERES", "SCC_ADDSCENERESP", "SCC_ENHANCEDADDSCENE"])

############################################################################################################
# Default Values Settings based on device type
scenesClusterHandling()

############################################################################################################
##################################### FTL Files Definitions ################################################
############################################################################################################

# SCENES CLUSTER Common header
scenesClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_SCENES_CLUSTER_CONF2", None)
scenesClusterConf.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/scenes/zclZllScenesCluster.h.ftl")
scenesClusterConf.setOutputName("zclZllScenesCluster.h")
scenesClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
scenesClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
scenesClusterConf.setType("HEADER")
scenesClusterConf.setOverwrite(True)
scenesClusterConf.setMarkup(True)

scenesClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_SCENESCLUSTER_CONF_SRC1", None)
scenesClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/scenes/scenesCluster.c.ftl")
scenesClusterConfSrc.setOutputName("scenesCluster.c")
scenesClusterConfSrc.setDestPath("/zigbee/z3device/clusters")
scenesClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/clusters/")
scenesClusterConfSrc.setType("SOURCE")
scenesClusterConfSrc.setOverwrite(True)
scenesClusterConfSrc.setMarkup(True)
scenesClusterConfSrc.setEnabled(ScenesCluster.getValue())
scenesClusterConfSrc.setDependencies(ScenesClusterEnableCheck,["SCENES_CLUSTER_ENABLE"])

# SCENES CLUSTER - Light
scenesClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_SCENES_CLUSTER_CONF_SRC_LIGHT", None)
scenesClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/scenes/lightScenesCluster.c.ftl")
scenesClusterConfSrc.setOutputName("lightScenesCluster.c")
scenesClusterConfSrc.setDestPath("/zigbee/z3device/light")
scenesClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/light/")
scenesClusterConfSrc.setType("SOURCE")
scenesClusterConfSrc.setOverwrite(True)
scenesClusterConfSrc.setMarkup(True)
scenesClusterConfSrc.setEnabled(checkDevTypeLight)

# SCENES CLUSTER - Custom
scenesClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_SCENES_CLUSTER_CONF_SRC_CUSTOM", None)
scenesClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/scenes/customScenesCluster.c.ftl")
scenesClusterConfSrc.setOutputName("customScenesCluster.c")
scenesClusterConfSrc.setDestPath("/zigbee/z3device/custom")
scenesClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/custom/")
scenesClusterConfSrc.setType("SOURCE")
scenesClusterConfSrc.setOverwrite(True)
scenesClusterConfSrc.setMarkup(True)
scenesClusterConfSrc.setEnabled(checkDevTypeCustom and ScenesCluster.getValue())
scenesClusterConfSrc.setDependencies(customScenesClusterEnableCheck,["SCENES_CLUSTER_ENABLE"])

# SCENES CLUSTER - Color Scene Controller
scenesClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_SCENES_CLUSTER_CONF_SRC_CSC", None)
scenesClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/scenes/cscScenesCluster.c.ftl")
scenesClusterConfSrc.setOutputName("cscScenesCluster.c")
scenesClusterConfSrc.setDestPath("/zigbee/z3device/colorSceneController")
scenesClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/colorSceneController/")
scenesClusterConfSrc.setType("SOURCE")
scenesClusterConfSrc.setOverwrite(True)
scenesClusterConfSrc.setMarkup(True)
scenesClusterConfSrc.setEnabled(checkDevTypeRemote)

# SCENES CLUSTER - Combined Interface
scenesClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_SCENES_CLUSTER_CONF_SRC_CI", None)
scenesClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/scenes/ciScenesCluster.c.ftl")
scenesClusterConfSrc.setOutputName("ciScenesCluster.c")
scenesClusterConfSrc.setDestPath("/zigbee/z3device/combinedInterface")
scenesClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/combinedInterface/")
scenesClusterConfSrc.setType("SOURCE")
scenesClusterConfSrc.setOverwrite(True)
scenesClusterConfSrc.setMarkup(True)
scenesClusterConfSrc.setEnabled(checkDevTypeCombInterface)

# SCENES CLUSTER - Thermostat
scenesClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_SCENES_CLUSTER_CONF_SRC_TH", None)
scenesClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/scenes/thScenesCluster.c.ftl")
scenesClusterConfSrc.setOutputName("thScenesCluster.c")
scenesClusterConfSrc.setDestPath("/zigbee/z3device/thermostat")
scenesClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/thermostat/")
scenesClusterConfSrc.setType("SOURCE")
scenesClusterConfSrc.setOverwrite(True)
scenesClusterConfSrc.setMarkup(True)
scenesClusterConfSrc.setEnabled(checkDevTypeThermostat)
############################################################################################################
