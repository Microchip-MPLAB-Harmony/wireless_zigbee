/*******************************************************************************
  Application Zigbee Handler Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_zigbee_handler.c

  Summary:
    This file contains the Application Zigbee functions for this project.

  Description:
    This file contains the Application Zigbee functions for this project.
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <app_zigbee/app_zigbee_handler.h>
#include <app_zigbee/zigbee_console/console.h>
<#if (ALARMS_CLUSTER_ENABLE == true)>
#include <zcl/include/zclAlarmsCluster.h>
</#if>
<#if (IDENTIFY_CLUSTER_ENABLE == true)>
#include <zcl/include/zclZllIdentifyCluster.h>
</#if>
<#if (GROUPS_CLUSTER_ENABLE == true)>
#include <zcl/include/zclZllGroupsCluster.h>
</#if>
<#if (ONOFF_CLUSTER_ENABLE == true)>
#include <zcl/include/zclZllOnOffCluster.h>
</#if>
<#if (LEVELCONTROL_CLUSTER_ENABLE == true)>
#include <zcl/include/zclZllLevelControlCluster.h>
</#if>
<#if (COLORCONTROL_CLUSTER_ENABLE == true)>
#include <zcl/include/zclZllColorControlCluster.h>
</#if>
<#if (SCENES_CLUSTER_ENABLE == true)>
#include <zcl/include/zclZllScenesCluster.h>
</#if>
<#if (IASACE_CLUSTER_ENABLE == true)>
#include <zcl/include/zclIasACECluster.h>
</#if>
<#if (IASZONE_CLUSTER_ENABLE == true)>
#include <zcl/include/zclIasZoneCluster.h>
</#if>
<#if (FANCONTROL_CLUSTER_ENABLE == true)>
#include <zcl/include/zclFanControlCluster.h>
</#if>
<#if (THERMOSTAT_CLUSTER_ENABLE == true)>
#include <zcl/include/zclThermostatCluster.h>
</#if>
<#if (TEMPERATUREMEASUREMENT_CLUSTER_ENABLE == true)>
#include <zcl/include/zclTemperatureMeasurementCluster.h>
</#if>
<#if (TIME_CLUSTER_ENABLE == true)>
#include <zcl/include/zclTimeCluster.h>
</#if>
<#if (THERMOSTATUI_CLUSTER_ENABLE == true)>
#include <zcl/include/zclThermostatUiConfCluster.h>
</#if>
<#if ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE == true>
#include <zcl/include/zclIlluminanceMeasurementCluster.h>
</#if>
<#if OCCUPANCYSENSING_CLUSTER_ENABLE == true>
#include <zcl/include/zcloccupancysensingcluster.h>
</#if>
<#if (ZB_DEVICE_TYPE == "ZIGBEE_MULTI_SENSOR")>
<#if ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE == true>
#include <z3device/multiSensor/include/lsIlluminanceMeasurementCluster.h>
</#if>
<#if OCCUPANCYSENSING_CLUSTER_ENABLE == true>
#include <z3device/multiSensor/include/osOccupancySensingCluster.h>
</#if>
<#if (TEMPERATUREMEASUREMENT_CLUSTER_ENABLE == true)>
#include <z3device/multiSensor/include/tsTemperatureMeasurementCluster.h>
</#if>
<#if WATERCONTENTMEASUREMENT_CLUSTER_ENABLE == true>
#include <z3device/multiSensor/include/hsHumidityMeasurementCluster.h>
</#if>
</#if>
<#if (ZB_DEVICE_TYPE == "ZIGBEE_CUSTOM")>
<#if (ONOFF_CLUSTER_ENABLE == true)>
#include <z3device/custom/include/customOnOffCluster.h>
</#if>
<#if OCCUPANCYSENSING_CLUSTER_ENABLE == true>
#include <z3device/custom/include/customOccupancySensingCluster.h>
</#if>
<#if ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE == true>
#include <z3device/custom/include/customIlluminanceMeasurementCluster.h>
</#if>
<#if (LEVELCONTROL_CLUSTER_ENABLE == true)>
#include <z3device/custom/include/customLevelControlCluster.h>
</#if>
<#if (COLORCONTROL_CLUSTER_ENABLE == true)>
#include <z3device/custom/include/customColorControlCluster.h>
</#if>
<#if (THERMOSTAT_CLUSTER_ENABLE == true)>
#include <z3device/custom/include/customThermostatCluster.h>
</#if>
<#if TEMPERATUREMEASUREMENT_CLUSTER_ENABLE == true>
#include <z3device/custom/include/customTemperatureMeasurementCluster.h>
</#if>
<#if THERMOSTATUI_CLUSTER_ENABLE == true>
#include <z3device/custom/include/customThermostatUiConfCluster.h>
</#if>
<#if (ALARMS_CLUSTER_ENABLE == true)>
#include <z3device/custom/include/customAlarmsCluster.h>
</#if>
</#if>
<#if (ZB_DEVICE_TYPE == "ZIGBEE_THERMOSTAT")>
<#if OCCUPANCYSENSING_CLUSTER_ENABLE == true>
#include <z3device/thermostat/include/thOccupancySensingCluster.h>
</#if>
<#if (THERMOSTAT_CLUSTER_ENABLE == true)>
#include <z3device/thermostat/include/thThermostatCluster.h>
</#if>
<#if TEMPERATUREMEASUREMENT_CLUSTER_ENABLE == true>
#include <z3device/thermostat/include/thTemperatureMeasurementCluster.h>
</#if>
<#if THERMOSTATUI_CLUSTER_ENABLE == true>
#include <z3device/thermostat/include/thThermostatUiConfCluster.h>
</#if>
<#if WATERCONTENTMEASUREMENT_CLUSTER_ENABLE == true>
#include <z3device/thermostat/include/thHumidityMeasurementCluster.h>
</#if>
<#if (ALARMS_CLUSTER_ENABLE == true)>
#include <z3device/thermostat/include/thAlarmsCluster.h>
</#if>
</#if>
<#if (ZB_DEVICE_TYPE == "ZIGBEE_ON_OFF_LIGHT") || (ZB_DEVICE_TYPE == "ZIGBEE_DIMMABLE_LIGHT") || (ZB_DEVICE_TYPE == "ZIGBEE_COLOR_LIGHT") || (ZB_DEVICE_TYPE == "ZIGBEE_EXTENDED_COLOR_LIGHT") || (ZB_DEVICE_TYPE == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")>
<#if (ONOFF_CLUSTER_ENABLE == true)>
#include <z3device/light/include/lightOnOffCluster.h>
</#if>
<#if (LEVELCONTROL_CLUSTER_ENABLE == true)>
#include <z3device/light/include/lightLevelControlCluster.h>
</#if>
<#if (COLORCONTROL_CLUSTER_ENABLE == true)>
#include <z3device/light/include/lightColorControlCluster.h>
</#if>
</#if>
<#if (ZB_DEVICE_TYPE == "ZIGBEE_COMBINED_INTERFACE")>
<#if (THERMOSTAT_CLUSTER_ENABLE == true)>
#include <z3device/combinedInterface/include/ciThermostatCluster.h>
</#if>
</#if>
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

void BSP_Event_Handler(APP_Zigbee_Event_t event);
void Cluster_Event_Handler(APP_Zigbee_Event_t event);
void Zigbee_Event_Handler(APP_Zigbee_Event_t event);

#define MIN_COLOR_LEVEL           0
#define MAX_COLOR_LEVEL           0xfeff

#define MIN_SATURATION_LEVEL      0
#define MAX_SATURATION_LEVEL      0xfe
// *****************************************************************************
// *****************************************************************************
// Section: Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Zigbee_Handler(APP_Zigbee_Event_t event)

  Remarks:
    See prototype in app_zigbee_handler.h.
******************************************************************************/

void APP_Zigbee_Handler(APP_Zigbee_Event_t event)
{
    switch(event.eventGroup)
    {
        case EVENT_BSP:
        {
            /* BSP Events Dispatcher */
            BSP_Event_Handler(event);
        }
        break;

        case EVENT_ZIGBEE:
        {
            /* Zigbee Events Dispatcher */
            Zigbee_Event_Handler(event);
        }
        break;

        case EVENT_CLUSTER:
        {
            /* Cluster Events Dispatcher */
            Cluster_Event_Handler(event);
        }
        break;

        default:
        break;
    }
}

/*******************************************************************************
  Function:
    void BSP_Event_Handler(APP_Zigbee_Event_t event)

  Remarks:
    See prototype in app_zigbee_handler.h.
******************************************************************************/

void BSP_Event_Handler(APP_Zigbee_Event_t event)
{
    // User to handle  board Support package events
    switch(event.eventId)
    {
        case CMD_LED_OPEN:
        {
            /* Init/Open LEDs */
            //appSnprintf("Init /Open LEDs\r\n");
        }
        break;

        case CMD_LED_ON:
        {
            /* Turn on the LED */
            //Access - > event.eventData.value;
            //appSnprintf("On\r\n");
        }
        break;

        case CMD_LED_OFF:
        {
            /* Turn off the LED */
            //Access - > event.eventData.value;
            //appSnprintf("Off\r\n");
        }
        break;

        case CMD_LED_TOGGLE:
        {
            /* Toggle the LED */
            //Access - > event.eventData.value;
            //appSnprintf("Toggle\r\n");
        }
        break;
        case CMD_LED_BRIGHTNESS:
        {
            /* Set the given LED brightness */
            //Access - > event.eventData.value;
            //appSnprintf("Led Brightness \r\n");
        }
        break;

        case CMD_LED_COLOR_HS:
        {
            /* LED Hue , Saturation */
            //Access - > event.eventData.colorHS.hue;
            //Access - > event.eventData.colorHS.saturation;
            //appSnprintf("LED Hue , Saturation \r\n");
        }
        break;

        case CMD_LED_COLOR_XY:
        {
            /* Set the LED Color X Y */
            //Access - > event.eventData.colorXY.x;
            //Access - > event.eventData.colorXY.y;
            //appSnprintf("LED X,Y Color \r\n");
        }
        break;

        case CMD_BUTTON_OPEN:
        {
            /* Button Init */
            //appSnprintf("Button Init/Open \r\n");
        }
        break;

        case CMD_BUTTON_READ:
        {
            /* Button Press */
            //Access - > event.eventData.state;
            //appSnprintf("Button Read \r\n");
        }
        break;

        case CMD_SENSOR_OPEN:
        {
            /* Sensor Data */
            //appSnprintf("Sensor Open /Init Event \r\n");
        }        
        break;

        case CMD_SENSOR_READ:
        {
            /* Sensor Data */
            //Access - > event.eventData.data;
            //appSnprintf("Sensor Read Event \r\n");
        }        
        break;

        default:
        break;
    }
}

/*******************************************************************************
  Function:
    void Zigbee_Event_Handler(APP_Zigbee_Event_t event)

  Remarks:
    See prototype in app_zigbee_handler.h.
******************************************************************************/

