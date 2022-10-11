/*******************************************************************************
  Light device Color Control cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    eclColorControlCluster.c

  Summary:
    This file contains the Light device Color Control cluster interface.

  Description:
    This file contains the Light device Color Control cluster interface.
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
                    Includes
******************************************************************************/
#include <uartManager.h>
#include <z3Device.h>

#include <eclColorControlCluster.h>
#include <eclScenesCluster.h>
#include <eclOnOffCluster.h>
#include <eclColorSchemesConversion.h>

#include <pdsDataserver.h>

#ifdef BOARD_MEGARF
  #include <buttonsExt.h>
#endif
#if defined(BOARD_MEGARF) || defined(BOARD_SAMR21)
  #include <ledsExt.h>
  #include <lcdExt.h>
#endif

/******************************************************************************
                    Definitions
******************************************************************************/
#define UPDATE_TIMER_INTERVAL    100 // 1/10th of a second as per specification

#define MIN_HUE_LEVEL            0
#define MAX_HUE_LEVEL            0xfeff
#define MIN_SATURATION_LEVEL     0
#define MAX_SATURATION_LEVEL     0xfe
#define MIN_COLOR_LEVEL          0
#define MAX_COLOR_LEVEL          0xfeff

#define DEFAULT_SATURATION_LEVEL (MAX_SATURATION_LEVEL / 2)
#define DEFAULT_TRANSITION_TIME  2

#define HUE_SATURATION_SUPPORTED    (1 << 0)
#define ENHANCED_HUE_SUPPORTED      (1 << 1)
#define COLOR_LOOP_SUPPORTED        (1 << 2)
#define X_Y_ATTRIBUTES_SUPPORTED    (1 << 3)
#define COLOR_TEMPERATURE_SUPPORTED (1 << 4)

#define COLOR_LOOP_UPDATE_ACTION    (1 << 0)
#define COLOR_LOOP_UPDATE_DIRECTION (1 << 1)
#define COLOR_LOOP_UPDATE_TIME      (1 << 2)
#define COLOR_LOOP_UPDATE_START_HUE (1 << 3)

#define ABS(x)  ((x > 0) ? (x) : -(x))

#define ABSOLUTE_MAXIMUM_COLOR_TEMP  0xffff

/******************************************************************************
                    Types
******************************************************************************/
typedef enum _TransitionType_t
{
  NONE        = 0x00,
  ALL         = 0xff,
  HUE         = 0x01,
  SATURATION  = 0x02,
  COLOR       = 0x04,
  COLOR_LOOP  = 0x08,
  TEMPERATURE = 0x10,
} TransitionType_t;

/******************************************************************************
                    Prototypes
******************************************************************************/
static ZCL_Status_t moveToHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToHueCommand_t *payload);
static ZCL_Status_t moveHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveHueCommand_t *payload);
static ZCL_Status_t stepHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepHueCommand_t *payload);
static ZCL_Status_t moveToSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToSaturationCommand_t *payload);
static ZCL_Status_t moveSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveSaturationCommand_t *payload);
static ZCL_Status_t stepSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepSaturationCommand_t *payload);
static ZCL_Status_t moveToHueAndSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToHueAndSaturationCommand_t *payload);
static ZCL_Status_t moveToColorInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToColorCommand_t *payload);
static ZCL_Status_t moveColorInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveColorCommand_t *payload);
static ZCL_Status_t stepColorInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepColorCommand_t *payload);
static ZCL_Status_t enhancedMoveToHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllEnhancedMoveToHueCommand_t *payload);
static ZCL_Status_t enhancedMoveHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllEnhancedMoveHueCommand_t *payload);
static ZCL_Status_t enhancedStepHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllEnhancedStepHueCommand_t *payload);
static ZCL_Status_t enhancedMoveToHueAndSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllEnhancedMoveToHueAndSaturationCommand_t *payload);
static ZCL_Status_t colorLoopSetInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllColorLoopSetCommand_t *payload);
static ZCL_Status_t stopMoveStepInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, void *payload);
static ZCL_Status_t moveToColorTemperatureInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToColorTemperatureCommand_t *payload);
static ZCL_Status_t moveColorTemperatureInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveColorTemperatureCommand_t *payload);
static ZCL_Status_t stepColorTemperatureInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepColorTemperatureCommand_t *payload);

static void setColorMode(uint8_t mode);
static void setHue(uint16_t hue);
static void setSaturation(uint8_t saturation);
static void setColor(uint16_t x, uint16_t y);
static void setColorTemperature(uint16_t temperature);
static void handleColorLoopTransition(void);

static void displayStatus(void);
static void updateTransitionState(void);

static void transitionStart(TransitionType_t type);
static void transitionStop(TransitionType_t type);

static void setColorLoop(uint8_t colorLoopActive, uint8_t colorLoopDirection, uint16_t colorLoopTime);
static void startColorLoop(ZCL_ZllColorLoopAction_t action);
static TransitionType_t prepareMoveToHue(uint16_t hue, uint8_t direction, uint16_t transitionTime,
                                         bool byStep);
static TransitionType_t prepareMoveToSaturation(uint8_t saturation, uint16_t transitionTime,
                                                bool byStep);
static bool prepareMoveToColorTemperature(uint16_t temperature, uint16_t transitionTime, bool byStep);
static void handleColorTemperatureTransition(void);
static bool prepareMoveColorTemperature(uint8_t moveMode, uint16_t rate, uint16_t tempMin, uint16_t tempMax);

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_ColorControlClusterServerAttributes_t eclColorControlClusterServerAttributes =
{
  DEFINE_COLOR_CONTROL_SERVER_CLUSTER_ATTRIBUTES()
};

ZCL_ColorControlClusterCommands_t eclColorControlClusterServerCommands =
{
  ZCL_COLOR_CONTROL_CLUSTER_COMMANDS_FOR_EXTENDED_COLOR_LIGHT(moveToHueInd, moveHueInd, stepHueInd,
      moveToSaturationInd, moveSaturationInd, stepSaturationInd, moveToHueAndSaturationInd, moveToColorInd,
      moveColorInd, stepColorInd, moveToColorTemperatureInd, enhancedMoveToHueInd,
      enhancedMoveHueInd, enhancedStepHueInd, enhancedMoveToHueAndSaturationInd, colorLoopSetInd,
      stopMoveStepInd, moveColorTemperatureInd, stepColorTemperatureInd)
};

/******************************************************************************
                    Local variables
******************************************************************************/
static HAL_AppTimer_t updateTimer;
static uint8_t bckpSaturation;
static uint16_t bckpEnhacnedHue;

static TransitionType_t inTransition = NONE;

static struct
{
  uint32_t delta;
  uint32_t current;
  uint16_t target;
  bool     direction;
  bool     byStep;
} hueTransition;

static struct
{
  uint32_t delta;
  uint32_t current;
  uint8_t  target;
  bool     direction;
  bool     byStep;
} saturationTransition;

