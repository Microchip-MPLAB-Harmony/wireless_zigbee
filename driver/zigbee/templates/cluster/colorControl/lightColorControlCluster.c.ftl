/*******************************************************************************
  Light device Color Control cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    lightColorControlCluster.c

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

#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT

/******************************************************************************
                    Includes
******************************************************************************/
#ifdef BOARD_MEGARF
#include <buttonsExt.h>
#endif

#if defined(BOARD_MEGARF) || defined(BOARD_SAMR21)
#include <ledsExt.h>
#include <lcdExt.h>
#endif

#if (BSP_SUPPORT == BOARD_SAMR21_ZLLEK)
#include <printLcd.h>
#else
#define dbgLcdMsg(...) while (0) {;}
#endif

#include <z3device/common/include/hs2xy.h>

#include <z3device/clusters/include/haClusters.h>
#include <z3device/light/include/lightScenesCluster.h>
#include <z3device/light/include/lightOnOffCluster.h>
#include <z3device/light/include/lightLevelControlCluster.h>
#include <z3device/light/include/lightColorControlCluster.h>
#include <z3device/common/include/z3Device.h>

#include <z3device/light/include/lightColorSchemesConversion.h>

#include <zllplatform/ZLL/N_DeviceInfo/include/N_DeviceInfo_Bindings.h>
#include <zllplatform/ZLL/N_DeviceInfo/include/N_DeviceInfo.h>
#include <pds/include/wlPdsMemIds.h>
#include <zcl/include/zclCommandManager.h>
#include <app_zigbee/zigbee_console/console.h>
#include <app_zigbee/app_zigbee_handler.h>
#include <zcl/include/zclAttributes.h>

/******************************************************************************
                    Definitions
******************************************************************************/
#define UPDATE_TIMER_INTERVAL    100 // 1/10th of a second as per specification

#define MIN_HUE_LEVEL             0
#define MAX_HUE_LEVEL             0xfeff
#define MAX_ENHANCED_HUE_LEVEL    0xffff

#define MIN_SATURATION_LEVEL      0
#define MAX_SATURATION_LEVEL      0xfe

#define MIN_COLOR_LEVEL           0
#define MAX_COLOR_LEVEL           0xfeff

#define DEFAULT_SATURATION_LEVEL 110
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
#if APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
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
#endif // APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
static ZCL_Status_t moveToColorTemperatureInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToColorTemperatureCommand_t *payload);
static ZCL_Status_t moveColorTemperatureInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveColorTemperatureCommand_t *payload);
static ZCL_Status_t stepColorTemperatureInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepColorTemperatureCommand_t *payload);
#endif // APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT

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

#if APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
static void setColorLoop(uint8_t colorLoopActive, uint8_t colorLoopDirection, uint16_t colorLoopTime);
static void startColorLoop(ZCL_ZllColorLoopAction_t action);
static TransitionType_t prepareMoveToHue(uint16_t hue, uint8_t direction, uint16_t transitionTime,
                                         bool byStep);
static TransitionType_t prepareMoveToSaturation(uint8_t saturation, uint16_t transitionTime,
                                                bool byStep);
static bool prepareMoveToColor(uint16_t x, uint16_t y, uint16_t transitionTime);
#endif // APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
static void ZCL_ColorControlAttributeEventInd(ZCL_Addressing_t *addressing,
  ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
#endif // APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
static bool prepareMoveToColorTemperature(uint16_t temperature, uint16_t transitionTime, bool byStep);
static void handleColorTemperatureTransition(void);
static bool prepareMoveColorTemperature(uint8_t moveMode, uint16_t rate, uint16_t tempMin, uint16_t tempMax);

#if ZLO_CLUSTER_ENHANCEMENTS == 1
static void lightUpdateStartupColorTemperature(void);

static void lightColorControlWriteAttributeEventHandler(SYS_EventId_t eventId, SYS_EventData_t data);

static SYS_EventReceiver_t lightColorControlWriteAttributeEvent = { .func = lightColorControlWriteAttributeEventHandler};
#endif
#endif // APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT


/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_ColorControlClusterServerAttributes_t lightColorControlClusterServerAttributes =
{
  ZCL_DEFINE_COLOR_CONTROL_SERVER_CLUSTER_ATTRIBUTES(0, 0)
};

PROGMEM_DECLARE(ZCL_ColorControlClusterCommands_t lightColorControlClusterServerCommands) =
{
#if APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
  ZCL_COLOR_CONTROL_CLUSTER_COMMANDS_FOR_EXTENDED_COLOR_LIGHT(moveToHueInd, moveHueInd, stepHueInd,
      moveToSaturationInd, moveSaturationInd, stepSaturationInd, moveToHueAndSaturationInd, moveToColorInd,
      moveColorInd, stepColorInd, moveToColorTemperatureInd, enhancedMoveToHueInd,
      enhancedMoveHueInd, enhancedStepHueInd, enhancedMoveToHueAndSaturationInd, colorLoopSetInd,
      stopMoveStepInd, moveColorTemperatureInd, stepColorTemperatureInd)
#elif APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_LIGHT
  ZCL_COLOR_CONTROL_CLUSTER_COMMANDS_FOR_COLOR_LIGHT(moveToHueInd, moveHueInd, stepHueInd,
      moveToSaturationInd, moveSaturationInd, stepSaturationInd, moveToHueAndSaturationInd, moveToColorInd,
      moveColorInd, stepColorInd, enhancedMoveToHueInd, enhancedMoveHueInd, enhancedStepHueInd,
      enhancedMoveToHueAndSaturationInd, colorLoopSetInd, stopMoveStepInd)
#else
  ZCL_COLOR_CONTROL_CLUSTER_COMMANDS_FOR_TEMPERATURE_COLOR_LIGHT(moveToColorTemperatureInd,
    moveColorTemperatureInd, stepColorTemperatureInd)
#endif
};

/******************************************************************************
                    Local variables
******************************************************************************/
static HAL_AppTimer_t updateTimer;
#if APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
static uint8_t bckpSaturation;
static uint16_t bckpEnhacnedHue;
#endif // APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT

/* gExecuteIfOff:
 * --------------
 * Used with the "Execute If Off" behavior
 *
 * true  => if the device is in OFF state, color control command
 *          WILL BE PROCESSED but there WILL NOT BE change in LED.
 *          i.e., Execute If, the device is, Off
 *
 * false => if the device is in OFF state, color control command
 *           WILL NOT BE PROCESSED
 */
static bool gExecuteIfOff = false;

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
void lightColorControlClusterInit(void)
{
#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
  ZCL_Cluster_t *cluster =  ZCL_GetCluster(APP_ENDPOINT_LIGHT, COLOR_CONTROL_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
  if (cluster)
    cluster->ZCL_AttributeEventInd = ZCL_ColorControlAttributeEventInd;
#endif //#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT

  if (!PDS_IsAbleToRestore(APP_LIGHT_COLOR_CONTROL_MEM_ID))
  {
#if APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
    uint8_t colorCapabilities = 0;
#else
    uint8_t colorCapabilities = 1;
#endif // APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTHUE == true) >
    lightColorControlClusterServerAttributes.currentHue.value                 = ZCL_ZLL_CLUSTER_CURRENT_HUE_DEFAULT_VALUE;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTSATURATION == true) >
    lightColorControlClusterServerAttributes.currentSaturation.value          = DEFAULT_SATURATION_LEVEL;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_REMAININGTIME == true) >
    lightColorControlClusterServerAttributes.remainingTime.value              = ZCL_ZLL_CLUSTER_REMAINING_TIME_DEFAULT_VALUE;
</#if>

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTX == true) >  
    lightColorControlClusterServerAttributes.currentX.value                   = ZCL_ZLL_CLUSTER_CURRENT_X_DEFAULT_VALUE;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTY == true) > 
    lightColorControlClusterServerAttributes.currentY.value                   = ZCL_ZLL_CLUSTER_CURRENT_Y_DEFAULT_VALUE;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPMIREDS == true) >
    lightColorControlClusterServerAttributes.colorTemperature.value           = ZCL_ZCL_CLUSTER_COLOR_TEMP_DEFAULT_VALUE;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORMODE == true) >
    lightColorControlClusterServerAttributes.colorMode.value                  = ZCL_ZLL_CLUSTER_COLOR_MODE_DEFAULT_VALUE;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_NUMBEROFPRIMARIES == true) >
    lightColorControlClusterServerAttributes.numberOfPrimaries.value          = 1;
</#if>

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY1X == true) > 
    lightColorControlClusterServerAttributes.primary1X.value                  = 41942; // red
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY1Y == true) > 
    lightColorControlClusterServerAttributes.primary1Y.value                  = 20971; // red
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY1INTENSITY == true) >
    lightColorControlClusterServerAttributes.primary1XIntensity.value         = 0;
</#if>

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY2X == true) >
    lightColorControlClusterServerAttributes.primary2X.value                  = 0;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY2Y == true) > 
    lightColorControlClusterServerAttributes.primary2Y.value                  = 0;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY2INTENSITY == true) >
    lightColorControlClusterServerAttributes.primary2XIntensity.value         = 0;
</#if>

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY3X == true) >  
    lightColorControlClusterServerAttributes.primary3X.value                  = 0;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY3Y == true) > 
    lightColorControlClusterServerAttributes.primary3Y.value                  = 0;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY3INTENSITY == true) >
    lightColorControlClusterServerAttributes.primary3XIntensity.value         = 0;
</#if>

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY4X == true) >
    lightColorControlClusterServerAttributes.primary4X.value                  = 0;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY4Y == true) >
    lightColorControlClusterServerAttributes.primary4Y.value                  = 0;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY4INTENSITY == true) >
    lightColorControlClusterServerAttributes.primary4XIntensity.value         = 0;
</#if>

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY5X == true) >
    lightColorControlClusterServerAttributes.primary5X.value                  = 0;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY5Y == true) >
    lightColorControlClusterServerAttributes.primary5Y.value                  = 0;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY5INTENSITY == true) >
    lightColorControlClusterServerAttributes.primary5XIntensity.value         = 0;
</#if>

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY6X == true) >
    lightColorControlClusterServerAttributes.primary6X.value                  = 0;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY6Y == true) >
    lightColorControlClusterServerAttributes.primary6Y.value                  = 0;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY6INTENSITY == true) >
    lightColorControlClusterServerAttributes.primary6XIntensity.value         = 0;