void Zigbee_Event_Handler(APP_Zigbee_Event_t event)
{
    // User to handle all zigbee stack events  
    switch(event.eventId)
    {
        case EVENT_NETWORK_ESTABLISHED:
        {
<#if (AUTOMATIC_COMMISSIONING_ON_STARTUP == true) >
            appSnprintf("Network Established\r\n");
<#else>
            //appSnprintf("Network Established\r\n");
</#if>
        }
        break;
        case EVENT_DISCONNECTED:
        {
<#if (AUTOMATIC_COMMISSIONING_ON_STARTUP == true) >
            appSnprintf("Disconnected from the Network\r\n");
<#else>
            //appSnprintf("Disconnected from the Network\r\n");
</#if>
        }
        break;
<#if (AUTOMATIC_COMMISSIONING_ON_STARTUP == true) >
        case EVENT_COMMISSIONING_STARTED:
        {
            appSnprintf("Commissioning Procedure Started - 180 Seconds \r\n");
            appSnprintf("Commissioning Sequence: ");
<#if TOUCHLINK == true>
            appSnprintf("Touchlink->");
</#if>
<#if NETWORK_FORMATION == true>
            appSnprintf("Formation->");
</#if>
<#if NETWORK_STEERING == true>
            appSnprintf("Steering->");
</#if>
<#if FINDING_AND_BINDING == true>
            appSnprintf("Find & Bind->");
</#if>
            appSnprintf("\r\n");
        }
        break;

        case EVENT_COMMISSIONING_COMPLETE:
        {
            appSnprintf("Commissioning Procedure Complete \r\n");
        }
        break;
        case EVENT_COMMISSIONING_FORMATION_COMPLETE:
        {
            appSnprintf("Nwk Formation: ");
            if(event.eventData.value == BDB_COMMISSIONING_SUCCESS)
                appSnprintf("Success\r\n");
            else //BDB_COMMISSIONING_FORMATION_FAILURE
                appSnprintf("Failed\r\n");
        }
        break;
        case EVENT_COMMISSIONING_STEERING_COMPLETE:
        {
            appSnprintf("Steering: ");
            if(event.eventData.value == BDB_COMMISSIONING_NO_NETWORK)
                appSnprintf("No networks found to join\r\n");
            else if(event.eventData.value == BDB_COMMISSIONING_SUCCESS)
                appSnprintf("Success\r\n");
            else
                appSnprintf("Failed\r\n");
        }
        break;
        case EVENT_COMMISSIONING_TOUCHLINK_COMPLETE:
        {
            appSnprintf("Touchlink: Attempt: ");
            if(event.eventData.value == BDB_COMMISSIONING_NO_SCAN_RESPONSE)
                appSnprintf("No scan response\r\n");
            else if(event.eventData.value == BDB_COMMISSIONING_SUCCESS)
                appSnprintf("Success\r\n");
            else
                appSnprintf("Failed\r\n");
        }
        break;
        case EVENT_COMMISSIONING_FINDBIND_COMPLETE:
        {
            appSnprintf("Finding & Binding: ");
            if(event.eventData.value == BDB_COMMISSIONING_NO_IDENTIFY_QUERY_RESPONSE)
              appSnprintf("No identify Query Response\r\n");
            else if(event.eventData.value == BDB_COMMISSIONING_BINDING_TABLE_FULL)
              appSnprintf("Binding table full\r\n");
            else if(event.eventData.value == BDB_COMMISSIONING_SUCCESS)
              appSnprintf("Success\r\n");
            else
              appSnprintf("Failed\r\n");
        }
        break;
        case EVENT_COMMISSIONING_FAILURE:
        {
          switch(event.eventData.value)
          {
              case BDB_COMMISSIONING_NO_NETWORK:
              {
                  //appSnprintf("No network found in search\r\n");
              }
              break;
              case BDB_COMMISSIONING_NOT_SUPPORTED:
              {
                  appSnprintf("Commissioning: One of the BDB commissioning procedure not supported\r\n");
              }
              break;
              case BDB_COMMISSIONING_NO_SCAN_RESPONSE:
              break;
              case BDB_COMMISSIONING_NO_IDENTIFY_QUERY_RESPONSE:
              break;
              default:
              break;
          }
        }
        break;

        case EVENT_STARTED_CENTRALIZED_NETWORK:
        {
            appSnprintf("Started Centralized Network\r\n");
        }
        break;
</#if>
        case EVENT_STARTED_DISTRIBUTED_NETWORK:
        {
<#if (AUTOMATIC_COMMISSIONING_ON_STARTUP == true) >
            appSnprintf("Started Distributed Network\r\n");
<#else>
            //appSnprintf("Started Distributed Network\r\n");
</#if>
        }
        break;
<#if (AUTOMATIC_COMMISSIONING_ON_STARTUP == true) >
        case EVENT_JOINED_TO_AN_EXISTING_NETWORK:
        {
            appSnprintf("Network Search: Complete: Joined to a Network \r\n");
            appSnprintf("Joined to: Address 0x%04x  MACID 0x%08x%08x ExtendedPANID 0x%08x%08x\r\n", event.eventData.ParentChildInfo.shortAddress, (uint32_t)(event.eventData.ParentChildInfo.extendedAddress >> 32), (uint32_t)(event.eventData.ParentChildInfo.extendedAddress & 0xFFFFFFFF), (uint32_t)(event.eventData.ParentChildInfo.extendedPanId >> 32), (uint32_t)(event.eventData.ParentChildInfo.extendedPanId & 0xFFFFFFFF));
        }
        break;
</#if>

        case EVENT_WAKEUP:
        {
            //appSnprintf("Wake up Indication \r\n");
        }
        break;

        case EVENT_LEFT_FROM_NETWORK:
        {
            //appSnprintf("Left from the Network \r\n");
        }
        break;

        case EVENT_CHILD_JOINED:
        {
<#if (AUTOMATIC_COMMISSIONING_ON_STARTUP == true) >
            appSnprintf("Device joined: Address 0x%04x  MACID 0x%08x%08x ExtendedPANID 0x%08x%08x\r\n", event.eventData.ParentChildInfo.shortAddress, (uint32_t)(event.eventData.ParentChildInfo.extendedAddress >> 32), (uint32_t)(event.eventData.ParentChildInfo.extendedAddress & 0xFFFFFFFF), (uint32_t)(event.eventData.ParentChildInfo.extendedPanId >> 32), (uint32_t)(event.eventData.ParentChildInfo.extendedPanId & 0xFFFFFFFF));
<#else>
            //appSnprintf("Device joined: Address 0x%04x  MACID 0x%08x%08x ExtendedPANID 0x%08x%08x\r\n", event.eventData.ParentChildInfo.shortAddress, //(uint32_t)(event.eventData.ParentChildInfo.extendedAddress >> 32), (uint32_t)(event.eventData.ParentChildInfo.extendedAddress & 0xFFFFFFFF), //(uint32_t)(event.eventData.ParentChildInfo.extendedPanId >> 32), (uint32_t)(event.eventData.ParentChildInfo.extendedPanId & 0xFFFFFFFF));
</#if>
        }
        break;

        case EVENT_CHILD_REMOVED:
        {
<#if (AUTOMATIC_COMMISSIONING_ON_STARTUP == true) >
            appSnprintf("Child Left\r\n");
<#else>
            //appSnprintf("Child Left\r\n");
</#if>
        }
        break;

        case EVENT_NWK_UPDATE:
        {
            //appSnprintf("Network Information updated \r\n");
        }
        break;

        case EVENT_RESET_TO_FACTORY_DEFAULTS:
        {
<#if (AUTOMATIC_COMMISSIONING_ON_STARTUP == true) >
            //appSnprintf("Reset To Factory New\r\n");
<#else>
            appSnprintf("Reset To Factory New\r\n");
</#if>
        }
        break;

        case EVENT_NWK_ADDRESS_RESPONSE:
        {
            if(event.eventData.ParentChildInfo.status == ZCL_SUCCESS_STATUS)
                appSnprintf( "->NwkAddrResponse, status = %d, address = %04x\r\n" ,event.eventData.ParentChildInfo.status, event.eventData.ParentChildInfo.shortAddress);
            else
                appSnprintf( "->NwkAddrResponse, status = %d \r\n" ,event.eventData.ParentChildInfo.status);
        }
        break;

        case EVENT_IEEE_ADDRESS_RESPONSE:
        {
            if(event.eventData.ParentChildInfo.status == ZCL_SUCCESS_STATUS)
                appSnprintf("->IeeeAddrResponse, status = %d, address = 0x%04x \r\n", event.eventData.ParentChildInfo.status, (uint32_t)(event.eventData.ParentChildInfo.extendedAddress >> 32), (uint32_t)(event.eventData.ParentChildInfo.extendedAddress & 0xFFFFFFFF));
            else
                appSnprintf( "->IeeeAddrResponse, status = %d, address = 0x%04x \r\n", event.eventData.ParentChildInfo.status);
        }
        break;

        case EVENT_SIMPLE_DESCRIPTOR_RESPONSE:
        {
            appSnprintf( "->SimpleDescResponse, status = %d \r\n" ,event.eventData.ParentChildInfo.status);
        }
        break;

        case EVENT_MATCH_DESCRIPTOR_RESPONSE:
        {
            if(event.eventData.ParentChildInfo.status == ZCL_SUCCESS_STATUS)
                appSnprintf( "->MatchDescResponse, status = %d, MatchedEpCount = %d\r\n" ,event.eventData.ParentChildInfo.status, event.eventData.ParentChildInfo.ep);
            else
                appSnprintf( "->MatchDescResponse, status = %d \r\n" ,event.eventData.ParentChildInfo.status);
        }
        break;

        case EVENT_ACTIVE_EP_RESPONSE:
        {
            if(event.eventData.ParentChildInfo.status == ZCL_SUCCESS_STATUS)
                appSnprintf( "->ActiveEpResponse, status = %d, EpCount = %d\r\n" ,event.eventData.ParentChildInfo.status, event.eventData.ParentChildInfo.ep);
            else
                appSnprintf( "->ActiveEpResponse, status = %d \r\n" ,event.eventData.ParentChildInfo.status);
        }
        break;

        case EVENT_NODE_DESCRIPTOR_RESPONSE:
        {
            appSnprintf( "->NodeDescResponse, status = %d \r\n" ,event.eventData.ParentChildInfo.status);
        }
        break;

        case EVENT_LEAVE_RESPONSE:
        {
            appSnprintf( "->LeaveRsp, status = %d \r\n" ,event.eventData.ParentChildInfo.status);
        }
        break;

        case EVENT_MANAGEMENT_BIND_RESPONSE:
        {
            appSnprintf( "MgmtBindRsp %d\r\n", event.eventData.ParentChildInfo.status); 
        }
        break;

        case EVENT_LQI_RESPONSE:
        {
            appSnprintf( "->MgmtLqiRsp, status = %d \r\n" ,event.eventData.ParentChildInfo.status);
        }
        break;

        case EVENT_BIND_RESPONSE:
        {
            appSnprintf( "->BindRsp, status = %d \r\n" ,event.eventData.ParentChildInfo.status);
        }
        break;

        case EVENT_UNBIND_RESPONSE:
        {
            appSnprintf( "->UnBindRsp, status = %d \r\n" ,event.eventData.ParentChildInfo.status);
        }
        break;

        default:
        break;
    }
}

/*******************************************************************************
  Function:
    void Cluster_Event_Handler(APP_Zigbee_Event_t event)

  Remarks:
    See prototype in app_zigbee_handler.h.
******************************************************************************/

