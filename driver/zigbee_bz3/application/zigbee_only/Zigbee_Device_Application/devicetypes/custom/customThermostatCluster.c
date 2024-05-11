/*******************************************************************************
  Custom Thermostat Cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    customThermostatCluster.c

  Summary:
    This file contains the Custom Thermostat Cluster implementation.

  Description:
    This file contains the Custom Thermostat Cluster implementation.
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
#include <custom/include/customThermostatCluster.h>
#if APP_ENABLE_CONSOLE == 1

#endif
#include <custom/include/customAlarmsCluster.h>
#include <haClusters.h>
#include <zclCommandManager.h>
#include <zclAttributes.h>
#include <wlPdsMemIds.h>
#include <appConsts.h>
#include <console.h>
#include <z3Device.h>
/*******************************************************************************
                             Defines section
*******************************************************************************/
#define THERMOSTAT_SETPOINT_SCALE 10

#if THERMOSTAT_LOCAL_TEMPERATURE_MAX_REPORT_PERIOD > 2
#define TEMP_MEAS_TIME  ((THERMOSTAT_LOCAL_TEMPERATURE_MAX_REPORT_PERIOD/2) - 1)*1000
#else
#define TEMP_MEAS_TIME 1000
#endif
/*******************************************************************************
                             Types section
*******************************************************************************/
typedef struct PACK
{
  ZCL_AttributeId_t id;
  uint8_t type;
  uint8_t properties;
  int16_t value;
} setPoint_t;

/*******************************************************************************
                    Static functions prototypes section
*******************************************************************************/
static ZCL_Status_t setpointCommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_SetpointRaiseLower_t * payload);
static void readTemperature(void);
static void customThermostatAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
static void thermostatSettingsAttrInit(void);
static void thermostatInformationAttrInit(void);
static void customThermostatEventListener(SYS_EventId_t eventId, SYS_EventData_t data);
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
  static void thermostatUpdateThRunningMode(int16_t temperature);
#endif
#if defined(THERMOSTAT_EXTERNAL_TEMPERATURE_SENSOR_NODE_AVAILABLE) && defined (ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES)
  static void thermostatReadExternalTempSensor(int16_t *pTemperature);
#endif
static ZCL_Status_t thermostatValidateSystemModeValue(ZCL_ThControlSeqOfOperation_t ctrlSeqOperation,ZCL_ThSystemMode_t sysModeValue);
static void customThermostatReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload);

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_ThermostatClusterServerAttributes_t customThermostatClusterServerAttributes =
{
  ZCL_DEFINE_THERMOSTAT_CLUSTER_SERVER_MANDATORY_ATTRIBUTES(0, 0)
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES    
  ZCL_DEFINE_THERMOSTAT_CLUSTER_SERVER_OPTIONAL_ATTRIBUTES(0, 0)
#endif    
};

PROGMEM_DECLARE (ZCL_ThermostatClusterCommands_t customThermostatClusterServerCommands) =
{
  ZCL_DEFINE_THERMOSTAT_CLUSTER_COMMANDS(setpointCommandInd)
};

ZCL_ThermostatClusterClientAttributes_t customThermostatClusterClientAttributes =
{  
  ZCL_DEFINE_THERMOSTAT_MEASUREMENT_CLUSTER_CLIENT_ATTRIBUTES()
};

extern ZCL_AlarmEntry_t customAlarmTable[];

/******************************************************************************
                    Local variables
******************************************************************************/
static HAL_AppTimer_t tempMeasTimer;
static uint8_t customActiveAlarms = 0;

