/*******************************************************************************
  Control Bridge Identify cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
   cbIdentifyCluster.c

  Summary:
    This file contains the Control Bridge Identify cluster interface.

  Description:
    This file contains the Control Bridge Identify cluster interface.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_CONTROL_BRIDGE)
/******************************************************************************
                    Includes section
******************************************************************************/
#include <haClusters.h>
#include <cbIdentifyCluster.h>
#include <identifyCluster.h>
#include <zclCommandManager.h>
#include <pdsDataServer.h>
#include <z3Device.h>
#include <sysQueue.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define IDENTIFY_TIMER_PERIOD         1000u
#define BLINK_IDENTIFY_TIME           1U   // in seconds
#define BREATHE_IDENTIFY_TIME         15U  // in seconds
#define OKAY_IDENTIFY_TIME            2U   // in seconds
#define CHANNEL_CHANGE_IDENTIFY_TIME  8U   // in seconds

#define LED_MAX_BRIGHTNESS            254U
#define LED_MIN_BRIGHTNESS            2U
#define LED_NO_BRIGHTNESS             0U
#define IDENTIFY_EFFECT_TIMER_PERIOD  500U // in milliseconds

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t identifyInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Identify_t *payload);
static ZCL_Status_t identifyQueryInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t identifyQueryResponseInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_IdentifyQueryResponse_t *payload);
static ZCL_Status_t triggerEffectInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_TriggerEffect_t *payload);
static void identifyTimerFired(void);
static void ZCL_IdentifyAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
// timer functions
static void identifyEffectTimerFired(void);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_IdentifyClusterServerAttributes_t cbIdentifyClusterServerAttributes =
{
  ZCL_DEFINE_IDENTIFY_CLUSTER_SERVER_ATTRIBUTES()
};

ZCL_IdentifyClusterClientAttributes_t cbIdentifyClusterClientAttributes =
{
  ZCL_DEFINE_IDENTIFY_CLUSTER_CLIENT_ATTRIBUTES()
};

PROGMEM_DECLARE(ZCL_IdentifyClusterCommands_t cbIdentifyCommands) =
{
  ZCL_IDENTIFY_CLUSTER_COMMANDS(identifyInd, identifyQueryInd, triggerEffectInd, identifyQueryResponseInd)
};

extern QueueDescriptor_t identifySubscribers;
/******************************************************************************
                    Static variables section
******************************************************************************/
static HAL_AppTimer_t identifyTimer;
//static DECLARE_QUEUE(subscribers);
static HAL_AppTimer_t identifyEffectTimer;

static struct
{
  bool period        : 1;
  bool finish        : 1;
  bool chChangeEffect: 1;
  bool minTime       : 1;
} identificationStatus;

