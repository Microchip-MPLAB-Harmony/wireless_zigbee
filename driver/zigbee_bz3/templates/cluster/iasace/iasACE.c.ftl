/*******************************************************************************
  Intruder Alarm System -  Ancillary Control Equipment Source File

  Company:
    Microchip Technology Inc.

  File Name:
    iasACE.c

  Summary:
    This file contains the Intruder Alarm System -  Ancillary Control Equipment.

  Description:
    This file contains the Intruder Alarm System -  Ancillary Control Equipment.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_IAS_ACE)

/******************************************************************************
                             Includes section
******************************************************************************/
#include <z3device/ias_ace/include/iasACEAceCluster.h>
#include <z3device/ias_ace/include/iasACEZoneCluster.h>
#include <z3device/ias_ace/include/iasACECluster.h>
#include <z3device/ias_ace/include/iasaceidentifycluster.h>
#include <z3device/ias_ace/include/iasACEGroupsCluster.h>
#include <z3device/ias_ace/include/iasaceidentifycluster.h>
#include <z3device/ias_ace/include/iasacebasiccluster.h>
#include <z3device/clusters/include/basicCluster.h>
#include <zcl/clusters/include/identifyCluster.h>
#include <z3device/common/include/z3Device.h>
#include <zcl/include/zclSecurityManager.h>
#include <app_zigbee/zigbee_console/console.h>
#include <pds/include/wlPdsMemIds.h>
#include <z3device/clusters/include/haClusters.h>
#include <z3device/common/include/otauService.h>
#include <zcl/include/zclCommandManager.h>
#include <hal/include/sleep.h>
#include <systemenvironment/include/sysIdleHandler.h>
#ifdef OTAU_CLIENT
#include <zcl/include/zclOtauManager.h>
#endif

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
                   Define(s) section
******************************************************************************/

/*******************************************************************************
                    Static functions section
*******************************************************************************/
static void isBusyOrPollCheck(SYS_EventId_t eventId, SYS_EventData_t data);
void iasFindingBindingFinishedForACluster(Endpoint_t ResponentEp, ClusterId_t clusterId);
#ifdef OTAU_CLIENT 
static void configureImageKeyDone(void);
static void iasAddOTAUClientCluster(void);
#endif

<#if DEVICE_DEEP_SLEEP_ENABLED>
/******************************************************************************
                    Static functions section
******************************************************************************/
static void APP_RestoreZCLAttributes(void);
</#if>
/******************************************************************************
                    Local variables section
******************************************************************************/
static ZCL_DeviceEndpoint_t iasACEEndpoint =
{
  .simpleDescriptor =
  {
    .endpoint            = APP_ENDPOINT_IAS_ACE,
    .AppProfileId        = PROFILE_ID_HOME_AUTOMATION,
    .AppDeviceId         = APP_Z3DEVICE_ID,
    .AppInClustersCount  = ARRAY_SIZE(iasACEServerClusterIds),
    .AppInClustersList   = iasACEServerClusterIds,
    .AppOutClustersCount = ARRAY_SIZE(iasACEClientClusterIds),
    .AppOutClustersList  = iasACEClientClusterIds,
  },
  .serverCluster = iasACEServerClusters,
  .clientCluster = iasACEClientClusters,
};

static ClusterId_t iasACEClientClusterToBindIds[] =
{
  IDENTIFY_CLUSTER_ID,
  IAS_ACE_CLUSTER_ID,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT") || (DEVICE == "BOTH") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${clusterName?upper_case}_CLUSTER_ID,
  </#if>
  </#list> 
};

static ClusterId_t iasACEServerClusterToBindIds[] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  IAS_ZONE_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER") || (DEVICE == "BOTH") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${clusterName?upper_case}_CLUSTER_ID,
  </#if>  
  </#list>
};

static AppBindReq_t iasACEBindReq =
{
  .srcEndpoint       = APP_ENDPOINT_IAS_ACE,
  .remoteServersCnt  = ARRAY_SIZE(iasACEClientClusterToBindIds),
  .remoteClientsCnt  = ARRAY_SIZE(iasACEServerClusterToBindIds),
  .groupId           = 0xffff, 
  .remoteServers     = iasACEClientClusterToBindIds,
  .remoteClients     = iasACEServerClusterToBindIds,
  .callback          = iasFindingBindingFinishedForACluster,
  .startIdentifyingFn= iasIdentifyStartIdetifyingCb
};

static SYS_EventReceiver_t zdoBusyPollCheck = { .func = isBusyOrPollCheck};

/******************************************************************************
                    Implementation section
******************************************************************************/

