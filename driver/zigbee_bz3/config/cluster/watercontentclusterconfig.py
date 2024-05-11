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
###########################################  WATER CONTENT MEASUREMENT CLUSTER CONFIGURATION   #############
############################################################################################################

############################################################################################################
############################################# Function Definitions #########################################
############################################################################################################
def waterContentMeasurementClusterCsCheck(symbol, event):
    if (waterContentMeasurementCluster.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def waterContentMeasurementClusterEnableCheck(symbol, event):
    if (waterContentMeasurementCluster.getValue() == False):
        symbol.setEnabled(False)
    else:
        symbol.setEnabled(True)

def customWaterContentMeasurementClusterEnableCheck(symbol, event):
    if ((zigbeeDeviceType.getValue() == 'ZIGBEE_CUSTOM') and (waterContentMeasurementCluster.getValue() == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def waterContentMeasurementClusterClientCheck(symbol, event):
    if ((waterContentMeasurementCluster.getValue() == False) or waterContentMeasurementClusterCS.getValue() == "SERVER"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def waterContentMeasurementClusterServerCheck(symbol, event):
    if ((waterContentMeasurementCluster.getValue() == False) or waterContentMeasurementClusterCS.getValue() == "CLIENT"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def waterContentMeasurementClusterHandling():

    getDevice = zigbeeDeviceType.getValue()

    if ((getDevice == "ZIGBEE_COLOR_SCENE_CONTROLLER")
        or (getDevice == "ZIGBEE_CONTROL_BRIDGE")
        or (getDevice == "ZIGBEE_IAS_ACE")
        or (getDevice == "ZIGBEE_ON_OFF_LIGHT")
        or (getDevice == "ZIGBEE_DIMMABLE_LIGHT")
        or (getDevice == "ZIGBEE_COLOR_LIGHT")
        or (getDevice == "ZIGBEE_EXTENDED_COLOR_LIGHT")
        or (getDevice == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")
        ):
        waterContentMeasurementCluster.setVisible(False)
        waterContentMeasurementCluster.setValue(False)
    elif ((getDevice == "ZIGBEE_COMBINED_INTERFACE")):
        waterContentMeasurementCluster.setVisible(True)
        waterContentMeasurementCluster.setValue(True)
        waterContentMeasurementCluster.setReadOnly(True)
        waterContentMeasurementClusterCS.setValue("CLIENT")
        waterContentMeasurementClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_MULTI_SENSOR")):
        waterContentMeasurementCluster.setVisible(True)
        waterContentMeasurementCluster.setValue(True)
        waterContentMeasurementCluster.setReadOnly(True)
        waterContentMeasurementClusterCS.setValue("SERVER")
        waterContentMeasurementClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_THERMOSTAT")):
        waterContentMeasurementCluster.setVisible(True)
        waterContentMeasurementCluster.setValue(True)
        waterContentMeasurementCluster.setReadOnly(True)
        waterContentMeasurementClusterCS.setValue("BOTH")
        waterContentMeasurementClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_CUSTOM")):
        waterContentMeasurementCluster.setVisible(True)
        waterContentMeasurementCluster.setValue(True)
        waterContentMeasurementClusterCS.setValue("BOTH")
    else:
        waterContentMeasurementCluster.setVisible(False)

def waterContentMeasClusterServerAttributeCountUpdate(symbol, event):
    count = 0
    if (waterContentMeasClusterServerAttributeMeasuredValue.getValue()):
        count += 1
    if (waterContentMeasClusterServerAttributeMinMeasuredValue.getValue()):
        count += 1
    if (waterContentMeasClusterServerAttributeMaxMeasuredValue.getValue()):
        count += 1
    if (waterContentMeasClusterServerAttributeTolerance.getValue()):
        count += 1
    if (waterContentMeasClusterServerAttributeClusterRevision.getValue()):
        count += 1
    waterContentMeasClusterServerAttributeCount.setValue(count) 
    return count

def waterContentMeasClusterClientAttributeCountUpdate(symbol, event):
    count = 0
    if (waterContentMeasClusterClientAttributeClusterRevision.getValue()):
        count += 1
    waterContentMeasClusterClientAttributeCount.setValue(count)
    return count
############################################################################################################
##################################### Configuration Item Definitions #######################################
############################################################################################################

global waterContentMeasurementCluster
waterContentMeasurementCluster = drvZigbeeComponent.createBooleanSymbol("WATERCONTENTMEASUREMENT_CLUSTER_ENABLE", clusterConfigMenu)
waterContentMeasurementCluster.setLabel("0x0405 Water Content Measurement Cluster")
waterContentMeasurementCluster.setDefaultValue(False)
waterContentMeasurementCluster.setVisible(False)
waterContentMeasurementCluster.setDescription("WATER CONTENT MEASUREMENT CLUSTER- check the box to enable")
waterContentMeasurementCluster.setReadOnly(False)

global waterContentMeasurementClusterCS
waterContentMeasurementClusterCS = drvZigbeeComponent.createComboSymbol("WATERCONTENTMEASUREMENT_CLUSTER_CS",  waterContentMeasurementCluster, ["CLIENT","SERVER", "BOTH"])
waterContentMeasurementClusterCS.setLabel("Supported Implementation")
waterContentMeasurementClusterCS.setDefaultValue("BOTH")
#waterContentMeasurementClusterCS.setVisible(False)
waterContentMeasurementClusterCS.setDescription("WaterContent Measurement Cluster Supported Implementation- Select the option")
waterContentMeasurementClusterCS.setDependencies(waterContentMeasurementClusterCsCheck,["WATERCONTENTMEASUREMENT_CLUSTER_ENABLE"])

waterContentMeasurementClusterClientMenu = drvZigbeeComponent.createMenuSymbol("WATERCONTENTMEASUREMENT_CLUSTER_CLIENT_MENU", waterContentMeasurementCluster)
waterContentMeasurementClusterClientMenu.setLabel("Client")
#waterContentMeasurementClusterClientMenu.setVisible(False)
waterContentMeasurementClusterClientMenu.setDescription("WATERCONTENT MEASUREMENT CLUSTER CLIENT")
waterContentMeasurementClusterClientMenu.setDependencies(waterContentMeasurementClusterClientCheck,["WATERCONTENTMEASUREMENT_CLUSTER_CS","WATERCONTENTMEASUREMENT_CLUSTER_ENABLE"])

waterContentMeasurementClusterServerMenu = drvZigbeeComponent.createMenuSymbol("WATERCONTENTMEASUREMENT_CLUSTER_SERVER_MENU", waterContentMeasurementCluster)
waterContentMeasurementClusterServerMenu.setLabel("Server")
#waterContentMeasurementClusterServerMenu.setVisible(False)
waterContentMeasurementClusterServerMenu.setDescription("WATERCONTENT MEASUREMENT CLUSTER SERVER")
waterContentMeasurementClusterServerMenu.setDependencies(waterContentMeasurementClusterServerCheck,["WATERCONTENTMEASUREMENT_CLUSTER_CS","WATERCONTENTMEASUREMENT_CLUSTER_ENABLE"])

waterContentMeasurementClusterClientAttributes = drvZigbeeComponent.createMenuSymbol("WATERCONTENTMEASUREMENT_CLUSTER_CLIENT__ATTRIBUTES_MENU", waterContentMeasurementClusterClientMenu)
waterContentMeasurementClusterClientAttributes.setLabel("Attributes")
#waterContentMeasurementClusterClientAttributes.setVisible(False)
waterContentMeasurementClusterClientAttributes.setDescription("WATER CONTENT MEASUREMENT CLUSTER CLIENT ATTRIBUTES")
waterContentMeasurementClusterClientAttributes.setDependencies(waterContentMeasurementClusterClientCheck,["WATERCONTENTMEASUREMENT_CLUSTER_CS"])

# waterContentMeasurementClusterClientCommands = drvZigbeeComponent.createMenuSymbol("WATERCONTENTMEASUREMENT_CLUSTER_CLIENT__COMMANDS_MENU", waterContentMeasurementClusterClientMenu)
# waterContentMeasurementClusterClientCommands.setLabel("Commands")
# #waterContentMeasurementClusterClientCommands.setVisible(False)
# waterContentMeasurementClusterClientCommands.setDescription("WATERCONTENT MEASUREMENT CLUSTER CLIENT COMMANDS")
# waterContentMeasurementClusterClientCommands.setDependencies(waterContentMeasurementClusterClientCheck,["WATERCONTENTMEASUREMENT_CLUSTER_CS"])

waterContentMeasurementClusterServerAttributes = drvZigbeeComponent.createMenuSymbol("WATERCONTENTMEASUREMENT_CLUSTER_SERVER__ATTRIBUTES_MENU", waterContentMeasurementClusterServerMenu)
waterContentMeasurementClusterServerAttributes.setLabel("Attributes")
#waterContentMeasurementClusterServerAttributes.setVisible(False)
waterContentMeasurementClusterServerAttributes.setDescription("WATER CONTENT MEASUREMENT CLUSTER SERVER ATTRIBUTES")
waterContentMeasurementClusterServerAttributes.setDependencies(waterContentMeasurementClusterServerCheck,["WATERCONTENTMEASUREMENT_CLUSTER_CS"])

# waterContentMeasurementClusterServerCommands = drvZigbeeComponent.createMenuSymbol("WATERCONTENTMEASUREMENT_CLUSTER_SERVER__COMMANDS_MENU", waterContentMeasurementClusterServerMenu)
# waterContentMeasurementClusterServerCommands.setLabel("Commands")
# #waterContentMeasurementClusterServerCommands.setVisible(False)
# waterContentMeasurementClusterServerCommands.setDescription("WATER CONTENT MEASUREMENT CLUSTER SERVER COMMANDS")
# waterContentMeasurementClusterServerCommands.setDependencies(waterContentMeasurementClusterServerCheck,["WATERCONTENTMEASUREMENT_CLUSTER_CS"])

#################               Server Attributes                                 ###############

global waterContentMeasClusterServerAttributeMeasuredValue
waterContentMeasClusterServerAttributeMeasuredValue = drvZigbeeComponent.createBooleanSymbol("WCMC_MEASUREDVALUE", waterContentMeasurementClusterServerAttributes)
waterContentMeasClusterServerAttributeMeasuredValue.setLabel("0x0000 MeasuredValue")
waterContentMeasClusterServerAttributeMeasuredValue.setDefaultValue(True)
waterContentMeasClusterServerAttributeMeasuredValue.setDescription("MeasuredValue - check the box to enable")
waterContentMeasClusterServerAttributeMeasuredValue.setReadOnly(True)

global waterContentMeasClusterServerAttributeMinMeasuredValue
waterContentMeasClusterServerAttributeMinMeasuredValue = drvZigbeeComponent.createBooleanSymbol("WCMC_MINMEASUREDVALUE", waterContentMeasurementClusterServerAttributes)
waterContentMeasClusterServerAttributeMinMeasuredValue.setLabel("0x0001 MinMeasuredValue")
waterContentMeasClusterServerAttributeMinMeasuredValue.setDefaultValue(True)
waterContentMeasClusterServerAttributeMinMeasuredValue.setDescription("MinMeasuredValue - check the box to enable")
waterContentMeasClusterServerAttributeMinMeasuredValue.setReadOnly(True)

global waterContentMeasClusterServerAttributeMaxMeasuredValue
waterContentMeasClusterServerAttributeMaxMeasuredValue = drvZigbeeComponent.createBooleanSymbol("WCMC_MAXMEASUREDVALUE", waterContentMeasurementClusterServerAttributes)
waterContentMeasClusterServerAttributeMaxMeasuredValue.setLabel("0x0002 MaxMeasuredValue")
waterContentMeasClusterServerAttributeMaxMeasuredValue.setDefaultValue(True)
waterContentMeasClusterServerAttributeMaxMeasuredValue.setDescription("MaxMeasuredValue - check the box to enable")
waterContentMeasClusterServerAttributeMaxMeasuredValue.setReadOnly(True)

global waterContentMeasClusterServerAttributeTolerance
waterContentMeasClusterServerAttributeTolerance = drvZigbeeComponent.createBooleanSymbol("WCMC_TOLERANCE", waterContentMeasurementClusterServerAttributes)
waterContentMeasClusterServerAttributeTolerance.setLabel("0x0003 Tolerance")
waterContentMeasClusterServerAttributeTolerance.setDefaultValue(True)
waterContentMeasClusterServerAttributeTolerance.setDescription("Tolerance - check the box to enable")

global waterContentMeasClusterServerAttributeClusterRevision
waterContentMeasClusterServerAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("WCMC_CLUSTERREVISION", waterContentMeasurementClusterServerAttributes)
waterContentMeasClusterServerAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
waterContentMeasClusterServerAttributeClusterRevision.setDefaultValue(True)
waterContentMeasClusterServerAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
waterContentMeasClusterServerAttributeClusterRevision.setReadOnly(True)

global waterContentMeasClusterServerAttributeCount
waterContentMeasClusterServerAttributeCount = drvZigbeeComponent.createIntegerSymbol("WCMC_SERVERATTRIBUTECOUNT", waterContentMeasurementClusterServerAttributes)
waterContentMeasClusterServerAttributeCount.setLabel("Attributes Count")
waterContentMeasClusterServerAttributeCount.setDefaultValue(waterContentMeasClusterServerAttributeCountUpdate(0,0))
waterContentMeasClusterServerAttributeCount.setVisible(True)
waterContentMeasClusterServerAttributeCount.setDescription("Attributes Count")
waterContentMeasClusterServerAttributeCount.setReadOnly(True)
waterContentMeasClusterServerAttributeCount.setDependencies(waterContentMeasClusterServerAttributeCountUpdate,["WCMC_MEASUREDVALUE","WCMC_MINMEASUREDVALUE","WCMC_MAXMEASUREDVALUE","WCMC_TOLERANCE","WCMC_CLUSTERREVISION"])
#################               Server Commands                                 ###############

# Commands received
# No cluster specific commands are received by the server.

# Commands generated
# No cluster specific commands are generated by the server.

#################               Client Attributes                                 ###############
global waterContentMeasClusterClientAttributeClusterRevision
waterContentMeasClusterClientAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("WCMCC_CLUSTERREVISION", waterContentMeasurementClusterClientAttributes)
waterContentMeasClusterClientAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
waterContentMeasClusterClientAttributeClusterRevision.setDefaultValue(True)
waterContentMeasClusterClientAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
waterContentMeasClusterClientAttributeClusterRevision.setReadOnly(True)

global waterContentMeasClusterClientAttributeCount
waterContentMeasClusterClientAttributeCount = drvZigbeeComponent.createIntegerSymbol("WMCC_CLIENTATTRIBUTECOUNT", waterContentMeasurementClusterClientAttributes)
waterContentMeasClusterClientAttributeCount.setLabel("Attributes Count")
waterContentMeasClusterClientAttributeCount.setDefaultValue(waterContentMeasClusterClientAttributeCountUpdate(0,0))
waterContentMeasClusterClientAttributeCount.setVisible(True)
waterContentMeasClusterClientAttributeCount.setDescription("Attributes Count")
waterContentMeasClusterClientAttributeCount.setReadOnly(True)
waterContentMeasClusterClientAttributeCount.setDependencies(waterContentMeasClusterClientAttributeCountUpdate,["WCMCC_CLUSTERREVISION"])

#################               Client Commands                                 ###############

# Commands generated
# No cluster specific commands are generated by the client.

# Commands received
# No cluster specific commands are received by the client.

############################################################################################################
# Default Values Settings based on device type
waterContentMeasurementClusterHandling()

############################################################################################################
##################################### FTL Files Definitions ################################################
############################################################################################################

# WATER CONTENT MEASUREMENT CLUSTER Common header
waterContentMeasClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_WATERCONTENTMEASUREMENT_CLUSTER_CONF", None)
waterContentMeasClusterConf.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/watercontent/zclHumidityMeasurementCluster.h.ftl")
waterContentMeasClusterConf.setOutputName("zclHumidityMeasurementCluster.h")
waterContentMeasClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
waterContentMeasClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
waterContentMeasClusterConf.setType("HEADER")
waterContentMeasClusterConf.setOverwrite(True)
waterContentMeasClusterConf.setMarkup(True)

# WATER CONTENT MEASUREMENT CLUSTER - Combined Interface
waterContentMeasClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_WATERCONTENTMEASUREMENT_CLUSTER_CONF_SRC_CI", None)
waterContentMeasClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/watercontent/ciHumidityMeasurementCluster.c.ftl")
waterContentMeasClusterConfSrc.setOutputName("ciHumidityMeasurementCluster.c")
waterContentMeasClusterConfSrc.setDestPath("/zigbee/z3device/combinedInterface")
waterContentMeasClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/combinedInterface/")
waterContentMeasClusterConfSrc.setType("SOURCE")
waterContentMeasClusterConfSrc.setOverwrite(True)
waterContentMeasClusterConfSrc.setMarkup(True)
waterContentMeasClusterConfSrc.setEnabled(checkDevTypeCombInterface)

# WATER CONTENT MEASUREMENT CLUSTER - Multi Sensor
waterContentMeasClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_WATERCONTENTMEASUREMENT_CLUSTER_CONF_SRC_MS", None)
waterContentMeasClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/watercontent/hsHumidityMeasurementCluster.c.ftl")
waterContentMeasClusterConfSrc.setOutputName("hsHumidityMeasurementCluster.c")
waterContentMeasClusterConfSrc.setDestPath("/zigbee/z3device/multiSensor")
waterContentMeasClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/multiSensor/")
waterContentMeasClusterConfSrc.setType("SOURCE")
waterContentMeasClusterConfSrc.setOverwrite(True)
waterContentMeasClusterConfSrc.setMarkup(True)
waterContentMeasClusterConfSrc.setEnabled(checkDevTypeMultiSensor)

# WATER CONTENT MEASUREMENT CLUSTER - Thermostat
waterContentMeasClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_WATERCONTENTMEASUREMENT_CLUSTER_CONF_SRC_TH", None)
waterContentMeasClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/watercontent/thHumidityMeasurementCluster.c.ftl")
waterContentMeasClusterConfSrc.setOutputName("thHumidityMeasurementCluster.c")
waterContentMeasClusterConfSrc.setDestPath("/zigbee/z3device/thermostat")
waterContentMeasClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/thermostat/")
waterContentMeasClusterConfSrc.setType("SOURCE")
waterContentMeasClusterConfSrc.setOverwrite(True)
waterContentMeasClusterConfSrc.setMarkup(True)
waterContentMeasClusterConfSrc.setEnabled(checkDevTypeThermostat)

# WATER CONTENT MEASUREMENT CLUSTER - Custom
waterContentMeasClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_WATERCONTENTMEASUREMENT_CLUSTER_CONF_SRC_CUSTOM", None)
waterContentMeasClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/watercontent/customHumidityMeasurementCluster.c.ftl")
waterContentMeasClusterConfSrc.setOutputName("customHumidityMeasurementCluster.c")
waterContentMeasClusterConfSrc.setDestPath("/zigbee/z3device/custom")
waterContentMeasClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/custom/")
waterContentMeasClusterConfSrc.setType("SOURCE")
waterContentMeasClusterConfSrc.setOverwrite(True)
waterContentMeasClusterConfSrc.setMarkup(True)
waterContentMeasClusterConfSrc.setEnabled(checkDevTypeCustom and waterContentMeasurementCluster.getValue())
waterContentMeasClusterConfSrc.setDependencies(customWaterContentMeasurementClusterEnableCheck,["WATERCONTENTMEASUREMENT_CLUSTER_ENABLE"])
############################################################################################################
