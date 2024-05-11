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
###########################################  ALARMS CLUSTER CONFIGURATION   #################################
############################################################################################################

############################################################################################################
############################################# Function Definitions #########################################
############################################################################################################
def alarmsClusterCsCheck(symbol, event):
    if (alarmsCluster.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def alarmsClusterEnableCheck(symbol, event):
    if (alarmsCluster.getValue() == False):
        symbol.setEnabled(False)
    else:
        symbol.setEnabled(True)

def customAlarmsClusterEnableCheck(symbol, event):
    if ((zigbeeDeviceType.getValue() == 'ZIGBEE_CUSTOM') and (alarmsCluster.getValue() == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def combinedInterfaceAlarmsClusterEnableCheck(symbol, event):
    if ((zigbeeDeviceType.getValue() == 'ZIGBEE_COMBINED_INTERFACE') and (alarmsCluster.getValue() == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def alarmsClusterClientCheck(symbol, event):
    if ((alarmsCluster.getValue() == False) or alarmsClusterCS.getValue() == "SERVER"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def alarmsClusterServerCheck(symbol, event):
    if ((alarmsCluster.getValue() == False) or alarmsClusterCS.getValue() == "CLIENT"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def alarmsClusterHandling():

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
        alarmsCluster.setVisible(False)
        alarmsCluster.setValue(False)
    elif ((getDevice == "ZIGBEE_COMBINED_INTERFACE")):
        alarmsCluster.setVisible(True)
        alarmsCluster.setValue(True)
        alarmsCluster.setReadOnly(False)
        alarmsClusterCS.setValue("CLIENT")
        alarmsClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_THERMOSTAT")):
        alarmsCluster.setVisible(True)
        alarmsCluster.setValue(True)
        alarmsCluster.setReadOnly(True)
        alarmsClusterCS.setValue("SERVER")
        alarmsClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_CUSTOM")):
        alarmsCluster.setVisible(True)
        alarmsCluster.setValue(True)
        alarmsClusterCS.setValue("SERVER")
        alarmsClusterCS.setVisible(True)
        alarmsClusterClientMenu.setVisible(False)
        alarmsClusterServerMenu.setVisible(True)
    else:
        alarmsCluster.setVisible(False)

def alarmsClusterServerAttributeCountUpdate(symbol, event):
    count = 0
    if (alarmsClusterServerAttributeAlarmCount.getValue()):
        count += 1
    if (alarmsClusterServerAttributeClusterRevision.getValue()):
        count += 1
    alarmsClusterServerAttributeCount.setValue(count) 
    return count

def alarmsClusterServerCommandCountUpdate(symbol, event):
    count = 0
    if (alarmsClusterServerCommandResetAlarm.getValue()):
        count += 1
    if (alarmsClusterServerCommandResetAllAlarm.getValue()):
        count += 1
    if (alarmsClusterServerCommandGetAlarm.getValue()):
        count += 1
    if (alarmsClusterServerCommandResetAlarmLog.getValue()):
        count += 1
    if (alarmsClusterServerCommandAlarm.getValue()):
        count += 1
    if (alarmsClusterServerCommandAlarmResp.getValue()):
        count += 1
    alarmsClusterServerCommandCount.setValue(count)
    return count

def alarmsClusterClientAttributeCountUpdate(symbol, event):
    count = 0
    if (alarmsClusterClientAttributeClusterRevision.getValue()):
        count += 1
    alarmsClusterClientAttributeCount.setValue(count)
    return count

def alarmsClusterClientCommandCountUpdate(symbol, event):
    count = 0
    if (alarmsClusterClientCommandResetAlarm.getValue()):
        count += 1
    if (alarmsClusterClientCommandResetAllAlarm.getValue()):
        count += 1
    if (alarmsClusterClientCommandGetAlarm.getValue()):
        count += 1
    if (alarmsClusterClientCommandResetAlarmLog.getValue()):
        count += 1
    if (alarmsClusterClientCommandAlarm.getValue()):
        count += 1
    if (alarmsClusterClientCommandAlarmResp.getValue()):
        count += 1
    alarmsClusterClientCommandCount.setValue(count)
    return count
############################################################################################################
##################################### Configuration Item Definitions #######################################
############################################################################################################

global alarmsCluster
alarmsCluster = drvZigbeeComponent.createBooleanSymbol("ALARMS_CLUSTER_ENABLE", clusterConfigMenu)
alarmsCluster.setLabel("0x0009 Alarms Cluster")
alarmsCluster.setDefaultValue(False)
alarmsCluster.setVisible(False)
alarmsCluster.setDescription("ALARMS CLUSTER- check the box to enable")
alarmsCluster.setReadOnly(False)

global alarmsClusterCS
alarmsClusterCS = drvZigbeeComponent.createComboSymbol("ALARMS_CLUSTER_CS",  alarmsCluster, ["CLIENT","SERVER", "BOTH"])
alarmsClusterCS.setLabel("Supported Implementation")
alarmsClusterCS.setDefaultValue("BOTH")
#alarmsClusterCS.setVisible(False)
alarmsClusterCS.setDescription("Alarms Cluster Supported Implementation- Select the option")
alarmsClusterCS.setDependencies(alarmsClusterCsCheck,["ALARMS_CLUSTER_ENABLE"])

global alarmsClusterClientMenu
alarmsClusterClientMenu = drvZigbeeComponent.createMenuSymbol("ALARMS_CLUSTER_CLIENT_MENU", alarmsCluster)
alarmsClusterClientMenu.setLabel("Client")
#alarmsClusterClientMenu.setVisible(False)
alarmsClusterClientMenu.setDescription("ALARMS CLUSTER CLIENT")
alarmsClusterClientMenu.setDependencies(alarmsClusterClientCheck,["ALARMS_CLUSTER_CS","ALARMS_CLUSTER_ENABLE"])

global alarmsClusterServerMenu
alarmsClusterServerMenu = drvZigbeeComponent.createMenuSymbol("ALARMS_CLUSTER_SERVER_MENU", alarmsCluster)
alarmsClusterServerMenu.setLabel("Server")
#alarmsClusterServerMenu.setVisible(False)
alarmsClusterServerMenu.setDescription("ALARMS CLUSTER SERVER")
alarmsClusterServerMenu.setDependencies(alarmsClusterServerCheck,["ALARMS_CLUSTER_CS","ALARMS_CLUSTER_ENABLE"])

alarmsClusterClientAttributes = drvZigbeeComponent.createMenuSymbol("ALARMS_CLUSTER_CLIENT__ATTRIBUTES_MENU", alarmsClusterClientMenu)
alarmsClusterClientAttributes.setLabel("Attributes")
#alarmsClusterClientAttributes.setVisible(False)
alarmsClusterClientAttributes.setDescription("ALARMS CLUSTER CLIENT ATTRIBUTES")
alarmsClusterClientAttributes.setDependencies(alarmsClusterClientCheck,["ALARMS_CLUSTER_CS"])

alarmsClusterClientCommands = drvZigbeeComponent.createMenuSymbol("alarms_CLUSTER_CLIENT__COMMANDS_MENU", alarmsClusterClientMenu)
alarmsClusterClientCommands.setLabel("Commands")
#alarmsClusterClientCommands.setVisible(False)
alarmsClusterClientCommands.setDescription("ALARMS CLUSTER CLIENT COMMANDS")
alarmsClusterClientCommands.setDependencies(alarmsClusterClientCheck,["ALARMS_CLUSTER_CS"])

alarmsClusterServerAttributes = drvZigbeeComponent.createMenuSymbol("ALARMS_CLUSTER_SERVER__ATTRIBUTES_MENU", alarmsClusterServerMenu)
alarmsClusterServerAttributes.setLabel("Attributes")
#alarmsClusterServerAttributes.setVisible(False)
alarmsClusterServerAttributes.setDescription("ALARMS CLUSTER SERVER ATTRIBUTES")
alarmsClusterServerAttributes.setDependencies(alarmsClusterServerCheck,["ALARMS_CLUSTER_CS"])

alarmsClusterServerCommands = drvZigbeeComponent.createMenuSymbol("ALARMS_CLUSTER_SERVER__COMMANDS_MENU", alarmsClusterServerMenu)
alarmsClusterServerCommands.setLabel("Commands")
#alarmsClusterServerCommands.setVisible(False)
alarmsClusterServerCommands.setDescription("ALARMS CLUSTER SERVER COMMANDS")
alarmsClusterServerCommands.setDependencies(alarmsClusterServerCheck,["ALARMS_CLUSTER_CS"])

#################               Server Attributes                                 ###############

global alarmsClusterServerAttributeAlarmCount
alarmsClusterServerAttributeAlarmCount = drvZigbeeComponent.createBooleanSymbol("AC_ALARMCOUNT", alarmsClusterServerAttributes)
alarmsClusterServerAttributeAlarmCount.setLabel("0x0000 AlarmCount")
alarmsClusterServerAttributeAlarmCount.setDefaultValue(True)
alarmsClusterServerAttributeAlarmCount.setDescription("AlarmCount  - check the box to enable")

global alarmsClusterServerAttributeClusterRevision
alarmsClusterServerAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("AC_CLUSTERREVISION", alarmsClusterServerAttributes)
alarmsClusterServerAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
alarmsClusterServerAttributeClusterRevision.setDefaultValue(True)
alarmsClusterServerAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
alarmsClusterServerAttributeClusterRevision.setReadOnly(True)

global alarmsClusterServerAttributeCount
alarmsClusterServerAttributeCount = drvZigbeeComponent.createIntegerSymbol("AC_SERVERATTRIBUTECOUNT", alarmsClusterServerAttributes)
alarmsClusterServerAttributeCount.setLabel("Attributes Count")
alarmsClusterServerAttributeCount.setDefaultValue(alarmsClusterServerAttributeCountUpdate(0,0))
alarmsClusterServerAttributeCount.setVisible(True)
alarmsClusterServerAttributeCount.setDescription("Attributes Count")
alarmsClusterServerAttributeCount.setReadOnly(True)
alarmsClusterServerAttributeCount.setDependencies(alarmsClusterServerAttributeCountUpdate,["AC_ALARMCOUNT","AC_CLUSTERREVISION"])

#################               Server Commands                                 ###############

# Commands received
global alarmsClusterServerCommandResetAlarm
alarmsClusterServerCommandResetAlarm = drvZigbeeComponent.createBooleanSymbol("AS_RESETALARM", alarmsClusterServerCommands)
alarmsClusterServerCommandResetAlarm.setLabel("0x00.Rx Reset Alarm")
alarmsClusterServerCommandResetAlarm.setDefaultValue(True)
alarmsClusterServerCommandResetAlarm.setDescription("Receive Reset Alarm - check the box to enable")
alarmsClusterServerCommandResetAlarm.setReadOnly(True)

global alarmsClusterServerCommandResetAllAlarm
alarmsClusterServerCommandResetAllAlarm = drvZigbeeComponent.createBooleanSymbol("AS_RESETALLALARMS", alarmsClusterServerCommands)
alarmsClusterServerCommandResetAllAlarm.setLabel("0x01.Rx Reset All Alarms")
alarmsClusterServerCommandResetAllAlarm.setDefaultValue(True)
alarmsClusterServerCommandResetAllAlarm.setDescription("Receive Reset All Alarms  - check the box to enable")
alarmsClusterServerCommandResetAllAlarm.setReadOnly(True)

global alarmsClusterServerCommandGetAlarm
alarmsClusterServerCommandGetAlarm = drvZigbeeComponent.createBooleanSymbol("AS_GETALARM", alarmsClusterServerCommands)
alarmsClusterServerCommandGetAlarm.setLabel("0x02.Rx Get Alarm ")
alarmsClusterServerCommandGetAlarm.setDefaultValue(True)
alarmsClusterServerCommandGetAlarm.setDescription("Receive Get Alarm   - check the box to enable")

global alarmsClusterServerCommandResetAlarmLog
alarmsClusterServerCommandResetAlarmLog = drvZigbeeComponent.createBooleanSymbol("AS_RESETALLALARMLOG", alarmsClusterServerCommands)
alarmsClusterServerCommandResetAlarmLog.setLabel("0x03.Rx Reset Alarm Log ")
alarmsClusterServerCommandResetAlarmLog.setDefaultValue(True)
alarmsClusterServerCommandResetAlarmLog.setDescription("Receive Reset Alarm Log  - check the box to enable")

# Commands generated
global alarmsClusterServerCommandAlarm
alarmsClusterServerCommandAlarm = drvZigbeeComponent.createBooleanSymbol("AS_ALARM", alarmsClusterServerCommands)
alarmsClusterServerCommandAlarm.setLabel("0x00.Tx Alarm")
alarmsClusterServerCommandAlarm.setDefaultValue(True)
alarmsClusterServerCommandAlarm.setDescription("Transmits Alarm - check the box to enable")
alarmsClusterServerCommandAlarm.setReadOnly(True)

global alarmsClusterServerCommandAlarmResp
alarmsClusterServerCommandAlarmResp = drvZigbeeComponent.createBooleanSymbol("AS_GETALARMRESPONSE", alarmsClusterServerCommands)
alarmsClusterServerCommandAlarmResp.setLabel("0x01.Tx Get Alarm Response ")
alarmsClusterServerCommandAlarmResp.setDefaultValue(True)
alarmsClusterServerCommandAlarmResp.setDescription("Transmits Get Alarm Response  - check the box to enable")

global alarmsClusterServerCommandCount
alarmsClusterServerCommandCount = drvZigbeeComponent.createIntegerSymbol("AS_SERVERCOMMANDCOUNT", alarmsClusterServerCommands)
alarmsClusterServerCommandCount.setLabel("Commands Count")
alarmsClusterServerCommandCount.setDefaultValue(alarmsClusterServerCommandCountUpdate(0,0))
alarmsClusterServerCommandCount.setVisible(True)
alarmsClusterServerCommandCount.setDescription("Commands Count")
alarmsClusterServerCommandCount.setReadOnly(True)
alarmsClusterServerCommandCount.setDependencies(alarmsClusterServerCommandCountUpdate,["AS_RESETALARM","AS_RESETALLALARMS","AS_GETALARM","AS_RESETALLALARMLOG"
                                                                                      ,"AS_ALARM","AS_GETALARMRESPONSE"])

#################               Client Attributes                                 ###############
global alarmsClusterClientAttributeClusterRevision
alarmsClusterClientAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("ACC_CLUSTERREVISION", alarmsClusterClientAttributes)
alarmsClusterClientAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
alarmsClusterClientAttributeClusterRevision.setDefaultValue(True)
alarmsClusterClientAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
alarmsClusterClientAttributeClusterRevision.setReadOnly(True)

global alarmsClusterClientAttributeCount
alarmsClusterClientAttributeCount = drvZigbeeComponent.createIntegerSymbol("AC_CLIENTATTRIBUTECOUNT", alarmsClusterClientAttributes)
alarmsClusterClientAttributeCount.setLabel("Attributes Count")
alarmsClusterClientAttributeCount.setDefaultValue(alarmsClusterClientAttributeCountUpdate(0,0))
alarmsClusterClientAttributeCount.setVisible(True)
alarmsClusterClientAttributeCount.setDescription("Attributes Count")
alarmsClusterClientAttributeCount.setReadOnly(True)
alarmsClusterClientAttributeCount.setDependencies(alarmsClusterClientAttributeCountUpdate,["ACC_CLUSTERREVISION"])

#################               Client Commands                                 ###############

# Commands generated
global alarmsClusterClientCommandResetAlarm
alarmsClusterClientCommandResetAlarm = drvZigbeeComponent.createBooleanSymbol("AC_RESETALARM", alarmsClusterClientCommands)
alarmsClusterClientCommandResetAlarm.setLabel("0x00.Tx Reset Alarm")
alarmsClusterClientCommandResetAlarm.setDefaultValue(True)
alarmsClusterClientCommandResetAlarm.setDescription("Transmits Reset Alarm - check the box to enable")

global alarmsClusterClientCommandResetAllAlarm
alarmsClusterClientCommandResetAllAlarm = drvZigbeeComponent.createBooleanSymbol("AC_RESETALLALARMS", alarmsClusterClientCommands)
alarmsClusterClientCommandResetAllAlarm.setLabel("0x01.Tx Reset All Alarms")
alarmsClusterClientCommandResetAllAlarm.setDefaultValue(True)
alarmsClusterClientCommandResetAllAlarm.setDescription("Transmits Reset All Alarms  - check the box to enable")

global alarmsClusterClientCommandGetAlarm
alarmsClusterClientCommandGetAlarm = drvZigbeeComponent.createBooleanSymbol("AC_GETALARM", alarmsClusterClientCommands)
alarmsClusterClientCommandGetAlarm.setLabel("0x02.Tx Get Alarm ")
alarmsClusterClientCommandGetAlarm.setDefaultValue(True)
alarmsClusterClientCommandGetAlarm.setDescription("Transmits Get Alarm   - check the box to enable")

global alarmsClusterClientCommandResetAlarmLog
alarmsClusterClientCommandResetAlarmLog = drvZigbeeComponent.createBooleanSymbol("AC_RESETALARMLOG", alarmsClusterClientCommands)
alarmsClusterClientCommandResetAlarmLog.setLabel("0x03.Tx Reset Alarm Log ")
alarmsClusterClientCommandResetAlarmLog.setDefaultValue(True)
alarmsClusterClientCommandResetAlarmLog.setDescription("Transmits Reset Alarm Log  - check the box to enable")

# Commands received
global alarmsClusterClientCommandAlarm
alarmsClusterClientCommandAlarm = drvZigbeeComponent.createBooleanSymbol("AC_ALARM", alarmsClusterClientCommands)
alarmsClusterClientCommandAlarm.setLabel("0x00.Rx Alarm")
alarmsClusterClientCommandAlarm.setDefaultValue(True)
alarmsClusterClientCommandAlarm.setDescription("Receive Alarm - check the box to enable")

global alarmsClusterClientCommandAlarmResp
alarmsClusterClientCommandAlarmResp = drvZigbeeComponent.createBooleanSymbol("AC_GETALARMRESPONSE", alarmsClusterClientCommands)
alarmsClusterClientCommandAlarmResp.setLabel("0x01.Rx Get Alarm Response ")
alarmsClusterClientCommandAlarmResp.setDefaultValue(True)
alarmsClusterClientCommandAlarmResp.setDescription("Receive Get Alarm Response  - check the box to enable")

global alarmsClusterClientCommandCount
alarmsClusterClientCommandCount = drvZigbeeComponent.createIntegerSymbol("AC_CLIENTCOMMANDCOUNT", alarmsClusterClientCommands)
alarmsClusterClientCommandCount.setLabel("Commands Count")
alarmsClusterClientCommandCount.setDefaultValue(alarmsClusterClientCommandCountUpdate(0,0))
alarmsClusterClientCommandCount.setVisible(True)
alarmsClusterClientCommandCount.setDescription("Commands Count")
alarmsClusterClientCommandCount.setReadOnly(True)
alarmsClusterClientCommandCount.setDependencies(alarmsClusterClientCommandCountUpdate,["AC_RESETALARM","AC_RESETALLALARMS","AC_GETALARM","AC_RESETALARMLOG"
                                                                                      ,"AC_ALARM","AC_GETALARMRESPONSE"])

############################################################################################################
# Default Settings handling based on device type
alarmsClusterHandling()

############################################################################################################
##################################### FTL Files Definitions ################################################
############################################################################################################

# ALARMS CLUSTER Common header
alarmsClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_ALARMS_CLUSTER_CONF", None)
alarmsClusterConf.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/alarms/zclAlarmsCluster.h.ftl")
alarmsClusterConf.setOutputName("zclAlarmsCluster.h")
alarmsClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
alarmsClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
alarmsClusterConf.setType("HEADER")
alarmsClusterConf.setOverwrite(True)
alarmsClusterConf.setMarkup(True)

alarmsClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_ALARMSCLUSTER_CONF_SRC1", None)
alarmsClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/alarms/alarmsCluster.c.ftl")
alarmsClusterConfSrc.setOutputName("alarmCluster.c")
alarmsClusterConfSrc.setDestPath("/zigbee/z3device/clusters")
alarmsClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/clusters/")
alarmsClusterConfSrc.setType("SOURCE")
alarmsClusterConfSrc.setOverwrite(True)
alarmsClusterConfSrc.setMarkup(True)
alarmsClusterConfSrc.setEnabled(alarmsCluster.getValue())
alarmsClusterConfSrc.setDependencies(alarmsClusterEnableCheck,["ALARMS_CLUSTER_ENABLE"])

# ALARMS CLUSTER - Combined Interface
alarmsClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_ALARMS_CLUSTER_CONF_SRC_CI", None)
alarmsClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/alarms/ciAlarmsCluster.c.ftl")
alarmsClusterConfSrc.setOutputName("ciAlarmsCluster.c")
alarmsClusterConfSrc.setDestPath("/zigbee/z3device/combinedInterface")
alarmsClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/combinedInterface/")
alarmsClusterConfSrc.setType("SOURCE")
alarmsClusterConfSrc.setOverwrite(True)
alarmsClusterConfSrc.setMarkup(True)
alarmsClusterConfSrc.setEnabled(checkDevTypeCombInterface and alarmsCluster.getValue())
alarmsClusterConfSrc.setDependencies(combinedInterfaceAlarmsClusterEnableCheck,["ALARMS_CLUSTER_ENABLE"])

alarmsClusterConfInc = drvZigbeeComponent.createFileSymbol("CIALARMSCLUSTER_H", None)
alarmsClusterConfInc.setSourcePath("/driver/zigbee" + suffix + "/application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciAlarmsCluster.h")
alarmsClusterConfInc.setOutputName("ciAlarmsCluster.h")
alarmsClusterConfInc.setDestPath("/zigbee/z3device/combinedInterface/include")
alarmsClusterConfInc.setProjectPath("config/" + configName + "/zigbee/z3device/combinedInterface/include/")
alarmsClusterConfInc.setType("HEADER")
alarmsClusterConfInc.setOverwrite(True)
alarmsClusterConfInc.setEnabled(checkDevTypeCombInterface and alarmsCluster.getValue())
alarmsClusterConfInc.setDependencies(combinedInterfaceAlarmsClusterEnableCheck,["ALARMS_CLUSTER_ENABLE"])

    
# ALARMS CLUSTER - Thermostat
alarmsClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_ALARMS_CLUSTER_CONF_SRC_TH", None)
alarmsClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/alarms/thAlarmsCluster.c.ftl")
alarmsClusterConfSrc.setOutputName("thAlarmsCluster.c")
alarmsClusterConfSrc.setDestPath("/zigbee/z3device/thermostat")
alarmsClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/thermostat/")
alarmsClusterConfSrc.setType("SOURCE")
alarmsClusterConfSrc.setOverwrite(True)
alarmsClusterConfSrc.setMarkup(True)
alarmsClusterConfSrc.setEnabled(checkDevTypeThermostat)

# ALARMS CLUSTER - Custom
alarmsClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_ALARMS_CLUSTER_CONF_SRC_CUSTOM", None)
alarmsClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/alarms/customAlarmsCluster.c.ftl")
alarmsClusterConfSrc.setOutputName("customAlarmsCluster.c")
alarmsClusterConfSrc.setDestPath("/zigbee/z3device/custom")
alarmsClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/custom/")
alarmsClusterConfSrc.setType("SOURCE")
alarmsClusterConfSrc.setOverwrite(True)
alarmsClusterConfSrc.setMarkup(True)
alarmsClusterConfSrc.setEnabled(checkDevTypeCustom and alarmsCluster.getValue())
alarmsClusterConfSrc.setDependencies(customAlarmsClusterEnableCheck,["ALARMS_CLUSTER_ENABLE"])
############################################################################################################
