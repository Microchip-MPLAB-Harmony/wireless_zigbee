/*******************************************************************************
  Custom Thermostat Cluster Source file

  Company:
    Microchip Technology Inc.

  File Name:
    customThermostatCluster.c

  Summary:
    This file contains Custom Thermstat Cluster Implementation.

  Description:
    This file contains Custom Thermostat Cluster Implementation.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
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
*******************************************************************************/
// DOM-IGNORE-END

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_CUSTOM_DEVICE)

/******************************************************************************
                    Includes section
******************************************************************************/
#include <z3device/custom/include/customThermostatCluster.h>
#if APP_ENABLE_CONSOLE == 1

#endif
#include <z3device/custom/include/customAlarmsCluster.h>
#include <z3device/clusters/include/haClusters.h>
#include <zcl/include/zclCommandManager.h>
#include <zcl/include/zclAttributes.h>
#include <pds/include/wlPdsMemIds.h>
#include <z3device/common/include/appConsts.h>
#include <app_zigbee/zigbee_console/console.h>
#include <z3device/common/include/z3Device.h>
/*******************************************************************************
                             Defines section
*******************************************************************************/
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")>
#define THERMOSTAT_SETPOINT_SCALE 10

#if THERMOSTAT_LOCAL_TEMPERATURE_MAX_REPORT_PERIOD > 2
#define TEMP_MEAS_TIME  ((THERMOSTAT_LOCAL_TEMPERATURE_MAX_REPORT_PERIOD/2) - 1)*1000
#else
#define TEMP_MEAS_TIME 1000
#endif
</#if>
/*******************************************************************************
                             Types section
*******************************************************************************/

/*******************************************************************************
                    Static functions prototypes section
*******************************************************************************/
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")>
static ZCL_Status_t setpointCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_SetpointRaiseLower_t * payload);
static void readTemperature(void);
static void thermostatSettingsAttrInit(void);
static void thermostatInformationAttrInit(void);
static void customThermostatEventListener(SYS_EventId_t eventId, SYS_EventData_t data);
#if defined(THERMOSTAT_EXTERNAL_TEMPERATURE_SENSOR_NODE_AVAILABLE) && defined (ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES)
  static void thermostatReadExternalTempSensor(int16_t *pTemperature);
#endif
static ZCL_Status_t thermostatValidateSystemModeValue(ZCL_ThControlSeqOfOperation_t ctrlSeqOperation,ZCL_ThSystemMode_t sysModeValue);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "SERVER")>
static void customThermostatReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload);
</#if>
static void customThermostatAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);

/******************************************************************************
                    Global variables
******************************************************************************/
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")>
ZCL_ThermostatClusterServerAttributes_t customThermostatClusterServerAttributes =
{
  ZCL_DEFINE_THERMOSTAT_CLUSTER_SERVER_MANDATORY_ATTRIBUTES(0, 0)
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES    
  ZCL_DEFINE_THERMOSTAT_CLUSTER_SERVER_OPTIONAL_ATTRIBUTES(0, 0)
#endif    
};

extern ZCL_AlarmEntry_t customAlarmTable[];

PROGMEM_DECLARE (ZCL_ThermostatClusterCommands_t customThermostatClusterServerCommands) =
{
  ZCL_DEFINE_THERMOSTAT_CLUSTER_COMMANDS(setpointCommandInd)
};

</#if>

<#if (THERMOSTAT_CLUSTER_CS != "SERVER")>
ZCL_ThermostatClusterClientAttributes_t customThermostatClusterClientAttributes =
{  
  ZCL_DEFINE_THERMOSTAT_MEASUREMENT_CLUSTER_CLIENT_ATTRIBUTES()
};

</#if>

//###########################################################################

<#if DEVICE_DEEP_SLEEP_ENABLED>
<#if ((THERMOSTAT_CLUSTER_ENABLE == true) && ((THERMOSTAT_CLUSTER_CS != "CLIENT") || (THERMOSTAT_CLUSTER_CS == "BOTH")))>
ZCL_ThermostatClusterServerAttributes_t __attribute__((persistent)) backupCstmThermostatClusterServerAttributes;
</#if>
</#if>


/******************************************************************************
                    Local variables
******************************************************************************/
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")>
static HAL_AppTimer_t tempMeasTimer;
static uint8_t customActiveAlarms = 0;

/* BitCloud events receiver */
static SYS_EventReceiver_t customEventReceiver = { .func = customThermostatEventListener};
</#if>

/******************************************************************************
                    Implementation section
******************************************************************************/

/**************************************************************************//**
\brief Initializes thermostat cluster atttributes to their defaults,
        register events and required timers
\param NA
******************************************************************************/
void customThermostatClusterInit(void)
{
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")>
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, THERMOSTAT_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "SERVER")>
  ZCL_Cluster_t *clientCluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, THERMOSTAT_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")>
  if (cluster)
  {
    cluster->ZCL_AttributeEventInd = customThermostatAttrEventInd;
  }
<#else>
  if (clientCluster)
  {
    clientCluster->ZCL_AttributeEventInd = customThermostatAttrEventInd;
  }
</#if>

<#if (THERMOSTAT_CLUSTER_CS != "SERVER")>
  if (clientCluster)
  {
    clientCluster->ZCL_ReportInd = customThermostatReportInd;
  }
 </#if>
 <#if (THERMOSTAT_CLUSTER_CS != "CLIENT")>
  thermostatClusterInitAttributes();
  TEMP_SENSOR_OPEN();
<#if (THERMOSTAT_CLUSTER_CS != "SERVER")  && (THCC_CLUSTERREVISION == true)>
  customThermostatClusterClientAttributes.clusterVersion.value = THERMOSTAT_CLUSTER_VERSION;
</#if>
  /*Start periodic temperature measurement - this period shall always be less
  than reporting period*/
  tempMeasTimer.interval = TEMP_MEAS_TIME;
  tempMeasTimer.mode = TIMER_REPEAT_MODE;
  tempMeasTimer.callback = readTemperature;
  HAL_StopAppTimer(&tempMeasTimer);
  HAL_StartAppTimer(&tempMeasTimer);
  SYS_SubscribeToEvent(BC_ZCL_EVENT_ACTION_REQUEST, &customEventReceiver);