static struct
{
  uint32_t deltaX;
  uint32_t deltaY;
  uint32_t currentX;
  uint32_t currentY;
  uint16_t targetX;
  uint16_t targetY;
  bool     directionX;
  bool     directionY;
} colorTransition;

static struct
{
  uint32_t delta;
  uint32_t current;
  uint16_t target;
  bool     direction;
  bool     byStep;
  uint16_t minTemp;
  uint16_t maxTemp;
} colorTemperatureTransition;

/******************************************************************************
                    Implementations section
******************************************************************************/

/**************************************************************************//**
\brief Initialize Color Control cluster.
******************************************************************************/
void colorControlClusterInit(void)
{
  if (!PDS_IsAbleToRestore(APP_LIGHT_COLOR_CONTROL_CLUSTER_SERVER_ATTR_MEM_ID))
  {
    uint8_t colorCapabilities = 1;
    eclColorControlClusterServerAttributes.currentHue.value                 = ZCL_ZLL_CLUSTER_CURRENT_HUE_DEFAULT_VALUE;
    eclColorControlClusterServerAttributes.currentSaturation.value          = DEFAULT_SATURATION_LEVEL;
    eclColorControlClusterServerAttributes.remainingTime.value              = ZCL_ZLL_CLUSTER_REMAINING_TIME_DEFAULT_VALUE;
    eclColorControlClusterServerAttributes.currentX.value                   = ZCL_ZLL_CLUSTER_CURRENT_X_DEFAULT_VALUE;
    eclColorControlClusterServerAttributes.currentY.value                   = ZCL_ZLL_CLUSTER_CURRENT_Y_DEFAULT_VALUE;
    eclColorControlClusterServerAttributes.colorTemperature.value           = ZCL_ZCL_CLUSTER_COLOR_TEMP_DEFAULT_VALUE;
    eclColorControlClusterServerAttributes.colorMode.value                  = ZCL_ZLL_CLUSTER_COLOR_MODE_DEFAULT_VALUE;
    eclColorControlClusterServerAttributes.numberOfPrimaries.value          = 1;

    eclColorControlClusterServerAttributes.primary1X.value                  = 41942; // red
    eclColorControlClusterServerAttributes.primary1Y.value                  = 20971; // red
    eclColorControlClusterServerAttributes.primary1XIntensity.value         = 0;

    eclColorControlClusterServerAttributes.primary2X.value                  = 0;
    eclColorControlClusterServerAttributes.primary2Y.value                  = 0;
    eclColorControlClusterServerAttributes.primary2XIntensity.value         = 0;

    eclColorControlClusterServerAttributes.primary3X.value                  = 0;
    eclColorControlClusterServerAttributes.primary3Y.value                  = 0;
    eclColorControlClusterServerAttributes.primary3XIntensity.value         = 0;

    eclColorControlClusterServerAttributes.primary4X.value                  = 0;
    eclColorControlClusterServerAttributes.primary4Y.value                  = 0;
    eclColorControlClusterServerAttributes.primary4XIntensity.value         = 0;

    eclColorControlClusterServerAttributes.primary5X.value                  = 0;
    eclColorControlClusterServerAttributes.primary5Y.value                  = 0;
    eclColorControlClusterServerAttributes.primary5XIntensity.value         = 0;

    eclColorControlClusterServerAttributes.primary6X.value                  = 0;
    eclColorControlClusterServerAttributes.primary6Y.value                  = 0;
    eclColorControlClusterServerAttributes.primary6XIntensity.value         = 0;

    eclColorControlClusterServerAttributes.enhancedCurrentHue.value         = ZCL_ZCL_CLUSTER_ENHANCED_CURRENT_HUE_DEFAULT_VALUE;
    eclColorControlClusterServerAttributes.enhancedColorMode.value          = ZCL_ZCL_CLUSTER_ENHANCED_COLOR_MODE_DEFAULT_VALUE;
    eclColorControlClusterServerAttributes.colorLoopActive.value            = ZCL_ZCL_CLUSTER_COLOR_LOOP_ACTIVE_DEFAULT_VALUE;
    eclColorControlClusterServerAttributes.colorLoopDirection.value         = ZCL_ZCL_CLUSTER_COLOR_LOOP_DIRECTION_DEFAULT_VALUE;
    eclColorControlClusterServerAttributes.colorLoopTime.value              = ZCL_ZCL_CLUSTER_COLOR_LOOP_TIME_DEFAULT_VALUE;
    eclColorControlClusterServerAttributes.colorLoopStartEnhancedHue.value  = ZCL_ZCL_CLUSTER_COLOR_LOOP_START_ENHANCED_HUE_DEFAULT_VALUE;
    eclColorControlClusterServerAttributes.colorLoopStoredEnhancedHue.value = ZCL_ZCL_CLUSTER_COLOR_LOOP_STORED_ENHANCED_HUE_DEFAULT_VALUE;

    eclColorControlClusterServerAttributes.colorCapabilities.value.hueSaturationSupported = colorCapabilities;
    eclColorControlClusterServerAttributes.colorCapabilities.value.enhancedHueSupported   = colorCapabilities;
    eclColorControlClusterServerAttributes.colorCapabilities.value.colorLoopSupported     = colorCapabilities;
    eclColorControlClusterServerAttributes.colorCapabilities.value.XYAttributesSupported  = colorCapabilities;
    eclColorControlClusterServerAttributes.colorCapabilities.value.colorTemperatureSupported = 1;

    eclColorControlClusterServerAttributes.colorTempPhysicalMin.value = ZCL_ZCL_CLUSTER_TEMP_PHYSICAL_MIN_DEFAULT_VALUE;
    eclColorControlClusterServerAttributes.colorTempPhysicalMax.value = ZCL_ZCL_CLUSTER_TEMP_PHYSICAL_MAX_DEFAULT_VALUE;
  }

  updateTimer.mode = TIMER_REPEAT_MODE;
  updateTimer.interval = UPDATE_TIMER_INTERVAL;
  updateTimer.callback = updateTransitionState;

  displayStatus();
}

/**************************************************************************//**
\brief Set Extension Field Set
******************************************************************************/
void colorControlClusterSetExtensionField(Scene_t *scene)
{
  setColorMode(scene->colorMode);
  setHue(scene->enhancedCurrentHue);
  setSaturation(scene->currentSaturation);
  setColorLoop(scene->colorLoopActive, scene->colorLoopDirection, scene->colorLoopTime);
  setColor(scene->currentX, scene->currentY);
  setColorTemperature(lightConvertXYToColor(scene->currentX, scene->currentY));
}

INLINE uint8_t levelControlCalculateIntensity(void)
{
  // Wrong in general..
  return eclColorControlClusterServerAttributes.currentSaturation.value == UINT8_MAX ?
         UINT8_MAX - 1 : eclColorControlClusterServerAttributes.currentSaturation.value;
  // Should be something like..
  //return (uint8_t) pow(10.0, ((currentLevel - 1) * 3 / 253 ) - 1);
}

