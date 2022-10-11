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
#include <hal/cortexm4/pic32cx/include/halSleep.h>
#include <systemenvironment/include/sysIdleHandler.h>
#ifdef OTAU_CLIENT
#include <zcl/include/zclOtauManager.h>
#endif

/******************************************************************************
                   Define(s) section
******************************************************************************/

/*******************************************************************************
                    Static functions section
*******************************************************************************/
#if defined (_SLEEP_WHEN_IDLE_) //&& (APP_ENABLE_CONSOLE == 1)
  static void sleepModeHandler(SYS_EventId_t eventId, SYS_EventData_t data);
  static void sleepEventHandler(SYS_EventId_t eventId, SYS_EventData_t data);
  static void ZDO_WakeUpConf(ZDO_WakeUpConf_t *conf);
#endif
static void isBusyOrPollCheck(SYS_EventId_t eventId, SYS_EventData_t data);

#ifdef OTAU_CLIENT 
static void configureImageKeyDone(void);
static void iasAddOTAUClientCluster(void);
#endif
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
};

static ClusterId_t iasACEServerClusterToBindIds[] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  IAS_ZONE_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
};

static AppBindReq_t iasACEBindReq =
{
  .srcEndpoint       = APP_ENDPOINT_IAS_ACE,
  .remoteServersCnt  = ARRAY_SIZE(iasACEClientClusterToBindIds),
  .remoteClientsCnt  = ARRAY_SIZE(iasACEServerClusterToBindIds),
  .groupId           = 0xffff, 
  .remoteServers     = iasACEClientClusterToBindIds,
  .remoteClients     = iasACEServerClusterToBindIds,
  .callback          = NULL,
  .startIdentifyingFn= iasIdentifyStartIdetifyingCb
};

#if defined (_SLEEP_WHEN_IDLE_) //&& (APP_ENABLE_CONSOLE == 1)
  static ZDO_WakeUpReq_t zdoWakeUpReq;
  static SYS_EventReceiver_t sleepEventListener = {.func = sleepEventHandler};
  static SYS_EventReceiver_t sleepModeListener = {.func = sleepModeHandler};
#endif
static SYS_EventReceiver_t zdoBusyPollCheck = { .func = isBusyOrPollCheck};

/******************************************************************************
                    Implementation section
******************************************************************************/

/**************************************************************************//**
\brief Device initialization routine
******************************************************************************/
void appDeviceInit(void)
{
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

#if defined (_SLEEP_WHEN_IDLE_)
#if (ZB_COMMISSIONING_ON_STARTUP  == 1)
  SYS_EnableSleepWhenIdle();
#endif
#if (APP_ENABLE_CONSOLE == 1)
  SYS_SubscribeToEvent(HAL_EVENT_FALLING_ASLEEP, &sleepModeListener);
  SYS_SubscribeToEvent(HAL_EVENT_CONTINUING_SLEEP, &sleepModeListener);
#endif
  SYS_SubscribeToEvent(HAL_EVENT_WAKING_UP, &sleepEventListener);
#endif
  SYS_SubscribeToEvent(BC_EVENT_POLL_REQUEST, &zdoBusyPollCheck);
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

#if defined (_SLEEP_WHEN_IDLE_)
/**************************************************************************//**
  \brief Processes HAL_EVENT_WAKING_UP event

  \param[in] eventId - id of raised event;
  \param[in] data    - event's data.
******************************************************************************/
static void sleepEventHandler(SYS_EventId_t eventId, SYS_EventData_t data)
{
  HAL_SleepControl_t *sleepControl = (HAL_SleepControl_t *)data;

  if (HAL_WAKEUP_SOURCE_EXT_IRQ == sleepControl->wakeupSource)
  {
    zdoWakeUpReq.ZDO_WakeUpConf = ZDO_WakeUpConf;
    ZDO_WakeUpReq(&zdoWakeUpReq);
  }
  (void)eventId; /* Do nothing, to avoid compiler warning */
}
#endif

#if defined (_SLEEP_WHEN_IDLE_) //&& (APP_ENABLE_CONSOLE == 1)
/**************************************************************************//**
  \brief Processes HAL_EVENT_FALL_ASLEEP & HAL_EVENT_CONITUING_SLEEP events

  \param[in] eventId - id of raised event;
  \param[in] data    - event's data.
******************************************************************************/
static void sleepModeHandler(SYS_EventId_t eventId, SYS_EventData_t data)
{
  // when console is enabled, we go to idle mode to handle UART Rx interrupt
  // because UART Rx interrupt will not wake up the MCU from power save or power down modes
  *(HAL_SleepMode_t *)data = HAL_SLEEP_MODE_IDLE;
  (void)eventId;
}
/**************************************************************************//**
  \brief Wake up confirmation handler.

  \param[in] conf - confirmation parameters.
*****************************************************************************/
static void ZDO_WakeUpConf(ZDO_WakeUpConf_t *conf)
{
  (void)conf;
}
#endif

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
