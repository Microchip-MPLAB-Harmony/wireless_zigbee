/*******************************************************************************
  Custom Cluster Source file

  Company:
    Microchip Technology Inc.

  File Name:
    customCluster.c

  Summary:
    This file contains Custom Cluster Implementation.

  Description:
    This file contains Custom Cluster Implementation . 
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
#include <zcl/clusters/include/identifyCluster.h>
#include <z3device/custom/include/customClusters.h>
#include <z3device/custom/include/customBasicCluster.h>
#include <z3device/custom/include/customIdentifyCluster.h>
#include <z3device/custom/include/customOnOffCluster.h>
#include <z3device/custom/include/customLevelControlCluster.h>
#include <z3device/custom/include/customColorControlCluster.h>
#include <z3device/custom/include/customGroupsCluster.h>
#include <z3device/custom/include/customScenesCluster.h>
#include <z3device/custom/include/customAlarmsCluster.h>
#include <z3device/custom/include/customFanControlCluster.h>
#include <z3device/custom/include/customHumidityMeasurementCluster.h>
#include <z3device/custom/include/customIasACECluster.h>
#include <z3device/custom/include/customIasZoneCluster.h>
#include <z3device/custom/include/customOccupancySensingCluster.h>
#include <z3device/custom/include/customIlluminanceMeasurementCluster.h>
#include <z3device/custom/include/customTemperatureMeasurementCluster.h>
#include <z3device/custom/include/customThermostatCluster.h>
#include <z3device/custom/include/customThermostatUiConfCluster.h>
#include <z3device/custom/include/customTimeCluster.h>
#include <z3device/custom/include/customCommissioningCluster.h>
#include <z3device/custom/include/customDiagnosticsCluster.h>

<#compress>
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >

  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  <#assign devicetype = DEVICE_TYPE_FILE_PATH >
#include <z3device/${devicetype}/include/${deviceTypeFunctionPrefix + clusterName}Cluster.h>
#include <zcl/include/zcl${clusterName}Cluster.h>

  </#list>

</#compress>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_Cluster_t customServerClusters[CUSTOM_SERVER_CLUSTERS_COUNT] =
{
<#if (BASIC_CLUSTER_ENABLE == true) && (BASIC_CLUSTER_CS != "CLIENT")  >
  ZCL_DEFINE_BASIC_CLUSTER_SERVER(&customBasicClusterServerAttributes, &customBasicClusterServerCommands),
</#if><#if (IDENTIFY_CLUSTER_ENABLE == true) && (IDENTIFY_CLUSTER_CS != "CLIENT")  >
  DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customIdentifyClusterServerAttributes, &customIdentifyCommands),
</#if><#if (GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "CLIENT")  >  
  DEFINE_GROUPS_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customGroupsClusterServerAttributes, &customGroupsCommands),
</#if><#if (SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  >
  DEFINE_SCENES_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customScenesClusterServerAttributes, &customScenesCommands),
</#if><#if (ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "CLIENT")  >
  DEFINE_ONOFF_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customOnOffClusterServerAttributes, &customOnOffCommands),
</#if><#if (LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  >
  DEFINE_LEVEL_CONTROL_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customLevelControlClusterServerAttributes, &customLevelControlCommands),
</#if><#if (COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  >
  DEFINE_COLOR_CONTROL_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customColorControlClusterServerAttributes, &customColorControlClusterServerCommands),
</#if>
  DEFINE_COMMISSIONING_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customCommissioningClusterServerAttributes, &customCommissioningClusterCommands),
<#if (ALARMS_CLUSTER_ENABLE == true) && (ALARMS_CLUSTER_CS != "CLIENT")  >
  DEFINE_ALARMS_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customAlarmsClusterServerAttributes, &customAlarmsClusterServerCommands),
</#if><#if (TIME_CLUSTER_ENABLE == true) && (TIME_CLUSTER_CS != "CLIENT")  >
  DEFINE_TIME_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customTimeClusterServerAttributes, NULL),
</#if><#if (THERMOSTAT_CLUSTER_ENABLE == true) && (THERMOSTAT_CLUSTER_CS != "CLIENT")  >
  DEFINE_THERMOSTAT_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customThermostatClusterServerAttributes, &customThermostatClusterServerCommands),
</#if><#if (FANCONTROL_CLUSTER_ENABLE == true) && (FANCONTROL_CLUSTER_CS != "CLIENT")  >
  DEFINE_FAN_CONTROL_CLUSTER(ZCL_SERVER_CLUSTER_TYPE,&customFanControlClusterServerAttributes,NULL),
</#if><#if (OCCUPANCYSENSING_CLUSTER_ENABLE == true) && (OCCUPANCYSENSING_CLUSTER_CS != "CLIENT")  >
  DEFINE_OCCUPANCY_SENSING_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customOccupancySensingClusterServerAttributes, NULL),
</#if><#if (ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE == true) && (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT")  >
  DEFINE_ILLUMINANCE_MEASUREMENT_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customIlluminanceMeasurementClusterServerAttributes),
</#if><#if (TEMPERATUREMEASUREMENT_CLUSTER_ENABLE == true) && (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")  >
  DEFINE_TEMPERATURE_MEASUREMENT_CLUSTER(ZCL_SERVER_CLUSTER_TYPE,&customTemperatureMeasurementClusterServerAttributes),
</#if><#if (WATERCONTENTMEASUREMENT_CLUSTER_ENABLE == true) && (WATERCONTENTMEASUREMENT_CLUSTER_CS != "CLIENT")  >
  DEFINE_HUMIDITY_MEASUREMENT_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customHumidityMeasurementClusterServerAttributes),
</#if><#if (THERMOSTATUI_CLUSTER_ENABLE == true) && (THERMOSTATUI_CLUSTER_CS != "CLIENT")  >
  DEFINE_THERMOSTAT_UI_CONF_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customThermostatUiConfClusterServerAttributes, NULL),
</#if><#if (IASZONE_CLUSTER_ENABLE == true) && (IASZONE_CLUSTER_CS != "CLIENT")  >
  DEFINE_IAS_ZONE_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customIasZoneClusterServerAttributes, &customIasZoneClusterServerCommands),
</#if><#if (IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  >
  DEFINE_IAS_ACE_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &customIasAceClusterServerAttributes, &customIasAceClusterServerCommands),
</#if><#if (DIAGONSTICS_CLUSTER_ENABLE == true) && (DIAGONSTICS_CLUSTER_CS != "CLIENT")  >
  DEFINE_DIAGNOSTICS_CLUSTER(ZCL_SERVER_CLUSTER_TYPE,&customDiagnosticsClusterServerAttributes, NULL),
</#if>
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER") || (DEVICE == "BOTH") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  DEFINE_${(clusterName)?upper_case}_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &${clusterName?lower_case}${"SERVER"?capitalize}ClusterAttributes, &${clusterName?lower_case}ClusterCommands),
  </#if>
  </#list>
};

void (*customServerClusterInitFunctions[CUSTOM_SERVER_CLUSTER_INIT_COUNT])() =
{
<#if (BASIC_CLUSTER_ENABLE == true) && (BASIC_CLUSTER_CS != "CLIENT")  >
  customBasicClusterInit,
</#if><#if (IDENTIFY_CLUSTER_ENABLE == true) && (IDENTIFY_CLUSTER_CS != "CLIENT")  >
  customIdentifyClusterInit,
</#if><#if (GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "CLIENT")  >  
  customGroupsClusterInit,
</#if><#if (SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  >
  customScenesClusterInit,
</#if><#if (ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "CLIENT")  >
  customOnOffClusterInit,
</#if><#if (LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  >
  customLevelControlClusterInit,
</#if><#if (COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  >
  customColorControlClusterInit,
</#if>
  customCommissioningClusterInit,
<#if (ALARMS_CLUSTER_ENABLE == true) && (ALARMS_CLUSTER_CS != "CLIENT")  >
  customAlarmsClusterInit,
</#if><#if (TIME_CLUSTER_ENABLE == true) && (TIME_CLUSTER_CS != "CLIENT")  >
  customTimeClusterInit,
</#if><#if (THERMOSTAT_CLUSTER_ENABLE == true) && (THERMOSTAT_CLUSTER_CS != "CLIENT")  >
  customThermostatClusterInit,
</#if><#if (FANCONTROL_CLUSTER_ENABLE == true) && (FANCONTROL_CLUSTER_CS != "CLIENT")  >
  customFanControlClusterInit,
</#if><#if (OCCUPANCYSENSING_CLUSTER_ENABLE == true) && (OCCUPANCYSENSING_CLUSTER_CS != "CLIENT")  >
  customOccupancySensingClusterInit,
</#if><#if (ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE == true) && (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT")  >
  customIlluminanceMeasurementClusterInit,
</#if><#if (TEMPERATUREMEASUREMENT_CLUSTER_ENABLE == true) && (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")  >
  customTemperatureMeasurementClusterInit,
</#if><#if (WATERCONTENTMEASUREMENT_CLUSTER_ENABLE == true) && (WATERCONTENTMEASUREMENT_CLUSTER_CS != "CLIENT")  >
  customHumidityMeasurementClusterInit,
</#if><#if (THERMOSTATUI_CLUSTER_ENABLE == true) && (THERMOSTATUI_CLUSTER_CS != "CLIENT")  >
  customThermostatUiConfClusterInit,
</#if><#if (IASZONE_CLUSTER_ENABLE == true) && (IASZONE_CLUSTER_CS != "CLIENT")  >
  customIasZoneClusterInit,
</#if><#if (IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  >
  customIasACEClusterInit,
</#if><#if (DIAGONSTICS_CLUSTER_ENABLE == true) && (DIAGONSTICS_CLUSTER_CS != "CLIENT")  >
  customDiagnosticsClusterInit
</#if>
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER") || (DEVICE == "BOTH") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${deviceTypeFunctionPrefix}${clusterName}Init,
  </#if>
  </#list>
};


ClusterId_t customServerClusterIds[CUSTOM_SERVER_CLUSTERS_COUNT] =
{
<#if (BASIC_CLUSTER_ENABLE == true) && (BASIC_CLUSTER_CS != "CLIENT")  >
  BASIC_CLUSTER_ID,
</#if><#if (IDENTIFY_CLUSTER_ENABLE == true) && (IDENTIFY_CLUSTER_CS != "CLIENT")  >
  IDENTIFY_CLUSTER_ID,
</#if><#if (GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "CLIENT")  >
  GROUPS_CLUSTER_ID,
</#if><#if (SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  >
  SCENES_CLUSTER_ID,
</#if><#if (ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "CLIENT")  >
  ONOFF_CLUSTER_ID,
</#if><#if (LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  >
  LEVEL_CONTROL_CLUSTER_ID,
</#if><#if (COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  >
  COLOR_CONTROL_CLUSTER_ID,
</#if>
  ZLL_COMMISSIONING_CLUSTER_ID,
<#if (THERMOSTAT_CLUSTER_ENABLE == true) && (THERMOSTAT_CLUSTER_CS != "CLIENT")  >
  THERMOSTAT_CLUSTER_ID,
</#if><#if (FANCONTROL_CLUSTER_ENABLE == true) && (FANCONTROL_CLUSTER_CS != "CLIENT")  >
  FAN_CONTROL_CLUSTER_ID,
</#if><#if (OCCUPANCYSENSING_CLUSTER_ENABLE == true) && (OCCUPANCYSENSING_CLUSTER_CS != "CLIENT")  >
  OCCUPANCY_SENSING_CLUSTER_ID,
</#if><#if (ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE == true) && (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT")  >
  ILLUMINANCE_MEASUREMENT_CLUSTER_ID,
</#if><#if (TEMPERATUREMEASUREMENT_CLUSTER_ENABLE == true) && (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")  >
  TEMPERATURE_MEASUREMENT_CLUSTER_ID,
</#if><#if (WATERCONTENTMEASUREMENT_CLUSTER_ENABLE == true) && (WATERCONTENTMEASUREMENT_CLUSTER_CS != "CLIENT")  >
  HUMIDITY_MEASUREMENT_CLUSTER_ID,
</#if><#if (THERMOSTATUI_CLUSTER_ENABLE == true) && (THERMOSTATUI_CLUSTER_CS != "CLIENT")  >
  THERMOSTAT_UI_CONF_CLUSTER_ID,
</#if><#if (IASZONE_CLUSTER_ENABLE == true) && (IASZONE_CLUSTER_CS != "CLIENT")  >
  IAS_ZONE_CLUSTER_ID,
</#if><#if (IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  >
  IAS_ACE_CLUSTER_ID,
</#if><#if (ALARMS_CLUSTER_ENABLE == true) && (ALARMS_CLUSTER_CS != "CLIENT")  >
  ALARMS_CLUSTER_ID,
</#if><#if (TIME_CLUSTER_ENABLE == true) && (TIME_CLUSTER_CS != "CLIENT")  >
  TIME_CLUSTER_ID,
</#if><#if (DIAGONSTICS_CLUSTER_ENABLE == true) && (DIAGONSTICS_CLUSTER_CS != "CLIENT")  >
  DIAGNOSTICS_CLUSTER_ID,
</#if>
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER") || (DEVICE == "BOTH") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${clusterName?upper_case}_CLUSTER_ID,
  </#if>
  </#list>
};

ZCL_Cluster_t customClientClusters[CUSTOM_CLIENT_CLUSTERS_COUNT] =
{
<#if (BASIC_CLUSTER_ENABLE == true) && (BASIC_CLUSTER_CS != "SERVER")  >
  ZCL_DEFINE_BASIC_CLUSTER_CLIENT(&customBasicClusterClientAttributes),
</#if><#if (IDENTIFY_CLUSTER_ENABLE == true) && (IDENTIFY_CLUSTER_CS != "SERVER")  >
  DEFINE_IDENTIFY_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customIdentifyClusterClientAttributes, &customIdentifyCommands),
</#if><#if (GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "SERVER")  >  
  DEFINE_GROUPS_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customGroupsClusterClientAttributes, &customGroupsCommands),
</#if><#if (ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "SERVER")  >
  DEFINE_ONOFF_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customOnOffClusterClientAttributes, &customOnOffCommands),
</#if><#if (LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "SERVER")  >
  DEFINE_LEVEL_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customLevelControlClusterClientAttributes, &customLevelControlCommands),
</#if><#if (COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "SERVER")  >
  DEFINE_COLOR_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customColorControlClusterClientAttributes, &customColorControlClusterClientCommands),
</#if><#if (SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  >
  DEFINE_SCENES_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customScenesClusterClientAttributes, &customScenesClientCommands),
</#if><#if (OCCUPANCYSENSING_CLUSTER_ENABLE == true) && (OCCUPANCYSENSING_CLUSTER_CS != "SERVER")  >
  DEFINE_OCCUPANCY_SENSING_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customOccupancySensingClusterClientAttributes, NULL),
</#if><#if (ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE == true) && (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "SERVER")  >
  DEFINE_ILLUMINANCE_MEASUREMENT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customIlluminanceMeasurementClusterClientAttributes), 
</#if><#if (WATERCONTENTMEASUREMENT_CLUSTER_ENABLE == true) && (WATERCONTENTMEASUREMENT_CLUSTER_CS != "SERVER")  >
  DEFINE_HUMIDITY_MEASUREMENT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customHumidityMeasurementClusterClientAttributes),
</#if><#if (TEMPERATUREMEASUREMENT_CLUSTER_ENABLE == true) && (TEMPERATUREMEASUREMENT_CLUSTER_CS != "SERVER")  >
  DEFINE_TEMPERATURE_MEASUREMENT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customTemperatureMeasurementClusterClientAttributes),
</#if>
  DEFINE_COMMISSIONING_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customCommissioningClusterClientAttributes, &customCommissioningClusterCommands),
<#if (THERMOSTAT_CLUSTER_ENABLE == true) && (THERMOSTAT_CLUSTER_CS != "SERVER")  >
  DEFINE_THERMOSTAT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customThermostatClusterClientAttributes, NULL),
</#if><#if (THERMOSTATUI_CLUSTER_ENABLE == true) && (THERMOSTATUI_CLUSTER_CS != "SERVER")  >
  DEFINE_THERMOSTAT_UI_CONF_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customThermostatUiConfClusterClientAttributes, NULL),
</#if><#if (ALARMS_CLUSTER_ENABLE == true) && (ALARMS_CLUSTER_CS != "SERVER")  >
  DEFINE_ALARMS_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customAlarmsClusterClientAttributes, &customAlarmsClusterClientCommands),
</#if><#if (FANCONTROL_CLUSTER_ENABLE == true) && (FANCONTROL_CLUSTER_CS != "SERVER")  >
  DEFINE_FAN_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customFanControlClusterClientAttributes, NULL),
</#if><#if (IASZONE_CLUSTER_ENABLE == true) && (IASZONE_CLUSTER_CS != "SERVER")  >
  DEFINE_IAS_ZONE_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customIasZoneClusterClientAttributes, &customIasZoneClusterClientCommands),
</#if><#if (IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  >
  DEFINE_IAS_ACE_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &customIasAceClusterClientAttributes , &customIasAceClusterClientCommands),
</#if><#if (TIME_CLUSTER_ENABLE == true) && (TIME_CLUSTER_CS != "SERVER")  >
  DEFINE_TIME_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, NULL),
</#if>
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT") || (DEVICE == "BOTH") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  DEFINE_${(clusterName)?upper_case}_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &${clusterName?lower_case}${"CLIENT"?capitalize}ClusterAttributes, &${clusterName?lower_case}ClusterCommands),
  </#if>
  </#list>
};


ClusterId_t customClientClusterIds[CUSTOM_CLIENT_CLUSTERS_COUNT] =
{
<#if (BASIC_CLUSTER_ENABLE == true) && (BASIC_CLUSTER_CS != "SERVER")  >
  BASIC_CLUSTER_ID,
</#if><#if (IDENTIFY_CLUSTER_ENABLE == true) && (IDENTIFY_CLUSTER_CS != "SERVER")  >
  IDENTIFY_CLUSTER_ID,
</#if><#if (GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "SERVER")  >
  GROUPS_CLUSTER_ID,
</#if><#if (SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  >
  SCENES_CLUSTER_ID,
</#if><#if (ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "SERVER")  >
  ONOFF_CLUSTER_ID,
</#if><#if (LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "SERVER")  >
  LEVEL_CONTROL_CLUSTER_ID,
</#if><#if (COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "SERVER")  >
  COLOR_CONTROL_CLUSTER_ID,
</#if>
  ZLL_COMMISSIONING_CLUSTER_ID,
<#if (THERMOSTAT_CLUSTER_ENABLE == true) && (THERMOSTAT_CLUSTER_CS != "SERVER")  >
  THERMOSTAT_CLUSTER_ID,
</#if><#if (FANCONTROL_CLUSTER_ENABLE == true) && (FANCONTROL_CLUSTER_CS != "SERVER")  >
  FAN_CONTROL_CLUSTER_ID,
</#if><#if (OCCUPANCYSENSING_CLUSTER_ENABLE == true) && (OCCUPANCYSENSING_CLUSTER_CS != "SERVER")  >
  OCCUPANCY_SENSING_CLUSTER_ID,
</#if><#if (ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE == true) && (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "SERVER")  >
  ILLUMINANCE_MEASUREMENT_CLUSTER_ID,
</#if><#if (TEMPERATUREMEASUREMENT_CLUSTER_ENABLE == true) && (TEMPERATUREMEASUREMENT_CLUSTER_CS != "SERVER")  >
  TEMPERATURE_MEASUREMENT_CLUSTER_ID,
</#if><#if (WATERCONTENTMEASUREMENT_CLUSTER_ENABLE == true) && (WATERCONTENTMEASUREMENT_CLUSTER_CS != "SERVER")  >
  HUMIDITY_MEASUREMENT_CLUSTER_ID,
</#if><#if (THERMOSTATUI_CLUSTER_ENABLE == true) && (THERMOSTATUI_CLUSTER_CS != "SERVER")  >
  THERMOSTAT_UI_CONF_CLUSTER_ID,
</#if><#if (IASZONE_CLUSTER_ENABLE == true) && (IASZONE_CLUSTER_CS != "SERVER")  >
  IAS_ZONE_CLUSTER_ID,
</#if><#if (IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  >
  IAS_ACE_CLUSTER_ID,
</#if><#if (ALARMS_CLUSTER_ENABLE == true) && (ALARMS_CLUSTER_CS != "SERVER")  >
  ALARMS_CLUSTER_ID,
</#if><#if (TIME_CLUSTER_ENABLE == true) && (TIME_CLUSTER_CS != "SERVER")  >
  TIME_CLUSTER_ID,
</#if>
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT") || (DEVICE == "BOTH") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${clusterName?upper_case}_CLUSTER_ID,
  </#if>
  </#list>
};

void (*customClientClusterInitFunctions[CUSTOM_CLIENT_CLUSTER_INIT_COUNT])() =
{
<#if (BASIC_CLUSTER_ENABLE == true) && (BASIC_CLUSTER_CS != "SERVER")  >
  customBasicClusterInit,
</#if><#if (IDENTIFY_CLUSTER_ENABLE == true) && (IDENTIFY_CLUSTER_CS != "SERVER")  >
  customIdentifyClusterInit,
</#if><#if (GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "SERVER")  >  
  customGroupsClusterInit,
</#if><#if (SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  >
  customScenesClusterInit,
</#if><#if (ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "SERVER")  >
  customOnOffClusterInit,
</#if><#if (LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "SERVER")  >
  customLevelControlClusterInit,
</#if><#if (COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "SERVER")  >
  customColorControlClusterInit,
</#if>
  customCommissioningClusterInit,
<#if (ALARMS_CLUSTER_ENABLE == true) && (ALARMS_CLUSTER_CS != "SERVER")  >
  customAlarmsClusterInit,
</#if><#if (TIME_CLUSTER_ENABLE == true) && (TIME_CLUSTER_CS != "SERVER")  >
  customTimeClusterInit,
</#if><#if (THERMOSTAT_CLUSTER_ENABLE == true) && (THERMOSTAT_CLUSTER_CS != "SERVER")  >
  customThermostatClusterInit,
</#if><#if (FANCONTROL_CLUSTER_ENABLE == true) && (FANCONTROL_CLUSTER_CS != "SERVER")  >
  customFanControlClusterInit,
</#if><#if (OCCUPANCYSENSING_CLUSTER_ENABLE == true) && (OCCUPANCYSENSING_CLUSTER_CS != "SERVER")  >
  customOccupancySensingClusterInit,
</#if><#if (ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE == true) && (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "SERVER")  >
  customIlluminanceMeasurementClusterInit,
</#if><#if (TEMPERATUREMEASUREMENT_CLUSTER_ENABLE == true) && (TEMPERATUREMEASUREMENT_CLUSTER_CS != "SERVER")  >
  customTemperatureMeasurementClusterInit,
</#if><#if (WATERCONTENTMEASUREMENT_CLUSTER_ENABLE == true) && (WATERCONTENTMEASUREMENT_CLUSTER_CS != "SERVER")  >
  customHumidityMeasurementClusterInit,
</#if><#if (THERMOSTATUI_CLUSTER_ENABLE == true) && (THERMOSTATUI_CLUSTER_CS != "SERVER")  >
  customThermostatUiConfClusterInit,
</#if><#if (IASZONE_CLUSTER_ENABLE == true) && (IASZONE_CLUSTER_CS != "SERVER")  >
  customIasZoneClusterInit,
</#if><#if (IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  >
  customIasACEClusterInit,
</#if>
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT") || (DEVICE == "BOTH") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${deviceTypeFunctionPrefix}${clusterName}Init,
  </#if>
  </#list>
};


#endif // #if APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_CUSTOM_DEVICE

// eof customClusters.c
