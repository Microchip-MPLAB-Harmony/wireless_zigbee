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
###########################################  CONSOLE FILES CLUSTER RELATED FTL DEFINTIONS  #################
############################################################################################################

############################################################################################################
##################################### FTL Files Definitions ################################################
############################################################################################################

# Warning definition for exceeding number of clusters supported
global clusterWarning
clusterWarning = drvZigbeeComponent.createCommentSymbol("CLUSTER_WARNING", None)
clusterWarning.setLabel("Warning!!! Selected number of clusters is exceeding the recommended total number of Client and Server Clusters.")

def clusterWarningCheck(symbol, event):
    print numberOfServerClusterCountVar.getValue() + numberOfClientClusterCountVar.getValue()
    if ((numberOfServerClusterCountVar.getValue() + numberOfClientClusterCountVar.getValue())>30):
        symbol.setVisible(True)
        Log.writeErrorMessage("Warning!!! Selected number of clusters is exceeding the recommended total number of Client and Server Clusters.")
    else:
        symbol.setVisible(False)

def numberOfServerClusterCountUpdate(symbol, event):
    count = 0
    if (alarmsCluster.getValue() and (alarmsClusterCS.getValue() != "CLIENT")):
        count += 1
    if (basicCluster.getValue() and (basicClusterCS.getValue() != "CLIENT")):
        count += 1
    if (ColorControlCluster.getValue() and (ColorControlClusterCS.getValue() != "CLIENT")):
        count += 1
    if (diagnosticsCluster.getValue() and (diagnosticsClusterCS.getValue() != "CLIENT")):
        count += 1
    if (fanControlCluster.getValue() and (fanControlClusterCS.getValue() != "CLIENT")):
        count += 1
    if (GroupsCluster.getValue() and (GroupsClusterCS.getValue() != "CLIENT")):
        count += 1
    if (iasACECluster.getValue() and (iasACEClusterCS.getValue() != "CLIENT")):
        count += 1
    if (iasZoneCluster.getValue() and (iasZoneClusterCS.getValue() != "CLIENT")):
        count += 1
    if (IdentifyCluster.getValue() and (IdentifyClusterCS.getValue() != "CLIENT")):
        count += 1
    if (illuminanceMeasurementCluster.getValue() and (illuminanceMeasurementClusterCS.getValue() != "CLIENT")):
        count += 1
    if (LevelControlCluster.getValue() and (LevelControlClusterCS.getValue() != "CLIENT")):
        count += 1
    if (occupancySensingCluster.getValue() and (occupancySensingClusterCS.getValue() != "CLIENT")):
        count += 1
    if (OnOffCluster.getValue() and (OnOffClusterCS.getValue() != "CLIENT")):
        count += 1
    if (ScenesCluster.getValue() and (ScenesClusterCS.getValue() != "CLIENT")):
        count += 1
    if (temperatureMeasurementCluster.getValue() and (temperatureMeasurementClusterCS.getValue() != "CLIENT")):
        count += 1
    if (thermostatCluster.getValue() and (thermostatClusterCS.getValue() != "CLIENT")):
        count += 1
    if (thermostatUICluster.getValue() and (thermostatUIClusterCS.getValue() != "CLIENT")):
        count += 1
    if (timeCluster.getValue() and (timeClusterCS.getValue() != "CLIENT")):
        count += 1
    if (waterContentMeasurementCluster.getValue() and (waterContentMeasurementClusterCS.getValue() != "CLIENT")):
        count += 1
    numberOfServerClusterCountVar.setValue(count)
    #print numberOfServerClusterCountVar.getValue()
    if ((numberOfServerClusterCountVar.getValue() + numberOfServerClusterCountVar.getValue())> 30):
       clusterWarning.setVisible(True)
       Log.writeErrorMessage("Warning!!! Selected number of clusters is exceeding the recommended total number of Client and Server Clusters.")
    else:
       clusterWarning.setVisible(False)
    return count

