/*******************************************************************************
  Combined Interface clusters Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ciClusters.h

  Summary:
    This file contains the Combined Interface clusters interface.

  Description:
    This file contains the Combined Interface clusters interface.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_COMBINED_INTERFACE)
/******************************************************************************
                    Includes section
******************************************************************************/
#include <z3device/clusters/include/haClusters.h>
#include <z3device/combinedInterface/include/ciClusters.h>
#include <z3device/clusters/include/basicCluster.h>
#include <zcl/clusters/include/identifyCluster.h>
#include <z3device/combinedInterface/include/ciBasicCluster.h>
#include <z3device/combinedInterface/include/ciIdentifyCluster.h>
<#if (ONOFF_CLUSTER_ENABLE == true) >
#include <z3device/combinedInterface/include/ciOnOffCluster.h>
</#if><#if (LEVELCONTROL_CLUSTER_ENABLE == true) >
#include <z3device/combinedInterface/include/ciLevelControlCluster.h>
</#if>
#include <z3device/combinedInterface/include/ciGroupsCluster.h>
<#if (SCENES_CLUSTER_ENABLE == true) >
#include <z3device/combinedInterface/include/ciScenesCluster.h>
</#if><#if (OCCUPANCYSENSING_CLUSTER_ENABLE == true) >
#include <z3device/combinedInterface/include/ciOccupancySensingCluster.h>
</#if>
#include <z3device/combinedInterface/include/ciCommissioningCluster.h>
<#if (ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE == true) >
#include <z3device/combinedInterface/include/ciIlluminanceMeasurementCluster.h>
</#if><#if (WATERCONTENTMEASUREMENT_CLUSTER_ENABLE == true) >
#include <z3device/combinedInterface/include/ciHumidityMeasurementCluster.h>
</#if><#if (TEMPERATUREMEASUREMENT_CLUSTER_ENABLE == true) >
#include <z3device/combinedInterface/include/ciTemperatureMeasurementCluster.h>
</#if><#if (COLORCONTROL_CLUSTER_ENABLE == true) >
#include <z3device/combinedInterface/include/ciColorControlCluster.h>
</#if><#if (THERMOSTAT_CLUSTER_ENABLE == true) >
#include <z3device/combinedInterface/include/ciThermostatCluster.h>
</#if><#if (FANCONTROL_CLUSTER_ENABLE == true) >
#include <z3device/combinedInterface/include/ciFanControlCluster.h>
</#if><#if (TIME_CLUSTER_ENABLE == true) >
#include <z3device/combinedInterface/include/ciTimeCluster.h>
</#if><#if (ALARMS_CLUSTER_ENABLE == true) >
#include <z3device/combinedInterface/include/ciAlarmsCluster.h>
</#if><#if (THERMOSTATUI_CLUSTER_ENABLE == true) >
#include <z3device/combinedInterface/include/ciThermostatUiConfCluster.h>
</#if><#if (IASZONE_CLUSTER_ENABLE == true) >
#include <z3device/combinedInterface/include/ciIasZoneCluster.h>
</#if><#if (IASACE_CLUSTER_ENABLE == true) >
#include <z3device/combinedInterface/include/ciIasACECluster.h>
</#if>

<#compress>
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>

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
ZCL_Cluster_t ciServerClusters[CI_SERVER_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER(&ciBasicClusterServerAttributes, &ciBasicClusterServerCommands),
  DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &ciIdentifyClusterServerAttributes, &ciIdentifyCommands),
  DEFINE_GROUPS_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &ciGroupsClusterServerAttributes, &ciGroupsCommands),
  <#if (IASACE_CLUSTER_ENABLE == true) >
  DEFINE_IAS_ACE_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &ciIasACEAceClusterServerAttributes, &ciIASACEClusterCommands),
  </#if>
     // Optional
  DEFINE_COMMISSIONING_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &ciCommissioningClusterServerAttributes, &ciCommissioningClusterCommands),
  <#if (TIME_CLUSTER_ENABLE == true) >
  DEFINE_TIME_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &ciTimeClusterServerAttributes, NULL),
  </#if>
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER") || (DEVICE == "BOTH") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  DEFINE_${(clusterName)?upper_case}_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &${clusterName?lower_case}${"SERVER"?capitalize}ClusterAttributes, &${clusterName?lower_case}ClusterCommands),
  </#if>
  </#list>
};