/**************************************************************************//**
\brief Device initialization routine
******************************************************************************/
void appDeviceInit(void)
{
<#if DEVICE_DEEP_SLEEP_ENABLED>
  uint8_t deepSleepWakeupSrc = 0U;
</#if>
#if APP_ENABLE_CONSOLE == 1
  initConsole();
#endif
  if (!APP_RegisterEndpoint(&iasACEEndpoint, &iasACEBindReq))
    return;
  
  ZCL_CommandManagerInit();
  iasBasicClusterInit();
  iasIdentifyClusterInit();
  iasGroupsClusterInit();
  iasZoneClusterInit();
  iasACEClusterInit();
#ifdef OTAU_CLIENT
  iasAddOTAUClientCluster();
#endif //OTAU_CLIENT

<#if DEVICE_DEEP_SLEEP_ENABLED>
  CS_ReadParameter(CS_DEVICE_DEEP_SLEEP_WAKEUP_SRC_ID, &deepSleepWakeupSrc);

  /* Execute only if it is wakenup from deep sleep. */
  if(deepSleepWakeupSrc > 0U)
    APP_RestoreZCLAttributes();
</#if>

#if defined (_SLEEP_WHEN_IDLE_)
#if (ZB_COMMISSIONING_ON_STARTUP  == 1)
  SYS_EnableSleepWhenIdle();
#endif
#endif
  SYS_SubscribeToEvent(BC_EVENT_POLL_REQUEST, &zdoBusyPollCheck);
<#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
<#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
<#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
<#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${deviceTypeFunctionPrefix}${clusterName}Init();
</#list>
}

#ifdef OTAU_CLIENT
/**************************************************************************//**
\brief Adds OTAU client cluster to list of clients clusters of multisensor 
       device.
******************************************************************************/
static void iasAddOTAUClientCluster(void)
{
  iasACEClientClusters[IAS_ACE_CLIENT_CLUSTERS_COUNT - 1U] = ZCL_GetOtauClientCluster(); 
}

/**************************************************************************//**
\brief Callback about confguring image key on EEPROM
******************************************************************************/
static void configureImageKeyDone(void)
{}
#endif // OTAU_CLIENT

/**************************************************************************//**
\brief Device common task handler
******************************************************************************/
void appDeviceTaskHandler(void)
{
  switch (appDeviceState) // Actual device state when one joined network
  {
    case DEVICE_INITIAL_STATE:
      {
        appDeviceState = DEVICE_ACTIVE_IDLE_STATE;
      }
#ifdef OTAU_CLIENT
      startOtauClient();
#endif
      break;
    case DEVICE_ACTIVE_IDLE_STATE:
    default:
      break;
  }
}

/*******************************************************************************
\brief callback called on the finishing of binding of one cluster
********************************************************************************/
<#function hasReportableServerCluster>


<#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>

  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >

  <#if (DEVICE == "SERVER") || (DEVICE == "BOTH") >

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
void iasFindingBindingFinishedForACluster(Endpoint_t ResponentEp, ClusterId_t clusterId)
{
  <#if (hasReportableServerCluster())>
  ZCL_StartReporting();

  </#if>
  (void)ResponentEp;
  (void)clusterId;
}

/**************************************************************************//**
\brief backup ZCL attributes
******************************************************************************/
void APP_BackupZCLAttributes(void)
{
	//Add implementation here to backup zcl attributes if any.
<#if DEVICE_DEEP_SLEEP_ENABLED>
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
    <#assign DEVICE = ("ZCC" + customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval>
      <#if (DEVICE == "SERVER")||(DEVICE == "BOTH")>
    ${deviceTypeFunctionPrefix}ccZCC${(customClusterIndex)?eval}BackupAttribute();
    </#if>
  </#list>
</#if>
}

<#if DEVICE_DEEP_SLEEP_ENABLED>
/******************************************************************************
                    Static functions section
******************************************************************************/
static void APP_RestoreZCLAttributes(void)
{ 
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
    <#assign DEVICE = ("ZCC" + customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval>
    <#if (DEVICE == "SERVER")||(DEVICE == "BOTH")>
    ${deviceTypeFunctionPrefix}ccZCC${(customClusterIndex)?eval}RestoreAttribute();
    </#if>
  </#list>   
}
</#if>

/**************************************************************************//**
\brief Stops identifying on endpoints
******************************************************************************/
void appIdentifyStart(uint16_t identifyTime, bool colorEffect, uint16_t enhancedHue)
{
  iasIdentifyStart(identifyTime);
  (void)colorEffect;
  (void)enhancedHue;
}

/**************************************************************************//**
\brief Stops identifying on endpoints
******************************************************************************/
void appIdentifyStop(void)
{
  iasIdentifyStop();
}

/**************************************************************************//**
  \brief Processes BC_EVENT_BUSY_REQUEST and BC_EVENT_POLL_REQUEST events

  \param[in] eventId - id of raised event;
  \param[in] data    - event's data.
******************************************************************************/
static void isBusyOrPollCheck(SYS_EventId_t eventId, SYS_EventData_t data)
{
#if defined (_SLEEP_WHEN_IDLE_)
  bool *check = (bool *)data;

  if (BC_EVENT_POLL_REQUEST == eventId)
    *check |= isCommssioiningInProgress();
#else
  (void)eventId, (void)data;
#endif
}
#endif // APP_DEVICE_TYPE_IAS_ACE
// eof iasACE.c