/* BitCloud events receiver */
static SYS_EventReceiver_t customEventReceiver = { .func = customThermostatEventListener};

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
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, THERMOSTAT_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
  ZCL_Cluster_t *clientCluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, THERMOSTAT_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
  if (cluster)
  {
    cluster->ZCL_AttributeEventInd = customThermostatAttrEventInd;
  }
  if (clientCluster)
  {
    clientCluster->ZCL_ReportInd = customThermostatReportInd;
  }
  thermostatClusterInitAttributes();
  TEMP_SENSOR_OPEN();
  customThermostatClusterClientAttributes.clusterVersion.value = CLUSTER_VERSION;
  /*Start periodic temperature measurement - this period shall always be less
  than reporting period*/
  tempMeasTimer.interval = TEMP_MEAS_TIME;
  tempMeasTimer.mode = TIMER_REPEAT_MODE;
  tempMeasTimer.callback = readTemperature;
  HAL_StopAppTimer(&tempMeasTimer);
  HAL_StartAppTimer(&tempMeasTimer);
  SYS_SubscribeToEvent(BC_ZCL_EVENT_ACTION_REQUEST, &customEventReceiver);
}
/**************************************************************************//**
\brief Initializes thermostat cluster atttributes to their defaults
\param NA
******************************************************************************/
 void thermostatClusterInitAttributes(void)
 {
  customThermostatClusterServerAttributes.clusterVersion.value = CLUSTER_VERSION;
  thermostatInformationAttrInit();
  thermostatSettingsAttrInit();
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES  
  customThermostatClusterServerAttributes.thermostatRunningState.value = CCPU_TO_LE16(ZCL_TH_RUNNING_STATE_DEF);
#endif
 }
/**************************************************************************//**
\brief Initializes the thermostat information attributes to their defaults
\param NA
******************************************************************************/
static void thermostatInformationAttrInit(void)
{
  customThermostatClusterServerAttributes.localTemperature.value =
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_LOCAL_TEMPERATURE_DEF);
  customThermostatClusterServerAttributes.localTemperature.minReportInterval = 
      THERMOSTAT_LOCAL_TEMPERATURE_MIN_REPORT_PERIOD;
  customThermostatClusterServerAttributes.localTemperature.maxReportInterval = 
      THERMOSTAT_LOCAL_TEMPERATURE_MAX_REPORT_PERIOD;
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
  customThermostatClusterServerAttributes.outdoorTemperature.value =
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_LOCAL_TEMPERATURE_DEF);
  customThermostatClusterServerAttributes.occupancy.value.occupied = CCPU_TO_LE16(ZCL_NOT_OCCUPIED);
  customThermostatClusterServerAttributes.absMinHeatSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_ABS_MIN_HEAT_SP_LIMIT_DEF);
  customThermostatClusterServerAttributes.absMaxHeatSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_ABS_MAX_HEAT_SP_LIMIT_DEF);
  customThermostatClusterServerAttributes.absMinCoolSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_ABS_MIN_COOL_SP_LIMIT_DEF);
  customThermostatClusterServerAttributes.absMaxCoolSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_ABS_MAX_COOL_SP_LIMIT_DEF);
  customThermostatClusterServerAttributes.PICoolingDemand.value =
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_PI_COOLING_DEMAND_DEF);
  customThermostatClusterServerAttributes.PICoolingDemand.maxReportInterval =
      THERMOSTAT_PI_CO0LING_DEMAND_MIN_REPORT_PERIOD;
  customThermostatClusterServerAttributes.PICoolingDemand.minReportInterval =
      THERMOSTAT_PI_CO0LING_DEMAND_MAX_REPORT_PERIOD;
  customThermostatClusterServerAttributes.PIHeatingDemand.value =
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_PI_HEATING_DEMAND_DEF);
  customThermostatClusterServerAttributes.PIHeatingDemand.minReportInterval =
      THERMOSTAT_PI_HEATING_DEMAND_MIN_REPORT_PERIOD;
  customThermostatClusterServerAttributes.PIHeatingDemand.maxReportInterval = 
      THERMOSTAT_PI_HEATING_DEMAND_MAX_REPORT_PERIOD;
  /*hvacSystemTypeConfiguration*/
  customThermostatClusterServerAttributes.hvacSystemTypeConfiguration.value.coolingStage = 
      (uint8_t)CCPU_TO_LE16(ZCL_HVAC_COOL_STAGE_1);
  customThermostatClusterServerAttributes.hvacSystemTypeConfiguration.value.heatingStage = 
      (uint8_t)CCPU_TO_LE16(ZCL_HVAC_HEAT_STAGE_1);
  customThermostatClusterServerAttributes.hvacSystemTypeConfiguration.value.heatingType = 
      (uint8_t)CCPU_TO_LE16(ZCL_HVAC_TYPE_CONVENTIONAL);
  customThermostatClusterServerAttributes.hvacSystemTypeConfiguration.value.heatingFuelSource = 
      (uint8_t)CCPU_TO_LE16(ZCL_HVAC_SOURCE_ELECTRIC);