void (*ciServerClusterInitFunctions[CI_SERVER_CLUSTER_INIT_COUNT])() =
{
  ciBasicClusterInit,
  ciIdentifyClusterInit,
  ciGroupsClusterInit,
  <#if (IASACE_CLUSTER_ENABLE == true) >
  ciIasACEClusterInit,
  </#if>
    // Optional
  ciCommissioningClusterInit,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER") || (DEVICE == "BOTH") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${deviceTypeFunctionPrefix}${clusterName}Init,
  </#if>
  </#list>
};

ZCL_Cluster_t ciClientClusters[CI_CLIENT_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_CLIENT(&ciBasicClusterClientAttributes),
  DEFINE_IDENTIFY_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &ciIdentifyClusterClientAttributes, &ciIdentifyCommands),
  <#if (ONOFF_CLUSTER_ENABLE == true) >
  DEFINE_ONOFF_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &ciOnOffClusterClientAttributes, &ciOnOffCommands),
  </#if><#if (LEVELCONTROL_CLUSTER_ENABLE == true) >
  DEFINE_LEVEL_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &ciOnOffClusterClientAttributes, &ciLevelControlCommands),
  </#if>
  DEFINE_GROUPS_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &ciGroupsClusterClientAttributes, &ciGroupsCommands),
  <#if (SCENES_CLUSTER_ENABLE == true) >
  DEFINE_SCENES_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &ciScenesClusterClientAttributes, &ciScenesCommands),
  </#if><#if (OCCUPANCYSENSING_CLUSTER_ENABLE == true) >
  DEFINE_OCCUPANCY_SENSING_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &ciOccupancySensingClusterClientAttributes, NULL),
  </#if><#if (ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE == true) >
  DEFINE_ILLUMINANCE_MEASUREMENT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &ciIlluminanceMeasurementClusterClientAttributes), 
  </#if><#if (WATERCONTENTMEASUREMENT_CLUSTER_ENABLE == true) >
  DEFINE_HUMIDITY_MEASUREMENT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &ciHumidityMeasurementClusterClientAttributes),
  </#if><#if (TEMPERATUREMEASUREMENT_CLUSTER_ENABLE == true) >
  DEFINE_TEMPERATURE_MEASUREMENT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &ciTemperatureMeasurementClusterClientAttributes),
  </#if>
  DEFINE_COMMISSIONING_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &ciCommissioningClusterClientAttributes, &ciCommissioningClusterCommands),
  <#if (COLORCONTROL_CLUSTER_ENABLE == true) >
  DEFINE_COLOR_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &ciColorControlClusterClientAttributes, &ciColorControlCommands),
  </#if><#if (THERMOSTAT_CLUSTER_ENABLE == true) >
  DEFINE_THERMOSTAT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &ciThermostatClusterClientAttributes, NULL),
  </#if><#if (THERMOSTATUI_CLUSTER_ENABLE == true) >
  DEFINE_THERMOSTAT_UI_CONF_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &ciThermostatUiConfClusterClientAttributes, NULL),
  </#if><#if (ALARMS_CLUSTER_ENABLE == true) >
  DEFINE_ALARMS_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &ciAlarmsClusterClientAttributes, &ciAlarmsCommands),
  </#if><#if (FANCONTROL_CLUSTER_ENABLE == true) >
  DEFINE_FAN_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &ciFanControlClusterClientAttributes, NULL),
  </#if><#if (IASZONE_CLUSTER_ENABLE == true) >
  DEFINE_IAS_ZONE_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &ciZoneClusterClientAttributes, &ciIASZoneClusterClientCommands),
  </#if>
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT") || (DEVICE == "BOTH") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  DEFINE_${(clusterName)?upper_case}_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &${clusterName?lower_case}${"CLIENT"?capitalize}ClusterAttributes, &${clusterName?lower_case}ClusterCommands),
  </#if>
  </#list> 
};

ClusterId_t   ciServerClusterIds[CI_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  <#if (IASACE_CLUSTER_ENABLE == true) >
  IAS_ACE_CLUSTER_ID,
  </#if>
  // Optional
  ZLL_COMMISSIONING_CLUSTER_ID,
  <#if (TIME_CLUSTER_ENABLE == true) >
  TIME_CLUSTER_ID,
  </#if>
#ifdef OTAU_SERVER
  OTAU_CLUSTER_ID, // Always should be on last position in list of clusters ID.
#endif // OTAU_SERVER
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER") || (DEVICE == "BOTH") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >  
  ${clusterName?upper_case}_CLUSTER_ID,
  </#if>
  </#list>
};

