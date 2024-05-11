/*******************************************************************************
  Custom clusters Source File

  Company:
    Microchip Technology Inc.

  File Name:
    customClusters.c

  Summary:
    This file contains the Custom Clusters implementation.

  Description:
    This file contains the Custom Clusters implementation.
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
#if APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_CUSTOM_DEVICE
/******************************************************************************
                    Includes section
******************************************************************************/
#include <identifyCluster.h>
#include <custom/include/customClusters.h>
#include <custom/include/customBasicCluster.h>
#include <custom/include/customIdentifyCluster.h>
#include <custom/include/customOnOffCluster.h>
#include <custom/include/customLevelControlCluster.h>
#include <custom/include/customColorControlCluster.h>
#include <custom/include/customGroupsCluster.h>
#include <custom/include/customScenesCluster.h>
#include <custom/include/customAlarmsCluster.h>
#include <custom/include/customFanControlCluster.h>
#include <custom/include/customHumidityMeasurementCluster.h>
#include <custom/include/customIasACECluster.h>
#include <custom/include/customIasZoneCluster.h>
#include <custom/include/customOccupancySensingCluster.h>
#include <custom/include/customIlluminanceMeasurementCluster.h>
#include <custom/include/customTemperatureMeasurementCluster.h>
#include <custom/include/customThermostatCluster.h>
#include <custom/include/customThermostatUiConfCluster.h>
#include <custom/include/customTimeCluster.h>
#include <custom/include/customCommissioningCluster.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_Cluster_t customServerClusters[CUSTOM_SERVER_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER(&customBasicClusterServerAttributes, &customBasicClusterServerCommands),
  DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customIdentifyClusterServerAttributes, &customIdentifyCommands),
  DEFINE_GROUPS_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customGroupsClusterServerAttributes, &customGroupsCommands),
  DEFINE_SCENES_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customScenesClusterServerAttributes, &customScenesCommands),
  DEFINE_ONOFF_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customOnOffClusterServerAttributes, &customOnOffCommands),
  DEFINE_LEVEL_CONTROL_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customLevelControlClusterServerAttributes, &customLevelControlCommands),
  DEFINE_COLOR_CONTROL_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customColorControlClusterServerAttributes, &customColorControlClusterServerCommands),
  DEFINE_COMMISSIONING_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customCommissioningClusterServerAttributes, &customCommissioningClusterCommands),
  DEFINE_ALARMS_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customAlarmsClusterServerAttributes, &customAlarmsClusterServerCommands),
  DEFINE_TIME_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customTimeClusterServerAttributes, NULL),
  DEFINE_THERMOSTAT_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customThermostatClusterServerAttributes, &customThermostatClusterServerCommands),
  DEFINE_FAN_CONTROL_CLUSTER(ZCL_SERVER_CLUSTER_TYPE,&customFanControlClusterServerAttributes,NULL),
  DEFINE_OCCUPANCY_SENSING_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customOccupancySensingClusterServerAttributes, NULL),
  DEFINE_ILLUMINANCE_MEASUREMENT_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customIlluminanceMeasurementClusterServerAttributes),
  DEFINE_TEMPERATURE_MEASUREMENT_CLUSTER(ZCL_SERVER_CLUSTER_TYPE,&customTemperatureMeasurementClusterServerAttributes),
  DEFINE_HUMIDITY_MEASUREMENT_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customHumidityMeasurementClusterServerAttributes),
  DEFINE_THERMOSTAT_UI_CONF_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customThermostatUiConfClusterServerAttributes, NULL),
  DEFINE_IAS_ZONE_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customIasZoneClusterServerAttributes, &customIasZoneClusterServerCommands),
  DEFINE_IAS_ACE_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customIasAceClusterServerAttributes, &customIasAceClusterServerCommands),
};

void (*customServerClusterInitFunctions[CUSTOM_SERVER_CLUSTER_INIT_COUNT])() =
{
  customBasicClusterInit,
  customIdentifyClusterInit,
  customGroupsClusterInit,
  customScenesClusterInit,
  customOnOffClusterInit,
  customLevelControlClusterInit,
  customColorControlClusterInit,
  customCommissioningClusterInit,
  customAlarmsClusterInit,
  customTimeClusterInit,
  customThermostatClusterInit,
  customFanControlClusterInit,
  customOccupancySensingClusterInit,
  customIlluminanceMeasurementClusterInit,
  customTemperatureMeasurementClusterInit,
  customHumidityMeasurementClusterInit,
  customThermostatUiConfClusterInit,
  customIasZoneClusterInit,
  customIasACEClusterInit
};


