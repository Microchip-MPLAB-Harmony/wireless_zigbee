/*******************************************************************************
  Custom Humidity Measurement cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    customHumidityMeasurementCluster.c

  Summary:
    This file contains the Custom Humidity Measurement Cluster implementation.

  Description:
    This file contains the Custom Humidity Measurement Cluster implementation.
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
#include <haClusters.h>
#include <custom/include/customHumidityMeasurementCluster.h>
#include <wlPdsMemIds.h>
#include <z3Device.h>
#include <console.h>
#include <zclCommandManager.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_HumidityMeasurementClusterServerAttributes_t customHumidityMeasurementClusterServerAttributes =
{
  ZCL_DEFINE_HUMIDITY_MEASUREMENT_CLUSTER_SERVER_ATTRIBUTES(HUMIDITY_MEASUREMENT_VAL_MIN_REPORT_PERIOD, HUMIDITY_MEASUREMENT_VAL_MAX_REPORT_PERIOD)
};

ZCL_HumidityMeasurementClusterClientAttributes_t customHumidityMeasurementClusterClientAttributes =
{
  ZCL_DEFINE_HUMIDITY_MEASUREMENT_CLUSTER_CLIENT_ATTRIBUTES()
};

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void customHumidityMeasurementReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload);
static void customHumidityAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Humidity Measurement cluster
******************************************************************************/
void customHumidityMeasurementClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, HUMIDITY_MEASUREMENT_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);

  if (cluster)
  {
    customHumidityMeasurementClusterClientAttributes.clusterVersion.value = CLUSTER_VERSION;
    cluster->ZCL_ReportInd = customHumidityMeasurementReportInd;
  }
  cluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
  cluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, HUMIDITY_MEASUREMENT_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);

  if (cluster)
  {
    customHumidityMeasurementClusterServerAttributes.clusterVersion.value = CLUSTER_VERSION;
    customHumidityMeasurementClusterServerAttributes.measuredValue.value = APP_HUMIDITY_MEASUREMENT_MEASURED_VALUE_ATTRIBUTE_VALUE;
    customHumidityMeasurementClusterServerAttributes.minMeasuredValue.value = APP_HUMIDITY_MEASUREMENT_MIN_MEASURED_VALUE_ATTRIBUTE_VALUE;
    customHumidityMeasurementClusterServerAttributes.maxMeasuredValue.value = APP_HUMIDITY_MEASUREMENT_MAX_MEASURED_VALUE_ATTRIBUTE_VALUE;
    customHumidityMeasurementClusterServerAttributes.tolerance.value = APP_HUMIDITY_MEASUREMENT_TOLERANCE_ATTRIBUTE_VALUE;//to be updated
    ZCL_ReportOnChangeIfNeeded(&customHumidityMeasurementClusterServerAttributes.measuredValue);
    cluster->ZCL_AttributeEventInd = customHumidityAttributeEventInd;
  }

  if (PDS_IsAbleToRestore(APP_CUSTOM_HUMIDITY_MEASURED_VALUE_MEM_ID))
    PDS_Restore(APP_CUSTOM_HUMIDITY_MEASURED_VALUE_MEM_ID);

}

/**************************************************************************//**
\brief Update the measured Value
******************************************************************************/
void humidityMeasurementUpdateMeasuredValue(void)
{
  uint16_t measuredValue ;

  measuredValue = customHumidityMeasurementClusterServerAttributes.measuredValue.value + APP_HUMIDITY_MEASUREMENT_MEASURED_VALUE_PERIODIC_CHANGE;

  if (measuredValue > customHumidityMeasurementClusterServerAttributes.maxMeasuredValue.value)
    customHumidityMeasurementClusterServerAttributes.measuredValue.value =  customHumidityMeasurementClusterServerAttributes.minMeasuredValue.value;
  else
    customHumidityMeasurementClusterServerAttributes.measuredValue.value = measuredValue;

  PDS_Store(APP_CUSTOM_HUMIDITY_MEASURED_VALUE_MEM_ID);
#ifdef _ZCL_REPORTING_SUPPORT_
  ZCL_ReportOnChangeIfNeeded(&customHumidityMeasurementClusterServerAttributes.measuredValue);
#endif
}

/**************************************************************************//**
\brief Report attribute indication handler

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void customHumidityMeasurementReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload)
{
  ZCL_Report_t *rep = (ZCL_Report_t *)reportPayload;
  uint16_t reportValue;

  memcpy(&reportValue, &rep->value[0], sizeof(uint16_t));
  LOG_STRING(reportAttrIndStr, "<-Humidity Measurement Attr Report: t = %u\r\n");
  appSnprintf(reportAttrIndStr, reportValue);

  (void)addressing, (void)reportLength, (void)rep;
}

/**************************************************************************//**
\brief Attribute event (writing/reading) callback.

\param[in] addressing - incoming request addressing information.
\param[in] attributeId - attribute identifier.
\param[in] event - attribute event (read/write).
******************************************************************************/
static void customHumidityAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  if ((ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == event) && \
      (ZCL_HUMIDITY_MEASUREMENT_CLUSTER_SERVER_MEASURED_VALUE_ATTRIBUTE_ID == attributeId))
  {
    customHumidityMeasurementClusterServerAttributes.measuredValue.minReportInterval = HUMIDITY_MEASUREMENT_VAL_MIN_REPORT_PERIOD;
    customHumidityMeasurementClusterServerAttributes.measuredValue.maxReportInterval = HUMIDITY_MEASUREMENT_VAL_MAX_REPORT_PERIOD;
    customHumidityMeasurementClusterServerAttributes.measuredValue.reportableChange  = 0;
  }
  if (((ZCL_CONFIGURE_ATTRIBUTE_REPORTING_EVENT == event) || \
       (ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == event)) && \
      (ZCL_HUMIDITY_MEASUREMENT_CLUSTER_SERVER_MEASURED_VALUE_ATTRIBUTE_ID == attributeId))      
  {
    PDS_Store(APP_CUSTOM_HUMIDITY_MEASURED_VALUE_MEM_ID);
  }

  (void)addressing;
}
#endif // APP_DEVICE_TYPE_CUSTOM_DEVICE

// eof customHumidityMeasuementCluster.c