ClusterId_t   ciClientClusterIds[CI_CLIENT_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  <#if (ONOFF_CLUSTER_ENABLE == true) >
  ONOFF_CLUSTER_ID,
  </#if><#if (LEVELCONTROL_CLUSTER_ENABLE == true) >
  LEVEL_CONTROL_CLUSTER_ID,
  </#if>
  GROUPS_CLUSTER_ID,
  <#if (SCENES_CLUSTER_ENABLE == true) >
  SCENES_CLUSTER_ID,
  </#if><#if (OCCUPANCYSENSING_CLUSTER_ENABLE == true) >
  OCCUPANCY_SENSING_CLUSTER_ID,
  </#if><#if (ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE == true) >
  ILLUMINANCE_MEASUREMENT_CLUSTER_ID,
  </#if><#if (TEMPERATUREMEASUREMENT_CLUSTER_ENABLE == true) >
  TEMPERATURE_MEASUREMENT_CLUSTER_ID,
  </#if><#if (WATERCONTENTMEASUREMENT_CLUSTER_ENABLE == true) >
  HUMIDITY_MEASUREMENT_CLUSTER_ID,
  </#if>
  ZLL_COMMISSIONING_CLUSTER_ID,
  <#if (COLORCONTROL_CLUSTER_ENABLE == true) >
  COLOR_CONTROL_CLUSTER_ID,
  </#if><#if (THERMOSTAT_CLUSTER_ENABLE == true) >
  THERMOSTAT_CLUSTER_ID,
  </#if><#if (THERMOSTATUI_CLUSTER_ENABLE == true) >
  THERMOSTAT_UI_CONF_CLUSTER_ID,
  </#if><#if (ALARMS_CLUSTER_ENABLE == true) >
  ALARMS_CLUSTER_ID,
  </#if><#if (FANCONTROL_CLUSTER_ENABLE == true) >
  FAN_CONTROL_CLUSTER_ID,
  </#if><#if (IASZONE_CLUSTER_ENABLE == true) >
  IAS_ZONE_CLUSTER_ID,
  </#if>
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT") || (DEVICE == "BOTH") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >  
  ${clusterName?upper_case}_CLUSTER_ID,
  </#if>
  </#list>
};

void (*ciClientClusterInitFunctions[CI_CLIENT_CLUSTER_INIT_COUNT])() =
{
  ciBasicClusterInit,
  ciIdentifyClusterInit,
  <#if (ONOFF_CLUSTER_ENABLE == true) >
  ciOnOffClusterInit,
  </#if><#if (LEVELCONTROL_CLUSTER_ENABLE == true) >
  ciLevelControlClusterInit,
  </#if>
  ciGroupsClusterInit,
  <#if (SCENES_CLUSTER_ENABLE == true) >
  ciScenesClusterInit,
  </#if><#if (OCCUPANCYSENSING_CLUSTER_ENABLE == true) >
  ciOccupancySensingClusterInit,
  </#if><#if (ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE == true) >
  ciIlluminanceMeasurementClusterInit,
  </#if><#if (TEMPERATUREMEASUREMENT_CLUSTER_ENABLE == true) >
  ciTemperatureMeasurementClusterInit,
  </#if><#if (WATERCONTENTMEASUREMENT_CLUSTER_ENABLE == true) >
  ciHumidityMeasurementClusterInit,
  </#if>
  ciCommissioningClusterInit,
  <#if (COLORCONTROL_CLUSTER_ENABLE == true) >
  ciColorControlClusterInit,
  </#if><#if (THERMOSTAT_CLUSTER_ENABLE == true) >
  ciThermostatClusterInit,
  </#if><#if (THERMOSTATUI_CLUSTER_ENABLE == true) >
  ciThermostatUiConfClusterInit,
  </#if><#if (ALARMS_CLUSTER_ENABLE == true) >
  ciAlarmsClusterInit,
  </#if><#if (FANCONTROL_CLUSTER_ENABLE == true) >
  ciFanControlClusterInit,
  </#if><#if (IASZONE_CLUSTER_ENABLE == true) >
  ciIasZoneClusterInit,
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
#endif // APP_DEVICE_TYPE_COMBINED_INTERFACE

// eof ciClusters.c
