/*******************************************************************************
  Fake board-specific Source File

  Company:
    Microchip Technology Inc.

  File Name:
    fakeBSP.c

  Summary:
    This file contains Implementation of fake board-specific periphery.

  Description:
    This file contains Implementation of fake board-specific periphery.
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

/******************************************************************************
                   Includes section
******************************************************************************/
#include <systemenvironment/include/sysTypes.h>
#include <app_zigbee/app_zigbee_handler.h>
/******************************************************************************
                   Local variables section
******************************************************************************/
static void(* readTemperatureDataCallback)(bool error, int16_t data);
static void(* readLightDataCallback)(bool error, int16_t data);
static void(* readBatteryDataCallback)(int16_t data);

<#if SLEEP_SUPPORTED_DEVICE && RESET_TO_FN_ENABLE>
static bool userButtonState = false;
static App_ButtonPressCallback_t userButtonShortPressCallback;
static uint32_t __attribute__((persistent)) rtcValueDuringButtonPress;

#define USER_BUTTON_MASK    		(1<<4U)
#define BUTTON_RESET_PERIOD         3000U
<#if DEVICE_DEEP_SLEEP_ENABLED>
#define INT0_WAKEUP                 1U
#define EXTINT0						7U
</#if>
</#if>

/******************************************************************************
                   Implementations section
******************************************************************************/
#if BSP_SUPPORT == BOARD_PIC32CX

<#if SLEEP_SUPPORTED_DEVICE && RESET_TO_FN_ENABLE>
/**************************************************************************//**
\brief Read User Button State.

\return
    None
\param[in]
    None
******************************************************************************/
static void ReadUserButton(void)
{
    uint32_t portBValue = GPIO_PortRead(GPIO_PORT_B);
    
    if((portBValue & USER_BUTTON_MASK) == 0) 
    {
        userButtonState = true;
    }
    else 
    {
        userButtonState = false;
    }
}

</#if>
/******************************************************************************
 Returns number which was read from external eeprom.
 Parameters:
   id - UID buffer pointer.
 Returns:
   0 - if unique ID has been found without error;
  -1 - if there are some erros during UID discovery.
******************************************************************************/
int BSP_ReadUid(uint64_t *id)
{
  (void)id;
  return 0;
}

/******************************************************************************
                             Leds
******************************************************************************/
/**************************************************************************//**
\brief Turns on the LED.

\param[in]
    id - number of led
******************************************************************************/
void BSP_OnLed(void)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_BSP;
  event.eventId = CMD_LED_ON;
  //event.eventData = NULL;
  memset(&event.eventData, 0, sizeof(APP_Zigbee_EventData));
  APP_Zigbee_Handler(event);
}

/**************************************************************************//**
\brief Turns off the LED.

\param[in]
      id - number of led
******************************************************************************/
void BSP_OffLed(void)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_BSP;
  event.eventId = CMD_LED_OFF;
  //event.eventData = 0;
  memset(&event.eventData, 0, sizeof(APP_Zigbee_EventData));
  APP_Zigbee_Handler(event);
}

/**************************************************************************//**
\brief Changes the LED state to opposite.

\param[in]
      id - number of led
******************************************************************************/
void BSP_ToggleLed(void)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_BSP;
  event.eventId = CMD_LED_TOGGLE;
  //event.eventData = 0;
  memset(&event.eventData, 0, sizeof(APP_Zigbee_EventData));
  APP_Zigbee_Handler(event);
}

/**************************************************************************//**
\brief Initialize LEDs.
******************************************************************************/
void BSP_LedsOpen(void)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_BSP;
  event.eventId = CMD_LED_OPEN;
  memset(&event.eventData, 0, sizeof(APP_Zigbee_EventData));
  APP_Zigbee_Handler(event);
}

/**************************************************************************//**
\brief Set brightness level
\param[in] level - new brightness level
******************************************************************************/
void BSP_SetLedBrightnessLevel(uint8_t level)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_BSP;
  event.eventId = CMD_LED_BRIGHTNESS;
  event.eventData.value = level;
  APP_Zigbee_Handler(event);
}

/**************************************************************************//**
\brief Set the color using Hue and Saturation as parameters
\param[in] level - a new brightness level
******************************************************************************/
void BSP_SetLedColorHS(uint16_t hue, uint8_t saturation)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_BSP;
  event.eventId = CMD_LED_COLOR_HS;
  event.eventData.colorHS.hue = hue;
  event.eventData.colorHS.saturation = saturation;
  APP_Zigbee_Handler(event);
}

/**************************************************************************//**
\brief Set the color using X and Y as parameters
\param[in] level - a new brightness level
******************************************************************************/
void BSP_SetLedColorXY(uint16_t x, uint16_t y)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_BSP;
  event.eventId = CMD_LED_COLOR_XY;
  event.eventData.colorXY.x = x;
  event.eventData.colorXY.y = y;
  APP_Zigbee_Handler(event);
}