#endif
}

/**************************************************************************//**
\brief Initializes the thermostat settings attributes to their defaults

\param NA
******************************************************************************/
static void thermostatSettingsAttrInit(void)
{
    ZCL_Cluster_t *clientCluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, THERMOSTAT_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES  
  customThermostatClusterServerAttributes.localTemperatureCalibration.value = 
      CCPU_TO_LE16(ZCL_TH_LOCAL_TEMP_CALIB_DEF);
#endif
  customThermostatClusterServerAttributes.occupiedCoolingSetpoint.value =
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_OCCUPIED_COOLING_SP_DEF);
  customThermostatClusterServerAttributes.occupiedHeatingSetpoint.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_OCCUPIED_HEATING_SP_DEF);
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
  customThermostatClusterServerAttributes.unOccupiedCoolingSetpoint.value =
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_UNOCCUPIED_COOLING_SP_DEF);
  customThermostatClusterServerAttributes.unOccupiedHeatingSetpoint.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_UNOCCUPIED_HEATING_SP_DEF);
  customThermostatClusterServerAttributes.minHeatSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_MIN_HEAT_SP_LIMIT_DEF);
  customThermostatClusterServerAttributes.maxHeatSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_MAX_HEAT_SP_LIMIT_DEF);
  customThermostatClusterServerAttributes.minCoolSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_MIN_COOL_SP_LIMIT_DEF);
  customThermostatClusterServerAttributes.maxCoolSetpointLimit.value = 
      CCPU_TO_LE16(ZCL_THERMOSTAT_TEMPERATURE_SCALE * ZCL_TH_MAX_COOL_SP_LIMIT_DEF);
  customThermostatClusterServerAttributes.minSetpointDeadBand.value = 
      (int8_t)CCPU_TO_LE16(ZCL_TH_MIN_SP_DEADBABD_DEF);
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
#endif
  customThermostatClusterServerAttributes.controlSequenceofOperation.value = 
      CCPU_TO_LE16(ZCL_COOL_HEAT_4PIPES);
  customThermostatClusterServerAttributes.systemMode.value = CCPU_TO_LE16(ZCL_SYS_MODE_AUTO);
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
  customThermostatClusterServerAttributes.alarmMask.value.initFailure = 
      CCPU_TO_LE16(ZCL_TH_ALARM_DISABLED);
  customThermostatClusterServerAttributes.alarmMask.value.hardwareFailure = 
      CCPU_TO_LE16(ZCL_TH_ALARM_DISABLED);
  customThermostatClusterServerAttributes.alarmMask.value.selfCalibrationFailure = 
      CCPU_TO_LE16(ZCL_TH_ALARM_DISABLED);
  customThermostatClusterServerAttributes.thermostatRunningMode.value = 
      CCPU_TO_LE16(ZCL_RUNNING_MODE_OFF);
#endif
}