</#if>

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDCURRENTHUE == true) >
    lightColorControlClusterServerAttributes.enhancedCurrentHue.value         = ZCL_ZCL_CLUSTER_ENHANCED_CURRENT_HUE_DEFAULT_VALUE;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDCOLORMODE == true) >
    lightColorControlClusterServerAttributes.enhancedColorMode.value          = ZCL_ZCL_CLUSTER_ENHANCED_COLOR_MODE_DEFAULT_VALUE;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPACTIVE == true) > 
    lightColorControlClusterServerAttributes.colorLoopActive.value            = ZCL_ZCL_CLUSTER_COLOR_LOOP_ACTIVE_DEFAULT_VALUE;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPDIRECTION == true) >
    lightColorControlClusterServerAttributes.colorLoopDirection.value         = ZCL_ZCL_CLUSTER_COLOR_LOOP_DIRECTION_DEFAULT_VALUE;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPTIME == true) >
    lightColorControlClusterServerAttributes.colorLoopTime.value              = ZCL_ZCL_CLUSTER_COLOR_LOOP_TIME_DEFAULT_VALUE;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPSTARTENHANCEDHUE == true) > 
    lightColorControlClusterServerAttributes.colorLoopStartEnhancedHue.value  = ZCL_ZCL_CLUSTER_COLOR_LOOP_START_ENHANCED_HUE_DEFAULT_VALUE;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPSTOREDENHANCEDHUE == true) >
    lightColorControlClusterServerAttributes.colorLoopStoredEnhancedHue.value = ZCL_ZCL_CLUSTER_COLOR_LOOP_STORED_ENHANCED_HUE_DEFAULT_VALUE;
</#if>

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORCAPABILITIES == true) >
    lightColorControlClusterServerAttributes.colorCapabilities.value.hueSaturationSupported = colorCapabilities;
    lightColorControlClusterServerAttributes.colorCapabilities.value.enhancedHueSupported   = colorCapabilities;
    lightColorControlClusterServerAttributes.colorCapabilities.value.colorLoopSupported     = colorCapabilities;
    lightColorControlClusterServerAttributes.colorCapabilities.value.XYAttributesSupported  = colorCapabilities;
</#if>

#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORCAPABILITIES == true) >
    lightColorControlClusterServerAttributes.colorCapabilities.value.colorTemperatureSupported = 1;
</#if>
#if ZLO_CLUSTER_ENHANCEMENTS == 1
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_STARTUPCOLORTEMPMIREDS == true) >
    lightColorControlClusterServerAttributes.startUpColorTemperatureMireds.value = ZCL_ZLL_STARTUP_COLOR_TEMPERATURE_PREVIOUS;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COUPLECOLORTEMPTOLEVELMINMIREDS == true) >
    lightColorControlClusterServerAttributes.coupleColorTempToLevelMinMireds.value = ZCL_ZCL_CLUSTER_TEMP_PHYSICAL_MIN_DEFAULT_VALUE;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_OPTIONS == true) >
    lightColorControlClusterServerAttributes.options.value = 0x00; // Bit#0: ExecuteIfOff
</#if>
#endif
    gExecuteIfOff = false;
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORCAPABILITIES == true) >
#else
    lightColorControlClusterServerAttributes.colorCapabilities.value.colorTemperatureSupported = 0;
</#if>
#endif // APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPPHYMINMIREDS == true) >
    lightColorControlClusterServerAttributes.colorTempPhysicalMin.value = ZCL_ZCL_CLUSTER_TEMP_PHYSICAL_MIN_DEFAULT_VALUE;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPPHYMAXMIREDS == true) >
    lightColorControlClusterServerAttributes.colorTempPhysicalMax.value = ZCL_ZCL_CLUSTER_TEMP_PHYSICAL_MAX_DEFAULT_VALUE;
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTHUE == true) >
  lightColorControlClusterServerAttributes.currentHue.minReportInterval = COLOR_CONTROL_CUURENT_HUE_MIN_REPORT_PERIOD;
  lightColorControlClusterServerAttributes.currentHue.maxReportInterval = COLOR_CONTROL_CUURENT_HUE_MAX_REPORT_PERIOD;
</#if>

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTSATURATION == true) >
  lightColorControlClusterServerAttributes.currentSaturation.minReportInterval = COLOR_CONTROL_CURRENT_SAT_MIN_REPORT_PERIOD;
  lightColorControlClusterServerAttributes.currentSaturation.maxReportInterval = COLOR_CONTROL_CURRENT_SAT_MAX_REPORT_PERIOD;
</#if>

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTX == true) >
  lightColorControlClusterServerAttributes.currentX.minReportInterval = COLOR_CONTROL_CURR_X_MIN_REPORT_PERIOD;
  lightColorControlClusterServerAttributes.currentX.maxReportInterval = COLOR_CONTROL_CURR_X_MAX_REPORT_PERIOD;
</#if>

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTY == true) >
  lightColorControlClusterServerAttributes.currentY.minReportInterval = COLOR_CONTROL_CURR_Y_MIN_REPORT_PERIOD;
  lightColorControlClusterServerAttributes.currentY.maxReportInterval = COLOR_CONTROL_CURR_Y_MAX_REPORT_PERIOD;
</#if>

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPMIREDS == true) >
  lightColorControlClusterServerAttributes.colorTemperature.minReportInterval = COLOR_CONTROL_COLOR_TEMP_MIN_REPORT_PERIOD;
  lightColorControlClusterServerAttributes.colorTemperature.maxReportInterval = COLOR_CONTROL_COLOR_TEMP_MAX_REPORT_PERIOD;
</#if>

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CLUSTERREVISION == true) >
  lightColorControlClusterServerAttributes.clusterVersion.value = COLOR_CONTROL_CLUSTER_VERSION;
</#if>
  }
#if (APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT)
  else
  {
    PDS_Restore(APP_LIGHT_COLOR_CONTROL_MEM_ID);
  }
#endif //(APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT)

  updateTimer.mode = TIMER_REPEAT_MODE;
  updateTimer.interval = UPDATE_TIMER_INTERVAL;
  updateTimer.callback = updateTransitionState;

#if ZLO_CLUSTER_ENHANCEMENTS == 1
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_STARTUPCOLORTEMPMIREDS == true) >
#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
  lightUpdateStartupColorTemperature();

  SYS_SubscribeToEvent(BC_ZCL_EVENT_ACTION_REQUEST, &lightColorControlWriteAttributeEvent);
#endif //#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
</#if>
#endif

  displayStatus();

}

/**************************************************************************//**
\brief Set Extension Field Set
******************************************************************************/
void colorControlClusterSetExtensionField(Scene_t *scene, uint16_t transitionTime)
{
  uint8_t proceedWith = 0;
  setColorMode(scene->colorMode);
#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_LIGHT) || (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT)
  if (0xffff == transitionTime || 0 == transitionTime)
  {
    setHue(scene->enhancedCurrentHue);
    setSaturation(scene->currentSaturation);
  }
  else
  {
    if(prepareMoveToHue(scene->enhancedCurrentHue, 1 , transitionTime, false))
      proceedWith = HUE;
    if(prepareMoveToSaturation(scene->currentSaturation, transitionTime, false))
      proceedWith |= SATURATION;
  }
  setColorLoop(scene->colorLoopActive, scene->colorLoopDirection, scene->colorLoopTime);
#endif // (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_LIGHT) || (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT)
#if APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
  if (0xffff == transitionTime || 0 == transitionTime)
    setColor(scene->currentX, scene->currentY);
  else
    if(prepareMoveToColor(scene->currentX, scene->currentY, transitionTime))
      proceedWith |= COLOR;
#endif   
#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
  if (0xffff == transitionTime || 0 == transitionTime)
    setColorTemperature(scene->colorTemperature);
  else
    if(prepareMoveToColorTemperature(scene->colorTemperature, transitionTime, false))
      proceedWith |= TEMPERATURE;
#endif // APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
  if (proceedWith)
    transitionStart((TransitionType_t)proceedWith);
}

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY1INTENSITY == true) && (CC_CURRENTSATURATION == true)>
INLINE uint8_t levelControlCalculateIntensity(void)
{
  // Wrong in general..
  return lightColorControlClusterServerAttributes.currentSaturation.value == UINT8_MAX ?
         UINT8_MAX - 1 : lightColorControlClusterServerAttributes.currentSaturation.value;
  // Should be something like..
  //return (uint8_t) pow(10.0, ((currentLevel - 1) * 3 / 253 ) - 1);
}
</#if>

/**************************************************************************//**
\brief Display current level status.
******************************************************************************/
static void displayStatus(void)
{
  /* if the device is in OFF state, color control command
   * WILL BE PROCESSED but there WILL NOT BE change in LED.
   */
  if (gExecuteIfOff)
    return;

    // add information about color temperature
#if APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
  LCD_PRINT(0, 1, 
   "<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTX == true) >%5u </#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTY == true) > %5u </#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDCURRENTHUE == true) >%5u </#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTSATURATION == true) >%3u</#if>",
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTX == true) >
            lightColorControlClusterServerAttributes.currentX.value,
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTY == true) >
            lightColorControlClusterServerAttributes.currentY.value,
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDCURRENTHUE == true) >            
            lightColorControlClusterServerAttributes.enhancedCurrentHue.value,
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTSATURATION == true) >            
            lightColorControlClusterServerAttributes.currentSaturation.value
</#if>
           );
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORMODE == true) > 
  switch (lightColorControlClusterServerAttributes.colorMode.value)
  {
     uint32_t tmpColorX, tmpColorY;
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDCURRENTHUE == true) && (CC_CURRENTSATURATION == true) >        
    case ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION:  
      // Get the X and Y values for the required hue and saturation
      HS2XY((int)lightColorControlClusterServerAttributes.enhancedCurrentHue.value >> 8,
        (int)lightColorControlClusterServerAttributes.currentSaturation.value,
        (unsigned int *)&tmpColorX,(unsigned int *)&tmpColorY);        
      // Set the LED color for the X and Y values
      LEDS_SET_COLOR_XY(tmpColorX,tmpColorY);
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTX == true) >
      lightColorControlClusterServerAttributes.currentX.value = tmpColorX;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTY == true) >
      lightColorControlClusterServerAttributes.currentY.value = tmpColorY;
</#if>
      break;
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPMIREDS == true) > 
    case ZCL_ZLL_COLOR_TEMPERATURE:
      lightConvertColorToXY(lightColorControlClusterServerAttributes.colorTemperature.value,
        (uint16_t *)&tmpColorX, (uint16_t *)&tmpColorY
      );
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTX == true) >
      lightColorControlClusterServerAttributes.currentX.value = (uint16_t)tmpColorX;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTY == true) >
      lightColorControlClusterServerAttributes.currentY.value = (uint16_t)tmpColorY;
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTX == true) && (CC_CURRENTY == true) >
    // fall through from ZCL_ZLL_COLOR_TEMPERATURE case
    default:
      LEDS_SET_COLOR_XY(
        lightColorControlClusterServerAttributes.currentX.value,
        lightColorControlClusterServerAttributes.currentY.value
      );
      break;
