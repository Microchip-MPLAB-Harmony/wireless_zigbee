/*******************************************************************************
  Custom Temperature Measurement Cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    customTemperatureMeasurementCluster.c

  Summary:
    This file contains the Custom Temperature Measurement Cluster implementation.

  Description:
    This file contains the Custom Temperature Measurement Cluster implementation.
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
#include <custom/include/customTemperatureMeasurementCluster.h>
#include <wlPdsMemIds.h>
#include <z3Device.h>
#include <console.h>
#include <zclCommandManager.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define TEMPERATURE_REPORT_PERIOD   20000UL

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_TemperatureMeasurementClusterServerAttributes_t customTemperatureMeasurementClusterServerAttributes =
{
  ZCL_DEFINE_TEMPERATURE_MEASUREMENT_CLUSTER_SERVER_ATTRIBUTES(TEMPERATURE_MEASUREMENT_VAL_MIN_REPORT_PERIOD, TEMPERATURE_MEASUREMENT_VAL_MAX_REPORT_PERIOD)
};

ZCL_TemperatureMeasurementClusterClientAttributes_t customTemperatureMeasurementClusterClientAttributes =
{
  ZCL_DEFINE_TEMPERATURE_MEASUREMENT_CLUSTER_CLIENT_ATTRIBUTES()
};

/******************************************************************************
                    Local variables section
******************************************************************************/
static HAL_AppTimer_t readTemperatureimer =
{
  .interval = TEMPERATURE_REPORT_PERIOD,
  .mode     = TIMER_REPEAT_MODE,
  .callback = customTempeartureMeasurementUpdateMeasuredValue,
};

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void customTemperatureMeasurementReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload);
static void customTemparatureAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Temperature Measurement cluster
******************************************************************************/
void customTemperatureMeasurementClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, TEMPERATURE_MEASUREMENT_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
  customTemperatureMeasurementClusterClientAttributes.clusterVersion.value = CLUSTER_VERSION;
  customTemperatureMeasurementClusterServerAttributes.clusterVersion.value = CLUSTER_VERSION;
  if (cluster)
  {
    cluster->ZCL_ReportInd = customTemperatureMeasurementReportInd;
  }
  cluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
  cluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, TEMPERATURE_MEASUREMENT_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);

  if (cluster)
  {
    cluster->ZCL_AttributeEventInd = customTemparatureAttributeEventInd;
    customTemperatureMeasurementClusterServerAttributes.measuredValue.value = APP_TEMPERATURE_MEASUREMENT_MEASURED_VALUE_ATTRIBUTE_VALUE;
    customTemperatureMeasurementClusterServerAttributes.minMeasuredValue.value = APP_TEMPERATURE_MEASUREMENT_MIN_MEASURED_VALUE_ATTRIBUTE_VALUE;
    customTemperatureMeasurementClusterServerAttributes.maxMeasuredValue.value = APP_TEMPERATURE_MEASUREMENT_MAX_MEASURED_VALUE_ATTRIBUTE_VALUE;
    customTemperatureMeasurementClusterServerAttributes.tolerance.value = APP_TEMPERATURE_MEASUREMENT_TOLERANCE_ATTRIBUTE_VALUE;//to be updated
    HAL_StartAppTimer(&readTemperatureimer);
     
    if (PDS_IsAbleToRestore(APP_CUSTOM_TEMPERATURE_MEASURED_VALUE_MEM_ID))
      PDS_Restore(APP_CUSTOM_TEMPERATURE_MEASURED_VALUE_MEM_ID);
  }
}

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
/**************************************************************************//**
\brief Report attribute indication handler

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void customTemperatureMeasurementReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload)
{
  ZCL_Report_t *rep = (ZCL_Report_t *)reportPayload;
  int16_t reportValue;

  memcpy(&reportValue, &rep->value[0], sizeof(int16_t));
  appSnprintf("<-Temperature Measurement Attr Report: t = %d\r\n", reportValue);

  (void)addressing, (void)reportLength, (void)rep;
}

/**************************************************************************//**
\brief Attribute event (writing/reading) callback.

\param[in] addressing - incoming request addressing information.
\param[in] attributeId - attribute identifier.
\param[in] event - attribute event (read/write).
******************************************************************************/
static void customTemparatureAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  if ((ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == event) && \
       (ZCL_TEMPERATURE_MEASUREMENT_CLUSTER_SERVER_MEASURED_VALUE_ATTRIBUTE_ID == attributeId))
   {    
    customTemperatureMeasurementClusterServerAttributes.measuredValue.minReportInterval = TEMPERATURE_MEASUREMENT_VAL_MIN_REPORT_PERIOD;
    customTemperatureMeasurementClusterServerAttributes.measuredValue.maxReportInterval = TEMPERATURE_MEASUREMENT_VAL_MAX_REPORT_PERIOD;
    customTemperatureMeasurementClusterServerAttributes.measuredValue.reportableChange = 0;     
   }
  if (((ZCL_CONFIGURE_ATTRIBUTE_REPORTING_EVENT == event) || \
       (ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == event)) && \
      (ZCL_TEMPERATURE_MEASUREMENT_CLUSTER_SERVER_MEASURED_VALUE_ATTRIBUTE_ID == attributeId))
  {
    PDS_Store(APP_CUSTOM_TEMPERATURE_MEASURED_VALUE_MEM_ID);
  }

  (void)addressing;
}
#endif
// eof customTemperatureMeasurementCluster.c
