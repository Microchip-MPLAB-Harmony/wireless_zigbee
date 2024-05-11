/*******************************************************************************
  Custom IlluminanceMeasurement Cluster Source file

  Company:
    Microchip Technology Inc.

  File Name:
    customIlluminanceMeasurementCluster.c

  Summary:
    This file contains Custom IlluminanceMeasurement Cluster Implementation.

  Description:
    This file contains Custom IlluminanceMeasurement Cluster Implementation.
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

/******************************************************************************
                    Includes section
******************************************************************************/
#include <z3device/clusters/include/haClusters.h>

#include <pds/include/wlPdsMemIds.h>
#include <z3device/common/include/z3Device.h>
#include <zcl/include/zclZllBasicCluster.h>
#include <zcl/include/zclCommandManager.h>
#include <z3device/custom/include/customBasicCluster.h>
#include <z3device/custom/include/customIdentifyCluster.h>
#include <z3device/custom/include/customClusters.h>
#include <z3device/custom/include/customIlluminanceMeasurementCluster.h>
#include <app_zigbee/app_zigbee_handler.h>

/*******************************************************************************
                    Static functions section
*******************************************************************************/
static void ZCL_customIlluminanceAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "SERVER")>
static void customLightSensorReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload);
</#if>
/******************************************************************************
                    static variables
******************************************************************************/
<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT")>
ZCL_IlluminanceMeasurementClusterServerAttributes_t customIlluminanceMeasurementClusterServerAttributes =
{
  ZCL_DEFINE_ILLUMINANCE_MEASUREMENT_CLUSTER_SERVER_ATTRIBUTES(ILLUMINANCE_MEASUREMENT_VAL_MIN_REPORT_PERIOD, ILLUMINANCE_MEASUREMENT_VAL_MAX_REPORT_PERIOD)
};
</#if>
<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "SERVER")>
ZCL_IlluminanceMeasurementClusterClientAttributes_t customIlluminanceMeasurementClusterClientAttributes =
{
  ZCL_DEFINE_ILLUMINANCE_MEASUREMENT_CLUSTER_CLIENT_ATTRIBUTES()
};
</#if>

/****************************************************************************
*****************************************************************************/
<#if DEVICE_DEEP_SLEEP_ENABLED>
<#if ((ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE == true) && ((ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT") || (ILLUMINANCEMEASUREMENT_CLUSTER_CS == "BOTH")))>
    ZCL_IlluminanceMeasurementClusterServerAttributes_t __attribute__((persistent)) backupCstmIlluminanceMeasurementClusterServerAttributes;
</#if>
</#if>

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Illuminance measurement Sensing cluster
******************************************************************************/
void customIlluminanceMeasurementClusterInit(void)
{
<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT")>
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, ILLUMINANCE_MEASUREMENT_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
</#if>
<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "SERVER")>
  ZCL_Cluster_t *clientSideCluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, ILLUMINANCE_MEASUREMENT_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
</#if>

<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT")>
  if (cluster)
    cluster->ZCL_AttributeEventInd = ZCL_customIlluminanceAttributeEventInd;
<#else>
  if (clientSideCluster)
    clientSideCluster->ZCL_AttributeEventInd = ZCL_customIlluminanceAttributeEventInd;
</#if>

<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT")>
<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT")  && (IMC_LIGHTSENSORTYPE == true)>
  customIlluminanceMeasurementClusterServerAttributes.lightSensorType.value = APP_ILLUMINANCE_MEASUREMENT_LIGHT_SENSOR_TYPE_VALUE;
</#if>
<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT")  && (IMC_MEASUREDVALUE == true)>
  customIlluminanceMeasurementClusterServerAttributes.measuredValue.value = APP_ILLUMINANCE_MEASUREMENT_MEASURED_VALUE_ATTRIBUTE_VALUE;
</#if>
<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT")  && (IMC_MINMEASUREDVALUE == true)>
  customIlluminanceMeasurementClusterServerAttributes.minMeasuredValue.value = APP_ILLUMINANCE_MEASUREMENT_MIN_MEASURED_VALUE_ATTRIBUTE_VALUE;
</#if>
<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT")  && (IMC_MAXMEASUREDVALUE == true)>
  customIlluminanceMeasurementClusterServerAttributes.maxMeasuredValue.value = APP_ILLUMINANCE_MEASUREMENT_MAX_MEASURED_VALUE_ATTRIBUTE_VALUE;
</#if>
<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT")  && (IMC_TOLERANCE == true)>
  customIlluminanceMeasurementClusterServerAttributes.tolerance.value = APP_ILLUMINANCE_MEASUREMENT_TOLERANCE_ATTRIBUTE_VALUE;