</#if>
</#if>
  }
</#if>
#ifdef _ZCL_REPORTING_SUPPORT_
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTX == true) >
  ZCL_ReportOnChangeIfNeeded(&lightColorControlClusterServerAttributes.currentX);
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTY == true) >
  ZCL_ReportOnChangeIfNeeded(&lightColorControlClusterServerAttributes.currentY);
</#if>
#endif
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPMIREDS == true) >
#else
  LCD_PRINT(0, 1, "%5u", lightColorControlClusterServerAttributes.colorTemperature.value);
</#if>
#endif // APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
}


/**************************************************************************//**
\brief Set current mode
******************************************************************************/
static void setColorMode(uint8_t mode)
{
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDCOLORMODE == true) >
  lightColorControlClusterServerAttributes.enhancedColorMode.value  = mode;
</#if>

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORMODE == true) >
  if (ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION == mode)
    lightColorControlClusterServerAttributes.colorMode.value = ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION;
  else
    lightColorControlClusterServerAttributes.colorMode.value = mode;
</#if>
}


/**************************************************************************//**
\brief Set hue value
******************************************************************************/
static void setHue(uint16_t hue)
{
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDCURRENTHUE == true) >  
  if (lightColorControlClusterServerAttributes.enhancedCurrentHue.value != hue)
  {
    lightColorControlClusterServerAttributes.enhancedCurrentHue.value = hue;
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTHUE == true) >    
    lightColorControlClusterServerAttributes.currentHue.value = hue >> 8;
</#if>
    lightScenesInvalidate();
    displayStatus();
#ifdef _ZCL_REPORTING_SUPPORT_
    ZCL_ReportOnChangeIfNeeded(&lightColorControlClusterServerAttributes.currentHue);
#endif
  }
</#if>
}

/**************************************************************************//**
\brief Set saturation value
******************************************************************************/
static void setSaturation(uint8_t saturation)
{
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTSATURATION == true) >
  if (lightColorControlClusterServerAttributes.currentSaturation.value != saturation)
  {
    lightColorControlClusterServerAttributes.currentSaturation.value = saturation;
    lightScenesInvalidate();
    displayStatus();
#ifdef _ZCL_REPORTING_SUPPORT_
    ZCL_ReportOnChangeIfNeeded(&lightColorControlClusterServerAttributes.currentSaturation);
#endif
  }
</#if>
}

/**************************************************************************//**
\brief Set color value
******************************************************************************/
static void setColor(uint16_t x, uint16_t y)
{
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTX == true) && (CC_CURRENTY == true) >  
  if (lightColorControlClusterServerAttributes.currentX.value != x ||
      lightColorControlClusterServerAttributes.currentY.value != y)
  {
    lightColorControlClusterServerAttributes.currentX.value = x;
    lightColorControlClusterServerAttributes.currentY.value = y;
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY1X == true) >
    lightColorControlClusterServerAttributes.primary1X.value = x;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY1Y == true) >
    lightColorControlClusterServerAttributes.primary1Y.value = y;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_PRIMARY1INTENSITY == true) && (CC_CURRENTSATURATION == true)>
    lightColorControlClusterServerAttributes.primary1XIntensity.value =
      levelControlCalculateIntensity();
</#if>

    lightScenesInvalidate();
    displayStatus();
#ifdef _ZCL_REPORTING_SUPPORT_
    ZCL_ReportOnChangeIfNeeded(&lightColorControlClusterServerAttributes.currentX);
    ZCL_ReportOnChangeIfNeeded(&lightColorControlClusterServerAttributes.currentY);
#endif
  }
</#if>
}

/**************************************************************************//**
\brief Set color temperature value
******************************************************************************/
static void setColorTemperature(uint16_t temperature)
{
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPMIREDS == true) >
  if (lightColorControlClusterServerAttributes.colorTemperature.value != temperature)
  {
    lightColorControlClusterServerAttributes.colorTemperature.value = temperature;
    lightScenesInvalidate();
    displayStatus();
#ifdef _ZCL_REPORTING_SUPPORT_
    ZCL_ReportOnChangeIfNeeded(&lightColorControlClusterServerAttributes.colorTemperature);
#endif
  }
</#if>
}

#if APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
/**************************************************************************//**
\brief Set Color Loop values
******************************************************************************/
static void setColorLoop(uint8_t colorLoopActive, uint8_t colorLoopDirection, uint16_t colorLoopTime)
{
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPACTIVE == true) >  
  lightColorControlClusterServerAttributes.colorLoopActive.value    = colorLoopActive;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPDIRECTION == true) >
  lightColorControlClusterServerAttributes.colorLoopDirection.value = colorLoopDirection;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPTIME == true) >
  lightColorControlClusterServerAttributes.colorLoopTime.value      = colorLoopTime;
</#if>

  if (colorLoopActive)
    startColorLoop(COLOR_LOOP_ACTIVATE_FROM_ECH);
}

/**************************************************************************//**
\brief Stop Color Loop handler.
******************************************************************************/
static void stopColorLoop(void)
{
  transitionStop(ALL);
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPACTIVE == true) >   
  lightColorControlClusterServerAttributes.colorLoopActive.value = 0;
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPSTOREDENHANCEDHUE == true) >
  setHue(lightColorControlClusterServerAttributes.colorLoopStoredEnhancedHue.value);
</#if>
}

/**************************************************************************//**
\brief Starts the color loop specified way.

\param[in] action - color loop mode.
******************************************************************************/
static void startColorLoop(ZCL_ZllColorLoopAction_t action)
{
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDCURRENTHUE == true) >
  lightColorControlClusterServerAttributes.colorLoopStoredEnhancedHue.value =
    lightColorControlClusterServerAttributes.enhancedCurrentHue.value;
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPSTARTENHANCEDHUE == true) >
  if (COLOR_LOOP_ACTIVATE_FROM_ECH == action)
      lightColorControlClusterServerAttributes.colorLoopStartEnhancedHue.value =
      lightColorControlClusterServerAttributes.enhancedCurrentHue.value;
</#if>
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPACTIVE == true) >
  lightColorControlClusterServerAttributes.colorLoopActive.value = 1;
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_REMAININGTIME == true) >
  lightColorControlClusterServerAttributes.remainingTime.value = 0xffff;
</#if>
  setColorMode(ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION);
  transitionStart(COLOR_LOOP);
}
#endif // APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT

/**************************************************************************//**
\brief Handle hue transition
******************************************************************************/
static void handleHueTransition(void)
{
  if (hueTransition.direction)
  {// Up transition
    hueTransition.current += hueTransition.delta;
  }
  else
  {// Down transition
    hueTransition.current -= hueTransition.delta;
  }

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
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPTIME == true) >
  uint16_t delta = (MAX_HUE_LEVEL - MIN_HUE_LEVEL) /
                   (lightColorControlClusterServerAttributes.colorLoopTime.value * 10);
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDCURRENTHUE == true) >
  int32_t enhancedHue = lightColorControlClusterServerAttributes.enhancedCurrentHue.value;

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPDIRECTION == true) >
  // Up transition
  if (lightColorControlClusterServerAttributes.colorLoopDirection.value)
    enhancedHue += delta;
  // Down transition
  else
    enhancedHue -= delta;
</#if>

  if (enhancedHue < MIN_HUE_LEVEL)
    enhancedHue = MAX_HUE_LEVEL;
  else if (MAX_HUE_LEVEL < enhancedHue)
    enhancedHue = MIN_HUE_LEVEL;

  setHue(enhancedHue);
</#if>
</#if>
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
#if APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
  TransitionType_t proceedWith;
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTSATURATION == true) >
  bckpSaturation = lightColorControlClusterServerAttributes.currentSaturation.value;
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDCURRENTHUE == true) >
  bckpEnhacnedHue = lightColorControlClusterServerAttributes.enhancedCurrentHue.value;
</#if>
  proceedWith = prepareMoveToHue(enhancedHue,
    ZCL_ZLL_MOVE_TO_HUE_DIRECTION_SHORTEST_DISTANCE, DEFAULT_TRANSITION_TIME, false);
  proceedWith |= prepareMoveToSaturation(DEFAULT_SATURATION_LEVEL,
    DEFAULT_TRANSITION_TIME, false);

  if (proceedWith)
  {
    setColorMode(ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(proceedWith);
  }
#else
  (void)enhancedHue;
#endif // APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
}

/**************************************************************************//**
\brief Stop showing identify effect and return to previous state.
******************************************************************************/
void colorControlStopIdentifyEffect(void)
{
#if APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
  TransitionType_t proceedWith;

  proceedWith = prepareMoveToHue(bckpEnhacnedHue,
    ZCL_ZLL_MOVE_TO_HUE_DIRECTION_SHORTEST_DISTANCE, DEFAULT_TRANSITION_TIME, false);
  proceedWith |= prepareMoveToSaturation(bckpSaturation, DEFAULT_TRANSITION_TIME, false);

  if (proceedWith)
  {
    setColorMode(ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(proceedWith);
  }
#endif // APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
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
#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
    setColorTemperature(lightConvertXYToColor(colorTransition.targetX, colorTransition.targetY));
#endif // APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
  }

  if (inTransition & TEMPERATURE)
  {
#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
    uint16_t x, y;

    lightConvertColorToXY(colorTemperatureTransition.target, &x, &y);
    setColor(x, y);
#endif // APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
    setColorTemperature(colorTemperatureTransition.target);
  }
}

/**************************************************************************//**
\brief Update transition state
******************************************************************************/
static void updateTransitionState(void)
{
  if (!deviceIsOn() && !gExecuteIfOff)
  {
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_REMAININGTIME == true) >
    lightColorControlClusterServerAttributes.remainingTime.value = 0;
</#if>
    HAL_StopAppTimer(&updateTimer);
    return;
  }

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_REMAININGTIME == true) >
  if (lightColorControlClusterServerAttributes.remainingTime.value < 0xffff)
    lightColorControlClusterServerAttributes.remainingTime.value--;

  if ((lightColorControlClusterServerAttributes.remainingTime.value > 0) ||
          (lightColorControlClusterServerAttributes.colorLoopActive.value ==1))
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
</#if>
}

/**************************************************************************//**
\brief Start the transition
******************************************************************************/
static void transitionStart(TransitionType_t type)
{
  inTransition |= type;

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_REMAININGTIME == true) >
  if (lightColorControlClusterServerAttributes.remainingTime.value > 0)
  {
    HAL_StopAppTimer(&updateTimer);
    HAL_StartAppTimer(&updateTimer);
  }
  else
  {
    setTargetValue();
    transitionStop(type);
  }
</#if>
}