/**************************************************************************//**
\brief Display current level status.
******************************************************************************/
static void displayStatus(void)
{
    // add information about color temperature
  LCD_PRINT(0, 1, "%5u %5u %5u %3u",
            eclColorControlClusterServerAttributes.currentX.value,
            eclColorControlClusterServerAttributes.currentY.value,
            eclColorControlClusterServerAttributes.enhancedCurrentHue.value,
            eclColorControlClusterServerAttributes.currentSaturation.value
           );

  if (ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION == eclColorControlClusterServerAttributes.colorMode.value)
    LEDS_SET_COLOR_HS(
      eclColorControlClusterServerAttributes.enhancedCurrentHue.value,
      eclColorControlClusterServerAttributes.currentSaturation.value
    );
  else
    LEDS_SET_COLOR_XY(
      eclColorControlClusterServerAttributes.currentX.value,
      eclColorControlClusterServerAttributes.currentY.value
    );
}

/**************************************************************************//**
\brief Set current mode
******************************************************************************/
static void setColorMode(uint8_t mode)
{
  eclColorControlClusterServerAttributes.enhancedColorMode.value  = mode;

  if (ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION == mode)
    eclColorControlClusterServerAttributes.colorMode.value = ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION;
  else
    eclColorControlClusterServerAttributes.colorMode.value = mode;
}

/**************************************************************************//**
\brief Set hue value
******************************************************************************/
static void setHue(uint16_t hue)
{
  if (eclColorControlClusterServerAttributes.enhancedCurrentHue.value != hue)
  {
    eclColorControlClusterServerAttributes.enhancedCurrentHue.value = hue;
    eclColorControlClusterServerAttributes.currentHue.value = hue >> 8;
    scenesClusterInvalidate();
    displayStatus();
  }
}

/**************************************************************************//**
\brief Set saturation value
******************************************************************************/
static void setSaturation(uint8_t saturation)
{
  if (eclColorControlClusterServerAttributes.currentSaturation.value != saturation)
  {
    eclColorControlClusterServerAttributes.currentSaturation.value = saturation;
    scenesClusterInvalidate();
    displayStatus();
  }
}

/**************************************************************************//**
\brief Set color value
******************************************************************************/
static void setColor(uint16_t x, uint16_t y)
{
  if (eclColorControlClusterServerAttributes.currentX.value != x ||
      eclColorControlClusterServerAttributes.currentY.value != y)
  {
    eclColorControlClusterServerAttributes.currentX.value = x;
    eclColorControlClusterServerAttributes.currentY.value = y;
    eclColorControlClusterServerAttributes.primary1X.value = x;
    eclColorControlClusterServerAttributes.primary1Y.value = y;
    eclColorControlClusterServerAttributes.primary1XIntensity.value =
      levelControlCalculateIntensity();

    scenesClusterInvalidate();
    displayStatus();
  }
}

/**************************************************************************//**
\brief Set color temperature value
******************************************************************************/
static void setColorTemperature(uint16_t temperature)
{
  if (eclColorControlClusterServerAttributes.colorTemperature.value != temperature)
  {
    eclColorControlClusterServerAttributes.colorTemperature.value = temperature;
    scenesClusterInvalidate();
    displayStatus();
  }
}

/**************************************************************************//**
\brief Set Color Loop values
******************************************************************************/
static void setColorLoop(uint8_t colorLoopActive, uint8_t colorLoopDirection, uint16_t colorLoopTime)
{
  eclColorControlClusterServerAttributes.colorLoopActive.value    = colorLoopActive;
  eclColorControlClusterServerAttributes.colorLoopDirection.value = colorLoopDirection;
  eclColorControlClusterServerAttributes.colorLoopTime.value      = colorLoopTime;

  if (colorLoopActive)
    startColorLoop(COLOR_LOOP_ACTIVATE_FROM_ECH);
}

/**************************************************************************//**
\brief Stop Color Loop handler.
******************************************************************************/
static void stopColorLoop(void)
{
  transitionStop(ALL);
  eclColorControlClusterServerAttributes.colorLoopActive.value = 0;
  setHue(eclColorControlClusterServerAttributes.colorLoopStoredEnhancedHue.value);
}

/**************************************************************************//**
\brief Starts the color loop specified way.

\param[in] action - color loop mode.
******************************************************************************/
static void startColorLoop(ZCL_ZllColorLoopAction_t action)
{
  eclColorControlClusterServerAttributes.colorLoopStoredEnhancedHue.value =
    eclColorControlClusterServerAttributes.enhancedCurrentHue.value;

  if (COLOR_LOOP_ACTIVATE_FROM_ECH == action)
    eclColorControlClusterServerAttributes.colorLoopStartEnhancedHue.value =
      eclColorControlClusterServerAttributes.enhancedCurrentHue.value;

  eclColorControlClusterServerAttributes.colorLoopActive.value = 1;

  eclColorControlClusterServerAttributes.remainingTime.value = 0xffff;
  setColorMode(ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION);
  transitionStart(COLOR_LOOP);
}

/**************************************************************************//**
\brief Handle hue transition
******************************************************************************/
static void handleHueTransition(void)
{
  // Up transition
  if (hueTransition.direction)
    hueTransition.current += hueTransition.delta;
  // Down transition
  else
    hueTransition.current -= hueTransition.delta;
    setHue(hueTransition.current >> 16);
}

/**************************************************************************//**
\brief Handle saturation transition
******************************************************************************/
static void handleSaturationTransition(void)
{
  uint8_t saturation;
  bool finish = false;

  // Up transition
  if (saturationTransition.direction)
  {
    if (((uint32_t){MAX_SATURATION_LEVEL} << 16) - saturationTransition.delta < saturationTransition.current)
    {
      saturation = MAX_SATURATION_LEVEL;
      finish = true;
    }
    else
    {
      saturationTransition.current += saturationTransition.delta;
      saturation = saturationTransition.current >> 16;
    }
  }
  // Down transition
  else
  {
    if (saturationTransition.current - ((uint32_t){MIN_SATURATION_LEVEL} << 16) < saturationTransition.delta)
    {
      saturation = MIN_SATURATION_LEVEL;
      finish = true;
    }
    else
    {
      saturationTransition.current -= saturationTransition.delta;
      saturation = saturationTransition.current >> 16;
    }
  }

  setSaturation(saturation);

  if (finish)
    transitionStop(SATURATION);
}