void Cluster_Event_Handler(APP_Zigbee_Event_t event)
{
    switch(event.eventId)
    {
<#if ((ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "CLIENT")  && (OC_ON == true))>
        case CMD_ZCL_ON:
        {
            /* ZCL Command ON received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("On\r\n");
        }
        break;
</#if>
<#if ((ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "CLIENT")  && (OC_OFF == true))>
        case CMD_ZCL_OFF:
        {
            /* ZCL Command Off received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("Off\r\n");
        }
        break;
</#if>
<#if ((ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "CLIENT")  && (OC_TOGGLE == true))>
        case CMD_ZCL_TOGGLE:
        {
            /* ZCL Command Toggle received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("Toggle\r\n");
        }
        break;
</#if>
<#if ((ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "CLIENT")  && (OC_OFFWITHEFFECT == true))>
        case CMD_ZCL_OFF_WITH_EFFECT:
        {
            /* ZCL Command Off with effect received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_OffWithEffect_t *payload = (ZCL_OffWithEffect_t *)event.eventData.zclEventData.payload;
            appSnprintf("OffWithEffect %d 0x%x\r\n", payload->effectIdentifier, payload->effectVariant);
        }
        break;
</#if>
<#if ((ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "CLIENT")  && (OC_ONWITHRECALL == true))>
        case CMD_ZCL_ON_WITH_RECALL_GLOBALSCENE:
        {
            /* ZCL Command on with recall globalscene received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("OnWithRecallGlobalScene\r\n");
        }
        break;
</#if>
<#if ((ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "CLIENT")  && (OC_ONWITHTIMEDOFF == true))>
        case CMD_ZCL_ON_WITH_TIMED_OFF:
        {
            /* ZCL Command on with timed off received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_OnWithTimedOff_t *payload = (ZCL_OnWithTimedOff_t *)event.eventData.zclEventData.payload;
            appSnprintf("OnWithTimedOff %d %d 0x%x\r\n", payload->onOffControl, payload->onTime, payload->offWaitTime);
        }
        break;
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVETOHUE == true))>
        case CMD_ZCL_MOVE_TO_HUE:
        {
            /* ZCL Command Move to Hue received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("moveToHueInd()\r\n");
        }
        break;
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVEHUE == true))>
        case CMD_ZCL_MOVE_HUE:
        {
            /* ZCL Command Move Hue received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
           appSnprintf("moveHueInd()\r\n");
        }
        break;
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_STEPHUE == true))>
        case CMD_ZCL_STEP_HUE:
        {
            /* ZCL Command Step Hue received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("stepHueInd()\r\n");
        }
        break;
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVETOSATURATION == true))>
        case CMD_ZCL_MOVE_TO_SATURATION:
        {
            /* ZCL Command Move to Saturation received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("moveToSaturationInd()\r\n");
        }
        break;
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVESATURATION == true))>
        case CMD_ZCL_MOVE_SATURATION:
        {
            /* ZCL Command Move Saturation received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("moveSaturationInd()\r\n");
        }
        break;
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_STEPSATURATION == true))>
        case CMD_ZCL_STEP_SATURATION:
        {
            /* ZCL Command Step Saturation received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("stepSaturationInd()\r\n");
        }
        break;
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVETOHUESATURATION == true))>
        case CMD_ZCL_MOVE_TO_HUE_SATURATION:
        {
            /* ZCL Command Move to Hue Saturation received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("moveToHueAndSaturationInd()\r\n");
        }
        break;
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVETOCOLOR == true))>
        case CMD_ZCL_MOVE_TO_COLOR:
        {
            /* ZCL Command Move to Color received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            uint16_t x, y;
            ZCL_ZllMoveToColorCommand_t *payload = (ZCL_ZllMoveToColorCommand_t*)event.eventData.zclEventData.payload;
            x = (MAX_COLOR_LEVEL < payload->colorX) ? MAX_COLOR_LEVEL : payload->colorX;
            y = (MAX_COLOR_LEVEL < payload->colorY) ? MAX_COLOR_LEVEL : payload->colorY;
            appSnprintf("moveToColorInd() X=%d Y=%d\r\n", x,y);
        }
        break;
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVECOLOR == true))>
        case CMD_ZCL_MOVE_COLOR:
        {
            /* ZCL Command Move Color received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("moveColorInd()\r\n");
        }
        break;
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_STEPCOLOR == true))>
        case CMD_ZCL_STEP_COLOR:
        {
            /* ZCL Command Step Color received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("stepColorInd()\r\n");
        }
        break;
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVETOCOLORTEMP == true))>
        case CMD_ZCL_MOVE_TO_COLOR_TEMPERATURE:
        {
            /* ZCL Command Move to Color Temerature received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("moveToColorTemperatureInd()\r\n");
        }
        break;
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDMOVETOHUE == true))>
        case CMD_ZCL_ENHANCED_MOVE_TO_HUE:
        {
            /* ZCL Command Enhanced Move to Hue received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("enhancedMoveToHueInd()\r\n");
        }
        break;
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDMOVEHUE == true))>
        case CMD_ZCL_ENHANCED_MOVE_HUE:
        {
            /* ZCL Command Move Hue received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("enhancedMoveHueInd()\r\n");
        }
        break;
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDSTEPHUE == true))>
        case CMD_ZCL_ENHANCED_STEP_HUE:
        {
            /* ZCL Command Step Hue received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("enhancedStepHueInd()\r\n");
        }
        break;
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDMOVETOHUESATURATION == true))>
        case CMD_ZCL_ENHANCED_MOVED_TO_HUE_SATURATION:
        {
            /* ZCL Command Move to Hue Saturation received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            uint16_t saturation;
            ZCL_ZllEnhancedMoveToHueAndSaturationCommand_t *payload = (ZCL_ZllEnhancedMoveToHueAndSaturationCommand_t*)event.eventData.zclEventData.payload;
            saturation = (MAX_SATURATION_LEVEL < payload->saturation) ? MAX_SATURATION_LEVEL : payload->saturation;
            appSnprintf("enhancedMoveToHueAndSaturationInd() Hue=%d Saturation=%d\r\n", payload->enhancedHue,saturation);
        }
        break;
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPSET == true))>
        case CMD_ZCL_COLOR_LOOP_SET:
        {
            /* ZCL Command Color loop Set received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("colorLoopSetInd()\r\n");
        }
        break;
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_STOPMOVESTEP == true))>
       case CMD_ZCL_STOP_MOVE_STEP:
        {
            /* ZCL Command ZCL STOP MOVE SET received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
             appSnprintf("stopMoveStepInd()\r\n");
        }
        break;
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVECOLORTEMP == true))>
        case CMD_ZCL_MOVE_COLOR_TEMPERATURE:
        {
            /* ZCL Command Move to Color Temperature received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("moveColorTemperatureInd()\r\n");
        }
        break;
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_STEPCOLORTEMP == true))>
        case CMD_ZCL_STEP_COLOR_TEMPERATURE:
        {
            /* ZCL Command Step Color Temperature received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("stepColorTemperatureInd()\r\n");
        }
        break;
</#if>
<#if ((BASIC_CLUSTER_ENABLE == true) && (BASIC_CLUSTER_CS != "CLIENT")  &&  (BS_RESETTOFNCMD == true))>
        case CMD_ZCL_RESET_TO_FACTORY_DEFAULTS:
        {
            /* Command ZCL ResetToFactoryDefaults */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            //appSnprintf("ZCL ResetToFactoryDefaults\r\n");
        }
        break;
</#if>
<#if ((IDENTIFY_CLUSTER_ENABLE == true) && (IDENTIFY_CLUSTER_CS != "CLIENT")  && (IC_IDENTIFYCMD == true))>
        case CMD_ZCL_IDENTIFY:
        {
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf( "->Identify\r\n");
        }
        break;
</#if>
<#if ((IDENTIFY_CLUSTER_ENABLE == true) && (IDENTIFY_CLUSTER_CS != "CLIENT")  && (IC_IDENTIFYQUERYCMD == true))>
        case CMD_ZCL_IDENTIFY_QUERY:
        {
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
<#if (AUTOMATIC_COMMISSIONING_ON_STARTUP == true) >
            //appSnprintf("->IdentifyQuery\r\n");
<#else>
            appSnprintf("->IdentifyQuery\r\n");
</#if>  
        }
        break;
</#if>
<#if ((IDENTIFY_CLUSTER_ENABLE == true) && (IDENTIFY_CLUSTER_CS != "CLIENT")  && (IC_TRIGGEREFFECT == true))>
        case CMD_ZCL_TRIGGER_EFFECT:
        {
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_TriggerEffect_t *payload = (ZCL_TriggerEffect_t *)event.eventData.zclEventData.payload;
            appSnprintf("->TriggerEffect 0x%x\r\n",  payload->effectIdentifier);
        }
        break;
</#if>
<#if ((IDENTIFY_CLUSTER_ENABLE == true) && (IDENTIFY_CLUSTER_CS != "SERVER")  && (ICC_IDENTIFYQUERYRESCMD == true))>
        case CMD_ZCL_IDENTIFY_QUERY_RESPONSE:
        {
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
<#if (AUTOMATIC_COMMISSIONING_ON_STARTUP == true) >
            //appSnprintf("->IdentifyQueryResponse, addr = 0x%04x, timeout = 0x%04x\r\n", addressing->addr.shortAddress, payload->timeout);
<#else>	
            ZCL_IdentifyQueryResponse_t *payload = (ZCL_IdentifyQueryResponse_t *)event.eventData.zclEventData.payload;
            ZCL_Addressing_t *addressing = (ZCL_Addressing_t *)event.eventData.zclEventData.addressing;
            appSnprintf("->IdentifyQueryResponse, addr = 0x%04x, timeout = 0x%04x\r\n", addressing->addr.shortAddress, payload->timeout);
</#if>
        }
        break;
</#if>
<#if ((GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "CLIENT")  && (GC_ADDGROUP == true))>
        case CMD_ZCL_ADD_GROUP:
        {
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_AddGroup_t *payload = (ZCL_AddGroup_t *)event.eventData.zclEventData.payload;
            appSnprintf("addGroupInd(): 0x%04x\r\n", payload->groupId);
        }
        break;
</#if>
<#if ((GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "CLIENT")  && (GC_VIEWGROUP == true))>
        case CMD_ZCL_VIEW_GROUP:
        {
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_ViewGroup_t *payload = (ZCL_ViewGroup_t *)event.eventData.zclEventData.payload;
            appSnprintf("viewGroupInd(): 0x%04x\r\n", payload->groupId);
        }
        break;
</#if>
<#if ((GROUPS_CLUSTER_ENABLE == true) &&  (GROUPS_CLUSTER_CS != "CLIENT")  && (GC_GROUPMEM == true))>
        case CMD_ZCL_GET_GROUP_MEMBERSHIP:
        {
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload; 
            appSnprintf("getGroupMembershipInd()\r\n");
        }
        break;
</#if>
<#if ((GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "CLIENT")  && (GC_REMOVEGROUP == true))>
        case CMD_ZCL_REMOVE_GROUP:
        {
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_RemoveGroup_t *payload = (ZCL_RemoveGroup_t *)event.eventData.zclEventData.payload;
            appSnprintf("removeGroupInd(): 0x%04x\r\n", payload->groupId);
        }
        break;
</#if>
<#if ((GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "CLIENT")  && (GC_REMOVEGROUPALL == true))>
        case CMD_ZCL_REMOVE_ALL_GROUP:
        {
            //Access - > event.eventData.zclAttributeData.addressing;
            //Access - > event.eventData.zclAttributeData.attributeId;
            //Access - > event.eventData.zclAttributeData.event;
            appSnprintf( "removeAllGroupsInd()\r\n");
        }
        break;
</#if>
<#if ((GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "CLIENT")  && (GC_ADDGROUPIF == true))>
        case CMD_ZCL_ADD_GROUP_IF_IDENTIFYING:
        {
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_AddGroupIfIdentifying_t *payload = (ZCL_AddGroupIfIdentifying_t *)event.eventData.zclEventData.payload;
            appSnprintf("addGroupIfIdentifyingInd(): 0x%04x\r\n", payload->groupId);
        }
        break;
</#if>
<#if ((GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "SERVER")  && (GCC_ADDGROUPRESP == true))>
        case CMD_ZCL_ADD_GROUP_RESPONSE:
        {
            //Access - > event.eventData.zclAttributeData.addressing;
            //Access - > event.eventData.zclAttributeData.attributeId;
            //Access - > event.eventData.zclAttributeData.event;
            appSnprintf("addGroupResponseInd()\r\n");
        }
        break;
</#if>
<#if ((GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "SERVER")  && (GCC_VIEWGROUPRESP == true))>
        case CMD_ZCL_VIEW_GROUP_RESPONSE:
        {
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_ViewGroupResponse_t *payload = (ZCL_ViewGroupResponse_t *)event.eventData.zclEventData.payload;
            appSnprintf("viewGroupResponse(): status = 0x%02x\r\n", payload->status);
            appSnprintf("groupId = 0x%04x\r\n", payload->groupId);
        }
        break;
</#if>
<#if ((GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "SERVER")  && (GCC_GROUPMEMRESP == true))>
        case CMD_ZCL_GET_GROUP_MEMBERSHIP_RESPONSE:
        {
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_GetGroupMembershipResponse_t *payload = (ZCL_GetGroupMembershipResponse_t *)event.eventData.zclEventData.payload;
            appSnprintf("getGroupMembershipResponse()\r\n");
            appSnprintf("groupCount = %d\r\n", payload->groupCount);
            for (uint8_t i = 0; i < payload->groupCount; i++)
              appSnprintf("groupId = 0x%04x\r\n", payload->groupList[i]);
        }
        break;
</#if>
<#if ((GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "SERVER")  && (GCC_REMOVEGROUPRESP == true))>
        case CMD_ZCL_REMOVE_GROUP_RESPONSE:
        {
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_RemoveGroupResponse_t *payload = (ZCL_RemoveGroupResponse_t *)event.eventData.zclEventData.payload;
            appSnprintf("removeGroupResponseInd()\r\n");
            appSnprintf("groupId = 0x%04x\r\n", payload->groupId);

        }
        break;
</#if>
<#if ((LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  && (LC_MOVETOLEVEL == true))>
        case CMD_ZCL_MOVE_TO_LEVEL:
        {
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_MoveToLevel_t *payload = (ZCL_MoveToLevel_t *)event.eventData.zclEventData.payload;
            appSnprintf("->MoveToLevel: lvl=0x%x trTime=%u\r\n", ((ZCL_MoveToLevel_t *)payload)->level, ((ZCL_MoveToLevel_t *)payload)->transitionTime);
        }
        break;
</#if>
<#if ((LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  && (LC_MOVE == true))>
        case CMD_ZCL_MOVE:
        {
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_Move_t *payload = (ZCL_Move_t *)event.eventData.zclEventData.payload;
            appSnprintf("->Move: mode=0x%x rate=0x%x\r\n", ((ZCL_Move_t*)payload)->moveMode, ((ZCL_Move_t*)payload)->rate);
        }
        break;
</#if>
<#if ((LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  && (LC_STEP == true))>
        case CMD_ZCL_STEP:
        {
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_Step_t *payload = (ZCL_Step_t *)event.eventData.zclEventData.payload;
            appSnprintf( "->Step: mode=0x%x stepSize=0x%x trTime=%u\r\n", ((ZCL_Step_t *)payload)->stepMode, ((ZCL_Step_t *)payload)->stepSize, ((ZCL_Step_t *)payload)->transitionTime);
        }
        break;
</#if>
<#if ((LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  && (LC_STOP == true))>
        case CMD_ZCL_STOP:
        {
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("->Stop\r\n");
        }
        break;
</#if>
<#if ((LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  && (LC_MOVETOLEVELWITHONOFF == true))>
        case CMD_ZCL_MOVE_TO_LEVEL_WITH_ONOFF:
        {
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_MoveToLevelWithOnOff_t *payload = (ZCL_MoveToLevelWithOnOff_t *)event.eventData.zclEventData.payload;
            appSnprintf("->MoveToLevelWithOnOff: lvl=0x%x trTime=%u\r\n", ((ZCL_MoveToLevelWithOnOff_t*)payload)->level, ((ZCL_MoveToLevelWithOnOff_t*)payload)->transitionTime);
        }
        break;
</#if>
<#if ((LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  && (LC_MOVEWITHONOFF == true))>
        case CMD_ZCL_MOVE_WITH_ONOFF:
        {
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_MoveWithOnOff_t *payload = (ZCL_MoveWithOnOff_t *)event.eventData.zclEventData.payload;
            appSnprintf("->Move with on/off: mode=0x%x rate=0x%x\r\n", ((ZCL_MoveWithOnOff_t*)payload)->moveMode, ((ZCL_MoveWithOnOff_t*)payload)->rate);
        }
        break;
</#if>
<#if ((LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  && (LC_STEPWITHONOFF == true))>
        case CMD_ZCL_STEP_WITH_ONOFF:
        {
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_StepWithOnOff_t *payload = (ZCL_StepWithOnOff_t *)event.eventData.zclEventData.payload;
            appSnprintf("->Step with on/off: mode=0x%x stepSize=0x%x trTime=%u\r\n", ((ZCL_StepWithOnOff_t*)payload)->stepMode, ((ZCL_StepWithOnOff_t*)payload)->stepSize, ((ZCL_StepWithOnOff_t*)payload)->transitionTime);
        }
        break;
</#if>
<#if ((LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  && (LC_STOPWITHONOFF == true))>
        case CMD_ZCL_STOP_WITH_ONOFF:
        {
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("->Stop with on/off\r\n");
        }
        break;
</#if>
<#if ((ALARMS_CLUSTER_ENABLE == true) && (ALARMS_CLUSTER_CS != "SERVER")  && (AC_ALARM == true))>
        case CMD_ZCL_ALARM:
        {
            /* Command ZCL OnOffAttributeEventInd */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_Alarm_t *payload = (ZCL_Alarm_t *)event.eventData.zclEventData.payload;
            appSnprintf("<-Alarms alarmCode = %d clusterId = 0x%x\r\n", payload->alarmCode, payload->clusterIdentifier);
        }
        break;
</#if>
<#if ((ALARMS_CLUSTER_ENABLE == true) && (ALARMS_CLUSTER_CS != "SERVER")  && (AC_GETALARMRESPONSE == true))>
        case CMD_ZCL_GET_ALARM_RESPONSE:
        {
            /* Command ZCL OnOffAttributeEventInd */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload; 
            ZCL_getAlarmResponse_t *payload = (ZCL_getAlarmResponse_t *)event.eventData.zclEventData.payload; 
            if ( BC_SUCCESS == payload->status)
            {
                appSnprintf("<-GetAlarmResponse status = 0x%x clusterId = 0x%x alarmCode = 0x%x\r\n", payload->status, payload->clusterIdentifier, payload->alarmCode);
            }
            else
            {
                appSnprintf("<-GetAlarmResponse failed status = 0x%x\r\n", payload->status);
            }
        }
        break;
</#if>
<#if ((ALARMS_CLUSTER_ENABLE == true) && (ALARMS_CLUSTER_CS != "CLIENT")  && (AS_RESETALLALARMS == true))>
    case CMD_ZCL_RESET_ALL_ALARMS:
        {
            /* Command ZCL OnOffAttributeEventInd */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;            
            appSnprintf("<-resetAllAlarm\r\n");
        }
        break;
</#if>
<#if ((ALARMS_CLUSTER_ENABLE == true) && (ALARMS_CLUSTER_CS != "CLIENT")  && (AS_RESETALARM == true))>
    case CMD_ZCL_RESET_ALARM:
        {
            /* Command ZCL OnOffAttributeEventInd */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_ResetAlarm_t *payload = (ZCL_ResetAlarm_t *)event.eventData.zclEventData.payload;        
            appSnprintf("<-resetAlarm clusterId = 0x%x alarmCode = 0x%x\r\n", payload->clusterIdentifier, payload->alarmCode);
        }
        break;
</#if>
<#if ((ALARMS_CLUSTER_ENABLE == true) && (ALARMS_CLUSTER_CS != "CLIENT")  && (AS_GETALARM == true))>
    case CMD_ZCL_GET_ALARM:
        {
            /* Command ZCL OnOffAttributeEventInd */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload; 
            appSnprintf("<-getAlarm\r\n");
        }
        break;
</#if>
<#if ((ALARMS_CLUSTER_ENABLE == true) && (ALARMS_CLUSTER_CS != "CLIENT")  && (AS_RESETALLALARMLOG == true))>
    case CMD_ZCL_RESET_ALARM_LOG:
        {
            /* Command ZCL OnOffAttributeEventInd */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload; 
            appSnprintf("<-resetAlarmLog\r\n");
        }
        break;
</#if>
<#if ((THERMOSTAT_CLUSTER_ENABLE == true) && (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (THC_SETPOINTRAISELOWER == true))>
        case CMD_ZCL_SETPOINT:
        {
            /* Command ZCL TH HumidityMeasurementReportInd Prints Report Value */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;    
           //appSnprintf("ZCL SetEndpoint Ind");
        }
        break;
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  && (SC_ADDSCENE == true))>
        case CMD_ZCL_ADD_SCENE:
        {
            /* ZCL Command add scene received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_AddScene_t *cmd =((ZCL_AddScene_t*)event.eventData.zclEventData.payload);
            appSnprintf("addSceneInd(): 0x%04x, 0x%02x\r\n", cmd->groupId, cmd->sceneId);
        }
        break;
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  && (SC_VIEWSCENE == true))>
        case CMD_ZCL_VIEW_SCENE:
        {
            /* ZCL Command view scene received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_ViewScene_t *cmd = ((ZCL_ViewScene_t*)event.eventData.zclEventData.payload);
            appSnprintf("viewSceneInd(): 0x%04x, 0x%02x\r\n", cmd->groupId, cmd->sceneId);
        }
        break;
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  && (SC_ENHANCEDADDSCENE == true))>
        case CMD_ZCL_ENHANCED_ADD_SCENE:
        {
            /* ZCL Command enhanced add scene received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_EnhancedAddScene_t *cmd = ((ZCL_EnhancedAddScene_t*)event.eventData.zclEventData.payload);
            appSnprintf("enhancedAddSceneInd(): 0x%04x, 0x%02x\r\n", cmd->groupId, cmd->sceneId);
        }
        break;
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  && (SC_ENHANCEDVIEWSCENE == true))>
        case CMD_ZCL_ENHANCED_VIEW_SCENE:
        {
            /* ZCL Command enhanced view scene received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_EnhancedViewScene_t *cmd = ((ZCL_EnhancedViewScene_t*)event.eventData.zclEventData.payload);
            appSnprintf("enhancedViewSceneInd(): 0x%04x, 0x%02x\r\n", cmd->groupId, cmd->sceneId);
        }
        break;
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  && (SC_REMOVESCENE == true))>
        case CMD_ZCL_REMOVE_SCENE:
        {
            /* ZCL Command remove scene received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_RemoveScene_t *cmd = ((ZCL_RemoveScene_t*)event.eventData.zclEventData.payload);
            appSnprintf("removeSceneInd(): 0x%04x, 0x%02x\r\n", cmd->groupId, cmd->sceneId);
        }
        break;
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  && (SC_REMOVESCENEALL == true))>
        case CMD_ZCL_REMOVE_ALL_SCENES:
        {
            /* ZCL Command remove all scenes received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_RemoveAllScenes_t *cmd = ((ZCL_RemoveAllScenes_t*)event.eventData.zclEventData.payload);
            appSnprintf("removeAllScenesInd(): 0x%04x\r\n", cmd->groupId);
        }
        break;
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  && (SC_STORESCENE == true))>
        case CMD_ZCL_STORE_SCENE:
        {
            /* ZCL Command store scene received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_StoreScene_t *cmd = ((ZCL_StoreScene_t*)event.eventData.zclEventData.payload);
            appSnprintf("storeSceneInd(): 0x%04x, 0x%x\r\n", cmd->groupId, cmd->sceneId);
        }
        break;
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  && (SC_RECALLSCENE == true))>
        case CMD_ZCL_RECALL_SCENE:
        {
            /* ZCL Command recall scene received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_RecallScene_t *cmd = ((ZCL_RecallScene_t *)event.eventData.zclEventData.payload);
            appSnprintf("recallSceneInd(): 0x%04x, 0x%x\r\n", cmd->groupId, cmd->sceneId);
        }
        break;
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  && (SC_SCENEMEM == true))>
        case CMD_ZCL_GET_SCENE_MEMBERSHIP:
        {
            /* ZCL Command get scene membership received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_GetSceneMembership_t *cmd = ((ZCL_GetSceneMembership_t *)event.eventData.zclEventData.payload);
            appSnprintf("getSceneMembershipInd(): 0x%04x\r\n", cmd->groupId);
        }
        break;
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  && (SC_COPYSCENE == true))>
        case CMD_ZCL_COPY_SCENE:
        {
            /* ZCL Command get scene membership received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_GetSceneMembership_t *cmd = ((ZCL_GetSceneMembership_t *)event.eventData.zclEventData.payload);
            appSnprintf("copySceneInd()\r\n");
        }
        break;
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  && (SCC_ADDSCENERESP == true))>
        case CMD_ZCL_ADD_SCENE_RESP:
        {
            /* ZCL Command Add scene response received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_AddSceneResponse_t *resp = ((ZCL_AddSceneResponse_t*)event.eventData.zclEventData.payload);
            appSnprintf("Add scene response: status = 0x%02x\r\n", resp->status);
            appSnprintf("groupId = 0x%04x\r\n", resp->groupId);
            appSnprintf("sceneId = 0x%02x\r\n", resp->sceneId);
        }
        break;
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  && (SCC_VIEWSCENERES == true))>
        case CMD_ZCL_VIEW_SCENE_RESP:
        {
            /* ZCL Command View scene response received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_ViewSceneResponse_t *resp = ((ZCL_ViewSceneResponse_t*)event.eventData.zclEventData.payload);
            appSnprintf("View scene response: status = 0x%02x\r\n", resp->status);
            appSnprintf( "groupId = 0x%04x\r\n", resp->groupId);
            appSnprintf("sceneId = 0x%02x\r\n", resp->sceneId);
            appSnprintf("transitionTime = 0x%04x\r\n", resp->transitionTime);
        }
        break;
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  && (SCC_REMOVESCENERES == true))>
        case CMD_ZCL_REMOVE_SCENE_RESP:
        {
            /* ZCL Command remove scene response received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_RemoveSceneResponse_t *resp = ((ZCL_RemoveSceneResponse_t*)event.eventData.zclEventData.payload);
            appSnprintf("Remove scene response: status = 0x%02x\r\n",resp->status);
            appSnprintf("groupId = 0x%04x\r\n", resp->groupId);
            appSnprintf("sceneId = 0x%02x\r\n", resp->sceneId);
        }
        break;
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  && (SCC_REMOVESCENEALLRES == true))>
        case CMD_ZCL_REMOVE_ALL_SCENES_RESP:
        {
            /* ZCL Command remove all scenes response received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_RemoveAllScenesResponse_t *resp = ((ZCL_RemoveAllScenesResponse_t*)event.eventData.zclEventData.payload);
            appSnprintf("Remove all scenes response: status = 0x%02x\r\n", resp->status);
            appSnprintf("groupId = 0x%04x\r\n", resp->groupId);
        }
        break;
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  && (SCC_STORESCENERES == true))>
        case CMD_ZCL_STORE_SCENE_RESP:
        {
            /* ZCL Command store scene response received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_StoreSceneResponse_t *resp = ((ZCL_StoreSceneResponse_t*)event.eventData.zclEventData.payload);
            appSnprintf("Store scene response: status = 0x%02x\r\n",resp->status);
            appSnprintf("groupId = 0x%04x\r\n", resp->groupId);
            appSnprintf("sceneId = 0x%02x\r\n", resp->sceneId);
        }
        break;
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  && (SCC_SCENEMEMRES == true))>
        case CMD_ZCL_GET_SCENE_MEMBERSHIP_RESP:
        {
            /* ZCL Command get scene membership response received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_GetSceneMembershipResponse_t *resp = ((ZCL_GetSceneMembershipResponse_t*)event.eventData.zclEventData.payload);
            appSnprintf("Get scene membership response: status = 0x%02x\r\n", resp->status);
            appSnprintf("groupId = 0x%04x\r\n", resp->groupId);
            appSnprintf("sceneCount = 0x%02x\r\n", resp->sceneCount);
            for (uint8_t i = 0; i < resp->sceneCount; i++)
              appSnprintf("sceneId = 0x%02x\r\n", resp->sceneList[i]);
        }
        break;
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  && (SCC_ENHANCEDADDSCENERES == true))>
        case CMD_ZCL_ENHANCED_ADD_SCENE_RESP:
        {
            /* ZCL Command enhanced Add scene response received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_EnhancedAddSceneResponse_t *resp = (ZCL_EnhancedAddSceneResponse_t *)(event.eventData.zclEventData.payload);
            appSnprintf("Enhanced add scene response: status = 0x%02x\r\n", resp->status);
            appSnprintf("groupId = 0x%04x\r\n", resp->groupId);
            appSnprintf("sceneId = 0x%02x\r\n", resp->sceneId);
        }
        break;
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  && (SCC_ENHANCEDVIEWSCENERES == true))>
        case CMD_ZCL_ENHANCED_VIEW_SCENE_RESP:
        {
            /* ZCL Command enhanced view scene response received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_EnhancedViewSceneResponse_t *resp = ((ZCL_EnhancedViewSceneResponse_t *)(event.eventData.zclEventData.payload));
            appSnprintf("Enhanced view scene response: status = 0x%02x\r\n", resp->status);
            appSnprintf("groupId = 0x%04x\r\n", resp->groupId);
            appSnprintf("sceneId = 0x%02x\r\n", resp->sceneId);
            appSnprintf("transitionTime = 0x%04x\r\n", resp->transitionTime);
        }
        break;
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  && (SCC_COPYSCENERES == true))>
        case CMD_ZCL_COPY_SCENE_RESP:
        {
            /* ZCL Command copy scene response received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_CopySceneResponse_t *resp = ((ZCL_CopySceneResponse_t*)event.eventData.zclEventData.payload);
            appSnprintf("Copy scene response: status = 0x%02x\r\n", resp->status);
        }
        break;
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_GETPANELSTATUS == true))>
        case CMD_ZCL_ACE_GET_PANEL_STATUS:
        {
            /* ZCL Command copy scene response received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf(" ->ACEGetPanelStatusCommandInd Received\r\n");
        }
        break;
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONESTATUSRESP == true))>
        case CMD_ZCL_ACE_GET_PANEL_STATUS_RESP:
        {
            /* ZCL Command copy scene response received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf(" ->aceGetPanelStatusRespReceived\r\n");
        }
        break;
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_ARM == true))>
        case CMD_ZCL_ACE_ARM:
        {
            /* ZCL command IAS ACE arm received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            //appSnprintf("aceArmCommandInd()\r\n");
        }
        break;
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_GETZONEINFO == true))>
        case CMD_ZCL_ACE_GET_ZONE_INFO:
        {
            /* ZCL ace get zone information received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("aceGetZoneInformationCommandInd()\r\n");
        }
        break;
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_GETZONEIDMAP == true))>
        case CMD_ZCL_ACE_GET_ZONE_ID_MAP:
        {
            /* ZCL IAS ACE get zone ID received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("aceGetZoneIdMapCommandInd()\r\n");
        }
        break;
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_BYPASS == true))>
        case CMD_ZCL_ACE_BYPASS:
        {
            /* ZCL IAS ACE bypass command received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("aceByPassCommandInd()\r\n");
        }
        break;
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_GETBYPASSZONELIST == true))>
        case CMD_ZCL_ACE_GET_BYPASSED_ZONE_LIST:
        {
            /* ZCL IAS ACE get bypassed zone list command received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("aceGetByPassedZoneListCommandInd()\r\n");
        }
        break;
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_EMERGENCY == true))>
        case CMD_ZCL_ACE_EMERGENCY:
        {
            /* ZCL IAS ACE emergency command received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf(" ->ACE Emergency Command Received\r\n");
        }
        break;
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_FIRE == true))>
        case CMD_ZCL_ACE_FIRE:
        {
            /* ZCL IAS ACE fire command received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf(" ->ACE Fire Command Received\r\n");
        }
        break;
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_PANIC == true))>
        case CMD_ZCL_ACE_PANIC:
        {
            /* ZCL Command IAS ACE PANIC received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf(" ->ACE Panic Command Received\r\n");
        }
        break;
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  && (IACC_ARMRESP == true))>
        case CMD_ZCL_ACE_ARM_RESP:
        {
            /* ZCL Command IAS ACE arm received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf(" ->ACEArmResponseCommand Received\r\n");
        }
        break;
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONEIDMAPRESP == true))>
        case CMD_ZCL_ACE_GET_ZONE_ID_MAP_RESP:
        {
            /* ZCL Command IAS ACE get zone id map response received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf(" ->ZoneIdMapResponseCommand Received \r\n");
        }
        break;
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONESTATUSRESP == true))>
        case CMD_ZCL_ACE_GET_ZONE_STATUS_RESP:
        {
            /* ZCL Command IAS ACE get zone status response received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf(" ->aceGetZoneStatusRespReceived\r\n");
        }
        break;
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  && (IACC_PANELSTATUSCHANGED == true))>
        case CMD_ZCL_ACE_PANEL_STATUS_CHANGED:
        {
            /* ZCL Command IAS ACE panel status received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            //appSnprintf("acePanelStatusChangedCommandInd()\r\n");
        }
        break;
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  && (IACC_ZONESTATUSCHANGED == true))>
        case CMD_ZCL_ACE_ZONE_STATUS_CHANGED:
        {
            /* ZCL IAS ACE ZONE status changed received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            //appSnprintf("aceZoneStatusChangedCommandInd()\r\n");
        }
        break;
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONEINFORESP == true))>
        case CMD_ZCL_ACE_GET_ZONE_INFO_RESP:
        {
            /* ZCL Command IAS ACE get zone information response received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf("aceGetZoneInformationResponseCommandInd()\r\n");
        }
        break;
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  && (IACC_SETBYPASSEDZONELIST == true))>
        case CMD_ZCL_ACE_SET_BYPASSED_ZONE_LIST:
        {
            /* ZCL Command IAS ACE bypassed zone list received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf(" ->ACESetByPassesZoneListCommandIndReceived\r\n");
        }
        break;
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  && (IACC_BYPASSRESPONSE == true))>
        case CMD_ZCL_ACE_BYPASS_RESP:
        {
            /* ZCL Command IAS ACE Bypass response received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            //appSnprintf("aceByPassResponseCommandInd()\r\n");
        }
        break;
</#if>
<#if ((IASZONE_CLUSTER_ENABLE == true) && (IASZONE_CLUSTER_CS != "SERVER")  && (IZCC_ZONESTATUSCHANGENOTIFICATION == true))>
        case CMD_ZCL_ZONE_STATUS_CHANGE_NOTIFY:
        {
            /* ZCL Command zone status change notification received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            appSnprintf(" <-Zone Status Change Notification Received\r\n");
        }
        break;
</#if>
<#if ((IASZONE_CLUSTER_ENABLE == true) && (IASZONE_CLUSTER_CS != "SERVER")  && (IZCC_ZONEENROLLREQ == true))>
        case CMD_ZCL_ZONE_ENROLL_REQ:
        {
            /* ZCL Command ZOne enroll request received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            //appSnprintf("zoneEnrollRequestCommandInd()\r\n");
        }
        break;
</#if>
<#if ((IASZONE_CLUSTER_ENABLE == true) && (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_INITIATENORMALOPMODE == true))>
        case CMD_ZCL_ZONE_INITIATE_NORMAL_OPERATING_MODE:
        {
            /* ZCL Command zone initiate normal operating mode received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            //appSnprintf("zoneInitiateNormalOperatingModeInd()\r\n");
        }
        break;
</#if>
<#if ((IASZONE_CLUSTER_ENABLE == true) && (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_INITIATETESTMODE == true))>
        case CMD_ZCL_ZONE_INITIATE_TEST_MODE:
        {
            /* ZCL Command zone initiate test mode received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            //appSnprintf("zoneInitiateTestModeInd()\r\n");
        }
        break;
</#if>
<#if ((IASZONE_CLUSTER_ENABLE == true) && (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONEENROLLRESP == true))>
        case CMD_ZCL_ZONE_ENROLL_RESP:
        {
            /* ZCL Command zone enroll response received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            ZCL_ZoneEnrollResCommand_t *resp = (ZCL_ZoneEnrollResCommand_t*)event.eventData.zclEventData.payload;
            appSnprintf(" <-ZoneEnrollResponseInd Command : Status = %u\r\n", resp->enrollResponseCode);
        }
        break;
</#if>
<#if COLORCONTROL_CLUSTER_ENABLE == true>
        case CMD_ZCL_ATTR_COLOR_CONTROL:
        {
            /* Command ZCL ColorControlAttributeEventInd */
            //Access - > event.eventData.zclAttributeData.addressing;
            //Access - > event.eventData.zclAttributeData.attributeId;
            //Access - > event.eventData.zclAttributeData.event;
            //appSnprintf("ZCL ColorControlAttributeEventInd\r\n");
           if(ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == event.eventData.zclAttributeData.event)
           {
            switch(event.eventData.zclAttributeData.attributeId)
            {
<#if (ZB_DEVICE_TYPE == "ZIGBEE_CUSTOM")>
            <#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTHUE == true) >
            case ZCL_ZLL_CLUSTER_CURRENT_HUE_SERVER_ATTRIBUTE_ID:
                customColorControlClusterServerAttributes.currentHue.minReportInterval = COLOR_CONTROL_CUURENT_HUE_MIN_REPORT_PERIOD;
                customColorControlClusterServerAttributes.currentHue.maxReportInterval = COLOR_CONTROL_CUURENT_HUE_MAX_REPORT_PERIOD;
                customColorControlClusterServerAttributes.currentHue.reportableChange  = 0;
            break;
            </#if>

            <#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTSATURATION == true) >
            case ZCL_ZLL_CLUSTER_CURRENT_SATURATION_SERVER_ATTRIBUTE_ID:
                customColorControlClusterServerAttributes.currentSaturation.minReportInterval = COLOR_CONTROL_CURRENT_SAT_MIN_REPORT_PERIOD;
                customColorControlClusterServerAttributes.currentSaturation.maxReportInterval = COLOR_CONTROL_CURRENT_SAT_MAX_REPORT_PERIOD;
                customColorControlClusterServerAttributes.currentSaturation.reportableChange  = 0;
            break;
            </#if>

            <#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTX == true) >
            case ZCL_ZLL_CLUSTER_CURRENT_X_SERVER_ATTRIBUTE_ID:
                customColorControlClusterServerAttributes.currentX.minReportInterval = COLOR_CONTROL_CURR_X_MIN_REPORT_PERIOD;
                customColorControlClusterServerAttributes.currentX.maxReportInterval = COLOR_CONTROL_CURR_X_MAX_REPORT_PERIOD;
                customColorControlClusterServerAttributes.currentX.reportableChange  = 0;
            break;
            </#if>

            <#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTY == true) >
            case ZCL_ZLL_CLUSTER_CURRENT_Y_SERVER_ATTRIBUTE_ID:
                customColorControlClusterServerAttributes.currentY.minReportInterval = COLOR_CONTROL_CURR_Y_MIN_REPORT_PERIOD;
                customColorControlClusterServerAttributes.currentY.maxReportInterval = COLOR_CONTROL_CURR_Y_MAX_REPORT_PERIOD;
                customColorControlClusterServerAttributes.currentY.reportableChange  = 0;
            break;
            </#if>

            <#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPMIREDS == true) >
            case ZCL_ZLL_CLUSTER_COLOR_TEMPERATURE_SERVER_ATTRIBUTE_ID:
                customColorControlClusterServerAttributes.colorTemperature.minReportInterval = COLOR_CONTROL_COLOR_TEMP_MIN_REPORT_PERIOD;
                customColorControlClusterServerAttributes.colorTemperature.maxReportInterval = COLOR_CONTROL_COLOR_TEMP_MAX_REPORT_PERIOD;
                customColorControlClusterServerAttributes.colorTemperature.reportableChange  = 0;
            break;
            </#if>
</#if>
<#if (ZB_DEVICE_TYPE == "ZIGBEE_ON_OFF_LIGHT") || (ZB_DEVICE_TYPE == "ZIGBEE_DIMMABLE_LIGHT") || (ZB_DEVICE_TYPE == "ZIGBEE_COLOR_LIGHT") || (ZB_DEVICE_TYPE == "ZIGBEE_EXTENDED_COLOR_LIGHT") || (ZB_DEVICE_TYPE == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")>
            <#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTHUE == true) >
            case ZCL_ZLL_CLUSTER_CURRENT_HUE_SERVER_ATTRIBUTE_ID:
                lightColorControlClusterServerAttributes.currentHue.minReportInterval = COLOR_CONTROL_CUURENT_HUE_MIN_REPORT_PERIOD;
                lightColorControlClusterServerAttributes.currentHue.maxReportInterval = COLOR_CONTROL_CUURENT_HUE_MAX_REPORT_PERIOD;
                lightColorControlClusterServerAttributes.currentHue.reportableChange  = 0;
            break;
            </#if>

            <#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTSATURATION == true) >
            case ZCL_ZLL_CLUSTER_CURRENT_SATURATION_SERVER_ATTRIBUTE_ID:
                lightColorControlClusterServerAttributes.currentSaturation.minReportInterval = COLOR_CONTROL_CURRENT_SAT_MIN_REPORT_PERIOD;
                lightColorControlClusterServerAttributes.currentSaturation.maxReportInterval = COLOR_CONTROL_CURRENT_SAT_MAX_REPORT_PERIOD;
                lightColorControlClusterServerAttributes.currentSaturation.reportableChange  = 0;
            break;
            </#if>

            <#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTX == true) >
            case ZCL_ZLL_CLUSTER_CURRENT_X_SERVER_ATTRIBUTE_ID:
                lightColorControlClusterServerAttributes.currentX.minReportInterval = COLOR_CONTROL_CURR_X_MIN_REPORT_PERIOD;
                lightColorControlClusterServerAttributes.currentX.maxReportInterval = COLOR_CONTROL_CURR_X_MAX_REPORT_PERIOD;
                lightColorControlClusterServerAttributes.currentX.reportableChange  = 0;
            break;
            </#if>

            <#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_CURRENTY == true) >
            case ZCL_ZLL_CLUSTER_CURRENT_Y_SERVER_ATTRIBUTE_ID:
                lightColorControlClusterServerAttributes.currentY.minReportInterval = COLOR_CONTROL_CURR_Y_MIN_REPORT_PERIOD;
                lightColorControlClusterServerAttributes.currentY.maxReportInterval = COLOR_CONTROL_CURR_Y_MAX_REPORT_PERIOD;
                lightColorControlClusterServerAttributes.currentY.reportableChange  = 0;
            break;
            </#if>

            <#if (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORTEMPMIREDS == true) >
            case ZCL_ZLL_CLUSTER_COLOR_TEMPERATURE_SERVER_ATTRIBUTE_ID:
                lightColorControlClusterServerAttributes.colorTemperature.minReportInterval = COLOR_CONTROL_COLOR_TEMP_MIN_REPORT_PERIOD;
                lightColorControlClusterServerAttributes.colorTemperature.maxReportInterval = COLOR_CONTROL_COLOR_TEMP_MAX_REPORT_PERIOD;
                lightColorControlClusterServerAttributes.colorTemperature.reportableChange  = 0;
            break;
            </#if>
</#if>
            default:
              break;
        }
           }
        }
        break;
</#if>
<#if IDENTIFY_CLUSTER_ENABLE == true>
        case CMD_ZCL_ATTR_IDENTIFY:
        {
            /* Command ZCL IdentifyAttributeEventInd */ 
            //Access - > event.eventData.zclAttributeData.addressing;
            //Access - > event.eventData.zclAttributeData.attributeId;
            //Access - > event.eventData.zclAttributeData.event;
            //appSnprintf("ZCL IdentifyAttributeEventInd\r\n");
        }
        break;
</#if>
<#if LEVELCONTROL_CLUSTER_ENABLE == true>
        case CMD_ZCL_ATTR_LEVEL_CONTROL:
        {
            /* Command ZCL LevelControlAttributeEventInd */
            //Access - > event.eventData.zclAttributeData.addressing;
            //Access - > event.eventData.zclAttributeData.attributeId;
            //Access - > event.eventData.zclAttributeData.event;
<#if (ZB_DEVICE_TYPE == "ZIGBEE_CUSTOM")> 
<#if (LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  && (LC_CURRENTLEVEL == true) >
            ZCL_AttributeEvent_t eventzcl = event.eventData.zclAttributeData.event;
            ZCL_AttributeId_t attributeId = event.eventData.zclAttributeData.attributeId;    
            if((ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == eventzcl) && \
                (ZCL_LEVEL_CONTROL_CLUSTER_CURRENT_LEVEL_ATTRIBUTE_ID == attributeId))
            {
                customLevelControlClusterServerAttributes.currentLevel.minReportInterval = LEVEL_CONTROL_VAL_MIN_REPORT_PERIOD;
                customLevelControlClusterServerAttributes.currentLevel.maxReportInterval = LEVEL_CONTROL_VAL_MAX_REPORT_PERIOD;
                customLevelControlClusterServerAttributes.currentLevel.reportableChange  = 0;
            }
</#if>
</#if>
<#if (ZB_DEVICE_TYPE == "ZIGBEE_ON_OFF_LIGHT") || (ZB_DEVICE_TYPE == "ZIGBEE_DIMMABLE_LIGHT") || (ZB_DEVICE_TYPE == "ZIGBEE_COLOR_LIGHT") || (ZB_DEVICE_TYPE == "ZIGBEE_EXTENDED_COLOR_LIGHT") || (ZB_DEVICE_TYPE == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")>
<#if (LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  && (LC_CURRENTLEVEL == true) > 
            ZCL_AttributeEvent_t eventzcl = event.eventData.zclAttributeData.event;
            ZCL_AttributeId_t attributeId = event.eventData.zclAttributeData.attributeId;    
            if((ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == eventzcl) && \
                (ZCL_LEVEL_CONTROL_CLUSTER_CURRENT_LEVEL_ATTRIBUTE_ID == attributeId))
            {
                lightLevelControlClusterServerAttributes.currentLevel.minReportInterval = LEVEL_CONTROL_VAL_MIN_REPORT_PERIOD;
                lightLevelControlClusterServerAttributes.currentLevel.maxReportInterval = LEVEL_CONTROL_VAL_MAX_REPORT_PERIOD;
                lightLevelControlClusterServerAttributes.currentLevel.reportableChange  = 0;
            }
</#if>
</#if>
        }
        break;
</#if>
<#if ONOFF_CLUSTER_ENABLE == true>
        case CMD_ZCL_ATTR_ONOFF:
        {
            /* Command ZCL OnOffAttributeEventInd */
            //Access - > event.eventData.zclAttributeData.addressing;
            //Access - > event.eventData.zclAttributeData.attributeId;
            //Access - > event.eventData.zclAttributeData.event; 
<#if (ZB_DEVICE_TYPE == "ZIGBEE_CUSTOM")>
<#if (ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "CLIENT")  && (OC_ONOFF == true) >
            ZCL_AttributeEvent_t eventzcl = event.eventData.zclAttributeData.event;
            ZCL_AttributeId_t attributeId = event.eventData.zclAttributeData.attributeId;  
            if((ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == eventzcl) && \
                (ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID == attributeId))
            {
                customOnOffClusterServerAttributes.onOff.minReportInterval = ONOFF_VAL_MIN_REPORT_PERIOD;
                customOnOffClusterServerAttributes.onOff.maxReportInterval = ONOFF_VAL_MAX_REPORT_PERIOD;
                customOnOffClusterServerAttributes.onOff.reportableChange  = 0;
            }
</#if>
</#if>
<#if (ZB_DEVICE_TYPE == "ZIGBEE_ON_OFF_LIGHT") || (ZB_DEVICE_TYPE == "ZIGBEE_DIMMABLE_LIGHT") || (ZB_DEVICE_TYPE == "ZIGBEE_COLOR_LIGHT") || (ZB_DEVICE_TYPE == "ZIGBEE_EXTENDED_COLOR_LIGHT") || (ZB_DEVICE_TYPE == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")>
<#if (ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "CLIENT")  && (OC_ONOFF == true) >  
            ZCL_AttributeEvent_t eventzcl = event.eventData.zclAttributeData.event;
            ZCL_AttributeId_t attributeId = event.eventData.zclAttributeData.attributeId; 
            if((ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == eventzcl) && \
                (ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID == attributeId))
            {
                lightOnOffClusterServerAttributes.onOff.minReportInterval = ONOFF_VAL_MIN_REPORT_PERIOD;
                lightOnOffClusterServerAttributes.onOff.maxReportInterval = ONOFF_VAL_MAX_REPORT_PERIOD;
                lightOnOffClusterServerAttributes.onOff.reportableChange  = 0;
            }
</#if>
</#if>
        }
        break;
</#if>
<#if OCCUPANCYSENSING_CLUSTER_ENABLE == true>
        case CMD_ZCL_ATTR_OCCUPANCY:
        {
            /* Command ZCL OccupancyAttributeEventInd */
            //Access - > event.eventData.zclAttributeData.addressing;
            //Access - > event.eventData.zclAttributeData.attributeId;
            //Access - > event.eventData.zclAttributeData.event;
<#if (ZB_DEVICE_TYPE == "ZIGBEE_CUSTOM")>
<#if (OCCUPANCYSENSING_CLUSTER_CS != "CLIENT")  && (OC_OCCUPANCY == true)>
            ZCL_AttributeEvent_t eventzcl = event.eventData.zclAttributeData.event;
            ZCL_AttributeId_t attributeId = event.eventData.zclAttributeData.attributeId;
            if ((ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == eventzcl) && \
                (ZCL_OCCUPANCY_SENSING_CLUSTER_OCCUPANCY_SERVER_ATTRIBUTE_ID == attributeId))
            {
                customOccupancySensingClusterServerAttributes.occupancy.minReportInterval = OCCUPANCY_SENSING_VAL_MIN_REPORT_PERIOD;
                customOccupancySensingClusterServerAttributes.occupancy.maxReportInterval = OCCUPANCY_SENSING_VAL_MAX_REPORT_PERIOD;
                customOccupancySensingClusterServerAttributes.occupancy.reportableChange = 0;     
            }
</#if>
</#if>
<#if (ZB_DEVICE_TYPE == "ZIGBEE_MULTI_SENSOR")>
<#if (OCCUPANCYSENSING_CLUSTER_CS != "CLIENT")  && (OC_OCCUPANCY == true)>
            ZCL_AttributeEvent_t eventzcl = event.eventData.zclAttributeData.event;
            ZCL_AttributeId_t attributeId = event.eventData.zclAttributeData.attributeId;
            if ((ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == eventzcl) && \
                (ZCL_OCCUPANCY_SENSING_CLUSTER_OCCUPANCY_SERVER_ATTRIBUTE_ID == attributeId))
            {
                osOccupancySensingClusterServerAttributes.occupancy.minReportInterval = OCCUPANCY_SENSING_VAL_MIN_REPORT_PERIOD;
                osOccupancySensingClusterServerAttributes.occupancy.maxReportInterval = OCCUPANCY_SENSING_VAL_MAX_REPORT_PERIOD;
                osOccupancySensingClusterServerAttributes.occupancy.reportableChange = 0;     
            }
</#if>
</#if>
<#if (ZB_DEVICE_TYPE == "ZIGBEE_THERMOSTAT")>
<#if (OCCUPANCYSENSING_CLUSTER_CS != "CLIENT")  && (OC_OCCUPANCY == true)>
            ZCL_AttributeEvent_t eventzcl = event.eventData.zclAttributeData.event;
            ZCL_AttributeId_t attributeId = event.eventData.zclAttributeData.attributeId;
            if ((ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == eventzcl) && \
                (ZCL_OCCUPANCY_SENSING_CLUSTER_OCCUPANCY_SERVER_ATTRIBUTE_ID == attributeId))
            {
                thOccupancySensingClusterServerAttributes.occupancy.minReportInterval = OCCUPANCY_SENSING_VAL_MIN_REPORT_PERIOD;
                thOccupancySensingClusterServerAttributes.occupancy.maxReportInterval = OCCUPANCY_SENSING_VAL_MAX_REPORT_PERIOD;
                thOccupancySensingClusterServerAttributes.occupancy.reportableChange = 0;     
            }
</#if>
</#if>
        }
        break;
</#if>
<#if ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE == true>
        case CMD_ZCL_ATTR_ILLUMINANCE_MEASUREMENT:
        {
            /* Command ZCL OnOffAttributeEventInd */
            //Access - > event.eventData.zclAttributeData.addressing;
            //Access - > event.eventData.zclAttributeData.attributeId;
            //Access - > event.eventData.zclAttributeData.event;
<#if (ZB_DEVICE_TYPE == "ZIGBEE_CUSTOM")>
<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT")  && (IMC_MEASUREDVALUE == true)>
            ZCL_AttributeEvent_t eventzcl = event.eventData.zclAttributeData.event;
            ZCL_AttributeId_t attributeId = event.eventData.zclAttributeData.attributeId;
            if((ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == eventzcl) && \
                (ZCL_ILLUMINANCE_MEASUREMENT_CLUSTER_MEASURED_VALUE_SERVER_ATTRIBUTE_ID == attributeId))
            {
                customIlluminanceMeasurementClusterServerAttributes.measuredValue.minReportInterval = ILLUMINANCE_MEASUREMENT_VAL_MIN_REPORT_PERIOD;
                customIlluminanceMeasurementClusterServerAttributes.measuredValue.maxReportInterval = ILLUMINANCE_MEASUREMENT_VAL_MAX_REPORT_PERIOD;
                customIlluminanceMeasurementClusterServerAttributes.measuredValue.reportableChange = 0;
            }
</#if>
</#if>
<#if (ZB_DEVICE_TYPE == "ZIGBEE_MULTI_SENSOR")>
<#if (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "CLIENT")  && (IMC_MEASUREDVALUE == true)>
            ZCL_AttributeEvent_t eventzcl = event.eventData.zclAttributeData.event;
            ZCL_AttributeId_t attributeId = event.eventData.zclAttributeData.attributeId;
            if((ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == eventzcl) && \
                (ZCL_ILLUMINANCE_MEASUREMENT_CLUSTER_MEASURED_VALUE_SERVER_ATTRIBUTE_ID == attributeId))
            {
                lsIlluminanceMeasurementClusterServerAttributes.measuredValue.minReportInterval = ILLUMINANCE_MEASUREMENT_VAL_MIN_REPORT_PERIOD;
                lsIlluminanceMeasurementClusterServerAttributes.measuredValue.maxReportInterval = ILLUMINANCE_MEASUREMENT_VAL_MAX_REPORT_PERIOD;
                lsIlluminanceMeasurementClusterServerAttributes.measuredValue.reportableChange = 0;
            }
</#if>
</#if>
        }
        break;
 </#if>
<#if WATERCONTENTMEASUREMENT_CLUSTER_ENABLE == true>
        case CMD_ZCL_ATTR_HUMIDITY_MEASUREMENT:
        {
            /* Command ZCL CustomHumidityMeasurementReportInd Prints Report Value */
            //Access - > event.zclAttributeData.zclEventData.addressing;
            //Access - > event.zclAttributeData.zclEventData.attributeId;
            //Access - > event.zclAttributeData.zclEventData.event;           
            //appSnprintf("ZCL HS Humidity Measurement Attr Ind\r\n");
<#if (ZB_DEVICE_TYPE == "ZIGBEE_THERMOSTAT")>
            ZCL_AttributeEvent_t eventzcl = event.eventData.zclAttributeData.event;
            ZCL_AttributeId_t attributeId = event.eventData.zclAttributeData.attributeId;
            if ((ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == eventzcl) && \
                (ZCL_HUMIDITY_MEASUREMENT_CLUSTER_SERVER_MEASURED_VALUE_ATTRIBUTE_ID == attributeId))
            {
              thHumidityMeasurementClusterServerAttributes.measuredValue.minReportInterval = HUMIDITY_MEASUREMENT_VAL_MIN_REPORT_PERIOD;
              thHumidityMeasurementClusterServerAttributes.measuredValue.maxReportInterval = HUMIDITY_MEASUREMENT_VAL_MAX_REPORT_PERIOD;
              thHumidityMeasurementClusterServerAttributes.measuredValue.reportableChange  = 0;
            }
</#if>
<#if (ZB_DEVICE_TYPE == "ZIGBEE_MULTI_SENSOR")>	
            ZCL_AttributeEvent_t eventzcl = event.eventData.zclAttributeData.event;
            ZCL_AttributeId_t attributeId = event.eventData.zclAttributeData.attributeId;
            if ((ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == eventzcl) && \
                (ZCL_HUMIDITY_MEASUREMENT_CLUSTER_SERVER_MEASURED_VALUE_ATTRIBUTE_ID == attributeId))
            {
              hsHumidityMeasurementClusterServerAttributes.measuredValue.minReportInterval = HUMIDITY_MEASUREMENT_VAL_MIN_REPORT_PERIOD;
              hsHumidityMeasurementClusterServerAttributes.measuredValue.maxReportInterval = HUMIDITY_MEASUREMENT_VAL_MAX_REPORT_PERIOD;
              hsHumidityMeasurementClusterServerAttributes.measuredValue.reportableChange  = 0;
            }
</#if>			
        }
        break;
</#if>
<#if TIME_CLUSTER_ENABLE == true>
        case CMD_ZCL_ATTR_TIME:
        {
            /* Command ZCL Time attribute indication */         
            if(event.eventData.zclAttributeData.attributeId == ZCL_TIME_CLUSTER_SERVER_TIME_ATTRIBUTE_ID && 
               event.eventData.zclAttributeData.event == ZCL_WRITE_ATTRIBUTE_EVENT)
            {
	          appSnprintf("Standard and local time updated by client\r\n");
            }
        }
        break;
</#if>
<#if THERMOSTATUI_CLUSTER_ENABLE == true>
        case CMD_ZCL_ATTR_THERMOSTAT_UI_CONF:
        {
<#if (ZB_DEVICE_TYPE == "ZIGBEE_THERMOSTAT")>
            /* Command ZCL Thermostat UI conf attribute indication*/
<#if (THERMOSTATUI_CLUSTER_CS != "CLIENT")>			
            if (ZCL_WRITE_ATTRIBUTE_EVENT == event.eventData.zclAttributeData.event)
            {
              switch(event.eventData.zclAttributeData.attributeId)
              {
<#if (TUIC_TEMPDISPLAYMODE == true) && (TC_LOCALTEMP == true)>  
                case ZCL_THERMOSTAT_UI_CONF_CLUSTER_TEMPERATURE_DISPLAY_MODE_SERVER_ATTRIBUTE_ID:
                {
                  if(thThermostatUiConfClusterServerAttributes.temperatureDisplayMode.value == ZCL_TEMPERATURE_IN_CELSIUS)
                  {          
                    appSnprintf(" Temp in Celcius = %d\r\n",thThermostatClusterServerAttributes.localTemperature.value);           
                  }
                  else
                  {
                    appSnprintf(" Temp in Fahr = %d\r\n",thTranslateZclCelciusTemptoFahr(thThermostatClusterServerAttributes.localTemperature.value));
                  }
                }
                break;
</#if>
<#if (TUIC_KEYPADLOCKOUT == true)> 
                case ZCL_THERMOSTAT_UI_CONF_CLUSTER_KEYPAD_LOCKOUT_SERVER_ATTRIBUTE_ID:
                {
                  appSnprintf(" Keypad Lock Attribute = 0x%x\r\n",thThermostatUiConfClusterServerAttributes.keypadLockOut.value);
                }
                break;
</#if>
<#if (TUIC_SCHEDULEPROGRAMVISIBILITY == true)>    
                case ZCL_THERMOSTAT_UI_CONF_CLUSTER_SCHEDULE_PROGRAMMING_VISIBILITY_SERVER_ATTRIBUTE_ID:
                {
                  appSnprintf(" Schedule Programming Visibility Attribute = 0x%x\r\n",thThermostatUiConfClusterServerAttributes.scheduleProgVisibility.value);
                }
                break;
</#if>
          default:
                  break;
              }
            }

</#if>

<#if (ZB_DEVICE_TYPE == "ZIGBEE_CUSTOM")>
            /* Command ZCL Thermostat UI conf attribute indication*/
<#if (THERMOSTATUI_CLUSTER_CS != "CLIENT")>			
            if (ZCL_WRITE_ATTRIBUTE_EVENT == event.eventData.zclAttributeData.event)
            {
              switch(event.eventData.zclAttributeData.attributeId)
              {		  
<#if (TUIC_TEMPDISPLAYMODE == true) && (TC_LOCALTEMP == true)>  
                case ZCL_THERMOSTAT_UI_CONF_CLUSTER_TEMPERATURE_DISPLAY_MODE_SERVER_ATTRIBUTE_ID:
                {
                  if(customThermostatUiConfClusterServerAttributes.temperatureDisplayMode.value == ZCL_TEMPERATURE_IN_CELSIUS)
                  {          
                    appSnprintf(" Temp in Celcius = %d\r\n",customThermostatClusterServerAttributes.localTemperature.value);           
                  }
                  else
                  {
                    appSnprintf(" Temp in Fahr = %d\r\n",customTranslateZclCelciusTemptoFahr(customThermostatClusterServerAttributes.localTemperature.value));
                  }
                }
                break;
</#if>
</#if>
<#if (TUIC_KEYPADLOCKOUT == true)> 
                case ZCL_THERMOSTAT_UI_CONF_CLUSTER_KEYPAD_LOCKOUT_SERVER_ATTRIBUTE_ID:
                {
                  appSnprintf(" Keypad Lock Attribute = 0x%x\r\n",customThermostatUiConfClusterServerAttributes.keypadLockOut.value);
                }
                break;
</#if>
<#if (TUIC_SCHEDULEPROGRAMVISIBILITY == true)>    
                case ZCL_THERMOSTAT_UI_CONF_CLUSTER_SCHEDULE_PROGRAMMING_VISIBILITY_SERVER_ATTRIBUTE_ID:
                {
                  appSnprintf(" Schedule Programming Visibility Attribute = 0x%x\r\n",customThermostatUiConfClusterServerAttributes.scheduleProgVisibility.value);
                }
                break;
</#if>
                default:
                  break;
              }
            }
</#if>
</#if>
        }
        break;
</#if>
<#if THERMOSTAT_CLUSTER_ENABLE == true>
        case CMD_ZCL_ATTR_THERMOSTAT:
        {
          /* Command ZCL Thermostat Attribute Indication */
          //Access - > eventItem.eventData.zclAttributeData.addressing;
          //Access - > eventItem.eventData.zclAttributeData.attributeId;
          //Access - > eventItem.eventData.zclAttributeData.event;  
<#if (ZB_DEVICE_TYPE == "ZIGBEE_THERMOSTAT")>		  
          ZCL_AttributeId_t attributeId;
          ZCL_AttributeEvent_t zclEvent;
          attributeId = event.eventData.zclAttributeData.attributeId;
          zclEvent = event.eventData.zclAttributeData.event;
          if(ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == zclEvent)
          {
           switch(attributeId)
           {
             <#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_LOCALTEMP == true)>      
              case ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID:
                thThermostatClusterServerAttributes.localTemperature.minReportInterval = THERMOSTAT_LOCAL_TEMPERATURE_MIN_REPORT_PERIOD;
                thThermostatClusterServerAttributes.localTemperature.maxReportInterval = THERMOSTAT_LOCAL_TEMPERATURE_MAX_REPORT_PERIOD;
                thThermostatClusterServerAttributes.localTemperature.reportableChange = 0;    
              break;
            </#if>

            <#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_PICOOLINGDEMAND == true)>        
            case ZCL_THERMOSTAT_CLUSTER_PI_COOLING_DEMAND_SERVER_ATTRIBUTE_ID:
              thThermostatClusterServerAttributes.PICoolingDemand.minReportInterval = THERMOSTAT_PI_CO0LING_DEMAND_MIN_REPORT_PERIOD;
              thThermostatClusterServerAttributes.PICoolingDemand.maxReportInterval = THERMOSTAT_PI_CO0LING_DEMAND_MAX_REPORT_PERIOD;
              thThermostatClusterServerAttributes.PICoolingDemand.reportableChange = 0;
            break;
           </#if>  
           <#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_PIHEATINGDEMAND == true)>        
           case ZCL_THERMOSTAT_CLUSTER_PI_HEATING_DEMAND_SERVER_ATTRIBUTE_ID:
             thThermostatClusterServerAttributes.PIHeatingDemand.minReportInterval = THERMOSTAT_PI_HEATING_DEMAND_MIN_REPORT_PERIOD;
             thThermostatClusterServerAttributes.PIHeatingDemand.maxReportInterval = THERMOSTAT_PI_HEATING_DEMAND_MAX_REPORT_PERIOD;
             thThermostatClusterServerAttributes.PIHeatingDemand.reportableChange = 0;
           break;
            </#if>
        
      default :
        break;
      
            }
          }
</#if>
<#if (ZB_DEVICE_TYPE == "ZIGBEE_CUSTOM")>
          ZCL_AttributeId_t attributeId;
          ZCL_AttributeEvent_t zclEvent;
          attributeId = event.eventData.zclAttributeData.attributeId;
          zclEvent = event.eventData.zclAttributeData.event;
          if(ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == zclEvent)
          {
            switch(attributeId)
            {
              <#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_LOCALTEMP == true)>      
              case ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID:
                customThermostatClusterServerAttributes.localTemperature.minReportInterval = THERMOSTAT_LOCAL_TEMPERATURE_MIN_REPORT_PERIOD;
                customThermostatClusterServerAttributes.localTemperature.maxReportInterval = THERMOSTAT_LOCAL_TEMPERATURE_MAX_REPORT_PERIOD;
                customThermostatClusterServerAttributes.localTemperature.reportableChange = 0;    
              break;
              </#if>

              <#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_PICOOLINGDEMAND == true)>        
              case ZCL_THERMOSTAT_CLUSTER_PI_COOLING_DEMAND_SERVER_ATTRIBUTE_ID:
              customThermostatClusterServerAttributes.PICoolingDemand.minReportInterval = THERMOSTAT_PI_CO0LING_DEMAND_MIN_REPORT_PERIOD;
              customThermostatClusterServerAttributes.PICoolingDemand.maxReportInterval = THERMOSTAT_PI_CO0LING_DEMAND_MAX_REPORT_PERIOD;
              customThermostatClusterServerAttributes.PICoolingDemand.reportableChange = 0;
             break;
             </#if>

             <#if (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (TC_PIHEATINGDEMAND == true)>        
             case ZCL_THERMOSTAT_CLUSTER_PI_HEATING_DEMAND_SERVER_ATTRIBUTE_ID:
               customThermostatClusterServerAttributes.PIHeatingDemand.minReportInterval = THERMOSTAT_PI_HEATING_DEMAND_MIN_REPORT_PERIOD;
               customThermostatClusterServerAttributes.PIHeatingDemand.maxReportInterval = THERMOSTAT_PI_HEATING_DEMAND_MAX_REPORT_PERIOD;
               customThermostatClusterServerAttributes.PIHeatingDemand.reportableChange = 0;
             break;
             </#if>
            default :
            break;

            }
          }
</#if>
        }
        break;
</#if>
<#if TEMPERATUREMEASUREMENT_CLUSTER_ENABLE == true>
        case CMD_ZCL_ATTR_TEMPERATURE_MEASUREMENT:
        {
            /* Command ZCL Temperature measurement Attribute Indication */
            //Access - > eventItem.eventData.zclAttributeData.addressing;
            //Access - > eventItem.eventData.zclAttributeData.attributeId;
            //Access - > eventItem.eventData.zclAttributeData.event;
<#if (ZB_DEVICE_TYPE == "ZIGBEE_CUSTOM")>
           <#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")  && (TMC_MEASUREDVALUE == true)>   
           if ((ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == event.eventData.zclAttributeData.event) && \
          (ZCL_TEMPERATURE_MEASUREMENT_CLUSTER_SERVER_MEASURED_VALUE_ATTRIBUTE_ID == event.eventData.zclAttributeData.attributeId))
           {    
              customTemperatureMeasurementClusterServerAttributes.measuredValue.minReportInterval = TEMPERATURE_MEASUREMENT_VAL_MIN_REPORT_PERIOD;//User can change the min report period
              customTemperatureMeasurementClusterServerAttributes.measuredValue.maxReportInterval = TEMPERATURE_MEASUREMENT_VAL_MAX_REPORT_PERIOD;//User can change the max report period
              customTemperatureMeasurementClusterServerAttributes.measuredValue.reportableChange = 0;     
           }
          </#if>
</#if>
<#if (ZB_DEVICE_TYPE == "ZIGBEE_THERMOSTAT")>
           <#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")  && (TMC_MEASUREDVALUE == true)>   
           if ((ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == event.eventData.zclAttributeData.event) && \
           (ZCL_TEMPERATURE_MEASUREMENT_CLUSTER_SERVER_MEASURED_VALUE_ATTRIBUTE_ID == event.eventData.zclAttributeData.attributeId))
           {    
             thTemperatureMeasurementClusterServerAttributes.measuredValue.minReportInterval = TEMPERATURE_MEASUREMENT_VAL_MIN_REPORT_PERIOD;//User can change the min report period
             thTemperatureMeasurementClusterServerAttributes.measuredValue.maxReportInterval = TEMPERATURE_MEASUREMENT_VAL_MAX_REPORT_PERIOD;//User can change the max report period
             thTemperatureMeasurementClusterServerAttributes.measuredValue.reportableChange = 0;     
           }
           </#if>
</#if>
<#if (ZB_DEVICE_TYPE == "ZIGBEE_MULTI_SENSOR")>
          <#if (TEMPERATUREMEASUREMENT_CLUSTER_CS != "CLIENT")  && (TMC_MEASUREDVALUE == true)>
          if ((ZCL_CONFIGURE_DEFAULT_ATTRIBUTE_REPORTING_EVENT == event.eventData.zclAttributeData.event) && \
          (ZCL_TEMPERATURE_MEASUREMENT_CLUSTER_SERVER_MEASURED_VALUE_ATTRIBUTE_ID == event.eventData.zclAttributeData.attributeId))
          {
            tsTemperatureMeasurementClusterServerAttributes.measuredValue.minReportInterval = TEMPERATURE_MEASUREMENT_VAL_MIN_REPORT_PERIOD;//User can change the min report period
            tsTemperatureMeasurementClusterServerAttributes.measuredValue.maxReportInterval = TEMPERATURE_MEASUREMENT_VAL_MAX_REPORT_PERIOD;//User can change the max report period
            tsTemperatureMeasurementClusterServerAttributes.measuredValue.reportableChange = 0;     
          }
          </#if>
</#if>
        }
        break;
</#if>
<#if FANCONTROL_CLUSTER_ENABLE == true>
        case CMD_ZCL_ATTR_FANCONTROL:
        {   
            //Access - > event.eventData.zclAttributeData.addressing;
            //Access - > event.eventData.zclAttributeData.attributeId;
            //Access - > event.eventData.zclAttributeData.event;   		
            //appSnprintf("<-Attr ID 0x%x event 0x%x\r\n",event.eventData.zclAttributeData.attributeId, event.eventData.zclAttributeData.event);
        }
        break;
</#if>
<#if IASZONE_CLUSTER_ENABLE == true>
        case CMD_ZCL_ATTR_IASZONE:
        {
            /* command zcl IASACE attribute indication */
            //Access - > event.eventData.zclAttributeData.addressing;
            //Access - > event.eventData.zclAttributeData.attributeId;
            //Access - > event.eventData.zclAttributeData.event;               
            //appSnprintf("<-Attr ID 0x%x event 0x%x\r\n",event.eventData.zclAttributeData.attributeId, event.eventData.zclAttributeData.event);
        }
        break;
</#if>
<#if ((ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "SERVER"))>
        case CMD_ZCL_REPORTING_ONOFF:
        {
            /* Command ZCL OnOffReportInd */
            //Access - > event.eventData.zclAttributeData.addressing;
            //Access - > event.eventData.zclAttributeData.payloadLength;
            //Access - > event.eventData.zclAttributeData.payload;
            ZCL_Report_t *rep = (ZCL_Report_t *)event.eventData.zclEventData.payload;
            appSnprintf("<-On/Off Attr Report: Value = 0x%x\r\n", (int)rep->value[0]);
        }
        break;
</#if>
<#if ((ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE == true) && (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "SERVER"))>
        case CMD_ZCL_REPORTING_LIGHT_SENSOR:
        {
            /* Command ZCL LightSensorReportInd */
            //Access - > event.eventData.zclAttributeData.addressing;
            //Access - > event.eventData.zclAttributeData.payloadLength;
            //Access - > event.eventData.zclAttributeData.payload;
            ZCL_Report_t *rep = (ZCL_Report_t *)event.eventData.zclEventData.payload;;
            uint16_t reportValue;
            memcpy(&reportValue, &rep->value[0], sizeof(uint16_t));
            appSnprintf("<-Light Sensor Attr Report: Value = 0x%x\r\n", reportValue);
        }
        break;
</#if>
<#if ((LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "SERVER"))>
        case CMD_ZCL_REPORTING_LEVEL:
        {
            /* Command ZCL LevelReportInd( */
            //Access - > event.eventData.zclAttributeData.addressing;
            //Access - > event.eventData.zclAttributeData.payloadLength;
            //Access - > event.eventData.zclAttributeData.payload;
            ZCL_Report_t *rep = (ZCL_Report_t *)event.eventData.zclEventData.payload;
            appSnprintf("<-Level Control Attr Report: Value = 0x%x\r\n", (int)rep->value[0]);
        }
        break;
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "SERVER"))>
        case CMD_ZCL_REPORTING_COLOR_CONTROL:
        {
            /* ZCL Command ZCL STOP MOVE SET received */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;
            do  //Possibilities of getting more than one report at a time.
            {
                ZCL_Report_t *rep = (ZCL_Report_t *)(event.eventData.zclEventData.payload);
                uint16_t reportValue = 0;
                if(rep->type == ZCL_U8BIT_DATA_TYPE_ID)
                {
                    memcpy(&reportValue, (event.eventData.zclEventData.payload+ sizeof(ZCL_AttributeId_t)+ sizeof(rep->type)), sizeof(uint8_t));
                }
                else
                {
                    memcpy(&reportValue, (event.eventData.zclEventData.payload+ sizeof(ZCL_AttributeId_t)+ sizeof(rep->type)), sizeof(uint16_t));
                }
                appSnprintf("<-Color Control Attr (0x%x) Report: Value = 0x%x\r\n", (unsigned)rep->id, reportValue);
                
                if((event.eventData.zclEventData.payloadLength >= 4))
                {
                    if(rep->type == ZCL_U8BIT_DATA_TYPE_ID)//Attribute data is of 1 byte
                    {
                        event.eventData.zclEventData.payloadLength = event.eventData.zclEventData.payloadLength - sizeof(uint32_t);  // Skip the first report 
                        event.eventData.zclEventData.payload = (event.eventData.zclEventData.payload)+ sizeof(uint32_t);             // Align the pointer to read next        
                    }
                    else // Attribute data is of 2 byte
                    {
                        event.eventData.zclEventData.payloadLength = event.eventData.zclEventData.payloadLength - sizeof(uint32_t) - sizeof(uint8_t); // Skip the first report 
                        event.eventData.zclEventData.payload = (event.eventData.zclEventData.payload) + sizeof(uint32_t) + sizeof(uint8_t);          // Align the pointer to read next            
                    }
               }
            }while(event.eventData.zclEventData.payloadLength);   
        }
        break;
