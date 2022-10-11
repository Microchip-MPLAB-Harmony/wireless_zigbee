/*******************************************************************************
  Custom Temperature Measurement Cluster Source file

  Company:
    Microchip Technology Inc.

  File Name:
    customTemperatureMeasurementCluster.c

  Summary:
    This file contains Custom Temperature Measurement Cluster Implementation.

  Description:
    This file contains Custom Temperature Measurement Cluster Implementation.
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
#include <z3device/custom/include/customTemperatureMeasurementCluster.h>
#include <pds/include/wlPdsMemIds.h>
#include <z3device/common/include/z3Device.h>
#include <app_zigbee/zigbee_console/console.h>
#include <zcl/include/zclCommandManager.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")>
#define TEMPERATURE_REPORT_PERIOD   20000UL
</#if>

/******************************************************************************
                    Global variables
******************************************************************************/
<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")>
ZCL_TemperatureMeasurementClusterServerAttributes_t customTemperatureMeasurementClusterServerAttributes =
{
  ZCL_DEFINE_TEMPERATURE_MEASUREMENT_CLUSTER_SERVER_ATTRIBUTES(TEMPERATURE_MEASUREMENT_VAL_MIN_REPORT_PERIOD, TEMPERATURE_MEASUREMENT_VAL_MAX_REPORT_PERIOD)
};
</#if>

<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "SERVER")>
ZCL_TemperatureMeasurementClusterClientAttributes_t customTemperatureMeasurementClusterClientAttributes =
{
  ZCL_DEFINE_TEMPERATURE_MEASUREMENT_CLUSTER_CLIENT_ATTRIBUTES()
};
</#if>

/******************************************************************************
                    Local variables section
******************************************************************************/
<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")>
static HAL_AppTimer_t readTemperatureimer =
{
  .interval = TEMPERATURE_REPORT_PERIOD,
  .mode     = TIMER_REPEAT_MODE,
  .callback = customTempeartureMeasurementUpdateMeasuredValue,
};
</#if>

/******************************************************************************
                    Prototypes section
******************************************************************************/
<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "SERVER")>
static void customTemperatureMeasurementReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload);
</#if>
<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")>
static void customTemparatureAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
</#if>

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Temperature Measurement cluster
******************************************************************************/
void customTemperatureMeasurementClusterInit(void)
{
<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "SERVER")>
  ZCL_Cluster_t *tempcluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, TEMPERATURE_MEASUREMENT_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "SERVER")  && (TMCC_CLUSTERREVISION == true)>  
  customTemperatureMeasurementClusterClientAttributes.clusterVersion.value = TEMPERATURE_MEASUREMENT_CLUSTER_VERSION;
</#if>
<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")  && (TMC_CLUSTERREVISION == true)> 
  customTemperatureMeasurementClusterServerAttributes.clusterVersion.value = TEMPERATURE_MEASUREMENT_CLUSTER_VERSION;
</#if>
  if (tempcluster)
  {
    tempcluster->ZCL_ReportInd = customTemperatureMeasurementReportInd;
  }
  tempcluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
</#if>
<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")>
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, TEMPERATURE_MEASUREMENT_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);

  if (cluster)
  {
    cluster->ZCL_AttributeEventInd = customTemparatureAttributeEventInd;
<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")  && (TMC_MEASUREDVALUE == true)>     
    customTemperatureMeasurementClusterServerAttributes.measuredValue.value = APP_TEMPERATURE_MEASUREMENT_MEASURED_VALUE_ATTRIBUTE_VALUE;
</#if>
<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")  && (TMC_MINMEASUREDVALUE == true)> 
    customTemperatureMeasurementClusterServerAttributes.minMeasuredValue.value = APP_TEMPERATURE_MEASUREMENT_MIN_MEASURED_VALUE_ATTRIBUTE_VALUE;
</#if>
<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")  && (TMC_MAXMEASUREDVALUE == true)>
    customTemperatureMeasurementClusterServerAttributes.maxMeasuredValue.value = APP_TEMPERATURE_MEASUREMENT_MAX_MEASURED_VALUE_ATTRIBUTE_VALUE;
</#if>
<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")  && (TMC_TOLERANCE == true)>  
    customTemperatureMeasurementClusterServerAttributes.tolerance.value = APP_TEMPERATURE_MEASUREMENT_TOLERANCE_ATTRIBUTE_VALUE;//to be updated
</#if>
    HAL_StartAppTimer(&readTemperatureimer);
     
    if (PDS_IsAbleToRestore(APP_CUSTOM_TEMPERATURE_MEASURED_VALUE_MEM_ID))
      PDS_Restore(APP_CUSTOM_TEMPERATURE_MEASURED_VALUE_MEM_ID);
  }
</#if>
}

<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")>
<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")  && (TMC_MEASUREDVALUE == true)> 
/**************************************************************************//**
\brief Update the measured Value
******************************************************************************/
void customTempeartureMeasurementUpdateMeasuredValue(void)
{
  int16_t measuredValue;

  measuredValue = customTemperatureMeasurementClusterServerAttributes.measuredValue.value - APP_TEMPERATURE_MEASUREMENT_MEASURED_VALUE_PERIODIC_CHANGE;

  if (measuredValue < customTemperatureMeasurementClusterServerAttributes.minMeasuredValue.value)
    customTemperatureMeasurementClusterServerAttributes.measuredValue.value =  customTemperatureMeasurementClusterServerAttributes.maxMeasuredValue.value;
  else
    customTemperatureMeasurementClusterServerAttributes.measuredValue.value = measuredValue;

  PDS_Store(APP_CUSTOM_TEMPERATURE_MEASURED_VALUE_MEM_ID);
#ifdef _ZCL_REPORTING_SUPPORT_
  ZCL_ReportOnChangeIfNeeded(&customTemperatureMeasurementClusterServerAttributes.measuredValue);
#endif
}
</#if>

/**************************************************************************//**
\brief Attribute event (writing/reading) callback.

\param[in] addressing - incoming request addressing information.
\param[in] attributeId - attribute identifier.
\param[in] event - attribute event (read/write).
******************************************************************************/
static void customTemparatureAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
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
    PDS_Store(APP_CUSTOM_TEMPERATURE_MEASURED_VALUE_MEM_ID);
  }
}
</#if>
<#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "SERVER")>
/**************************************************************************//**
\brief Report attribute indication handler

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void customTemperatureMeasurementReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_REPORTING_TEMPERATURE_MEASUREMENT;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = reportLength;
  event.eventData.zclEventData.payload = reportPayload;

  APP_Zigbee_Handler(event);
}
</#if>

#endif
// eof customTemperatureMeasurementCluster.c
