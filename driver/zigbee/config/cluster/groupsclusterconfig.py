############################################################################################################
###########################################  GROUPS CLUSTER CONFIGURATION  #################################
############################################################################################################

############################################################################################################
############################################# Function Definitions #########################################
############################################################################################################

def groupsclusterCsCheck(symbol, event):
    if (GroupsCluster.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def groupsclusterClientCheck(symbol, event):
    if ((GroupsCluster.getValue() == False) or GroupsClusterCS.getValue() == "SERVER"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def groupsclusterServerCheck(symbol, event):
    if ((GroupsCluster.getValue() == False) or GroupsClusterCS.getValue() == "CLIENT"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def groupsClusterHandling():

    getDevice = zigbeeDeviceType.getValue()

    if ((getDevice == "ZIGBEE_COLOR_SCENE_CONTROLLER")):
        GroupsCluster.setVisible(True)
        GroupsCluster.setValue(True)
        GroupsCluster.setReadOnly(True)
        GroupsClusterCS.setValue("BOTH")#CLIENT
    elif ((getDevice == "ZIGBEE_MULTI_SENSOR")):
        GroupsCluster.setVisible(True)
        GroupsCluster.setValue(True)
        GroupsCluster.setReadOnly(True)
        GroupsClusterCS.setValue("BOTH")#CLIENT
    elif ((getDevice == "ZIGBEE_COMBINED_INTERFACE")):
        GroupsCluster.setVisible(True)
        GroupsCluster.setValue(True)
        GroupsCluster.setReadOnly(True)
        GroupsClusterCS.setValue("BOTH")
    elif ((getDevice == "ZIGBEE_CONTROL_BRIDGE")):
        GroupsCluster.setVisible(True)
        GroupsCluster.setValue(True)
        GroupsCluster.setReadOnly(True)
        GroupsClusterCS.setValue("BOTH")
    elif ((getDevice == "ZIGBEE_THERMOSTAT")):
        GroupsCluster.setVisible(True)
        GroupsCluster.setValue(True)
        GroupsCluster.setReadOnly(True)
        GroupsClusterCS.setValue("BOTH")#SERVER
    elif ((getDevice == "ZIGBEE_IAS_ACE")):
        GroupsCluster.setVisible(True)
        GroupsCluster.setValue(True)
        GroupsCluster.setReadOnly(True)
        GroupsClusterCS.setValue("BOTH")
    elif ((getDevice == "ZIGBEE_ON_OFF_LIGHT")):
        GroupsCluster.setVisible(True)
        GroupsCluster.setValue(True)
        GroupsCluster.setReadOnly(True)
        GroupsClusterCS.setValue("BOTH")
    elif ((getDevice == "ZIGBEE_DIMMABLE_LIGHT")):
        GroupsCluster.setVisible(True)
        GroupsCluster.setValue(True)
        GroupsCluster.setReadOnly(True)
        GroupsClusterCS.setValue("BOTH")
    elif ((getDevice == "ZIGBEE_COLOR_LIGHT")):
        GroupsCluster.setVisible(True)
        GroupsCluster.setValue(True)
        GroupsCluster.setReadOnly(True)
        GroupsClusterCS.setValue("BOTH")
    elif ((getDevice == "ZIGBEE_EXTENDED_COLOR_LIGHT")):
        GroupsCluster.setVisible(True)
        GroupsCluster.setValue(True)
        GroupsCluster.setReadOnly(True)
        GroupsClusterCS.setValue("BOTH")
    elif ((getDevice == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")):
        GroupsCluster.setVisible(True)
        GroupsCluster.setValue(True)
        GroupsCluster.setReadOnly(True)
        GroupsClusterCS.setValue("BOTH")
    elif ((getDevice == "ZIGBEE_CUSTOM")):
        GroupsCluster.setVisible(True)
        GroupsCluster.setValue(True)
        GroupsClusterCS.setValue("BOTH")
    else:
        GroupsCluster.setVisible(False)
    GroupsCluster.setReadOnly(True)
    GroupsClusterCS.setReadOnly(True)

def GroupsClusterServerAttributeCountUpdate(symbol, event):
    count = 0
    if (GroupsClusterServerAttributeIdentifyTime.getValue()):
        count += 1
    if (GroupsClusterServerAttributeClusterRevision.getValue()):
        count += 1
    GroupsClusterServerAttributeCount.setValue(count) 
    return count

def GroupsClusterServerCommandCountUpdate(symbol, event):
    count = 0
    if (GroupsClusterServerAddGroup.getValue()):
        count += 1
    if (GroupsClusterServerCommandsViewGroup.getValue()):
        count += 1
    if (GroupsClusterServerCommandsGroupMembership.getValue()):
        count += 1
    if (GroupsClusterServerCommandsRemoveGroup.getValue()):
        count += 1
    if (GroupsClusterServerCommandsRemoveAllGroup.getValue()):
        count += 1
    if (GroupsClusterServerAddGroupIf.getValue()):
        count += 1
    if (GroupsClusterServerAddGroupResp.getValue()):
        count += 1
    if (GroupsClusterServerCommandsViewGroupResp.getValue()):
        count += 1
    if (GroupsClusterServerCommandsGroupMembershipResp.getValue()):
        count += 1
    if (GroupsClusterServerCommandsRemoveGroupResp.getValue()):
        count += 1	
    GroupsClusterServerCommandCount.setValue(count)
    return count

def GroupsClusterClientAttributeCountUpdate(symbol, event):
    count = 0
    if (GroupsClusterClientAttributeClusterRevision.getValue()):
        count += 1
    GroupsClusterClientAttributeCount.setValue(count)
    return count

def GroupsClusterClientCommandCountUpdate(symbol, event):
    count = 0
    if (GroupsClusterClientAddGroup.getValue()):
        count += 1
    if (GroupsClusterClientCommandsViewGroup.getValue()):
        count += 1
    if (GroupsClusterClientCommandsGroupMembership.getValue()):
        count += 1
    if (GroupsClusterClientCommandsRemoveGroup.getValue()):
        count += 1
    if (GroupsClusterClientCommandsRemoveAllGroup.getValue()):
        count += 1
    if (GroupsClusterClientAddGroupIf.getValue()):
        count += 1
    if (GroupsClusterClientAddGroupResp.getValue()):
        count += 1
    if (GroupsClusterClientCommandsViewGroupResp.getValue()):
        count += 1
    if (GroupsClusterClientCommandsGroupMembershipResp.getValue()):
        count += 1
    if (GroupsClusterClientCommandsRemoveGroupResp.getValue()):
        count += 1	
    GroupsClusterClientCommandCount.setValue(count)
    return count
############################################################################################################
##################################### Configuration Item Definitions #######################################
############################################################################################################

global GroupsCluster
GroupsCluster = drvZigbeeComponent.createBooleanSymbol("GROUPS_CLUSTER_ENABLE", clusterConfigMenu)
GroupsCluster.setLabel("0x0004 Groups Cluster")
GroupsCluster.setDefaultValue(False)
GroupsCluster.setVisible(False)
GroupsCluster.setDescription("GROUPS CLUSTER- check the box to enable")

global GroupsClusterCS
GroupsClusterCS = drvZigbeeComponent.createComboSymbol("GROUPS_CLUSTER_CS",  GroupsCluster, ["CLIENT","SERVER", "BOTH"])
GroupsClusterCS.setLabel("Supported Implementation")
GroupsClusterCS.setDefaultValue("")
GroupsClusterCS.setVisible(False)
GroupsClusterCS.setDescription("GROUPS CLUSTER Supported Implementation- check the box to enable")
GroupsClusterCS.setDependencies(groupsclusterCsCheck,["GROUPS_CLUSTER_ENABLE"])

GroupsClusterClientMenu = drvZigbeeComponent.createMenuSymbol("GROUPS_CLUSTER_CLIENT_MENU", GroupsCluster)
GroupsClusterClientMenu.setLabel("Client")
GroupsClusterClientMenu.setVisible(False)
GroupsClusterClientMenu.setDescription("GROUPS CLUSTER CLIENT")
GroupsClusterClientMenu.setDependencies(groupsclusterClientCheck,["GROUPS_CLUSTER_CS","GROUPS_CLUSTER_ENABLE"])

GroupsClusterServerMenu = drvZigbeeComponent.createMenuSymbol("GROUPS_CLUSTER_SERVER_MENU", GroupsCluster)
GroupsClusterServerMenu.setLabel("Server")
GroupsClusterServerMenu.setVisible(False)
GroupsClusterServerMenu.setDescription("GROUPS CLUSTER SERVER")
GroupsClusterServerMenu.setDependencies(groupsclusterServerCheck,["GROUPS_CLUSTER_CS","GROUPS_CLUSTER_ENABLE"])

GroupsClusterClientAttributes = drvZigbeeComponent.createMenuSymbol("GROUPS_CLUSTER_CLIENT__ATTRIBUTES_MENU", GroupsClusterClientMenu)
GroupsClusterClientAttributes.setLabel("Attributes")
#GroupsClusterClientAttributes.setVisible(False)
GroupsClusterClientAttributes.setDescription("GROUPS CLUSTER CLIENT ATTRIBUTES")
GroupsClusterClientAttributes.setDependencies(groupsclusterClientCheck,["GROUPS_CLUSTER_CS"])

GroupsClusterClientCommands = drvZigbeeComponent.createMenuSymbol("GROUPS_CLUSTER_CLIENT__COMMANDS_MENU", GroupsClusterClientMenu)
GroupsClusterClientCommands.setLabel("Commands")
#GroupsClusterClientCommands.setVisible(False)
GroupsClusterClientCommands.setDescription("GROUPS CLUSTER CLIENT COMMANDS")
GroupsClusterClientCommands.setDependencies(groupsclusterClientCheck,["GROUPS_CLUSTER_CS"])

GroupsClusterServerAttributes = drvZigbeeComponent.createMenuSymbol("GROUPS_CLUSTER_SERVER__ATTRIBUTES_MENU", GroupsClusterServerMenu)
GroupsClusterServerAttributes.setLabel("Attributes")
#GroupsClusterServerAttributes.setVisible(False)
GroupsClusterServerAttributes.setDescription("GROUPS CLUSTER SERVER ATTRIBUTES")
GroupsClusterServerAttributes.setDependencies(groupsclusterServerCheck,["GROUPS_CLUSTER_CS"])

GroupsClusterServerCommands = drvZigbeeComponent.createMenuSymbol("GROUPS_CLUSTER_SERVER__COMMANDS_MENU", GroupsClusterServerMenu)
GroupsClusterServerCommands.setLabel("Commands")
#GroupsClusterServerCommands.setVisible(False)
GroupsClusterServerCommands.setDescription("GROUPS CLUSTER SERVER COMMANDS")
GroupsClusterServerCommands.setDependencies(groupsclusterServerCheck,["GROUPS_CLUSTER_CS"])

#################               Server Attributes                                 ###############

global GroupsClusterServerAttributeIdentifyTime
GroupsClusterServerAttributeIdentifyTime = drvZigbeeComponent.createBooleanSymbol("GC_NAMESUPPORT", GroupsClusterServerAttributes)
GroupsClusterServerAttributeIdentifyTime.setLabel("0x0000 NameSupport")
GroupsClusterServerAttributeIdentifyTime.setDefaultValue(True)
GroupsClusterServerAttributeIdentifyTime.setReadOnly(True)

global GroupsClusterServerAttributeClusterRevision
GroupsClusterServerAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("GCS_CLUSTERREVISION", GroupsClusterServerAttributes)
GroupsClusterServerAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
GroupsClusterServerAttributeClusterRevision.setDefaultValue(True)
GroupsClusterServerAttributeClusterRevision.setReadOnly(True)

global GroupsClusterServerAttributeCount
GroupsClusterServerAttributeCount = drvZigbeeComponent.createIntegerSymbol("GCS_SERVERATTRIBUTECOUNT", GroupsClusterServerAttributes)
GroupsClusterServerAttributeCount.setLabel("Attributes Count")
GroupsClusterServerAttributeCount.setDefaultValue(GroupsClusterServerAttributeCountUpdate(0,0))
GroupsClusterServerAttributeCount.setVisible(True)
GroupsClusterServerAttributeCount.setDescription("Attributes Count")
GroupsClusterServerAttributeCount.setReadOnly(True)
GroupsClusterServerAttributeCount.setDependencies(GroupsClusterServerAttributeCountUpdate,["GC_NAMESUPPORT","GCS_CLUSTERREVISION"])

#################               Server Commands                                 ###############

global GroupsClusterServerAddGroup
GroupsClusterServerAddGroup = drvZigbeeComponent.createBooleanSymbol("GC_ADDGROUP", GroupsClusterServerCommands)
GroupsClusterServerAddGroup.setLabel("0x00.Rx Add group")
GroupsClusterServerAddGroup.setDefaultValue(True)
GroupsClusterServerAddGroup.setDescription("Receive Add Group command - check the box to enable")
GroupsClusterServerAddGroup.setReadOnly(True)

global GroupsClusterServerCommandsViewGroup
GroupsClusterServerCommandsViewGroup = drvZigbeeComponent.createBooleanSymbol("GC_VIEWGROUP", GroupsClusterServerCommands)
GroupsClusterServerCommandsViewGroup.setLabel("0x01.Rx View group")
GroupsClusterServerCommandsViewGroup.setDefaultValue(True)
GroupsClusterServerCommandsViewGroup.setDescription("Receive View Group command - check the box to enable")
GroupsClusterServerCommandsViewGroup.setReadOnly(True)

global GroupsClusterServerCommandsGroupMembership
GroupsClusterServerCommandsGroupMembership = drvZigbeeComponent.createBooleanSymbol("GC_GROUPMEM", GroupsClusterServerCommands)
GroupsClusterServerCommandsGroupMembership.setLabel("0x02.Rx Get group membership")
GroupsClusterServerCommandsGroupMembership.setDefaultValue(True)
GroupsClusterServerCommandsGroupMembership.setDescription("Receive Get Group Membership- check the box to enable")
GroupsClusterServerCommandsGroupMembership.setReadOnly(True)

global GroupsClusterServerCommandsRemoveGroup
GroupsClusterServerCommandsRemoveGroup = drvZigbeeComponent.createBooleanSymbol("GC_REMOVEGROUP", GroupsClusterServerCommands)
GroupsClusterServerCommandsRemoveGroup.setLabel("0x03.Rx Remove group")
GroupsClusterServerCommandsRemoveGroup.setDefaultValue(True)
GroupsClusterServerCommandsRemoveGroup.setDescription("Receive Remove Group command - check the box to enable")
GroupsClusterServerCommandsRemoveGroup.setReadOnly(True)

global GroupsClusterServerCommandsRemoveAllGroup
GroupsClusterServerCommandsRemoveAllGroup = drvZigbeeComponent.createBooleanSymbol("GC_REMOVEGROUPALL", GroupsClusterServerCommands)
GroupsClusterServerCommandsRemoveAllGroup.setLabel("0x04.Rx Remove all groups")
GroupsClusterServerCommandsRemoveAllGroup.setDefaultValue(True)
GroupsClusterServerCommandsRemoveAllGroup.setDescription("Receive Remove Group command - check the box to enable")
GroupsClusterServerCommandsRemoveAllGroup.setReadOnly(True)

global GroupsClusterServerAddGroupIf
GroupsClusterServerAddGroupIf = drvZigbeeComponent.createBooleanSymbol("GC_ADDGROUPIF", GroupsClusterServerCommands)
GroupsClusterServerAddGroupIf.setLabel("0x05.Rx Add group if identifying")
GroupsClusterServerAddGroupIf.setDefaultValue(True)
GroupsClusterServerAddGroupIf.setDescription("Receive Add Group If identifying command - check the box to enable")
GroupsClusterServerAddGroupIf.setReadOnly(True)

global GroupsClusterServerAddGroupResp
GroupsClusterServerAddGroupResp = drvZigbeeComponent.createBooleanSymbol("GC_ADDGROUPRESP", GroupsClusterServerCommands)
GroupsClusterServerAddGroupResp.setLabel("0x00.Tx Add group response")
GroupsClusterServerAddGroupResp.setDefaultValue(True)
GroupsClusterServerAddGroupResp.setDescription("Sends Add Group Response- check the box to enable")
GroupsClusterServerAddGroupResp.setReadOnly(True)

global GroupsClusterServerCommandsViewGroupResp
GroupsClusterServerCommandsViewGroupResp = drvZigbeeComponent.createBooleanSymbol("GC_VIEWGROUPRESP", GroupsClusterServerCommands)
GroupsClusterServerCommandsViewGroupResp.setLabel("0x01.Tx View group response")
GroupsClusterServerCommandsViewGroupResp.setDefaultValue(True)
GroupsClusterServerCommandsViewGroupResp.setDescription("Sends View Group response command - check the box to enable")
GroupsClusterServerCommandsViewGroupResp.setReadOnly(True)

global GroupsClusterServerCommandsGroupMembershipResp
GroupsClusterServerCommandsGroupMembershipResp = drvZigbeeComponent.createBooleanSymbol("GC_GROUPMEMRESP", GroupsClusterServerCommands)
GroupsClusterServerCommandsGroupMembershipResp.setLabel("0x02.Tx Get group membership response")
GroupsClusterServerCommandsGroupMembershipResp.setDefaultValue(True)
GroupsClusterServerCommandsGroupMembershipResp.setDescription("Sends Get Group Membership response- check the box to enable")
GroupsClusterServerCommandsGroupMembershipResp.setReadOnly(True)

global GroupsClusterServerCommandsRemoveGroupResp
GroupsClusterServerCommandsRemoveGroupResp = drvZigbeeComponent.createBooleanSymbol("GC_REMOVEGROUPRESP", GroupsClusterServerCommands)
GroupsClusterServerCommandsRemoveGroupResp.setLabel("0x03.Tx Remove group response")
GroupsClusterServerCommandsRemoveGroupResp.setDefaultValue(True)
GroupsClusterServerCommandsRemoveGroupResp.setDescription("Sends Remove Group response command - check the box to enable")
GroupsClusterServerCommandsRemoveGroupResp.setReadOnly(True)

global GroupsClusterServerCommandCount
GroupsClusterServerCommandCount = drvZigbeeComponent.createIntegerSymbol("GC_SERVERCOMMANDCOUNT", GroupsClusterServerCommands)
GroupsClusterServerCommandCount.setLabel("Commands Count")
GroupsClusterServerCommandCount.setDefaultValue(GroupsClusterServerCommandCountUpdate(0,0))
GroupsClusterServerCommandCount.setVisible(True)
GroupsClusterServerCommandCount.setDescription("Commands Count")
GroupsClusterServerCommandCount.setReadOnly(True)
GroupsClusterServerCommandCount.setDependencies(GroupsClusterServerCommandCountUpdate,["GC_ADDGROUPRESP", "GC_VIEWGROUPRESP", "GC_GROUPMEMRESP", "GC_REMOVEGROUPRESP","GC_ADDGROUP", "GC_VIEWGROUP", "GC_GROUPMEM","GC_REMOVEGROUP","GC_REMOVEGROUPALL","GC_ADDGROUPIF"])


#################               Client Attributes                                 ###############
global GroupsClusterClientAttributeClusterRevision
GroupsClusterClientAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("GCC_CLUSTERREVISION", GroupsClusterClientAttributes)
GroupsClusterClientAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
GroupsClusterClientAttributeClusterRevision.setDefaultValue(True)
GroupsClusterClientAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
GroupsClusterClientAttributeClusterRevision.setReadOnly(True)

global GroupsClusterClientAttributeCount
GroupsClusterClientAttributeCount = drvZigbeeComponent.createIntegerSymbol("GCC_CLIENTATTRIBUTECOUNT", GroupsClusterClientAttributes)
GroupsClusterClientAttributeCount.setLabel("Attributes Count")
GroupsClusterClientAttributeCount.setDefaultValue(GroupsClusterClientAttributeCountUpdate(0,0))
GroupsClusterClientAttributeCount.setVisible(True)
GroupsClusterClientAttributeCount.setDescription("Attributes Count")
GroupsClusterClientAttributeCount.setReadOnly(True)
GroupsClusterClientAttributeCount.setDependencies(GroupsClusterClientAttributeCountUpdate,["GCC_CLUSTERREVISION"])

#################               Client Commands                                 ###############
global GroupsClusterClientAddGroupResp
GroupsClusterClientAddGroupResp = drvZigbeeComponent.createBooleanSymbol("GCC_ADDGROUPRESP", GroupsClusterClientCommands)
GroupsClusterClientAddGroupResp.setLabel("0x00.Rx Add group response")
GroupsClusterClientAddGroupResp.setDefaultValue(True)
GroupsClusterClientAddGroupResp.setDescription("Receive Add Group Response- check the box to enable")
GroupsClusterClientAddGroupResp.setReadOnly(True)

global GroupsClusterClientCommandsViewGroupResp
GroupsClusterClientCommandsViewGroupResp = drvZigbeeComponent.createBooleanSymbol("GCC_VIEWGROUPRESP", GroupsClusterClientCommands)
GroupsClusterClientCommandsViewGroupResp.setLabel("0x01.Rx View group response")
GroupsClusterClientCommandsViewGroupResp.setDefaultValue(True)
GroupsClusterClientCommandsViewGroupResp.setDescription("Receive View Group response command - check the box to enable")
GroupsClusterClientCommandsViewGroupResp.setReadOnly(True)

global GroupsClusterClientCommandsGroupMembershipResp
GroupsClusterClientCommandsGroupMembershipResp = drvZigbeeComponent.createBooleanSymbol("GCC_GROUPMEMRESP", GroupsClusterClientCommands)
GroupsClusterClientCommandsGroupMembershipResp.setLabel("0x02.Rx Get group membership response")
GroupsClusterClientCommandsGroupMembershipResp.setDefaultValue(True)
GroupsClusterClientCommandsGroupMembershipResp.setDescription("Receive Group Membership response- check the box to enable")
GroupsClusterClientCommandsGroupMembershipResp.setReadOnly(True)

global GroupsClusterClientCommandsRemoveGroupResp
GroupsClusterClientCommandsRemoveGroupResp = drvZigbeeComponent.createBooleanSymbol("GCC_REMOVEGROUPRESP", GroupsClusterClientCommands)
GroupsClusterClientCommandsRemoveGroupResp.setLabel("0x03.Rx Remove group response")
GroupsClusterClientCommandsRemoveGroupResp.setDefaultValue(True)
GroupsClusterClientCommandsRemoveGroupResp.setDescription("Receive Remove Group response command - check the box to enable")
GroupsClusterClientCommandsRemoveGroupResp.setReadOnly(True)

global GroupsClusterClientAddGroup
GroupsClusterClientAddGroup = drvZigbeeComponent.createBooleanSymbol("GCC_ADDGROUP", GroupsClusterClientCommands)
GroupsClusterClientAddGroup.setLabel("0x00.Tx Add group")
GroupsClusterClientAddGroup.setDefaultValue(True)
GroupsClusterClientAddGroup.setDescription("Sends Add Group command - check the box to enable")
GroupsClusterClientAddGroup.setReadOnly(True)

global GroupsClusterClientCommandsViewGroup
GroupsClusterClientCommandsViewGroup = drvZigbeeComponent.createBooleanSymbol("GCC_VIEWGROUP", GroupsClusterClientCommands)
GroupsClusterClientCommandsViewGroup.setLabel("0x01.Tx View group")
GroupsClusterClientCommandsViewGroup.setDefaultValue(True)
GroupsClusterClientCommandsViewGroup.setDescription("Sends View Group command - check the box to enable")

global GroupsClusterClientCommandsGroupMembership
GroupsClusterClientCommandsGroupMembership = drvZigbeeComponent.createBooleanSymbol("GCC_GROUPMEM", GroupsClusterClientCommands)
GroupsClusterClientCommandsGroupMembership.setLabel("0x02.Tx Get group membership")
GroupsClusterClientCommandsGroupMembership.setDefaultValue(True)
GroupsClusterClientCommandsGroupMembership.setDescription("Sends Group Membership- check the box to enable")

global GroupsClusterClientCommandsRemoveGroup
GroupsClusterClientCommandsRemoveGroup = drvZigbeeComponent.createBooleanSymbol("GCC_REMOVEGROUP", GroupsClusterClientCommands)
GroupsClusterClientCommandsRemoveGroup.setLabel("0x03.Tx Remove group")
GroupsClusterClientCommandsRemoveGroup.setDefaultValue(True)
GroupsClusterClientCommandsRemoveGroup.setDescription("Sends Remove Group command - check the box to enable")

global GroupsClusterClientCommandsRemoveAllGroup
GroupsClusterClientCommandsRemoveAllGroup = drvZigbeeComponent.createBooleanSymbol("GCC_REMOVEGROUPALL", GroupsClusterClientCommands)
GroupsClusterClientCommandsRemoveAllGroup.setLabel("0x04.Tx Remove all groups")
GroupsClusterClientCommandsRemoveAllGroup.setDefaultValue(True)
GroupsClusterClientCommandsRemoveAllGroup.setDescription("Sends Remove Group command - check the box to enable")

global GroupsClusterClientAddGroupIf
GroupsClusterClientAddGroupIf = drvZigbeeComponent.createBooleanSymbol("GCC_ADDGROUPIF", GroupsClusterClientCommands)
GroupsClusterClientAddGroupIf.setLabel("0x05.Tx Add group if identifying")
GroupsClusterClientAddGroupIf.setDefaultValue(True)
GroupsClusterClientAddGroupIf.setDescription("Sends Add Group If identifying command - check the box to enable")

global GroupsClusterClientCommandCount
GroupsClusterClientCommandCount = drvZigbeeComponent.createIntegerSymbol("GCC_CLIENTCOMMANDCOUNT", GroupsClusterClientCommands)
GroupsClusterClientCommandCount.setLabel("Commands Count")
GroupsClusterClientCommandCount.setDefaultValue(GroupsClusterClientCommandCountUpdate(0,0))
GroupsClusterClientCommandCount.setVisible(True)
GroupsClusterClientCommandCount.setDescription("Commands Count")
GroupsClusterClientCommandCount.setReadOnly(True)
GroupsClusterClientCommandCount.setDependencies(GroupsClusterClientCommandCountUpdate,["GCC_ADDGROUPRESP", "GCC_VIEWGROUPRESP", "GCC_GROUPMEMRESP", "GCC_REMOVEGROUPRESP","GCC_ADDGROUP", "GCC_VIEWGROUP", "GCC_GROUPMEM","GCC_REMOVEGROUP","GCC_REMOVEGROUPALL","GCC_ADDGROUPIF"])

############################################################################################################
# Default Values Settings based on device type
groupsClusterHandling()

############################################################################################################
##################################### FTL Files Definitions ################################################
############################################################################################################

# GROUPS CLUSTER Common header
groupsClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_GROUPS_CLUSTER_CONF", None)
groupsClusterConf.setSourcePath("/driver/zigbee/templates/cluster/groups/zclGroupsCluster.h.ftl")
groupsClusterConf.setOutputName("zclGroupsCluster.h")
groupsClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
groupsClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
groupsClusterConf.setType("HEADER")
groupsClusterConf.setOverwrite(True)
groupsClusterConf.setMarkup(True)

groupsClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_GROUPS_CLUSTER_CONF2", None)
groupsClusterConf.setSourcePath("/driver/zigbee/templates/cluster/groups/zclZllGroupsCluster.h.ftl")
groupsClusterConf.setOutputName("zclZllGroupsCluster.h")
groupsClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
groupsClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
groupsClusterConf.setType("HEADER")
groupsClusterConf.setOverwrite(True)
groupsClusterConf.setMarkup(True)

groupsClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_GROUPSCLUSTER_CONF_SRC1", None)
groupsClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/groups/groupsCluster.c.ftl")
groupsClusterConfSrc.setOutputName("groupsCluster.c")
groupsClusterConfSrc.setDestPath("/zigbee/z3device/clusters")
groupsClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/clusters/")
groupsClusterConfSrc.setType("SOURCE")
groupsClusterConfSrc.setOverwrite(True)
groupsClusterConfSrc.setMarkup(True)

# GROUPS CLUSTER - Light
groupsClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_GROUPS_CLUSTER_CONF_SRC_LIGHT", None)
groupsClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/groups/lightGroupsCluster.c.ftl")
groupsClusterConfSrc.setOutputName("lightGroupsCluster.c")
groupsClusterConfSrc.setDestPath("/zigbee/z3device/light")
groupsClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/light/")
groupsClusterConfSrc.setType("SOURCE")
groupsClusterConfSrc.setOverwrite(True)
groupsClusterConfSrc.setMarkup(True)
groupsClusterConfSrc.setEnabled(checkDevTypeLight)

# GROUPS CLUSTER - Custom
groupsClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_GROUPS_CLUSTER_CONF_SRC_CUSTOM", None)
groupsClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/groups/customGroupsCluster.c.ftl")
groupsClusterConfSrc.setOutputName("customGroupsCluster.c")
groupsClusterConfSrc.setDestPath("/zigbee/z3device/custom")
groupsClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/custom/")
groupsClusterConfSrc.setType("SOURCE")
groupsClusterConfSrc.setOverwrite(True)
groupsClusterConfSrc.setMarkup(True)
groupsClusterConfSrc.setEnabled(checkDevTypeCustom and GroupsCluster.getValue())

# GROUPS CLUSTER - Color Scene Controller
groupsClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_GROUPS_CLUSTER_CONF_SRC_CSC", None)
groupsClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/groups/cscGroupsCluster.c.ftl")
groupsClusterConfSrc.setOutputName("cscGroupsCluster.c")
groupsClusterConfSrc.setDestPath("/zigbee/z3device/colorSceneController")
groupsClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/colorSceneController/")
groupsClusterConfSrc.setType("SOURCE")
groupsClusterConfSrc.setOverwrite(True)
groupsClusterConfSrc.setMarkup(True)
groupsClusterConfSrc.setEnabled(checkDevTypeRemote)

# GROUPS CLUSTER - Combined Interface
groupsClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_GROUPS_CLUSTER_CONF_SRC_CI", None)
groupsClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/groups/ciGroupsCluster.c.ftl")
groupsClusterConfSrc.setOutputName("ciGroupsCluster.c")
groupsClusterConfSrc.setDestPath("/zigbee/z3device/combinedInterface")
groupsClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/combinedInterface/")
groupsClusterConfSrc.setType("SOURCE")
groupsClusterConfSrc.setOverwrite(True)
groupsClusterConfSrc.setMarkup(True)
groupsClusterConfSrc.setEnabled(checkDevTypeCombInterface)

# GROUPS CLUSTER - IAS ACE
groupsClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_GROUPS_CLUSTER_CONF_SRC_IAS", None)
groupsClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/groups/iasACEGroupsCluster.c.ftl")
groupsClusterConfSrc.setOutputName("iasACEGroupsCluster.c")
groupsClusterConfSrc.setDestPath("/zigbee/z3device/ias_ace")
groupsClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/ias_ace/")
groupsClusterConfSrc.setType("SOURCE")
groupsClusterConfSrc.setOverwrite(True)
groupsClusterConfSrc.setMarkup(True)
groupsClusterConfSrc.setEnabled(checkDevTypeIasAce)

# GROUPS CLUSTER - Multi Sensor
# GROUPS CLUSTER - Humidity Sensor
groupsClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_GROUPS_CLUSTER_CONF_SRC_HS", None)
groupsClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/groups/hsGroupsCluster.c.ftl")
groupsClusterConfSrc.setOutputName("hsGroupsCluster.c")
groupsClusterConfSrc.setDestPath("/zigbee/z3device/multiSensor")
groupsClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/multiSensor/")
groupsClusterConfSrc.setType("SOURCE")
groupsClusterConfSrc.setOverwrite(True)
groupsClusterConfSrc.setMarkup(True)
groupsClusterConfSrc.setEnabled(checkDevTypeMultiSensor)

# GROUPS CLUSTER - Occupancy Sensor
groupsClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_GROUPS_CLUSTER_CONF_SRC_OS", None)
groupsClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/groups/osGroupsCluster.c.ftl")
groupsClusterConfSrc.setOutputName("osGroupsCluster.c")
groupsClusterConfSrc.setDestPath("/zigbee/z3device/multiSensor")
groupsClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/multiSensor/")
groupsClusterConfSrc.setType("SOURCE")
groupsClusterConfSrc.setOverwrite(True)
groupsClusterConfSrc.setMarkup(True)
groupsClusterConfSrc.setEnabled(checkDevTypeMultiSensor)

# GROUPS CLUSTER - Temperature Sensor
groupsClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_GROUPS_CLUSTER_CONF_SRC_TS", None)
groupsClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/groups/tsGroupsCluster.c.ftl")
groupsClusterConfSrc.setOutputName("tsGroupsCluster.c")
groupsClusterConfSrc.setDestPath("/zigbee/z3device/multiSensor")
groupsClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/multiSensor/")
groupsClusterConfSrc.setType("SOURCE")
groupsClusterConfSrc.setOverwrite(True)
groupsClusterConfSrc.setMarkup(True)
groupsClusterConfSrc.setEnabled(checkDevTypeMultiSensor)

# GROUPS CLUSTER - Thermostat
groupsClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_GROUPS_CLUSTER_CONF_SRC_TH", None)
groupsClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/groups/thGroupsCluster.c.ftl")
groupsClusterConfSrc.setOutputName("thGroupsCluster.c")
groupsClusterConfSrc.setDestPath("/zigbee/z3device/thermostat")
groupsClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/thermostat/")
groupsClusterConfSrc.setType("SOURCE")
groupsClusterConfSrc.setOverwrite(True)
groupsClusterConfSrc.setMarkup(True)
groupsClusterConfSrc.setEnabled(checkDevTypeThermostat)
############################################################################################################