</#if>
<#if ((OCCUPANCYSENSING_CLUSTER_ENABLE == true) && (OCCUPANCYSENSING_CLUSTER_CS != "SERVER"))>
        case CMD_ZCL_REPORTING_OCCUPANCY:
        {
            /* Command ZCL LevelReportInd( */
            //Access - > event.eventData.zclAttributeData.addressing;
            //Access - > event.eventData.zclAttributeData.payloadLength;
            //Access - > event.eventData.zclAttributeData.payload;
            ZCL_Report_t *rep = (ZCL_Report_t *)event.eventData.zclEventData.payload;
            appSnprintf("<-Occupancy Sensor Attr Report: Value = 0x%x\r\n", (int)rep->value[0]);
        }
        break;
</#if>
<#if ((THERMOSTAT_CLUSTER_ENABLE == true) && (THERMOSTAT_CLUSTER_CS != "SERVER"))>
        case CMD_ZCL_REPORTING_THERMOSTAT:
        {
            /* Command ZCL Thermostat Report Indication */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;                
            //appSnprintf("ZCL Report TH Thermostat Ind\r\n");
            ZCL_Report_t *rep = (ZCL_Report_t *)event.eventData.zclEventData.payload;
            int16_t reportValue = 0;
<#if (ZB_DEVICE_TYPE == "ZIGBEE_COMBINED_INTERFACE") || (ZB_DEVICE_TYPE == "ZIGBEE_CUSTOM") >
            if(rep->id == ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID || (rep->id == ZCL_THERMOSTAT_CLUSTER_PI_COOLING_DEMAND_SERVER_ATTRIBUTE_ID)
            || (rep->id == ZCL_THERMOSTAT_CLUSTER_PI_HEATING_DEMAND_SERVER_ATTRIBUTE_ID))
            {
              if(rep->id == ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID)
              {
                memcpy(&reportValue, &rep->value[0], sizeof(int16_t));
                appSnprintf("<-Thermostat Attr (0x%x) Report: Value = %d.%dC\r\n", rep->id, (int)(reportValue/THERMOSTAT_LOCAL_TEMPERATURE_SCALE),(int)(reportValue%THERMOSTAT_LOCAL_TEMPERATURE_SCALE));
              }
              else
              {
                memcpy(&reportValue, &rep->value[0], sizeof(uint8_t));
                appSnprintf("<-Thermostat Attr (0x%x) Report: Value = 0x%x\r\n", rep->id, (uint8_t)reportValue);
              }
            }
            else if(rep->id == ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID)
            {
              setPoint_t *payload = (setPoint_t*)rep;
    
              appSnprintf("<-Setpoints changed on Thermostat:\r\n");
              memcpy(&reportValue, &rep->value[1], sizeof(int16_t));

              appSnprintf("#cool setpoint: Value = %d.%d\r\n", (int)(reportValue/THERMOSTAT_LOCAL_TEMPERATURE_SCALE),(int)(reportValue%THERMOSTAT_LOCAL_TEMPERATURE_SCALE));
              payload++;

              memcpy(&reportValue, &payload->value, sizeof(int16_t));
              appSnprintf("#heat setpoint: Value = %d.%d\r\n", (int)(reportValue/THERMOSTAT_LOCAL_TEMPERATURE_SCALE),(int)(reportValue%THERMOSTAT_LOCAL_TEMPERATURE_SCALE));
            }
</#if>
<#if (ZB_DEVICE_TYPE == "ZIGBEE_THERMOSTAT") || (ZB_DEVICE_TYPE == "ZIGBEE_CUSTOM")>
<#if (THERMOSTAT_CLUSTER_CS != "CLIENT")>
            #if defined(THERMOSTAT_EXTERNAL_TEMPERATURE_SENSOR_NODE_AVAILABLE)
             if(rep->id == ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID)
             {
               memcpy(&reportValue, &rep->value[0], sizeof(int16_t));
               thermostatUpdateServerAttributes(reportValue);
               #ifdef ZCL_THERMOSTAT_CLUSTER_INCLUDE_OPTIONAL_ATTRIBUTES  
                 thermostatUpdateThRunningMode(reportValue);
               #endif
               appSnprintf("<-Thermostat Attr (0x%x) Report: Value = %d.%dC\r\n", (unsigned)rep->id, (int)(reportValue/THERMOSTAT_LOCAL_TEMPERATURE_SCALE),(int)(reportValue%THERMOSTAT_LOCAL_TEMPERATURE_SCALE));
              }
              else if ((rep->id == ZCL_THERMOSTAT_CLUSTER_PI_COOLING_DEMAND_SERVER_ATTRIBUTE_ID) || (rep->id == ZCL_THERMOSTAT_CLUSTER_PI_HEATING_DEMAND_SERVER_ATTRIBUTE_ID))
              {
                memcpy(&reportValue, &rep->value[0], sizeof(uint8_t));
                appSnprintf("<-Thermostat Attr (0x%x) Report: Value = 0x%x\r\n", rep->id, (uint8_t)reportValue);
              }
             #endif
</#if>
</#if>
        }
        break;
