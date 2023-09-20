/*******************************************************************************
  Thermostat clusters Source File

  Company:
    Microchip Technology Inc.

  File Name:
   thClusters.c

  Summary:
    This file contains the Thermostat clusters interface.

  Description:
    This file contains the Thermostat clusters interface.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_THERMOSTAT)
/******************************************************************************
                    Includes section
******************************************************************************/
#include <z3device/thermostat/include/thClusters.h>
#include <z3device/clusters/include/basicCluster.h>
#include <zcl/clusters/include/identifyCluster.h>
#include <z3device/thermostat/include/thBasicCluster.h>
#include <z3device/thermostat/include/thIdentifyCluster.h>
#include <z3device/thermostat/include/thThermostatCluster.h>
#include <z3device/thermostat/include/thThermostatUiConfCluster.h>
#include <z3device/thermostat/include/thOccupancySensingCluster.h>
#include <z3device/thermostat/include/thFanControlCluster.h>
#include <z3device/thermostat/include/thAlarmsCluster.h>
#include <z3device/thermostat/include/thHumidityMeasurementCluster.h>
#include <z3device/thermostat/include/thGroupsCluster.h>
#include <z3device/thermostat/include/thScenesCluster.h>
#include <z3device/thermostat/include/thTemperatureMeasurementCluster.h>
#include <zcl/include/zclTimeCluster.h>
#include <z3device/thermostat/include/thTimeCluster.h>

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
ZCL_Cluster_t thServerClusters[TH_SERVER_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER(&thBasicClusterServerAttributes, &thBasicClusterServerCommands),
  DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &thIdentifyClusterServerAttributes, &thIdentifyCommands),
  DEFINE_THERMOSTAT_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &thThermostatClusterServerAttributes, &thThermostatClusterServerCommands),
  DEFINE_THERMOSTAT_UI_CONF_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &thThermostatUiConfClusterServerAttributes, NULL),
  DEFINE_OCCUPANCY_SENSING_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &thOccupancySensingClusterServerAttributes, NULL),
  DEFINE_ALARMS_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &thAlarmsClusterServerAttributes, &thAlarmsClusterServerCommands),
  DEFINE_HUMIDITY_MEASUREMENT_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &thHumidityMeasurementClusterServerAttributes),
  DEFINE_FAN_CONTROL_CLUSTER(ZCL_SERVER_CLUSTER_TYPE,&thFanControlClusterServerAttributes,NULL),
  DEFINE_GROUPS_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &thGroupsClusterServerAttributes, &thGroupsCommands),
  DEFINE_SCENES_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &thScenesClusterServerAttributes, &thScenesCommands),
  DEFINE_TEMPERATURE_MEASUREMENT_CLUSTER(ZCL_SERVER_CLUSTER_TYPE,&thTemperatureMeasurementClusterServerAttributes),
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  DEFINE_${(clusterName)?upper_case}_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &${clusterName?lower_case}${DEVICE?capitalize}ClusterAttributes, &${clusterName?lower_case}${DEVICE?capitalize}ClusterCommands),
  </#if>
  </#list>
};

void (*thServerClusterInitFunctions[TH_SERVER_CLUSTER_INIT_COUNT])() =
{
  thBasicClusterInit,
  thIdentifyClusterInit,
  thThermostatClusterInit,
  thThermostatUiConfClusterInit,
  thOccupancySensingClusterInit,
  thAlarmsClusterInit,
  thHumidityMeasurementClusterInit,
  thFanControlClusterInit,
  thGroupsClusterInit,
  thScenesClusterInit,
  thTemperatureMeasurementClusterInit,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${deviceTypeFunctionPrefix}${clusterName}Init,
  </#if>
  </#list>
};

ClusterId_t thServerClusterIds[TH_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  THERMOSTAT_CLUSTER_ID,
  THERMOSTAT_UI_CONF_CLUSTER_ID,
  OCCUPANCY_SENSING_CLUSTER_ID,
  ALARMS_CLUSTER_ID,
  HUMIDITY_MEASUREMENT_CLUSTER_ID,
  FAN_CONTROL_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  SCENES_CLUSTER_ID,
  TEMPERATURE_MEASUREMENT_CLUSTER_ID,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${clusterName?upper_case}_CLUSTER_ID,
  </#if>
  </#list>
};

ZCL_Cluster_t thClientClusters[TH_CLIENT_CLUSTERS_COUNT] = 
{
  DEFINE_IDENTIFY_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &thIdentifyClusterClientAttributes, &thIdentifyCommands),
  DEFINE_OCCUPANCY_SENSING_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &thOccupancySensingClusterClientAttributes, NULL),
  DEFINE_TIME_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, NULL),
  DEFINE_HUMIDITY_MEASUREMENT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE,&thHumidityMeasurementClusterClientAttributes),
  DEFINE_TEMPERATURE_MEASUREMENT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &thTemperatureMeasurementClusterClientAttributes),
  DEFINE_FAN_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &thFanControlClusterClientAttributes, NULL),
  DEFINE_THERMOSTAT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, NULL),
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  DEFINE_${(clusterName)?upper_case}_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &${clusterName?lower_case}${DEVICE?capitalize}ClusterAttributes, &${clusterName?lower_case}${DEVICE?capitalize}ClusterCommands),
  </#if>
  </#list>
};

ClusterId_t thClientClusterIds[TH_CLIENT_CLUSTERS_COUNT] =
{
  IDENTIFY_CLUSTER_ID,
  OCCUPANCY_SENSING_CLUSTER_ID,
  TIME_CLUSTER_ID,
  HUMIDITY_MEASUREMENT_CLUSTER_ID,
  TEMPERATURE_MEASUREMENT_CLUSTER_ID,
  FAN_CONTROL_CLUSTER_ID,
  THERMOSTAT_CLUSTER_ID,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${clusterName?upper_case}_CLUSTER_ID,
  </#if>
  </#list>
#ifdef OTAU_CLIENT
  OTAU_CLUSTER_ID, // Always should be on last position in list of clusters ID.
#endif
};

void (*thClientClusterInitFunctions[TH_CLIENT_CLUSTER_INIT_COUNT])() =
{
  thIdentifyClusterInit,
  thOccupancySensingClusterInit,
  thTimeCluserInit,
  thHumidityMeasurementClusterInit,
  thTemperatureMeasurementClusterInit,
  thFanControlClusterInit,
  thThermostatClusterInit,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${deviceTypeFunctionPrefix}${clusterName}Init,
  </#if>
  </#list>
#ifdef OTAU_CLIENT
  NULL, // Always should be on last position in list of clusters ID.
#endif
};

#endif // APP_DEVICE_TYPE_THERMOSTAT

// eof thClusters.c