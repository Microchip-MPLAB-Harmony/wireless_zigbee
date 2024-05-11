/*******************************************************************************
  Dimmer Switch Identify cluster Header File

  Company:
    Microchip Technology Inc.

  File Name:
    dsIdentifyCluster.h

  Summary:
    This file contains the Dimmer Switch Identify cluster interface.

  Description:
    This file contains the Dimmer Switch Identify cluster interface.
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
#include <z3device/clusters/include/haClusters.h>
#include <dsIdentifyCluster.h>
#include <zcl/include/zclCommandManager.h>
#include <app_zigbee/zigbee_console/console.h>
#include <pds/include/wlPdsMemIds.h>
#include <z3device/common/include/z3Device.h>
#include <leds.h>
#if defined(BOARD_MEGARF) || defined(BOARD_SAMR21)
#include <ledsExt.h>
#include <lcdExt.h>
#endif
#include <leds.h>
#include <dimmerSwitch.h>
#include <zcl/clusters/include/identifyCluster.h>
#include <app_zigbee/app_zigbee_handler.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define IDENTIFY_EFFECT_TIMER_PERIOD  500U // in milliseconds
#define DEFAULT_IDENTIFY_TIME         3U

#define BLINK_IDENTIFY_TIME           1U   // in seconds
#define BREATHE_IDENTIFY_TIME         15U  // in seconds
#define OKAY_IDENTIFY_TIME            2U   // in seconds
#define CHANNEL_CHANGE_IDENTIFY_TIME  8U   // in seconds

#define LED_MAX_BRIGHTNESS            254U
#define LED_MIN_BRIGHTNESS            2U
#define LED_NO_BRIGHTNESS             0U

/******************************************************************************
                    Prototypes section
******************************************************************************/
static void ZCL_IdentifyAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);

// server side indications
static ZCL_Status_t identifyInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Identify_t *payload);
static ZCL_Status_t identifyQueryInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t triggerEffectInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_TriggerEffect_t *payload);

// client side indication
static ZCL_Status_t identifyQueryResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_IdentifyQueryResponse_t *payload);

// timer functions
static void identifyEffectTimerFired(void);

// some support functions
static void (*identifycb)(void);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_IdentifyClusterServerAttributes_t dsIdentifyClusterServerAttributes =
{
  ZCL_DEFINE_IDENTIFY_CLUSTER_SERVER_ATTRIBUTES()
};

ZCL_IdentifyClusterClientAttributes_t dsIdentifyClusterClientAttributes =
{
  ZCL_DEFINE_IDENTIFY_CLUSTER_CLIENT_ATTRIBUTES()
};

PROGMEM_DECLARE(ZCL_IdentifyClusterCommands_t dsIdentifyCommands) =
{
  ZCL_IDENTIFY_CLUSTER_COMMANDS(identifyInd, identifyQueryInd, triggerEffectInd, identifyQueryResponseInd)
};

/******************************************************************************
                    Static variables section
******************************************************************************/
static HAL_AppTimer_t identifyEffectTimer;

static struct
{
  bool period        : 1;
  bool finish        : 1;
  bool chChangeEffect: 1;
  bool minTime       : 1;
} identificationStatus;

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Identify cluster
******************************************************************************/
void dsIdentifyClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_DIMMER_SWITCH, IDENTIFY_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
  ZCL_Cluster_t *identifyCluster = ZCL_GetCluster(APP_ENDPOINT_COLOR_SCENE_CONTROLLER, IDENTIFY_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
  // All ongoing identification (if any) should be stopped
  dsIdentifyStop();

  // Server attributes init
<#if (IDENTIFY_CLUSTER_CS != "CLIENT")  && (IC_IDENTIFYTIME == true) >
  dsIdentifyClusterServerAttributes.identifyTime.value = 0;
</#if>
<#if (IDENTIFY_CLUSTER_CS != "CLIENT")  && (ICS_CLUSTERREVISION == true) >
  dsIdentifyClusterServerAttributes.clusterVersion.value = CLUSTER_VERSION;
</#if>

  if (cluster)
  {
    cluster->ZCL_AttributeEventInd = ZCL_IdentifyAttributeEventInd;
  }

  // Client attributes init
<#if (IDENTIFY_CLUSTER_CS != "SERVER")  && (ICC_CLUSTERREVISION == true) >
  dsIdentifyClusterClientAttributes.clusterVersion.value = CLUSTER_VERSION;
</#if>
  BSP_SetLedColorHS(255,255);
  identifyCluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
}

/******************************************************************************
*                     SOME SUPPORT FUNCTIONS
******************************************************************************/