</#if>
}

<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")>
/**************************************************************************//**
\brief Initializes thermostat cluster atttributes to their defaults
\param NA
******************************************************************************/
 void thermostatClusterInitAttributes(void)
 {
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (THC_CLUSTERREVISION == true)>
  customThermostatClusterServerAttributes.clusterVersion.value = THERMOSTAT_CLUSTER_VERSION;
</#if>
  thermostatInformationAttrInit();
  thermostatSettingsAttrInit();
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_THERMOSTATRUNNINGMODE == true)>
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES  
  customThermostatClusterServerAttributes.thermostatRunningState.value = CCPU_TO_LE16(ZCL_TH_RUNNING_STATE_DEF);
#endif
</#if>
 }
/**************************************************************************//**
\brief Initializes the thermostat information attributes to their defaults
\param NA
******************************************************************************/
static void thermostatInformationAttrInit(void)
{
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_LOCALTEMP == true)>
  customThermostatClusterServerAttributes.localTemperature.value =
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_LOCAL_TEMPERATURE_DEF);
  customThermostatClusterServerAttributes.localTemperature.minReportInterval = 
      THERMOSTAT_LOCAL_TEMPERATURE_MIN_REPORT_PERIOD;
  customThermostatClusterServerAttributes.localTemperature.maxReportInterval = 
      THERMOSTAT_LOCAL_TEMPERATURE_MAX_REPORT_PERIOD;
</#if>
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_OUTDOORTEMP == true)>
  customThermostatClusterServerAttributes.outdoorTemperature.value =
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_LOCAL_TEMPERATURE_DEF);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_OCCUPANCY == true)>
  customThermostatClusterServerAttributes.occupancy.value.occupied = CCPU_TO_LE16(ZCL_NOT_OCCUPIED);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_ABSMINHEATSETPOINTLIMIT == true)>
  customThermostatClusterServerAttributes.absMinHeatSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_ABS_MIN_HEAT_SP_LIMIT_DEF);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_ABSMAXHEATSETPOINTLIMIT == true)>
  customThermostatClusterServerAttributes.absMaxHeatSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_ABS_MAX_HEAT_SP_LIMIT_DEF);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_ABSMINCOOLSETPOINTLIMIT == true)>
  customThermostatClusterServerAttributes.absMinCoolSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_ABS_MIN_COOL_SP_LIMIT_DEF);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_ABSMAXCOOLSETPOINTLIMIT == true)>
  customThermostatClusterServerAttributes.absMaxCoolSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_ABS_MAX_COOL_SP_LIMIT_DEF);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_PICOOLINGDEMAND == true)>
  customThermostatClusterServerAttributes.PICoolingDemand.value =
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_PI_COOLING_DEMAND_DEF);
  customThermostatClusterServerAttributes.PICoolingDemand.maxReportInterval =
      THERMOSTAT_PI_CO0LING_DEMAND_MIN_REPORT_PERIOD;
  customThermostatClusterServerAttributes.PICoolingDemand.minReportInterval =
      THERMOSTAT_PI_CO0LING_DEMAND_MAX_REPORT_PERIOD;
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_PIHEATINGDEMAND == true)>
  customThermostatClusterServerAttributes.PIHeatingDemand.value =
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_PI_HEATING_DEMAND_DEF);
  customThermostatClusterServerAttributes.PIHeatingDemand.minReportInterval =
      THERMOSTAT_PI_HEATING_DEMAND_MIN_REPORT_PERIOD;
  customThermostatClusterServerAttributes.PIHeatingDemand.maxReportInterval = 
      THERMOSTAT_PI_HEATING_DEMAND_MAX_REPORT_PERIOD;
  /*hvacSystemTypeConfiguration*/
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_HVACSYSTEMCONFIG == true)>
  customThermostatClusterServerAttributes.hvacSystemTypeConfiguration.value.coolingStage = 
      (uint8_t)CCPU_TO_LE16(ZCL_HVAC_COOL_STAGE_1);
  customThermostatClusterServerAttributes.hvacSystemTypeConfiguration.value.heatingStage = 
      (uint8_t)CCPU_TO_LE16(ZCL_HVAC_HEAT_STAGE_1);
  customThermostatClusterServerAttributes.hvacSystemTypeConfiguration.value.heatingType = 
      (uint8_t)CCPU_TO_LE16(ZCL_HVAC_TYPE_CONVENTIONAL);
  customThermostatClusterServerAttributes.hvacSystemTypeConfiguration.value.heatingFuelSource = 
      (uint8_t)CCPU_TO_LE16(ZCL_HVAC_SOURCE_ELECTRIC);
</#if>
#endif
}

/**************************************************************************//**
\brief Initializes the thermostat settings attributes to their defaults

\param NA
******************************************************************************/
static void thermostatSettingsAttrInit(void)
{
    ZCL_Cluster_t *clientCluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, THERMOSTAT_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_LOCALTEMPCALIBRATION == true)>
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES  
  customThermostatClusterServerAttributes.localTemperatureCalibration.value = 
      CCPU_TO_LE16(ZCL_TH_LOCAL_TEMP_CALIB_DEF);
#endif
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_OCCUPIEDCOOLINGSETPOINT == true)>
  customThermostatClusterServerAttributes.occupiedCoolingSetpoint.value =
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_OCCUPIED_COOLING_SP_DEF);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_OCCUPIEDHEATINGSETPOINT == true)>
  customThermostatClusterServerAttributes.occupiedHeatingSetpoint.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_OCCUPIED_HEATING_SP_DEF);
