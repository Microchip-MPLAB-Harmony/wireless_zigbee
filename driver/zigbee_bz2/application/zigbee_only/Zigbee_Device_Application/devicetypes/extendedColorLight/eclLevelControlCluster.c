/*******************************************************************************
  Extended Color Light Level Control cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    eclLevelControlCluster.c

  Summary:
    This file contains the Extended Color Light Level Control cluster interface.

  Description:
    This file contains the Extended Color Light Level Control cluster interface.
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
#include <eclLevelControlCluster.h>
#include <eclOnOffCluster.h>
#include <eclScenesCluster.h>

#include <appTimer.h>
#include <uartManager.h>
#include <pdsDataServer.h>

#include <z3Device.h>
#if defined(BOARD_MEGARF) || defined(BOARD_SAMR21)
#include <ledsExt.h>
#include <lcdExt.h>
#endif

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define MAX_LIGHT_LEVEL 254
#define MIN_LIGHT_LEVEL 1

#define LEVEL_TRANSITION_TIMER_INTERVAL 100

/******************************************************************************
                    Types section
******************************************************************************/
/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t moveToLevelInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t moveInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t stepInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t stopInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t moveToLevelWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t moveWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t stepWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
static ZCL_Status_t stopWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);

static void setLevel(bool wOnOff, uint8_t level);
static void moveToLevel(bool wOnOff, uint8_t newLevel, uint16_t transitionTime);
static void stopMoving(void);
static void updateTransitionState(void);
static void adjustOnOffState(uint8_t level);

/******************************************************************************
                    Local variables
******************************************************************************/
static HAL_AppTimer_t updateTimer;
static uint8_t gTargetLevel;
static uint16_t gTransitionTime;
static int16_t gDelta;
static bool gWithOnOff;

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_LevelControlClusterServerAttributes_t eclLevelControlClusterServerAttributes =
{
  ZCL_DEFINE_LEVEL_CONTROL_CLUSTER_SERVER_MANDATORY_ATTRIBUTES(LEVEL_CONTROL_VAL_MIN_REPORT_PERIOD, LEVEL_CONTROL_VAL_MAX_REPORT_PERIOD)
};

ZCL_LevelControlClusterCommands_t         eclLevelControlCommands =
{
  ZCL_DEFINE_LEVEL_CONTROL_CLUSTER_COMMANDS(moveToLevelInd, moveInd, stepInd, stopInd,
                                            moveToLevelWOnOffInd, moveWOnOffInd, stepWOnOffInd, stopWOnOffInd)
};

/******************************************************************************
                    Static variables section
******************************************************************************/
/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Level Control cluster
******************************************************************************/
void levelControlClusterInit(void)
{
  eclLevelControlClusterServerAttributes.clusterVersion.value = 1;
  eclLevelControlClusterServerAttributes.currentLevel.value = 0;
  eclLevelControlClusterServerAttributes.remainingTime.value = 0;
  eclLevelControlClusterServerAttributes.currentLevel.minReportInterval = LEVEL_CONTROL_VAL_MIN_REPORT_PERIOD;
  eclLevelControlClusterServerAttributes.currentLevel.maxReportInterval = LEVEL_CONTROL_VAL_MAX_REPORT_PERIOD;

  levelControlDisplayLevel();
}

/**************************************************************************//**
\brief Set Extension Field Set
******************************************************************************/
void levelControlClusterSetExtensionField(uint16_t currentLevel)
{
  stopMoving();
  setLevel(false, currentLevel);
}

/**************************************************************************//**
\brief Display current level value.
******************************************************************************/
void levelControlDisplayLevel(void)
{
  uint8_t level = eclLevelControlClusterServerAttributes.currentLevel.value;

//  LCD_PRINT(2, 0, "%3d", level);
//#if (APP_ENABLE_CERTIFICATION_EXTENSION == 0 && APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_DIMMABLE_LIGHT)
//  {
//    LOG_STRING(currentLevelValueStr, "Current level value: %3d\r\n");
//
//    appSnprintf(currentLevelValueStr, level);
//  }
//#endif //APP_ENABLE_CERTIFICATION_EXTENSION == 0

  if (!isDeviceOn())
    level = 0;

  LEDS_SET_BRIGHTNESS(level);
  (void)level;
}