/******************************************************************************
                             Buttons
******************************************************************************/
/**************************************************************************//**
\brief Reads state of buttons.

\param[in]
    bool state of the device
\return
    None
******************************************************************************/
void BSP_ReadButtonsState(bool buttonRead)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_BSP;
  event.eventId = CMD_BUTTON_READ;
  memset(&event.eventData, 0, sizeof(APP_Zigbee_EventData));
  APP_Zigbee_Handler(event);
  buttonRead = event.eventData.state;
}

/**************************************************************************//**
\brief Init/ Open button.

\return
    None
\param[in]
    None
******************************************************************************/
void BSP_ButtonOpen()
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_BSP;
  event.eventId = CMD_BUTTON_OPEN;
  memset(&event.eventData, 0, sizeof(APP_Zigbee_EventData));
  APP_Zigbee_Handler(event);    
}
/**************************************************************************//**
\brief Initilise/ Open Temp Sensor.

\return
    None
\param[in]
    None
******************************************************************************/
void BSP_TempSensorOpen()
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_BSP;
  event.eventId = CMD_SENSOR_OPEN;
  memset(&event.eventData, 0, sizeof(APP_Zigbee_EventData));
  APP_Zigbee_Handler(event);    
}

/**************************************************************************//**
\brief Read Temperature Sensor.

\param[in]
    measuredValue
\return
    None
******************************************************************************/
void BSP_ReadTempSensor(uint16_t *measuredValue)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_BSP;
  event.eventId = CMD_SENSOR_READ;
  memset(&event.eventData, 0, sizeof(APP_Zigbee_EventData));
  APP_Zigbee_Handler(event);    
  *measuredValue = event.eventData.data;
}

<#if SLEEP_SUPPORTED_DEVICE && RESET_TO_FN_ENABLE>
/**************************************************************************//**
\brief Initialize the user button.

\return
    None
\param[in]
    buttonPressCallback - callback function when user button short pressed.
******************************************************************************/
void BSP_InitializeUserButton(App_ButtonPressCallback_t buttonPressCallback)
{
    /* Configure PB4 pin as input. */
	((gpio_registers_t*)GPIO_PORT_B)->GPIO_TRISSET |= (USER_BUTTON_MASK);
    
    /* Disable the configuration lock. */
    CFG_REGS->CFG_CFGCON0 &= ~(CFG_CFGCON0_IOLOCK_Msk);
    /* Enable the External interrupt 0. */
    PPS_REGS->PPS_EXTINT0R = 5U;
	
	userButtonShortPressCallback = buttonPressCallback;
}

/**************************************************************************//**
\brief Return the User Button State.

\return
    True - if the button is pressed.
	False - if the button is released.
\param[in]
    None
******************************************************************************/
bool BSP_IsUserButtonPressed(void)
{
    return userButtonState;
}

<#if DEVICE_DEEP_SLEEP_ENABLED>
/**************************************************************************//**
\brief Evaluate wether the user button is long pressed.

\return
    None
\param[in]
    Deep sleep wakeup source.
******************************************************************************/
void BSP_EvaluateUserButton(uint8_t deepSleepWakeupSrc)
<#else>
/**************************************************************************//**
\brief Evaluate wether the user button is long pressed.

\return
    None
\param[in]
    None
******************************************************************************/
void BSP_EvaluateUserButton(void)
</#if>
{   
    ReadUserButton();
    
	<#if DEVICE_DEEP_SLEEP_ENABLED>
    if((deepSleepWakeupSrc == INT0_WAKEUP) || (deepSleepWakeupSrc == EXTINT0))
	</#if>
    {
        if(BSP_IsUserButtonPressed())
        {
            rtcValueDuringButtonPress = RTC_Timer32CounterGet();
        } 
        else 
        {
            uint32_t rtcDifference = SYS_calculateDifference(rtcValueDuringButtonPress, RTC_Timer32CounterGet());
            rtcDifference = rtcDifference * configTICK_RATE_HZ;
            uint32_t completedTickPeriod = rtcDifference / RTC_Timer32FrequencyGet();
            
            if(completedTickPeriod >= BUTTON_RESET_PERIOD) 
            {
				APP_Zigbee_Event_t event;
                event.eventGroup = EVENT_BSP;
                event.eventId = CMD_BUTTON_LONG_PRESS;
                memset(&event.eventData, 0, sizeof(APP_Zigbee_EventData));
                APP_Zigbee_Handler(event);
            }
			else
			{
				userButtonShortPressCallback();
			}
        }
    } 
}
</#if>

#endif
// eof fakeBSP.c
