/*******************************************************************************
  Custom Thermostat Ui Conf Cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    customThermostatUiConfCluster.c

  Summary:
    This file contains the Custom Thermostat Ui Conf Cluster implementation.

  Description:
    This file contains the Custom Thermostat Ui Conf Cluster implementation.
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
#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_CUSTOM_DEVICE)
/******************************************************************************
                    Includes section
******************************************************************************/
#include <custom/include/customThermostatUiConfCluster.h>
#include <custom/include/customThermostatCluster.h>
#include <zclCommandManager.h>
#include <console.h>
#include <z3device.h>

/*******************************************************************************
                             Defines section
*******************************************************************************/
/*******************************************************************************
                    Static functions prototypes section
*******************************************************************************/
static void ZCL_ThermostatUiConfAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
static void customThermostatUiConfUpdateKeypadLock(uint8_t value);
static void customThermostatUiConfUpdateScheduleProgrammingVisibility(uint8_t value);

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_ThermostatUiConfClusterServerAttributes_t customThermostatUiConfClusterServerAttributes =
{
  ZCL_DEFINE_THERMOSTAT_UI_CONF_CLUSTER_SERVER_ATTRIBUTES()
};

ZCL_ThermostatUiConfClusterClientAttributes_t customThermostatUiConfClusterClientAttributes =
{  
  ZCL_DEFINE_THERMOSTAT_UI_CONF_CLUSTER_CLIENT_ATTRIBUTES()
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes thermostat ui conf cluster
******************************************************************************/
void customThermostatUiConfClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, THERMOSTAT_UI_CONF_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
  ZCL_Cluster_t *clusterclient = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, THERMOSTAT_UI_CONF_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);

  if (cluster)
    cluster->ZCL_AttributeEventInd = ZCL_ThermostatUiConfAttributeEventInd;

  customThermostatUiConfClusterServerAttributes.temperatureDisplayMode.value = ZCL_TEMPERATURE_IN_CELSIUS;
  customThermostatUiConfClusterServerAttributes.keypadLockOut.value = ZCL_NO_LOCKOUT;
  customThermostatUiConfClusterServerAttributes.scheduleProgVisibility.value = ZCL_ENABLE_LOCAL_SCHEDULE_PROGRAMMING;
  customThermostatUiConfClusterServerAttributes.clusterVersion.value = CLUSTER_VERSION;

  // Enable LCD and Display local Temparature on it
  LCD_PRINT(0,3,"Temp = %d deg C",customThermostatClusterServerAttributes.localTemperature.value);

  customThermostatUiConfClusterClientAttributes.clusterVersion.value = CLUSTER_VERSION;
  clusterclient->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
}

static void ZCL_ThermostatUiConfAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  if (ZCL_WRITE_ATTRIBUTE_EVENT == event)
  {
    switch(attributeId)
    {
      case ZCL_THERMOSTAT_UI_CONF_CLUSTER_TEMPERATURE_DISPLAY_MODE_SERVER_ATTRIBUTE_ID:
      {
        if(customThermostatUiConfClusterServerAttributes.temperatureDisplayMode.value == ZCL_TEMPERATURE_IN_CELSIUS)
        {          
          LCD_PRINT(0, 3,"Temp in Celcius = %d ",(customThermostatClusterServerAttributes.localTemperature.value/100));
          appSnprintf(" Temp in Celcius = %d\r\n",customThermostatClusterServerAttributes.localTemperature.value);           
        }
        else
        {
          LCD_PRINT(0,3,"Temp in Fahr = %d    ",customTranslateZclCelciusTemptoFahr(customThermostatClusterServerAttributes.localTemperature.value));
          appSnprintf(" Temp in Fahr = %d\r\n",customTranslateZclCelciusTemptoFahr(customThermostatClusterServerAttributes.localTemperature.value));
        }
      }
      break;
      case ZCL_THERMOSTAT_UI_CONF_CLUSTER_KEYPAD_LOCKOUT_SERVER_ATTRIBUTE_ID:
      {
        appSnprintf(" Keypad Lock Attribute = %d\r\n",customThermostatUiConfClusterServerAttributes.keypadLockOut.value);
        customThermostatUiConfUpdateKeypadLock(customThermostatUiConfClusterServerAttributes.keypadLockOut.value);
      }
      break;
      case ZCL_THERMOSTAT_UI_CONF_CLUSTER_SCHEDULE_PROGRAMMING_VISIBILITY_SERVER_ATTRIBUTE_ID:
      {
        appSnprintf(" Schedule Programming Visibility Attribute = %d\r\n",customThermostatUiConfClusterServerAttributes.scheduleProgVisibility.value);
        customThermostatUiConfUpdateScheduleProgrammingVisibility(customThermostatUiConfClusterServerAttributes.scheduleProgVisibility.value);
      }
      break;
      default:
        break;
    }
  }
}

static void customThermostatUiConfUpdateKeypadLock(uint8_t value)
{
  
}

static void customThermostatUiConfUpdateScheduleProgrammingVisibility(uint8_t value)
{
  
}

/**************************************************************************//** 
* Function : translateZclTemp() 
* Description : Converts the temperature setpoints in ZCLto the half degF format. 
* The half degF format is 8-bit unsigned, and represents 2x temperature value in 
* Farenheit (to get 0.5 resolution).The format used in ZCL is 16-bit signed 
* in Celsius and multiplied by 100S to get 0.01 resolution. 
* e.g. 2500(25.00 deg C) ---> 0x9A (77 deg F) 
* Input Para : Temperature in ZCL (degC)format 
* Output Para: Temperature in half DegF format 
******************************************************************************/
int8_t customTranslateZclCelciusTemptoFahr(int16_t temperature) 
{ 
int32_t x = temperature; 
//rearrangement of 
// = (x * (9/5) / 100 + 32); 
// the added 250 is for proper rounding. 
// a rounding technique that only works 
// with positive numbers 

return (int8_t) ((x*9 + 250)/ (5*100) + 32); 
} 

#endif // APP_DEVICE_TYPE_CUSTOM_DEVICE
// eof customThermostatUiConfCluster.c
