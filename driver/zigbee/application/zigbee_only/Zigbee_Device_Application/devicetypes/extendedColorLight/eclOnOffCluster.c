/*******************************************************************************
  Extended Color Light On/Off cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
   eclOnOffCluster.c

  Summary:
    This file contains the Extended Color Light On/Off cluster interface.

  Description:
    This file contains the Extended Color Light On/Off cluster interface.
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

#ifdef APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <eclOnOffCluster.h>
#include <eclLevelControlCluster.h>
#include <eclScenesCluster.h>
#include <uartManager.h>
#include <pdsDataServer.h>
#include <leds.h>
#include <z3Device.h>
#if defined(BOARD_MEGARF) || defined(BOARD_SAMR21)
#include <ledsExt.h>
#include <lcdExt.h>
#endif

/******************************************************************************
                    Defines section
******************************************************************************/
#define UPDATE_TIMER_INTERVAL    100 // 1/10th of a second as per specification
#define FADE_TIMER_INTERVAL      UPDATE_TIMER_INTERVAL

/******************************************************************************
                    Types section
******************************************************************************/
typedef struct
{
  HAL_AppTimer_t timer;
  uint8_t        firstInterval;
  uint8_t        secondInterval;
  uint8_t        currentLevel;
  int16_t        delta;
  uint8_t        transitionTime;
} FadeMem_t;

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t onInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t offInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t toggleInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t offWithEffectInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_OffWithEffect_t *payload);
static ZCL_Status_t onWithRecallGlobalSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t onWithTimedOff(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_OnWithTimedOff_t *payload);

static void startDeviceUpdate(void);
static void stopDeviceUpdate(void);

static void displayStatus(void);

static void updateOnOffState(void);
//static void setOnOff(bool onOff);

static void fadeTimerFired(void);
static void processOffEffect(uint8_t effectId, uint8_t effectVariant);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_OnOffClusterServerAttributes_t eclOnOffClusterServerAttributes =
{
  ZCL_DEFINE_ONOFF_CLUSTER_SERVER_ATTRIBUTES(ONOFF_VAL_MIN_REPORT_PERIOD, ONOFF_VAL_MAX_REPORT_PERIOD)
};

ZCL_OnOffClusterCommands_t         eclOnOffCommands =
{
  ZCL_DEFINE_ONOFF_CLUSTER_COMMANDS(onInd, offInd, toggleInd, offWithEffectInd, onWithRecallGlobalSceneInd, onWithTimedOff)
};

/******************************************************************************
                    Static variables section
******************************************************************************/
static HAL_AppTimer_t updateTimer;
static FadeMem_t fadeMem;

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes On/Off cluster
******************************************************************************/
void onOffClusterInit(void)
{
  eclOnOffClusterServerAttributes.onOff.value = false;
  eclOnOffClusterServerAttributes.globalSceneControl.value = true;
  eclOnOffClusterServerAttributes.onTime.value = 0;
  eclOnOffClusterServerAttributes.offWaitTime.value = 0;
  eclOnOffClusterServerAttributes.clusterVersion.value = 1;

  updateTimer.mode = TIMER_REPEAT_MODE;
  updateTimer.interval = UPDATE_TIMER_INTERVAL;
  updateTimer.callback = updateOnOffState;

  fadeMem.timer.mode     = TIMER_REPEAT_MODE;
  fadeMem.timer.interval = FADE_TIMER_INTERVAL;
  fadeMem.timer.callback = fadeTimerFired;

  displayStatus();
}

/**************************************************************************//**
\brief Set Extension Field Set
******************************************************************************/
void onOffClusterSetExtensionField(bool onOff)
{
  if (eclOnOffClusterServerAttributes.onOff.value != onOff)
  {
    if (!onOff)
    {
      eclOnOffClusterServerAttributes.onTime.value = 0;
    }
    else
    {
      eclOnOffClusterServerAttributes.offWaitTime.value = 0;
      stopDeviceUpdate();
    }

    eclOnOffClusterServerAttributes.onOff.value = onOff;
    displayStatus();

    PDS_Store(HA_APP_MEMORY_MEM_ID);
  }
}

/**************************************************************************//**
\brief Checks, if device is in On state

\return True, if device is in On state; false - otherwise.
******************************************************************************/
bool isDeviceOn(void)
{
  return eclOnOffClusterServerAttributes.onOff.value;
}

/**************************************************************************//**
\brief Start device update procedure
******************************************************************************/
static void startDeviceUpdate(void)
{
  HAL_StopAppTimer(&updateTimer);
  HAL_StartAppTimer(&updateTimer);
}

/**************************************************************************//**
\brief Stop device update procedure
******************************************************************************/
void stopDeviceUpdate(void)
{
  HAL_StopAppTimer(&updateTimer);
}

