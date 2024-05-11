/*******************************************************************************
  Custom Illuminance Measurement cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    customIlluminanceMeasurementCluster.c

  Summary:
    This file contains the Custom Illuminance Measurement Cluster implementation.

  Description:
    This file contains the Custom Illuminance Measurement Cluster implementation.
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
#include <haClusters.h>

#include <wlPdsMemIds.h>
#include <z3Device.h>
#include <zclZllBasicCluster.h>
#include <zclCommandManager.h>
#include <custom/include/customBasicCluster.h>
#include <custom/include/customIdentifyCluster.h>
#include <custom/include/customClusters.h>
#include <custom/include/customIlluminanceMeasurementCluster.h>
/*******************************************************************************
                    Static functions section
*******************************************************************************/
static void customFindingBindingFinishedForACluster(Endpoint_t ResponentEp, ClusterId_t id);
static void customConfigureReportingResp(ZCL_Notify_t *ntfy);
static void ZCL_customIlluminanceAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
static void customLightSensorReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload);
/******************************************************************************
                    static variables
******************************************************************************/
static ZCL_DeviceEndpoint_t customEndpoint =
{
  .simpleDescriptor =
  {
    .endpoint            = APP_ENDPOINT_CUSTOM,
    .AppProfileId        = PROFILE_ID_HOME_AUTOMATION,
    .AppDeviceId         = ZLO_CUSTOM_DEVICE_ID,
    .AppInClustersCount  = ARRAY_SIZE(customServerClusterIds),
    .AppInClustersList   = customServerClusterIds,
    .AppOutClustersCount = ARRAY_SIZE(customClientClusterIds),
    .AppOutClustersList  = customClientClusterIds,
  },
  .serverCluster = customServerClusters,
  .clientCluster = customClientClusters,
};

static ClusterId_t customServerClusterToBindIds[] =
{
  ILLUMINANCE_MEASUREMENT_CLUSTER_ID,
};

static AppBindReq_t customBindReq =
{
  .remoteServers     = NULL,
  .remoteServersCnt  = 0,
  .remoteClients     = customServerClusterToBindIds,
  .remoteClientsCnt  = ARRAY_SIZE(customServerClusterToBindIds),
  .groupId           = 0xffff,
  .srcEndpoint       = APP_ENDPOINT_EXTENDED_COLOR_LIGHT_SENSOR,
  .callback          = customFindingBindingFinishedForACluster,
  .startIdentifyingFn= customIdetifyStartIdentifyingCb
};

ZCL_IlluminanceMeasurementClusterServerAttributes_t customIlluminanceMeasurementClusterServerAttributes =
{
  ZCL_DEFINE_ILLUMINANCE_MEASUREMENT_CLUSTER_SERVER_ATTRIBUTES(ILLUMINANCE_MEASUREMENT_VAL_MIN_REPORT_PERIOD, ILLUMINANCE_MEASUREMENT_VAL_MAX_REPORT_PERIOD)
};

ZCL_IlluminanceMeasurementClusterClientAttributes_t customIlluminanceMeasurementClusterClientAttributes =
{
  ZCL_DEFINE_ILLUMINANCE_MEASUREMENT_CLUSTER_CLIENT_ATTRIBUTES()
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Device initialization routine
******************************************************************************/
void customDeviceInit(void)
{
  APP_RegisterEndpoint(&customEndpoint, &customBindReq);

  customBasicClusterInit();
  customIdentifyClusterInit();
  customIlluminanceMeasurementClusterInit();

  if (PDS_IsAbleToRestore(APP_CUSTOM_ILLU_MEASURED_VALUE_MEM_ID))
    PDS_Restore(APP_CUSTOM_ILLU_MEASURED_VALUE_MEM_ID);
}

/**************************************************************************//**
\brief Initializes Illuminance measurement Sensing cluster
******************************************************************************/
void customIlluminanceMeasurementClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, ILLUMINANCE_MEASUREMENT_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
  ZCL_Cluster_t *clientSideCluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, ILLUMINANCE_MEASUREMENT_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);

  if (cluster)
    cluster->ZCL_AttributeEventInd = ZCL_customIlluminanceAttributeEventInd;

  customIlluminanceMeasurementClusterServerAttributes.lightSensorType.value = APP_ILLUMINANCE_MEASUREMENT_LIGHT_SENSOR_TYPE_VALUE;
  customIlluminanceMeasurementClusterServerAttributes.measuredValue.value = APP_ILLUMINANCE_MEASUREMENT_MEASURED_VALUE_ATTRIBUTE_VALUE;
  customIlluminanceMeasurementClusterServerAttributes.minMeasuredValue.value = APP_ILLUMINANCE_MEASUREMENT_MIN_MEASURED_VALUE_ATTRIBUTE_VALUE;
  customIlluminanceMeasurementClusterServerAttributes.maxMeasuredValue.value = APP_ILLUMINANCE_MEASUREMENT_MAX_MEASURED_VALUE_ATTRIBUTE_VALUE;
  customIlluminanceMeasurementClusterServerAttributes.tolerance.value = APP_ILLUMINANCE_MEASUREMENT_TOLERANCE_ATTRIBUTE_VALUE;
  customIlluminanceMeasurementClusterServerAttributes.clusterVersion.value = CLUSTER_VERSION;

  customIlluminanceMeasurementClusterClientAttributes.clusterVersion.value = CLUSTER_VERSION;

  if (clientSideCluster)
    cluster->ZCL_ReportInd = customLightSensorReportInd;

  if (clientSideCluster)
    clientSideCluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
}