def numberOfClientClusterCountUpdate(symbol, event):
    count = 0
    if (alarmsCluster.getValue() and (alarmsClusterCS.getValue() != "SERVER")):
        count += 1
    if (basicCluster.getValue() and (basicClusterCS.getValue() != "SERVER")):
        count += 1
    if (ColorControlCluster.getValue() and (ColorControlClusterCS.getValue() != "SERVER")):
        count += 1
    if (diagnosticsCluster.getValue() and (diagnosticsClusterCS.getValue() != "SERVER")):
        count += 1
    if (fanControlCluster.getValue() and (fanControlClusterCS.getValue() != "SERVER")):
        count += 1
    if (GroupsCluster.getValue() and (GroupsClusterCS.getValue() != "SERVER")):
        count += 1
    if (iasACECluster.getValue() and (iasACEClusterCS.getValue() != "SERVER")):
        count += 1
    if (iasZoneCluster.getValue() and (iasZoneClusterCS.getValue() != "SERVER")):
        count += 1
    if (IdentifyCluster.getValue() and (IdentifyClusterCS.getValue() != "SERVER")):
        count += 1
    if (illuminanceMeasurementCluster.getValue() and (illuminanceMeasurementClusterCS.getValue() != "SERVER")):
        count += 1
    if (LevelControlCluster.getValue() and (LevelControlClusterCS.getValue() != "SERVER")):
        count += 1
    if (occupancySensingCluster.getValue() and (occupancySensingClusterCS.getValue() != "SERVER")):
        count += 1
    if (OnOffCluster.getValue() and (OnOffClusterCS.getValue() != "SERVER")):
        count += 1
    if (ScenesCluster.getValue() and (ScenesClusterCS.getValue() != "SERVER")):
        count += 1
    if (temperatureMeasurementCluster.getValue() and (temperatureMeasurementClusterCS.getValue() != "SERVER")):
        count += 1
    if (thermostatCluster.getValue() and (thermostatClusterCS.getValue() != "SERVER")):
        count += 1
    if (thermostatUICluster.getValue() and (thermostatUIClusterCS.getValue() != "SERVER")):
        count += 1
    if (timeCluster.getValue() and (timeClusterCS.getValue() != "SERVER")):
        count += 1
    if (waterContentMeasurementCluster.getValue() and (waterContentMeasurementClusterCS.getValue() != "SERVER")):
        count += 1
    numberOfClientClusterCountVar.setValue(count)
    #print numberOfClientClusterCountVar.getValue()
    if ((numberOfServerClusterCountVar.getValue() + numberOfServerClusterCountVar.getValue())> 30):
       clusterWarning.setVisible(True)
       #Log.writeErrorMessage("Warning!!! Selected number of clusters is exceeding the recommended total number of Client and Server Clusters.")
    else:
       clusterWarning.setVisible(False)
    return count

global numberOfServerClusterCountVar
numberOfServerClusterCountVar = drvZigbeeComponent.createIntegerSymbol("NUMBER_OF_SERVER_CLUSTERS_COUNT", None)
numberOfServerClusterCountVar.setLabel("Server Clusters Count")
numberOfServerClusterCountVar.setDefaultValue(numberOfServerClusterCountUpdate(0,0))
numberOfServerClusterCountVar.setVisible(False)
numberOfServerClusterCountVar.setDescription("Server Clusters Count")
numberOfServerClusterCountVar.setReadOnly(True)
numberOfServerClusterCountVar.setDependencies(numberOfServerClusterCountUpdate,["ALARMS_CLUSTER_ENABLE","ALARMS_CLUSTER_CS",
"BASIC_CLUSTER_ENABLE","BASIC_CLUSTER_CS",
"COLORCONTROL_CLUSTER_ENABLE","COLORCONTROL_CLUSTER_CS",
"DIAGONSTICS_CLUSTER_ENABLE","DIAGONSTICS_CLUSTER_CS",
"FANCONTROL_CLUSTER_ENABLE","FANCONTROL_CLUSTER_CS",
"GROUPS_CLUSTER_ENABLE","GROUPS_CLUSTER_CS",
"IASACE_CLUSTER_ENABLE","IASACE_CLUSTER_CS",
"IASZONE_CLUSTER_ENABLE","IASZONE_CLUSTER_CS",
"IDENTIFY_CLUSTER_ENABLE","IDENTIFY_CLUSTER_CS",
"ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE","ILLUMINANCEMEASUREMENT_CLUSTER_CS",
"LEVELCONTROL_CLUSTER_ENABLE","LEVELCONTROL_CLUSTER_CS",
"OCCUPANCYSENSING_CLUSTER_ENABLE","OCCUPANCYSENSING_CLUSTER_CS",
"ONOFF_CLUSTER_ENABLE","ONOFF_CLUSTER_CS",
"SCENES_CLUSTER_ENABLE","SCENES_CLUSTER_CS",
"TEMPERATUREMEASUREMENT_CLUSTER_ENABLE","TEMPERATUREMEASUREMENT_CLUSTER_CS",
"THERMOSTAT_CLUSTER_ENABLE","THERMOSTAT_CLUSTER_CS",
"THERMOSTATUI_CLUSTER_ENABLE","THERMOSTATUI_CLUSTER_CS",
"TIME_CLUSTER_ENABLE","TIME_CLUSTER_CS",
"WATERCONTENTMEASUREMENT_CLUSTER_ENABLE","WATERCONTENTMEASUREMENT_CLUSTER_CS"
])