</#if>
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_UNOCCUPIEDCOOLINGSETPOINT == true)>
  customThermostatClusterServerAttributes.unOccupiedCoolingSetpoint.value =
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_UNOCCUPIED_COOLING_SP_DEF);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_UNOCCUPIEDHEATINGSETPOINT == true)>
  customThermostatClusterServerAttributes.unOccupiedHeatingSetpoint.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_UNOCCUPIED_HEATING_SP_DEF);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_MINHEATSETPOINTLIMIT == true)>
  customThermostatClusterServerAttributes.minHeatSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_MIN_HEAT_SP_LIMIT_DEF);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_MAXHEATSETPOINTLIMIT == true)>
  customThermostatClusterServerAttributes.maxHeatSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_MAX_HEAT_SP_LIMIT_DEF);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_MINCOOLSETPOINTLIMIT == true)>
  customThermostatClusterServerAttributes.minCoolSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_MIN_COOL_SP_LIMIT_DEF);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_MAXCOOLSETPOINTLIMIT == true)>
  customThermostatClusterServerAttributes.maxCoolSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_MAX_COOL_SP_LIMIT_DEF);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_MINSETPOINTDEADBAND == true)>
  customThermostatClusterServerAttributes.minSetpointDeadBand.value = 
      (int8_t)CCPU_TO_LE16(ZCL_TH_MIN_SP_DEADBABD_DEF);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_REMOTESENSING == true)>
  /*remoteSensing*/
  if(clientCluster)
  customThermostatClusterServerAttributes.remoteSensing.value.localTemperature = 
      CCPU_TO_LE16(ZCL_SENSE_EXTERNALLY);
  else
  customThermostatClusterServerAttributes.remoteSensing.value.localTemperature = 
      CCPU_TO_LE16(ZCL_SENSE_INTERNALLY);
  customThermostatClusterServerAttributes.remoteSensing.value.outdoorTemperature = 
      CCPU_TO_LE16(ZCL_SENSE_INTERNALLY);
  customThermostatClusterServerAttributes.remoteSensing.value.occupancySense = 
      CCPU_TO_LE16(ZCL_SENSE_INTERNALLY);
</#if>
#endif
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_CONTROLSEQOPERATION == true)>  
  customThermostatClusterServerAttributes.controlSequenceofOperation.value = 
      CCPU_TO_LE16(ZCL_COOL_HEAT_4PIPES);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_SYSTEMMODE == true)> 
  customThermostatClusterServerAttributes.systemMode.value = CCPU_TO_LE16(ZCL_SYS_MODE_AUTO);
</#if>
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_ALARMMASK == true)>   
  customThermostatClusterServerAttributes.alarmMask.value.initFailure = 
      CCPU_TO_LE16(ZCL_TH_ALARM_DISABLED);
  customThermostatClusterServerAttributes.alarmMask.value.hardwareFailure = 
      CCPU_TO_LE16(ZCL_TH_ALARM_DISABLED);
  customThermostatClusterServerAttributes.alarmMask.value.selfCalibrationFailure = 
      CCPU_TO_LE16(ZCL_TH_ALARM_DISABLED);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_THERMOSTATRUNNINGMODE == true)>
  customThermostatClusterServerAttributes.thermostatRunningMode.value = 
      CCPU_TO_LE16(ZCL_RUNNING_MODE_OFF);
</#if>
#endif
}

/**************************************************************************//**
\brief Updates the thermostat server attributes based on the given temperature

\param[in] - measured temperature
\param[out] - None
******************************************************************************/
void thermostatUpdateServerAttributes(int16_t temperature)
{
  uint8_t piCoolingDemand = 0;
  uint8_t piHeatingingDemand = 0;
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_LOCALTEMP == true)>
  customThermostatClusterServerAttributes.localTemperature.value = temperature;
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_OCCUPIEDCOOLINGSETPOINT == true) && (TC_OCCUPIEDHEATINGSETPOINT == true)>
  if(temperature > customThermostatClusterServerAttributes.occupiedCoolingSetpoint.value) 
  {  
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_MAXCOOLSETPOINTLIMIT == true)>
    piCoolingDemand = (temperature*100)/((customThermostatClusterServerAttributes.maxCoolSetpointLimit.value)+(customThermostatClusterServerAttributes.occupiedCoolingSetpoint.value));
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_SYSTEMMODE == true)>  
    customThermostatClusterServerAttributes.systemMode.value = ZCL_SYS_MODE_COOL;
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_PICOOLINGDEMAND == true)>  
    customThermostatClusterServerAttributes.PICoolingDemand.value = piCoolingDemand;
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_PIHEATINGDEMAND == true)>  
    customThermostatClusterServerAttributes.PIHeatingDemand.value = 0x00;
</#if>
</#if>
</#if>
</#if>
  }
  else if(temperature < customThermostatClusterServerAttributes.occupiedHeatingSetpoint.value)
  {
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_MINHEATSETPOINTLIMIT == true)>
    piHeatingingDemand = (temperature*100)/((customThermostatClusterServerAttributes.minHeatSetpointLimit.value)+(customThermostatClusterServerAttributes.occupiedHeatingSetpoint.value));
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_SYSTEMMODE == true)>
    customThermostatClusterServerAttributes.systemMode.value = ZCL_SYS_MODE_HEAT;
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_PIHEATINGDEMAND == true)>  
    customThermostatClusterServerAttributes.PIHeatingDemand.value = piHeatingingDemand;
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_PICOOLINGDEMAND == true)> 
    customThermostatClusterServerAttributes.PICoolingDemand.value = 0x00;
</#if>
</#if>
</#if>
</#if>
  }
  else // if the temparature is in between OccupiedHeatingSetPoint & OccupiedCoolingSetPoint then the sysMode is OFF
  {
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_SYSTEMMODE == true)>
    customThermostatClusterServerAttributes.systemMode.value = ZCL_SYS_MODE_OFF;
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_PIHEATINGDEMAND == true)>  
    customThermostatClusterServerAttributes.PIHeatingDemand.value = 0x00;
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_PICOOLINGDEMAND == true)> 
    customThermostatClusterServerAttributes.PICoolingDemand.value = 0x00;
</#if>
  }
</#if>
}

