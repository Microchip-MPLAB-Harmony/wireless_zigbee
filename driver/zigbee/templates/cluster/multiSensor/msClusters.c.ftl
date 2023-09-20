/*******************************************************************************
  Multi-Sensor clusters Source File

  Company:
    Microchip Technology Inc.

  File Name:
    msClusters.c

  Summary:
    This file contains Multi-Sensor clusters interface.

  Description:
    This file contains Multi-Sensor clusters interface.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_MULTI_SENSOR)

/******************************************************************************
                    Includes section
******************************************************************************/
#include <z3device/multiSensor/include/msClusters.h>
#include <z3device/clusters/include/basicCluster.h>
#include <zcl/clusters/include/identifyCluster.h>
#include <z3device/multiSensor/include/osOccupancySensingCluster.h>
#include <z3device/multiSensor/include/lsIlluminanceMeasurementCluster.h>
#include <z3device/multiSensor/include/tsTemperatureMeasurementCluster.h>
#include <z3device/multiSensor/include/hsHumidityMeasurementCluster.h>
#include <z3device/multiSensor/include/osBasicCluster.h>
#include <z3device/multiSensor/include/osIdentifyCluster.h>
#include <z3device/multiSensor/include/osGroupsCluster.h>
#include <z3device/multiSensor/include/lsBasicCluster.h>
#include <z3device/multiSensor/include/lsIdentifyCluster.h>
#include <z3device/multiSensor/include/lsGroupsCluster.h>
#include <z3device/multiSensor/include/tsBasicCluster.h>
#include <z3device/multiSensor/include/tsIdentifyCluster.h>
#include <z3device/multiSensor/include/tsGroupsCluster.h>
#include <z3device/multiSensor/include/hsBasicCluster.h>
#include <z3device/multiSensor/include/hsIdentifyCluster.h>
#include <z3device/multiSensor/include/hsGroupsCluster.h>

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

#ifdef OTAU_CLIENT
ClusterId_t msClientClusterIds[MS_CLIENT_CLUSTERS_COUNT] =
{
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${clusterName?upper_case}_CLUSTER_ID,
  </#if>
  </#list>
  OTAU_CLUSTER_ID, // Always should be on last position in list of clusters ID.
};

void (*msClientClusterInitFunctions[MS_CLIENT_CLUSTER_INIT_COUNT])() =
{
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${deviceTypeFunctionPrefix}${clusterName}Init,
  </#if>
  </#list>
  NULL // needs to add otau client init
};

ZCL_Cluster_t msClientClusters[MS_CLIENT_CLUSTERS_COUNT] = 
{
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  DEFINE_${(clusterName)?upper_case}_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &${clusterName?lower_case}${DEVICE?capitalize}ClusterAttributes, &${clusterName?lower_case}${DEVICE?capitalize}ClusterCommands),
  </#if>
  </#list>
};

#endif //OTAU_CLIENT

#ifdef APP_SENSOR_TYPE_OCCUPANCY_SENSOR
ZCL_Cluster_t osServerClusters[OS_SERVER_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER(&osBasicClusterServerAttributes, &osBasicClusterServerCommands),
  DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &osIdentifyClusterServerAttributes, &osIdentifyCommands),
  DEFINE_OCCUPANCY_SENSING_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &osOccupancySensingClusterServerAttributes, NULL),  
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  DEFINE_${(clusterName)?upper_case}_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &${clusterName?lower_case}${DEVICE?capitalize}ClusterAttributes, &${clusterName?lower_case}${DEVICE?capitalize}ClusterCommands),
  </#if>
  </#list>
};

ClusterId_t osServerClusterIds[OS_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  OCCUPANCY_SENSING_CLUSTER_ID,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${clusterName?upper_case}_CLUSTER_ID,
  </#if>
  </#list>
};

ZCL_Cluster_t osClientClusters[OS_CLIENT_CLUSTERS_COUNT] =
{
  DEFINE_IDENTIFY_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &osIdentifyClusterClientAttributes, &osIdentifyCommands),
  DEFINE_GROUPS_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &osGroupsClusterClientAttributes, &osGroupsCommands),
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  DEFINE_${(clusterName)?upper_case}_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &${clusterName?lower_case}${DEVICE?capitalize}ClusterAttributes, &${clusterName?lower_case}${DEVICE?capitalize}ClusterCommands),
  </#if>
  </#list>
};

