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
###########################################  ILLUMINANCE MEASUREMENT CLUSTER CONFIGURATION   ###############
############################################################################################################

############################################################################################################
############################################# Function Definitions #########################################
############################################################################################################
def illuminanceMeasurementClusterCsCheck(symbol, event):
    if (illuminanceMeasurementCluster.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def illuminanceMeasurementClusterEnableCheck(symbol, event):
    if (illuminanceMeasurementCluster.getValue() == False):
        symbol.setEnabled(False)
    else:
        symbol.setEnabled(True)

def customIlluminanceMeasurementClusterEnableCheck(symbol, event):
    if ((zigbeeDeviceType.getValue() == 'ZIGBEE_CUSTOM') and (illuminanceMeasurementCluster.getValue() == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def combinedInterfaceIlluminanceMeasurementClusterEnableCheck(symbol, event):
    if ((zigbeeDeviceType.getValue() == 'ZIGBEE_COMBINED_INTERFACE') and (illuminanceMeasurementCluster.getValue() == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def illuminanceMeasurementClusterClientCheck(symbol, event):
    if ((illuminanceMeasurementCluster.getValue() == False) or illuminanceMeasurementClusterCS.getValue() == "SERVER"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def illuminanceMeasurementClusterServerCheck(symbol, event):
    if ((illuminanceMeasurementCluster.getValue() == False) or illuminanceMeasurementClusterCS.getValue() == "CLIENT"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def illuminanceMeasurementClusterHandling():

    getDevice = zigbeeDeviceType.getValue()

    if ((getDevice == "ZIGBEE_COLOR_SCENE_CONTROLLER")
        or (getDevice == "ZIGBEE_CONTROL_BRIDGE")
        or (getDevice == "ZIGBEE_IAS_ACE")
        or (getDevice == "ZIGBEE_ON_OFF_LIGHT")
        or (getDevice == "ZIGBEE_DIMMABLE_LIGHT")
        or (getDevice == "ZIGBEE_COLOR_LIGHT")
        or (getDevice == "ZIGBEE_EXTENDED_COLOR_LIGHT")
        or (getDevice == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")
        or (getDevice == "ZIGBEE_THERMOSTAT")
        ):
        illuminanceMeasurementCluster.setVisible(False)
        illuminanceMeasurementCluster.setValue(False)
    elif ((getDevice == "ZIGBEE_COMBINED_INTERFACE")):
        illuminanceMeasurementCluster.setVisible(True)
        illuminanceMeasurementCluster.setValue(True)
        illuminanceMeasurementCluster.setReadOnly(False)
        illuminanceMeasurementClusterCS.setValue("CLIENT")
        illuminanceMeasurementClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_MULTI_SENSOR")):
        illuminanceMeasurementCluster.setVisible(True)
        illuminanceMeasurementCluster.setValue(True)
        illuminanceMeasurementCluster.setReadOnly(True)
        illuminanceMeasurementClusterCS.setValue("SERVER")
        illuminanceMeasurementClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_CUSTOM")):
        illuminanceMeasurementCluster.setVisible(True)
        illuminanceMeasurementCluster.setValue(True)
        illuminanceMeasurementClusterCS.setValue("SERVER")
        illuminanceMeasurementClusterCS.setVisible(True)
        illuminanceMeasurementClusterClientMenu.setVisible(False) 
        illuminanceMeasurementClusterServerMenu.setVisible(True)
    else:
        illuminanceMeasurementCluster.setVisible(False)

def illuMeasClusterServerAttributeCountUpdate(symbol, event):
    count = 0
    if (illuMeasClusterServerAttributeMeasuredValue.getValue()):
        count += 1
    if (illuMeasClusterServerAttributeMinMeasuredValue.getValue()):
        count += 1
    if (illuMeasClusterServerAttributeMaxMeasuredValue.getValue()):
        count += 1
    if (illuMeasClusterServerAttributeTolerance.getValue()):
        count += 1
    if (illuMeasClusterServerAttributeLightSensorType.getValue()):
        count += 1
    if (illuMeasClusterServerAttributeClusterRevision.getValue()):
        count += 1
    illuMeasClusterServerAttributeCount.setValue(count) 
    return count

def illuMeasClusterClientAttributeCountUpdate(symbol, event):
    count = 0
    if (illuMeasClusterClientAttributeClusterRevision.getValue()):
        count += 1
    illuMeasClusterClientAttributeCount.setValue(count)
    return count

############################################################################################################
##################################### Configuration Item Definitions #######################################
############################################################################################################

global illuminanceMeasurementCluster
illuminanceMeasurementCluster = drvZigbeeComponent.createBooleanSymbol("ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE", clusterConfigMenu)
illuminanceMeasurementCluster.setLabel("0x0400 Illuminance Measurement Cluster")
illuminanceMeasurementCluster.setDefaultValue(False)
illuminanceMeasurementCluster.setVisible(False)
illuminanceMeasurementCluster.setDescription("ILLUMINANCE MEASUREMENT CLUSTER- check the box to enable")
illuminanceMeasurementCluster.setReadOnly(False)

global illuminanceMeasurementClusterCS
illuminanceMeasurementClusterCS = drvZigbeeComponent.createComboSymbol("ILLUMINANCEMEASUREMENT_CLUSTER_CS",  illuminanceMeasurementCluster, ["CLIENT","SERVER", "BOTH"])
illuminanceMeasurementClusterCS.setLabel("Supported Implementation")
illuminanceMeasurementClusterCS.setDefaultValue("BOTH")
#illuminanceMeasurementClusterCS.setVisible(False)
illuminanceMeasurementClusterCS.setDescription("Illuminance Measurement Cluster Supported Implementation- Select the option")
illuminanceMeasurementClusterCS.setDependencies(illuminanceMeasurementClusterCsCheck,["ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE"])

global illuminanceMeasurementClusterClientMenu
illuminanceMeasurementClusterClientMenu = drvZigbeeComponent.createMenuSymbol("ILLUMINANCEMEASUREMENT_CLUSTER_CLIENT_MENU", illuminanceMeasurementCluster)
illuminanceMeasurementClusterClientMenu.setLabel("Client")
#illuminanceMeasurementClusterClientMenu.setVisible(False)
illuminanceMeasurementClusterClientMenu.setDescription("ILLUMINANCE MEASUREMENT CLUSTER CLIENT")
illuminanceMeasurementClusterClientMenu.setDependencies(illuminanceMeasurementClusterClientCheck,["ILLUMINANCEMEASUREMENT_CLUSTER_CS","ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE"])

global illuminanceMeasurementClusterServerMenu
illuminanceMeasurementClusterServerMenu = drvZigbeeComponent.createMenuSymbol("ILLUMINANCEMEASUREMENT_CLUSTER_SERVER_MENU", illuminanceMeasurementCluster)
illuminanceMeasurementClusterServerMenu.setLabel("Server")
#illuminanceMeasurementClusterServerMenu.setVisible(False)
illuminanceMeasurementClusterServerMenu.setDescription("ILLUMINANCE MEASUREMENT CLUSTER SERVER")
illuminanceMeasurementClusterServerMenu.setDependencies(illuminanceMeasurementClusterServerCheck,["ILLUMINANCEMEASUREMENT_CLUSTER_CS","ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE"])

illuminanceMeasurementClusterClientAttributes = drvZigbeeComponent.createMenuSymbol("ILLUMINANCEMEASUREMENT_CLUSTER_CLIENT__ATTRIBUTES_MENU", illuminanceMeasurementClusterClientMenu)
illuminanceMeasurementClusterClientAttributes.setLabel("Attributes")
#illuminanceMeasurementClusterClientAttributes.setVisible(False)
illuminanceMeasurementClusterClientAttributes.setDescription("ILLUMINANCE MEASUREMENT CLUSTER CLIENT ATTRIBUTES")
illuminanceMeasurementClusterClientAttributes.setDependencies(illuminanceMeasurementClusterClientCheck,["ILLUMINANCEMEASUREMENT_CLUSTER_CS"])

# illuminanceMeasurementClusterClientCommands = drvZigbeeComponent.createMenuSymbol("ILLUMINANCEMEASUREMENT_CLUSTER_CLIENT__COMMANDS_MENU", illuminanceMeasurementClusterClientMenu)
# illuminanceMeasurementClusterClientCommands.setLabel("Commands")
# #illuminanceMeasurementClusterClientCommands.setVisible(False)
# illuminanceMeasurementClusterClientCommands.setDescription("ILLUMINANCE MEASUREMENT CLUSTER CLIENT COMMANDS")
# illuminanceMeasurementClusterClientCommands.setDependencies(illuminanceMeasurementClusterClientCheck,["ILLUMINANCEMEASUREMENT_CLUSTER_CS"])

illuminanceMeasurementClusterServerAttributes = drvZigbeeComponent.createMenuSymbol("ILLUMINANCEMEASUREMENT_CLUSTER_SERVER__ATTRIBUTES_MENU", illuminanceMeasurementClusterServerMenu)
illuminanceMeasurementClusterServerAttributes.setLabel("Attributes")
#illuminanceMeasurementClusterServerAttributes.setVisible(False)
illuminanceMeasurementClusterServerAttributes.setDescription("ILLUMINANCE MEASUREMENT CLUSTER SERVER ATTRIBUTES")
illuminanceMeasurementClusterServerAttributes.setDependencies(illuminanceMeasurementClusterServerCheck,["ILLUMINANCEMEASUREMENT_CLUSTER_CS"])

# illuminanceMeasurementClusterServerCommands = drvZigbeeComponent.createMenuSymbol("ILLUMINANCEMEASUREMENT_CLUSTER_SERVER__COMMANDS_MENU", illuminanceMeasurementClusterServerMenu)
# illuminanceMeasurementClusterServerCommands.setLabel("Commands")
# #illuminanceMeasurementClusterServerCommands.setVisible(False)
# illuminanceMeasurementClusterServerCommands.setDescription("ILLUMINANCE MEASUREMENT CLUSTER SERVER COMMANDS")
# illuminanceMeasurementClusterServerCommands.setDependencies(illuminanceMeasurementClusterServerCheck,["ILLUMINANCEMEASUREMENT_CLUSTER_CS"])

#################               Server Attributes                                 ###############

global illuMeasClusterServerAttributeMeasuredValue
illuMeasClusterServerAttributeMeasuredValue = drvZigbeeComponent.createBooleanSymbol("IMC_MEASUREDVALUE", illuminanceMeasurementClusterServerAttributes)
illuMeasClusterServerAttributeMeasuredValue.setLabel("0x0000 MeasuredValue")
illuMeasClusterServerAttributeMeasuredValue.setDefaultValue(True)
illuMeasClusterServerAttributeMeasuredValue.setDescription("MeasuredValue - check the box to enable")
illuMeasClusterServerAttributeMeasuredValue.setReadOnly(True)

global illuMeasClusterServerAttributeMinMeasuredValue
illuMeasClusterServerAttributeMinMeasuredValue = drvZigbeeComponent.createBooleanSymbol("IMC_MINMEASUREDVALUE", illuminanceMeasurementClusterServerAttributes)
illuMeasClusterServerAttributeMinMeasuredValue.setLabel("0x0001 MinMeasuredValue")
illuMeasClusterServerAttributeMinMeasuredValue.setDefaultValue(True)
illuMeasClusterServerAttributeMinMeasuredValue.setDescription("MinMeasuredValue - check the box to enable")
illuMeasClusterServerAttributeMinMeasuredValue.setReadOnly(True)

global illuMeasClusterServerAttributeMaxMeasuredValue
illuMeasClusterServerAttributeMaxMeasuredValue = drvZigbeeComponent.createBooleanSymbol("IMC_MAXMEASUREDVALUE", illuminanceMeasurementClusterServerAttributes)
illuMeasClusterServerAttributeMaxMeasuredValue.setLabel("0x0002 MaxMeasuredValue")
illuMeasClusterServerAttributeMaxMeasuredValue.setDefaultValue(True)
illuMeasClusterServerAttributeMaxMeasuredValue.setDescription("MaxMeasuredValue - check the box to enable")
illuMeasClusterServerAttributeMaxMeasuredValue.setReadOnly(True)

global illuMeasClusterServerAttributeTolerance
illuMeasClusterServerAttributeTolerance = drvZigbeeComponent.createBooleanSymbol("IMC_TOLERANCE", illuminanceMeasurementClusterServerAttributes)
illuMeasClusterServerAttributeTolerance.setLabel("0x0003 Tolerance")
illuMeasClusterServerAttributeTolerance.setDefaultValue(True)
illuMeasClusterServerAttributeTolerance.setDescription("Tolerance - check the box to enable")

global illuMeasClusterServerAttributeLightSensorType
illuMeasClusterServerAttributeLightSensorType = drvZigbeeComponent.createBooleanSymbol("IMC_LIGHTSENSORTYPE", illuminanceMeasurementClusterServerAttributes)
illuMeasClusterServerAttributeLightSensorType.setLabel("0x0004 LightSensorType")
illuMeasClusterServerAttributeLightSensorType.setDefaultValue(True)
illuMeasClusterServerAttributeLightSensorType.setDescription("LightSensorType - check the box to enable")

global illuMeasClusterServerAttributeClusterRevision
illuMeasClusterServerAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("IMC_CLUSTERREVISION", illuminanceMeasurementClusterServerAttributes)
illuMeasClusterServerAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
illuMeasClusterServerAttributeClusterRevision.setDefaultValue(True)
illuMeasClusterServerAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
illuMeasClusterServerAttributeClusterRevision.setReadOnly(True)

global illuMeasClusterServerAttributeCount
illuMeasClusterServerAttributeCount = drvZigbeeComponent.createIntegerSymbol("IMC_SERVERATTRIBUTECOUNT", illuminanceMeasurementClusterServerAttributes)
illuMeasClusterServerAttributeCount.setLabel("Attributes Count")
illuMeasClusterServerAttributeCount.setDefaultValue(illuMeasClusterServerAttributeCountUpdate(0,0))
illuMeasClusterServerAttributeCount.setVisible(True)
illuMeasClusterServerAttributeCount.setDescription("Attributes Count")
illuMeasClusterServerAttributeCount.setReadOnly(True)
illuMeasClusterServerAttributeCount.setDependencies(illuMeasClusterServerAttributeCountUpdate,["IMC_MEASUREDVALUE","IMC_MINMEASUREDVALUE","IMC_MAXMEASUREDVALUE","IMC_TOLERANCE","IMC_LIGHTSENSORTYPE","IMC_CLUSTERREVISION"])
#################               Server Commands                                 ###############

# Commands received
# No cluster specific commands are received by the server.

# Commands generated
# No cluster specific commands are generated by the server.

#################               Client Attributes                                 ###############
global illuMeasClusterClientAttributeClusterRevision
illuMeasClusterClientAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("IMCC_CLUSTERREVISION", illuminanceMeasurementClusterClientAttributes)
illuMeasClusterClientAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
illuMeasClusterClientAttributeClusterRevision.setDefaultValue(True)
illuMeasClusterClientAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
illuMeasClusterClientAttributeClusterRevision.setReadOnly(True)

global illuMeasClusterClientAttributeCount
illuMeasClusterClientAttributeCount = drvZigbeeComponent.createIntegerSymbol("IMCC_CLIENTATTRIBUTECOUNT", illuminanceMeasurementClusterClientAttributes)
illuMeasClusterClientAttributeCount.setLabel("Attributes Count")
illuMeasClusterClientAttributeCount.setDefaultValue(illuMeasClusterClientAttributeCountUpdate(0,0))
illuMeasClusterClientAttributeCount.setVisible(True)
illuMeasClusterClientAttributeCount.setDescription("Attributes Count")
illuMeasClusterClientAttributeCount.setReadOnly(True)
illuMeasClusterClientAttributeCount.setDependencies(illuMeasClusterClientAttributeCountUpdate,["IMCC_CLUSTERREVISION"])

#################               Client Commands                                 ###############

# Commands generated
# No cluster specific commands are generated by the client.

# Commands received
# No cluster specific commands are received by the client.


############################################################################################################
# Default Values Settings based on device type
illuminanceMeasurementClusterHandling()

############################################################################################################
##################################### FTL Files Definitions ################################################
############################################################################################################

# ILLUMINANCE MEASUREMENT CLUSTER Common header
illuMeasClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_ILLUMINANCEMEASUREMENT_CLUSTER_CONF", None)
illuMeasClusterConf.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/illuminancemeasurement/zclIlluminanceMeasurementCluster.h.ftl")
illuMeasClusterConf.setOutputName("zclIlluminanceMeasurementCluster.h")
illuMeasClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
illuMeasClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
illuMeasClusterConf.setType("HEADER")
illuMeasClusterConf.setOverwrite(True)
illuMeasClusterConf.setMarkup(True)

# ILLUMINANCE MEASUREMENT CLUSTER - Combined Interface
illuMeasClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_ILLUMINANCEMEASUREMENT_CLUSTER_CONF_SRC_CI", None)
illuMeasClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/illuminancemeasurement/ciIlluminanceMeasurementCluster.c.ftl")
illuMeasClusterConfSrc.setOutputName("ciIlluminanceMeasurementCluster.c")
illuMeasClusterConfSrc.setDestPath("/zigbee/z3device/combinedInterface")
illuMeasClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/combinedInterface/")
illuMeasClusterConfSrc.setType("SOURCE")
illuMeasClusterConfSrc.setOverwrite(True)
illuMeasClusterConfSrc.setMarkup(True)
illuMeasClusterConfSrc.setEnabled(checkDevTypeCombInterface and illuminanceMeasurementCluster.getValue())
illuMeasClusterConfSrc.setDependencies(combinedInterfaceIlluminanceMeasurementClusterEnableCheck, ["ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE"])

illuMeasClusterConfInc = drvZigbeeComponent.createFileSymbol("CIILLUMINANCEMEASUREMENTCLUSTER_H", None)
illuMeasClusterConfInc.setSourcePath("/driver/zigbee" + suffix + "/application/zigbee_only/Zigbee_Device_Application/devicetypes/combinedInterface/include/ciIlluminanceMeasurementCluster.h")
illuMeasClusterConfInc.setOutputName("ciIlluminanceMeasurementCluster.h")
illuMeasClusterConfInc.setDestPath("/zigbee/z3device/combinedInterface/include")
illuMeasClusterConfInc.setProjectPath("config/" + configName + "/zigbee/z3device/combinedInterface/include/")
illuMeasClusterConfInc.setType("HEADER")
illuMeasClusterConfInc.setOverwrite(True)
illuMeasClusterConfInc.setEnabled(checkDevTypeCombInterface and illuminanceMeasurementCluster.getValue())
illuMeasClusterConfInc.setDependencies(combinedInterfaceIlluminanceMeasurementClusterEnableCheck,["ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE"])

# ILLUMINANCE MEASUREMENT CLUSTER - Multi Sensor
illuMeasClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_ILLUMINANCEMEASUREMENT_CLUSTER_CONF_SRC_MS", None)
illuMeasClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/illuminancemeasurement/lsIlluminanceMeasurementCluster.c.ftl")
illuMeasClusterConfSrc.setOutputName("lsIlluminanceMeasurementCluster.c")
illuMeasClusterConfSrc.setDestPath("/zigbee/z3device/multiSensor")
illuMeasClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/multiSensor/")
illuMeasClusterConfSrc.setType("SOURCE")
illuMeasClusterConfSrc.setOverwrite(True)
illuMeasClusterConfSrc.setMarkup(True)
illuMeasClusterConfSrc.setEnabled(checkDevTypeMultiSensor)

# ILLUMINANCE MEASUREMENT CLUSTER - Custom
illuMeasClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_ILLUMINANCEMEASUREMENT_CLUSTER_CONF_SRC_CUSTOM", None)
illuMeasClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/illuminancemeasurement/customIlluminanceMeasurementCluster.c.ftl")
illuMeasClusterConfSrc.setOutputName("customIlluminanceMeasurementCluster.c")
illuMeasClusterConfSrc.setDestPath("/zigbee/z3device/custom")
illuMeasClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/custom/")
illuMeasClusterConfSrc.setType("SOURCE")
illuMeasClusterConfSrc.setOverwrite(True)
illuMeasClusterConfSrc.setMarkup(True)
illuMeasClusterConfSrc.setEnabled(checkDevTypeCustom and illuminanceMeasurementCluster.getValue())
illuMeasClusterConfSrc.setDependencies(customIlluminanceMeasurementClusterEnableCheck,["ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE"])
############################################################################################################