/**************************************************************************//**
\brief Makes device to start identify itself

\param[in] time - identifying time in seconds
******************************************************************************/
void dsIdetifyStartIdentifyingCb(uint16_t time, void (*cb)(void))
{
<#if (IDENTIFY_CLUSTER_CS != "CLIENT")  && (IC_IDENTIFYTIME == true)
  dsIdentifyClusterServerAttributes.identifyTime.value = time;
  identifycb = cb;

  dsIdentifyStart(dsIdentifyClusterServerAttributes.identifyTime.value);
</#if>
}

/******************************************************************************
*                 IDENTIFICATION and TRIGGER EFFECT TIMER HANDLER
******************************************************************************/
/**************************************************************************//**
\brief Checks if identification process is in progress

\returns true if it is, false otherwise
******************************************************************************/
bool dsIdentifyIsIdentifying(void)
{
<#if (IDENTIFY_CLUSTER_CS != "CLIENT")  && (IC_IDENTIFYTIME == true)>
  return (dsIdentifyClusterServerAttributes.identifyTime.value > 0);
<#else>
  return false;
</#if>
}

/**************************************************************************//**
\brief Stop identification routine.
******************************************************************************/
void dsIdentifyStop(void)
{
  identificationStatus.period = 0;
  identificationStatus.minTime = false;
  identificationStatus.chChangeEffect = false;

  HAL_StopAppTimer(&identifyEffectTimer);

<#if (IDENTIFY_CLUSTER_CS != "CLIENT")  && (IC_IDENTIFYTIME == true)>
  dsIdentifyClusterServerAttributes.identifyTime.value = 0;
</#if>

  if (identifycb)
    identifycb();

  BSP_SetLedBrightnessLevel(LED_NO_BRIGHTNESS);
}

/**************************************************************************//**
\brief Finish identification routine.
******************************************************************************/
void dsIdentifyFinish(void)
{
  identificationStatus.finish = true;
}

/**************************************************************************//**
\brief Shows identification effect in way specified.

\param[in] identifyTime - identifying period in seconds.
******************************************************************************/
void dsIdentifyStart(uint16_t identifyTime)
{
  HAL_StopAppTimer(&identifyEffectTimer);

  identificationStatus.finish = false;
<#if (IDENTIFY_CLUSTER_CS != "CLIENT")  && (IC_IDENTIFYTIME == true)>
  dsIdentifyClusterServerAttributes.identifyTime.value = identifyTime;
</#if>
  BSP_SetLedBrightnessLevel(LED_NO_BRIGHTNESS);

  identifyEffectTimer.mode = TIMER_REPEAT_MODE;
  identifyEffectTimer.interval = IDENTIFY_EFFECT_TIMER_PERIOD;
  identifyEffectTimer.callback = identifyEffectTimerFired;

  HAL_StartAppTimer(&identifyEffectTimer);
}

/**************************************************************************//**
\brief Timer expiry handler for identifyEffectTimer
******************************************************************************/
static void identifyEffectTimerFired(void)
{
  uint8_t level = 0;
  /**CHANGE - Add description here- some comments*/
  if (identificationStatus.chChangeEffect)
  {
    if (identificationStatus.period)
    {
<#if (IDENTIFY_CLUSTER_CS != "CLIENT")  && (IC_IDENTIFYTIME == true) >
      dsIdentifyClusterServerAttributes.identifyTime.value--;
</#if>
      identificationStatus.period = !identificationStatus.period;
    }
    else
    {
      identificationStatus.period = !identificationStatus.period;
    }

    if (!identificationStatus.minTime)
    {
      level = LED_MAX_BRIGHTNESS;
      identificationStatus.minTime = !identificationStatus.minTime;
    }
    else
    {
      level = LED_MIN_BRIGHTNESS;
    }
  }
  else
  { // Effects such as Blink, Breathe and Okay or Normal Identify
    identificationStatus.period = !identificationStatus.period;

    if (identificationStatus.period)
    {
      level = LED_MAX_BRIGHTNESS;
<#if (IDENTIFY_CLUSTER_CS != "CLIENT")  && (IC_IDENTIFYTIME == true) >
      dsIdentifyClusterServerAttributes.identifyTime.value--;
</#if>
    }
  }

  BSP_SetLedBrightnessLevel(level);
  /**CHANGE - Need to be checked - identificationStatus.finish shall be there or not */
  if ((0 == dsIdentifyClusterServerAttributes.identifyTime.value) || identificationStatus.finish)
  {
    dsIdentifyStop();
  }
}

