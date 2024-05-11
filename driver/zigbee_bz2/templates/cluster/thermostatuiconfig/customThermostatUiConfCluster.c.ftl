/*******************************************************************************
  Custom Thermostat UIConf Cluster Source file

  Company:
    Microchip Technology Inc.

  File Name:
    customThermostatUiConfCluster.c

  Summary:
    This file contains Custom Thermostat UIConf Cluster Implementation.

  Description:
    This file contains Custom Thermostat UIConf Cluster Implementation.
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
#include <z3device/custom/include/customThermostatUiConfCluster.h>
#include <z3device/custom/include/customThermostatCluster.h>
#include <zcl/include/zclCommandManager.h>
#include <app_zigbee/zigbee_console/console.h>
#include <z3device/common/include/z3Device.h>
#include <app_zigbee/app_zigbee_handler.h>
/*******************************************************************************
                             Defines section
*******************************************************************************/
/*******************************************************************************
                    Static functions prototypes section
*******************************************************************************/
<#if (THERMOSTATUI_CLUSTER_CS != "CLIENT")>
static void ZCL_ThermostatUiConfAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
</#if>

/******************************************************************************
                    Global variables
******************************************************************************/
<#if (THERMOSTATUI_CLUSTER_CS != "CLIENT")>
ZCL_ThermostatUiConfClusterServerAttributes_t customThermostatUiConfClusterServerAttributes =
{
  ZCL_DEFINE_THERMOSTAT_UI_CONF_CLUSTER_SERVER_ATTRIBUTES()
};
</#if>

<#if (THERMOSTATUI_CLUSTER_CS != "SERVER")>
ZCL_ThermostatUiConfClusterClientAttributes_t customThermostatUiConfClusterClientAttributes =
{  
  ZCL_DEFINE_THERMOSTAT_UI_CONF_CLUSTER_CLIENT_ATTRIBUTES()
};
</#if>

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes thermostat ui conf cluster
******************************************************************************/
void customThermostatUiConfClusterInit(void)
{
<#if (THERMOSTATUI_CLUSTER_CS != "CLIENT")>
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, THERMOSTAT_UI_CONF_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
  if (cluster)
  {
    cluster->ZCL_AttributeEventInd = ZCL_ThermostatUiConfAttributeEventInd;
	cluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
  }
</#if>
<#if (THERMOSTATUI_CLUSTER_CS != "SERVER")>
  ZCL_Cluster_t *clusterclient = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, THERMOSTAT_UI_CONF_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);

  if (clusterclient)
  {
	clusterclient->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
  }
</#if>

<#if (THERMOSTATUI_CLUSTER_CS != "CLIENT")>
<#if (THERMOSTATUI_CLUSTER_CS != "CLIENT")  && (TUIC_TEMPDISPLAYMODE == true)>
  customThermostatUiConfClusterServerAttributes.temperatureDisplayMode.value = ZCL_TEMPERATURE_IN_CELSIUS;
</#if>
<#if (THERMOSTATUI_CLUSTER_CS != "CLIENT")  && (TUIC_KEYPADLOCKOUT == true)>  
  customThermostatUiConfClusterServerAttributes.keypadLockOut.value = ZCL_NO_LOCKOUT;
</#if>
<#if (THERMOSTATUI_CLUSTER_CS != "CLIENT")  && (TUIC_SCHEDULEPROGRAMVISIBILITY == true)>  
  customThermostatUiConfClusterServerAttributes.scheduleProgVisibility.value = ZCL_ENABLE_LOCAL_SCHEDULE_PROGRAMMING;
</#if>
<#if (THERMOSTATUI_CLUSTER_CS != "CLIENT")  && (TUIC_CLUSTERREVISION == true)>  
  customThermostatUiConfClusterServerAttributes.clusterVersion.value = THERMOSTAT_UI_CONF_CLUSTER_VERSION;
</#if>  

<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_LOCALTEMP == true)>
  // Enable LCD and Display local Temparature on it
  LCD_PRINT(0,3,"Temp = %d deg C",customThermostatClusterServerAttributes.localTemperature.value);
</#if>
</#if>
<#if (THERMOSTATUI_CLUSTER_CS != "SERVER")  && (TUICC_CLUSTERREVISION == true)>   
  customThermostatUiConfClusterClientAttributes.clusterVersion.value = THERMOSTAT_UI_CONF_CLUSTER_VERSION;
</#if>

}

<#if (THERMOSTATUI_CLUSTER_CS != "CLIENT")>
static void ZCL_ThermostatUiConfAttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
  APP_Zigbee_Event_t eventItem;
  eventItem.eventGroup = EVENT_CLUSTER;
  eventItem.eventId = CMD_ZCL_ATTR_THERMOSTAT_UI_CONF;
  eventItem.eventData.zclAttributeData.addressing = addressing;
  eventItem.eventData.zclAttributeData.attributeId = attributeId;
  eventItem.eventData.zclAttributeData.event = event;
  APP_Zigbee_Handler(eventItem);
}

<#if (THERMOSTATUI_CLUSTER_CS != "CLIENT")  && (TUIC_TEMPDISPLAYMODE == true) && (TC_LOCALTEMP == true)>
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
</#if>
</#if>

#endif // APP_DEVICE_TYPE_CUSTOM_DEVICE
// eof customThermostatUiConfCluster.c
