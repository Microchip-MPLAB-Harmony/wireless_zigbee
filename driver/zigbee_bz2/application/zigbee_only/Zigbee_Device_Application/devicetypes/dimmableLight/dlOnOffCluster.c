/*******************************************************************************
  Dimmable Light On/Off cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    dlOnOffCluster.c

  Summary:
    This file contains the Dimmable Light On/Off cluster interface.

  Description:
    This file contains the Dimmable Light On/Off cluster interface.
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

#ifdef APP_DEVICE_TYPE_DIMMABLE_LIGHT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <dlOnOffCluster.h>
#include <dlScenesCluster.h>
#include <console.h>
#include <pdsDataServer.h>
#include <leds.h>

/******************************************************************************
                    Defines section
******************************************************************************/
#define UPDATE_TIMER_INTERVAL    100 // 1/10th of a second as per specification

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t onInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t offInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t toggleInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t offWithEffectInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_OffWithEffect_t *payload);
static ZCL_Status_t onWithRecallGlobalSceneInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t onWithTimedOff(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_OnWithTimedOff_t *payload);

//static bool isDeviceOn(void);
static void startDeviceUpdate(void);

static void updateOnOffState(void);
static void setOnOff(bool onOff);
static void recallGlobalScene(void);
static void storeGlobalScene(void);
/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_OnOffClusterServerAttributes_t dlOnOffClusterServerAttributes =
{
  ZCL_DEFINE_ONOFF_CLUSTER_SERVER_ATTRIBUTES(ONOFF_VAL_MIN_REPORT_PERIOD, ONOFF_VAL_MAX_REPORT_PERIOD)
};

ZCL_OnOffClusterCommands_t         dlOnOffCommands =
{
  ZCL_DEFINE_ONOFF_CLUSTER_COMMANDS(onInd, offInd, toggleInd, offWithEffectInd, onWithRecallGlobalSceneInd, onWithTimedOff)
};

/******************************************************************************
                    Static variables section
******************************************************************************/
static HAL_AppTimer_t updateTimer;

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes On/Off cluster
******************************************************************************/
void onOffClusterInit(void)
{
  dlOnOffClusterServerAttributes.onOff.value = false;
  
  dlOnOffClusterServerAttributes.globalSceneControl.value = true;
  dlOnOffClusterServerAttributes.onTime.value = 0x0000u;
  dlOnOffClusterServerAttributes.offWaitTime.value = 0x0000u;
  
  dlOnOffClusterServerAttributes.clusterVersion.value = 0x0001u;
  
  updateTimer.mode = TIMER_REPEAT_MODE;
  updateTimer.interval = UPDATE_TIMER_INTERVAL;
  updateTimer.callback = updateOnOffState;
}

