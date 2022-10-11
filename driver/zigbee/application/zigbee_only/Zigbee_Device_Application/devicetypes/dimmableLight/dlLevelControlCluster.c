/*******************************************************************************
  Dimmable Light Level Control cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    dlLevelControlCluster.c

  Summary:
    This file contains the Dimmable Light Level Control cluster interface.

  Description:
    This file contains the Dimmable Light Level Control cluster interface.
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
#include <dlLevelControlCluster.h>
#include <dlOnOffCluster.h>
#include <dlScenesCluster.h>
#include <appTimer.h>
#include <console.h>
#include <pdsDataServer.h>
#include <bspLeds.h>
#include <leds.h>
#if defined(BOARD_MEGARF) || defined(BOARD_SAMR21)
#include <ledsExt.h>
#include <lcdExt.h>
#endif
/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define MAX_LIGHT_LEVEL 254
#define MIN_LIGHT_LEVEL 1

#define LEVEL_TRANSITION_TIMER_INTERVAL 100 // 1/10ths of a second

/******************************************************************************
                    Types section
******************************************************************************/
typedef struct
{
  uint16_t transitionTime;
  uint8_t  level;
  int16_t  levelDelta;
  uint16_t remainingTime;
  bool     offAtMin; // whether to update onOff attribute when currentLevel hits minimum
} DlLevelControlMem_t;

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t moveToLevelInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_MoveToLevel_t *payload);
static ZCL_Status_t moveInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Move_t *payload);
static ZCL_Status_t stepInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Step_t *payload);
static ZCL_Status_t stopInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t moveToLevelWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_MoveToLevelWithOnOff_t *payload);
static ZCL_Status_t moveWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_MoveWithOnOff_t *payload);
static ZCL_Status_t stepWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StepWithOnOff_t *payload);
static ZCL_Status_t stopWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);

static void moveToLevel(uint8_t level, uint16_t time, bool onOff);
static void moveLevel(uint8_t mode, uint8_t rate, bool onOff);
static void stepLevel(uint8_t mode, uint8_t size, uint16_t time, bool onOff);

static void levelTransitionTimerFired(void);

static void setLevel(uint8_t level);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_LevelControlClusterServerAttributes_t dlLevelControlClusterServerAttributes =
{
  ZCL_DEFINE_LEVEL_CONTROL_CLUSTER_SERVER_MANDATORY_ATTRIBUTES(LEVEL_CONTROL_VAL_MIN_REPORT_PERIOD, LEVEL_CONTROL_VAL_MAX_REPORT_PERIOD)
};

ZCL_LevelControlClusterCommands_t         dlLevelControlCommands =
{
  ZCL_DEFINE_LEVEL_CONTROL_CLUSTER_COMMANDS(moveToLevelInd, moveInd, stepInd, stopInd,
                                            moveToLevelWOnOffInd, moveWOnOffInd, stepWOnOffInd, stopWOnOffInd)
};

/******************************************************************************
                    Static variables section
******************************************************************************/
static HAL_AppTimer_t      levelTransitionTimer;
static DlLevelControlMem_t levelControlMem;

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Level Control cluster
******************************************************************************/
void levelControlClusterInit(void)
{
  dlLevelControlClusterServerAttributes.clusterVersion.value = CLUSTER_VERSION;

  dlLevelControlClusterServerAttributes.remainingTime.value = 0;
  dlLevelControlClusterServerAttributes.currentLevel.value = 0;

  dlLevelControlClusterServerAttributes.currentLevel.minReportInterval = LEVEL_CONTROL_VAL_MIN_REPORT_PERIOD;
  dlLevelControlClusterServerAttributes.currentLevel.maxReportInterval = LEVEL_CONTROL_VAL_MAX_REPORT_PERIOD;

  levelTransitionTimer.mode     = TIMER_REPEAT_MODE;
  levelTransitionTimer.interval = LEVEL_TRANSITION_TIMER_INTERVAL;
  levelTransitionTimer.callback = levelTransitionTimerFired;

  levelControlMem.offAtMin      = false;
}

/**************************************************************************//**
\brief Stops Level Control cluster
******************************************************************************/
void levelControlClusterStop(void)
{
  HAL_StopAppTimer(&levelTransitionTimer);
}

/**************************************************************************//**
\brief Gets current color level

\returns current coloe level
******************************************************************************/
uint8_t levelControlCurrentLevel(void)
{
  return dlLevelControlClusterServerAttributes.currentLevel.value;
}