</#if>
<#if (THERMOSTAT_CLUSTER_CS != "SERVER")>
/**************************************************************************//**
\brief Report attribute indication handler

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void customThermostatReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_REPORTING_THERMOSTAT;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = reportLength;
  event.eventData.zclEventData.payload = reportPayload;

  APP_Zigbee_Handler(event);
}
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")>
/**************************************************************************//**
\brief Temperature measurement on timer expiry
       The temp sensor returns a temperature value already scaled by 
       THERMOSTAT_LOCAL_TEMPERATURE_SCALE.So further scaling is not needed here.

\param NA
******************************************************************************/
static void readTemperature(void)
{
  int16_t measuredTemp = 0;
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_REMOTESENSING == true)>
  if (ZCL_SENSE_INTERNALLY == customThermostatClusterServerAttributes.remoteSensing.value.localTemperature)
</#if>
#endif
    TEMP_SENSOR_READ(&measuredTemp);
#if defined(THERMOSTAT_EXTERNAL_TEMPERATURE_SENSOR_NODE_AVAILABLE) && defined(ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES)
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_REMOTESENSING == true)>
  else </#if>
  thermostatReadExternalTempSensor(&measuredTemp);
#endif  

  thermostatUpdateServerAttributes(measuredTemp);
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES  
  thermostatUpdateThRunningMode(measuredTemp);
#endif
}

#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
#if (ZB_COMMISSIONING_ON_STARTUP == 0)
/**************************************************************************//**
\brief Set local temperature
******************************************************************************/
void setLocalTemperature(int16_t temp)
{
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_LOCALTEMP == true)>  
  ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&temp);
</#if>                                     
}

/**************************************************************************//**
\brief Set Occupied cooling setpoint
******************************************************************************/
void setOccupiedCoolingSp(int16_t temp)
{
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_MINCOOLSETPOINTLIMIT == true) && (TC_MAXCOOLSETPOINTLIMIT == true)>  
  if((temp >= customThermostatClusterServerAttributes.minCoolSetpointLimit.value) && (temp <= customThermostatClusterServerAttributes.maxCoolSetpointLimit.value))
    ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                    ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                    ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&temp);
</#if>                                    
}

/**************************************************************************//**
\brief Set Occupied heating setpoint
******************************************************************************/
void setOccupiedHeatingSp(int16_t temp)
{
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_MINHEATSETPOINTLIMIT == true) && (TC_MAXHEATSETPOINTLIMIT == true)>    
  if((temp >= customThermostatClusterServerAttributes.minHeatSetpointLimit.value) && (temp <= customThermostatClusterServerAttributes.maxHeatSetpointLimit.value))
   ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                    ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_OCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                    ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&temp);
</#if>                                    
}

/**************************************************************************//**
\brief Set Absolute MinCoolSetpointLimit
******************************************************************************/
void setAbsMinCoolSetpointLimit(int16_t temp)
{
   ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                    ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_ABS_MIN_COOL_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID,
                                    ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&temp);
}
/**************************************************************************//**
\brief Set PI Cooling demand
******************************************************************************/
void setPiCoolingDemand(uint8_t temp)
{
   ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                    ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_PI_COOLING_DEMAND_SERVER_ATTRIBUTE_ID,
                                    ZCL_U8BIT_DATA_TYPE_ID,&temp);
}
/**************************************************************************//**
\brief Set PI Heating demand
******************************************************************************/
void setPiHeatingDemand(uint8_t temp)
{
  ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                    ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_PI_HEATING_DEMAND_SERVER_ATTRIBUTE_ID,
                                    ZCL_U8BIT_DATA_TYPE_ID,&temp);
}
#endif //#if ZB_COMMISSIONING_ON_STARTUP == 0
/**************************************************************************//**
\brief Updates the thermostat running mode based on the given temperature

\param[in] - measured temperature
\param[out] - None
******************************************************************************/
void thermostatUpdateThRunningMode(int16_t temperature)
{
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_OCCUPANCY == true) && (TC_THERMOSTATRUNNINGMODE == true)>  
  if (ZCL_OCCUPIED == customThermostatClusterServerAttributes.occupancy.value.occupied)
  {
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_OCCUPIEDHEATINGSETPOINT == true)>  
    if(temperature <= customThermostatClusterServerAttributes.occupiedHeatingSetpoint.value)
      customThermostatClusterServerAttributes.thermostatRunningMode.value = ZCL_RUNNING_MODE_HEAT;

    else </#if><#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_OCCUPIEDCOOLINGSETPOINT == true)> if(temperature >= customThermostatClusterServerAttributes.occupiedCoolingSetpoint.value)
      customThermostatClusterServerAttributes.thermostatRunningMode.value = ZCL_RUNNING_MODE_COOL;
  
    else</#if>
      customThermostatClusterServerAttributes.thermostatRunningMode.value = ZCL_RUNNING_MODE_OFF;
  }
  else if (ZCL_NOT_OCCUPIED == customThermostatClusterServerAttributes.occupancy.value.occupied)
  {
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_UNOCCUPIEDHEATINGSETPOINT == true)>  
    if(temperature <= customThermostatClusterServerAttributes.unOccupiedHeatingSetpoint.value)
      customThermostatClusterServerAttributes.thermostatRunningMode.value = ZCL_RUNNING_MODE_HEAT;
  
    else </#if><#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_UNOCCUPIEDCOOLINGSETPOINT == true)> if(temperature >= customThermostatClusterServerAttributes.unOccupiedCoolingSetpoint.value)
      customThermostatClusterServerAttributes.thermostatRunningMode.value = ZCL_RUNNING_MODE_COOL;
  
    else</#if>
      customThermostatClusterServerAttributes.thermostatRunningMode.value = ZCL_RUNNING_MODE_OFF;
  }
</#if>  
}
#endif