/**************************************************************************//**
\brief Start current transition
******************************************************************************/
static void transitionStop(TransitionType_t type)
{
  gExecuteIfOff = false;

  inTransition &= ~type;

  if (NONE == inTransition)
  {
    HAL_StopAppTimer(&updateTimer);
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_REMAININGTIME == true) >
    lightColorControlClusterServerAttributes.remainingTime.value = 0;
</#if>
  }

  PDS_Store(Z3DEVICE_APP_MEMORY_MEM_ID);
}

#if APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
/**************************************************************************//**
\brief Prepare Move To Hue parameters
******************************************************************************/
static TransitionType_t prepareMoveToHue(uint16_t hue, uint8_t direction, uint16_t transitionTime,
                                         bool byStep)
{
  uint16_t delta;
  bool dir = true;

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDCURRENTHUE == true) > 
  if (hue == lightColorControlClusterServerAttributes.enhancedCurrentHue.value)
    return NONE;
</#if>

  hueTransition.target = hue;
  hueTransition.byStep = byStep;


  {
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDCURRENTHUE == true) > 
    // Get shortest distance direction and delta
    if (hue > lightColorControlClusterServerAttributes.enhancedCurrentHue.value)
    {
      dir = true;
      delta = hue - lightColorControlClusterServerAttributes.enhancedCurrentHue.value;
    }
    else
    {
      dir = false;
      delta = lightColorControlClusterServerAttributes.enhancedCurrentHue.value - hue;
    }
</#if>

    // Check if change in direction is needed
    if (ZCL_ZLL_MOVE_TO_HUE_DIRECTION_LONGEST_DISTANCE == direction ||
        (ZCL_ZLL_MOVE_TO_HUE_DIRECTION_UP == direction && false == dir) ||
        (ZCL_ZLL_MOVE_TO_HUE_DIRECTION_DOWN == direction && true == dir))
    {
      dir = !dir;
      delta = (MAX_HUE_LEVEL - MIN_HUE_LEVEL) - delta;
    }
   if(transitionTime)
     hueTransition.delta = ((uint32_t)delta << 16) / transitionTime;
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDCURRENTHUE == true) >     
    hueTransition.current = (uint32_t)lightColorControlClusterServerAttributes.enhancedCurrentHue.value << 16;
</#if>
    hueTransition.direction = dir;
  }

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_REMAININGTIME == true) >
  lightColorControlClusterServerAttributes.remainingTime.value = transitionTime;
</#if>

  return HUE;
}

/**************************************************************************//**
\brief Prepare Move Hue parameters
******************************************************************************/
static bool prepareMoveHue(uint8_t mode, uint16_t rate)
{
  if (ZCL_ZLL_MOVE_HUE_MOVE_MODE_UP == mode)
    hueTransition.direction = true;
  else
    hueTransition.direction = false;

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDCURRENTHUE == true) >
  hueTransition.current = (uint32_t)lightColorControlClusterServerAttributes.enhancedCurrentHue.value << 16;
</#if>
  hueTransition.target = 0;
  hueTransition.delta = ((uint32_t)rate << 16) / 10;
  hueTransition.byStep = false;
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_REMAININGTIME == true) >
  lightColorControlClusterServerAttributes.remainingTime.value = 0xffff;
</#if>

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

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTSATURATION == true) >
  if (saturation == lightColorControlClusterServerAttributes.currentSaturation.value)
    return NONE;
</#if>

  saturationTransition.target = saturation;
  saturationTransition.byStep = byStep;


  {
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTSATURATION == true) >
    // Get shortest distance direction and delta
    if (saturation > lightColorControlClusterServerAttributes.currentSaturation.value)
    {
      dir = true;
      delta = saturation - lightColorControlClusterServerAttributes.currentSaturation.value;
    }
    else
    {
      dir = false;
      delta = lightColorControlClusterServerAttributes.currentSaturation.value - saturation;
    }
    if(transitionTime)
      saturationTransition.delta = ((uint32_t)delta << 16) / (uint32_t)transitionTime;
    saturationTransition.current = (uint32_t)lightColorControlClusterServerAttributes.currentSaturation.value << 16;
    saturationTransition.direction = dir;
</#if>
  }
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_REMAININGTIME == true) >
  lightColorControlClusterServerAttributes.remainingTime.value = transitionTime;
</#if>

  return SATURATION;
}

/**************************************************************************//**
\brief Prepare Move Saturation parameters
******************************************************************************/
static bool prepareMoveSaturation(uint8_t mode, uint16_t rate)
{
  if (ZCL_ZLL_MOVE_HUE_MOVE_MODE_UP == mode)
    saturationTransition.direction = true;
  else
    saturationTransition.direction = false;
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTSATURATION == true) >
  saturationTransition.current = (uint32_t)lightColorControlClusterServerAttributes.currentSaturation.value << 16;
</#if>
  saturationTransition.target = 0;
  saturationTransition.delta = ((uint32_t)rate << 16) / 10;
  saturationTransition.byStep = false;

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_REMAININGTIME == true) >
  lightColorControlClusterServerAttributes.remainingTime.value = 0xffff;
</#if>
  return true;
}


/**************************************************************************//**
\brief Prepare Move To Color parameters
******************************************************************************/
static bool prepareMoveToColor(uint16_t x, uint16_t y, uint16_t transitionTime)
{
  uint16_t deltax, deltay;
  bool dirx, diry;
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTX == true) && (CC_CURRENTY == true)>
  if (x == lightColorControlClusterServerAttributes.currentX.value &&
      y == lightColorControlClusterServerAttributes.currentY.value)
    return false;

  // Get shortest distance direction and delta
  dirx = x > lightColorControlClusterServerAttributes.currentX.value;

  if (dirx)
    deltax = x - lightColorControlClusterServerAttributes.currentX.value;
  else
    deltax = lightColorControlClusterServerAttributes.currentX.value - x;

  diry = y > lightColorControlClusterServerAttributes.currentY.value;

  if (diry)
    deltay = y - lightColorControlClusterServerAttributes.currentY.value;
  else
    deltay = lightColorControlClusterServerAttributes.currentY.value - y;

  if(transitionTime)
  {
    colorTransition.deltaX = ((uint32_t)deltax << 16) / transitionTime;
    colorTransition.deltaY = ((uint32_t)deltay << 16) / transitionTime;
  }
  colorTransition.currentX = (uint32_t)lightColorControlClusterServerAttributes.currentX.value << 16;
  colorTransition.currentY = (uint32_t)lightColorControlClusterServerAttributes.currentY.value << 16;
  colorTransition.directionX = dirx;
  colorTransition.directionY = diry;
  colorTransition.targetX = x;
  colorTransition.targetY = y;
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_REMAININGTIME == true) >
  lightColorControlClusterServerAttributes.remainingTime.value = transitionTime;
</#if>
  return true;
}

/**************************************************************************//**
\brief Prepare Move Color parameters
******************************************************************************/
static bool prepareMoveColor(int16_t ratex, int16_t ratey)
{
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTX == true)>
  // X
  colorTransition.deltaX = ((uint32_t)ABS(ratex) << 16) / 10;
  colorTransition.currentX = (uint32_t)lightColorControlClusterServerAttributes.currentX.value << 16;
  colorTransition.directionX = ratex > 0;
  colorTransition.targetX = 0;
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTY == true)>
  // Y
  colorTransition.deltaY = ((uint32_t)ABS(ratey) << 16) / 10;
  colorTransition.currentY = (uint32_t)lightColorControlClusterServerAttributes.currentY.value << 16;
  colorTransition.directionY = ratey > 0;
  colorTransition.targetY = 0;
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_REMAININGTIME == true) >
  lightColorControlClusterServerAttributes.remainingTime.value = 0xffff;
</#if>
  return true;
}
#endif // APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
/**************************************************************************//**
\brief Prepare Move To Color Temperature parameters
******************************************************************************/
static bool prepareMoveToColorTemperature(uint16_t temperature, uint16_t transitionTime, bool byStep)
{
  uint16_t deltaTemp;
  bool dirTemp;

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPMIREDS == true) >
  if (temperature == lightColorControlClusterServerAttributes.colorTemperature.value)
    return false;

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_REMAININGTIME == true) >
  lightColorControlClusterServerAttributes.remainingTime.value = transitionTime;
</#if>  
  colorTemperatureTransition.target                       = temperature;
  colorTemperatureTransition.byStep                       = byStep;

  // Get shortest distance direction and delta
  dirTemp = temperature > lightColorControlClusterServerAttributes.colorTemperature.value;
  if (dirTemp)
    deltaTemp = temperature - lightColorControlClusterServerAttributes.colorTemperature.value;
  else
    deltaTemp = lightColorControlClusterServerAttributes.colorTemperature.value - temperature;
  if(transitionTime)
    colorTemperatureTransition.delta     = ((uint32_t)deltaTemp << 16) / transitionTime;
  colorTemperatureTransition.current   = (uint32_t)lightColorControlClusterServerAttributes.colorTemperature.value << 16;
  colorTemperatureTransition.direction = dirTemp;
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPPHYMINMIREDS == true) >
  colorTemperatureTransition.minTemp   = lightColorControlClusterServerAttributes.colorTempPhysicalMin.value;
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPPHYMAXMIREDS == true) >
  colorTemperatureTransition.maxTemp   = lightColorControlClusterServerAttributes.colorTempPhysicalMax.value;
</#if>

  return true;
</#if>
}

/**************************************************************************//**
\brief Prepare Move Color Temperature parameters
******************************************************************************/
static bool prepareMoveColorTemperature(uint8_t moveMode, uint16_t rate, uint16_t tempMin, uint16_t tempMax)
{
  colorTemperatureTransition.delta     = ((uint32_t)ABS(rate) << 16) / 10;
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPMIREDS == true) >  
  colorTemperatureTransition.current   = (uint32_t)lightColorControlClusterServerAttributes.colorTemperature.value << 16;
</#if>
  colorTemperatureTransition.direction = ZCL_ZLL_MOVE_SATURATION_MOVE_MODE_UP == moveMode;
  colorTemperatureTransition.target    = 0;
  colorTemperatureTransition.byStep    = false;
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPPHYMINMIREDS == true) >  
  colorTemperatureTransition.minTemp   = MAX(tempMin, lightColorControlClusterServerAttributes.colorTempPhysicalMin.value);
</#if><#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPPHYMAXMIREDS == true) >
  colorTemperatureTransition.maxTemp   = MIN(tempMax, lightColorControlClusterServerAttributes.colorTempPhysicalMax.value);
</#if>

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_REMAININGTIME == true) >
  lightColorControlClusterServerAttributes.remainingTime.value = 0xffff;
</#if>

  return true;
}
#endif // APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT


#if APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVETOHUE == true) >
/**************************************************************************//**
\brief Callback on receive of Move To Hue command
******************************************************************************/
static ZCL_Status_t moveToHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToHueCommand_t *payload)
{
  uint8_t on, type;
  uint16_t hue;
  ZCL_Status_t status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID,
                          ZCL_CLUSTER_SIDE_SERVER, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
                          &type, &on);
  bool executeIfOff = false;
  //appSnprintf("moveToHueInd()\r\n");
  dbgLcdMsg("moveToHue");
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_MOVE_TO_HUE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
#if ZLO_CLUSTER_ENHANCEMENTS == 1
  if (!status && !on)
  {
    if (payloadLength > sizeof(ZCL_ZllMoveToHueCommand_t))
    {
      /* Check for options override */
      ZCL_ZllMoveToHueWithOptionsCommand_t *tmp = (ZCL_ZllMoveToHueWithOptionsCommand_t *)payload;

      executeIfOff = (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsMask);
      executeIfOff &= (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsOverride);
      if (!executeIfOff)
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
    else
    {
      /* Check for ExecuteIfOff bit */
      if (ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK &
          lightColorControlClusterServerAttributes.options.value)
      {
        executeIfOff = true;
      }
      else
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
  }
#endif
  gExecuteIfOff = executeIfOff;

  hue = ((MAX_HUE_LEVEL >> 8) < payload->hue) ? (MAX_HUE_LEVEL >> 8) : payload->hue;
  if (prepareMoveToHue(hue << 8, payload->direction, payload->transitionTime, false))
  {
    setColorMode(ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(HUE);
  } 

  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVEHUE == true) >
/**************************************************************************//**
\brief Callback on receive of Move Hue command
******************************************************************************/
static ZCL_Status_t moveHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveHueCommand_t *payload)
{
  uint8_t on, type;
  bool executeIfOff = false;
  ZCL_Status_t status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID,
                          ZCL_CLUSTER_SIDE_SERVER, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
                          &type, &on);
  //appSnprintf("moveHueInd()\r\n");
  dbgLcdMsg("moveHue");
  
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_MOVE_HUE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
#if ZLO_CLUSTER_ENHANCEMENTS == 1
  if (!status && !on)
  {
    if (payloadLength > sizeof(ZCL_ZllMoveHueCommand_t))
    {
      /* Check for options override */
      ZCL_ZllMoveHueWithOptionsCommand_t *tmp = (ZCL_ZllMoveHueWithOptionsCommand_t *)payload;

      executeIfOff = (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsMask);
      executeIfOff &= (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsOverride);
      if (!executeIfOff)
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_OPTIONS == true) >       
    else
    {
      /* Check for ExecuteIfOff bit */
      if (ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK &
          lightColorControlClusterServerAttributes.options.value)
      {
        executeIfOff = true;
      }
      else
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
</#if>    
  }
#endif
  gExecuteIfOff = executeIfOff;

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

  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_STEPHUE == true) >
/**************************************************************************//**
\brief Callback on receive of Step Hue command
******************************************************************************/
static ZCL_Status_t stepHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepHueCommand_t *payload)
{
  uint16_t hue;
  uint8_t on, type;
  bool executeIfOff = false;
  ZCL_Status_t status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID,
                          ZCL_CLUSTER_SIDE_SERVER, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
                          &type, &on);

  //appSnprintf("stepHueInd()\r\n");
  dbgLcdMsg("stepHue");

  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_STEP_HUE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
#if ZLO_CLUSTER_ENHANCEMENTS == 1
  if (!status && !on)
  {
    if (payloadLength > sizeof(ZCL_ZllStepHueCommand_t))
    {
      /* Check for options override */
      ZCL_ZllStepHueWithOptionsCommand_t *tmp = (ZCL_ZllStepHueWithOptionsCommand_t *)payload;

      executeIfOff = (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsMask);
      executeIfOff &= (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsOverride);
      if (!executeIfOff)
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_OPTIONS == true) >     
    else
    {
      /* Check for ExecuteIfOff bit */
      if (ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK &
          lightColorControlClusterServerAttributes.options.value)
      {
        executeIfOff = true;
      }
      else
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
</#if>    
  }
#endif
  gExecuteIfOff = executeIfOff;

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDCURRENTHUE == true) >
  hue = lightColorControlClusterServerAttributes.enhancedCurrentHue.value;

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
</#if>

  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVETOSATURATION == true) >
/**************************************************************************//**
\brief Callback on receive of Move To Saturation command
******************************************************************************/
static ZCL_Status_t moveToSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToSaturationCommand_t *payload)
{
  uint8_t on, type, saturation;
  bool executeIfOff = false;
  ZCL_Status_t status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID,
                          ZCL_CLUSTER_SIDE_SERVER, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
                          &type, &on);

  //appSnprintf("moveToSaturationInd()\r\n");
  dbgLcdMsg("moveToSat");

  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_MOVE_TO_SATURATION;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
#if ZLO_CLUSTER_ENHANCEMENTS == 1
  if (!status && !on)
  {
    if (payloadLength > sizeof(ZCL_ZllMoveToSaturationCommand_t))
    {
      /* Check for options override */
      ZCL_ZllMoveToSaturationWithOptionsCommand_t *tmp = (ZCL_ZllMoveToSaturationWithOptionsCommand_t *)payload;

      executeIfOff = (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsMask);
      executeIfOff &= (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsOverride);
      if (!executeIfOff)
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_OPTIONS == true) >    
    else
    {
      /* Check for ExecuteIfOff bit */
      if (ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK &
          lightColorControlClusterServerAttributes.options.value)
      {
        executeIfOff = true;
      }
      else
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
</#if>    
  }
#endif
  gExecuteIfOff = executeIfOff;

  saturation = (MAX_SATURATION_LEVEL < payload->saturation) ? MAX_SATURATION_LEVEL : payload->saturation;
  if (prepareMoveToSaturation(saturation, payload->transitionTime, false))
  {
    setColorMode(ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(SATURATION);
  }
  
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVESATURATION == true) >
/**************************************************************************//**
\brief Callback on receive of Move Saturation command
******************************************************************************/
static ZCL_Status_t moveSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveSaturationCommand_t *payload)
{
  uint8_t on, type;
  bool executeIfOff = false;
  ZCL_Status_t status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID,
                          ZCL_CLUSTER_SIDE_SERVER, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
                          &type, &on);

  //appSnprintf("moveSaturationInd()\r\n");
  dbgLcdMsg("moveSat");
 
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_MOVE_SATURATION;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
#if ZLO_CLUSTER_ENHANCEMENTS == 1
  if (!status && !on)
  {
    if (payloadLength > sizeof(ZCL_ZllMoveSaturationCommand_t))
    {
      /* Check for options override */
      ZCL_ZllMoveSaturationWithOptionsCommand_t *tmp = (ZCL_ZllMoveSaturationWithOptionsCommand_t *)payload;

      executeIfOff = (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsMask);
      executeIfOff &= (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsOverride);
      if (!executeIfOff)
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_OPTIONS == true) >     
    else
    {
      /* Check for ExecuteIfOff bit */
      if (ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK &
          lightColorControlClusterServerAttributes.options.value)
      {
        executeIfOff = true;
      }
      else
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
</#if>
  }
#endif  

  gExecuteIfOff = executeIfOff;

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

  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_STEPSATURATION == true) >
/**************************************************************************//**
\brief Callback on receive of Step Saturation command
******************************************************************************/
static ZCL_Status_t stepSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepSaturationCommand_t *payload)
{
  int16_t saturation;
  uint8_t on, type;
  bool executeIfOff = false;
  ZCL_Status_t status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID,
                          ZCL_CLUSTER_SIDE_SERVER, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
                          &type, &on);

  //appSnprintf("stepSaturationInd()\r\n");
  dbgLcdMsg("stepSat");
  
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_STEP_SATURATION;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
#if ZLO_CLUSTER_ENHANCEMENTS == 1
  if (!status && !on)
  {
    if (payloadLength > sizeof(ZCL_ZllStepSaturationCommand_t))
    {
      /* Check for options override */
      ZCL_ZllStepSaturationWithOptionsCommand_t *tmp = (ZCL_ZllStepSaturationWithOptionsCommand_t *)payload;

      executeIfOff = (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsMask);
      executeIfOff &= (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsOverride);
      if (!executeIfOff)
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_OPTIONS == true) >  
    else
    {
      /* Check for ExecuteIfOff bit */
      if (ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK &
          lightColorControlClusterServerAttributes.options.value)
      {
        executeIfOff = true;
      }
      else
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
</#if>    
  }
#endif
  gExecuteIfOff = executeIfOff;

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTSATURATION == true) >
  saturation = lightColorControlClusterServerAttributes.currentSaturation.value;

  if (ZCL_ZLL_STEP_SATURATION_STEP_MODE_UP == payload->stepMode)
    saturation += payload->stepSize;
  else if (ZCL_ZLL_STEP_HUE_STEP_MODE_DOWN == payload->stepMode)
    saturation -= payload->stepSize;
  else
    return ZCL_SUCCESS_STATUS;

  if (prepareMoveToSaturation(saturation, payload->transitionTime, true))
  {
    setColorMode(ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(SATURATION);
  }
</#if>

  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVETOHUESATURATION == true) >
/**************************************************************************//**
\brief Callback on receive of Move To Hue And Saturation command
******************************************************************************/
static ZCL_Status_t moveToHueAndSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToHueAndSaturationCommand_t *payload)
{
  TransitionType_t proceedWith;
  uint8_t on, type, saturation;
  uint16_t hue;
  ZCL_Status_t status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID,
                          ZCL_CLUSTER_SIDE_SERVER, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
                          &type, &on);
  bool executeIfOff = false;
  //appSnprintf("moveToHueAndSaturationInd()\r\n");
  dbgLcdMsg("moveToHueAndSat");

  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_MOVE_TO_HUE_SATURATION;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
