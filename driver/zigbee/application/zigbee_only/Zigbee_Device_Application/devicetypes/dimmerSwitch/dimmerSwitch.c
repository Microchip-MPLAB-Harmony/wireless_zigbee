/*******************************************************************************
  Dimmer Switch Source File

  Company:
    Microchip Technology Inc.

  File Name:
   dimmerSwitch.c

  Summary:
    This file contains the Dimmer Switch interface.

  Description:
    This file contains the Dimmer Switch interface.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_DIMMER_SWITCH)

/******************************************************************************
                        Includes section
******************************************************************************/
#include <dsClusters.h>
#include <basicCluster.h>
#include <identifyCluster.h>
#include <groupsCluster.h>
#include <dsIdentifyCluster.h>
#include <dsOnOffCluster.h>
#include <dsLevelControlCluster.h>
#include <dsGroupsCluster.h>
#include <dsScenesCluster.h>
//#include <dsPowerConfigurationCluster.h>
#include <z3Device.h>
#include <console.h>
#include <zclSecurityManager.h>
#include <sysIdleHandler.h>
#include <otauService.h>
#include <sleep.h>
#include <halSleep.h>
#include <dsBasicCluster.h>
#include <zclCommandManager.h>

/******************************************************************************
                        Prototypes section
******************************************************************************/
static void isBusyOrPollCheck(SYS_EventId_t eventId, SYS_EventData_t data);
#if defined (_SLEEP_WHEN_IDLE_)
#if (APP_ENABLE_CONSOLE == 1)
static void sleepModeHandler(SYS_EventId_t eventId, SYS_EventData_t data);
#endif
static void sleepEventHandler(SYS_EventId_t eventId, SYS_EventData_t data);
static void ZDO_WakeUpConf(ZDO_WakeUpConf_t *conf);
#endif

/******************************************************************************
                    Local variables section
******************************************************************************/
static ZCL_DeviceEndpoint_t dsEndpoint =
{
  .simpleDescriptor =
  {
    .endpoint            = APP_ENDPOINT_DIMMER_SWITCH,
    .AppProfileId        = PROFILE_ID_HOME_AUTOMATION,
    .AppDeviceId         = APP_Z3DEVICE_ID,
    .AppDeviceVersion    = 0x1,
    .AppInClustersCount  = ARRAY_SIZE(dsServerClusterIds),
    .AppInClustersList   = dsServerClusterIds,
    .AppOutClustersCount = ARRAY_SIZE(dsClientClusterIds),
    .AppOutClustersList  = dsClientClusterIds,
  },
  .serverCluster = dsServerClusters,
  .clientCluster = dsClientClusters,
};

static ClusterId_t dsClientClusterToBindIds[] =
{
  ONOFF_CLUSTER_ID,
  LEVEL_CONTROL_CLUSTER_ID
};

static AppBindReq_t dsBindReq =
{
  .remoteServers     = dsClientClusterToBindIds,
  .remoteServersCnt  = ARRAY_SIZE(dsClientClusterToBindIds),
  .remoteClients     = NULL,// dsServerClusterToBindIds,
  .remoteClientsCnt  = 0, //ARRAY_SIZE(dsServerClusterToBindIds),
  .groupId           = 0xffff, 
  .srcEndpoint       = APP_ENDPOINT_DIMMER_SWITCH,
  .callback          = NULL,
  .startIdentifyingFn= dsIdetifyStartIdentifyingCb
};

static SYS_EventReceiver_t zdoBusyPollCheck = { .func = isBusyOrPollCheck};
#if defined (_SLEEP_WHEN_IDLE_)
static ZDO_WakeUpReq_t zdoWakeUpReq;
static SYS_EventReceiver_t sleepEventListener = {.func = sleepEventHandler};
#if (APP_ENABLE_CONSOLE == 1)
static SYS_EventReceiver_t sleepModeListener = {.func = sleepModeHandler};
#endif
#endif
//static AppBindReq_t* deviceBindReqs[APP_ENDPOINTS_AMOUNT];
extern bool pollRequired;

/******************************************************************************
                        Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Device initialization routine
******************************************************************************/
void appDeviceInit(void)
{
  
#if (APP_ENABLE_CONSOLE == 1) || (APP_DEVICE_EVENTS_LOGGING == 1)
  uartInit();
#endif

#if APP_ENABLE_CONSOLE == 1
  initConsole();
#endif

  APP_RegisterEndpoint(&dsEndpoint, &dsBindReq);

  dsBasicClusterInit();
  dsIdentifyClusterInit();
  dsOnOffClusterInit();
  dsLevelControlClusterInit();
  dsGroupsClusterInit();
  dsScenesClusterInit();
  commandManagerInit();  
#if defined (_SLEEP_WHEN_IDLE_)
#if (APP_ENABLE_CERTIFICATION_EXTENSION == 0)
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
        startOtauClient(&dsClientClusters[DS_CLIENT_CLUSTERS_COUNT - 1]);
      }
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
  dsIdentifyStart(identifyTime);
  (void)colorEffect,(void)enhancedHue;
}

/**************************************************************************//**
\brief Stops identifying on endpoints
******************************************************************************/
void appIdentifyStop(void)
{
  dsIdentifyStop();
}

/**************************************************************************//**
  \brief Processes BC_EVENT_POLL_REQUEST event

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

#if (APP_ENABLE_CONSOLE == 1)
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
#endif // #if (APP_ENABLE_CONSOLE == 1)
#endif // #if defined (_SLEEP_WHEN_IDLE_)
#endif // APP_DEVICE_TYPE_DIMMER_SWITCH
// eof dimmerSwitch.c