global numberOfClientClusterCountVar
numberOfClientClusterCountVar = drvZigbeeComponent.createIntegerSymbol("NUMBER_OF_CLIENT_CLUSTERS_COUNT", None)
numberOfClientClusterCountVar.setLabel("Client Clusters Count")
numberOfClientClusterCountVar.setDefaultValue(numberOfClientClusterCountUpdate(0,0))
numberOfClientClusterCountVar.setVisible(False)
numberOfClientClusterCountVar.setDescription("Client Clusters Count")
numberOfClientClusterCountVar.setReadOnly(True)
numberOfClientClusterCountVar.setDependencies(numberOfClientClusterCountUpdate,["ALARMS_CLUSTER_ENABLE","ALARMS_CLUSTER_CS",
"BASIC_CLUSTER_ENABLE","BASIC_CLUSTER_CS",
"COLORCONTROL_CLUSTER_ENABLE","COLORCONTROL_CLUSTER_CS",
"DIAGONSTICS_CLUSTER_ENABLE","DIAGONSTICS_CLUSTER_CS",
"FANCONTROL_CLUSTER_ENABLE","FANCONTROL_CLUSTER_CS",
"GROUPS_CLUSTER_ENABLE","GROUPS_CLUSTER_CS",
"IASACE_CLUSTER_ENABLE","IASACE_CLUSTER_CS",
"IASZONE_CLUSTER_ENABLE","IASZONE_CLUSTER_CS",
"IDENTIFY_CLUSTER_ENABLE","IDENTIFY_CLUSTER_CS",
"ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE","ILLUMINANCEMEASUREMENT_CLUSTER_CS",
"LEVELCONTROL_CLUSTER_ENABLE","LEVELCONTROL_CLUSTER_CS",
"OCCUPANCYSENSING_CLUSTER_ENABLE","OCCUPANCYSENSING_CLUSTER_CS",
"ONOFF_CLUSTER_ENABLE","ONOFF_CLUSTER_CS",
"SCENES_CLUSTER_ENABLE","SCENES_CLUSTER_CS",
"TEMPERATUREMEASUREMENT_CLUSTER_ENABLE","TEMPERATUREMEASUREMENT_CLUSTER_CS",
"THERMOSTAT_CLUSTER_ENABLE","THERMOSTAT_CLUSTER_CS",
"THERMOSTATUI_CLUSTER_ENABLE","THERMOSTATUI_CLUSTER_CS",
"TIME_CLUSTER_ENABLE","TIME_CLUSTER_CS",
"WATERCONTENTMEASUREMENT_CLUSTER_ENABLE","WATERCONTENTMEASUREMENT_CLUSTER_CS"
])