#if ZLO_CLUSTER_ENHANCEMENTS == 1 
  if (!status && !on)
  {
    if (payloadLength > sizeof(ZCL_ZllMoveToHueAndSaturationCommand_t))
    {
      /* Check for options override */
      ZCL_ZllMoveToHueAndSaturationWithOptionsCommand_t *tmp = (ZCL_ZllMoveToHueAndSaturationWithOptionsCommand_t *)payload;

      executeIfOff = (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsMask);
      executeIfOff &= (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsOverride);
      if (!executeIfOff)
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_OPTIONS == true) >    
    else
    {
      /* Check for ExecuteIfOff bit */
      if (ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK &
          lightColorControlClusterServerAttributes.options.value)
      {
        executeIfOff = true;
      }
      else
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
</#if>    
  }
#endif
  gExecuteIfOff = executeIfOff;

  hue = ((MAX_HUE_LEVEL >> 8) < payload->hue) ? (MAX_HUE_LEVEL >> 8) : payload->hue;
  saturation = (MAX_SATURATION_LEVEL < payload->saturation) ? MAX_SATURATION_LEVEL : payload->saturation;

  proceedWith = prepareMoveToHue((uint16_t)hue << 8, ZCL_ZLL_MOVE_TO_HUE_DIRECTION_SHORTEST_DISTANCE, payload->transitionTime, false);
  proceedWith |= prepareMoveToSaturation(saturation, payload->transitionTime, false);

  if (proceedWith)
  {
    setColorMode(ZCL_ZLL_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(proceedWith);
  }
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVETOCOLOR == true) >
/**************************************************************************//**
\brief Callback on receive of Move To Color command
******************************************************************************/
static ZCL_Status_t moveToColorInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToColorCommand_t *payload)
{
  uint8_t on, type;
  uint16_t x, y;
  ZCL_Status_t status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID,
                          ZCL_CLUSTER_SIDE_SERVER, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
                          &type, &on);
  bool executeIfOff = false;
  //appSnprintf("moveToColorInd()\r\n");
  dbgLcdMsg("moveToColor");
 
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_MOVE_TO_COLOR;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
#if ZLO_CLUSTER_ENHANCEMENTS == 1
  if (!status && !on)
  {
    if (payloadLength > sizeof(ZCL_ZllMoveToColorCommand_t))
    {
      /* Check for options override */
      ZCL_ZllMoveToColorWithOptionsCommand_t *tmp = (ZCL_ZllMoveToColorWithOptionsCommand_t *)payload;

      executeIfOff = (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsMask);
      executeIfOff &= (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsOverride);
      if (!executeIfOff)
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_OPTIONS == true) >     
    else
    {
      /* Check for ExecuteIfOff bit */
      if (ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK &
          lightColorControlClusterServerAttributes.options.value)
      {
        executeIfOff = true;
      }
      else
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
</#if>
  }
#endif
  gExecuteIfOff = executeIfOff;

  x = (MAX_COLOR_LEVEL < payload->colorX) ? MAX_COLOR_LEVEL : payload->colorX;
  y = (MAX_COLOR_LEVEL < payload->colorY) ? MAX_COLOR_LEVEL : payload->colorY;

  if (prepareMoveToColor(x, y, payload->transitionTime))
  {
    setColorMode(ZCL_ZLL_CURRENT_X_AND_CURRENT_Y);
    transitionStart(COLOR);
  }

  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVECOLOR == true) >
/**************************************************************************//**
\brief Callback on receive of Move Color command
******************************************************************************/
static ZCL_Status_t moveColorInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveColorCommand_t *payload)
{
  uint8_t on, type;

  ZCL_Status_t status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID,
                          ZCL_CLUSTER_SIDE_SERVER, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
                          &type, &on);
  bool executeIfOff = false;

  //appSnprintf("moveColorInd()\r\n");
  dbgLcdMsg("moveColor");
 
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_MOVE_COLOR;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
#if ZLO_CLUSTER_ENHANCEMENTS == 1
  if (!status && !on)
  {
    if (payloadLength > sizeof(ZCL_ZllMoveColorCommand_t))
    {
      /* Check for options override */
      ZCL_ZllMoveColorWithOptionsCommand_t *tmp = (ZCL_ZllMoveColorWithOptionsCommand_t *)payload;

      executeIfOff = (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsMask);
      executeIfOff &= (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsOverride);
      if (!executeIfOff)
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_OPTIONS == true) >    
    else
    {
      /* Check for ExecuteIfOff bit */
      if (ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK &
          lightColorControlClusterServerAttributes.options.value)
      {
        executeIfOff = true;
      }
      else
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
</#if>
  }
#endif
  gExecuteIfOff = executeIfOff;

  if (prepareMoveColor(payload->rateX, payload->rateY))
  {
    setColorMode(ZCL_ZLL_CURRENT_X_AND_CURRENT_Y);
    transitionStart(COLOR);
  }

  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_STEPCOLOR == true) >
/**************************************************************************//**
\brief Callback on receive of Step Color command
******************************************************************************/
static ZCL_Status_t stepColorInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepColorCommand_t *payload)
{
  int32_t x, y;
  uint8_t on, type;
  bool executeIfOff = false;
  ZCL_Status_t status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID,
                          ZCL_CLUSTER_SIDE_SERVER, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
                          &type, &on);

  //appSnprintf("stepColorInd()\r\n");
  dbgLcdMsg("stepColor");
  
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_STEP_COLOR;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
#if ZLO_CLUSTER_ENHANCEMENTS == 1
  if (!status && !on)
  {
    if (payloadLength > sizeof(ZCL_ZllStepColorCommand_t))
    {
      /* Check for options override */
      ZCL_ZllStepColorWithOptionsCommand_t *tmp = (ZCL_ZllStepColorWithOptionsCommand_t *)payload;

      executeIfOff = (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsMask);
      executeIfOff &= (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsOverride);
      if (!executeIfOff)
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_OPTIONS == true) > 
    else
    {
      /* Check for ExecuteIfOff bit */
      if (ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK &
          lightColorControlClusterServerAttributes.options.value)
      {
        executeIfOff = true;
      }
      else
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
</#if>
  }
#endif
  gExecuteIfOff = executeIfOff;

  if (0 == payload->stepX && 0 == payload->stepY)
  {
    transitionStop(ALL);
    return ZCL_SUCCESS_STATUS;
  }

  x = (int32_t)lightColorControlClusterServerAttributes.currentX.value + payload->stepX;
  y = (int32_t)lightColorControlClusterServerAttributes.currentY.value + payload->stepY;

  if (prepareMoveToColor(x, y, payload->transitionTime))
  {
    setColorMode(ZCL_ZLL_CURRENT_X_AND_CURRENT_Y);
    transitionStart(COLOR);
  }

  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDMOVETOHUE == true) >
/**************************************************************************//**
\brief Callback on receive of Enhanced Move To Hue command
******************************************************************************/
static ZCL_Status_t enhancedMoveToHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllEnhancedMoveToHueCommand_t *payload)
{
  uint8_t on, type;
  bool executeIfOff = false;
  ZCL_Status_t status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID,
                          ZCL_CLUSTER_SIDE_SERVER, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
                          &type, &on);

  //appSnprintf("enhancedMoveToHueInd()\r\n");
  dbgLcdMsg("eMoveToHue");

  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ENHANCED_MOVE_TO_HUE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
#if ZLO_CLUSTER_ENHANCEMENTS == 1
  if (!status && !on)
  {
    if (payloadLength > sizeof(ZCL_ZllEnhancedMoveToHueCommand_t))
    {
      /* Check for options override */
      ZCL_ZllEnhancedMoveToHueWithOptionsCommand_t *tmp = (ZCL_ZllEnhancedMoveToHueWithOptionsCommand_t *)payload;

      executeIfOff = (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsMask);
      executeIfOff &= (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsOverride);
      if (!executeIfOff)
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_OPTIONS == true) >    
    else
    {
      /* Check for ExecuteIfOff bit */
      if (ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK &
          lightColorControlClusterServerAttributes.options.value)
      {
        executeIfOff = true;
      }
      else
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
</#if>
  }
#endif
  gExecuteIfOff = executeIfOff;

  // Check for direction == 1?
  setColorMode(ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION);
  if (prepareMoveToHue(payload->enhancedHue, payload->direction, payload->transitionTime, false))
  {
    transitionStart(HUE);
  }

  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDMOVEHUE == true) >
/**************************************************************************//**
\brief Callback on receive of Enhanced Move Hue command
******************************************************************************/
static ZCL_Status_t enhancedMoveHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllEnhancedMoveHueCommand_t *payload)
{
  uint8_t on, type;

  ZCL_Status_t status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID,
                          ZCL_CLUSTER_SIDE_SERVER, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
                          &type, &on);
  bool executeIfOff = false;
  //appSnprintf("enhancedMoveHueInd()\r\n");
  dbgLcdMsg("eMoveHue");

  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ENHANCED_MOVE_HUE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
#if ZLO_CLUSTER_ENHANCEMENTS == 1
  if (!status && !on)
  {
    if (payloadLength > sizeof(ZCL_ZllEnhancedMoveHueCommand_t))
    {
      /* Check for options override */
      ZCL_ZllEnhancedMoveHueWithOptionsCommand_t *tmp = (ZCL_ZllEnhancedMoveHueWithOptionsCommand_t *)payload;

      executeIfOff = (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsMask);
      executeIfOff &= (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsOverride);
      if (!executeIfOff)
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
  <#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_OPTIONS == true) > 
    else
    {
      /* Check for ExecuteIfOff bit */
      if (ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK &
          lightColorControlClusterServerAttributes.options.value)
      {
        executeIfOff = true;
      }
      else
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
  </#if>
  }
#endif
  gExecuteIfOff = executeIfOff;

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

  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDSTEPHUE == true) >
/**************************************************************************//**
\brief Callback on receive of Enhanced Step Hue command
******************************************************************************/
static ZCL_Status_t enhancedStepHueInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllEnhancedStepHueCommand_t *payload)
{
  uint16_t hue;
  uint8_t on, type;
  bool executeIfOff = false;
  ZCL_Status_t status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID,
                          ZCL_CLUSTER_SIDE_SERVER, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
                          &type, &on);

  //appSnprintf("enhancedStepHueInd()\r\n");
  dbgLcdMsg("eStepHue");
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ENHANCED_STEP_HUE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
#if ZLO_CLUSTER_ENHANCEMENTS == 1
  if (!status && !on)
  {
    if (payloadLength > sizeof(ZCL_ZllEnhancedStepHueCommand_t))
    {
      /* Check for options override */
      ZCL_ZllEnhancedStepHueWithOptionsCommand_t *tmp = (ZCL_ZllEnhancedStepHueWithOptionsCommand_t *)payload;

      executeIfOff = (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsMask);
      executeIfOff &= (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsOverride);
      if (!executeIfOff)
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_OPTIONS == true) >    
    else
    {
      /* Check for ExecuteIfOff bit */
      if (ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK &
          lightColorControlClusterServerAttributes.options.value)
      {
        executeIfOff = true;
      }
      else
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
</#if>
  }
#endif
  gExecuteIfOff = executeIfOff;
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDCURRENTHUE == true) >
  hue = lightColorControlClusterServerAttributes.enhancedCurrentHue.value;
</#if>
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

  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDMOVETOHUESATURATION == true) >
/**************************************************************************//**
\brief Callback on receive of Enhanced Move To Hue And Saturation command
******************************************************************************/
static ZCL_Status_t enhancedMoveToHueAndSaturationInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllEnhancedMoveToHueAndSaturationCommand_t *payload)
{
  TransitionType_t proceedWith;
  uint8_t on, type;
  uint16_t saturation;
  ZCL_Status_t status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID,
                          ZCL_CLUSTER_SIDE_SERVER, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
                          &type, &on);
  bool executeIfOff = false;

  //appSnprintf("enhancedMoveToHueAndSaturationInd()\r\n");
  dbgLcdMsg("eMTHAS");

  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_ENHANCED_MOVED_TO_HUE_SATURATION;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