#if defined(THERMOSTAT_EXTERNAL_TEMPERATURE_SENSOR_NODE_AVAILABLE) && defined (ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES)
/**************************************************************************//**
\brief Read temperature from the remote sensor node on the network

\param[in] - pointer to return the measured temperature
\param[out] - None
******************************************************************************/
static void thermostatReadExternalTempSensor(int16_t *pTemperature)
{
  ZCL_Cluster_t *clientCluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, THERMOSTAT_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
  if(clientCluster)
  {
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_LOCALTEMP == true)>
    *pTemperature = customThermostatClusterServerAttributes.localTemperature.value;
</#if>
  }
  else
  {
    *pTemperature = ((int16_t)rand()) % (ZCL_TH_ABS_MAX_COOL_SP_LIMIT_DEF - ZCL_TH_ABS_MIN_HEAT_SP_LIMIT_DEF) 
                    + ZCL_TH_ABS_MIN_HEAT_SP_LIMIT_DEF;
    *pTemperature *= ZCL_THERMOSTAT_TEMPERATURE_SCALE;
  }
}
#endif
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (THC_SETPOINTRAISELOWER == true)>
/****************************************************************//**
 \brief thermostat cluster setpointRaiseLowerCommand indication
 \param addressing - source info
 \param reportLength  - length of data in reportPayload
 \param payload - payload data
 \return none
********************************************************************/
static ZCL_Status_t setpointCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, 
                                       ZCL_SetpointRaiseLower_t * payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_SETPOINT;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;

  int16_t requestedValue = 0;
  switch(payload->mode)
  {
      case ZCL_ADJUST_HEAT_SETPOINT:
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_OCCUPANCY == true)>
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
        if(ZCL_OCCUPIED == customThermostatClusterServerAttributes.occupancy.value.occupied)
#endif
</#if>          
        {
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_OCCUPIEDHEATINGSETPOINT == true)> 
          requestedValue = customThermostatClusterServerAttributes.occupiedHeatingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_OCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
</#if>
        }
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_UNOCCUPIEDHEATINGSETPOINT == true)>         
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
        else
        {

          requestedValue = customThermostatClusterServerAttributes.unOccupiedHeatingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_UNOCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
        }
#endif
</#if>
        break;
      case ZCL_ADJUST_COOL_SETPOINT:
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_OCCUPANCY == true)>
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES        
        if(ZCL_OCCUPIED == customThermostatClusterServerAttributes.occupancy.value.occupied)
#endif
</#if>
        {
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_OCCUPIEDCOOLINGSETPOINT == true)> 
          requestedValue = customThermostatClusterServerAttributes.occupiedCoolingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
</#if>
        }
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_UNOCCUPIEDCOOLINGSETPOINT == true)>        
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
        else
        {          
          requestedValue = customThermostatClusterServerAttributes.unOccupiedCoolingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_UNOCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
        }
#endif
</#if>
        break;
      case ZCL_ADJUST_HEAT_AND_COOL_SETPOINT:
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_OCCUPANCY == true)>      
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
        if(ZCL_OCCUPIED == customThermostatClusterServerAttributes.occupancy.value.occupied)
#endif
</#if>
        {
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_OCCUPIEDHEATINGSETPOINT == true)>           
          requestedValue = customThermostatClusterServerAttributes.occupiedHeatingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_OCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_OCCUPIEDCOOLINGSETPOINT == true)>                                      
          requestedValue = customThermostatClusterServerAttributes.occupiedCoolingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
</#if>                                     
        }        
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_OCCUPANCY == true)>
        else
</#if>        
        {
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_UNOCCUPIEDHEATINGSETPOINT == true)>           
          requestedValue = customThermostatClusterServerAttributes.unOccupiedHeatingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_UNOCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_UNOCCUPIEDCOOLINGSETPOINT == true)>                                     
          requestedValue = customThermostatClusterServerAttributes.unOccupiedCoolingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_UNOCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
</#if>
        }
#endif
        break;
      default:
        return ZCL_INVALID_ATTRIBUTE_VALUE_STATUS;
        break;
  }

#if APP_ENABLE_CONSOLE == 1
  appSnprintf("->SetPoints updated by CI: \r\n");
  appSnprintf("#setpoint mode: %d\r\n",payload->mode);
  appSnprintf("->setpoint amount updated by: %d.%d C\r\n", (int)((payload->amount)/THERMOSTAT_SETPOINT_SCALE),(int)((payload->amount)%THERMOSTAT_SETPOINT_SCALE));