/**************************************************************************//**
\brief On/Off cluster update timer callback
******************************************************************************/
static void updateOnOffState(void)
{
  if (eclOnOffClusterServerAttributes.onOff.value)
  {
    if (eclOnOffClusterServerAttributes.onTime.value)
    {
      eclOnOffClusterServerAttributes.onTime.value--;
    }
    else
    {
      eclOnOffClusterServerAttributes.offWaitTime.value = 0;
      eclOnOffSetOnOffState(false);
    }
  }
  else
  {
    if (eclOnOffClusterServerAttributes.offWaitTime.value)
    {
      eclOnOffClusterServerAttributes.offWaitTime.value--;
    }
    else
    {
      stopDeviceUpdate();
    }
  }
}

/**************************************************************************//**
\brief Sets on/off state
******************************************************************************/
void eclOnOffSetOnOffState(bool state)
{
  bool previousOnOffValue = eclOnOffClusterServerAttributes.onOff.value;
  eclOnOffClusterServerAttributes.onOff.value = state;
  scenesClusterInvalidate();
  displayStatus();

  if (state)
  {
    LEDS_SET_BRIGHTNESS(eclLevelControlClusterServerAttributes.currentLevel.value);
  }
  else
  {
    LEDS_SET_BRIGHTNESS(0);
  }

  ZCL_ReportOnChangeIfNeeded(&eclOnOffClusterServerAttributes.onOff);

  if (previousOnOffValue != state)
  {
    scenesClusterInvalidate();
    PDS_Store(HA_APP_MEMORY_MEM_ID);
  }
}

/**************************************************************************//**
\brief Display current On/Off status.
******************************************************************************/
static void displayStatus(void)
{
  LCD_PRINT(0, 0, eclOnOffClusterServerAttributes.onOff.value ? "I" : "O");
}

/**************************************************************************//**
\brief gets on/off state

\return on/off state
******************************************************************************/
bool onOffState(void)
{
  return eclOnOffClusterServerAttributes.onOff.value;
}

/**************************************************************************//**
\brief Fade timer has fired
******************************************************************************/
static void fadeTimerFired(void)
{
  if (fadeMem.firstInterval)
  {
    fadeMem.firstInterval--;

    int32_t remainingTime = fadeMem.firstInterval;
    int16_t targetLevel = MIN((uint16_t)fadeMem.currentLevel + fadeMem.delta, UINT8_MAX);
    int16_t newLevel    = targetLevel - (fadeMem.delta * remainingTime) / (int32_t)fadeMem.transitionTime;

    LEDS_SET_BRIGHTNESS(newLevel);
    (void)newLevel;
  }
  else if(fadeMem.secondInterval)
  {
    fadeMem.firstInterval  = fadeMem.secondInterval;
    fadeMem.transitionTime = fadeMem.secondInterval;
    fadeMem.secondInterval = 0;
    fadeMem.currentLevel   = MIN((uint16_t)fadeMem.currentLevel + fadeMem.delta, UINT8_MAX);
    fadeMem.delta          = -fadeMem.currentLevel;
    fadeTimerFired();
  }
  else
    HAL_StopAppTimer(&fadeMem.timer);
}

/**************************************************************************//**
\brief Processes efefect of OffWithEffect command

\param[in] effectId      - effect identifier;
\param[in] effectVariant - effect variant
******************************************************************************/
static void processOffEffect(uint8_t effectId, uint8_t effectVariant)
{
  fadeMem.currentLevel = eclLevelControlClusterServerAttributes.currentLevel.value;

  if (0 == effectId)
  {
    if (0 == effectVariant)
    {
      fadeMem.firstInterval  = 8;
      fadeMem.secondInterval = 0;
      fadeMem.delta          = -fadeMem.currentLevel;
    }
    if (1 == effectVariant)
    {
      LEDS_SET_BRIGHTNESS(0);
      return;
    }
    if (2 == effectVariant)
    {
      fadeMem.firstInterval  = 8;
      fadeMem.secondInterval = 120;
      fadeMem.delta          = -fadeMem.currentLevel / 2;
    }
  }
  if (1 == effectId)
    if (0 == effectVariant)
    {
      fadeMem.firstInterval  = 5;
      fadeMem.secondInterval = 10;
      fadeMem.delta          = ((uint16_t)fadeMem.currentLevel * 2) / 10;
    }

  if ((signed)UINT8_MAX < fadeMem.delta + fadeMem.currentLevel)
    fadeMem.delta = UINT8_MAX - fadeMem.currentLevel;
  fadeMem.transitionTime = fadeMem.firstInterval;
  HAL_StopAppTimer(&fadeMem.timer);
  HAL_StartAppTimer(&fadeMem.timer);
}

/**************************************************************************//**
\brief Set Global Scene Control attribute to 'true'
******************************************************************************/
void onOffClusterSetGlobalSceneControl(void)
{
  eclOnOffClusterServerAttributes.globalSceneControl.value = true;
}

