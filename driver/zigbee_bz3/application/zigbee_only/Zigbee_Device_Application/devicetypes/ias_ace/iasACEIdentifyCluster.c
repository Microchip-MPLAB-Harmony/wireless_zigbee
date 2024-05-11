/*******************************************************************************
  IAS ACE Identify Cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    iasACEIdentifyCluster.c

  Summary:
    This file contains the IAS ACE Identify Cluster interface.

  Description:
    This file contains the IAS ACE Identify Cluster interface.
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
#include <z3device/ias_ace/include/iasaceidentifycluster.h>
#include <zcl/clusters/include/identifyCluster.h>
#include <z3device/clusters/include/haClusters.h>
#include <app_zigbee/zigbee_console/console.h>
#include <zcl/include/zclCommandManager.h>
#include <pds/include/wlPdsMemIds.h>
#include <z3device/common/include/z3Device.h>
#if defined(BOARD_MEGARF) || defined(BOARD_SAMR21)
#include <ledsExt.h>
#include <lcdExt.h>
#endif

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
static ZCL_Status_t identifyInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Identify_t *payload);
static ZCL_Status_t identifyQueryInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t identifyQueryResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_IdentifyQueryResponse_t *payload);
static ZCL_Status_t triggerEffectInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_TriggerEffect_t *payload);
static void ZCL_IdentifyAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
static void identifyEffectTimerFired(void);
// Support functions
static void iasIdentifyFinish(void);
static void (*identifycb)(void);
/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_IdentifyClusterServerAttributes_t iasACEIdentifyClusterServerAttributes =
{
  ZCL_DEFINE_IDENTIFY_CLUSTER_SERVER_ATTRIBUTES()
};

ZCL_IdentifyClusterClientAttributes_t iasACEIdentifyClusterClientAttributes =
{
  ZCL_DEFINE_IDENTIFY_CLUSTER_CLIENT_ATTRIBUTES()
};

PROGMEM_DECLARE (ZCL_IdentifyClusterCommands_t   iasACEIdentifyCommands) =
{
  ZCL_IDENTIFY_CLUSTER_COMMANDS(identifyInd, identifyQueryInd, triggerEffectInd, identifyQueryResponseInd)
};


/******************************************************************************
                    Static variables section
******************************************************************************/
static HAL_AppTimer_t identifyTimer;

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
void iasIdentifyClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_IAS_ACE, IDENTIFY_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
  ZCL_Cluster_t *identifyCluster = ZCL_GetCluster(APP_ENDPOINT_IAS_ACE, IDENTIFY_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
  
  if (cluster)
    cluster->ZCL_AttributeEventInd = ZCL_IdentifyAttributeEventInd;

  iasIdentifyStop();
  identifyCluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
  LEDS_SET_COLOR_HS(255,255);
  iasACEIdentifyClusterClientAttributes.clusterVersion.value = IDENTIFY_CLUSTER_VERSION;
  iasACEIdentifyClusterServerAttributes.identifyTime.value = 0;
}

/**************************************************************************//**
\brief Makes device to start identify itself

\param[in] time - identifying time in seconds
******************************************************************************/
void iasIdentifyStartIdetifyingCb(uint16_t time, void (*cb)(void))
{
  iasACEIdentifyClusterServerAttributes.identifyTime.value = time;
  identifycb = cb;
  iasIdentifyStart(iasACEIdentifyClusterServerAttributes.identifyTime.value);
}

/**************************************************************************//**
\brief Stops Identify cluster
******************************************************************************/
void iasIdentifyStop(void)
{
  identificationStatus.period = 0;
  identificationStatus.minTime = false;
  identificationStatus.chChangeEffect = false;
  
  HAL_StopAppTimer(&identifyTimer);
  iasACEIdentifyClusterServerAttributes.identifyTime.value = 0;
  if (identifycb)
    identifycb();

  LEDS_SET_BRIGHTNESS(LED_NO_BRIGHTNESS);
}

/**************************************************************************//**
\brief Finish identification routine.
******************************************************************************/
static void iasIdentifyFinish(void)
{
  identificationStatus.finish = true;
}