#endif
  // warnings prevention
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
</#if>
/**************************************************************************//**
\brief Attribute Event indication handler(to indicate when attr values have
        read or written)

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void customThermostatAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  APP_Zigbee_Event_t eventItem;
  eventItem.eventGroup = EVENT_CLUSTER;
  eventItem.eventId = CMD_ZCL_ATTR_THERMOSTAT;
  eventItem.eventData.zclAttributeData.addressing = addressing;
  eventItem.eventData.zclAttributeData.attributeId = attributeId;
  eventItem.eventData.zclAttributeData.event = event;
  
  APP_Zigbee_Handler(eventItem);
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")>
  if((attributeId == ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID) && \
    ((event == ZCL_CONFIGURE_ATTRIBUTE_REPORTING_EVENT) || (event == ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT)))
  {
    PDS_Store(APP_CUSTOM_LOCAL_TEMPERATURE_MEM_ID);
  }
  else if((attributeId == ZCL_THERMOSTAT_CLUSTER_PI_COOLING_DEMAND_SERVER_ATTRIBUTE_ID) && \
    ((event == ZCL_CONFIGURE_ATTRIBUTE_REPORTING_EVENT) || (event == ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT)))
  {
    PDS_Store(APP_CUSTOM_PICOOLING_DEMAND_MEM_ID);
  }
  else if((attributeId == ZCL_THERMOSTAT_CLUSTER_PI_HEATING_DEMAND_SERVER_ATTRIBUTE_ID) && \
    ((event == ZCL_CONFIGURE_ATTRIBUTE_REPORTING_EVENT) || (event == ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT)))
  {
    PDS_Store(APP_CUSTOM_PIHEATING_DEMAND_MEM_ID);
  }
  else if ( (attributeId == ZCL_THERMOSTAT_CLUSTER_CONTROL_SEQUENCE_OF_OPERATION_SERVER_ATTRIBUTE_ID) 
           && (event == ZCL_WRITE_ATTRIBUTE_EVENT) )
  {
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_SYSTEMMODE == true)>    
    if(!thermostatValidateSystemModeValue((ZCL_ThControlSeqOfOperation_t)customThermostatClusterServerAttributes.controlSequenceofOperation.value,
                                         (ZCL_ThSystemMode_t)customThermostatClusterServerAttributes.systemMode.value))
      customThermostatClusterServerAttributes.systemMode.value = ZCL_SYS_MODE_AUTO;
</#if>
  }
  else if ( (attributeId == ZCL_THERMOSTAT_CLUSTER_SYSTEM_MODE_SERVER_ATTRIBUTE_ID) 
            && (event == ZCL_WRITE_ATTRIBUTE_EVENT) )
  {
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_SYSTEMMODE == true)>     
    if(customThermostatClusterServerAttributes.systemMode.value == ZCL_SYS_MODE_COOL)
    {
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_PIHEATINGDEMAND == true)>       
      customThermostatClusterServerAttributes.PIHeatingDemand.value = 0x00;
      PDS_Store(APP_CUSTOM_PIHEATING_DEMAND_MEM_ID);
</#if>      
    }
    else if(customThermostatClusterServerAttributes.systemMode.value == ZCL_SYS_MODE_HEAT)
    {
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_PICOOLINGDEMAND == true)>       
      customThermostatClusterServerAttributes.PICoolingDemand.value = 0x00;
      PDS_Store(APP_CUSTOM_PICOOLING_DEMAND_MEM_ID);
</#if>      
    }
    else if(customThermostatClusterServerAttributes.systemMode.value == ZCL_SYS_MODE_OFF)
    {
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_PIHEATINGDEMAND == true)>       
      customThermostatClusterServerAttributes.PIHeatingDemand.value = 0x00;
      PDS_Store(APP_CUSTOM_PIHEATING_DEMAND_MEM_ID);
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_PICOOLINGDEMAND == true)>       
      customThermostatClusterServerAttributes.PICoolingDemand.value = 0x00;
      PDS_Store(APP_CUSTOM_PICOOLING_DEMAND_MEM_ID);
</#if>
    }
</#if>    
  }
  else
  {
#if (APP_ENABLE_CONSOLE == 1) && (ZB_COMMISSIONING_ON_STARTUP == 1)
    appSnprintf("<-Attr ID 0x%x event 0x%x\r\n", attributeId, event);
#endif
  }
</#if>
}

<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")>
/**************************************************************************//**
\brief Validates the possible system mode value for the given control sequence 
       of operation

\param[in] - Control sequence of operation value
\param[in] - System mode value to be verified
\param[out] - None
******************************************************************************/
static ZCL_Status_t thermostatValidateSystemModeValue(ZCL_ThControlSeqOfOperation_t ctrlSeqOperation,ZCL_ThSystemMode_t sysModeValue)
{
  if(ZCL_SYS_MODE_RESERVED == sysModeValue)
  {
    return ZCL_FAILURE_STATUS;
  }
  switch(ctrlSeqOperation)
  {
    case ZCL_COOL_ONLY:
    case ZCL_COOL_WITH_REHEAT:
      if((ZCL_SYS_MODE_HEAT == sysModeValue) || (ZCL_SYS_MODE_EMERGENCY_HEATING == sysModeValue))
        return ZCL_FAILURE_STATUS;
      break;
    case ZCL_HEAT_ONLY:
    case ZCL_HEAT_WITH_REHEAT:
      if((ZCL_SYS_MODE_COOL == sysModeValue) || (ZCL_SYS_MODE_PRECOOLING == sysModeValue))
        return ZCL_FAILURE_STATUS;
      break;
    case ZCL_COOL_HEAT_4PIPES:      
    case ZCL_COOL_HEAT_4PIPES_REHEAT:
      return ZCL_SUCCESS_STATUS;
      break;
    default:
      return ZCL_SUCCESS_STATUS;
      break;
  }
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
  \brief  ZCL action request event handler, 
          handles the ZCL_ACTION_WRITE_ATTR_REQUEST for attribute specific validation

  \param[in] ev - must be BC_ZCL_EVENT_ACTION_REQUEST.
  \param[in] data - this field must contain pointer to the BcZCLActionReq_t structure,

  \return None.
 ******************************************************************************/
static void customThermostatEventListener(SYS_EventId_t eventId, SYS_EventData_t data)
{
  BcZCLActionReq_t *const actionReq = (BcZCLActionReq_t*)data;
  int16_t requestedValue = 0;
  if (BC_ZCL_EVENT_ACTION_REQUEST == eventId)
  {
    if(ZCL_PRE_ACTION_WRITE_ATTR_REQUEST == actionReq->action)
    {
      int8_t writeValue = 0;
      ZCLActionWriteAttrReq_t *const zclWriteAttrReq = (ZCLActionWriteAttrReq_t*)actionReq->context;
      if( (THERMOSTAT_CLUSTER_ID == zclWriteAttrReq->clusterId) && 
              (ZCL_CLUSTER_SIDE_SERVER == zclWriteAttrReq->clusterSide))
      {
        memcpy((void *)&writeValue,zclWriteAttrReq->attrValue, sizeof(int16_t));
        actionReq->denied = 0U;
        switch(zclWriteAttrReq->attrId)
        {  
        case ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_CALIBRATION_SERVER_ATTRIBUTE_ID:
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_LOCALTEMPCALIBRATION == true)>        
             if((writeValue > customThermostatClusterServerAttributes.localTemperatureCalibration.maxVal) ||
                  (writeValue < customThermostatClusterServerAttributes.localTemperatureCalibration.minVal))
          actionReq->denied = 1U;
</#if>          
            break;
          default:
            break;
        }
      }
    }
    if (ZCL_ACTION_WRITE_ATTR_REQUEST == actionReq->action)
    {
      ZCLActionWriteAttrReq_t *const zclWriteAttrReq = (ZCLActionWriteAttrReq_t*)actionReq->context;
      if( (THERMOSTAT_CLUSTER_ID == zclWriteAttrReq->clusterId) && 
              (ZCL_CLUSTER_SIDE_SERVER == zclWriteAttrReq->clusterSide))
      {
        memcpy((uint8_t *)&requestedValue,zclWriteAttrReq->attrValue, sizeof(int16_t));
        actionReq->denied = 0U;
        switch(zclWriteAttrReq->attrId)
        {
          case ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID:
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_OCCUPIEDHEATINGSETPOINT == true)>           
            if(requestedValue <= (customThermostatClusterServerAttributes.occupiedHeatingSetpoint.value 
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_MINSETPOINTDEADBAND == true)>            
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
                                  + customThermostatClusterServerAttributes.minSetpointDeadBand.value
#endif
</#if>
                                    ))
              actionReq->denied = 1U;
</#if>
            break;
          case ZCL_THERMOSTAT_CLUSTER_OCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID:
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_OCCUPIEDCOOLINGSETPOINT == true)>           
            if(requestedValue >= (customThermostatClusterServerAttributes.occupiedCoolingSetpoint.value
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_MINSETPOINTDEADBAND == true)>             
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
                                  - customThermostatClusterServerAttributes.minSetpointDeadBand.value
#endif
</#if>
                                    ))
              actionReq->denied = 1U;
</#if>
            break;
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
          case ZCL_THERMOSTAT_CLUSTER_UNOCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID:
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_UNOCCUPIEDHEATINGSETPOINT == true)>          
            if(requestedValue <= (customThermostatClusterServerAttributes.unOccupiedHeatingSetpoint.value
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_MINSETPOINTDEADBAND == true)>              + 
                                    customThermostatClusterServerAttributes.minSetpointDeadBand.value
</#if>                                    ))
              actionReq->denied = 1U;
</#if>
            break;
          case ZCL_THERMOSTAT_CLUSTER_UNOCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID: 
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_UNOCCUPIEDCOOLINGSETPOINT == true)>          
            if(requestedValue >= (customThermostatClusterServerAttributes.unOccupiedCoolingSetpoint.value 
            <#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_MINSETPOINTDEADBAND == true)> -
                                    customThermostatClusterServerAttributes.minSetpointDeadBand.value </#if>))
              actionReq->denied = 1U;
</#if>              
            break;
          case ZCL_THERMOSTAT_CLUSTER_MIN_HEAT_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID:
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_ABSMINHEATSETPOINTLIMIT == true)>               
            if(requestedValue < customThermostatClusterServerAttributes.absMinHeatSetpointLimit.value)
              actionReq->denied = 1U;
</#if>              
            break;
          case ZCL_THERMOSTAT_CLUSTER_MAX_HEAT_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID:
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_ABSMAXHEATSETPOINTLIMIT == true)>           
            if(requestedValue > customThermostatClusterServerAttributes.absMaxHeatSetpointLimit.value)
              actionReq->denied = 1U;