/**************************************************************************//**
\brief Sets color level

\param[in] level - color level
******************************************************************************/
void levelControlSetLevel(uint8_t level)
{
  HAL_StopAppTimer(&levelTransitionTimer);

  dlLevelControlClusterServerAttributes.currentLevel.value = level;
  if (MIN_LIGHT_LEVEL > dlLevelControlClusterServerAttributes.currentLevel.value)
  {
    dlLevelControlClusterServerAttributes.currentLevel.value = MIN_LIGHT_LEVEL;
  }

  ZCL_ReportOnChangeIfNeeded(&dlLevelControlClusterServerAttributes.currentLevel);
  PDS_Store(APP_DL_LEVEL_CONTROL_MEM_ID);
}

/**************************************************************************//**
\brief Callback on receiving Move To Level command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t moveToLevelInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_MoveToLevel_t *payload)
{
  appSnprintf("->MoveToLevel: lvl=0x%x trTime=%u\r\n", payload->level, payload->transitionTime);

//  if (!dlOnOffClusterServerAttributes.onOff.value)
//    return ZCL_SUCCESS_STATUS;

  if ((ZCL_LEVEL_CONTROL_CLUSTER_ASAP_TRANSITION_TIME == payload->transitionTime) ||
      (ZCL_LEVEL_CONTROL_CLUSTER_MOVE_IMMEDIATE_TRANSITION_TIME == payload->transitionTime))
  {
    setLevel(payload->level);
  }
  else
  {
    moveToLevel(payload->level, payload->transitionTime, false);
  }

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Move command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t moveInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Move_t *payload)
{
//  ZCL_Status_t status;
//  uint8_t type;
//  uint8_t onOffState;
  appSnprintf("->Move: mode=0x%x rate=0x%x\r\n", payload->moveMode, payload->rate);
//  status = ZCL_ReadAttributeValue(APP_SRC_ENDPOINT_ID, ONOFF_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER,
//                                  ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID, &type, &onOffState);
//
//  if (!onOffState && !status)
//    return ZCL_SUCCESS_STATUS;

  moveLevel(payload->moveMode, payload->rate, false);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Step command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t stepInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Step_t *payload)
{
//  ZCL_Status_t status;
//  uint8_t type;
//  uint8_t onOffState;
  appSnprintf("->Step: mode=0x%x stepSize=0x%x trTime=%u\r\n", payload->stepMode, payload->stepSize, payload->transitionTime);
//  status = ZCL_ReadAttributeValue(APP_SRC_ENDPOINT_ID, ONOFF_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER,
//                                  ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID, &type, &onOffState);
//
//  if (!onOffState && !status)
//    return ZCL_SUCCESS_STATUS;

  stepLevel(payload->stepMode, payload->stepSize, payload->transitionTime, false);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Stop command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t stopInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  appSnprintf("->Stop\r\n");

  HAL_StopAppTimer(&levelTransitionTimer);

  levelControlMem.offAtMin = false;

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Move To Level With On/Off command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t moveToLevelWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_MoveToLevelWithOnOff_t *payload)
{
  appSnprintf("->MoveToLevelWithOnOff: lvl=0x%x trTime=%u\r\n", payload->level, payload->transitionTime);

  switch (payload->transitionTime)
  {
    case ZCL_LEVEL_CONTROL_CLUSTER_ASAP_TRANSITION_TIME:
    case ZCL_LEVEL_CONTROL_CLUSTER_MOVE_IMMEDIATE_TRANSITION_TIME:
      if (payload->level > dlLevelControlClusterServerAttributes.currentLevel.value)
      {/** Before commencing any command that has the effect of increasing CurrentLevel, the OnOff attribute of the
        * On/Off cluster on the same endpoint, if implemented, shall be set to On.
        */
        onOffSetOnOffState(true);
        dlOnOffClusterServerAttributes.onTime.value = 0;
        dlOnOffClusterServerAttributes.offWaitTime.value = 0x0000u;
        stopDeviceUpdate();
      }
      else if (MIN_LIGHT_LEVEL >= payload->level)
      {/** If the command reduces the level to MININUM LEVEL,
        */
        onOffSetOnOffState(false);
        dlOnOffClusterServerAttributes.onTime.value = 0x0000u;
      }
      setLevel(payload->level);
      break;

    default:
      moveToLevel(payload->level, payload->transitionTime, true);
      break;
  }

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Move With On/Off command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t moveWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_MoveWithOnOff_t *payload)
{
  appSnprintf("->Move with on/off: mode=0x%x rate=0x%x\r\n", payload->moveMode, payload->rate);
  moveLevel(payload->moveMode, payload->rate, true);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Step With On/Off command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t stepWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StepWithOnOff_t *payload)
{
  appSnprintf("->Step with on/off: mode=0x%x stepSize=0x%x trTime=%u\r\n", payload->stepMode, payload->stepSize, payload->transitionTime);
  stepLevel(payload->stepMode, payload->stepSize, payload->transitionTime, true);

  (void)addressing, (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receiving Stop With On/Off command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
static ZCL_Status_t stopWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  appSnprintf("->Stop with on/off\r\n");

  HAL_StopAppTimer(&levelTransitionTimer);

  (void)addressing, (void)payloadLength, (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Moves to color level

\param[in] level - new color level;
\param[in] time  - transition time;
\param[in] onOff - true if level should be moved with on/off effect
******************************************************************************/
static void moveToLevel(uint8_t level, uint16_t time, bool onOff)
{
  // stop any other level changing
  HAL_StopAppTimer(&levelTransitionTimer);

  if (level > MAX_LIGHT_LEVEL)
  {// Bring the input level without allowed range
    level = MAX_LIGHT_LEVEL;
  }

  if (level < MIN_LIGHT_LEVEL)
  {// Bring the input level without allowed range
    level = MIN_LIGHT_LEVEL;
  }

  // update on/off cluster (on the same ep) attribute value if command is with on/off effect
  if (onOff)
  {
    if ((MIN_LIGHT_LEVEL >= level) || (level < dlLevelControlClusterServerAttributes.currentLevel.value))
    {
      levelControlMem.offAtMin = true;
    }
    else if (level > dlLevelControlClusterServerAttributes.currentLevel.value)
    {/** Before commencing any command that has the effect of increasing CurrentLevel, the OnOff attribute of the
      * On/Off cluster on the same endpoint, if implemented, shall be set to On.
      */
      onOffSetOnOffState(true);
      dlOnOffClusterServerAttributes.onTime.value = 0;
      dlOnOffClusterServerAttributes.offWaitTime.value = 0x0000u;
      stopDeviceUpdate();
    }
  }
  else
  {
    levelControlMem.offAtMin = false;
  }

  // store current level transition parameters
  levelControlMem.transitionTime = time;
  levelControlMem.level          = level;

  if (level <= dlLevelControlClusterServerAttributes.currentLevel.value)
  {
    levelControlMem.levelDelta     = dlLevelControlClusterServerAttributes.currentLevel.value - level;
  }
  else
  {
    levelControlMem.levelDelta     = level - dlLevelControlClusterServerAttributes.currentLevel.value;
  }

  // levelControlMem.remainingTime  = time;
  dlLevelControlClusterServerAttributes.remainingTime.value = time;

  HAL_StartAppTimer(&levelTransitionTimer);
}

/**************************************************************************//**
\brief Moves color level

\param[in] mode  - move mode (up or down);
\param[in] rate  - move rate;
\param[in] onOff - true if level should be moved with on/off effect
******************************************************************************/
static void moveLevel(uint8_t mode, uint8_t rate, bool onOff)
{
  // stop any other level changing
  HAL_StopAppTimer(&levelTransitionTimer);

  if (ZCL_MOVE_MODE_UP == mode)
  {
    levelControlMem.level          = MAX_LIGHT_LEVEL;
    levelControlMem.levelDelta     = levelControlMem.level - dlLevelControlClusterServerAttributes.currentLevel.value;

    levelControlMem.transitionTime = (levelControlMem.levelDelta * 10) / rate;

  }
  else
  {
    levelControlMem.level          = MIN_LIGHT_LEVEL;
    levelControlMem.levelDelta     = dlLevelControlClusterServerAttributes.currentLevel.value - levelControlMem.level;

    levelControlMem.transitionTime = (levelControlMem.levelDelta * 10) / rate;
  }

  // levelControlMem.remainingTime = levelControlMem.transitionTime;
  dlLevelControlClusterServerAttributes.remainingTime.value = levelControlMem.transitionTime;

  levelControlMem.offAtMin = onOff;

  if (onOff && (ZCL_MOVE_MODE_UP == mode))
  {/** Before commencing any command that has the effect of increasing CurrentLevel, the OnOff attribute of the
    * On/Off cluster on the same endpoint, if implemented, shall be set to On.
    */
    onOffSetOnOffState(true);

    dlOnOffClusterServerAttributes.onTime.value = 0;
    dlOnOffClusterServerAttributes.offWaitTime.value = 0x0000u;

    stopDeviceUpdate();
  }

  HAL_StartAppTimer(&levelTransitionTimer);
}

/**************************************************************************//**
\brief Steps color level

\param[in] mode  - step mode (up or down);
\param[in] size  - step size;
\param[in] time  - transition time;
\param[in] onOff - true if level should be moved with on/off effect
******************************************************************************/
static void stepLevel(uint8_t mode, uint8_t size, uint16_t time, bool onOff)
{
  // stop any other level changing
  HAL_StopAppTimer(&levelTransitionTimer);

  levelControlMem.level = dlLevelControlClusterServerAttributes.currentLevel.value;

  if (ZCL_STEP_MODE_UP == mode)
  {
    levelControlMem.level += size;
    levelControlMem.level = MIN(levelControlMem.level, MAX_LIGHT_LEVEL);
    levelControlMem.levelDelta = levelControlMem.level - dlLevelControlClusterServerAttributes.currentLevel.value;
  }
  else if (ZCL_STEP_MODE_DOWN == mode)
  {
    levelControlMem.level -= size;
    levelControlMem.level = MAX(levelControlMem.level, MIN_LIGHT_LEVEL);
    levelControlMem.levelDelta = dlLevelControlClusterServerAttributes.currentLevel.value - levelControlMem.level;
  }
  else
  {
    return;
  }

  if (onOff && (ZCL_MOVE_MODE_UP == mode))
  {/** Before commencing any command that has the effect of increasing CurrentLevel, the OnOff attribute of the
    * On/Off cluster on the same endpoint, if implemented, shall be set to On.
    */
    onOffSetOnOffState(true);
    dlOnOffClusterServerAttributes.onTime.value = 0;
    dlOnOffClusterServerAttributes.offWaitTime.value = 0x0000u;
    stopDeviceUpdate();
  }

  if (ZCL_LEVEL_CONTROL_CLUSTER_ASAP_TRANSITION_TIME == time)
  {
    setLevel(levelControlMem.level);
    return;
  }

  levelControlMem.offAtMin = onOff;

  // levelControlMem.remainingTime = time;
  dlLevelControlClusterServerAttributes.remainingTime.value = time;
  HAL_StartAppTimer(&levelTransitionTimer);
}

/**************************************************************************//**
\brief Level transition timer has fired
******************************************************************************/
static void levelTransitionTimerFired(void)
{
  if (--dlLevelControlClusterServerAttributes.remainingTime.value)
  {
    uint32_t remainingTime = dlLevelControlClusterServerAttributes.remainingTime.value;

    int32_t level = (int32_t)levelControlMem.level - ((remainingTime * levelControlMem.levelDelta) / (int32_t)levelControlMem.transitionTime);

    if (0 > level)
    {
      level = -(level);
    }

    setLevel((uint8_t) level);
  }
  else
  {
    if (levelControlMem.offAtMin && (MIN_LIGHT_LEVEL >= levelControlMem.level))
    {
      // update on/off cluster (on the same ep) attribute value if command is with on/off effect
      onOffSetOnOffState(false);
      dlOnOffClusterServerAttributes.onTime.value = 0x0000u;
      levelControlMem.offAtMin = false;
    }

    if (MIN_LIGHT_LEVEL >= levelControlMem.level)
    {
      levelControlMem.level = MIN_LIGHT_LEVEL;
    }

    HAL_StopAppTimer(&levelTransitionTimer);
    setLevel(levelControlMem.level);

    appSnprintf(" + Level transition is finished. Current level is %u\r\n", levelControlMem.level);

    PDS_Store(APP_DL_LEVEL_CONTROL_MEM_ID);
  }
}

/**************************************************************************//**
\brief Sets the given level

\param[in] level - new color level
******************************************************************************/
static void setLevel(uint8_t level)
{
  dlLevelControlClusterServerAttributes.currentLevel.value = level;
  BSP_SetLedBrightnessLevel(dlLevelControlClusterServerAttributes.currentLevel.value);
  scenesInvalidate();

  ZCL_ReportOnChangeIfNeeded(&dlLevelControlClusterServerAttributes.currentLevel);
}

#endif // APP_DEVICE_TYPE_DIMMABLE_LIGHT
// eof dlLevelControlCluster.c