/**************************************************************************//**
\brief Callback on receiving On command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
ZCL_Status_t onInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  if (0 == eclOnOffClusterServerAttributes.onTime.value)
  {
    eclOnOffClusterServerAttributes.offWaitTime.value = 0;
    stopDeviceUpdate();
  }

  onOffClusterSetGlobalSceneControl();
  eclOnOffSetOnOffState(true);

  appSnprintf("On\r\n");

  (void)addressing;
  (void)payloadLength;
  (void)payload;

  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Off command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
ZCL_Status_t offInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  eclOnOffClusterServerAttributes.onTime.value = 0;
  eclOnOffSetOnOffState(false);

  appSnprintf("Off\r\n");

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Toggle command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
ZCL_Status_t toggleInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  if (false == eclOnOffClusterServerAttributes.onOff.value)
  {
    if (0 == eclOnOffClusterServerAttributes.onTime.value)
      eclOnOffClusterServerAttributes.offWaitTime.value = 0;

    eclOnOffSetOnOffState(true);
    onOffClusterSetGlobalSceneControl();
  }
  else
  {
    eclOnOffClusterServerAttributes.onTime.value = 0;
    eclOnOffSetOnOffState(false);
  }

  if (eclOnOffClusterServerAttributes.onOff.value)
  {
    eclOnOffClusterServerAttributes.onTime.value = 0;
  }
  else
  {
    if(!eclOnOffClusterServerAttributes.onTime.value)
    {
      eclOnOffClusterServerAttributes.offWaitTime.value = 0;
      stopDeviceUpdate();
    }
  }

  appSnprintf("Toggle\r\n");

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Off with effect command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t offWithEffectInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_OffWithEffect_t *payload)
{
  if (eclOnOffClusterServerAttributes.globalSceneControl.value)
  {
    eclOnOffClusterServerAttributes.globalSceneControl.value = false;
    scenesClusterStoreGlobalScene();
  }

  eclOnOffClusterServerAttributes.onOff.value = false;
  eclOnOffClusterServerAttributes.onTime.value = 0;

  scenesClusterInvalidate();
  displayStatus();
  PDS_Store(HA_APP_MEMORY_MEM_ID);

  processOffEffect(payload->effectIdentifier, payload->effectVariant);

  appSnprintf("OffWithEffect %d %d\r\n", payload->effectIdentifier, payload->effectVariant);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving on with recall global scene command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t onWithRecallGlobalSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  eclOnOffSetOnOffState(true);
  // eclOnOffClusterServerAttributes.onTime.value = 0;
  // eclOnOffClusterServerAttributes.offWaitTime.value = 0;
  // stopDeviceUpdate();

  if (false == eclOnOffClusterServerAttributes.globalSceneControl.value)
  {
    scenesClusterRecallGlobalScene();

    if (0 == eclOnOffClusterServerAttributes.onTime.value)
    {
      eclOnOffClusterServerAttributes.offWaitTime.value = 0;
    }

    eclOnOffClusterServerAttributes.globalSceneControl.value = true;
  }

  if (!eclOnOffClusterServerAttributes.onTime.value)
  {
    eclOnOffClusterServerAttributes.offWaitTime.value = 0;
    stopDeviceUpdate();
  }

  appSnprintf("OnWithRecallGlobalScene\r\n");

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving on with timed off command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t onWithTimedOff(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_OnWithTimedOff_t *payload)
{
  if (payload->onOffControl & ZCL_ON_OFF_CLUSTER_ACCEPT_ONLY_WHEN_ON)
  {
    if (false == eclOnOffClusterServerAttributes.onOff.value)
      return ZCL_SUCCESS_STATUS;
  }

  if (eclOnOffClusterServerAttributes.offWaitTime.value > 0 &&
      false == eclOnOffClusterServerAttributes.onOff.value)
  {
    eclOnOffClusterServerAttributes.offWaitTime.value = MIN(payload->offWaitTime,
        eclOnOffClusterServerAttributes.offWaitTime.value);
  }
  else
  {
    eclOnOffClusterServerAttributes.onTime.value = MAX(payload->onTime,
        eclOnOffClusterServerAttributes.onTime.value);

    eclOnOffClusterServerAttributes.offWaitTime.value = payload->offWaitTime;

    eclOnOffSetOnOffState(true);
  }

  if (eclOnOffClusterServerAttributes.onTime.value < 0xffff &&
      eclOnOffClusterServerAttributes.offWaitTime.value < 0xffff)
  {
    startDeviceUpdate();
  }

  appSnprintf("OnWithTimedOff %d %d %d\r\n", payload->onOffControl, payload->onTime, payload->offWaitTime);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

#endif // APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT

// eof dlOnOffCluster.c