static void (*identifycb)(void);

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Identify cluster
******************************************************************************/
void cbIdentifyClusterInit(void)
{
  cbIdentifyClusterServerAttributes.identifyTime.value = 0;
  cbIdentifyClusterServerAttributes.clusterVersion.value = CLUSTER_VERSION;
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_CONTROL_BRIDGE, IDENTIFY_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
  ZCL_Cluster_t *identifyCluster = ZCL_GetCluster(APP_ENDPOINT_COLOR_SCENE_CONTROLLER, IDENTIFY_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
  if (cluster)
    cluster->ZCL_AttributeEventInd = ZCL_IdentifyAttributeEventInd;

  identifyTimer.interval = IDENTIFY_TIMER_PERIOD;
  identifyTimer.mode     = TIMER_REPEAT_MODE;
  identifyTimer.callback = identifyTimerFired;
  identifyCluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
}

/**************************************************************************//**
\brief Makes device to start identify itself

\param[in] time - identifying time in seconds
******************************************************************************/
void cbIdetifyStartIdentifyingCb(uint16_t time, void (*cb)(void))
{
  cbIdentifyClusterServerAttributes.identifyTime.value = time;
  identifycb = cb;

  cbIdentifyStart(cbIdentifyClusterServerAttributes.identifyTime.value);
}

/**************************************************************************//**
\brief Shows identification effect in way specified.

\param[in] identifyTime - identifying period in seconds.
******************************************************************************/
void cbIdentifyStart(uint16_t identifyTime)
{
  HAL_StopAppTimer(&identifyEffectTimer);

  identificationStatus.finish = false;

  cbIdentifyClusterServerAttributes.identifyTime.value = identifyTime;

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

  if (identificationStatus.chChangeEffect)
  {
    if (identificationStatus.period)
    {
      cbIdentifyClusterServerAttributes.identifyTime.value--;
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
      cbIdentifyClusterServerAttributes.identifyTime.value--;
    }
  }

  BSP_SetLedBrightnessLevel(level);

  (void)level;

  if ((0 == cbIdentifyClusterServerAttributes.identifyTime.value) || identificationStatus.finish)
  {
    cbIdentifyStop();
  }
}

/**************************************************************************//**
\brief Finish identification routine.
******************************************************************************/
void cbIdentifyFinish(void)
{
  identificationStatus.finish = true;
}

/**************************************************************************//**
\brief Stop identification routine.
******************************************************************************/
void cbIdentifyStop(void)
{
  identificationStatus.period = 0;
  identificationStatus.minTime = false;
  identificationStatus.chChangeEffect = false;

  HAL_StopAppTimer(&identifyEffectTimer);

  cbIdentifyClusterServerAttributes.identifyTime.value = 0;
  
  if (identifycb)
    identifycb();

  BSP_SetLedBrightnessLevel(LED_NO_BRIGHTNESS);
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

  if (payload->identifyTime)
  {
    cbIdentifyStart(payload->identifyTime);
  }
  else
  {
    cbIdentifyStop();
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

  if (cbIdentifyClusterServerAttributes.identifyTime.value)
    return sendIdentifyQueryResponse(addressing, APP_ENDPOINT_CONTROL_BRIDGE, cbIdentifyClusterServerAttributes.identifyTime.value);

  RAISE_CALLBACKS_TO_IDENTIFY_SUBSCIBERS(identifySubscribers, identifyQuery);

  (void)payload, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
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
  appSnprintf("->IdentifyQueryResponse, addr = %d, timeout = 0x%04x\r\n", addressing->addr.shortAddress, payload->timeout);

  RAISE_CALLBACKS_TO_IDENTIFY_SUBSCIBERS(identifySubscribers, identifyQueryResponse);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Identify timer has fired
******************************************************************************/
static void identifyTimerFired(void)
{
  --cbIdentifyClusterServerAttributes.identifyTime.value;
  // TO DO: toggle LED
  if (!cbIdentifyClusterServerAttributes.identifyTime.value)
  {
    HAL_StopAppTimer(&identifyTimer);
    identifycb();
    // TO DO: turn LED off
  }
}
/**************************************************************************//**
\brief Identify reset subscribers queue
******************************************************************************/
void idenityResetSubscribers()
{
  resetQueue(&identifySubscribers);
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
    if (cbIdentifyClusterServerAttributes.identifyTime.value)
    {
      cbIdentifyStart(cbIdentifyClusterServerAttributes.identifyTime.value);
    }
    else
    {
      cbIdentifyStop();
    }
    (void)addressing;
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
      cbIdentifyStart(BLINK_IDENTIFY_TIME);
      break;

    case ZCL_EFFECT_IDENTIFIER_BREATHE:
      cbIdentifyStart(BREATHE_IDENTIFY_TIME);
      break;

    case ZCL_EFFECT_IDENTIFIER_OKAY:
      cbIdentifyStart(OKAY_IDENTIFY_TIME);
      break;

    case ZCL_EFFECT_IDENTIFIER_CHANNEL_CHANGE:
      identificationStatus.chChangeEffect = true;
      cbIdentifyStart(CHANNEL_CHANGE_IDENTIFY_TIME);
      break;

    case ZCL_EFFECT_IDENTIFIER_FINISH_EFFECT:
      cbIdentifyFinish();
      break;

    case ZCL_EFFECT_IDENTIFIER_STOP_EFFECT:
      cbIdentifyStop();
      break;

    default:
      break;
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

#endif // APP_DEVICE_TYPE_CONTROL_BRIDGE

// eof cbIdentifyCluster.c