/**************************************************************************//**
\brief Update the measured Value
******************************************************************************/
void illuminanceMeasurementUpdateMeasuredValue(void)
{
  uint16_t measuredValue;

  measuredValue = rand()% APP_ILLUMINANCE_MEASUREMENT_MAX_MEASURED_VALUE_ATTRIBUTE_VALUE;
  if (measuredValue < customIlluminanceMeasurementClusterServerAttributes.minMeasuredValue.value)
    customIlluminanceMeasurementClusterServerAttributes.measuredValue.value = customIlluminanceMeasurementClusterServerAttributes.minMeasuredValue.value;
  else
    customIlluminanceMeasurementClusterServerAttributes.measuredValue.value = measuredValue;
  
  PDS_Store(APP_CUSTOM_ILLU_MEASURED_VALUE_MEM_ID);
#ifdef _ZCL_REPORTING_SUPPORT_
  ZCL_ReportOnChangeIfNeeded(&customIlluminanceMeasurementClusterServerAttributes.measuredValue);
#endif
}

/*******************************************************************************
\brief callback called on the finishing of binding of one cluster
********************************************************************************/
static void customFindingBindingFinishedForACluster(Endpoint_t ResponentEp, ClusterId_t clusterId)
{
  if (ILLUMINANCE_MEASUREMENT_CLUSTER_ID == clusterId)
  {
    ZCL_Cluster_t *serverCluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, ILLUMINANCE_MEASUREMENT_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
    if (serverCluster)
      sendConfigureReportingToNotify(APP_ENDPOINT_CUSTOM, APP_ENDPOINT_COMBINED_INTERFACE, ILLUMINANCE_MEASUREMENT_CLUSTER_ID,
      ZCL_ILLUMINANCE_MEASUREMENT_CLUSTER_MEASURED_VALUE_SERVER_ATTRIBUTE_ID, ILLUMINANCE_MEASUREMENT_VAL_MAX_REPORT_PERIOD, customConfigureReportingResp);
  }
}


/**************************************************************************//**
\brief Indication of configure reporting response

\param[in] ntfy - pointer to response
******************************************************************************/
static void customConfigureReportingResp(ZCL_Notify_t *ntfy)
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
static void ZCL_customIlluminanceAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  if((ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == event) && \
      (ZCL_ILLUMINANCE_MEASUREMENT_CLUSTER_MEASURED_VALUE_SERVER_ATTRIBUTE_ID == attributeId))
  {
    customIlluminanceMeasurementClusterServerAttributes.measuredValue.minReportInterval = ILLUMINANCE_MEASUREMENT_VAL_MIN_REPORT_PERIOD;
    customIlluminanceMeasurementClusterServerAttributes.measuredValue.maxReportInterval = ILLUMINANCE_MEASUREMENT_VAL_MAX_REPORT_PERIOD;
    customIlluminanceMeasurementClusterServerAttributes.measuredValue.reportableChange = 0;
  }
  if (((ZCL_CONFIGURE_ATTRIBUTE_REPORTING_EVENT == event) || \
       (ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == event)) && \
      (ZCL_ILLUMINANCE_MEASUREMENT_CLUSTER_MEASURED_VALUE_SERVER_ATTRIBUTE_ID == attributeId))
  {
    PDS_Store(APP_CUSTOM_ILLU_MEASURED_VALUE_MEM_ID);
  }

  (void)addressing;
}

/**************************************************************************//**
\brief Report attribute indication handler

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void customLightSensorReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload)
{
  ZCL_Report_t *rep = (ZCL_Report_t *)reportPayload;
  uint16_t reportValue;

  memcpy(&reportValue, &rep->value[0], sizeof(uint16_t));

  appSnprintf("<-Light Sensor Attr Report: t = %d\r\n", reportValue);

  (void)addressing, (void)reportLength, (void)rep;
}
// eof customilluminanceMeasurementCluster.c