ClusterId_t customServerClusterIds[CUSTOM_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  SCENES_CLUSTER_ID,
  ONOFF_CLUSTER_ID,
  LEVEL_CONTROL_CLUSTER_ID,
  COLOR_CONTROL_CLUSTER_ID,
  ZLL_COMMISSIONING_CLUSTER_ID,
  ALARMS_CLUSTER_ID,
  TIME_CLUSTER_ID,
  THERMOSTAT_CLUSTER_ID,
  FAN_CONTROL_CLUSTER_ID,
  OCCUPANCY_SENSING_CLUSTER_ID,
  ILLUMINANCE_MEASUREMENT_CLUSTER_ID,
  TEMPERATURE_MEASUREMENT_CLUSTER_ID,
  HUMIDITY_MEASUREMENT_CLUSTER_ID,
  THERMOSTAT_UI_CONF_CLUSTER_ID,
  IAS_ZONE_CLUSTER_ID,
  IAS_ACE_CLUSTER_ID
};

ZCL_Cluster_t customClientClusters[CUSTOM_CLIENT_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_CLIENT(&customBasicClusterClientAttributes),
  DEFINE_IDENTIFY_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customIdentifyClusterClientAttributes, &customIdentifyCommands),
  DEFINE_GROUPS_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customGroupsClusterClientAttributes, &customGroupsCommands),
  DEFINE_ONOFF_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customOnOffClusterClientAttributes, &customOnOffCommands),
  DEFINE_LEVEL_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customOnOffClusterClientAttributes, &customLevelControlCommands),
  DEFINE_COLOR_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customColorControlClusterClientAttributes, &customColorControlClusterClientCommands),
  DEFINE_SCENES_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customScenesClusterClientAttributes, &customScenesCommands),
  DEFINE_OCCUPANCY_SENSING_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customOccupancySensingClusterClientAttributes, NULL),
  DEFINE_ILLUMINANCE_MEASUREMENT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customIlluminanceMeasurementClusterClientAttributes), 
  DEFINE_HUMIDITY_MEASUREMENT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customHumidityMeasurementClusterClientAttributes),
  DEFINE_TEMPERATURE_MEASUREMENT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customTemperatureMeasurementClusterClientAttributes),
  DEFINE_COMMISSIONING_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customCommissioningClusterClientAttributes, &customCommissioningClusterCommands),
  DEFINE_COLOR_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customColorControlClusterClientAttributes, &customColorControlClusterClientCommands),
  DEFINE_THERMOSTAT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customThermostatClusterClientAttributes, NULL),
  DEFINE_THERMOSTAT_UI_CONF_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customThermostatUiConfClusterClientAttributes, NULL),
  DEFINE_ALARMS_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customAlarmsClusterClientAttributes, &customAlarmsClusterClientCommands),
  DEFINE_FAN_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customFanControlClusterClientAttributes, NULL),
  DEFINE_IAS_ZONE_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customIasZoneClusterClientAttributes, &customIasZoneClusterClientCommands),
  DEFINE_IAS_ACE_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customIasAceClusterClientAttributes , &customIasAceClusterClientCommands),
};


ClusterId_t customClientClusterIds[CUSTOM_CLIENT_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  SCENES_CLUSTER_ID,
  ONOFF_CLUSTER_ID,
  LEVEL_CONTROL_CLUSTER_ID,
  COLOR_CONTROL_CLUSTER_ID,
  ZLL_COMMISSIONING_CLUSTER_ID,
  ALARMS_CLUSTER_ID,
  TIME_CLUSTER_ID,
  THERMOSTAT_CLUSTER_ID,
  FAN_CONTROL_CLUSTER_ID,
  OCCUPANCY_SENSING_CLUSTER_ID,
  ILLUMINANCE_MEASUREMENT_CLUSTER_ID,
  TEMPERATURE_MEASUREMENT_CLUSTER_ID,
  HUMIDITY_MEASUREMENT_CLUSTER_ID,
  THERMOSTAT_UI_CONF_CLUSTER_ID,
  IAS_ZONE_CLUSTER_ID,
  IAS_ACE_CLUSTER_ID
};

void (*customClientClusterInitFunctions[CUSTOM_CLIENT_CLUSTER_INIT_COUNT])() =
{
  customBasicClusterInit,
  customIdentifyClusterInit,
  customGroupsClusterInit,
  customScenesClusterInit,
  customOnOffClusterInit,
  customLevelControlClusterInit,
  customColorControlClusterInit,
  customCommissioningClusterInit,
  customAlarmsClusterInit,
  customTimeClusterInit,
  customThermostatClusterInit,
  customFanControlClusterInit,
  customOccupancySensingClusterInit,
  customIlluminanceMeasurementClusterInit,
  customTemperatureMeasurementClusterInit,
  customHumidityMeasurementClusterInit,
  customThermostatUiConfClusterInit,
  customIasZoneClusterInit,
  customIasACEClusterInit
};


#endif // #if APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_CUSTOM_DEVICE

// eof customClusters.c