/**************************************************************************//**
\brief Updates the thermostat server attributes based on the given temperature

\param[in] - measured temperature
\param[out] - None
******************************************************************************/
static void thermostatUpdateServerAttributes(int16_t temperature)
{
  uint8_t piCoolingDemand = 0;
  uint8_t piHeatingingDemand = 0;
  customThermostatClusterServerAttributes.localTemperature.value = temperature;
  if(temperature > customThermostatClusterServerAttributes.occupiedCoolingSetpoint.value) 
  {  
    piCoolingDemand = (temperature*100)/((customThermostatClusterServerAttributes.maxCoolSetpointLimit.value)+(customThermostatClusterServerAttributes.occupiedCoolingSetpoint.value));
    customThermostatClusterServerAttributes.systemMode.value = ZCL_SYS_MODE_COOL;
    customThermostatClusterServerAttributes.PICoolingDemand.value = piCoolingDemand;
    customThermostatClusterServerAttributes.PIHeatingDemand.value = 0x00;
  }
  else if(temperature < customThermostatClusterServerAttributes.occupiedHeatingSetpoint.value)
  {
    piHeatingingDemand = (temperature*100)/((customThermostatClusterServerAttributes.minHeatSetpointLimit.value)+(customThermostatClusterServerAttributes.occupiedHeatingSetpoint.value));
    customThermostatClusterServerAttributes.systemMode.value = ZCL_SYS_MODE_HEAT;
    customThermostatClusterServerAttributes.PIHeatingDemand.value = piHeatingingDemand;
    customThermostatClusterServerAttributes.PICoolingDemand.value = 0x00;
  }
  else // if the temparature is in between OccupiedHeatingSetPoint & OccupiedCoolingSetPoint then the sysMode is OFF
  {
    customThermostatClusterServerAttributes.systemMode.value = ZCL_SYS_MODE_OFF;
    customThermostatClusterServerAttributes.PIHeatingDemand.value = 0x00;
    customThermostatClusterServerAttributes.PICoolingDemand.value = 0x00;
  }
}

/**************************************************************************//**
\brief Report attribute indication handler

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void customThermostatReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload)
{
#if defined(THERMOSTAT_EXTERNAL_TEMPERATURE_SENSOR_NODE_AVAILABLE)
  ZCL_Report_t *rep = (ZCL_Report_t *)reportPayload;
  int16_t reportValue = 0;
  
  if(rep->id == ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID)
  {
    memcpy(&reportValue, &rep->value[0], sizeof(int16_t));
    thermostatUpdateServerAttributes(reportValue);
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES  
  thermostatUpdateThRunningMode(reportValue);
#endif
    appSnprintf("<-Thermostat Attr (0x%x) Report: t = %d.%dC\r\n", (unsigned)rep->id, (int)(reportValue/THERMOSTAT_LOCAL_TEMPERATURE_SCALE),(int)(reportValue%THERMOSTAT_LOCAL_TEMPERATURE_SCALE));
  }
  else if ((rep->id == ZCL_THERMOSTAT_CLUSTER_PI_COOLING_DEMAND_SERVER_ATTRIBUTE_ID) || (rep->id == ZCL_THERMOSTAT_CLUSTER_PI_HEATING_DEMAND_SERVER_ATTRIBUTE_ID))
  {
    memcpy(&reportValue, &rep->value[0], sizeof(uint8_t));
    appSnprintf("<-Thermostat Attr (0x%x) Report: t = %d\r\n", rep->id, (uint8_t)reportValue);
  }
#endif
  (void)addressing, (void)reportLength;
}

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
  if (ZCL_SENSE_INTERNALLY == customThermostatClusterServerAttributes.remoteSensing.value.localTemperature)
#endif
    TEMP_SENSOR_READ(&measuredTemp);
#if defined(THERMOSTAT_EXTERNAL_TEMPERATURE_SENSOR_NODE_AVAILABLE) && defined(ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES)
  else 
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
  ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&temp);
}

/**************************************************************************//**
\brief Set Occupied cooling setpoint
******************************************************************************/
void setOccupiedCoolingSp(int16_t temp)
{
  if((temp >= customThermostatClusterServerAttributes.minCoolSetpointLimit.value) && (temp <= customThermostatClusterServerAttributes.maxCoolSetpointLimit.value))
    ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                    ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                    ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&temp);
}