clusterWarning.setVisible((numberOfServerClusterCountVar.getValue() + numberOfClientClusterCountVar.getValue()) > 30)
# clusterWarning.setDependencies(clusterWarningCheck,["ALARMS_CLUSTER_ENABLE","ALARMS_CLUSTER_CS",
# "BASIC_CLUSTER_ENABLE","BASIC_CLUSTER_CS",
# "COLORCONTROL_CLUSTER_ENABLE","COLORCONTROL_CLUSTER_CS",
# "DIAGONSTICS_CLUSTER_ENABLE","DIAGONSTICS_CLUSTER_CS",
# "FANCONTROL_CLUSTER_ENABLE","FANCONTROL_CLUSTER_CS",
# "GROUPS_CLUSTER_ENABLE","GROUPS_CLUSTER_CS",
# "IASACE_CLUSTER_ENABLE","IASACE_CLUSTER_CS",
# "IASZONE_CLUSTER_ENABLE","IASZONE_CLUSTER_CS",
# "IDENTIFY_CLUSTER_ENABLE","IDENTIFY_CLUSTER_CS",
# "ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE","ILLUMINANCEMEASUREMENT_CLUSTER_CS",
# "LEVELCONTROL_CLUSTER_ENABLE","LEVELCONTROL_CLUSTER_CS",
# "OCCUPANCYSENSING_CLUSTER_ENABLE","OCCUPANCYSENSING_CLUSTER_CS",
# "ONOFF_CLUSTER_ENABLE","ONOFF_CLUSTER_CS",
# "SCENES_CLUSTER_ENABLE","SCENES_CLUSTER_CS",
# "TEMPERATUREMEASUREMENT_CLUSTER_ENABLE","TEMPERATUREMEASUREMENT_CLUSTER_CS",
# "THERMOSTAT_CLUSTER_ENABLE","THERMOSTAT_CLUSTER_CS",
# "THERMOSTATUI_CLUSTER_ENABLE","THERMOSTATUI_CLUSTER_CS",
# "TIME_CLUSTER_ENABLE","TIME_CLUSTER_CS",
# "WATERCONTENTMEASUREMENT_CLUSTER_ENABLE","WATERCONTENTMEASUREMENT_CLUSTER_CS"
# ])

# Light Console
clusterConsoleSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_CONSOLE_LIGHT", None)
clusterConsoleSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/console/lightConsole.c.ftl")
clusterConsoleSrc.setOutputName("lightConsole.c")
clusterConsoleSrc.setDestPath('../../app_zigbee/zigbee_console/')
clusterConsoleSrc.setProjectPath('app_zigbee/zigbee_console/')
clusterConsoleSrc.setType("SOURCE")
clusterConsoleSrc.setOverwrite(True)
clusterConsoleSrc.setMarkup(True)
clusterConsoleSrc.setEnabled(checkDevTypeLight)

# Combined Interface Console
clusterConsoleSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_CONSOLE_CI", None)
clusterConsoleSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/console/ciConsole.c.ftl")
clusterConsoleSrc.setOutputName("ciConsole.c")
clusterConsoleSrc.setDestPath('../../app_zigbee/zigbee_console/')
clusterConsoleSrc.setProjectPath('app_zigbee/zigbee_console/')
clusterConsoleSrc.setType("SOURCE")
clusterConsoleSrc.setOverwrite(True)
clusterConsoleSrc.setMarkup(True)
clusterConsoleSrc.setEnabled(checkDevTypeCombInterface)

# Color Scene Controller Console
clusterConsoleSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_CONSOLE_CSC", None)
clusterConsoleSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/console/cscConsole.c.ftl")
clusterConsoleSrc.setOutputName("cscConsole.c")
clusterConsoleSrc.setDestPath('../../app_zigbee/zigbee_console/')
clusterConsoleSrc.setProjectPath('app_zigbee/zigbee_console/')
clusterConsoleSrc.setType("SOURCE")
clusterConsoleSrc.setOverwrite(True)
clusterConsoleSrc.setMarkup(True)
clusterConsoleSrc.setEnabled(checkDevTypeRemote)