/**************************************************************************//**
\brief Set Current Level attribute to a specified value
******************************************************************************/
static void setLevel(bool wOnOff, uint8_t level)
{
  if (wOnOff)
    adjustOnOffState(level);

  eclLevelControlClusterServerAttributes.currentLevel.value = level;
  scenesClusterInvalidate();
//#if APP_ZLL_DEVICE_TYPE >= APP_DEVICE_TYPE_DIMMABLE_LIGHT
  levelControlDisplayLevel();
//#endif
}

/**************************************************************************//**
\brief On/off value adjustment regarding to current level

\param[in] level - current level value
******************************************************************************/
static void adjustOnOffState(uint8_t level)
{
  bool turnOn = (level == MIN_LIGHT_LEVEL) ? false : true;

  onOffClusterSetExtensionField(turnOn);
  /*
#if APP_ZLL_DEVICE_TYPE == APP_DEVICE_TYPE_ON_OFF_LIGHT
  if(level > MIN_LIGHT_LEVEL)
  {
    LOG_STRING(onRcvdStr, "On\r\n");
    appSnprintf(onRcvdStr);
  }
  else
  {
    LOG_STRING(offRcvdStr, "Off\r\n");
    appSnprintf(offRcvdStr);
  }
#endif
  */
}

/**************************************************************************//**
\brief Stat moving to the specified level
******************************************************************************/
static void moveToLevel(bool wOnOff, uint8_t newLevel, uint16_t transitionTime)
{
  int16_t level = newLevel;
  stopMoving();

  gTransitionTime = transitionTime;
  gTargetLevel = newLevel;
  gDelta = level - eclLevelControlClusterServerAttributes.currentLevel.value;
  gWithOnOff = wOnOff;

  updateTimer.mode = TIMER_REPEAT_MODE;
  updateTimer.interval = UPDATE_TIMER_INTERVAL;
  updateTimer.callback = updateTransitionState;
  HAL_StopAppTimer(&updateTimer);
  HAL_StartAppTimer(&updateTimer);

  eclLevelControlClusterServerAttributes.remainingTime.value = transitionTime;
}

/**************************************************************************//**
\brief Update transition state
******************************************************************************/
static void updateTransitionState(void)
{
  if (!isDeviceOn() && !gWithOnOff)
  {
    eclLevelControlClusterServerAttributes.remainingTime.value = 0;
    HAL_StopAppTimer(&updateTimer);
    return;
  }

  eclLevelControlClusterServerAttributes.remainingTime.value--;

  if (eclLevelControlClusterServerAttributes.remainingTime.value > 0)
  {
    int32_t remainingTime = eclLevelControlClusterServerAttributes.remainingTime.value;
    int16_t newLevel = (int16_t)gTargetLevel - ((remainingTime * gDelta) / (int32_t)gTransitionTime);
    setLevel(gWithOnOff, (uint8_t)newLevel);
  }
  else
  {
    HAL_StopAppTimer(&updateTimer);
    setLevel(gWithOnOff, gTargetLevel);
    gWithOnOff = false;

    PDS_Store(HA_APP_MEMORY_MEM_ID);
  }
}

/**************************************************************************//**
\brief Stop moving
******************************************************************************/
static void stopMoving(void)
{
  HAL_StopAppTimer(&updateTimer);
  gWithOnOff = false;
  eclLevelControlClusterServerAttributes.remainingTime.value = 0;
  levelControlDisplayLevel();
}