#if ZLO_CLUSTER_ENHANCEMENTS == 1 
  if (!status && !on)
  {
    if (payloadLength > sizeof(ZCL_ZllEnhancedMoveToHueAndSaturationCommand_t))
    {
      /* Check for options override */
      ZCL_ZllEnhancedMoveToHueAndSaturationWithOptionsCommand_t *tmp = (ZCL_ZllEnhancedMoveToHueAndSaturationWithOptionsCommand_t *)payload;

      executeIfOff = (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsMask);
      executeIfOff &= (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsOverride);
      if (!executeIfOff)
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_OPTIONS == true) >     
    else
    {
      /* Check for ExecuteIfOff bit */
      if (ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK &
          lightColorControlClusterServerAttributes.options.value)
      {
        executeIfOff = true;
      }
      else
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
</#if>    
  }
#endif
  gExecuteIfOff = executeIfOff;

  saturation = (MAX_SATURATION_LEVEL < payload->saturation) ? MAX_SATURATION_LEVEL : payload->saturation;

  proceedWith = prepareMoveToHue(payload->enhancedHue, ZCL_ZLL_MOVE_TO_HUE_DIRECTION_SHORTEST_DISTANCE, payload->transitionTime, false);
  proceedWith |= prepareMoveToSaturation(saturation, payload->transitionTime, false);

  if (proceedWith)
  {
    setColorMode(ZCL_ZLL_ENHANCED_CURRENT_HUE_AND_CURRENT_SATURATION);
    transitionStart(proceedWith);
  }

  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPSET == true) >
/**************************************************************************//**
\brief Callback on receive of Color Loop Set command
******************************************************************************/
static ZCL_Status_t colorLoopSetInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllColorLoopSetCommand_t *payload)
{
  uint8_t on, type;
  bool executeIfOff = false;
  ZCL_Status_t status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID,
                          ZCL_CLUSTER_SIDE_SERVER, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
                          &type, &on);


  //appSnprintf("colorLoopSetInd()\r\n");
  dbgLcdMsg("colorLoopSet");

  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_COLOR_LOOP_SET;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
#if ZLO_CLUSTER_ENHANCEMENTS == 1
  if (!status && !on)
  {
    if (payloadLength > sizeof(ZCL_ZllColorLoopSetCommand_t))
    {
      /* Check for options override */
      ZCL_ZllColorLoopSetWithOptionsCommand_t *tmp = (ZCL_ZllColorLoopSetWithOptionsCommand_t *)payload;

      executeIfOff = (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsMask);
      executeIfOff &= (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsOverride);
      if (!executeIfOff)
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_OPTIONS == true) > 
    else
    {
      /* Check for ExecuteIfOff bit */
      if (ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK &
          lightColorControlClusterServerAttributes.options.value)
      {
        executeIfOff = true;
      }
      else
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
</#if>
  }
#endif
  gExecuteIfOff = executeIfOff;

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPDIRECTION == true) >
  if (COLOR_LOOP_UPDATE_DIRECTION & payload->updateFlags)
    lightColorControlClusterServerAttributes.colorLoopDirection.value = payload->direction;
</#if>

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPTIME == true) >
  if (COLOR_LOOP_UPDATE_TIME & payload->updateFlags)
    lightColorControlClusterServerAttributes.colorLoopTime.value = payload->time;
</#if>

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPSTARTENHANCEDHUE == true) >
  if (COLOR_LOOP_UPDATE_START_HUE & payload->updateFlags)
    lightColorControlClusterServerAttributes.colorLoopStartEnhancedHue.value = payload->startHue;
</#if>

  if (COLOR_LOOP_UPDATE_ACTION & payload->updateFlags)
  {
    switch (payload->action)
    {
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPACTIVE == true) >      
      case COLOR_LOOP_DEACTIVATE:
        if (lightColorControlClusterServerAttributes.colorLoopActive.value)
          stopColorLoop();
        break;
</#if>

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

  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_STOPMOVESTEP == true) >
/**************************************************************************//**
\brief Callback on receive of Stop Move Step command
******************************************************************************/
static ZCL_Status_t stopMoveStepInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, void *payload)
{
  uint8_t on, type;
  bool executeIfOff = false;
  ZCL_Status_t status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID,
                          ZCL_CLUSTER_SIDE_SERVER, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
                          &type, &on);
  dbgLcdMsg("stopMoveStep");
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_STOP_MOVE_STEP;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
#if ZLO_CLUSTER_ENHANCEMENTS == 1
  if (!status && !on)
  {
    if (payloadLength > 0)
    {
      /* Check for options override */
      ZCL_ZllStopMoveStepWithOptionsCommand_t *tmp = (ZCL_ZllStopMoveStepWithOptionsCommand_t *)payload;

      executeIfOff = (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsMask);
      executeIfOff &= (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsOverride);
      if (!executeIfOff)
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_OPTIONS == true) >    
    else
    {
      /* Check for ExecuteIfOff bit */
      if (ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK &
          lightColorControlClusterServerAttributes.options.value)
      {
        executeIfOff = true;
      }
      else
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
</#if>    
  }
#endif
  gExecuteIfOff = executeIfOff;

  transitionStop(ALL);
  
  return ZCL_SUCCESS_STATUS;
}
</#if>
#endif // APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_TEMPERATURE_COLOR_LIGHT

#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT
/**************************************************************************//**
\brief Attribute event (writing/reading) callback.

\param[in] addressing - incoming request addressing information.
\param[in] attributeId - attribute identifier.
\param[in] event - attribute event (read/write).
******************************************************************************/
static void ZCL_ColorControlAttributeEventInd(ZCL_Addressing_t *addressing,
  ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  APP_Zigbee_Event_t eventItem;
  eventItem.eventGroup = EVENT_CLUSTER;
  eventItem.eventId = CMD_ZCL_ATTR_COLOR_CONTROL;
  eventItem.eventData.zclAttributeData.addressing = addressing;
  eventItem.eventData.zclAttributeData.attributeId = attributeId;
  eventItem.eventData.zclAttributeData.event = event;	
  APP_Zigbee_Handler(eventItem);

#if ZLO_CLUSTER_ENHANCEMENTS == 1  
  if (((ZCL_WRITE_ATTRIBUTE_EVENT == event) && \
      ((ZCL_ZLL_CLUSTER_COLOR_TEMPERATURE_SERVER_ATTRIBUTE_ID == attributeId) || \
       (ZCL_ZLL_CLUSTER_STARTUP_COLOR_TEMPERATURE_SERVER_ATTRIBUTE_ID == attributeId))) || \
       ((ZCL_CONFIGURE_ATTRIBUTE_REPORTING_EVENT == event) && \
         ((ZCL_ZLL_CLUSTER_CURRENT_HUE_SERVER_ATTRIBUTE_ID == attributeId) || \
          (ZCL_ZLL_CLUSTER_CURRENT_SATURATION_SERVER_ATTRIBUTE_ID == attributeId) || \
          (ZCL_ZLL_CLUSTER_CURRENT_X_SERVER_ATTRIBUTE_ID == attributeId) || \
          (ZCL_ZLL_CLUSTER_CURRENT_Y_SERVER_ATTRIBUTE_ID == attributeId) || \
          (ZCL_ZLL_CLUSTER_COLOR_TEMPERATURE_SERVER_ATTRIBUTE_ID == attributeId)
         )
        )
      )
#else
	if (((ZCL_WRITE_ATTRIBUTE_EVENT == event) && \
      (ZCL_ZLL_CLUSTER_COLOR_TEMPERATURE_SERVER_ATTRIBUTE_ID == attributeId)) || \
       ((ZCL_CONFIGURE_ATTRIBUTE_REPORTING_EVENT == event) && \
         ((ZCL_ZLL_CLUSTER_CURRENT_HUE_SERVER_ATTRIBUTE_ID == attributeId) || \
          (ZCL_ZLL_CLUSTER_CURRENT_SATURATION_SERVER_ATTRIBUTE_ID == attributeId) || \
          (ZCL_ZLL_CLUSTER_CURRENT_X_SERVER_ATTRIBUTE_ID == attributeId) || \
          (ZCL_ZLL_CLUSTER_CURRENT_Y_SERVER_ATTRIBUTE_ID == attributeId) || \
          (ZCL_ZLL_CLUSTER_COLOR_TEMPERATURE_SERVER_ATTRIBUTE_ID == attributeId)
         )
        )
      )
#endif
  {
    PDS_Store(APP_LIGHT_COLOR_CONTROL_MEM_ID);
  }

}

#endif // APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_COLOR_LIGHT

#if APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVETOCOLORTEMP == true) >
/**************************************************************************//**
\brief Callback on receive of MoveToColorTemperature command
******************************************************************************/
static ZCL_Status_t moveToColorTemperatureInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveToColorTemperatureCommand_t *payload)
{
  uint16_t miredValue;
  uint8_t on, type;
  bool executeIfOff = false;
  ZCL_Status_t status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID,
                          ZCL_CLUSTER_SIDE_SERVER, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
                          &type, &on);


  //appSnprintf("moveToColorTemperatureInd()\r\n");
  dbgLcdMsg("moveToColorTemperature");

  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_MOVE_TO_COLOR_TEMPERATURE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
#if ZLO_CLUSTER_ENHANCEMENTS == 1
  if (!status && !on)
  {
    if (payloadLength > sizeof(ZCL_ZllMoveToColorTemperatureCommand_t))
    {
      /* Check for options override */
      ZCL_ZllMoveToColorTemperatureWithOptionsCommand_t *tmp = (ZCL_ZllMoveToColorTemperatureWithOptionsCommand_t *)payload;

      executeIfOff = (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsMask);
      executeIfOff &= (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsOverride);
      if (!executeIfOff)
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_OPTIONS == true) >     
    else
    {
      /* Check for ExecuteIfOff bit */
      if (ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK &
          lightColorControlClusterServerAttributes.options.value)
      {
        executeIfOff = true;
      }
      else
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
</#if>
  }
#endif
  gExecuteIfOff = executeIfOff;

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPPHYMINMIREDS == true) > 
  if (lightColorControlClusterServerAttributes.colorTempPhysicalMin.value > payload->colorTemperature)
  {
    miredValue = lightColorControlClusterServerAttributes.colorTempPhysicalMin.value;
  }
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPPHYMAXMIREDS == true) > 
  else if (lightColorControlClusterServerAttributes.colorTempPhysicalMax.value < payload->colorTemperature)
  {
    miredValue = lightColorControlClusterServerAttributes.colorTempPhysicalMax.value;
  }