ClusterId_t osClientClusterIds[OS_CLIENT_CLUSTERS_COUNT] =
{
  IDENTIFY_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${clusterName?upper_case}_CLUSTER_ID,
  </#if>
  </#list>
};

void (*osClientClusterInitFunctions[OS_CLIENT_CLUSTERS_COUNT])() =
{
  osIdentifyClusterInit,
  osGroupsClusterInit,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${deviceTypeFunctionPrefix}${clusterName}Init,
  </#if>
  </#list>
};

void (*osServerClusterInitFunctions[OS_SERVER_CLUSTERS_COUNT])() =
{
  osBasicClusterInit,
  osIdentifyClusterInit,
  occupancySensingClusterInit,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${deviceTypeFunctionPrefix}${clusterName}Init,
  </#if>
  </#list>
};

#endif //APP_SENSOR_TYPE_OCCUPANCY_SENSOR


#ifdef APP_SENSOR_TYPE_LIGHT_SENSOR
ZCL_Cluster_t lsServerClusters[LS_SERVER_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER(&lsBasicClusterServerAttributes, &lsBasicClusterServerCommands),
  DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &lsIdentifyClusterServerAttributes, &lsIdentifyCommands),
  DEFINE_ILLUMINANCE_MEASUREMENT_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &lsIlluminanceMeasurementClusterServerAttributes),
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  DEFINE_${(clusterName)?upper_case}_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &${clusterName?lower_case}${DEVICE?capitalize}ClusterAttributes, &${clusterName?lower_case}${DEVICE?capitalize}ClusterCommands),
  </#if>
  </#list>
};

ClusterId_t lsServerClusterIds[LS_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  ILLUMINANCE_MEASUREMENT_CLUSTER_ID,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${clusterName?upper_case}_CLUSTER_ID,
  </#if>
  </#list>
};

void (*lsServerClusterInitFunctions[LS_SERVER_CLUSTERS_COUNT])() =
{
  lsBasicClusterInit,
  lsIdentifyClusterInit,
  illuminanceMeasurementClusterInit,
    <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${deviceTypeFunctionPrefix}${clusterName}Init,
  </#if>
  </#list>
};

ZCL_Cluster_t lsClientClusters[LS_CLIENT_CLUSTERS_COUNT] =
{
  DEFINE_IDENTIFY_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &lsIdentifyClusterClientAttributes, &lsIdentifyCommands),
  DEFINE_GROUPS_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &lsGroupsClusterClientAttributes, &lsGroupsCommands),
    <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  DEFINE_${(clusterName)?upper_case}_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &${clusterName?lower_case}${DEVICE?capitalize}ClusterAttributes, &${clusterName?lower_case}${DEVICE?capitalize}ClusterCommands),
  </#if>
  </#list>
};

ClusterId_t lsClientClusterIds[LS_CLIENT_CLUSTERS_COUNT] =
{
  IDENTIFY_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${clusterName?upper_case}_CLUSTER_ID,
  </#if>
  </#list>
};

void (*lsClientClusterInitFunctions[LS_CLIENT_CLUSTERS_COUNT])() =
{
  lsIdentifyClusterInit,
  lsGroupsClusterInit,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${deviceTypeFunctionPrefix}${clusterName}Init,
  </#if>
  </#list>
};

#endif //APP_SENSOR_TYPE_LIGHT_SENSOR

#ifdef APP_SENSOR_TYPE_TEMPERATURE_SENSOR
ZCL_Cluster_t tsServerClusters[TS_SERVER_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER(&tsBasicClusterServerAttributes, &tsBasicClusterServerCommands),
  DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &tsIdentifyClusterServerAttributes, &tsIdentifyCommands),
  DEFINE_TEMPERATURE_MEASUREMENT_CLUSTER(ZCL_SERVER_CLUSTER_TYPE,&tsTemperatureMeasurementClusterServerAttributes),
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  DEFINE_${(clusterName)?upper_case}_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &${clusterName?lower_case}${DEVICE?capitalize}ClusterAttributes, &${clusterName?lower_case}${DEVICE?capitalize}ClusterCommands),
  </#if>
  </#list>
};