/**************************************************************************//**
\brief Process Move To Level command
******************************************************************************/
static ZCL_Status_t processMoveToLevel(bool wOnOff, ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  ZCL_MoveToLevel_t *req = (ZCL_MoveToLevel_t *)payload;
  ZCL_Status_t status;
  uint8_t type;
  uint8_t onOffState;

  status = ZCL_ReadAttributeValue(APP_ENDPOINT_EXTENDED_COLOR_LIGHT, ONOFF_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER,
                                  ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID, &type, &onOffState);

  if (!wOnOff && !onOffState && !status)
    return ZCL_SUCCESS_STATUS;

  if (!wOnOff && !isDeviceOn())
    return ZCL_SUCCESS_STATUS;

  if (req->level > MAX_LIGHT_LEVEL)
    req->level = MAX_LIGHT_LEVEL;

  if (req->level < MIN_LIGHT_LEVEL)
    req->level = MIN_LIGHT_LEVEL;

  if (0xffff != req->transitionTime && 0 != req->transitionTime)
  {
    moveToLevel(wOnOff, req->level, req->transitionTime);
  }
  else
  {
    setLevel(wOnOff, req->level);
    PDS_Store(HA_APP_MEMORY_MEM_ID);
  }
  
  if (wOnOff)
  {  
    appSnprintf("->MoveToLevelWithOnOff: lvl=0x%x trTime=%u\r\n", req->level, req->transitionTime);
  }
  else
  {
    appSnprintf("->MoveToLevel: lvl=0x%x trTime=%u\r\n", req->level, req->transitionTime);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Process Move command
******************************************************************************/
static ZCL_Status_t processMove(bool wOnOff, ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  ZCL_Move_t *req = (ZCL_Move_t *)payload;
  uint16_t transitionTime = MIN_TRANSITION_TIME;
  uint8_t level = MIN_LIGHT_LEVEL;
  uint8_t currentLevel = 0;

  ZCL_Status_t status;
  uint8_t type;
  uint8_t onOffState;

  status = ZCL_ReadAttributeValue(APP_ENDPOINT_EXTENDED_COLOR_LIGHT, ONOFF_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER,
                                  ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID, &type, &onOffState);

  if (!wOnOff && !onOffState && !status)
    return ZCL_SUCCESS_STATUS;

  if (!wOnOff && !isDeviceOn())
    return ZCL_SUCCESS_STATUS;

  currentLevel = eclLevelControlClusterServerAttributes.currentLevel.value;

  if (ZLL_LEVEL_CONTROL_UP_DIRECTION == req->moveMode)
  {
    level = MAX_LIGHT_LEVEL;
    transitionTime = ((MAX_LIGHT_LEVEL - currentLevel) * 10 /* 1/10 sec */) / req->rate;
  }

  else if (ZLL_LEVEL_CONTROL_DOWN_DIRECTION == req->moveMode)
  {
    level = MIN_LIGHT_LEVEL;
    transitionTime = ((currentLevel - MIN_LIGHT_LEVEL) * 10 /* 1/10 sec */) / req->rate;
  }

  moveToLevel(wOnOff, level, transitionTime);

  if (wOnOff)
  {
    appSnprintf("->Move with on/off: mode=0x%x rate=0x%x\r\n", req->moveMode, req->rate);
  }
  else
  {
    appSnprintf("->Move: mode=0x%x rate=0x%x\r\n", req->moveMode, req->rate);
  }
  
  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Process Step command
******************************************************************************/
static ZCL_Status_t processStep(bool wOnOff, ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  ZCL_Step_t *req = (ZCL_Step_t *)payload;
  int16_t level;
  ZCL_Status_t status;
  uint8_t type;
  uint8_t onOffState;

  status = ZCL_ReadAttributeValue(APP_ENDPOINT_EXTENDED_COLOR_LIGHT, ONOFF_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER,
                                  ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID, &type, &onOffState);

  if (!wOnOff && !onOffState && !status)
    return ZCL_SUCCESS_STATUS;

  if (!wOnOff && !isDeviceOn())
    return ZCL_SUCCESS_STATUS;

  level = eclLevelControlClusterServerAttributes.currentLevel.value;

  if (ZLL_LEVEL_CONTROL_UP_DIRECTION == req->stepMode)
  {
    level += req->stepSize;

    if (level > MAX_LIGHT_LEVEL)
      level = MAX_LIGHT_LEVEL;
  }

  else if (ZLL_LEVEL_CONTROL_DOWN_DIRECTION == req->stepMode)
  {
    level -= req->stepSize;

    if (level < MIN_LIGHT_LEVEL)
      level = MIN_LIGHT_LEVEL;
  }

  if (0xffff != req->transitionTime && 0 != req->transitionTime)
  {
    moveToLevel(wOnOff, level, req->transitionTime);
  }

  if (!wOnOff && !isDeviceOn())
    return ZCL_SUCCESS_STATUS;

  stopMoving();
  setLevel(wOnOff, level);
  PDS_Store(HA_APP_MEMORY_MEM_ID);

  if (wOnOff)
  {
    appSnprintf("->Step with on/off: mode=0x%x stepSize=0x%x trTime=%u\r\n", req->stepMode, req->stepSize, req->transitionTime);
  }
  else
  {
    appSnprintf("->Step: mode=0x%x stepSize=0x%x trTime=%u\r\n", req->stepMode, req->stepSize, req->transitionTime);
  }
  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Process Stop command
******************************************************************************/
static ZCL_Status_t processStop(bool wOnOff, ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  ZCL_Status_t status;
  uint8_t type;
  uint8_t onOffState;

  status = ZCL_ReadAttributeValue(APP_ENDPOINT_EXTENDED_COLOR_LIGHT, ONOFF_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER,
                                  ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID, &type, &onOffState);

  if (!wOnOff && !onOffState && !status)
    return ZCL_SUCCESS_STATUS;

  stopMoving();
  PDS_Store(HA_APP_MEMORY_MEM_ID);

  if (wOnOff)
  {
    appSnprintf("->Stop with on/off\r\n");
  }
  else
  {
    appSnprintf("->Stop\r\n");
  }
  
  (void)wOnOff;
  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Move To Level command
******************************************************************************/
static ZCL_Status_t moveToLevelInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  return processMoveToLevel(false, addressing, payloadLength, payload);
}

/**************************************************************************//**
\brief Callback on receive of Move command
******************************************************************************/
static ZCL_Status_t moveInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  return processMove(false, addressing, payloadLength, payload);
}

/**************************************************************************//**
\brief Callback on receive of Step command
******************************************************************************/
static ZCL_Status_t stepInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  return processStep(false, addressing, payloadLength, payload);
}

/**************************************************************************//**
\brief Callback on receive of Stop command
******************************************************************************/
static ZCL_Status_t stopInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  return processStop(false, addressing, payloadLength, payload);
}

/**************************************************************************//**
\brief Callback on receive of Move To Level With On/Off command
******************************************************************************/
static ZCL_Status_t moveToLevelWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  onOffClusterSetGlobalSceneControl();
  return processMoveToLevel(true, addressing, payloadLength, payload);
}

/**************************************************************************//**
\brief Callback on receive of Move With On/Off command
******************************************************************************/
static ZCL_Status_t moveWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  return processMove(true, addressing, payloadLength, payload);
}

/**************************************************************************//**
\brief Callback on receive of Step With On/Off command
******************************************************************************/
static ZCL_Status_t stepWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  return processStep(true, addressing, payloadLength, payload);
}

/**************************************************************************//**
\brief Callback on receive of Stop With On/Off command
******************************************************************************/
static ZCL_Status_t stopWOnOffInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  return processStop(true, addressing, payloadLength, payload);
}


/**************************************************************************//**
\brief Stop level transitions
******************************************************************************/
//void levelControlClusterStop(void)
//{
//  stopMoving();
//}
#endif // APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
// eof dlLevelControlCluster.c