</#if>  
  else
  {
    miredValue = payload->colorTemperature;
  }

  if (prepareMoveToColorTemperature(miredValue, payload->transitionTime, false))
  {
    setColorMode(ZCL_ZLL_COLOR_TEMPERATURE);
    transitionStart(TEMPERATURE);
  }

  /*clipped status also returns success status, default response check at ZCL layer */
   return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVECOLORTEMP == true) >
/**************************************************************************//**
\brief Callback on receive of MoveColorTemperature command
******************************************************************************/
static ZCL_Status_t moveColorTemperatureInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllMoveColorTemperatureCommand_t *payload)
{
  uint8_t on, type;
  bool executeIfOff = false;
  ZCL_Status_t status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID,
                          ZCL_CLUSTER_SIDE_SERVER, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
                          &type, &on);


  //appSnprintf( "moveColorTemperatureInd()\r\n");
  dbgLcdMsg("moveColorTemperature");

  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_MOVE_COLOR_TEMPERATURE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
#if ZLO_CLUSTER_ENHANCEMENTS == 1
  if (!status && !on)
  {
    if (payloadLength > sizeof(ZCL_ZllMoveColorTemperatureCommand_t))
    {
      /* Check for options override */
      ZCL_ZllMoveColorTemperatureWithOptionsCommand_t *tmp = (ZCL_ZllMoveColorTemperatureWithOptionsCommand_t *)payload;

      executeIfOff = (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsMask);
      executeIfOff &= (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsOverride);
      if (!executeIfOff)
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_OPTIONS == true) >  
    else
    {
      /* Check for ExecuteIfOff bit */
      if (ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK &
          lightColorControlClusterServerAttributes.options.value)
      {
        executeIfOff = true;
      }
      else
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
</#if>    
  }
#endif
  gExecuteIfOff = executeIfOff;

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

  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_STEPCOLORTEMP == true) >
/**************************************************************************//**
\brief Callback on receive of StepColorTemperature command
******************************************************************************/
static ZCL_Status_t stepColorTemperatureInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ZllStepColorTemperatureCommand_t *payload)
{
  uint16_t temperature;
  uint8_t on, type;
  bool executeIfOff = false;
  ZCL_Status_t status = ZCL_ReadAttributeValue(APP_ENDPOINT_LIGHT, ONOFF_CLUSTER_ID,
                          ZCL_CLUSTER_SIDE_SERVER, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
                          &type, &on);


  //appSnprintf("stepColorTemperatureInd()\r\n");
  dbgLcdMsg("stepColorTemperature");

  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_STEP_COLOR_TEMPERATURE;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = (uint8_t*)payload;
  APP_Zigbee_Handler(event);
#if ZLO_CLUSTER_ENHANCEMENTS == 1
  if (!status && !on)
  {
    if (payloadLength > sizeof(ZCL_ZllStepColorTemperatureCommand_t))
    {
      /* Check for options override */
      ZCL_ZllStepColorTemperatureWithOptionsCommand_t *tmp = (ZCL_ZllStepColorTemperatureWithOptionsCommand_t *)payload;

      executeIfOff = (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsMask);
      executeIfOff &= (bool)(ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK & tmp->optionsOverride);
      if (!executeIfOff)
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_OPTIONS == true) >     
    else
    {
      /* Check for ExecuteIfOff bit */
      if (ZCL_ZLL_OPTIONS_ATTR_EXECUTE_IF_OFF_MASK &
          lightColorControlClusterServerAttributes.options.value)
      {
        executeIfOff = true;
      }
      else
      {
        return ZCL_SUCCESS_STATUS;
      }
    }
</#if>
  }
#endif
  gExecuteIfOff = executeIfOff;

  if (0 == payload->stepSize)
  {
    transitionStop(ALL);
    return ZCL_SUCCESS_STATUS;
  }
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPMIREDS == true) >
  temperature = lightColorControlClusterServerAttributes.colorTemperature.value;

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

<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPPHYMINMIREDS == true) && (CC_COLORTEMPPHYMAXMIREDS == true) >
  if (temperature < lightColorControlClusterServerAttributes.colorTempPhysicalMin.value ||
      lightColorControlClusterServerAttributes.colorTempPhysicalMax.value < temperature)
    return ZCL_INVALID_VALUE_STATUS;
</#if>

  if (prepareMoveToColorTemperature(temperature, payload->transitionTime, true))
  {
    setColorMode(ZCL_ZLL_COLOR_TEMPERATURE);
    transitionStart(TEMPERATURE);
  }
</#if>

  return ZCL_SUCCESS_STATUS;
}
</#if>

#if ZLO_CLUSTER_ENHANCEMENTS == 1
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_STARTUPCOLORTEMPMIREDS == true) >
/**************************************************************************//**
\brief Update device ON state as per StartUpOnOff attribute value
******************************************************************************/
static void lightUpdateStartupColorTemperature(void)
{
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORMODE == true) >    
  /* if the color mode is ColorTemptertaure, startupColormireds decide the startup behaviour */
  if (ZCL_ZLL_COLOR_TEMPERATURE == lightColorControlClusterServerAttributes.colorMode.value)
  {
    if (ZCL_ZLL_STARTUP_COLOR_TEMPERATURE_PREVIOUS !=
        lightColorControlClusterServerAttributes.startUpColorTemperatureMireds.value)
    {
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPMIREDS == true) >    
      // Set the color temperature to startup value
      lightColorControlClusterServerAttributes.colorTemperature.value =
        lightColorControlClusterServerAttributes.startUpColorTemperatureMireds.value;
</#if>
    }
    /* In case of different value i.e., startUpColorTemp != 0xffff, use the value
     * restored from PDS */
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORMODE == true) >
    // Set the color mode to colorTemperature
    lightColorControlClusterServerAttributes.colorMode.value = ZCL_ZLL_COLOR_TEMPERATURE;
</#if>
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDCOLORMODE == true) > 
    // Set the enhanced color mode to colorTemperature
    lightColorControlClusterServerAttributes.enhancedColorMode.value = ZCL_ZLL_COLOR_TEMPERATURE;
</#if>

    PDS_Store(APP_LIGHT_COLOR_CONTROL_MEM_ID);
  }
}
</#if>
</#if>
#endif

/**************************************************************************//**
\brief Update the color temperature on level change if required

\param[in] deviceOn - The on/off status of the device
\param[in] updateColorTemp - Update coupleColorTemp bit overridden in optional fields
\param[in] level    - level the device is moving to
******************************************************************************/
#if ZLO_CLUSTER_ENHANCEMENTS == 1
void lightUpdateCoupledColorTemperature(bool deviceOn, bool updateColorTemp, uint8_t level)
{
  uint16_t tmpColorTempMax, tmpNewColorTemp;

  if (updateColorTemp)
  {
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORMODE == true) && (CC_ENHANCEDCOLORMODE == true) >    
    if ((ZCL_ZLL_COLOR_TEMPERATURE == lightColorControlClusterServerAttributes.colorMode.value)
        || (ZCL_ZLL_COLOR_TEMPERATURE == lightColorControlClusterServerAttributes.enhancedColorMode.value))
    {
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPMIREDS == true) >       
      switch (level)
      {        
        case ZCL_LEVEL_CONTROL_MAXIMUM_LEVEL:      
          lightColorControlClusterServerAttributes.colorTemperature.value =
            lightColorControlClusterServerAttributes.coupleColorTempToLevelMinMireds.value;
          break;

        case ZCL_LEVEL_CONTROL_MINIMUM_LEVEL:
          lightColorControlClusterServerAttributes.colorTemperature.value =
            lightColorControlClusterServerAttributes.colorTempPhysicalMax.value;
          break;

        default:
        {
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPPHYMAXMIREDS == true) && (CC_COLORTEMPPHYMINMIREDS == true) && (CC_COLORTEMPMIREDS == true)>          
          tmpColorTempMax = lightColorControlClusterServerAttributes.colorTempPhysicalMax.value -
            lightColorControlClusterServerAttributes.coupleColorTempToLevelMinMireds.value;

          tmpNewColorTemp = tmpColorTempMax - ((tmpColorTempMax / ZCL_LEVEL_CONTROL_MAXIMUM_LEVEL) * level);
          tmpNewColorTemp += lightColorControlClusterServerAttributes.coupleColorTempToLevelMinMireds.value;

          lightColorControlClusterServerAttributes.colorTemperature.value = tmpNewColorTemp;
</#if>          
        }
        break;
      } 
</#if>     
<#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPMIREDS == true) >        
#ifdef _ZCL_REPORTING_SUPPORT_
      ZCL_ReportOnChangeIfNeeded(&lightColorControlClusterServerAttributes.colorTemperature);
#endif
</#if>
      if (deviceOn)
      {
        displayStatus();
      }
    }
</#if>
    PDS_Store(APP_LIGHT_COLOR_CONTROL_MEM_ID);
  }
}

/**************************************************************************//**
  \brief Processes BC_ZCL_EVENT_ACTION_REQUEST

  \param[in] eventId - id of raised event;
  \param[in] data    - event's data
******************************************************************************/
static void lightColorControlWriteAttributeEventHandler(SYS_EventId_t eventId, SYS_EventData_t data)
{
  BcZCLActionReq_t *const actionReq = (BcZCLActionReq_t*)data;
  
  if(eventId == BC_ZCL_EVENT_ACTION_REQUEST) 
  {
    if (ZCL_ACTION_SPL_WRITE_ATTR_REQUEST == actionReq->action)
    {
      uint16_t attrVal = 0;
      ZCLActionWriteAttrReq_t* zclWriteAttrReqInfo  = (ZCLActionWriteAttrReq_t*)actionReq->context;
      memcpy(&attrVal, zclWriteAttrReqInfo->attrValue, sizeof(uint16_t));
      if((COLOR_CONTROL_CLUSTER_ID == zclWriteAttrReqInfo->clusterId) &&
              (ZCL_ZLL_CLUSTER_STARTUP_COLOR_TEMPERATURE_SERVER_ATTRIBUTE_ID == zclWriteAttrReqInfo->attrId) &&
              (ZCL_ZLL_STARTUP_COLOR_TEMPERATURE_PREVIOUS == attrVal))
          zclWriteAttrReqInfo->status = ZCL_SUCCESS_STATUS;
    }
  }
}

#endif
#endif // APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT

#elif APP_Z3_DEVICE_TYPE != APP_DEVICE_TYPE_COLOR_SCENE_CONTROLLER
  void colorControlClusterInit(void) {;}
#endif // APP_Z3_DEVICE_TYPE >= APP_DEVICE_TYPE_COLOR_LIGHT

// eof lightColorControlCluster.c