</#if>              
            break;
          case ZCL_THERMOSTAT_CLUSTER_MIN_COOL_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID:
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_ABSMINCOOLSETPOINTLIMIT == true)>           
            if(requestedValue < customThermostatClusterServerAttributes.absMinCoolSetpointLimit.value)
              actionReq->denied = 1U;
</#if>              
            break;
          case ZCL_THERMOSTAT_CLUSTER_MAX_COOL_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID:
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_ABSMAXCOOLSETPOINTLIMIT == true)>             
            if(requestedValue > customThermostatClusterServerAttributes.absMaxCoolSetpointLimit.value)
              actionReq->denied = 1U;
</#if>
            break;
#endif            
          case ZCL_THERMOSTAT_CLUSTER_SYSTEM_MODE_SERVER_ATTRIBUTE_ID:
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_SYSTEMMODE == true)>          
            if(ZCL_SUCCESS_STATUS != thermostatValidateSystemModeValue((ZCL_ThControlSeqOfOperation_t)customThermostatClusterServerAttributes.controlSequenceofOperation.value, 
                                                                       (ZCL_ThSystemMode_t)*(zclWriteAttrReq->attrValue)))
              actionReq->denied = 1U;
</#if>              
            break;
          default:
            break;
        }
      }
    }
    else if (ZCL_ACTION_RESET_ALARM_REQUEST == actionReq->action)
    {
      ZCL_ResetAlarmNotification_t  *resetAlarmNotification = (ZCL_ResetAlarmNotification_t *)(actionReq->context);

      if ((ZCL_ALARMS_CLUSTER_SERVER_RESET_ALARM_COMMAND_ID == resetAlarmNotification->commandId) && \
  	      (THERMOSTAT_CLUSTER_ID == resetAlarmNotification->clusterIdentifier))
      {
        //reset the alarmCode
#if APP_ENABLE_CONSOLE == 1
        appSnprintf("->thermostatResetAlarm:%d \r\n", resetAlarmNotification->alarmCode);
#endif
<#if (ALARMS_CLUSTER_ENABLE == true) && (ALARMS_CLUSTER_CS != "CLIENT")>
        // Remove the corresponding entry
        removeAlarmID(resetAlarmNotification->alarmCode,resetAlarmNotification->clusterIdentifier);
</#if>
<#if (ALARMS_CLUSTER_ENABLE == true)>
        if (isAlarmActive((ZclThermostatAlarmCode_t)resetAlarmNotification->alarmCode))
        {
          ZCL_Alarm_t alarmNtfy;

          alarmNtfy.alarmCode = resetAlarmNotification->alarmCode;
          alarmNtfy.clusterIdentifier = resetAlarmNotification->clusterIdentifier;
          ZCL_AlarmNotification(&alarmNtfy, APP_ENDPOINT_CUSTOM,isAlarmMasked((ZclThermostatAlarmCode_t)alarmNtfy.alarmCode));
        }
</#if>
      }
      else if (ZCL_ALARMS_CLUSTER_SERVER_RESET_ALL_ALARMS_COMMAND_ID == resetAlarmNotification->commandId)
      {
        ZCL_Alarm_t alarmNtfy;
#if APP_ENABLE_CONSOLE == 1
        appSnprintf("->thermostatResetAllAlarm\r\n");
#endif
<#if (ALARMS_CLUSTER_ENABLE == true) && (ALARMS_CLUSTER_CS != "CLIENT")  && (AC_ALARMCOUNT == true)>  
        for (uint8_t i = 0; i < customAlarmsClusterServerAttributes.alarmCount.value; i++)
        {
          alarmNtfy.alarmCode = customAlarmTable[0].alarmCode;
          alarmNtfy.clusterIdentifier = customAlarmTable[0].clusterIdentifier;

          removeAlarmID(alarmNtfy.alarmCode,alarmNtfy.clusterIdentifier);

          if (isAlarmActive((ZclThermostatAlarmCode_t)alarmNtfy.alarmCode))
          {
            ZCL_AlarmNotification(&alarmNtfy, APP_ENDPOINT_CUSTOM, isAlarmMasked((ZclThermostatAlarmCode_t)alarmNtfy.alarmCode));
          }
        }
</#if>        
      }
    }
  }
}