/**************************************************************************//**
\brief Set Occupied heating setpoint
******************************************************************************/
void setOccupiedHeatingSp(int16_t temp)
{
  if((temp >= customThermostatClusterServerAttributes.minHeatSetpointLimit.value) && (temp <= customThermostatClusterServerAttributes.maxHeatSetpointLimit.value))
   ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                    ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_OCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                    ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&temp);
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
static void thermostatUpdateThRunningMode(int16_t temperature)
{
  if (ZCL_OCCUPIED == customThermostatClusterServerAttributes.occupancy.value.occupied)
  {
    if(temperature <= customThermostatClusterServerAttributes.occupiedHeatingSetpoint.value)
      customThermostatClusterServerAttributes.thermostatRunningMode.value = ZCL_RUNNING_MODE_HEAT;

    else  if(temperature >= customThermostatClusterServerAttributes.occupiedCoolingSetpoint.value)
      customThermostatClusterServerAttributes.thermostatRunningMode.value = ZCL_RUNNING_MODE_COOL;
  
    else
      customThermostatClusterServerAttributes.thermostatRunningMode.value = ZCL_RUNNING_MODE_OFF;
  }
  else if (ZCL_NOT_OCCUPIED == customThermostatClusterServerAttributes.occupancy.value.occupied)
  {
    if(temperature <= customThermostatClusterServerAttributes.unOccupiedHeatingSetpoint.value)
      customThermostatClusterServerAttributes.thermostatRunningMode.value = ZCL_RUNNING_MODE_HEAT;
  
    else  if(temperature >= customThermostatClusterServerAttributes.unOccupiedCoolingSetpoint.value)
      customThermostatClusterServerAttributes.thermostatRunningMode.value = ZCL_RUNNING_MODE_COOL;
  
    else
      customThermostatClusterServerAttributes.thermostatRunningMode.value = ZCL_RUNNING_MODE_OFF;
  }
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
    *pTemperature = customThermostatClusterServerAttributes.localTemperature.value;
  }
  else
  {
    *pTemperature = ((int16_t)rand()) % (ZCL_TH_ABS_MAX_COOL_SP_LIMIT_DEF - ZCL_TH_ABS_MIN_HEAT_SP_LIMIT_DEF) 
                    + ZCL_TH_ABS_MIN_HEAT_SP_LIMIT_DEF;
    *pTemperature *= ZCL_THERMOSTAT_TEMPERATURE_SCALE;
  }
}
#endif
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
  int16_t requestedValue = 0;
  switch(payload->mode)
  {
      case ZCL_ADJUST_HEAT_SETPOINT:
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
        if(ZCL_OCCUPIED == customThermostatClusterServerAttributes.occupancy.value.occupied)
#endif
        {
          requestedValue = customThermostatClusterServerAttributes.occupiedHeatingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_OCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
        }
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
        break;
      case ZCL_ADJUST_COOL_SETPOINT:
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES        
        if(ZCL_OCCUPIED == customThermostatClusterServerAttributes.occupancy.value.occupied)
#endif
        {
          requestedValue = customThermostatClusterServerAttributes.occupiedCoolingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
        }
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
        break;
      case ZCL_ADJUST_HEAT_AND_COOL_SETPOINT:
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
        if(ZCL_OCCUPIED == customThermostatClusterServerAttributes.occupancy.value.occupied)
#endif
        {
          requestedValue = customThermostatClusterServerAttributes.occupiedHeatingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_OCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
          requestedValue = customThermostatClusterServerAttributes.occupiedCoolingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
        }        
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
        else
        {
          requestedValue = customThermostatClusterServerAttributes.unOccupiedHeatingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_UNOCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
          requestedValue = customThermostatClusterServerAttributes.unOccupiedCoolingSetpoint.value +
                                               (payload->amount)*THERMOSTAT_SETPOINT_SCALE;
          ZCL_WriteAttributeValue(APP_ENDPOINT_CUSTOM,THERMOSTAT_CLUSTER_ID,
                                     ZCL_SERVER_CLUSTER_TYPE,ZCL_THERMOSTAT_CLUSTER_UNOCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,(uint8_t *)&requestedValue);
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
  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Attribute Event indication handler(to indicate when attr values have
        read or written)

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void customThermostatAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  if(ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == event)
  {
    switch(attributeId)
    {
      case ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID:
       customThermostatClusterServerAttributes.localTemperature.minReportInterval = THERMOSTAT_LOCAL_TEMPERATURE_MIN_REPORT_PERIOD;
       customThermostatClusterServerAttributes.localTemperature.maxReportInterval = THERMOSTAT_LOCAL_TEMPERATURE_MAX_REPORT_PERIOD;
       customThermostatClusterServerAttributes.localTemperature.reportableChange = 0;    
       break;

      case ZCL_THERMOSTAT_CLUSTER_PI_COOLING_DEMAND_SERVER_ATTRIBUTE_ID:
        customThermostatClusterServerAttributes.PICoolingDemand.minReportInterval = THERMOSTAT_PI_CO0LING_DEMAND_MIN_REPORT_PERIOD;
        customThermostatClusterServerAttributes.PICoolingDemand.maxReportInterval = THERMOSTAT_PI_CO0LING_DEMAND_MAX_REPORT_PERIOD;
        customThermostatClusterServerAttributes.PICoolingDemand.reportableChange = 0;
        break;
      case ZCL_THERMOSTAT_CLUSTER_PI_HEATING_DEMAND_SERVER_ATTRIBUTE_ID:
        customThermostatClusterServerAttributes.PIHeatingDemand.minReportInterval = THERMOSTAT_PI_HEATING_DEMAND_MIN_REPORT_PERIOD;
        customThermostatClusterServerAttributes.PIHeatingDemand.maxReportInterval = THERMOSTAT_PI_HEATING_DEMAND_MAX_REPORT_PERIOD;
        customThermostatClusterServerAttributes.PIHeatingDemand.reportableChange = 0;
        break;
        
      default :
        break;
      
    }
  }
  
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
    if(!thermostatValidateSystemModeValue((ZCL_ThControlSeqOfOperation_t)customThermostatClusterServerAttributes.controlSequenceofOperation.value,
                                         (ZCL_ThSystemMode_t)customThermostatClusterServerAttributes.systemMode.value))
      customThermostatClusterServerAttributes.systemMode.value = ZCL_SYS_MODE_AUTO;
  }
  else if ( (attributeId == ZCL_THERMOSTAT_CLUSTER_SYSTEM_MODE_SERVER_ATTRIBUTE_ID) 
            && (event == ZCL_WRITE_ATTRIBUTE_EVENT) )
  {
    if(customThermostatClusterServerAttributes.systemMode.value == ZCL_SYS_MODE_COOL)
    {
      customThermostatClusterServerAttributes.PIHeatingDemand.value = 0x00;
      PDS_Store(APP_CUSTOM_PIHEATING_DEMAND_MEM_ID);
    }
    else if(customThermostatClusterServerAttributes.systemMode.value == ZCL_SYS_MODE_HEAT)
    {
      customThermostatClusterServerAttributes.PICoolingDemand.value = 0x00;
      PDS_Store(APP_CUSTOM_PICOOLING_DEMAND_MEM_ID);
    }
    else if(customThermostatClusterServerAttributes.systemMode.value == ZCL_SYS_MODE_OFF)
    {
      customThermostatClusterServerAttributes.PIHeatingDemand.value = 0x00;
      PDS_Store(APP_CUSTOM_PIHEATING_DEMAND_MEM_ID);
      customThermostatClusterServerAttributes.PICoolingDemand.value = 0x00;
      PDS_Store(APP_CUSTOM_PICOOLING_DEMAND_MEM_ID);
    }
  }
  else
  {
#if (APP_ENABLE_CONSOLE == 1) && (ZB_COMMISSIONING_ON_STARTUP == 1)
    appSnprintf("<-Attr ID 0x%x event 0x%x\r\n", attributeId, event);
#endif
  }
  (void)addressing;
}
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
             if((writeValue > customThermostatClusterServerAttributes.localTemperatureCalibration.maxVal) ||
                  (writeValue < customThermostatClusterServerAttributes.localTemperatureCalibration.minVal))
          actionReq->denied = 1U;
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
            if(requestedValue <= (customThermostatClusterServerAttributes.occupiedHeatingSetpoint.value 
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
                                  + customThermostatClusterServerAttributes.minSetpointDeadBand.value
#endif
                                    ))
              actionReq->denied = 1U;
            break;
          case ZCL_THERMOSTAT_CLUSTER_OCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID:
            if(requestedValue >= (customThermostatClusterServerAttributes.occupiedCoolingSetpoint.value
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
                                  - customThermostatClusterServerAttributes.minSetpointDeadBand.value
#endif
                                    ))
              actionReq->denied = 1U;
            break;
#ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES
          case ZCL_THERMOSTAT_CLUSTER_UNOCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID:
            if(requestedValue <= (customThermostatClusterServerAttributes.unOccupiedHeatingSetpoint.value
              + 
                                    customThermostatClusterServerAttributes.minSetpointDeadBand.value
                                    ))
              actionReq->denied = 1U;
            break;
          case ZCL_THERMOSTAT_CLUSTER_UNOCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID: 
            if(requestedValue >= (customThermostatClusterServerAttributes.unOccupiedCoolingSetpoint.value 
             -
                                    customThermostatClusterServerAttributes.minSetpointDeadBand.value ))
              actionReq->denied = 1U;
            break;
          case ZCL_THERMOSTAT_CLUSTER_MIN_HEAT_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID:
            if(requestedValue < customThermostatClusterServerAttributes.absMinHeatSetpointLimit.value)
              actionReq->denied = 1U;
            break;
          case ZCL_THERMOSTAT_CLUSTER_MAX_HEAT_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID:
            if(requestedValue > customThermostatClusterServerAttributes.absMaxHeatSetpointLimit.value)
              actionReq->denied = 1U;
            break;
          case ZCL_THERMOSTAT_CLUSTER_MIN_COOL_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID:
            if(requestedValue < customThermostatClusterServerAttributes.absMinCoolSetpointLimit.value)
              actionReq->denied = 1U;
            break;
          case ZCL_THERMOSTAT_CLUSTER_MAX_COOL_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID:
            if(requestedValue > customThermostatClusterServerAttributes.absMaxCoolSetpointLimit.value)
              actionReq->denied = 1U;
            break;