ClusterId_t tsServerClusterIds[TS_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
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

ZCL_Cluster_t tsClientClusters[TS_CLIENT_CLUSTERS_COUNT] =
{
  DEFINE_IDENTIFY_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &tsIdentifyClusterClientAttributes, &tsIdentifyCommands),
  DEFINE_GROUPS_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &tsGroupsClusterClientAttributes, &tsGroupsCommands),
    <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  DEFINE_${(clusterName)?upper_case}_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &${clusterName?lower_case}${DEVICE?capitalize}ClusterAttributes, &${clusterName?lower_case}${DEVICE?capitalize}ClusterCommands),
  </#if>
  </#list>
};

ClusterId_t tsClientClusterIds[TS_CLIENT_CLUSTERS_COUNT] =
{
  IDENTIFY_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${clusterName?upper_case}_CLUSTER_ID,
  </#if>
  </#list>
};

void (*tsClientClusterInitFunctions[TS_CLIENT_CLUSTERS_COUNT])() =
{
  tsIdentifyClusterInit,
  tsGroupsClusterInit,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${deviceTypeFunctionPrefix}${clusterName}Init,
  </#if>
  </#list>
};

void (*tsServerClusterInitFunctions[TS_SERVER_CLUSTERS_COUNT])() =
{
  tsBasicClusterInit,
  tsIdentifyClusterInit,
  temperatureMeasurementClusterInit,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${deviceTypeFunctionPrefix}${clusterName}Init,
  </#if>
  </#list>
};

#endif //APP_SENSOR_TYPE_TEMPERATURE_SENSOR

#ifdef APP_SENSOR_TYPE_HUMIDITY_SENSOR
ZCL_Cluster_t hsServerClusters[HS_SERVER_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER(&hsBasicClusterServerAttributes, &hsBasicClusterServerCommands),
  DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &hsIdentifyClusterServerAttributes, &hsIdentifyCommands),
  DEFINE_HUMIDITY_MEASUREMENT_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &hsHumidityMeasurementClusterServerAttributes),
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  DEFINE_${(clusterName)?upper_case}_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &${clusterName?lower_case}${DEVICE?capitalize}ClusterAttributes, &${clusterName?lower_case}${DEVICE?capitalize}ClusterCommands),
  </#if>
  </#list>
};

ClusterId_t hsServerClusterIds[HS_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  HUMIDITY_MEASUREMENT_CLUSTER_ID,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${clusterName?upper_case}_CLUSTER_ID,
  </#if>
  </#list>
};

ZCL_Cluster_t hsClientClusters[HS_CLIENT_CLUSTERS_COUNT] =
{
  DEFINE_IDENTIFY_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &hsIdentifyClusterClientAttributes, &hsIdentifyCommands),
  DEFINE_GROUPS_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &hsGroupsClusterClientAttributes, &hsGroupsCommands),
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  DEFINE_${(clusterName)?upper_case}_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &${clusterName?lower_case}${DEVICE?capitalize}ClusterAttributes, &${clusterName?lower_case}${DEVICE?capitalize}ClusterCommands),
  </#if>
  </#list>
};

ClusterId_t hsClientClusterIds[HS_CLIENT_CLUSTERS_COUNT] =
{
  IDENTIFY_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${clusterName?upper_case}_CLUSTER_ID,
  </#if>
  </#list>
};

void (*hsClientClusterInitFunctions[HS_CLIENT_CLUSTERS_COUNT])() =
{
  hsIdentifyClusterInit,
  hsGroupsClusterInit,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${deviceTypeFunctionPrefix}${clusterName}Init,
  </#if>
  </#list>
};

void (*hsServerClusterInitFunctions[HS_SERVER_CLUSTERS_COUNT])() =
{
  hsBasicClusterInit,
  hsIdentifyClusterInit,
  humidityMeasurementClusterInit,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER")  >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${deviceTypeFunctionPrefix}${clusterName}Init,
  </#if>
  </#list>
};

#endif //APP_SENSOR_TYPE_HUMIDITY_SENSOR

#endif // APP_DEVICE_TYPE_MULTI_SENSOR

// eof msClusters.c