/******************************************************************************
*                     ATTRIBUTE INDICATION HANDLER FUNCTION
******************************************************************************/
/**************************************************************************//**
\brief Attribute event (writing/reading) callback.

\param[in] addressing - incoming request addressing information.
\param[in] attributeId - attribute identifier.
\param[in] event - attribute event (read/write).
******************************************************************************/
static void ZCL_IdentifyAttributeEventInd(ZCL_Addressing_t *addressing,
  ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  APP_Zigbee_Event_t eventItem;
  eventItem.eventGroup = EVENT_CLUSTER;
  eventItem.eventId = CMD_ZCL_ATTR_IDENTIFY;
  eventItem.eventData.zclAttributeData.addressing = addressing;
  eventItem.eventData.zclAttributeData.attributeId = attributeId;
  eventItem.eventData.zclAttributeData.event = event;

  if ((ZCL_WRITE_ATTRIBUTE_EVENT == event) &&
      (ZCL_IDENTIFY_CLUSTER_IDENTIFY_TIME_ATTRIBUTE_ID == attributeId))
  {
    if (dsIdentifyClusterServerAttributes.identifyTime.value)
    {
      dsIdentifyStart(dsIdentifyClusterServerAttributes.identifyTime.value);
    }
    else
    {
      dsIdentifyStop();
    }
  APP_Zigbee_Handler(eventItem);
  }
}

/******************************************************************************
*                     COMMAND INDICATION HANDLERS
******************************************************************************/
<#if (IDENTIFY_CLUSTER_CS != "CLIENT")  && (IC_IDENTIFYCMD == true) >
/**************************************************************************//**
\brief Callback on receiving Identify command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t identifyInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Identify_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_IDENTIFY;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;

  if (payload->identifyTime)
  {
    dsIdentifyStart(payload->identifyTime);
  }
  else
  {
    dsIdentifyStop();
  }

  RAISE_CALLBACKS_TO_IDENTIFY_SUBSCIBERS(identifySubscribers, identify);

  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (IDENTIFY_CLUSTER_CS != "SERVER")  && (IC_IDENTIFYQUERYCMD == true) >
/**************************************************************************//**
\brief Callback on receiving Identify Query command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t identifyQueryInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_IDENTIFY_QUERY;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;

  RAISE_CALLBACKS_TO_IDENTIFY_SUBSCIBERS(identifySubscribers, identifyQuery);

  if (dsIdentifyClusterServerAttributes.identifyTime.value)
    return sendIdentifyQueryResponse(addressing, APP_ENDPOINT_DIMMER_SWITCH, dsIdentifyClusterServerAttributes.identifyTime.value);

  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (IDENTIFY_CLUSTER_CS != "SERVER")  && (ICC_IDENTIFYQUERYRESCMD == true) >
/**************************************************************************//**
\brief Callback on receiving Identify Query Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t identifyQueryResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_IdentifyQueryResponse_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_IDENTIFY_QUERY_RESPONSE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;

  RAISE_CALLBACKS_TO_IDENTIFY_SUBSCIBERS(identifySubscribers, identifyQueryResponse);

  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>


<#if (IDENTIFY_CLUSTER_CS != "CLIENT")  && (IC_TRIGGEREFFECT == true) >
/**************************************************************************//**
\brief Callback on receive of Trigger Effect command
******************************************************************************/
static ZCL_Status_t triggerEffectInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_TriggerEffect_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_TRIGGER_EFFECT;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;

  /**CHANGE-  Shall be checked the identifying status, if the devcie is identifying, this cmd shall be ignored*/
  switch (payload->effectIdentifier)
  {
    case ZCL_EFFECT_IDENTIFIER_BLINK:
      dsIdentifyStart(BLINK_IDENTIFY_TIME);
      break;

    case ZCL_EFFECT_IDENTIFIER_BREATHE:
      dsIdentifyStart(BREATHE_IDENTIFY_TIME);
      break;

    case ZCL_EFFECT_IDENTIFIER_OKAY:
      dsIdentifyStart(OKAY_IDENTIFY_TIME);
      break;

    case ZCL_EFFECT_IDENTIFIER_CHANNEL_CHANGE:
      identificationStatus.chChangeEffect = true;
      dsIdentifyStart(CHANNEL_CHANGE_IDENTIFY_TIME);
      break;

    case ZCL_EFFECT_IDENTIFIER_FINISH_EFFECT:
      dsIdentifyFinish();
      break;

    case ZCL_EFFECT_IDENTIFIER_STOP_EFFECT:
      dsIdentifyStop();
      break;

    default:
      break;
  }

  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
#endif // (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_CONTROLLER)

// eof dsIdentifyCluster.c