# IAS ACE Console
clusterConsoleSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_CONSOLE_IAS", None)
clusterConsoleSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/console/iasACEConsole.c.ftl")
clusterConsoleSrc.setOutputName("iasACEConsole.c")
clusterConsoleSrc.setDestPath('../../app_zigbee/zigbee_console/')
clusterConsoleSrc.setProjectPath('app_zigbee/zigbee_console/')
clusterConsoleSrc.setType("SOURCE")
clusterConsoleSrc.setOverwrite(True)
clusterConsoleSrc.setMarkup(True)
clusterConsoleSrc.setEnabled(checkDevTypeIasAce)

# MultiSensor Console
clusterConsoleSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_CONSOLE_MS", None)
clusterConsoleSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/console/msConsole.c.ftl")
clusterConsoleSrc.setOutputName("msConsole.c")
clusterConsoleSrc.setDestPath('../../app_zigbee/zigbee_console/')
clusterConsoleSrc.setProjectPath('app_zigbee/zigbee_console/')
clusterConsoleSrc.setType("SOURCE")
clusterConsoleSrc.setOverwrite(True)
clusterConsoleSrc.setMarkup(True)
clusterConsoleSrc.setEnabled(checkDevTypeMultiSensor)

# Thermostat Console
clusterConsoleSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_CONSOLE_TH", None)
clusterConsoleSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/console/thConsole.c.ftl")
clusterConsoleSrc.setOutputName("thConsole.c")
clusterConsoleSrc.setDestPath('../../app_zigbee/zigbee_console/')
clusterConsoleSrc.setProjectPath('app_zigbee/zigbee_console/')
clusterConsoleSrc.setType("SOURCE")
clusterConsoleSrc.setOverwrite(True)
clusterConsoleSrc.setMarkup(True)
clusterConsoleSrc.setEnabled(checkDevTypeThermostat)

# Custom Console
clusterConsoleSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_CONSOLE_CUSTOM", None)
clusterConsoleSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/console/customConsole.c.ftl")
clusterConsoleSrc.setOutputName("customConsole.c")
clusterConsoleSrc.setDestPath('../../app_zigbee/zigbee_console/')
clusterConsoleSrc.setProjectPath('app_zigbee/zigbee_console/')
clusterConsoleSrc.setType("SOURCE")
clusterConsoleSrc.setOverwrite(True)
clusterConsoleSrc.setMarkup(True)
clusterConsoleSrc.setEnabled(checkDevTypeCustom)

# Custom Clusters
clusterConsoleSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_CLUSTERS_CUSTOM", None)
clusterConsoleSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/console/custom.c.ftl")
clusterConsoleSrc.setOutputName("custom.c")
clusterConsoleSrc.setDestPath('../../app_zigbee/zigbee_console/')
clusterConsoleSrc.setProjectPath('app_zigbee/zigbee_console/')
clusterConsoleSrc.setType("SOURCE")
clusterConsoleSrc.setOverwrite(True)
clusterConsoleSrc.setMarkup(True)
clusterConsoleSrc.setEnabled(checkDevTypeCustom)

clusterConsoleSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_CLUSTERS_CUSTOM1", None)
clusterConsoleSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/console/customClusters.c.ftl")
clusterConsoleSrc.setOutputName("customClusters.c")
clusterConsoleSrc.setDestPath('../../app_zigbee/zigbee_console/')
clusterConsoleSrc.setProjectPath('app_zigbee/zigbee_console/')
clusterConsoleSrc.setType("SOURCE")
clusterConsoleSrc.setOverwrite(True)
clusterConsoleSrc.setMarkup(True)
clusterConsoleSrc.setEnabled(checkDevTypeCustom)

clusterConsoleSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_CLUSTERS_CUSTOM2", None)
clusterConsoleSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/console/customClusters.h.ftl")
clusterConsoleSrc.setOutputName("customClusters.h")
clusterConsoleSrc.setDestPath('zigbee/z3device/custom/include/')
clusterConsoleSrc.setProjectPath("config/" + configName + '/zigbee/z3device/custom/include/')
clusterConsoleSrc.setType("HEADER")
clusterConsoleSrc.setOverwrite(True)
clusterConsoleSrc.setMarkup(True)
clusterConsoleSrc.setEnabled(checkDevTypeCustom)