</#if>
<#if ((TEMPERATUREMEASUREMENT_CLUSTER_ENABLE == true) && (TEMPERATUREMEASUREMENT_CLUSTER_CS != "SERVER"))>
        case CMD_ZCL_REPORTING_TEMPERATURE_MEASUREMENT:
        {
            /* Command ZCL Thermostat Report Indication */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;              
            ZCL_Report_t *rep = (ZCL_Report_t *)event.eventData.zclEventData.payload;
            int16_t reportValue;
            memcpy(&reportValue, &rep->value[0], sizeof(int16_t));
            appSnprintf( "<-Temperature Measurement Attr Report: Value = 0x%02hx\r\n", reportValue);
        }
        break;
</#if>
<#if ((WATERCONTENTMEASUREMENT_CLUSTER_ENABLE == true) && (WATERCONTENTMEASUREMENT_CLUSTER_CS != "SERVER"))>
        case CMD_ZCL_REPORTING_HUMIDITY_MEASUREMENT:
        {
            /* Command ZCL Humidity Measurement Report Indication */
            //Access - > event.eventData.zclEventData.addressing;
            //Access - > event.eventData.zclEventData.payloadLength;
            //Access - > event.eventData.zclEventData.payload;              
            ZCL_Report_t *rep = (ZCL_Report_t *)event.eventData.zclEventData.payload;
            uint16_t reportValue;
            memcpy(&reportValue, &rep->value[0], sizeof(uint16_t));
            appSnprintf( "<-Relative Humidity Measurement Attr Report: Value = 0x%x\r\n", reportValue);
        }
        break;
</#if>
        default:
        break;
    }
}