/**************************************************************************//**
\brief Handle color transition
******************************************************************************/
static void handleColorTransition(void)
{
  uint16_t x, y;
  bool finishX = false;
  bool finishY = false;

  // X Up transition
  if (colorTransition.directionX)
  {
    if (((uint32_t){MAX_COLOR_LEVEL} << 16) - colorTransition.deltaX < colorTransition.currentX)
    {
      x = MAX_COLOR_LEVEL;
      finishX = true;
    }
    else
    {
      colorTransition.currentX += colorTransition.deltaX;
      x = colorTransition.currentX >> 16;
    }
  }
  // X Down transition
  else
  {
    if (colorTransition.currentX - ((uint32_t){MIN_COLOR_LEVEL} << 16) < colorTransition.deltaX)
    {
      x = MIN_COLOR_LEVEL;
      finishX = true;
    }
    else
    {
      colorTransition.currentX -= colorTransition.deltaX;
      x = colorTransition.currentX >> 16;
    }
  }

  // Y Up transition
  if (colorTransition.directionY)
  {
    if (((uint32_t){MAX_COLOR_LEVEL} << 16) - colorTransition.deltaY < colorTransition.currentY)
    {
      y = MAX_COLOR_LEVEL;
      finishY = true;
    }
    else
    {
      colorTransition.currentY += colorTransition.deltaY;
      y = colorTransition.currentY >> 16;
    }
  }
  // Y Down transition
  else
  {
    if (colorTransition.currentY - ((uint32_t){MIN_COLOR_LEVEL} << 16) < colorTransition.deltaY)
    {
      y = MIN_COLOR_LEVEL;
      finishY = true;
    }
    else
    {
      colorTransition.currentY -= colorTransition.deltaY;
      y = colorTransition.currentY >> 16;
    }
  }

  // Common
  setColor(x, y);

  if (finishX && finishY)
    transitionStop(COLOR);
}

/**************************************************************************//**
\brief Handle Color Loop transition
******************************************************************************/
static void handleColorLoopTransition(void)
{
  uint16_t delta = (MAX_HUE_LEVEL - MIN_HUE_LEVEL) /
                   (eclColorControlClusterServerAttributes.colorLoopTime.value * 10);
  int32_t enhancedHue = eclColorControlClusterServerAttributes.enhancedCurrentHue.value;

  // Up transition
  if (eclColorControlClusterServerAttributes.colorLoopDirection.value)
    enhancedHue += delta;
  // Down transition
  else
    enhancedHue -= delta;

  if (enhancedHue < MIN_HUE_LEVEL)
    enhancedHue = MAX_HUE_LEVEL;
  else if (MAX_HUE_LEVEL < enhancedHue)
    enhancedHue = MIN_HUE_LEVEL;

  setHue(enhancedHue);
}

/**************************************************************************//**
\brief Handle color temperature transition
******************************************************************************/
static void handleColorTemperatureTransition(void)
{
  uint16_t temp;
  bool finish = false;

  // Temperature Up transition
  if (colorTemperatureTransition.direction)
  {
    if (((uint32_t){colorTemperatureTransition.maxTemp} << 16) - colorTemperatureTransition.delta < colorTemperatureTransition.current)
    {
      temp = colorTemperatureTransition.maxTemp;
      finish = true;
    }
    else
    {
      colorTemperatureTransition.current += colorTemperatureTransition.delta;
      temp = colorTemperatureTransition.current >> 16;
    }
  }
  // Temperature Down transition
  else
  {
    if (colorTemperatureTransition.current - ((uint32_t){colorTemperatureTransition.minTemp} << 16) < colorTemperatureTransition.delta)
    {
      temp = colorTemperatureTransition.minTemp;
      finish = true;
    }
    else
    {
      colorTemperatureTransition.current -= colorTemperatureTransition.delta;
      temp = colorTemperatureTransition.current >> 16;
    }
  }

  // Common
  setColorTemperature(temp);

  if (finish)
    transitionStop(TEMPERATURE);
}