/**************************************************************************//**
\brief Shows identification effect in way specified.

\param[in] identifyTime - identifying period in seconds.
******************************************************************************/
void iasIdentifyStart(uint16_t identifyTime)
{
  HAL_StopAppTimer(&identifyTimer);

  identificationStatus.finish = false;
  iasACEIdentifyClusterServerAttributes.identifyTime.value = identifyTime;
  LEDS_SET_BRIGHTNESS(LED_NO_BRIGHTNESS);

  identifyTimer.mode = TIMER_REPEAT_MODE;
  identifyTimer.interval = IDENTIFY_EFFECT_TIMER_PERIOD;
  identifyTimer.callback = identifyEffectTimerFired;

  HAL_StartAppTimer(&identifyTimer);
}
/**************************************************************************//**
\brief Callback on receiving Identify command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t identifyInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Identify_t *payload)
{
  appSnprintf("->Identify\r\n");

  iasACEIdentifyClusterServerAttributes.identifyTime.value = payload->identifyTime;

  if (payload->identifyTime)
  {
    iasIdentifyStart(payload->identifyTime);
  }
  else
  {
    iasIdentifyStop();
  }

  RAISE_CALLBACKS_TO_IDENTIFY_SUBSCIBERS(identifySubscribers, identify);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Callback on receiving Identify Query command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t identifyQueryInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  appSnprintf("->IdentifyQuery\r\n");
  
  if (iasACEIdentifyClusterServerAttributes.identifyTime.value)
    return sendIdentifyQueryResponse(addressing, APP_ENDPOINT_IAS_ACE, iasACEIdentifyClusterServerAttributes.identifyTime.value);

  RAISE_CALLBACKS_TO_IDENTIFY_SUBSCIBERS(identifySubscribers, identifyQuery);

  (void)payload, (void)payloadLength;
  return ZCL_SUCCESS_WITH_DEFAULT_RESPONSE_STATUS;;
}
/**************************************************************************//**
\brief Callback on receiving Identify Query Response command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t identifyQueryResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_IdentifyQueryResponse_t *payload)
{
  appSnprintf("->IdentifyQueryResponse, addr = %d\r\n", addressing->addr.shortAddress);

  RAISE_CALLBACKS_TO_IDENTIFY_SUBSCIBERS(identifySubscribers, identifyQueryResponse);

  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Attribute event (writing/reading) callback.

\param[in] addressing - incoming request addressing information.
\param[in] attributeId - attribute identifier.
\param[in] event - attribute event (read/write).
******************************************************************************/
static void ZCL_IdentifyAttributeEventInd(ZCL_Addressing_t *addressing,
  ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  if ((ZCL_WRITE_ATTRIBUTE_EVENT == event) &&
      (ZCL_IDENTIFY_CLUSTER_IDENTIFY_TIME_ATTRIBUTE_ID == attributeId))
  {
    if (iasACEIdentifyClusterServerAttributes.identifyTime.value)
    {
      iasIdentifyStart(iasACEIdentifyClusterServerAttributes.identifyTime.value);
    }
    else
    {
      iasIdentifyStop();
    }
    HAL_StopAppTimer(&identifyTimer);
    if (iasACEIdentifyClusterServerAttributes.identifyTime.value)
      HAL_StartAppTimer(&identifyTimer);

    (void)addressing;
  }
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
      iasACEIdentifyClusterServerAttributes.identifyTime.value--;
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
      iasACEIdentifyClusterServerAttributes.identifyTime.value--;
    }    
  }

  LEDS_SET_BRIGHTNESS(level);
  (void)level;
  /**CHANGE - Need to be checked - identificationStatus.finish shall be there or not */
  if ((0 == iasACEIdentifyClusterServerAttributes.identifyTime.value) || identificationStatus.finish)
  {
    iasIdentifyStop();
  }
}
/**************************************************************************//**
\brief Callback on receive of Trigger Effect command
******************************************************************************/
static ZCL_Status_t triggerEffectInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_TriggerEffect_t *payload)
{
  appSnprintf("->TriggerEffect %d\r\n",  payload->effectIdentifier);

  switch (payload->effectIdentifier)
  {
    case ZCL_EFFECT_IDENTIFIER_BLINK:
      iasIdentifyStart(BLINK_IDENTIFY_TIME);
      break;

    case ZCL_EFFECT_IDENTIFIER_BREATHE:
      iasIdentifyStart(BREATHE_IDENTIFY_TIME);
      break;

    case ZCL_EFFECT_IDENTIFIER_OKAY:
      iasIdentifyStart(OKAY_IDENTIFY_TIME);
      break;

    case ZCL_EFFECT_IDENTIFIER_CHANNEL_CHANGE:
      identificationStatus.chChangeEffect = true;
      iasIdentifyStart(CHANNEL_CHANGE_IDENTIFY_TIME);
      break;

    case ZCL_EFFECT_IDENTIFIER_FINISH_EFFECT:
      iasIdentifyFinish();
      break;

    case ZCL_EFFECT_IDENTIFIER_STOP_EFFECT:
      iasIdentifyStop();
      break;

    default:
      break;
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}
#endif // APP_DEVICE_TYPE_IAS_ACE

// eof iasACEIdentifyCluster.c