/**************************************************************************//**
\brief Checks, if device is in On state

\return True, if device is in On state; false - otherwise.
******************************************************************************/
/*static bool isDeviceOn(void)
{
  return dlOnOffClusterServerAttributes.onOff.value;
}*/

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
  if (dlOnOffClusterServerAttributes.onOff.value)
  {
    if (dlOnOffClusterServerAttributes.onTime.value)
    {
      dlOnOffClusterServerAttributes.onTime.value--;
    }
    else
    {
      dlOnOffClusterServerAttributes.offWaitTime.value = 0;
      setOnOff(false);
    }
  }
  else
  {
    if (dlOnOffClusterServerAttributes.offWaitTime.value)
    {
      dlOnOffClusterServerAttributes.offWaitTime.value--;
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
void onOffSetOnOffState(bool state)
{
  bool previousOnOffValue = dlOnOffClusterServerAttributes.onOff.value;
  
  if (state)
  {
    BSP_OnLed(LED_FIRST);
  }
  else
  {
    BSP_OffLed(LED_FIRST);
  }

  dlOnOffClusterServerAttributes.onOff.value = state;
  ZCL_ReportOnChangeIfNeeded(&dlOnOffClusterServerAttributes.onOff);
  if (previousOnOffValue != state)
  {
    scenesInvalidate();
    PDS_Store(APP_DL_ONOFF_MEM_ID);
  }
}

/**************************************************************************//**
\brief gets on/off state

\return on/off state
******************************************************************************/
bool onOffState(void)
{
  return dlOnOffClusterServerAttributes.onOff.value;
}
/**************************************************************************//**
\brief Set Extension Field Set
******************************************************************************/
static void setOnOff(bool onOff)
{
  dlOnOffClusterServerAttributes.onOff.value = onOff;
  scenesInvalidate();

  if (onOff)
  {
    BSP_OnLed(LED_FIRST);
  }
  else
  {
    BSP_OffLed(LED_FIRST);
  }

  PDS_Store(HA_APP_MEMORY_MEM_ID);
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
  appSnprintf("On\r\n");

  onOffSetOnOffState(true);
  
  dlOnOffClusterServerAttributes.globalSceneControl.value = true;
  dlOnOffClusterServerAttributes.onOff.value = true;
  
  if (!dlOnOffClusterServerAttributes.onTime.value)
  {
    dlOnOffClusterServerAttributes.offWaitTime.value = 0;
    stopDeviceUpdate();
  }

  (void)addressing, (void)payloadLength, (void)payload;
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
  appSnprintf("Off\r\n");

  onOffSetOnOffState(false);
  
  dlOnOffClusterServerAttributes.onTime.value = 0;

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
  appSnprintf("Toggle\r\n");

  onOffSetOnOffState(!dlOnOffClusterServerAttributes.onOff.value);
  
  if (dlOnOffClusterServerAttributes.onOff.value)
    BSP_OnLed(LED_FIRST);
  else
    BSP_OffLed(LED_FIRST);
  
  if (dlOnOffClusterServerAttributes.onOff.value)
  {
    dlOnOffClusterServerAttributes.onTime.value = 0;
  }
  else
  {
    if(!dlOnOffClusterServerAttributes.onTime.value)
    {
      dlOnOffClusterServerAttributes.offWaitTime.value = 0;
      stopDeviceUpdate();
    }
  }

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
  appSnprintf("OffWithEffect %d %d\r\n", payload->effectIdentifier, payload->effectVariant);
  
  if (dlOnOffClusterServerAttributes.globalSceneControl.value)
  {
    storeGlobalScene();
    dlOnOffClusterServerAttributes.globalSceneControl.value = false;
  }
  
  onOffSetOnOffState(false);
  dlOnOffClusterServerAttributes.onOff.value = false;
  dlOnOffClusterServerAttributes.onTime.value = 0x0000;
  
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
  appSnprintf("OnWithRecallGlobalScene\r\n");
  
  onOffSetOnOffState(true);
  if (!dlOnOffClusterServerAttributes.onTime.value)
  {
    dlOnOffClusterServerAttributes.offWaitTime.value = 0;
    stopDeviceUpdate();
  }
    
  if (!dlOnOffClusterServerAttributes.globalSceneControl.value)
  {    
    recallGlobalScene();
    dlOnOffClusterServerAttributes.globalSceneControl.value = true;
  }
  
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
  appSnprintf("OnWithTimedOff %d %d %d\r\n", payload->onOffControl, payload->onTime, payload->offWaitTime);
  
  if (payload->onOffControl & ZCL_ON_OFF_CLUSTER_ACCEPT_ONLY_WHEN_ON)
  {
    if (false == dlOnOffClusterServerAttributes.onOff.value)
      return ZCL_SUCCESS_STATUS;
  }

  if (dlOnOffClusterServerAttributes.offWaitTime.value > 0 &&
      false == dlOnOffClusterServerAttributes.onOff.value)
  {
    dlOnOffClusterServerAttributes.offWaitTime.value = MIN(payload->offWaitTime,
        dlOnOffClusterServerAttributes.offWaitTime.value);
  }
  else
  {
    dlOnOffClusterServerAttributes.onTime.value = MAX(payload->onTime,
        dlOnOffClusterServerAttributes.onTime.value);

    dlOnOffClusterServerAttributes.offWaitTime.value = payload->offWaitTime;

    setOnOff(true);
  }

  if (dlOnOffClusterServerAttributes.onTime.value < 0xffff &&
      dlOnOffClusterServerAttributes.offWaitTime.value < 0xffff)
  {
    startDeviceUpdate();
  }

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Recall the global scene
******************************************************************************/
static void recallGlobalScene(void)
{
  ZCL_RecallScene_t globalScene;
  globalScene.groupId = 0x0000u;
  globalScene.sceneId = 0x00u;
  
  recallScene(&globalScene);
}

/**************************************************************************//**
\brief Store to global scene
******************************************************************************/
static void storeGlobalScene(void)
{
  ZCL_StoreScene_t globalScene;
  
  globalScene.groupId = 0x0000u;
  globalScene.sceneId = 0x00u;

  storeScene(&globalScene);  
}
#endif // APP_DEVICE_TYPE_DIMMABLE_LIGHT

// eof dlOnOffCluster.c

