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
###########################################  BASIC CLUSTER CONFIGURATION   #################################
############################################################################################################

############################################################################################################
############################################# Function Definitions #########################################
############################################################################################################
def basiclusterCsCheck(symbol, event):
    if (basicCluster.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def basiclusterEnableCheck(symbol, event):
    if (basicCluster.getValue() == False):
        symbol.setEnabled(False)
    else:
        symbol.setEnabled(True)

def customBasiclusterEnableCheck(symbol, event):
    if ((zigbeeDeviceType.getValue() == 'ZIGBEE_CUSTOM') and (basicCluster.getValue() == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def basiclusterClientCheck(symbol, event):
    if ((basicCluster.getValue() == False) or basicClusterCS.getValue() == "SERVER"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def basiclusterServerCheck(symbol, event):
    if ((basicCluster.getValue() == False) or basicClusterCS.getValue() == "CLIENT"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def basicClusterHandling():

    getDevice = zigbeeDeviceType.getValue()

    if ((getDevice == "ZIGBEE_COLOR_SCENE_CONTROLLER")
        or (getDevice == "ZIGBEE_COMBINED_INTERFACE")
        or (getDevice == "ZIGBEE_CONTROL_BRIDGE")
        or (getDevice == "ZIGBEE_THERMOSTAT")
        or (getDevice == "ZIGBEE_IAS_ACE")
        or (getDevice == "ZIGBEE_ON_OFF_LIGHT")
        or (getDevice == "ZIGBEE_DIMMABLE_LIGHT")
        or (getDevice == "ZIGBEE_EXTENDED_COLOR_LIGHT")
        or (getDevice == "ZIGBEE_COLOR_LIGHT")
        or (getDevice == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")
        ):
        basicCluster.setVisible(True)
        basicCluster.setValue(True)
        basicCluster.setReadOnly(True)
        basicClusterCS.setValue("BOTH")
        basicClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_MULTI_SENSOR")):
        basicCluster.setVisible(True)
        basicCluster.setValue(True)
        basicCluster.setReadOnly(True)
        basicClusterCS.setValue("SERVER")
        basicClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_CUSTOM")):
        basicCluster.setVisible(True)
        basicCluster.setValue(True)
        basicClusterCS.setValue("BOTH")
    else:
        basicCluster.setVisible(False)


def basicClusterServerAttributeCountUpdate(symbol, event):
    count = 0
    if (basicClusterServerAttributeZCLVersion.getValue()):
        count += 1
    if (basicClusterServerAttributeAppVersion.getValue()):
        count += 1
    if (basicClusterServerAttributeStackVersion.getValue()):
        count += 1
    if (basicClusterServerAttributeHWVersion.getValue()):
        count += 1
    if (basicClusterServerAttributeManufacturerName.getValue()):
        count += 1
    if (basicClusterServerAttributeModelId.getValue()):
        count += 1
    if (basicClusterServerAttributeDateCode.getValue()):
        count += 1
    if (basicClusterServerAttributePowerSource.getValue()):
        count += 1
    if (basicClusterServerAttributeGenericDeviceClass.getValue()):
        count += 1
    if (basicClusterServerAttributeGenericDeviceType.getValue()):
        count += 1
    if (basicClusterServerAttributeProductCode.getValue()):
        count += 1
    if (basicClusterServerAttributeProductURL.getValue()):
        count += 1
    if (basicClusterServerAttributePhyEnv.getValue()):
        count += 1
    if (basicClusterServerAttributeSWBuildId.getValue()):
        count += 1
    if (basicClusterServerAttributeClusterRevision.getValue()):
        count += 1
    basicClusterServerAttributeCount.setValue(count) 
    return count

def basicClusterServerCommandCountUpdate(symbol, event):
    count = 0
    if (basicClusterServerCommandResetToFN.getValue()):
        count += 1
    basicClusterServerCommandCount.setValue(count)
    return count

def basicClusterClientAttributeCountUpdate(symbol, event):
    count = 0
    if (basicClusterClientAttributeClusterRevision.getValue()):
        count += 1
    basicClusterClientAttributeCount.setValue(count)
    return count

def basicClusterClientCommandCountUpdate(symbol, event):
    count = 0
    if (basicClusterClientCommandResetToFN.getValue()):
        count += 1
    basicClusterClientCommandCount.setValue(count)
    return count
############################################################################################################
##################################### Configuration Item Definitions #######################################
############################################################################################################

global basicCluster
basicCluster = drvZigbeeComponent.createBooleanSymbol("BASIC_CLUSTER_ENABLE", clusterConfigMenu)
basicCluster.setLabel("0x0000 Basic Cluster")
basicCluster.setDefaultValue(False)
basicCluster.setVisible(False)
basicCluster.setDescription("BASIC CLUSTER- check the box to enable")
basicCluster.setReadOnly(False)

global basicClusterCS
basicClusterCS = drvZigbeeComponent.createComboSymbol("BASIC_CLUSTER_CS",  basicCluster, ["CLIENT","SERVER", "BOTH"])
basicClusterCS.setLabel("Supported Implementation")
basicClusterCS.setDefaultValue("BOTH")
#basicClusterCS.setVisible(False)
basicClusterCS.setDescription("Basic Cluster Supported Implementation- Select the option")
basicClusterCS.setDependencies(basiclusterCsCheck,["BASIC_CLUSTER_ENABLE"])

basicClusterClientMenu = drvZigbeeComponent.createMenuSymbol("BASIC_CLUSTER_CLIENT_MENU", basicCluster)
basicClusterClientMenu.setLabel("Client")
#basicClusterClientMenu.setVisible(False)
basicClusterClientMenu.setDescription("BASIC CLUSTER CLIENT")
basicClusterClientMenu.setDependencies(basiclusterClientCheck,["BASIC_CLUSTER_CS","BASIC_CLUSTER_ENABLE"])

basicClusterServerMenu = drvZigbeeComponent.createMenuSymbol("BASIC_CLUSTER_SERVER_MENU", basicCluster)
basicClusterServerMenu.setLabel("Server")
#basicClusterServerMenu.setVisible(False)
basicClusterServerMenu.setDescription("BASIC CLUSTER SERVER")
basicClusterServerMenu.setDependencies(basiclusterServerCheck,["BASIC_CLUSTER_CS","BASIC_CLUSTER_ENABLE"])

basicClusterClientAttributes = drvZigbeeComponent.createMenuSymbol("BASIC_CLUSTER_CLIENT__ATTRIBUTES_MENU", basicClusterClientMenu)
basicClusterClientAttributes.setLabel("Attributes")
#basicClusterClientAttributes.setVisible(False)
basicClusterClientAttributes.setDescription("BASIC CLUSTER CLIENT ATTRIBUTES")
basicClusterClientAttributes.setDependencies(basiclusterClientCheck,["BASIC_CLUSTER_CS"])

basicClusterClientCommands = drvZigbeeComponent.createMenuSymbol("BASIC_CLUSTER_CLIENT__COMMANDS_MENU", basicClusterClientMenu)
basicClusterClientCommands.setLabel("Commands")
#basicClusterClientCommands.setVisible(False)
basicClusterClientCommands.setDescription("BASIC CLUSTER CLIENT COMMANDS")
basicClusterClientCommands.setDependencies(basiclusterClientCheck,["BASIC_CLUSTER_CS"])

basicClusterServerAttributes = drvZigbeeComponent.createMenuSymbol("BASIC_CLUSTER_SERVER__ATTRIBUTES_MENU", basicClusterServerMenu)
basicClusterServerAttributes.setLabel("Attributes")
#basicClusterServerAttributes.setVisible(False)
basicClusterServerAttributes.setDescription("BASIC CLUSTER SERVER ATTRIBUTES")
basicClusterServerAttributes.setDependencies(basiclusterServerCheck,["BASIC_CLUSTER_CS"])

basicClusterServerCommands = drvZigbeeComponent.createMenuSymbol("BASIC_CLUSTER_SERVER__COMMANDS_MENU", basicClusterServerMenu)
basicClusterServerCommands.setLabel("Commands")
#basicClusterServerCommands.setVisible(False)
basicClusterServerCommands.setDescription("BASIC CLUSTER SERVER COMMANDS")
basicClusterServerCommands.setDependencies(basiclusterServerCheck,["BASIC_CLUSTER_CS"])

#################               Server Attributes                                 ###############

global basicClusterServerAttributeZCLVersion
basicClusterServerAttributeZCLVersion = drvZigbeeComponent.createBooleanSymbol("BC_ZCLVERSION", basicClusterServerAttributes)
basicClusterServerAttributeZCLVersion.setLabel("0x0000 ZCLVersion")
basicClusterServerAttributeZCLVersion.setDefaultValue(True)
basicClusterServerAttributeZCLVersion.setDescription("ZCL Version - check the box to enable")
basicClusterServerAttributeZCLVersion.setReadOnly(True)

global basicClusterServerAttributeAppVersion
basicClusterServerAttributeAppVersion = drvZigbeeComponent.createBooleanSymbol("BC_APPLCIATIONVERSION", basicClusterServerAttributes)
basicClusterServerAttributeAppVersion.setLabel("0x0001 ApplicationVersion")
basicClusterServerAttributeAppVersion.setDefaultValue(True)
basicClusterServerAttributeAppVersion.setDescription("Application version - check the box to enable")

global basicClusterServerAttributeStackVersion
basicClusterServerAttributeStackVersion = drvZigbeeComponent.createBooleanSymbol("BC_STACKVERSION", basicClusterServerAttributes)
basicClusterServerAttributeStackVersion.setLabel("0x0002 StackVersion")
basicClusterServerAttributeStackVersion.setDefaultValue(True)
basicClusterServerAttributeStackVersion.setDescription("stack version - check the box to enable")

global basicClusterServerAttributeHWVersion
basicClusterServerAttributeHWVersion= drvZigbeeComponent.createBooleanSymbol("BC_HWVERSION", basicClusterServerAttributes)
basicClusterServerAttributeHWVersion.setLabel("0x0003 HWVersion")
basicClusterServerAttributeHWVersion.setDefaultValue(True)
basicClusterServerAttributeHWVersion.setDescription("Hardware version - check the box to enable")

global basicClusterServerAttributeManufacturerName
basicClusterServerAttributeManufacturerName = drvZigbeeComponent.createBooleanSymbol("BC_MANUNAME", basicClusterServerAttributes)
basicClusterServerAttributeManufacturerName.setLabel("0x0004 ManufacturerName")
basicClusterServerAttributeManufacturerName.setDefaultValue(True)
basicClusterServerAttributeManufacturerName.setDescription("Manufacturer Name - check the box to enable")

global basicClusterServerAttributeModelId
basicClusterServerAttributeModelId = drvZigbeeComponent.createBooleanSymbol("BC_MODELID", basicClusterServerAttributes)
basicClusterServerAttributeModelId.setLabel("0x0005 ModelIdentifier")
basicClusterServerAttributeModelId.setDefaultValue(True)
basicClusterServerAttributeModelId.setDescription("Model Identifier - check the box to enable")

global basicClusterServerAttributeDateCode
basicClusterServerAttributeDateCode = drvZigbeeComponent.createBooleanSymbol("BC_DATECODE", basicClusterServerAttributes)
basicClusterServerAttributeDateCode.setLabel("0x0006 DateCode")
basicClusterServerAttributeDateCode.setDefaultValue(True)
basicClusterServerAttributeDateCode.setDescription("Date Code - check the box to enable")

global basicClusterServerAttributePowerSource
basicClusterServerAttributePowerSource = drvZigbeeComponent.createBooleanSymbol("BC_POWERSOURCE", basicClusterServerAttributes)
basicClusterServerAttributePowerSource.setLabel("0x0007 PowerSource")
basicClusterServerAttributePowerSource.setDefaultValue(True)
basicClusterServerAttributePowerSource.setReadOnly(True)

global basicClusterServerAttributeGenericDeviceClass
basicClusterServerAttributeGenericDeviceClass = drvZigbeeComponent.createBooleanSymbol("BC_GENDEVCLASS", basicClusterServerAttributes)
basicClusterServerAttributeGenericDeviceClass.setLabel("0x0008 GenericDeviceClass")
basicClusterServerAttributeGenericDeviceClass.setDefaultValue(True)

global basicClusterServerAttributeGenericDeviceType
basicClusterServerAttributeGenericDeviceType = drvZigbeeComponent.createBooleanSymbol("BC_GENDEVCTYPE", basicClusterServerAttributes)
basicClusterServerAttributeGenericDeviceType.setLabel("0x0009 GenericDeviceType")
basicClusterServerAttributeGenericDeviceType.setDefaultValue(True)

global basicClusterServerAttributeProductCode
basicClusterServerAttributeProductCode = drvZigbeeComponent.createBooleanSymbol("BC_PRODUCTCODE", basicClusterServerAttributes)
basicClusterServerAttributeProductCode.setLabel("0x000A ProductCode")
basicClusterServerAttributeProductCode.setDefaultValue(True)

global basicClusterServerAttributeProductURL
basicClusterServerAttributeProductURL = drvZigbeeComponent.createBooleanSymbol("BC_PRODUCTURL", basicClusterServerAttributes)
basicClusterServerAttributeProductURL.setLabel("0x000B ProductURL")
basicClusterServerAttributeProductURL.setDefaultValue(True)

# global basicClusterServerAttributeLocalDesc
# basicClusterServerAttributeLocalDesc = drvZigbeeComponent.createBooleanSymbol("BC_LOCALDEC", basicClusterServerAttributes)
# basicClusterServerAttributeLocalDesc.setLabel("0x0010 LocationDescription")
# basicClusterServerAttributeLocalDesc.setDefaultValue(True)

global basicClusterServerAttributePhyEnv
basicClusterServerAttributePhyEnv = drvZigbeeComponent.createBooleanSymbol("BC_PHYENV", basicClusterServerAttributes)
basicClusterServerAttributePhyEnv.setLabel("0x0011 PhysicalEnvironment")
basicClusterServerAttributePhyEnv.setDefaultValue(True)

# global basicClusterServerAttributeDeviceEnabled
# basicClusterServerAttributeDeviceEnabled = drvZigbeeComponent.createBooleanSymbol("BC_DEVICEENABLED", basicClusterServerAttributes)
# basicClusterServerAttributeDeviceEnabled.setLabel("0x0012 DeviceEnabled")
# basicClusterServerAttributeDeviceEnabled.setDefaultValue(True)

# global basicClusterServerAttributeAlarmMask
# basicClusterServerAttributeAlarmMask = drvZigbeeComponent.createBooleanSymbol("BC_ALARMMASK", basicClusterServerAttributes)
# basicClusterServerAttributeAlarmMask.setLabel("0x0013 AlarmMask")
# basicClusterServerAttributeAlarmMask.setDefaultValue(True)

# global basicClusterServerAttributeDisableLocalCOnfig
# basicClusterServerAttributeDisableLocalCOnfig = drvZigbeeComponent.createBooleanSymbol("BC_DISLOCCFG", basicClusterServerAttributes)
# basicClusterServerAttributeDisableLocalCOnfig.setLabel("0x0014 DisableLocalConfig")
# basicClusterServerAttributeDisableLocalCOnfig.setDefaultValue(True)

global basicClusterServerAttributeSWBuildId
basicClusterServerAttributeSWBuildId = drvZigbeeComponent.createBooleanSymbol("BC_SWBUILDID", basicClusterServerAttributes)
basicClusterServerAttributeSWBuildId.setLabel("0x4000 SWBuildID")
basicClusterServerAttributeSWBuildId.setDefaultValue(True)

global basicClusterServerAttributeClusterRevision
basicClusterServerAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("BC_CLUSTERREVISION", basicClusterServerAttributes)
basicClusterServerAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
basicClusterServerAttributeClusterRevision.setDefaultValue(True)
basicClusterServerAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
basicClusterServerAttributeClusterRevision.setReadOnly(True)

global basicClusterServerAttributeCount
basicClusterServerAttributeCount = drvZigbeeComponent.createIntegerSymbol("BC_SERVERATTRIBUTECOUNT", basicClusterServerAttributes)
basicClusterServerAttributeCount.setLabel("Attributes Count")
basicClusterServerAttributeCount.setDefaultValue(basicClusterServerAttributeCountUpdate(0,0))
basicClusterServerAttributeCount.setVisible(True)
basicClusterServerAttributeCount.setDescription("Attributes Count")
basicClusterServerAttributeCount.setReadOnly(True)
basicClusterServerAttributeCount.setDependencies(basicClusterServerAttributeCountUpdate,["BC_ZCLVERSION","BC_APPLCIATIONVERSION","BC_STACKVERSION","BC_HWVERSION",
                                                                                         "BC_MANUNAME","BC_MODELID","BC_DATECODE","BC_POWERSOURCE",
                                                                                         "BC_GENDEVCLASS","BC_GENDEVCTYPE","BC_PRODUCTCODE","BC_PRODUCTURL",
                                                                                         "BC_PHYENV","BC_SWBUILDID","BC_CLUSTERREVISION",
                                                                                        ])

#################               Server Commands                                 ###############
global basicClusterServerCommandResetToFN
basicClusterServerCommandResetToFN= drvZigbeeComponent.createBooleanSymbol("BS_RESETTOFNCMD", basicClusterServerCommands)
basicClusterServerCommandResetToFN.setLabel("0x00.Rx Reset to factory defaults")
basicClusterServerCommandResetToFN.setDefaultValue(True)
basicClusterServerCommandResetToFN.setDescription("Receive Reset to factory defaults - check the box to enable")

global basicClusterServerCommandCount
basicClusterServerCommandCount = drvZigbeeComponent.createIntegerSymbol("BC_SERVERCOMMANDCOUNT", basicClusterServerCommands)
basicClusterServerCommandCount.setLabel("Commands Count")
basicClusterServerCommandCount.setDefaultValue(basicClusterServerCommandCountUpdate(0,0))
basicClusterServerCommandCount.setVisible(True)
basicClusterServerCommandCount.setDescription("Commands Count")
basicClusterServerCommandCount.setReadOnly(True)
basicClusterServerCommandCount.setDependencies(basicClusterServerCommandCountUpdate,["BS_RESETTOFNCMD"])

#################               Client Attributes                                 ###############
global basicClusterClientAttributeClusterRevision
basicClusterClientAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("BS_CLUSTERREVISION", basicClusterClientAttributes)
basicClusterClientAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
basicClusterClientAttributeClusterRevision.setDefaultValue(True)
basicClusterClientAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
basicClusterClientAttributeClusterRevision.setReadOnly(True)

global basicClusterClientAttributeCount
basicClusterClientAttributeCount = drvZigbeeComponent.createIntegerSymbol("BC_CLIENTATTRIBUTECOUNT", basicClusterClientAttributes)
basicClusterClientAttributeCount.setLabel("Attributes Count")
basicClusterClientAttributeCount.setDefaultValue(basicClusterClientAttributeCountUpdate(0,0))
basicClusterClientAttributeCount.setVisible(True)
basicClusterClientAttributeCount.setDescription("Attributes Count")
basicClusterClientAttributeCount.setReadOnly(True)
basicClusterClientAttributeCount.setDependencies(basicClusterClientAttributeCountUpdate,["BS_CLUSTERREVISION"])

#################               Client Commands                                 ###############

global basicClusterClientCommandResetToFN
basicClusterClientCommandResetToFN = drvZigbeeComponent.createBooleanSymbol("BC_RESETTOFNCMD", basicClusterClientCommands)
basicClusterClientCommandResetToFN.setLabel("0x00.Tx Reset to factory defaults")
basicClusterClientCommandResetToFN.setDefaultValue(True)
basicClusterClientCommandResetToFN.setDescription("Sends Reset to factory defaults - check the box to enable")

global basicClusterClientCommandCount
basicClusterClientCommandCount = drvZigbeeComponent.createIntegerSymbol("BC_CLIENTCOMMANDCOUNT", basicClusterClientCommands)
basicClusterClientCommandCount.setLabel("Commands Count")
basicClusterClientCommandCount.setDefaultValue(basicClusterClientCommandCountUpdate(0,0))
basicClusterClientCommandCount.setVisible(True)
basicClusterClientCommandCount.setDescription("Commands Count")
basicClusterClientCommandCount.setReadOnly(True)
basicClusterClientCommandCount.setDependencies(basicClusterClientCommandCountUpdate,["BC_RESETTOFNCMD"])

############################################################################################################
# Default Settings handling based on device type
basicClusterHandling()

############################################################################################################
##################################### FTL Files Definitions ################################################
############################################################################################################

# BASIC CLUSTER Common header
basicClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_BASIC_CLUSTER_CONF", None)
basicClusterConf.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/basic/zclBasicCluster.h.ftl")
basicClusterConf.setOutputName("zclBasicCluster.h")
basicClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
basicClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
basicClusterConf.setType("HEADER")
basicClusterConf.setOverwrite(True)
basicClusterConf.setMarkup(True)

basicClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_BASIC_CLUSTER_CONF2", None)
basicClusterConf.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/basic/zclZllBasicCluster.h.ftl")
basicClusterConf.setOutputName("zclZllBasicCluster.h")
basicClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
basicClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
basicClusterConf.setType("HEADER")
basicClusterConf.setOverwrite(True)
basicClusterConf.setMarkup(True)

# BASIC CLUSTER - Light
basicClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_BASIC_CLUSTER_CONF_SRC_LIGHT", None)
basicClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/basic/lightBasicCluster.c.ftl")
basicClusterConfSrc.setOutputName("lightBasicCluster.c")
basicClusterConfSrc.setDestPath("/zigbee/z3device/light")
basicClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/light/")
basicClusterConfSrc.setType("SOURCE")
basicClusterConfSrc.setOverwrite(True)
basicClusterConfSrc.setMarkup(True)
basicClusterConfSrc.setEnabled(checkDevTypeLight)

# BASIC CLUSTER - Custom
basicClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_BASIC_CLUSTER_CONF_SRC_CUSTOM", None)
basicClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/basic/customBasicCluster.c.ftl")
basicClusterConfSrc.setOutputName("customBasicCluster.c")
basicClusterConfSrc.setDestPath("/zigbee/z3device/custom")
basicClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/custom/")
basicClusterConfSrc.setType("SOURCE")
basicClusterConfSrc.setOverwrite(True)
basicClusterConfSrc.setMarkup(True)
basicClusterConfSrc.setEnabled(checkDevTypeCustom and basicCluster.getValue())
basicClusterConfSrc.setDependencies(customBasiclusterEnableCheck,["BASIC_CLUSTER_ENABLE"])

# BASIC CLUSTER - Color Scene Controller
basicClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_BASIC_CLUSTER_CONF_SRC_CSC", None)
basicClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/basic/cscBasicCluster.c.ftl")
basicClusterConfSrc.setOutputName("cscBasicCluster.c")
basicClusterConfSrc.setDestPath("/zigbee/z3device/colorSceneController")
basicClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/colorSceneController/")
basicClusterConfSrc.setType("SOURCE")
basicClusterConfSrc.setOverwrite(True)
basicClusterConfSrc.setMarkup(True)
basicClusterConfSrc.setEnabled(checkDevTypeRemote)

# BASIC CLUSTER - Combined Interface
basicClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_BASIC_CLUSTER_CONF_SRC_CI", None)
basicClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/basic/ciBasicCluster.c.ftl")
basicClusterConfSrc.setOutputName("ciBasicCluster.c")
basicClusterConfSrc.setDestPath("/zigbee/z3device/combinedInterface")
basicClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/combinedInterface/")
basicClusterConfSrc.setType("SOURCE")
basicClusterConfSrc.setOverwrite(True)
basicClusterConfSrc.setMarkup(True)
basicClusterConfSrc.setEnabled(checkDevTypeCombInterface)

# BASIC CLUSTER - IAS ACE
basicClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_BASIC_CLUSTER_CONF_SRC_IAS", None)
basicClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/basic/iasACEBasicCluster.c.ftl")
basicClusterConfSrc.setOutputName("iasACEBasicCluster.c")
basicClusterConfSrc.setDestPath("/zigbee/z3device/ias_ace")
basicClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/ias_ace/")
basicClusterConfSrc.setType("SOURCE")
basicClusterConfSrc.setOverwrite(True)
basicClusterConfSrc.setMarkup(True)
basicClusterConfSrc.setEnabled(checkDevTypeIasAce)

# BASIC CLUSTER - Multi Sensor
# BASIC CLUSTER - Humidity Sensor
basicClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_BASIC_CLUSTER_CONF_SRC_HS", None)
basicClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/basic/hsBasicCluster.c.ftl")
basicClusterConfSrc.setOutputName("hsBasicCluster.c")
basicClusterConfSrc.setDestPath("/zigbee/z3device/multiSensor")
basicClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/multiSensor/")
basicClusterConfSrc.setType("SOURCE")
basicClusterConfSrc.setOverwrite(True)
basicClusterConfSrc.setMarkup(True)
basicClusterConfSrc.setEnabled(checkDevTypeMultiSensor)

# BASIC CLUSTER - Occupancy Sensor
basicClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_BASIC_CLUSTER_CONF_SRC_OS", None)
basicClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/basic/osBasicCluster.c.ftl")
basicClusterConfSrc.setOutputName("osBasicCluster.c")
basicClusterConfSrc.setDestPath("/zigbee/z3device/multiSensor")
basicClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/multiSensor/")
basicClusterConfSrc.setType("SOURCE")
basicClusterConfSrc.setOverwrite(True)
basicClusterConfSrc.setMarkup(True)
basicClusterConfSrc.setEnabled(checkDevTypeMultiSensor)

# BASIC CLUSTER - Temperature Sensor
basicClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_BASIC_CLUSTER_CONF_SRC_TS", None)
basicClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/basic/tsBasicCluster.c.ftl")
basicClusterConfSrc.setOutputName("tsBasicCluster.c")
basicClusterConfSrc.setDestPath("/zigbee/z3device/multiSensor")
basicClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/multiSensor/")
basicClusterConfSrc.setType("SOURCE")
basicClusterConfSrc.setOverwrite(True)
basicClusterConfSrc.setMarkup(True)
basicClusterConfSrc.setEnabled(checkDevTypeMultiSensor)

# BASIC CLUSTER - Thermostat
basicClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_BASIC_CLUSTER_CONF_SRC_TH", None)
basicClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/basic/thBasicCluster.c.ftl")
basicClusterConfSrc.setOutputName("thBasicCluster.c")
basicClusterConfSrc.setDestPath("/zigbee/z3device/thermostat")
basicClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/thermostat/")
basicClusterConfSrc.setType("SOURCE")
basicClusterConfSrc.setOverwrite(True)
basicClusterConfSrc.setMarkup(True)
basicClusterConfSrc.setEnabled(checkDevTypeThermostat)
############################################################################################################