/**************************************************************************//**
\brief Show identify effect.

\param[in] enhancedHue - enhanced hue to move to.
******************************************************************************/
void colorControlShowIdentifyEffect(uint16_t enhancedHue)
{
  uint8_t proceedWith;

  bckpSaturation = eclColorControlClusterServerAttributes.currentSaturation.value;
  bckpEnhacnedHue = eclColorControlClusterServerAttributes.enhancedCurrentHue.value;

  proceedWith = prepareMoveToHue(enhancedHue,
    ZCL_ZLL_MOVE_TO_HUE_DIRECTION_SHORTEST_DISTANCE, DEFAULT_TRANSITION_TIME, false);
  proceedWith |= prepareMoveToSaturation(DEFAULT_SATURATION_LEVEL,
    DEFAULT_TRANSITION_TIME, false);

  if (proceedWith)
  {
    setColorMode(ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(proceedWith);
  }
}

/**************************************************************************//**
\brief Stop showing identify effect and return to previous state.
******************************************************************************/
void colorControlStopIdentifyEffect(void)
{
  uint8_t proceedWith;

  proceedWith = prepareMoveToHue(bckpEnhacnedHue,
    ZCL_ZLL_MOVE_TO_HUE_DIRECTION_SHORTEST_DISTANCE, DEFAULT_TRANSITION_TIME, false);
  proceedWith |= prepareMoveToSaturation(bckpSaturation, DEFAULT_TRANSITION_TIME, false);

  if (proceedWith)
  {
    setColorMode(ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(proceedWith);
  }
}

/**************************************************************************//**
\brief Set target transition value
******************************************************************************/
static void setTargetValue()
{
  if (inTransition & HUE)
    setHue(hueTransition.target);

  if (inTransition & SATURATION)
    setSaturation(saturationTransition.target);

  if (inTransition & COLOR)
  {
    setColor(colorTransition.targetX, colorTransition.targetY);
    setColorTemperature(lightConvertXYToColor(colorTransition.targetX, colorTransition.targetY));
  }

  if (inTransition & TEMPERATURE)
  {
    uint16_t x, y;

    lightConvertColorToXY(colorTemperatureTransition.target, &x, &y);
    setColor(x, y);
    setColorTemperature(colorTemperatureTransition.target);
  }
}

/**************************************************************************//**
\brief Update transition state
******************************************************************************/
static void updateTransitionState(void)
{
  if (!isDeviceOn())
  {
    eclColorControlClusterServerAttributes.remainingTime.value = 0;
    HAL_StopAppTimer(&updateTimer);
    return;
  }

  if (eclColorControlClusterServerAttributes.remainingTime.value < 0xffff)
    eclColorControlClusterServerAttributes.remainingTime.value--;

  if (eclColorControlClusterServerAttributes.remainingTime.value > 0)
  {
    if (inTransition & HUE)
      handleHueTransition();

    if (inTransition & SATURATION)
      handleSaturationTransition();

    else if (inTransition & COLOR)
      handleColorTransition();

    else if (inTransition & COLOR_LOOP)
      handleColorLoopTransition();

    else if (inTransition & TEMPERATURE)
      handleColorTemperatureTransition();
  }
  else
  {
    setTargetValue();
    transitionStop(ALL);
  }
}

/**************************************************************************//**
\brief Start the transition
******************************************************************************/
static void transitionStart(TransitionType_t type)
{
  inTransition |= type;

  if (eclColorControlClusterServerAttributes.remainingTime.value > 0)
  {
    HAL_StopAppTimer(&updateTimer);
    HAL_StartAppTimer(&updateTimer);
  }
  else
  {
    setTargetValue();
  }
}

/**************************************************************************//**
\brief Start current transition
******************************************************************************/
static void transitionStop(TransitionType_t type)
{
  inTransition &= ~type;

  if (NONE == inTransition)
  {
    HAL_StopAppTimer(&updateTimer);
    eclColorControlClusterServerAttributes.remainingTime.value = 0;
  }

  PDS_Store(HA_APP_MEMORY_MEM_ID);
}

/**************************************************************************//**
\brief Prepare Move To Hue parameters
******************************************************************************/
static TransitionType_t prepareMoveToHue(uint16_t hue, uint8_t direction, uint16_t transitionTime,
                                         bool byStep)
{
  uint16_t delta;
  bool dir = true;

  if (!isDeviceOn())
    return NONE;

  if (hue == eclColorControlClusterServerAttributes.enhancedCurrentHue.value)
    return NONE;

  hueTransition.target = hue;
  hueTransition.byStep = byStep;

  if (!byStep)
  {

    // Get shortest distance direction and delta
    if (hue > eclColorControlClusterServerAttributes.enhancedCurrentHue.value)
    {
      dir = true;
      delta = hue - eclColorControlClusterServerAttributes.enhancedCurrentHue.value;
    }
    else
    {
      dir = false;
      delta = eclColorControlClusterServerAttributes.enhancedCurrentHue.value - hue;
    }

    // Check if change in direction is needed
    if (ZCL_ZLL_MOVE_TO_HUE_DIRECTION_LONGEST_DISTANCE == direction ||
        (ZCL_ZLL_MOVE_TO_HUE_DIRECTION_UP == direction && false == dir) ||
        (ZCL_ZLL_MOVE_TO_HUE_DIRECTION_DOWN == direction && true == dir))
    {
      dir = !dir;
      delta = (MAX_HUE_LEVEL - MIN_HUE_LEVEL) - delta;
    }

    hueTransition.delta = ((uint32_t)delta << 16) / transitionTime;
    hueTransition.current = (uint32_t)eclColorControlClusterServerAttributes.enhancedCurrentHue.value << 16;
    hueTransition.direction = dir;
  }

  eclColorControlClusterServerAttributes.remainingTime.value = transitionTime;

  return HUE;
}

/**************************************************************************//**
\brief Prepare Move Hue parameters
******************************************************************************/
static bool prepareMoveHue(uint8_t mode, uint16_t rate)
{
  if (!isDeviceOn())
    return false;

  if (ZCL_ZLL_MOVE_HUE_MOVE_MODE_UP == mode)
    hueTransition.direction = true;
  else
    hueTransition.direction = false;

  hueTransition.current = (uint32_t)eclColorControlClusterServerAttributes.enhancedCurrentHue.value << 16;
  hueTransition.target = 0;
  hueTransition.delta = ((uint32_t)rate << 16) / 10;
  hueTransition.byStep = false;

  eclColorControlClusterServerAttributes.remainingTime.value = 0xffff;

  return true;
}

/**************************************************************************//**
\brief Prepare Move To Saturation parameters
******************************************************************************/
static TransitionType_t prepareMoveToSaturation(uint8_t saturation, uint16_t transitionTime,
                                                bool byStep)
{
  uint16_t delta;
  bool dir = true;

  if (!isDeviceOn())
    return NONE;

  if (saturation == eclColorControlClusterServerAttributes.currentSaturation.value)
    return NONE;

  saturationTransition.target = saturation;
  saturationTransition.byStep = byStep;

  if (!byStep)
  {

    // Get shortest distance direction and delta
    if (saturation > eclColorControlClusterServerAttributes.currentSaturation.value)
    {
      dir = true;
      delta = saturation - eclColorControlClusterServerAttributes.currentSaturation.value;
    }
    else
    {
      dir = false;
      delta = eclColorControlClusterServerAttributes.currentSaturation.value - saturation;
    }

    saturationTransition.delta = ((uint32_t)delta << 16) / (uint32_t)transitionTime;
    saturationTransition.current = (uint32_t)eclColorControlClusterServerAttributes.currentSaturation.value << 16;
    saturationTransition.direction = dir;
  }

  eclColorControlClusterServerAttributes.remainingTime.value = transitionTime;

  return SATURATION;
}

/**************************************************************************//**
\brief Prepare Move Saturation parameters
******************************************************************************/
static bool prepareMoveSaturation(uint8_t mode, uint16_t rate)
{
  if (!isDeviceOn())
    return false;

  if (ZCL_ZLL_MOVE_HUE_MOVE_MODE_UP == mode)
    saturationTransition.direction = true;
  else
    saturationTransition.direction = false;

  saturationTransition.current = (uint32_t)eclColorControlClusterServerAttributes.currentSaturation.value << 16;
  saturationTransition.target = 0;
  saturationTransition.delta = ((uint32_t)rate << 16) / 10;
  saturationTransition.byStep = false;

  eclColorControlClusterServerAttributes.remainingTime.value = 0xffff;

  return true;
}


/**************************************************************************//**
\brief Prepare Move To Color parameters
******************************************************************************/
static bool prepareMoveToColor(uint16_t x, uint16_t y, uint16_t transitionTime)
{
  uint16_t deltax, deltay;
  bool dirx, diry;

  if (!isDeviceOn())
    return false;

  if (x == eclColorControlClusterServerAttributes.currentX.value &&
      y == eclColorControlClusterServerAttributes.currentY.value)
    return false;

  // Get shortest distance direction and delta
  dirx = x > eclColorControlClusterServerAttributes.currentX.value;

  if (dirx)
    deltax = x - eclColorControlClusterServerAttributes.currentX.value;
  else
    deltax = eclColorControlClusterServerAttributes.currentX.value - x;

  diry = y > eclColorControlClusterServerAttributes.currentY.value;

  if (diry)
    deltay = y - eclColorControlClusterServerAttributes.currentY.value;
  else
    deltay = eclColorControlClusterServerAttributes.currentY.value - y;

  colorTransition.deltaX = ((uint32_t)deltax << 16) / transitionTime;
  colorTransition.deltaY = ((uint32_t)deltay << 16) / transitionTime;
  colorTransition.currentX = (uint32_t)eclColorControlClusterServerAttributes.currentX.value << 16;
  colorTransition.currentY = (uint32_t)eclColorControlClusterServerAttributes.currentY.value << 16;
  colorTransition.directionX = dirx;
  colorTransition.directionY = diry;
  colorTransition.targetX = x;
  colorTransition.targetY = y;

  eclColorControlClusterServerAttributes.remainingTime.value = transitionTime;

  return true;
}

/**************************************************************************//**
\brief Prepare Move Color parameters
******************************************************************************/
static bool prepareMoveColor(int16_t ratex, int16_t ratey)
{
  if (!isDeviceOn())
    return false;

  // X
  colorTransition.deltaX = ((uint32_t)ABS(ratex) << 16) / 10;
  colorTransition.currentX = (uint32_t)eclColorControlClusterServerAttributes.currentX.value << 16;
  colorTransition.directionX = ratex > 0;
  colorTransition.targetX = 0;

  // Y
  colorTransition.deltaY = ((uint32_t)ABS(ratey) << 16) / 10;
  colorTransition.currentY = (uint32_t)eclColorControlClusterServerAttributes.currentY.value << 16;
  colorTransition.directionY = ratey > 0;
  colorTransition.targetY = 0;

  eclColorControlClusterServerAttributes.remainingTime.value = 0xffff;

  return true;
}
/**************************************************************************//**
\brief Prepare Move To Color Temperature parameters
******************************************************************************/
static bool prepareMoveToColorTemperature(uint16_t temperature, uint16_t transitionTime, bool byStep)
{
  uint16_t deltaTemp;
  bool dirTemp;

  if (!isDeviceOn())
    return false;

  if (temperature == eclColorControlClusterServerAttributes.colorTemperature.value)
    return false;

  eclColorControlClusterServerAttributes.remainingTime.value = transitionTime;
  colorTemperatureTransition.target                       = temperature;
  colorTemperatureTransition.byStep                       = byStep;

  // Get shortest distance direction and delta
  dirTemp = temperature > eclColorControlClusterServerAttributes.colorTemperature.value;
  if (dirTemp)
    deltaTemp = temperature - eclColorControlClusterServerAttributes.colorTemperature.value;
  else
    deltaTemp = eclColorControlClusterServerAttributes.colorTemperature.value - temperature;

  colorTemperatureTransition.delta     = ((uint32_t)deltaTemp << 16) / transitionTime;
  colorTemperatureTransition.current   = (uint32_t)eclColorControlClusterServerAttributes.colorTemperature.value << 16;
  colorTemperatureTransition.direction = dirTemp;
  colorTemperatureTransition.minTemp   = eclColorControlClusterServerAttributes.colorTempPhysicalMin.value;
  colorTemperatureTransition.maxTemp   = eclColorControlClusterServerAttributes.colorTempPhysicalMax.value;

  return true;
}

/**************************************************************************//**
\brief Prepare Move Color Temperature parameters
******************************************************************************/
static bool prepareMoveColorTemperature(uint8_t moveMode, uint16_t rate, uint16_t tempMin, uint16_t tempMax)
{
  if (!isDeviceOn())
    return false;

  colorTemperatureTransition.delta     = ((uint32_t)ABS(rate) << 16) / 10;
  colorTemperatureTransition.current   = (uint32_t)eclColorControlClusterServerAttributes.colorTemperature.value << 16;
  colorTemperatureTransition.direction = ZCL_ZLL_MOVE_SATURATION_MOVE_MODE_UP == moveMode;
  colorTemperatureTransition.target    = 0;
  colorTemperatureTransition.byStep    = false;
  colorTemperatureTransition.minTemp   = MAX(tempMin, eclColorControlClusterServerAttributes.colorTempPhysicalMin.value);
  colorTemperatureTransition.maxTemp   = MIN(tempMax, eclColorControlClusterServerAttributes.colorTempPhysicalMax.value);

  eclColorControlClusterServerAttributes.remainingTime.value = 0xffff;

  return true;
}
/**************************************************************************//**
\brief Callback on receive of Move To Hue command
******************************************************************************/
static ZCL_Status_t moveToHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToHueCommand_t *payload)
{
  appSnprintf("moveToHueInd()\r\n");
  //dbgLcdMsg("moveToHue");

  if ((MAX_HUE_LEVEL >> 8) < payload->hue)
    return ZCL_INVALID_VALUE_STATUS;

  if (prepareMoveToHue((uint16_t)payload->hue << 8, payload->direction, payload->transitionTime, false))
  {
    setColorMode(ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(HUE);
  }

  (void)addressing;
  (void)payloadLength;

  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Move Hue command
******************************************************************************/
static ZCL_Status_t moveHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveHueCommand_t *payload)
{
  appSnprintf("moveHueInd()\r\n");
  //dbgLcdMsg("moveHue");

  if (ZCL_ZLL_MOVE_HUE_MOVE_MODE_UP == payload->moveMode ||
      ZCL_ZLL_MOVE_HUE_MOVE_MODE_DOWN == payload->moveMode)
  {
    if (!payload->rate)
      return ZCL_INVALID_FIELD_STATUS;

    if (prepareMoveHue(payload->moveMode, (uint16_t)payload->rate << 8))
    {
      setColorMode(ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION);
      transitionStart(HUE);
    }
  }
  else if (ZCL_ZLL_MOVE_HUE_MOVE_MODE_STOP == payload->moveMode)
  {
    transitionStop(ALL);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Step Hue command
******************************************************************************/
static ZCL_Status_t stepHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepHueCommand_t *payload)
{
  uint16_t hue;

  appSnprintf("stepHueInd()\r\n");
  //dbgLcdMsg("stepHue");

  hue = eclColorControlClusterServerAttributes.enhancedCurrentHue.value;

  if (ZCL_ZLL_STEP_HUE_STEP_MODE_UP == payload->stepMode)
    hue += (uint16_t)payload->stepSize << 8;
  else if (ZCL_ZLL_STEP_HUE_STEP_MODE_DOWN == payload->stepMode)
    hue -= (uint16_t)payload->stepSize << 8;
  else
    return ZCL_SUCCESS_STATUS;

  if (prepareMoveToHue(hue, ZCL_ZLL_MOVE_TO_HUE_DIRECTION_SHORTEST_DISTANCE, payload->transitionTime, true))
  {
    setColorMode(ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(HUE);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Move To Saturation command
******************************************************************************/
static ZCL_Status_t moveToSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToSaturationCommand_t *payload)
{
  appSnprintf("moveToSaturationInd()\r\n");
  //dbgLcdMsg("moveToSat");

  if (MAX_SATURATION_LEVEL < payload->saturation)
    return ZCL_INVALID_VALUE_STATUS;

  if (prepareMoveToSaturation(payload->saturation, payload->transitionTime, false))
  {
    setColorMode(ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(SATURATION);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Move Saturation command
******************************************************************************/
static ZCL_Status_t moveSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveSaturationCommand_t *payload)
{
  appSnprintf("moveSaturationInd()\r\n");
  //dbgLcdMsg("moveSat");

  if (!payload->rate)
    return ZCL_INVALID_FIELD_STATUS;

  if (ZCL_ZLL_MOVE_SATURATION_MOVE_MODE_UP == payload->moveMode ||
      ZCL_ZLL_MOVE_SATURATION_MOVE_MODE_DOWN == payload->moveMode)
  {
    if (prepareMoveSaturation(payload->moveMode, payload->rate))
    {
      setColorMode(ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION);
      transitionStart(SATURATION);
    }
  }
  else if (ZCL_ZLL_MOVE_SATURATION_MOVE_MODE_STOP == payload->moveMode)
  {
    transitionStop(ALL);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Step Saturation command
******************************************************************************/
static ZCL_Status_t stepSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepSaturationCommand_t *payload)
{
  int16_t saturation;
  appSnprintf("stepSaturationInd()\r\n");
  //dbgLcdMsg("stepSat");

  saturation = eclColorControlClusterServerAttributes.currentSaturation.value;

  if (ZCL_ZLL_STEP_SATURATION_STEP_MODE_UP == payload->stepMode)
    saturation += payload->stepSize;
  else if (ZCL_ZLL_STEP_HUE_STEP_MODE_DOWN == payload->stepMode)
    saturation -= payload->stepSize;
  else
    return ZCL_SUCCESS_STATUS;

  if (saturation < MIN_SATURATION_LEVEL || MAX_SATURATION_LEVEL < saturation)
    return ZCL_INVALID_VALUE_STATUS;

  if (prepareMoveToSaturation(saturation, payload->transitionTime, true))
  {
    setColorMode(ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(SATURATION);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Move To Hue And Saturation command
******************************************************************************/
static ZCL_Status_t moveToHueAndSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToHueAndSaturationCommand_t *payload)
{
  uint8_t proceedWith;
  appSnprintf("moveToHueAndSaturationInd()\r\n");
  //dbgLcdMsg("moveToHueAndSat");

  if ((MAX_HUE_LEVEL >> 8) < payload->hue ||
      MAX_SATURATION_LEVEL < payload->saturation)
    return ZCL_INVALID_VALUE_STATUS;

  proceedWith = prepareMoveToHue((uint16_t)payload->hue << 8, ZCL_ZLL_MOVE_TO_HUE_DIRECTION_SHORTEST_DISTANCE, payload->transitionTime, false);
  proceedWith |= prepareMoveToSaturation(payload->saturation, payload->transitionTime, false);

  if (proceedWith)
  {
    setColorMode(ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(proceedWith);
  }

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Move To Color command
******************************************************************************/
static ZCL_Status_t moveToColorInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToColorCommand_t *payload)
{
  appSnprintf("moveToColorInd()\r\n");
  //dbgLcdMsg("moveToColor");

  if (MAX_COLOR_LEVEL < payload->colorX || MAX_COLOR_LEVEL < payload->colorY)
    return ZCL_INVALID_VALUE_STATUS;

  if (prepareMoveToColor(payload->colorX, payload->colorY, payload->transitionTime))
  {
    setColorMode(ZCL_ZLL_CURRENT_X_AND_CURRENT_Y);
    transitionStart(COLOR);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Move Color command
******************************************************************************/
static ZCL_Status_t moveColorInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveColorCommand_t *payload)
{
  appSnprintf("moveColorInd()\r\n");
  //dbgLcdMsg("moveColor");

  if (prepareMoveColor(payload->rateX, payload->rateY))
  {
    setColorMode(ZCL_ZLL_CURRENT_X_AND_CURRENT_Y);
    transitionStart(COLOR);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Step Color command
******************************************************************************/
static ZCL_Status_t stepColorInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepColorCommand_t *payload)
{
  int32_t x, y;
  appSnprintf("stepColorInd()\r\n");
  //dbgLcdMsg("stepColor");

  if (0 == payload->stepX && 0 == payload->stepY)
  {
    transitionStop(ALL);
    return ZCL_SUCCESS_STATUS;
  }

  x = (int32_t)eclColorControlClusterServerAttributes.currentX.value + payload->stepX;
  y = (int32_t)eclColorControlClusterServerAttributes.currentY.value + payload->stepY;

  if ((x < MIN_COLOR_LEVEL) || (MAX_COLOR_LEVEL < x) ||
      (y < MIN_COLOR_LEVEL) || (MAX_COLOR_LEVEL < y))
    return ZCL_INVALID_VALUE_STATUS;

  if (prepareMoveToColor(x, y, payload->transitionTime))
  {
    setColorMode(ZCL_ZLL_CURRENT_X_AND_CURRENT_Y);
    transitionStart(COLOR);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Enhanced Move To Hue command
******************************************************************************/
static ZCL_Status_t enhancedMoveToHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllEnhancedMoveToHueCommand_t *payload)
{
  appSnprintf("enhancedMoveToHueInd()\r\n");
  //dbgLcdMsg("eMoveToHue");

  // Check for direction == 1?
  if (MAX_HUE_LEVEL < payload->enhancedHue)
    return ZCL_INVALID_VALUE_STATUS;

  setColorMode(ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION);
  if (prepareMoveToHue(payload->enhancedHue, payload->direction, payload->transitionTime, false))
  {
    transitionStart(HUE);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Enhanced Move Hue command
******************************************************************************/
static ZCL_Status_t enhancedMoveHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllEnhancedMoveHueCommand_t *payload)
{
  appSnprintf("enhancedMoveHueInd()\r\n");
  //dbgLcdMsg("eMoveHue");


  if (ZCL_ZLL_MOVE_HUE_MOVE_MODE_UP == payload->moveMode ||
      ZCL_ZLL_MOVE_HUE_MOVE_MODE_DOWN == payload->moveMode)
  {
    if (!payload->rate)
      return ZCL_INVALID_FIELD_STATUS;

    if (prepareMoveHue(payload->moveMode, payload->rate))
    {
      setColorMode(ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION);
      transitionStart(HUE);
    }
  }
  else if (ZCL_ZLL_MOVE_HUE_MOVE_MODE_STOP == payload->moveMode)
  {
    transitionStop(ALL);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Enhanced Step Hue command
******************************************************************************/
static ZCL_Status_t enhancedStepHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllEnhancedStepHueCommand_t *payload)
{
  uint16_t hue;
  appSnprintf("enhancedStepHueInd()\r\n");
  //dbgLcdMsg("eStepHue");

  hue = eclColorControlClusterServerAttributes.enhancedCurrentHue.value;

  if (ZCL_ZLL_STEP_HUE_STEP_MODE_UP == payload->stepMode)
    hue += (uint16_t)payload->stepSize;
  else if (ZCL_ZLL_STEP_HUE_STEP_MODE_DOWN == payload->stepMode)
    hue -= (uint16_t)payload->stepSize;
  else
    return ZCL_SUCCESS_STATUS;

  if (prepareMoveToHue(hue, ZCL_ZLL_MOVE_TO_HUE_DIRECTION_SHORTEST_DISTANCE, payload->transitionTime, true))
  {
    setColorMode(ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(HUE);
  }

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Enhanced Move To Hue And Saturation command
******************************************************************************/
static ZCL_Status_t enhancedMoveToHueAndSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllEnhancedMoveToHueAndSaturationCommand_t *payload)
{
  uint8_t proceedWith;
  appSnprintf("enhancedMoveToHueAndSaturationInd()\r\n");
  //dbgLcdMsg("eMTHAS");

  if (MAX_HUE_LEVEL < payload->enhancedHue ||
      MAX_SATURATION_LEVEL < payload->saturation)
    return ZCL_INVALID_VALUE_STATUS;

  proceedWith = prepareMoveToHue(payload->enhancedHue, ZCL_ZLL_MOVE_TO_HUE_DIRECTION_SHORTEST_DISTANCE, payload->transitionTime, false);
  proceedWith |= prepareMoveToSaturation(payload->saturation, payload->transitionTime, false);

  if (proceedWith)
  {
    setColorMode(ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(proceedWith);
  }

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Color Loop Set command
******************************************************************************/
static ZCL_Status_t colorLoopSetInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllColorLoopSetCommand_t *payload)
{
  appSnprintf("colorLoopSetInd()\r\n");
  //dbgLcdMsg("colorLoopSet");

  if (!isDeviceOn())
    return ZCL_SUCCESS_STATUS;

  if (COLOR_LOOP_UPDATE_DIRECTION & payload->updateFlags)
    eclColorControlClusterServerAttributes.colorLoopDirection.value = payload->direction;

  if (COLOR_LOOP_UPDATE_TIME & payload->updateFlags)
    eclColorControlClusterServerAttributes.colorLoopTime.value = payload->time;

  if (COLOR_LOOP_UPDATE_START_HUE & payload->updateFlags)
    eclColorControlClusterServerAttributes.colorLoopStartEnhancedHue.value = payload->startHue;

  if (COLOR_LOOP_UPDATE_ACTION & payload->updateFlags)
  {
    switch (payload->action)
    {
      case COLOR_LOOP_DEACTIVATE:
        if (eclColorControlClusterServerAttributes.colorLoopActive.value)
          stopColorLoop();
        break;

      case COLOR_LOOP_ACTIVATE_FROM_CLSEH:
        startColorLoop(COLOR_LOOP_ACTIVATE_FROM_CLSEH);
        break;

      case COLOR_LOOP_ACTIVATE_FROM_ECH:
        startColorLoop(COLOR_LOOP_ACTIVATE_FROM_ECH);
        break;

      default:
        break;
    }
  }

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of Stop Move Step command
******************************************************************************/
static ZCL_Status_t stopMoveStepInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, void *payload)
{
  appSnprintf("stopMoveStepInd()\r\n");
  //dbgLcdMsg("stopMoveStep");

  transitionStop(ALL);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}
/**************************************************************************//**
\brief Callback on receive of MoveToColorTemperature command
******************************************************************************/
static ZCL_Status_t moveToColorTemperatureInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToColorTemperatureCommand_t *payload)
{
  uint16_t miredValue;
  bool clippedStatus = false;

  appSnprintf("moveToColorTemperatureInd()\r\n");
  //dbgLcdMsg("moveToColorTemperature");

  if (eclColorControlClusterServerAttributes.colorTempPhysicalMin.value > payload->colorTemperature)
  {
    miredValue = eclColorControlClusterServerAttributes.colorTempPhysicalMin.value;
    clippedStatus = true;
  }
  else if (eclColorControlClusterServerAttributes.colorTempPhysicalMax.value < payload->colorTemperature)
  {
    miredValue = eclColorControlClusterServerAttributes.colorTempPhysicalMax.value;
    clippedStatus = true;
  }
  else
  {
    miredValue = payload->colorTemperature;
    clippedStatus = false;
  }

  if (prepareMoveToColorTemperature(miredValue, payload->transitionTime, false))
  {
    setColorMode(ZCL_ZLL_COLOR_TEMPERATURE);
    transitionStart(TEMPERATURE);
  }

  (void)addressing;
  (void)payloadLength;

  if (clippedStatus)
    return ZCL_SUCCESS_WITH_DEFAULT_RESPONSE_STATUS;
  else
    return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of MoveColorTemperature command
******************************************************************************/
static ZCL_Status_t moveColorTemperatureInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveColorTemperatureCommand_t *payload)
{
  appSnprintf("moveColorTemperatureInd()\r\n");
  //dbgLcdMsg("moveColorTemperature");

  if (ZCL_ZLL_MOVE_COLOR_TEMPERATURE_MOVE_MODE_STOP != payload->moveMode)
    if (!payload->rate)
      return ZCL_INVALID_VALUE_STATUS;

  if (ZCL_ZLL_MOVE_COLOR_TEMPERATURE_MOVE_MODE_UP == payload->moveMode ||
      ZCL_ZLL_MOVE_COLOR_TEMPERATURE_MOVE_MODE_DOWN == payload->moveMode)
  {
    if (prepareMoveColorTemperature(payload->moveMode, payload->rate, payload->colorTemperatureMinimum, payload->colorTemperatureMaximum))
    {
      setColorMode(ZCL_ZLL_COLOR_TEMPERATURE);
      transitionStart(TEMPERATURE);
    }
  }
   else if(ZCL_ZLL_MOVE_COLOR_TEMPERATURE_MOVE_MODE_STOP == payload->moveMode)
     transitionStop(ALL);

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Callback on receive of StepColorTemperature command
******************************************************************************/
static ZCL_Status_t stepColorTemperatureInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepColorTemperatureCommand_t *payload)
{
  uint16_t temperature;

  appSnprintf("stepColorTemperatureInd()\r\n");
  //dbgLcdMsg("stepColorTemperature");

  if (0 == payload->stepSize)
  {
    transitionStop(ALL);
    return ZCL_SUCCESS_STATUS;
  }

  temperature = eclColorControlClusterServerAttributes.colorTemperature.value;

  if (ZCL_ZLL_STEP_COLOR_TEMPERATURE_STEP_MODE_UP == payload->stepMode)
  {
    if (ABSOLUTE_MAXIMUM_COLOR_TEMP - temperature > payload->stepSize)
      temperature += payload->stepSize;
    else
      temperature = ABSOLUTE_MAXIMUM_COLOR_TEMP;

    if (temperature > payload->colorTemperatureMaximum)
      temperature = payload->colorTemperatureMaximum;
  }
  else if (ZCL_ZLL_STEP_COLOR_TEMPERATURE_STEP_MODE_DOWN == payload->stepMode)
  {
    if (temperature >= payload->stepSize)
      temperature -= payload->stepSize;
    else
      temperature = 0;

    if (temperature < payload->colorTemperatureMinimum)
      temperature = payload->colorTemperatureMinimum;
  }
  else
    return ZCL_SUCCESS_STATUS;

  if (temperature < eclColorControlClusterServerAttributes.colorTempPhysicalMin.value ||
      eclColorControlClusterServerAttributes.colorTempPhysicalMax.value < temperature)
    return ZCL_INVALID_VALUE_STATUS;

  if (prepareMoveToColorTemperature(temperature, payload->transitionTime, true))
  {
    setColorMode(ZCL_ZLL_COLOR_TEMPERATURE);
    transitionStart(TEMPERATURE);
  }

  (void)addressing;
  (void)payloadLength;
  return ZCL_SUCCESS_STATUS;
}


/**************************************************************************//**
\brief Stop color transitions
******************************************************************************/
void colorControlClusterStop(void)
{
  transitionStop(NONE);
}
#endif //def APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT

// eof lightColorControlCluster.c
