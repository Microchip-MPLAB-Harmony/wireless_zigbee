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
###########################################  THERMOSTAT CLUSTER CONFIGURATION   #################################
############################################################################################################

############################################################################################################
############################################# Function Definitions #########################################
############################################################################################################
def thermostatClusterCsCheck(symbol, event):
    if (thermostatCluster.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def thermostatClusterEnabledCheck(symbol, event):
    if (thermostatCluster.getValue() == False):
        symbol.setEnabled(False)
    else:
        symbol.setEnabled(True)

def customThermostatClusterEnabledCheck(symbol, event):
    if ((zigbeeDeviceType.getValue() == 'ZIGBEE_CUSTOM') and (thermostatCluster.getValue() == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def thermostatClusterClientCheck(symbol, event):
    if ((thermostatCluster.getValue() == False) or thermostatClusterCS.getValue() == "SERVER"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def thermostatClusterServerCheck(symbol, event):
    if ((thermostatCluster.getValue() == False) or thermostatClusterCS.getValue() == "CLIENT"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def thermostatClusterHandling():

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
        thermostatCluster.setVisible(False)
        thermostatCluster.setValue(False)
    elif ((getDevice == "ZIGBEE_COMBINED_INTERFACE")):
        thermostatCluster.setVisible(True)
        thermostatCluster.setValue(True)
        thermostatCluster.setReadOnly(True)
        thermostatClusterCS.setValue("CLIENT")
        thermostatClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_THERMOSTAT")):
        thermostatCluster.setVisible(True)
        thermostatCluster.setValue(True)
        thermostatCluster.setReadOnly(True)
        thermostatClusterCS.setValue("BOTH")
        thermostatClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_CUSTOM")):
        thermostatCluster.setVisible(True)
        thermostatCluster.setValue(True)
        thermostatClusterCS.setValue("BOTH")
    else:
        thermostatCluster.setVisible(False)

def thermostatClusterServerAttributeCountUpdate(symbol, event):
    count = 0
    if (thermostatClusterServerAttributeLocalTemperature.getValue()):
        count += 1
    if (thermostatClusterServerAttributeOutdoorTemperature.getValue()):
        count += 1
    if (thermostatClusterServerAttributeOccupancy.getValue()):
        count += 1
    if (thermostatClusterServerAttributeAbsMinHeatSetpointLimit.getValue()):
        count += 1
    if (thermostatClusterServerAttributeAbsMaxHeatSetpointLimit.getValue()):
        count += 1
    if (thermostatClusterServerAttributeAbsMinCoolSetpointLimit.getValue()):
        count += 1
    if (thermostatClusterServerAttributeAbsMaxCoolSetpointLimit.getValue()):
        count += 1
    if (thermostatClusterServerAttributePICoolingDemand.getValue()):
        count += 1
    if (thermostatClusterServerAttributePIHeatingDemand.getValue()):
        count += 1
    if (thermostatClusterServerAttributeHVACSystemTypeConfiguration.getValue()):
        count += 1
    if (thermostatClusterServerAttributeLocalTempCalib.getValue()):
        count += 1
    if (thermostatClusterServerAttributeOccupiedCoolingSetpoint.getValue()):
        count += 1
    if (thermostatClusterServerAttributeOccupiedHeatingSetpoint.getValue()):
        count += 1
    if (thermostatClusterServerAttributeUnoccupiedCoolingSetpoint.getValue()):
        count += 1
    if (thermostatClusterServerAttributeUnoccupiedHeatingSetpoint.getValue()):
        count += 1
    if (thermostatClusterServerAttributeMinHeatSetpointLimit.getValue()):
        count += 1
    if (thermostatClusterServerAttributeMaxHeatSetpointLimit.getValue()):
        count += 1
    if (thermostatClusterServerAttributeMinCoolSetpointLimit.getValue()):
        count += 1
    if (thermostatClusterServerAttributeMaxCoolSetpointLimit.getValue()):
        count += 1
    if (thermostatClusterServerAttributeMinSetpointDeadBand.getValue()):
        count += 1
    if (thermostatClusterServerAttributeRemoteSensing.getValue()):
        count += 1
    if (thermostatClusterServerAttributeControlSequenceOfOperation.getValue()):
        count += 1
    if (thermostatClusterServerAttributeSystemMode.getValue()):
        count += 1
    if (thermostatClusterServerAttributeAlarmMask.getValue()):
        count += 1
    if (thermostatClusterServerAttributeThermostatRunningMode.getValue()):
        count += 1
    if (thermostatClusterServerAttributeClusterRevision.getValue()):
        count += 1
    thermostatClusterServerAttributeCount.setValue(count) 
    return count

def thermostatClusterServerCommandCountUpdate(symbol, event):
    count = 0
    if (thermostatClusterServerCommandSetPointRaiseLower.getValue()):
        count += 1
    thermostatClusterServerCommandCount.setValue(count)
    return count

def thermostatClusterClientAttributeCountUpdate(symbol, event):
    count = 0
    if (thermostatClusterClientAttributeClusterRevision.getValue()):
        count += 1
    thermostatClusterClientAttributeCount.setValue(count)
    return count

############################################################################################################
##################################### Configuration Item Definitions #######################################
############################################################################################################

global thermostatCluster
thermostatCluster = drvZigbeeComponent.createBooleanSymbol("THERMOSTAT_CLUSTER_ENABLE", clusterConfigMenu)
thermostatCluster.setLabel("0x0201 Thermostat Cluster")
thermostatCluster.setDefaultValue(False)
thermostatCluster.setVisible(False)
thermostatCluster.setDescription("THERMOSTAT CLUSTER- check the box to enable")
thermostatCluster.setReadOnly(False)

global thermostatClusterCS
thermostatClusterCS = drvZigbeeComponent.createComboSymbol("THERMOSTAT_CLUSTER_CS",  thermostatCluster, ["CLIENT","SERVER", "BOTH"])
thermostatClusterCS.setLabel("Supported Implementation")
thermostatClusterCS.setDefaultValue("BOTH")
#thermostatClusterCS.setVisible(False)
thermostatClusterCS.setDescription("Thermostat Cluster Supported Implementation- Select the option")
thermostatClusterCS.setDependencies(thermostatClusterCsCheck,["THERMOSTAT_CLUSTER_ENABLE"])

thermostatClusterClientMenu = drvZigbeeComponent.createMenuSymbol("THERMOSTAT_CLUSTER_CLIENT_MENU", thermostatCluster)
thermostatClusterClientMenu.setLabel("Client")
#thermostatClusterClientMenu.setVisible(False)
thermostatClusterClientMenu.setDescription("THERMOSTAT CLUSTER CLIENT")
thermostatClusterClientMenu.setDependencies(thermostatClusterClientCheck,["THERMOSTAT_CLUSTER_CS","THERMOSTAT_CLUSTER_ENABLE"])

thermostatClusterServerMenu = drvZigbeeComponent.createMenuSymbol("THERMOSTAT_CLUSTER_SERVER_MENU", thermostatCluster)
thermostatClusterServerMenu.setLabel("Server")
#thermostatClusterServerMenu.setVisible(False)
thermostatClusterServerMenu.setDescription("THERMOSTAT CLUSTER SERVER")
thermostatClusterServerMenu.setDependencies(thermostatClusterServerCheck,["THERMOSTAT_CLUSTER_CS","THERMOSTAT_CLUSTER_ENABLE"])

thermostatClusterClientAttributes = drvZigbeeComponent.createMenuSymbol("THERMOSTAT_CLUSTER_CLIENT__ATTRIBUTES_MENU", thermostatClusterClientMenu)
thermostatClusterClientAttributes.setLabel("Attributes")
#thermostatClusterClientAttributes.setVisible(False)
thermostatClusterClientAttributes.setDescription("THERMOSTAT CLUSTER CLIENT ATTRIBUTES")
thermostatClusterClientAttributes.setDependencies(thermostatClusterClientCheck,["THERMOSTAT_CLUSTER_CS"])

# thermostatClusterClientCommands = drvZigbeeComponent.createMenuSymbol("THERMOSTAT_CLUSTER_CLIENT__COMMANDS_MENU", thermostatClusterClientMenu)
# thermostatClusterClientCommands.setLabel("Commands")
# #thermostatClusterClientCommands.setVisible(False)
# thermostatClusterClientCommands.setDescription("THERMOSTAT CLUSTER CLIENT COMMANDS")
# thermostatClusterClientCommands.setDependencies(thermostatClusterClientCheck,["THERMOSTAT_CLUSTER_CS"])

thermostatClusterServerAttributes = drvZigbeeComponent.createMenuSymbol("THERMOSTAT_CLUSTER_SERVER__ATTRIBUTES_MENU", thermostatClusterServerMenu)
thermostatClusterServerAttributes.setLabel("Attributes")
#thermostatClusterServerAttributes.setVisible(False)
thermostatClusterServerAttributes.setDescription("THERMOSTAT CLUSTER SERVER ATTRIBUTES")
thermostatClusterServerAttributes.setDependencies(thermostatClusterServerCheck,["THERMOSTAT_CLUSTER_CS"])

thermostatClusterServerCommands = drvZigbeeComponent.createMenuSymbol("THERMOSTAT_CLUSTER_SERVER__COMMANDS_MENU", thermostatClusterServerMenu)
thermostatClusterServerCommands.setLabel("Commands")
#thermostatClusterServerCommands.setVisible(False)
thermostatClusterServerCommands.setDescription("THERMOSTAT CLUSTER SERVER COMMANDS")
thermostatClusterServerCommands.setDependencies(thermostatClusterServerCheck,["THERMOSTAT_CLUSTER_CS"])

#################               Server Attributes                                 ###############

## Thermostat Information Attribute Set
global thermostatClusterServerAttributeLocalTemperature
thermostatClusterServerAttributeLocalTemperature = drvZigbeeComponent.createBooleanSymbol("TC_LOCALTEMP", thermostatClusterServerAttributes)
thermostatClusterServerAttributeLocalTemperature.setLabel("0x0000 LocalTemperature")
thermostatClusterServerAttributeLocalTemperature.setDefaultValue(True)
thermostatClusterServerAttributeLocalTemperature.setDescription("LocalTemperature - check the box to enable")
thermostatClusterServerAttributeLocalTemperature.setReadOnly(True)

global thermostatClusterServerAttributeOutdoorTemperature
thermostatClusterServerAttributeOutdoorTemperature = drvZigbeeComponent.createBooleanSymbol("TC_OUTDOORTEMP", thermostatClusterServerAttributes)
thermostatClusterServerAttributeOutdoorTemperature.setLabel("0x0001 OutdoorTemperature")
thermostatClusterServerAttributeOutdoorTemperature.setDefaultValue(True)
thermostatClusterServerAttributeOutdoorTemperature.setDescription("OutdoorTemperature - check the box to enable")

global thermostatClusterServerAttributeOccupancy
thermostatClusterServerAttributeOccupancy = drvZigbeeComponent.createBooleanSymbol("TC_OCCUPANCY", thermostatClusterServerAttributes)
thermostatClusterServerAttributeOccupancy.setLabel("0x0002 Occupancy")
thermostatClusterServerAttributeOccupancy.setDefaultValue(True)
thermostatClusterServerAttributeOccupancy.setDescription("Occupancy - check the box to enable")

global thermostatClusterServerAttributeAbsMinHeatSetpointLimit
thermostatClusterServerAttributeAbsMinHeatSetpointLimit = drvZigbeeComponent.createBooleanSymbol("TC_ABSMINHEATSETPOINTLIMIT", thermostatClusterServerAttributes)
thermostatClusterServerAttributeAbsMinHeatSetpointLimit.setLabel("0x0003 AbsMinHeatSetpointLimit")
thermostatClusterServerAttributeAbsMinHeatSetpointLimit.setDefaultValue(True)
thermostatClusterServerAttributeAbsMinHeatSetpointLimit.setDescription("AbsMinHeatSetpointLimit - check the box to enable")

global thermostatClusterServerAttributeAbsMaxHeatSetpointLimit
thermostatClusterServerAttributeAbsMaxHeatSetpointLimit = drvZigbeeComponent.createBooleanSymbol("TC_ABSMAXHEATSETPOINTLIMIT", thermostatClusterServerAttributes)
thermostatClusterServerAttributeAbsMaxHeatSetpointLimit.setLabel("0x0004 AbsMaxHeatSetpointLimit")
thermostatClusterServerAttributeAbsMaxHeatSetpointLimit.setDefaultValue(True)
thermostatClusterServerAttributeAbsMaxHeatSetpointLimit.setDescription("AbsMaxHeatSetpointLimit - check the box to enable")

global thermostatClusterServerAttributeAbsMinCoolSetpointLimit
thermostatClusterServerAttributeAbsMinCoolSetpointLimit = drvZigbeeComponent.createBooleanSymbol("TC_ABSMINCOOLSETPOINTLIMIT", thermostatClusterServerAttributes)
thermostatClusterServerAttributeAbsMinCoolSetpointLimit.setLabel("0x0005 AbsMinCoolSetpointLimit")
thermostatClusterServerAttributeAbsMinCoolSetpointLimit.setDefaultValue(True)
thermostatClusterServerAttributeAbsMinCoolSetpointLimit.setDescription("AbsMinCoolSetpointLimit - check the box to enable")

global thermostatClusterServerAttributeAbsMaxCoolSetpointLimit
thermostatClusterServerAttributeAbsMaxCoolSetpointLimit = drvZigbeeComponent.createBooleanSymbol("TC_ABSMAXCOOLSETPOINTLIMIT", thermostatClusterServerAttributes)
thermostatClusterServerAttributeAbsMaxCoolSetpointLimit.setLabel("0x0006 AbsMaxCoolSetpointLimit ")
thermostatClusterServerAttributeAbsMaxCoolSetpointLimit.setDefaultValue(True)
thermostatClusterServerAttributeAbsMaxCoolSetpointLimit.setDescription("AbsMaxCoolSetpointLimit  - check the box to enable")

global thermostatClusterServerAttributePICoolingDemand
thermostatClusterServerAttributePICoolingDemand = drvZigbeeComponent.createBooleanSymbol("TC_PICOOLINGDEMAND", thermostatClusterServerAttributes)
thermostatClusterServerAttributePICoolingDemand.setLabel("0x0007 PICoolingDemand")
thermostatClusterServerAttributePICoolingDemand.setDefaultValue(True)
thermostatClusterServerAttributePICoolingDemand.setDescription("PICoolingDemand - check the box to enable")

global thermostatClusterServerAttributePIHeatingDemand
thermostatClusterServerAttributePIHeatingDemand = drvZigbeeComponent.createBooleanSymbol("TC_PIHEATINGDEMAND", thermostatClusterServerAttributes)
thermostatClusterServerAttributePIHeatingDemand.setLabel("0x0008 PIHeatingDemand")
thermostatClusterServerAttributePIHeatingDemand.setDefaultValue(True)
thermostatClusterServerAttributePIHeatingDemand.setDescription("PIHeatingDemand - check the box to enable")

global thermostatClusterServerAttributeHVACSystemTypeConfiguration
thermostatClusterServerAttributeHVACSystemTypeConfiguration = drvZigbeeComponent.createBooleanSymbol("TC_HVACSYSTEMCONFIG", thermostatClusterServerAttributes)
thermostatClusterServerAttributeHVACSystemTypeConfiguration.setLabel("0x0009 HVACSystemTypeConfiguration")
thermostatClusterServerAttributeHVACSystemTypeConfiguration.setDefaultValue(True)
thermostatClusterServerAttributeHVACSystemTypeConfiguration.setDescription("HVACSystemTypeConfiguration - check the box to enable")

## Thermostat Settings Attribute Set
global thermostatClusterServerAttributeLocalTempCalib
thermostatClusterServerAttributeLocalTempCalib = drvZigbeeComponent.createBooleanSymbol("TC_LOCALTEMPCALIBRATION", thermostatClusterServerAttributes)
thermostatClusterServerAttributeLocalTempCalib.setLabel("0x0010 LocalTemperatureCalibration")
thermostatClusterServerAttributeLocalTempCalib.setDefaultValue(True)
thermostatClusterServerAttributeLocalTempCalib.setDescription("LocalTemperatureCalibration - check the box to enable")

global thermostatClusterServerAttributeOccupiedCoolingSetpoint
thermostatClusterServerAttributeOccupiedCoolingSetpoint = drvZigbeeComponent.createBooleanSymbol("TC_OCCUPIEDCOOLINGSETPOINT", thermostatClusterServerAttributes)
thermostatClusterServerAttributeOccupiedCoolingSetpoint.setLabel("0x0011 OccupiedCoolingSetpoint")
thermostatClusterServerAttributeOccupiedCoolingSetpoint.setDefaultValue(True)
thermostatClusterServerAttributeOccupiedCoolingSetpoint.setDescription("OccupiedCoolingSetpoint - check the box to enable")
thermostatClusterServerAttributeOccupiedCoolingSetpoint.setReadOnly(True)

global thermostatClusterServerAttributeOccupiedHeatingSetpoint
thermostatClusterServerAttributeOccupiedHeatingSetpoint = drvZigbeeComponent.createBooleanSymbol("TC_OCCUPIEDHEATINGSETPOINT", thermostatClusterServerAttributes)
thermostatClusterServerAttributeOccupiedHeatingSetpoint.setLabel("0x0012 OccupiedHeatingSetpoint")
thermostatClusterServerAttributeOccupiedHeatingSetpoint.setDefaultValue(True)
thermostatClusterServerAttributeOccupiedHeatingSetpoint.setDescription("OccupiedHeatingSetpoint - check the box to enable")
thermostatClusterServerAttributeOccupiedHeatingSetpoint.setReadOnly(True)

global thermostatClusterServerAttributeUnoccupiedCoolingSetpoint
thermostatClusterServerAttributeUnoccupiedCoolingSetpoint = drvZigbeeComponent.createBooleanSymbol("TC_UNOCCUPIEDCOOLINGSETPOINT", thermostatClusterServerAttributes)
thermostatClusterServerAttributeUnoccupiedCoolingSetpoint.setLabel("0x0013 UnoccupiedCoolingSetpoint")
thermostatClusterServerAttributeUnoccupiedCoolingSetpoint.setDefaultValue(True)
thermostatClusterServerAttributeUnoccupiedCoolingSetpoint.setDescription("UnoccupiedCoolingSetpoint - check the box to enable")

global thermostatClusterServerAttributeUnoccupiedHeatingSetpoint
thermostatClusterServerAttributeUnoccupiedHeatingSetpoint = drvZigbeeComponent.createBooleanSymbol("TC_UNOCCUPIEDHEATINGSETPOINT", thermostatClusterServerAttributes)
thermostatClusterServerAttributeUnoccupiedHeatingSetpoint.setLabel("0x0014 UnoccupiedHeatingSetpoint")
thermostatClusterServerAttributeUnoccupiedHeatingSetpoint.setDefaultValue(True)
thermostatClusterServerAttributeUnoccupiedHeatingSetpoint.setDescription("UnoccupiedHeatingSetpoint - check the box to enable")

global thermostatClusterServerAttributeMinHeatSetpointLimit
thermostatClusterServerAttributeMinHeatSetpointLimit = drvZigbeeComponent.createBooleanSymbol("TC_MINHEATSETPOINTLIMIT", thermostatClusterServerAttributes)
thermostatClusterServerAttributeMinHeatSetpointLimit.setLabel("0x0015 MinHeatSetpointLimit")
thermostatClusterServerAttributeMinHeatSetpointLimit.setDefaultValue(True)
thermostatClusterServerAttributeMinHeatSetpointLimit.setDescription("MinHeatSetpointLimit  - check the box to enable")

global thermostatClusterServerAttributeMaxHeatSetpointLimit
thermostatClusterServerAttributeMaxHeatSetpointLimit = drvZigbeeComponent.createBooleanSymbol("TC_MAXHEATSETPOINTLIMIT", thermostatClusterServerAttributes)
thermostatClusterServerAttributeMaxHeatSetpointLimit.setLabel("0x0016 MaxHeatSetpointLimit")
thermostatClusterServerAttributeMaxHeatSetpointLimit.setDefaultValue(True)
thermostatClusterServerAttributeMaxHeatSetpointLimit.setDescription("MaxHeatSetpointLimit  - check the box to enable")

global thermostatClusterServerAttributeMinCoolSetpointLimit
thermostatClusterServerAttributeMinCoolSetpointLimit = drvZigbeeComponent.createBooleanSymbol("TC_MINCOOLSETPOINTLIMIT", thermostatClusterServerAttributes)
thermostatClusterServerAttributeMinCoolSetpointLimit.setLabel("0x0017 MinCoolSetpointLimit")
thermostatClusterServerAttributeMinCoolSetpointLimit.setDefaultValue(True)
thermostatClusterServerAttributeMinCoolSetpointLimit.setDescription("MinCoolSetpointLimit - check the box to enable")

global thermostatClusterServerAttributeMaxCoolSetpointLimit
thermostatClusterServerAttributeMaxCoolSetpointLimit = drvZigbeeComponent.createBooleanSymbol("TC_MAXCOOLSETPOINTLIMIT", thermostatClusterServerAttributes)
thermostatClusterServerAttributeMaxCoolSetpointLimit.setLabel("0x0018 MaxCoolSetpointLimit")
thermostatClusterServerAttributeMaxCoolSetpointLimit.setDefaultValue(True)
thermostatClusterServerAttributeMaxCoolSetpointLimit.setDescription("MaxCoolSetpointLimit - check the box to enable")

global thermostatClusterServerAttributeMinSetpointDeadBand
thermostatClusterServerAttributeMinSetpointDeadBand = drvZigbeeComponent.createBooleanSymbol("TC_MINSETPOINTDEADBAND", thermostatClusterServerAttributes)
thermostatClusterServerAttributeMinSetpointDeadBand.setLabel("0x0019 MinSetpointDeadBand")
thermostatClusterServerAttributeMinSetpointDeadBand.setDefaultValue(True)
thermostatClusterServerAttributeMinSetpointDeadBand.setDescription("MinSetpointDeadBand - check the box to enable")

global thermostatClusterServerAttributeRemoteSensing
thermostatClusterServerAttributeRemoteSensing = drvZigbeeComponent.createBooleanSymbol("TC_REMOTESENSING", thermostatClusterServerAttributes)
thermostatClusterServerAttributeRemoteSensing.setLabel("0x001A RemoteSensing")
thermostatClusterServerAttributeRemoteSensing.setDefaultValue(True)
thermostatClusterServerAttributeRemoteSensing.setDescription("RemoteSensing  - check the box to enable")

global thermostatClusterServerAttributeControlSequenceOfOperation
thermostatClusterServerAttributeControlSequenceOfOperation = drvZigbeeComponent.createBooleanSymbol("TC_CONTROLSEQOPERATION", thermostatClusterServerAttributes)
thermostatClusterServerAttributeControlSequenceOfOperation.setLabel("0x001B ControlSequenceOfOperation")
thermostatClusterServerAttributeControlSequenceOfOperation.setDefaultValue(True)
thermostatClusterServerAttributeControlSequenceOfOperation.setDescription("ControlSequenceOfOperation - check the box to enable")
thermostatClusterServerAttributeControlSequenceOfOperation.setReadOnly(True)

global thermostatClusterServerAttributeSystemMode
thermostatClusterServerAttributeSystemMode = drvZigbeeComponent.createBooleanSymbol("TC_SYSTEMMODE", thermostatClusterServerAttributes)
thermostatClusterServerAttributeSystemMode.setLabel("0x001C SystemMode")
thermostatClusterServerAttributeSystemMode.setDefaultValue(True)
thermostatClusterServerAttributeSystemMode.setDescription("SystemMode - check the box to enable")
thermostatClusterServerAttributeSystemMode.setReadOnly(True)

global thermostatClusterServerAttributeAlarmMask
thermostatClusterServerAttributeAlarmMask = drvZigbeeComponent.createBooleanSymbol("TC_ALARMMASK", thermostatClusterServerAttributes)
thermostatClusterServerAttributeAlarmMask.setLabel("0x001D AlarmMask")
thermostatClusterServerAttributeAlarmMask.setDefaultValue(True)
thermostatClusterServerAttributeAlarmMask.setDescription("AlarmMask - check the box to enable")

global thermostatClusterServerAttributeThermostatRunningMode
thermostatClusterServerAttributeThermostatRunningMode  = drvZigbeeComponent.createBooleanSymbol("TC_THERMOSTATRUNNINGMODE", thermostatClusterServerAttributes)
thermostatClusterServerAttributeThermostatRunningMode.setLabel("0x001E ThermostatRunningMode")
thermostatClusterServerAttributeThermostatRunningMode.setDefaultValue(True)
thermostatClusterServerAttributeThermostatRunningMode.setDescription("ThermostatRunningMode - check the box to enable")

# ## Thermostat Schedule & HVAC Relay Attribute Set
# thermostatClusterServerAttributeStartOfWeek  = drvZigbeeComponent.createBooleanSymbol("TC_STARTOFWEEK", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeStartOfWeek.setLabel("0x0020 StartOfWeek")
# thermostatClusterServerAttributeStartOfWeek.setDefaultValue(True)
# thermostatClusterServerAttributeStartOfWeek.setDescription("StartOfWeek - check the box to enable")

# thermostatClusterServerAttributeNumberOfWeeklyTransitions  = drvZigbeeComponent.createBooleanSymbol("TC_NUMOFWEEKLYTRANSITIONS", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeNumberOfWeeklyTransitions.setLabel("0x0021 NumberOfWeeklyTransitions")
# thermostatClusterServerAttributeNumberOfWeeklyTransitions.setDefaultValue(True)
# thermostatClusterServerAttributeNumberOfWeeklyTransitions.setDescription("NumberOfWeeklyTransitions - check the box to enable")

# thermostatClusterServerAttributeNumberOfDailyTransitions  = drvZigbeeComponent.createBooleanSymbol("TC_NUMOFFDAILYTRANSITIONS", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeNumberOfDailyTransitions.setLabel("0x0022 NumberOfDailyTransitions")
# thermostatClusterServerAttributeNumberOfDailyTransitions.setDefaultValue(True)
# thermostatClusterServerAttributeNumberOfDailyTransitions.setDescription("NumberOfDailyTransitions - check the box to enable")

# thermostatClusterServerAttributeTemperatureSetpointHold  = drvZigbeeComponent.createBooleanSymbol("TC_TEMPSETPOINTHOLD", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeTemperatureSetpointHold.setLabel("0x0023 TemperatureSetpointHold")
# thermostatClusterServerAttributeTemperatureSetpointHold.setDefaultValue(True)
# thermostatClusterServerAttributeTemperatureSetpointHold.setDescription("TemperatureSetpointHold - check the box to enable")

# thermostatClusterServerAttributeTemperatureSetpointHoldDuration  = drvZigbeeComponent.createBooleanSymbol("TC_TEMPSETPOINTHOLDDURATION", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeTemperatureSetpointHoldDuration.setLabel("0x0024 TemperatureSetpointHoldDuration")
# thermostatClusterServerAttributeTemperatureSetpointHoldDuration.setDefaultValue(True)
# thermostatClusterServerAttributeTemperatureSetpointHoldDuration.setDescription("TemperatureSetpointHoldDuration - check the box to enable")

# thermostatClusterServerAttributeThermostatProgrammingOpMode  = drvZigbeeComponent.createBooleanSymbol("TC_THERMOSTATPROOPMODE", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeThermostatProgrammingOpMode.setLabel("0x0025 ThermostatProgrammingOperationMode")
# thermostatClusterServerAttributeThermostatProgrammingOpMode.setDefaultValue(True)
# thermostatClusterServerAttributeThermostatProgrammingOpMode.setDescription("ThermostatProgrammingOperationMode - check the box to enable")

# thermostatClusterServerAttributeThermostatRunningState = drvZigbeeComponent.createBooleanSymbol("TC_THERMOSTATRUNNINGSTATE", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeThermostatRunningState.setLabel("0x0026 ThermostatRunningState")
# thermostatClusterServerAttributeThermostatRunningState.setDefaultValue(True)
# thermostatClusterServerAttributeThermostatRunningState.setDescription("ThermostatRunningState - check the box to enable")

# ## Thermostat Setpoint Change Tracking Attribute Set
# thermostatClusterServerAttributeSetpointChangeSource = drvZigbeeComponent.createBooleanSymbol("TC_SETPOINTCHANGESOURCE", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeSetpointChangeSource.setLabel("0x0030 SetpointChangeSource")
# thermostatClusterServerAttributeSetpointChangeSource.setDefaultValue(True)
# thermostatClusterServerAttributeSetpointChangeSource.setDescription("SetpointChangeSource - check the box to enable")

# thermostatClusterServerAttributeSetpointChangeAmount = drvZigbeeComponent.createBooleanSymbol("TC_SETPOINTCHANGEAMOUNT", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeSetpointChangeAmount.setLabel("0x0031 SetpointChangeAmount")
# thermostatClusterServerAttributeSetpointChangeAmount.setDefaultValue(True)
# thermostatClusterServerAttributeSetpointChangeAmount.setDescription("SetpointChangeAmount - check the box to enable")

# thermostatClusterServerAttributeSetpointChangeSourceTimestamp = drvZigbeeComponent.createBooleanSymbol("TC_SETPOINTSOURCETIMESTAMP", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeSetpointChangeSourceTimestamp.setLabel("0x0032 SetpointChangeSourceTimestamp")
# thermostatClusterServerAttributeSetpointChangeSourceTimestamp.setDefaultValue(True)
# thermostatClusterServerAttributeSetpointChangeSourceTimestamp.setDescription("SetpointChangeSourceTimestamp - check the box to enable")

# thermostatClusterServerAttributeOccupiedSetback = drvZigbeeComponent.createBooleanSymbol("TC_OOCUPIEDSETBACK", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeOccupiedSetback.setLabel("0x0034 OccupiedSetback")
# thermostatClusterServerAttributeOccupiedSetback.setDefaultValue(True)
# thermostatClusterServerAttributeOccupiedSetback.setDescription("OccupiedSetback - check the box to enable")

# thermostatClusterServerAttributeOccupiedSetbackMin = drvZigbeeComponent.createBooleanSymbol("TC_OCCUPIEDSETBACKMIN", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeOccupiedSetbackMin.setLabel("0x0035 OccupiedSetbackMin")
# thermostatClusterServerAttributeOccupiedSetbackMin.setDefaultValue(True)
# thermostatClusterServerAttributeOccupiedSetbackMin.setDescription("OccupiedSetbackMin - check the box to enable")

# thermostatClusterServerAttributeOccupiedSetbackMax = drvZigbeeComponent.createBooleanSymbol("TC_OCCUPIEDSETBACKMAX", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeOccupiedSetbackMax.setLabel("0x0036 OccupiedSetbackMax")
# thermostatClusterServerAttributeOccupiedSetbackMax.setDefaultValue(True)
# thermostatClusterServerAttributeOccupiedSetbackMax.setDescription("OccupiedSetbackMax - check the box to enable")

# thermostatClusterServerAttributeUnOccupiedSetback = drvZigbeeComponent.createBooleanSymbol("TC_UNOCCUPIEDSETBACK", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeUnOccupiedSetback.setLabel("0x0037 UnoccupiedSetback")
# thermostatClusterServerAttributeUnOccupiedSetback.setDefaultValue(True)
# thermostatClusterServerAttributeUnOccupiedSetback.setDescription("UnoccupiedSetback - check the box to enable")

# thermostatClusterServerAttributeUnoccupiedSetbackMin = drvZigbeeComponent.createBooleanSymbol("TC_UNOCCUPIEDSETBACKMIN", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeUnoccupiedSetbackMin.setLabel("0x0038 UnoccupiedSetbackMin")
# thermostatClusterServerAttributeUnoccupiedSetbackMin.setDefaultValue(True)
# thermostatClusterServerAttributeUnoccupiedSetbackMin.setDescription("UnoccupiedSetbackMin - check the box to enable")

# thermostatClusterServerAttributeUnoccupiedSetbackMax = drvZigbeeComponent.createBooleanSymbol("TC_UNOCCUPIEDSETBACKMAX", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeUnoccupiedSetbackMax.setLabel("0x0039 UnoccupiedSetbackMax")
# thermostatClusterServerAttributeUnoccupiedSetbackMax.setDefaultValue(True)
# thermostatClusterServerAttributeUnoccupiedSetbackMax.setDescription("UnoccupiedSetbackMax - check the box to enable")

# thermostatClusterServerAttributeEmergencyHeatDelta = drvZigbeeComponent.createBooleanSymbol("TC_EMERGENCYHEATDELTA", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeEmergencyHeatDelta.setLabel("0x003A EmergencyHeatDelta")
# thermostatClusterServerAttributeEmergencyHeatDelta.setDefaultValue(True)
# thermostatClusterServerAttributeEmergencyHeatDelta.setDescription("EmergencyHeatDelta - check the box to enable")

# ## AC Information Attribute Set
# thermostatClusterServerAttributeACType = drvZigbeeComponent.createBooleanSymbol("TC_ACTYPE", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeACType.setLabel("0x0040 ACType")
# thermostatClusterServerAttributeACType.setDefaultValue(True)
# thermostatClusterServerAttributeACType.setDescription("ACType - check the box to enable")

# thermostatClusterServerAttributeACCapacity = drvZigbeeComponent.createBooleanSymbol("TC_ACCAPACITY", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeACCapacity.setLabel("0x0041 ACCapacity")
# thermostatClusterServerAttributeACCapacity.setDefaultValue(True)
# thermostatClusterServerAttributeACCapacity.setDescription("ACCapacity - check the box to enable")

# thermostatClusterServerAttributeACRefrigerantType = drvZigbeeComponent.createBooleanSymbol("TC_ACREFRIGENTTYPE", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeACRefrigerantType.setLabel("0x0042 ACRefrigerantType")
# thermostatClusterServerAttributeACRefrigerantType.setDefaultValue(True)
# thermostatClusterServerAttributeACRefrigerantType.setDescription("ACRefrigerantType - check the box to enable")

# thermostatClusterServerAttributeACCompressorType = drvZigbeeComponent.createBooleanSymbol("TC_ACCOMPRESSORTYPE", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeACCompressorType.setLabel("0x0043 ACCompressorType")
# thermostatClusterServerAttributeACCompressorType.setDefaultValue(True)
# thermostatClusterServerAttributeACCompressorType.setDescription("ACCompressorType - check the box to enable")

# thermostatClusterServerAttributeACErrorCode = drvZigbeeComponent.createBooleanSymbol("TC_ACERRORCODE", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeACErrorCode.setLabel("0x0044 ACErrorCode")
# thermostatClusterServerAttributeACErrorCode.setDefaultValue(True)
# thermostatClusterServerAttributeACErrorCode.setDescription("ACErrorCode - check the box to enable")

# thermostatClusterServerAttributeACLouverPosition = drvZigbeeComponent.createBooleanSymbol("TC_ACLOUVERPOSITION", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeACLouverPosition.setLabel("0x0045 ACLouverPosition")
# thermostatClusterServerAttributeACLouverPosition.setDefaultValue(True)
# thermostatClusterServerAttributeACLouverPosition.setDescription("ACLouverPosition - check the box to enable")

# thermostatClusterServerAttributeACCoilTemperature = drvZigbeeComponent.createBooleanSymbol("TC_ACCOILTEMP", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeACCoilTemperature.setLabel("0x0046 ACCoilTemperature")
# thermostatClusterServerAttributeACCoilTemperature.setDefaultValue(True)
# thermostatClusterServerAttributeACCoilTemperature.setDescription("ACCoilTemperature - check the box to enable")

# thermostatClusterServerAttributeACCapacityFormat = drvZigbeeComponent.createBooleanSymbol("TC_ACCAPACITYFORMAT", thermostatClusterServerAttributes)
# thermostatClusterServerAttributeACCapacityFormat.setLabel("0x0047 ACCapacityFormat")
# thermostatClusterServerAttributeACCapacityFormat.setDefaultValue(True)
# thermostatClusterServerAttributeACCapacityFormat.setDescription("ACCapacityFormat - check the box to enable")


## Global attributes
global thermostatClusterServerAttributeClusterRevision
thermostatClusterServerAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("THC_CLUSTERREVISION", thermostatClusterServerAttributes)
thermostatClusterServerAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
thermostatClusterServerAttributeClusterRevision.setDefaultValue(True)
thermostatClusterServerAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
thermostatClusterServerAttributeClusterRevision.setReadOnly(True)

global thermostatClusterServerAttributeCount
thermostatClusterServerAttributeCount = drvZigbeeComponent.createIntegerSymbol("THC_SERVERATTRIBUTECOUNT", thermostatClusterServerAttributes)
thermostatClusterServerAttributeCount.setLabel("Attributes Count")
thermostatClusterServerAttributeCount.setDefaultValue(thermostatClusterServerAttributeCountUpdate(0,0))
thermostatClusterServerAttributeCount.setVisible(True)
thermostatClusterServerAttributeCount.setDescription("Attributes Count")
thermostatClusterServerAttributeCount.setReadOnly(True)
thermostatClusterServerAttributeCount.setDependencies(thermostatClusterServerAttributeCountUpdate,["THC_CLUSTERREVISION","TC_THERMOSTATRUNNINGMODE","TC_ALARMMASK","TC_SYSTEMMODE","TC_CONTROLSEQOPERATION","TC_REMOTESENSING","TC_MINSETPOINTDEADBAND","TC_MAXCOOLSETPOINTLIMIT","TC_MINCOOLSETPOINTLIMIT","TC_MAXHEATSETPOINTLIMIT","TC_MINHEATSETPOINTLIMIT","TC_UNOCCUPIEDCOOLINGSETPOINT","TC_OCCUPIEDHEATINGSETPOINT","TC_OCCUPIEDCOOLINGSETPOINT","TC_LOCALTEMPCALIBRATION","TC_HVACSYSTEMCONFIG","TC_PIHEATINGDEMAND","TC_PICOOLINGDEMAND","TC_ABSMAXCOOLSETPOINTLIMIT","TC_ABSMINCOOLSETPOINTLIMIT","TC_ABSMAXHEATSETPOINTLIMIT","TC_ABSMINHEATSETPOINTLIMIT","TC_OCCUPANCY","TC_OUTDOORTEMP","TC_LOCALTEMP"])


#################               Server Commands                                 ###############

# Commands received
global thermostatClusterServerCommandSetPointRaiseLower
thermostatClusterServerCommandSetPointRaiseLower = drvZigbeeComponent.createBooleanSymbol("THC_SETPOINTRAISELOWER", thermostatClusterServerCommands)
thermostatClusterServerCommandSetPointRaiseLower.setLabel("0x00.Rx Setpoint Raise/Lower")
thermostatClusterServerCommandSetPointRaiseLower.setDefaultValue(True)
thermostatClusterServerCommandSetPointRaiseLower.setDescription("Receive Setpoint Raise/Lower - check the box to enable")
thermostatClusterServerCommandSetPointRaiseLower.setReadOnly(True)

# thermostatClusterServerCommandSetWeeklySchedule = drvZigbeeComponent.createBooleanSymbol("THC_SETWEEKLYSCHEDULE", thermostatClusterServerCommands)
# thermostatClusterServerCommandSetWeeklySchedule.setLabel("0x01.Rx Set Weekly Schedule")
# thermostatClusterServerCommandSetWeeklySchedule.setDefaultValue(True)
# thermostatClusterServerCommandSetWeeklySchedule.setDescription("Receive Set Weekly Schedule - check the box to enable")

# thermostatClusterServerCommandGetWeeklySchedule = drvZigbeeComponent.createBooleanSymbol("THC_GETWEEKLYSCHEDULE", thermostatClusterServerCommands)
# thermostatClusterServerCommandGetWeeklySchedule.setLabel("0x02.Rx Get Weekly Schedule")
# thermostatClusterServerCommandGetWeeklySchedule.setDefaultValue(True)
# thermostatClusterServerCommandGetWeeklySchedule.setDescription("Receive Get Weekly Schedule - check the box to enable")

# thermostatClusterServerCommandGetWeeklySchedule = drvZigbeeComponent.createBooleanSymbol("THC_CLEARWEEKLYSCHEDULE", thermostatClusterServerCommands)
# thermostatClusterServerCommandGetWeeklySchedule.setLabel("0x03.Rx Clear Weekly Schedule")
# thermostatClusterServerCommandGetWeeklySchedule.setDefaultValue(True)
# thermostatClusterServerCommandGetWeeklySchedule.setDescription("Receive Clear Weekly Schedule - check the box to enable")

# thermostatClusterServerCommandGetRelayStatusLog = drvZigbeeComponent.createBooleanSymbol("THC_GETRELAYSTATUSLOG", thermostatClusterServerCommands)
# thermostatClusterServerCommandGetRelayStatusLog.setLabel("0x04.Rx Get Relay Status Log")
# thermostatClusterServerCommandGetRelayStatusLog.setDefaultValue(True)
# thermostatClusterServerCommandGetRelayStatusLog.setDescription("Receive Get Relay Status Log - check the box to enable")

# Commands generated
# thermostatClusterServerCommandGetWeeklyScheduleResp = drvZigbeeComponent.createBooleanSymbol("THC_GETWEEKLYSCHEDULERESP", thermostatClusterServerCommands)
# thermostatClusterServerCommandGetWeeklyScheduleResp.setLabel("0x00.Tx Get Weekly Schedule Response")
# thermostatClusterServerCommandGetWeeklyScheduleResp.setDefaultValue(True)
# thermostatClusterServerCommandGetWeeklyScheduleResp.setDescription("Receive Get Weekly Schedule Response - check the box to enable")
# #thermostatClusterServerCommandGetWeeklyScheduleResp.setReadOnly(True)

# thermostatClusterServerCommandGetRelayStatusLogResp = drvZigbeeComponent.createBooleanSymbol("THC_GETRELAYSTATUSLOGRESP", thermostatClusterServerCommands)
# thermostatClusterServerCommandGetRelayStatusLogResp.setLabel("0x01.Tx Get Relay Status Log Response")
# thermostatClusterServerCommandGetRelayStatusLogResp.setDefaultValue(True)
# thermostatClusterServerCommandGetRelayStatusLogResp.setDescription("Receive Get Relay Status Log Response - check the box to enable")
# #thermostatClusterServerCommandGetRelayStatusLogResp.setReadOnly(True)

global thermostatClusterServerCommandCount
thermostatClusterServerCommandCount = drvZigbeeComponent.createIntegerSymbol("THC_SERVERCOMMANDCOUNT", thermostatClusterServerCommands)
thermostatClusterServerCommandCount.setLabel("Commands Count")
thermostatClusterServerCommandCount.setDefaultValue(thermostatClusterServerCommandCountUpdate(0,0))
thermostatClusterServerCommandCount.setVisible(True)
thermostatClusterServerCommandCount.setDescription("Commands Count")
thermostatClusterServerCommandCount.setReadOnly(True)
thermostatClusterServerCommandCount.setDependencies(thermostatClusterServerCommandCountUpdate, ["THC_SETPOINTRAISELOWER"])

#################               Client Attributes                                 ###############
global thermostatClusterClientAttributeClusterRevision
thermostatClusterClientAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("THCC_CLUSTERREVISION", thermostatClusterClientAttributes)
thermostatClusterClientAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
thermostatClusterClientAttributeClusterRevision.setDefaultValue(True)
thermostatClusterClientAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
thermostatClusterClientAttributeClusterRevision.setReadOnly(True)

global thermostatClusterClientAttributeCount
thermostatClusterClientAttributeCount = drvZigbeeComponent.createIntegerSymbol("THCC_CLIENTATTRIBUTECOUNT", thermostatClusterClientAttributes)
thermostatClusterClientAttributeCount.setLabel("Attributes Count")
thermostatClusterClientAttributeCount.setDefaultValue(thermostatClusterClientAttributeCountUpdate(0,0))
thermostatClusterClientAttributeCount.setVisible(True)
thermostatClusterClientAttributeCount.setDescription("Attributes Count")
thermostatClusterClientAttributeCount.setReadOnly(True)
thermostatClusterClientAttributeCount.setDependencies(thermostatClusterClientAttributeCountUpdate,["THCC_CLUSTERREVISION"])

#################               Client Commands                                 ###############

# Commands generated
# There are no client Specific commands generated

# Commands received
# There are no client Specific commands received


############################################################################################################
# Default Values Settings based on device type
thermostatClusterHandling()

############################################################################################################
##################################### FTL Files Definitions ################################################
############################################################################################################

# THERMOSTAT CLUSTER Common header
thermostatClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_THERMOSTAT_CLUSTER_CONF", None)
thermostatClusterConf.setSourcePath("/driver/zigbee/templates/cluster/thermostat/zclThermostatCluster.h.ftl")
thermostatClusterConf.setOutputName("zclThermostatCluster.h")
thermostatClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
thermostatClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
thermostatClusterConf.setType("HEADER")
thermostatClusterConf.setOverwrite(True)
thermostatClusterConf.setMarkup(True)

# THERMOSTAT CLUSTER - Combined Interface
thermostatClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_THERMOSTAT_CLUSTER_CONF_SRC_CI", None)
thermostatClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/thermostat/ciThermostatCluster.c.ftl")
thermostatClusterConfSrc.setOutputName("ciThermostatCluster.c")
thermostatClusterConfSrc.setDestPath("/zigbee/z3device/combinedInterface")
thermostatClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/combinedInterface/")
thermostatClusterConfSrc.setType("SOURCE")
thermostatClusterConfSrc.setOverwrite(True)
thermostatClusterConfSrc.setMarkup(True)
thermostatClusterConfSrc.setEnabled(checkDevTypeCombInterface)

# THERMOSTAT CLUSTER - Thermostat
thermostatClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_THERMOSTAT_CLUSTER_CONF_SRC_THPDT", None)
thermostatClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/thermostat/thPdt.c.ftl")
thermostatClusterConfSrc.setOutputName("thPdt.c")
thermostatClusterConfSrc.setDestPath("/zigbee/z3device/thermostat")
thermostatClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/thermostat/")
thermostatClusterConfSrc.setType("SOURCE")
thermostatClusterConfSrc.setOverwrite(True)
thermostatClusterConfSrc.setMarkup(True)
thermostatClusterConfSrc.setEnabled(checkDevTypeThermostat)

thermostatClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_THERMOSTAT_CLUSTER_CONF_SRC_TH", None)
thermostatClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/thermostat/thThermostatCluster.c.ftl")
thermostatClusterConfSrc.setOutputName("thThermostatCluster.c")
thermostatClusterConfSrc.setDestPath("/zigbee/z3device/thermostat")
thermostatClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/thermostat/")
thermostatClusterConfSrc.setType("SOURCE")
thermostatClusterConfSrc.setOverwrite(True)
thermostatClusterConfSrc.setMarkup(True)
thermostatClusterConfSrc.setEnabled(checkDevTypeThermostat)

thermostatClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_THERMOSTAT_CLUSTER_CONF_SRC_CUSTOM", None)
thermostatClusterConfSrc.setSourcePath("/driver/zigbee/templates/cluster/thermostat/customThermostatCluster.c.ftl")
thermostatClusterConfSrc.setOutputName("customThermostatCluster.c")
thermostatClusterConfSrc.setDestPath("/zigbee/z3device/custom")
thermostatClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/custom/")
thermostatClusterConfSrc.setType("SOURCE")
thermostatClusterConfSrc.setOverwrite(True)
thermostatClusterConfSrc.setMarkup(True)
thermostatClusterConfSrc.setEnabled(checkDevTypeCustom and thermostatCluster.getValue())
thermostatClusterConfSrc.setDependencies(customThermostatClusterEnabledCheck,["THERMOSTAT_CLUSTER_ENABLE"])
############################################################################################################
