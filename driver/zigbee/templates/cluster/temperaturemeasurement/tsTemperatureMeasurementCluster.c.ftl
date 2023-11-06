/*******************************************************************************
  Temperature Measurement Sensor Source File

  Company:
    Microchip Technology Inc.

  File Name:
    tsTemperatureMeasurementCluster.c

  Summary:
    This file contains the Temperature Measurement Sensor Cluster.

  Description:
    This file contains the Temperature Measurement Sensor Cluster.
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
#ifdef APP_SENSOR_TYPE_TEMPERATURE_SENSOR

/******************************************************************************
                    Includes section
******************************************************************************/
#include <z3device/clusters/include/haClusters.h>
#include <pds/include/wlPdsMemIds.h>
#include <z3device/common/include/z3Device.h>
#include <zcl/include/zclZllBasicCluster.h>
#include <z3device/multiSensor/include/msClusters.h>
#include <z3device/multiSensor/include/tsBasicCluster.h>
#include <z3device/multiSensor/include/tsIdentifyCluster.h>
#include <z3device/multiSensor/include/tsGroupsCluster.h>
#include <z3device/multiSensor/include/tsTemperatureMeasurementCluster.h>
#include <zcl/include/zclCommandManager.h>

/*******************************************************************************
                    Static functions section
*******************************************************************************/
static void tsFindingBindingFinishedForACluster(Endpoint_t ResponentEp, ClusterId_t id);
static void tsConfigureReportingResp(ZCL_Notify_t *ntfy);
static void ZCL_tsTemparatureAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);

/******************************************************************************
                    static variables
******************************************************************************/
static ZCL_DeviceEndpoint_t tsEndpoint =
{
  .simpleDescriptor =
  {
    .endpoint            = APP_ENDPOINT_TEMPERATURE_SENSOR,
    .AppProfileId        = PROFILE_ID_HOME_AUTOMATION,
    .AppDeviceId         = APP_Z3DEVICE_TS_ID,
    .AppInClustersCount  = ARRAY_SIZE(tsServerClusterIds),
    .AppInClustersList   = tsServerClusterIds,
    .AppOutClustersCount = ARRAY_SIZE(tsClientClusterIds),
    .AppOutClustersList  = tsClientClusterIds,
  },
  .serverCluster = tsServerClusters,
  .clientCluster = tsClientClusters,
};

static ClusterId_t tsServerClusterToBindIds[] =
{
  TEMPERATURE_MEASUREMENT_CLUSTER_ID,
<#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#assign ENDPOINT = ("ZCC"+ customClusterIndex +"_MULTI_SENSOR_ENDPOINT")?eval >
  <#if (DEVICE == "SERVER") && (ENDPOINT == "TEMPERATURE") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${clusterName?upper_case}_CLUSTER_ID,
  </#if>
</#list>

};
<#assign clusterCount = 0>
<#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#assign ENDPOINT = ("ZCC" + customClusterIndex + "_MULTI_SENSOR_ENDPOINT")?eval >
  <#if (ENDPOINT == "TEMPERATURE") && (DEVICE == "CLIENT") >    
    <#assign clusterCount = clusterCount + 1>        
  </#if>  
</#list>
<#if (clusterCount > 0)>

static ClusterId_t tsClientClusterToBindIds[] =
{
<#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#assign ENDPOINT = ("ZCC"+ customClusterIndex +"_MULTI_SENSOR_ENDPOINT")?eval >
  <#if (DEVICE == "CLIENT") && (ENDPOINT == "TEMPERATURE") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${clusterName?upper_case}_CLUSTER_ID,
  </#if>
</#list>
};
</#if>

<#function tsClientClusterToBindIds>
<#if (clusterCount > 0)>
  <#return "tsClientClusterToBindIds">
</#if>
  <#return "NULL">
</#function>

<#function tsClientClusterToBindIdsCount>
<#if (clusterCount > 0)>
  <#return "ARRAY_SIZE(tsClientClusterToBindIds)">
</#if>
  <#return "0">
</#function>
static AppBindReq_t tsBindReq =
{
  .remoteServers     = ${tsClientClusterToBindIds()},
  .remoteServersCnt  = ${tsClientClusterToBindIdsCount()},
  .remoteClients     = tsServerClusterToBindIds,
  .remoteClientsCnt  = ARRAY_SIZE(tsServerClusterToBindIds),
  .groupId           = 0xffff,
  .srcEndpoint       = APP_ENDPOINT_TEMPERATURE_SENSOR,
  .callback          = tsFindingBindingFinishedForACluster,
  .startIdentifyingFn= tsIdetifyStartIdentifyingCb
};