</#if>
<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT")  && (IMC_CLUSTERREVISION == true)>
  customIlluminanceMeasurementClusterServerAttributes.clusterVersion.value = ILLUMINANCE_MEASUREMENT_CLUSTER_VERSION;
</#if>
</#if>
<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "SERVER")>
<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "SERVER")  && (IMCC_CLUSTERREVISION == true)>
  customIlluminanceMeasurementClusterClientAttributes.clusterVersion.value = ILLUMINANCE_MEASUREMENT_CLUSTER_VERSION;
</#if>

  if (clientSideCluster)
    clientSideCluster->ZCL_ReportInd = customLightSensorReportInd;

  if (clientSideCluster)
    clientSideCluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
</#if>
}

<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT")>
/**************************************************************************//**
\brief Update the measured Value
******************************************************************************/
void illuminanceMeasurementUpdateMeasuredValue(void)
{
  uint16_t measuredValue;

  measuredValue = rand()% APP_ILLUMINANCE_MEASUREMENT_MAX_MEASURED_VALUE_ATTRIBUTE_VALUE;
<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT")  && (IMC_MEASUREDVALUE == true)>
<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT")  && (IMC_MINMEASUREDVALUE == true)> 
  if (measuredValue < customIlluminanceMeasurementClusterServerAttributes.minMeasuredValue.value)
    customIlluminanceMeasurementClusterServerAttributes.measuredValue.value = customIlluminanceMeasurementClusterServerAttributes.minMeasuredValue.value;
  else</#if>
    customIlluminanceMeasurementClusterServerAttributes.measuredValue.value = measuredValue;
</#if>
  
  PDS_Store(APP_CUSTOM_ILLU_MEASURED_VALUE_MEM_ID);
#ifdef _ZCL_REPORTING_SUPPORT_
  ZCL_ReportOnChangeIfNeeded(&customIlluminanceMeasurementClusterServerAttributes.measuredValue);
#endif
}
</#if>

/**************************************************************************//**
\brief Attribute event (writing/reading) callback.

\param[in] addressing - incoming request addressing information.
\param[in] attributeId - attribute identifier.
\param[in] event - attribute event (read/write).
******************************************************************************/
static void ZCL_customIlluminanceAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  APP_Zigbee_Event_t eventItem;
  eventItem.eventGroup = EVENT_CLUSTER;
  eventItem.eventId = CMD_ZCL_ATTR_ILLUMINANCE_MEASUREMENT;
  eventItem.eventData.zclAttributeData.addressing = addressing;
  eventItem.eventData.zclAttributeData.attributeId = attributeId;
  eventItem.eventData.zclAttributeData.event = event;
  APP_Zigbee_Handler(eventItem);

  if (((ZCL_CONFIGURE_ATTRIBUTE_REPORTING_EVENT == event) || \
       (ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == event)) && \
      (ZCL_ILLUMINANCE_MEASUREMENT_CLUSTER_MEASURED_VALUE_SERVER_ATTRIBUTE_ID == attributeId))
  {
    PDS_Store(APP_CUSTOM_ILLU_MEASURED_VALUE_MEM_ID);
  }
}


<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "SERVER")>
/**************************************************************************//**
\brief Report attribute indication handler

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void customLightSensorReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload)
{
  APP_Zigbee_Event_t eventItem;
  eventItem.eventGroup = EVENT_CLUSTER;
  eventItem.eventId = CMD_ZCL_REPORTING_LIGHT_SENSOR;
  eventItem.eventData.zclEventData.addressing = addressing;
  eventItem.eventData.zclEventData.payloadLength = reportLength;
  eventItem.eventData.zclEventData.payload = reportPayload;

  APP_Zigbee_Handler(eventItem);
}
</#if>

/*********************************************************************************
*********************************************************************************/
<#if DEVICE_DEEP_SLEEP_ENABLED>
<#if ((ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE == true) && ((ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT") || (ILLUMINANCEMEASUREMENT_CLUSTER_CS == "BOTH")))>
void CDlsBackupLsAttributes(void)
{
   memcpy4ByteAligned(&backupCstmIlluminanceMeasurementClusterServerAttributes,&customIlluminanceMeasurementClusterServerAttributes, sizeof(ZCL_IlluminanceMeasurementClusterServerAttributes_t));
}
</#if>
<#if ((ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE == true) && ((ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT") || (ILLUMINANCEMEASUREMENT_CLUSTER_CS == "BOTH")))>
void CDlsRestoreLsAttributes(void)
{
  memcpy4ByteAligned(&customIlluminanceMeasurementClusterServerAttributes, &backupCstmIlluminanceMeasurementClusterServerAttributes, sizeof(ZCL_IlluminanceMeasurementClusterServerAttributes_t));
}
</#if>
</#if>
// eof customilluminanceMeasurementCluster.c