#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
/**************************************************************************//**
  \brief  Sets the occupancy attribute value         

  \param[in] value - Occupied or Not occupied
  \return Success(if valid value) / Failure (if not valid value)
 ******************************************************************************/
ZCL_Status_t thermostatSetOccupancy(ZCL_ThOccupancy_t value)
{
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_OCCUPANCY == true)>  
  if ((ZCL_OCCUPIED == value) || (ZCL_NOT_OCCUPIED == value))
  {
    customThermostatClusterServerAttributes.occupancy.value.occupied = value;
    return ZCL_SUCCESS_STATUS;
  }
  else 
</#if>  
    return ZCL_FAILURE_STATUS;
}
#endif


/**************************************************************************//**
\brief Set alarm mask
******************************************************************************/
void thermostatSetAlarmMaskAttr(uint8_t alarmMask)
{
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_ALARMMASK == true)>  
  uint8_t *alarmMaskAttr = (uint8_t *)&customThermostatClusterServerAttributes.alarmMask.value;
  *alarmMaskAttr = alarmMask;
</#if>
}

/**************************************************************************//**
  \brief set/reset alarm

  \param[in] alarmCode - alarmCode to be set/reset
  \param[in] setAlarm  - true - set the alarm
                         false - reset the alarm.
******************************************************************************/
void customSetAlarmActive(ZclThermostatAlarmCode_t alarmCode, bool active)
{
  if (active)
    customActiveAlarms |= (1 << alarmCode);
  else
    customActiveAlarms &= ~(1 << alarmCode);
}

/**************************************************************************//**
  \brief To check whether alarm is active or not

  \param[in] alarmCode - alarmCode to be checked
  \return    retStatus  - true if it is active
                          false if it is not active.
******************************************************************************/
bool isAlarmActive(ZclThermostatAlarmCode_t alarmCode)
{
  if (customActiveAlarms & ((uint8_t)1 << alarmCode))
  {
    return (true);
  }
  return (false);
}

/**************************************************************************//**
  \brief To check whether alarm is masked or not

  \param[in] alarmCode - alarmCode to be checked
  \return    retStatus  - true if it is masked
                          false if it is unmasked.
******************************************************************************/
bool isAlarmMasked(ZclThermostatAlarmCode_t alarmCode)
{
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_ALARMMASK == true)>  
  uint8_t *alarmMask = (uint8_t *)&customThermostatClusterServerAttributes.alarmMask.value;

  if (*alarmMask & ((uint8_t)1 << alarmCode))
  {
    return (true);
  }
</#if>  
  return (false);
}
</#if>
<#if (THERMOSTAT_CLUSTER_CS != "SERVER")>
/**************************************************************************//**
\brief Setpoint Raise/Lower command payload fillup

\param[out] payload - pointer to command structure;
\param[in] group - group id;
\param[in] scene - scene id
******************************************************************************/
static void customFillsendSetPointRaiseLowerPayload(ZCL_SetpointRaiseLower_t *payload, int8_t setPointMode, int8_t amount)
{
  payload->mode = setPointMode;
  payload->amount = amount;
}

/**************************************************************************//**
  \brief Sends Setpoint Raise/Lower command
  \param[in] mode - address mode;
  \param[in] addr - short address of destination node;
  \param[in] ep   - destination endpoint;
  \param[in] srcEp- source endpoint;
  \param mode - set points to be adjusted
  \param amount - amount of increase/decrease to setpoint value
        (in steps of 0.1°C.)
  \return none
******************************************************************************/
void customSendSetpointRaiseLowerCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp,
  int8_t setPointMode, int8_t amount)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_THERMOSTAT_CLUSTER_SETPOINT_RAISE_LOWER_COMMAND_ID, sizeof(ZCL_SetpointRaiseLower_t), srcEp);
  customFillsendSetPointRaiseLowerPayload((ZCL_SetpointRaiseLower_t *)req->requestPayload, setPointMode, amount);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, THERMOSTAT_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
}
</#if>

/*********************************************************************************
*********************************************************************************/
<#if DEVICE_DEEP_SLEEP_ENABLED>
<#if ((THERMOSTAT_CLUSTER_ENABLE == true) && ((THERMOSTAT_CLUSTER_CS != "CLIENT") || (THERMOSTAT_CLUSTER_CS == "BOTH")))>
void CDtsBackupTsAttributes(void)
{
   memcpy4ByteAligned(&backupCstmThermostatClusterServerAttributes,&customThermostatClusterServerAttributes, sizeof(ZCL_ThermostatClusterServerAttributes_t));
}
</#if>
<#if ((THERMOSTAT_CLUSTER_ENABLE == true) && ((THERMOSTAT_CLUSTER_CS != "CLIENT") || (THERMOSTAT_CLUSTER_CS == "BOTH")))>
void CDtsRestoreTsAttributes(void)
{
  memcpy4ByteAligned(&customThermostatClusterServerAttributes, &backupCstmThermostatClusterServerAttributes, sizeof(ZCL_ThermostatClusterServerAttributes_t));
}
</#if>
</#if>



#endif // APP_DEVICE_TYPE_CUSTOM

// eof customThermostatCluster.c