#endif            
          case ZCL_THERMOSTAT_CLUSTER_SYSTEM_MODE_SERVER_ATTRIBUTE_ID:
            if(ZCL_SUCCESS_STATUS != thermostatValidateSystemModeValue((ZCL_ThControlSeqOfOperation_t)customThermostatClusterServerAttributes.controlSequenceofOperation.value, 
                                                                       (ZCL_ThSystemMode_t)*(zclWriteAttrReq->attrValue)))
              actionReq->denied = 1U;
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
        // Remove the corresponding entry
        removeAlarmID(resetAlarmNotification->alarmCode,resetAlarmNotification->clusterIdentifier);

        if (isAlarmActive((ZclThermostatAlarmCode_t)resetAlarmNotification->alarmCode))
        {
          ZCL_Alarm_t alarmNtfy;

          alarmNtfy.alarmCode = resetAlarmNotification->alarmCode;
          alarmNtfy.clusterIdentifier = resetAlarmNotification->clusterIdentifier;
          ZCL_AlarmNotification(&alarmNtfy, APP_ENDPOINT_CUSTOM,isAlarmMasked((ZclThermostatAlarmCode_t)alarmNtfy.alarmCode));
        }
      }
      else if (ZCL_ALARMS_CLUSTER_SERVER_RESET_ALL_ALARMS_COMMAND_ID == resetAlarmNotification->commandId)
      {
        ZCL_Alarm_t alarmNtfy;
#if APP_ENABLE_CONSOLE == 1
        appSnprintf("->thermostatResetAllAlarm\r\n");
#endif
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
  if ((ZCL_OCCUPIED == value) || (ZCL_NOT_OCCUPIED == value))
  {
    customThermostatClusterServerAttributes.occupancy.value.occupied = value;
    return ZCL_SUCCESS_STATUS;
  }
  else 
    return ZCL_FAILURE_STATUS;
}
#endif


/**************************************************************************//**
\brief Set alarm mask
******************************************************************************/
void thermostatSetAlarmMaskAttr(uint8_t alarmMask)
{
  uint8_t *alarmMaskAttr = (uint8_t *)&customThermostatClusterServerAttributes.alarmMask.value;
  *alarmMaskAttr = alarmMask;
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
  uint8_t *alarmMask = (uint8_t *)&customThermostatClusterServerAttributes.alarmMask.value;

  if (*alarmMask & ((uint8_t)1 << alarmCode))
  {
    return (true);
  }
  return (false);
}

#endif // APP_DEVICE_TYPE_CUSTOM

// eof customThermostatCluster.c