ZCL_TemperatureMeasurementClusterServerAttributes_t tsTemperatureMeasurementClusterServerAttributes =
{
  ZCL_DEFINE_TEMPERATURE_MEASUREMENT_CLUSTER_SERVER_ATTRIBUTES(TEMPERATURE_MEASUREMENT_VAL_MIN_REPORT_PERIOD, TEMPERATURE_MEASUREMENT_VAL_MAX_REPORT_PERIOD)
};

ZCL_TemperatureMeasurementClusterServerAttributes_t   __attribute__((persistent)) backuptsTemperatureMeasurementClusterServerAttributes;

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Device initialization routine
******************************************************************************/
void tsDeviceInit(void)
{
  APP_RegisterEndpoint(&tsEndpoint, &tsBindReq);

  tsBasicClusterInit();
  tsIdentifyClusterInit();
  temperatureMeasurementClusterInit();

  if (PDS_IsAbleToRestore(APP_MS_TEMP_MEASURED_VALUE_MEM_ID))
    PDS_Restore(APP_MS_TEMP_MEASURED_VALUE_MEM_ID);
}

/**************************************************************************//**
\brief
 Initializes Temperature Measurement cluster
******************************************************************************/
void temperatureMeasurementClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_TEMPERATURE_SENSOR, TEMPERATURE_MEASUREMENT_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
  ZCL_Cluster_t *clientSidecluster = ZCL_GetCluster(APP_ENDPOINT_TEMPERATURE_SENSOR, TEMPERATURE_MEASUREMENT_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
  
  if (cluster)
    cluster->ZCL_AttributeEventInd = ZCL_tsTemparatureAttributeEventInd;

<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")  && (TMC_MEASUREDVALUE == true)> 
  tsTemperatureMeasurementClusterServerAttributes.measuredValue.value = APP_TEMPERATURE_MEASUREMENT_MEASURED_VALUE_ATTRIBUTE_VALUE;
</#if>
<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")  && (TMC_MINMEASUREDVALUE == true)> 
  tsTemperatureMeasurementClusterServerAttributes.minMeasuredValue.value = APP_TEMPERATURE_MEASUREMENT_MIN_MEASURED_VALUE_ATTRIBUTE_VALUE;
</#if>
<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")  && (TMC_MAXMEASUREDVALUE == true)>
  tsTemperatureMeasurementClusterServerAttributes.maxMeasuredValue.value = APP_TEMPERATURE_MEASUREMENT_MAX_MEASURED_VALUE_ATTRIBUTE_VALUE;
</#if>
<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")  && (TMC_TOLERANCE == true)> 
  tsTemperatureMeasurementClusterServerAttributes.tolerance.value = APP_TEMPERATURE_MEASUREMENT_TOLERANCE_ATTRIBUTE_VALUE;//to be updated
</#if>
<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")  && (TMC_CLUSTERREVISION == true)> 
  tsTemperatureMeasurementClusterServerAttributes.clusterVersion.value = TEMPERATURE_MEASUREMENT_CLUSTER_VERSION;
</#if>
  if (clientSidecluster)
    clientSidecluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
}

<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")  && (TMC_MEASUREDVALUE == true)> 
/**************************************************************************//**
\brief Update the measured Value
******************************************************************************/
void tempeartureMeasurementUpdateMeasuredValue(void)
{
  int16_t measuredValue;

  measuredValue = tsTemperatureMeasurementClusterServerAttributes.measuredValue.value - APP_TEMPERATURE_MEASUREMENT_MEASURED_VALUE_PERIODIC_CHANGE;

  if (measuredValue < tsTemperatureMeasurementClusterServerAttributes.minMeasuredValue.value)
    tsTemperatureMeasurementClusterServerAttributes.measuredValue.value =  tsTemperatureMeasurementClusterServerAttributes.maxMeasuredValue.value;
  else
    tsTemperatureMeasurementClusterServerAttributes.measuredValue.value = measuredValue;
  
  PDS_Store(APP_MS_TEMP_MEASURED_VALUE_MEM_ID);
#ifdef _ZCL_REPORTING_SUPPORT_
  ZCL_ReportOnChangeIfNeeded(&tsTemperatureMeasurementClusterServerAttributes.measuredValue);
#endif
}
</#if>

