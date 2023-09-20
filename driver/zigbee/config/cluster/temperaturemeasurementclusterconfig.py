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
###########################################  TEMPERATURE MEASUREMENT CLUSTER CONFIGURATION   ###############
############################################################################################################

############################################################################################################
############################################# Function Definitions #########################################
############################################################################################################
def temperatureMeasurementClusterCsCheck(symbol, event):
    if (temperatureMeasurementCluster.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def temperatureMeasurementClusterEnableCheck(symbol, event):
    if (temperatureMeasurementCluster.getValue() == False):
        symbol.setEnabled(False)
    else:
        symbol.setEnabled(True)

def customTemperatureMeasurementClusterEnableCheck(symbol, event):
    if ((zigbeeDeviceType.getValue() == 'ZIGBEE_CUSTOM') and (temperatureMeasurementCluster.getValue() == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def temperatureMeasurementClusterClientCheck(symbol, event):
    if ((temperatureMeasurementCluster.getValue() == False) or temperatureMeasurementClusterCS.getValue() == "SERVER"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def temperatureMeasurementClusterServerCheck(symbol, event):
    if ((temperatureMeasurementCluster.getValue() == False) or temperatureMeasurementClusterCS.getValue() == "CLIENT"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def temperatureMeasurementClusterHandling():

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
        temperatureMeasurementCluster.setVisible(False)
        temperatureMeasurementCluster.setValue(False)
    elif ((getDevice == "ZIGBEE_COMBINED_INTERFACE")):
        temperatureMeasurementCluster.setVisible(True)
        temperatureMeasurementCluster.setValue(True)
        temperatureMeasurementCluster.setReadOnly(True)
        temperatureMeasurementClusterCS.setValue("CLIENT")
        temperatureMeasurementClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_MULTI_SENSOR")):
        temperatureMeasurementCluster.setVisible(True)
        temperatureMeasurementCluster.setValue(True)
        temperatureMeasurementCluster.setReadOnly(True)
        temperatureMeasurementClusterCS.setValue("SERVER")
        temperatureMeasurementClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_THERMOSTAT")):
        temperatureMeasurementCluster.setVisible(True)
        temperatureMeasurementCluster.setValue(True)
        temperatureMeasurementCluster.setReadOnly(True)
        temperatureMeasurementClusterCS.setValue("BOTH")
        temperatureMeasurementClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_CUSTOM")):
        temperatureMeasurementCluster.setVisible(True)
        temperatureMeasurementCluster.setValue(True)
        temperatureMeasurementClusterCS.setValue("BOTH")
    else:
        temperatureMeasurementCluster.setVisible(False)

def tempMeasClusterServerAttributeCountUpdate(symbol, event):
    count = 0
    if (tempMeasClusterServerAttributeMeasuredValue.getValue()):
        count += 1
    if (tempMeasClusterServerAttributeMinMeasuredValue.getValue()):
        count += 1
    if (tempMeasClusterServerAttributeMaxMeasuredValue.getValue()):
        count += 1
    if (tempMeasClusterServerAttributeTolerance.getValue()):
        count += 1
    if (tempMeasClusterServerAttributeClusterRevision.getValue()):
        count += 1
    tempMeasClusterServerAttributeCount.setValue(count) 
    return count

def tempMeasClusterClientAttributeCountUpdate(symbol, event):
    count = 0
    if (tempMeasClusterClientAttributeClusterRevision.getValue()):
        count += 1
    tempMeasClusterClientAttributeCount.setValue(count)
    return count
############################################################################################################
##################################### Configuration Item Definitions #######################################
############################################################################################################

global temperatureMeasurementCluster
temperatureMeasurementCluster = drvZigbeeComponent.createBooleanSymbol("TEMPERATUREMEASUREMENT_CLUSTER_ENABLE", clusterConfigMenu)
temperatureMeasurementCluster.setLabel("0x0402 Temperature Measurement Cluster")
temperatureMeasurementCluster.setDefaultValue(False)
temperatureMeasurementCluster.setVisible(False)
temperatureMeasurementCluster.setDescription("TEMPERATURE MEASUREMENT CLUSTER- check the box to enable")
temperatureMeasurementCluster.setReadOnly(False)

global temperatureMeasurementClusterCS
temperatureMeasurementClusterCS = drvZigbeeComponent.createComboSymbol("TEMPERATUREMEASUREMENT_CLUSTER_CS",  temperatureMeasurementCluster, ["CLIENT","SERVER", "BOTH"])
temperatureMeasurementClusterCS.setLabel("Supported Implementation")
temperatureMeasurementClusterCS.setDefaultValue("BOTH")
#temperatureMeasurementClusterCS.setVisible(False)
temperatureMeasurementClusterCS.setDescription("Temperature Measurement Cluster Supported Implementation- Select the option")
temperatureMeasurementClusterCS.setDependencies(temperatureMeasurementClusterCsCheck,["TEMPERATUREMEASUREMENT_CLUSTER_ENABLE"])

temperatureMeasurementClusterClientMenu = drvZigbeeComponent.createMenuSymbol("TEMPERATUREMEASUREMENT_CLUSTER_CLIENT_MENU", temperatureMeasurementCluster)
temperatureMeasurementClusterClientMenu.setLabel("Client")
#temperatureMeasurementClusterClientMenu.setVisible(False)
temperatureMeasurementClusterClientMenu.setDescription("TEMPERATURE MEASUREMENT CLUSTER CLIENT")
temperatureMeasurementClusterClientMenu.setDependencies(temperatureMeasurementClusterClientCheck,["TEMPERATUREMEASUREMENT_CLUSTER_CS","TEMPERATUREMEASUREMENT_CLUSTER_ENABLE"])

temperatureMeasurementClusterServerMenu = drvZigbeeComponent.createMenuSymbol("TEMPERATUREMEASUREMENT_CLUSTER_SERVER_MENU", temperatureMeasurementCluster)
temperatureMeasurementClusterServerMenu.setLabel("Server")
#temperatureMeasurementClusterServerMenu.setVisible(False)
temperatureMeasurementClusterServerMenu.setDescription("TEMPERATURE MEASUREMENT CLUSTER SERVER")
temperatureMeasurementClusterServerMenu.setDependencies(temperatureMeasurementClusterServerCheck,["TEMPERATUREMEASUREMENT_CLUSTER_CS","TEMPERATUREMEASUREMENT_CLUSTER_ENABLE"])

temperatureMeasurementClusterClientAttributes = drvZigbeeComponent.createMenuSymbol("TEMPERATUREMEASUREMENT_CLUSTER_CLIENT__ATTRIBUTES_MENU", temperatureMeasurementClusterClientMenu)
temperatureMeasurementClusterClientAttributes.setLabel("Attributes")
#temperatureMeasurementClusterClientAttributes.setVisible(False)
temperatureMeasurementClusterClientAttributes.setDescription("TEMPERATURE MEASUREMENT CLUSTER CLIENT ATTRIBUTES")
temperatureMeasurementClusterClientAttributes.setDependencies(temperatureMeasurementClusterClientCheck,["TEMPERATUREMEASUREMENT_CLUSTER_CS"])

# temperatureMeasurementClusterClientCommands = drvZigbeeComponent.createMenuSymbol("TEMPERATUREMEASUREMENT_CLUSTER_CLIENT__COMMANDS_MENU", temperatureMeasurementClusterClientMenu)
# temperatureMeasurementClusterClientCommands.setLabel("Commands")
# #temperatureMeasurementClusterClientCommands.setVisible(False)
# temperatureMeasurementClusterClientCommands.setDescription("TEMPERATURE MEASUREMENT CLUSTER CLIENT COMMANDS")
# temperatureMeasurementClusterClientCommands.setDependencies(temperatureMeasurementClusterClientCheck,["TEMPERATUREMEASUREMENT_CLUSTER_CS"])

temperatureMeasurementClusterServerAttributes = drvZigbeeComponent.createMenuSymbol("TEMPERATUREMEASUREMENT_CLUSTER_SERVER__ATTRIBUTES_MENU", temperatureMeasurementClusterServerMenu)
temperatureMeasurementClusterServerAttributes.setLabel("Attributes")
#temperatureMeasurementClusterServerAttributes.setVisible(False)
temperatureMeasurementClusterServerAttributes.setDescription("TEMPERATURE MEASUREMENT CLUSTER SERVER ATTRIBUTES")
temperatureMeasurementClusterServerAttributes.setDependencies(temperatureMeasurementClusterServerCheck,["TEMPERATUREMEASUREMENT_CLUSTER_CS"])

# temperatureMeasurementClusterServerCommands = drvZigbeeComponent.createMenuSymbol("TEMPERATUREMEASUREMENT_CLUSTER_SERVER__COMMANDS_MENU", temperatureMeasurementClusterServerMenu)
# temperatureMeasurementClusterServerCommands.setLabel("Commands")
# #temperatureMeasurementClusterServerCommands.setVisible(False)
# temperatureMeasurementClusterServerCommands.setDescription("TEMPERATURE MEASUREMENT CLUSTER SERVER COMMANDS")
# temperatureMeasurementClusterServerCommands.setDependencies(temperatureMeasurementClusterServerCheck,["TEMPERATUREMEASUREMENT_CLUSTER_CS"])

#################               Server Attributes                                 ###############

global tempMeasClusterServerAttributeMeasuredValue
tempMeasClusterServerAttributeMeasuredValue = drvZigbeeComponent.createBooleanSymbol("TMC_MEASUREDVALUE", temperatureMeasurementClusterServerAttributes)
tempMeasClusterServerAttributeMeasuredValue.setLabel("0x0000 MeasuredValue")
tempMeasClusterServerAttributeMeasuredValue.setDefaultValue(True)
tempMeasClusterServerAttributeMeasuredValue.setDescription("MeasuredValue - check the box to enable")
tempMeasClusterServerAttributeMeasuredValue.setReadOnly(True)

global tempMeasClusterServerAttributeMinMeasuredValue
tempMeasClusterServerAttributeMinMeasuredValue = drvZigbeeComponent.createBooleanSymbol("TMC_MINMEASUREDVALUE", temperatureMeasurementClusterServerAttributes)
tempMeasClusterServerAttributeMinMeasuredValue.setLabel("0x0001 MinMeasuredValue")
tempMeasClusterServerAttributeMinMeasuredValue.setDefaultValue(True)
tempMeasClusterServerAttributeMinMeasuredValue.setDescription("MinMeasuredValue - check the box to enable")
tempMeasClusterServerAttributeMinMeasuredValue.setReadOnly(True)

global tempMeasClusterServerAttributeMaxMeasuredValue
tempMeasClusterServerAttributeMaxMeasuredValue = drvZigbeeComponent.createBooleanSymbol("TMC_MAXMEASUREDVALUE", temperatureMeasurementClusterServerAttributes)
tempMeasClusterServerAttributeMaxMeasuredValue.setLabel("0x0002 MaxMeasuredValue")
tempMeasClusterServerAttributeMaxMeasuredValue.setDefaultValue(True)
tempMeasClusterServerAttributeMaxMeasuredValue.setDescription("MaxMeasuredValue - check the box to enable")
tempMeasClusterServerAttributeMaxMeasuredValue.setReadOnly(True)

global tempMeasClusterServerAttributeTolerance
tempMeasClusterServerAttributeTolerance = drvZigbeeComponent.createBooleanSymbol("TMC_TOLERANCE", temperatureMeasurementClusterServerAttributes)
tempMeasClusterServerAttributeTolerance.setLabel("0x0003 Tolerance")
tempMeasClusterServerAttributeTolerance.setDefaultValue(True)
tempMeasClusterServerAttributeTolerance.setDescription("Tolerance - check the box to enable")

global tempMeasClusterServerAttributeClusterRevision
tempMeasClusterServerAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("TMC_CLUSTERREVISION", temperatureMeasurementClusterServerAttributes)
tempMeasClusterServerAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
tempMeasClusterServerAttributeClusterRevision.setDefaultValue(True)
tempMeasClusterServerAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
tempMeasClusterServerAttributeClusterRevision.setReadOnly(True)

global tempMeasClusterServerAttributeCount
tempMeasClusterServerAttributeCount = drvZigbeeComponent.createIntegerSymbol("TMC_SERVERATTRIBUTECOUNT", temperatureMeasurementClusterServerAttributes)
tempMeasClusterServerAttributeCount.setLabel("Attributes Count")
tempMeasClusterServerAttributeCount.setDefaultValue(tempMeasClusterServerAttributeCountUpdate(0,0))
tempMeasClusterServerAttributeCount.setVisible(True)
tempMeasClusterServerAttributeCount.setDescription("Attributes Count")
tempMeasClusterServerAttributeCount.setReadOnly(True)
tempMeasClusterServerAttributeCount.setDependencies(tempMeasClusterServerAttributeCountUpdate,["TMC_MEASUREDVALUE","TMC_MINMEASUREDVALUE","TMC_MAXMEASUREDVALUE","TMC_TOLERANCE","TMC_CLUSTERREVISION"])
#################               Server Commands                                 ###############

# Commands received
# No cluster specific commands are received by the server.

# Commands generated
# No cluster specific commands are generated by the server.

#################               Client Attributes                                 ###############
global tempMeasClusterClientAttributeClusterRevision
tempMeasClusterClientAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("TMCC_CLUSTERREVISION", temperatureMeasurementClusterClientAttributes)
tempMeasClusterClientAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
tempMeasClusterClientAttributeClusterRevision.setDefaultValue(True)
tempMeasClusterClientAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
tempMeasClusterClientAttributeClusterRevision.setReadOnly(True)

global tempMeasClusterClientAttributeCount
tempMeasClusterClientAttributeCount = drvZigbeeComponent.createIntegerSymbol("TMCC_CLIENTATTRIBUTECOUNT", temperatureMeasurementClusterClientAttributes)
tempMeasClusterClientAttributeCount.setLabel("Attributes Count")
tempMeasClusterClientAttributeCount.setDefaultValue(tempMeasClusterClientAttributeCountUpdate(0,0))
tempMeasClusterClientAttributeCount.setVisible(True)
tempMeasClusterClientAttributeCount.setDescription("Attributes Count")
tempMeasClusterClientAttributeCount.setReadOnly(True)
tempMeasClusterClientAttributeCount.setDependencies(tempMeasClusterClientAttributeCountUpdate,["IMCC_CLUSTERREVISION"])
#################               Client Commands                                 ###############

# Commands generated
# No cluster specific commands are generated by the client.

# Commands received
# No cluster specific commands are received by the client.


############################################################################################################
# Default Values Settings based on device type
temperatureMeasurementClusterHandling()

############################################################################################################
##################################### FTL Files Definitions ################################################
############################################################################################################

# TEMPERATURE MEASUREMENT CLUSTER Common header
tempMeasClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_TEMPERATUREMEASUREMENT_CLUSTER_CONF", None)
tempMeasClusterConf.setSourcePath("/driver/zigbee/templates/cluster/temperaturemeasurement/zclTemperatureMeasurementCluster.h.ftl")
tempMeasClusterConf.setOutputName("zclTemperatureMeasurementCluster.h")
tempMeasClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
tempMeasClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
tempMeasClusterConf.setType("HEADER")
tempMeasClusterConf.setOverwrite(True)
tempMeasClusterConf.setMarkup(True)

# TEMPERATURE MEASUREMENT CLUSTER - Combined Interface
tempMeasClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_TEMPERATUREMEASUREMENT_CLUSTER_CONF_SRC_CI", None)
tempMeasClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/temperaturemeasurement/ciTemperatureMeasurementCluster.c.ftl")
tempMeasClusterConfSrc.setOutputName("ciTemperatureMeasurementCluster.c")
tempMeasClusterConfSrc.setDestPath("/zigbee/z3device/combinedInterface")
tempMeasClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/combinedInterface/")
tempMeasClusterConfSrc.setType("SOURCE")
tempMeasClusterConfSrc.setOverwrite(True)
tempMeasClusterConfSrc.setMarkup(True)
tempMeasClusterConfSrc.setEnabled(checkDevTypeCombInterface)

# TEMPERATURE MEASUREMENT CLUSTER - Multi Sensor
tempMeasClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_TEMPERATUREMEASUREMENT_CLUSTER_CONF_SRC_MS", None)
tempMeasClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/temperaturemeasurement/tsTemperatureMeasurementCluster.c.ftl")
tempMeasClusterConfSrc.setOutputName("tsTemperatureMeasurementCluster.c")
tempMeasClusterConfSrc.setDestPath("/zigbee/z3device/multiSensor")
tempMeasClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/multiSensor/")
tempMeasClusterConfSrc.setType("SOURCE")
tempMeasClusterConfSrc.setOverwrite(True)
tempMeasClusterConfSrc.setMarkup(True)
tempMeasClusterConfSrc.setEnabled(checkDevTypeMultiSensor)

# TEMPERATURE MEASUREMENT CLUSTER - Thermostat
tempMeasClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_TEMPERATUREMEASUREMENT_CLUSTER_CONF_SRC_TH", None)
tempMeasClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/temperaturemeasurement/thTemperatureMeasurementCluster.c.ftl")
tempMeasClusterConfSrc.setOutputName("thTemperatureMeasurementCluster.c")
tempMeasClusterConfSrc.setDestPath("/zigbee/z3device/thermostat")
tempMeasClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/thermostat/")
tempMeasClusterConfSrc.setType("SOURCE")
tempMeasClusterConfSrc.setOverwrite(True)
tempMeasClusterConfSrc.setMarkup(True)
tempMeasClusterConfSrc.setEnabled(checkDevTypeThermostat)

# TEMPERATURE MEASUREMENT CLUSTER - Custom
tempMeasClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_TEMPERATUREMEASUREMENT_CLUSTER_CONF_SRC_CUSTOM", None)
tempMeasClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/temperaturemeasurement/customTemperatureMeasurementCluster.c.ftl")
tempMeasClusterConfSrc.setOutputName("customTemperatureMeasurementCluster.c")
tempMeasClusterConfSrc.setDestPath("/zigbee/z3device/custom")
tempMeasClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/custom/")
tempMeasClusterConfSrc.setType("SOURCE")
tempMeasClusterConfSrc.setOverwrite(True)
tempMeasClusterConfSrc.setMarkup(True)
tempMeasClusterConfSrc.setEnabled(checkDevTypeCustom and temperatureMeasurementCluster.getValue())
tempMeasClusterConfSrc.setDependencies(customTemperatureMeasurementClusterEnableCheck,["TEMPERATUREMEASUREMENT_CLUSTER_ENABLE"])
############################################################################################################