/*******************************************************************************
\brief callback called on the finishing of binding of one cluster
********************************************************************************/
<#function hasReportableServerCluster>


<#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>

  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#assign ENDPOINT = ("ZCC"+ customClusterIndex +"_MULTI_SENSOR_ENDPOINT")?eval >
  <#if (DEVICE == "SERVER") && (ENDPOINT == "TEMPERATURE")>

  <#assign prefixAttribute  = "ZCC"+ customClusterIndex + "_CUSTOM_CLUSTER_" + "SERVER" + "_ATTRIBUTES_">

  <#list 0..<(prefixAttribute  + "NO")?eval as attributeIndex>
      <#if (prefixAttribute +"PROP_REPORTABLE_"+attributeIndex)?eval>
          <#return true>
      </#if>
  </#list>

  </#if>

</#list>

  <#return false>

</#function>
static void tsFindingBindingFinishedForACluster(Endpoint_t ResponentEp, ClusterId_t clusterId)
{
  if (TEMPERATURE_MEASUREMENT_CLUSTER_ID == clusterId)
  {
    ZCL_Cluster_t *serverCluster = ZCL_GetCluster(APP_ENDPOINT_TEMPERATURE_SENSOR, TEMPERATURE_MEASUREMENT_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
    if (serverCluster)
      sendConfigureReportingToNotify(APP_ENDPOINT_TEMPERATURE_SENSOR, APP_ENDPOINT_COMBINED_INTERFACE, TEMPERATURE_MEASUREMENT_CLUSTER_ID,
      ZCL_TEMPERATURE_MEASUREMENT_CLUSTER_SERVER_MEASURED_VALUE_ATTRIBUTE_ID, TEMPERATURE_MEASUREMENT_VAL_MAX_REPORT_PERIOD, tsConfigureReportingResp);
  }
  <#if (hasReportableServerCluster())>
  else
  {
  ZCL_StartReporting();
  }
  </#if>
}


/**************************************************************************//**
\brief Indication of configure reporting response

\param[in] ntfy - pointer to response
******************************************************************************/
static void tsConfigureReportingResp(ZCL_Notify_t *ntfy)
{
#ifdef _ZCL_REPORTING_SUPPORT_
  ZCL_StartReporting();
#endif
  (void)ntfy;
}

/**************************************************************************//**
\brief Attribute event (writing/reading) callback.

\param[in] addressing - incoming request addressing information.
\param[in] attributeId - attribute identifier.
\param[in] event - attribute event (read/write).
******************************************************************************/
static void ZCL_tsTemparatureAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  APP_Zigbee_Event_t eventItem;
  eventItem.eventGroup = EVENT_CLUSTER;
  eventItem.eventId = CMD_ZCL_ATTR_TEMPERATURE_MEASUREMENT;
  eventItem.eventData.zclAttributeData.addressing = addressing;
  eventItem.eventData.zclAttributeData.attributeId = attributeId;
  eventItem.eventData.zclAttributeData.event = event;

  APP_Zigbee_Handler(eventItem);

  if (((ZCL_CONFIGURE_ATTRIBUTE_REPORTING_EVENT == event) || \
       (ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == event)) && \
      (ZCL_TEMPERATURE_MEASUREMENT_CLUSTER_SERVER_MEASURED_VALUE_ATTRIBUTE_ID == attributeId))
  {
    PDS_Store(APP_MS_TEMP_MEASURED_VALUE_MEM_ID);
  }
}
/**************************************************************************//**
\brief Backing up attributes
******************************************************************************/
void tsBackupTsAttributes(void)
{
    memcpy4ByteAligned(&backuptsTemperatureMeasurementClusterServerAttributes,&tsTemperatureMeasurementClusterServerAttributes, sizeof(ZCL_TemperatureMeasurementClusterServerAttributes_t));
}

/**************************************************************************//**
\brief Restoring attributes
******************************************************************************/
void tsRestoreTsAttributes(void)
{
  memcpy4ByteAligned(&tsTemperatureMeasurementClusterServerAttributes, &backuptsTemperatureMeasurementClusterServerAttributes, sizeof(ZCL_TemperatureMeasurementClusterServerAttributes_t));
}
#endif  //#ifdef APP_SENSOR_TYPE_TEMPERATURE_SENSOR
#endif  //#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_MULTI_SENSOR)



// eof tsTemperatureMeasurementCluster.c
