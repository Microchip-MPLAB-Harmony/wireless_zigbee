/*******************************************************************************
  Application Zigbee Handler Header File

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

#ifndef APPZIGBEEHANDLER_H
#define APPZIGBEEHANDLER_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <definitions.h>
#include <z3device/common/include/z3Device.h>
// *****************************************************************************
// *****************************************************************************
// Section: Macro definitions
// *****************************************************************************

// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************

/*******************************************************************************
 Application Zigbee Major Types of Events Trigger
******************************************************************************/
typedef enum
{
    /* BSP Events */
    EVENT_BSP,

    /* Cluster Events */
    EVENT_CLUSTER,

    /* Zigbee Events */
    EVENT_ZIGBEE,
} APP_Zigbee_EventGroup_t;

/*******************************************************************************
 Application Zigbee Events
******************************************************************************/
typedef enum
{
    /* Events in the BSP Group Event */
    /* LEDs Init/Open */
    CMD_LED_OPEN = 0,
    /* LED On Event */
    CMD_LED_ON,
    /* LED On Event */
    CMD_LED_OFF,
    /* LED Toggle Event */
    CMD_LED_TOGGLE,
    /* LED BRIGHTNESS Event */
    CMD_LED_BRIGHTNESS,
    /* LED Set Color HS Event */
    CMD_LED_COLOR_HS,
    /* LED Set Color XY Event */
    CMD_LED_COLOR_XY,
    /* Button Event */
    CMD_BUTTON_OPEN,
    /* Button Event */
    CMD_BUTTON_READ,
     /* Sensor Event */
    CMD_SENSOR_OPEN,
    /* Sensor Event */
    CMD_SENSOR_READ,
    /* Button Event */        
    CMD_BUTTON_LONG_PRESS,

    /* Events in the Zigbee Group Event */
    /* Network joining/rejoining done*/
    EVENT_NETWORK_ESTABLISHED,
    /* Disconnected Event */
    EVENT_DISCONNECTED,
    /* Reset To Factory Defaults Event */
    EVENT_RESET_TO_FACTORY_DEFAULTS,
    /* Commissioning Started Event */
    EVENT_COMMISSIONING_STARTED,
    /* Commissioning Complete Event */
    EVENT_COMMISSIONING_COMPLETE,
    /* Commissioning Failure Event */
    EVENT_COMMISSIONING_FAILURE,
    /* Touchlink completed Event */
    EVENT_COMMISSIONING_TOUCHLINK_COMPLETE,
    /*Formation completed event*/
    EVENT_COMMISSIONING_FORMATION_COMPLETE,
    /*Steering completed event*/
    EVENT_COMMISSIONING_STEERING_COMPLETE,
    /*Finding and Binding completed event*/
    EVENT_COMMISSIONING_FINDBIND_COMPLETE,
    /* Started Centralized Network Event */
    EVENT_STARTED_CENTRALIZED_NETWORK,
    /* Started Distributed Network Event */
    EVENT_STARTED_DISTRIBUTED_NETWORK,
    /* Joined to an existing Network Event */
    EVENT_JOINED_TO_AN_EXISTING_NETWORK,
    /* Wake up Indication Event */
    EVENT_WAKEUP,
    /* Network Left Event */
    EVENT_LEFT_FROM_NETWORK,
    /* Child Joined Event */
    EVENT_CHILD_JOINED,
    /* Child Removed Event */
    EVENT_CHILD_REMOVED,
    /* Network Update Event - Nwk Parameters Updated */
    EVENT_NWK_UPDATE,
    /* Network Address Response */
    EVENT_NWK_ADDRESS_RESPONSE,
    /* IEEE Address Response */
    EVENT_IEEE_ADDRESS_RESPONSE,
    /* Simple Descriptor Response */
    EVENT_SIMPLE_DESCRIPTOR_RESPONSE,
    /* Match Descriptor Response */
    EVENT_MATCH_DESCRIPTOR_RESPONSE,
    /* Active Endpoint Response */
    EVENT_ACTIVE_EP_RESPONSE,
    /* Node Descriptor Response */
    EVENT_NODE_DESCRIPTOR_RESPONSE,
    /* Leave response */
    EVENT_LEAVE_RESPONSE,
    /* Management bind response */
    EVENT_MANAGEMENT_BIND_RESPONSE,
    /* Lqi response */
    EVENT_LQI_RESPONSE,
    /* Bind Response */
    EVENT_BIND_RESPONSE,
    /* Unbind reponse */
    EVENT_UNBIND_RESPONSE,

    /* Events in the Cluster Group Event */
<#if ((ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "CLIENT")  && (OC_ON == true))>
    /* Command ZCL ON */
    CMD_ZCL_ON,
</#if>
<#if ((ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "CLIENT")  && (OC_OFF == true))>
    /* Command ZCL OFF */
    CMD_ZCL_OFF,
</#if>
<#if ((ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "CLIENT")  && (OC_TOGGLE == true))>
    /* Command ZCL Toggle */
    CMD_ZCL_TOGGLE,
</#if>
<#if ((ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "CLIENT")  && (OC_OFFWITHEFFECT == true))>
    /* Command ZCL Toggle */
    CMD_ZCL_OFF_WITH_EFFECT,
</#if>
<#if ((ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "CLIENT")  && (OC_ONWITHRECALL == true))>
    /* Command ZCL Toggle */
    CMD_ZCL_ON_WITH_RECALL_GLOBALSCENE,
</#if>
<#if ((ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "CLIENT")  && (OC_ONWITHTIMEDOFF == true))>
    /* Command ZCL Toggle */
    CMD_ZCL_ON_WITH_TIMED_OFF,
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVETOHUE == true))>
    /* Command ZCL MOVE TO HUE */
    CMD_ZCL_MOVE_TO_HUE,
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVEHUE == true))>
    /* Command ZCL MOVE HUE */
    CMD_ZCL_MOVE_HUE,
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_STEPHUE == true))>
    /* Command ZCL STEP HUE */
    CMD_ZCL_STEP_HUE,
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVETOSATURATION == true))>
    /* Command ZCL MOVE TO SATURATION */
    CMD_ZCL_MOVE_TO_SATURATION,
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVESATURATION == true))>
    /* Command ZCL MOVE SATURATION */
    CMD_ZCL_MOVE_SATURATION,
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_STEPSATURATION == true))>
    /* Command ZCL STEP SATURATION */
    CMD_ZCL_STEP_SATURATION,
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVETOHUESATURATION == true))>
    /* Command ZCL MOVE TO HUE SATURATION */
    CMD_ZCL_MOVE_TO_HUE_SATURATION,
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVETOCOLOR == true))>
    /* Command ZCL MOVE TO COLOR */
    CMD_ZCL_MOVE_TO_COLOR,
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVECOLOR == true))>
    /* Command ZCL MOVE COLOR */
    CMD_ZCL_MOVE_COLOR,
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_STEPCOLOR == true))>
    /* Command ZCL STEP COLOR */
    CMD_ZCL_STEP_COLOR,
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVETOCOLORTEMP == true))>
    /* Command ZCL MOVE TO COLOR TEMPERATURE*/
    CMD_ZCL_MOVE_TO_COLOR_TEMPERATURE,
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDMOVETOHUE == true))>
    /* Command ZCL ENHANCED MOVE TO HUE*/
    CMD_ZCL_ENHANCED_MOVE_TO_HUE,
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDMOVEHUE == true))>
    /* Command ZCL ENHANCED MOVE HUE*/
    CMD_ZCL_ENHANCED_MOVE_HUE,
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDSTEPHUE == true))>
    /* Command ZCL ENHANCED STEP HUE*/
    CMD_ZCL_ENHANCED_STEP_HUE,
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_ENHANCEDMOVETOHUESATURATION == true))>
    /* Command ZCL ENHANCED MOVE TO HUE SATURATION*/
    CMD_ZCL_ENHANCED_MOVED_TO_HUE_SATURATION,
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_COLORLOOPSET == true))>
    /* Command ZCL COLOR LOOP SET*/
    CMD_ZCL_COLOR_LOOP_SET,
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_STOPMOVESTEP == true))>
    /* Command ZCL COLOR LOOP SET*/
    CMD_ZCL_STOP_MOVE_STEP,
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_MOVECOLORTEMP == true))>
    /* Command ZCL MOVE COLOR TEMPERATURE*/
    CMD_ZCL_MOVE_COLOR_TEMPERATURE,
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "CLIENT")  && (CC_STEPCOLORTEMP == true))>
    /* Command ZCL STEP COLOR TEMPERATURE*/
    CMD_ZCL_STEP_COLOR_TEMPERATURE,
</#if>
<#if ((BASIC_CLUSTER_ENABLE == true) && (BASIC_CLUSTER_CS != "CLIENT")  &&  (BS_RESETTOFNCMD == true))>
    /* Command ZCL ResetToFactoryDefaults */
    CMD_ZCL_RESET_TO_FACTORY_DEFAULTS,
</#if>
<#if ((IDENTIFY_CLUSTER_ENABLE == true) && (IDENTIFY_CLUSTER_CS != "CLIENT")  && (IC_IDENTIFYCMD == true))>
    /* Command ZCL Identify */
    CMD_ZCL_IDENTIFY,
</#if>
<#if ((IDENTIFY_CLUSTER_ENABLE == true) && (IDENTIFY_CLUSTER_CS != "CLIENT")  && (IC_IDENTIFYQUERYCMD == true))>
    /* Command ZCL Identify Query */
    CMD_ZCL_IDENTIFY_QUERY,
</#if>
<#if ((IDENTIFY_CLUSTER_ENABLE == true) && (IDENTIFY_CLUSTER_CS != "CLIENT")  && (IC_TRIGGEREFFECT == true))>
    /* Command ZCL Trigger Effect */
    CMD_ZCL_TRIGGER_EFFECT,
</#if>
<#if ((IDENTIFY_CLUSTER_ENABLE == true) && (IDENTIFY_CLUSTER_CS != "SERVER")  && (ICC_IDENTIFYQUERYRESCMD == true))>
    /* Command ZCL Identify Query Response*/
    CMD_ZCL_IDENTIFY_QUERY_RESPONSE,
</#if>
<#if ((GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "CLIENT")  && (GC_ADDGROUP == true))>
    /* Command ZCL Add group */
    CMD_ZCL_ADD_GROUP,
</#if>
<#if ((GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "CLIENT")  && (GC_VIEWGROUP == true))>
    /* Command ZCL View group */
    CMD_ZCL_VIEW_GROUP,
</#if>
<#if ((GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "CLIENT")  && (GC_GROUPMEM == true))>
    /* Command ZCL Get Group Membership */
    CMD_ZCL_GET_GROUP_MEMBERSHIP,
</#if>
<#if ((GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "CLIENT")  && (GC_REMOVEGROUP == true))>
    /* Command ZCL Remove Group */
    CMD_ZCL_REMOVE_GROUP,
</#if>
<#if ((GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "CLIENT")  && (GC_REMOVEGROUPALL == true))>
    /* Command ZCL Remove All Group */
    CMD_ZCL_REMOVE_ALL_GROUP,
</#if>
<#if ((GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "CLIENT")  && (GC_ADDGROUPIF == true))>
    /* Command ZCL Add group if identifying */
    CMD_ZCL_ADD_GROUP_IF_IDENTIFYING,
</#if>
<#if ((GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "SERVER")  && (GCC_ADDGROUPRESP == true))>
    /* Command ZCL Add group response */
    CMD_ZCL_ADD_GROUP_RESPONSE,
</#if>
<#if ((GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "SERVER")  && (GCC_VIEWGROUPRESP == true))>
    /* Command ZCL View group response */
    CMD_ZCL_VIEW_GROUP_RESPONSE,
</#if>
<#if ((GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "SERVER")  && (GCC_GROUPMEMRESP == true))>
    /* Command ZCL Group Membership response */
    CMD_ZCL_GET_GROUP_MEMBERSHIP_RESPONSE,
</#if>
<#if ((GROUPS_CLUSTER_ENABLE == true) && (GROUPS_CLUSTER_CS != "SERVER")  && (GCC_REMOVEGROUPRESP == true))>
    /* Command ZCL Remove Group Response */
    CMD_ZCL_REMOVE_GROUP_RESPONSE,
</#if>
<#if ((LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  && (LC_MOVETOLEVEL == true))>
    /* Command Move To Level */
    CMD_ZCL_MOVE_TO_LEVEL,
</#if>
<#if ((LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  && (LC_MOVE == true))>
    /* Command Move To Level */
    CMD_ZCL_MOVE,
</#if>
<#if ((LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  && (LC_STEP == true))>
    /* Command Step */
    CMD_ZCL_STEP,
</#if>
<#if ((LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  && (LC_STOP == true))>
    /* Command Stop */
    CMD_ZCL_STOP,
</#if>
<#if ((LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  && (LC_MOVETOLEVELWITHONOFF == true))>
    /* Command Move To Level With Onoff */
    CMD_ZCL_MOVE_TO_LEVEL_WITH_ONOFF,
</#if>
<#if ((LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  && (LC_MOVEWITHONOFF == true))>
    /* Command Move With Onoff */
    CMD_ZCL_MOVE_WITH_ONOFF,
</#if>
<#if ((LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  && (LC_STEPWITHONOFF == true))>
    /* Command Step With Onoff */
    CMD_ZCL_STEP_WITH_ONOFF,
</#if>
<#if ((LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "CLIENT")  && (LC_STOPWITHONOFF == true))>
    /* Command Stop With Onoff */
    CMD_ZCL_STOP_WITH_ONOFF,
</#if>
<#if ((ALARMS_CLUSTER_ENABLE == true) && (ALARMS_CLUSTER_CS != "SERVER")  && (AC_ALARM == true))>
    /* Command ZCL Alarm Ind */
    CMD_ZCL_ALARM,
</#if>
<#if ((ALARMS_CLUSTER_ENABLE == true) && (ALARMS_CLUSTER_CS != "SERVER")  && (AC_GETALARMRESPONSE == true))>
    /* Command ZCL Get Alarm Response */
    CMD_ZCL_GET_ALARM_RESPONSE,
</#if>
<#if ((ALARMS_CLUSTER_ENABLE == true) && (ALARMS_CLUSTER_CS != "CLIENT")  && (AS_RESETALLALARMS == true))>
    /* Command ZCL Reset All Alarms Indication*/
    CMD_ZCL_RESET_ALL_ALARMS,
</#if>
<#if ((ALARMS_CLUSTER_ENABLE == true) && (ALARMS_CLUSTER_CS != "CLIENT")  && (AS_RESETALARM == true))>
    /* Command ZCL Reset Alarm Indication*/
    CMD_ZCL_RESET_ALARM,
</#if>
<#if ((ALARMS_CLUSTER_ENABLE == true) && (ALARMS_CLUSTER_CS != "CLIENT")  && (AS_GETALARM == true))>
    /* Command ZCL Get Alarm Indication*/
    CMD_ZCL_GET_ALARM,
</#if>
<#if ((ALARMS_CLUSTER_ENABLE == true) && (ALARMS_CLUSTER_CS != "CLIENT")  && (AS_GETALARM == true))>
    /* Command ZCL Rest Alarm Log Indication*/
    CMD_ZCL_RESET_ALARM_LOG,
</#if>
<#if ((THERMOSTAT_CLUSTER_ENABLE == true) && (THERMOSTAT_CLUSTER_CS != "CLIENT")  && (THC_SETPOINTRAISELOWER == true))>
    /* Command ZCL_SetPointInd*/
    CMD_ZCL_SETPOINT,
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  && (SC_ADDSCENE == true))>
    /* Command ZCL ADD SCENE*/
    CMD_ZCL_ADD_SCENE,
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  && (SC_VIEWSCENE == true))>
    /* Command ZCL VIEW SCENE*/
    CMD_ZCL_VIEW_SCENE,
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  && (SC_ENHANCEDADDSCENE == true))>
    /* Command ZCL ENHANCED ADD SCENE*/
    CMD_ZCL_ENHANCED_ADD_SCENE,
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  && (SC_ENHANCEDVIEWSCENE == true))>
    /* Command ZCL ENHANCED VIEW SCENE*/
    CMD_ZCL_ENHANCED_VIEW_SCENE,
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  && (SC_REMOVESCENE == true))>
    /* Command ZCL REMOVE SCENE*/
    CMD_ZCL_REMOVE_SCENE,
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  && (SC_REMOVESCENEALL == true))>
    /* Command ZCL REMOVE ALL SCENES*/
    CMD_ZCL_REMOVE_ALL_SCENES,
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  && (SC_STORESCENE == true))>
    /* Command ZCL STORE SCENES*/
    CMD_ZCL_STORE_SCENE,
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  && (SC_RECALLSCENE == true))>
    /* Command ZCL RECALL SCENE*/
    CMD_ZCL_RECALL_SCENE,
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  && (SC_SCENEMEM == true))>
    /* Command ZCL GET SCENE MEMBERSHIP*/
    CMD_ZCL_GET_SCENE_MEMBERSHIP,
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "CLIENT")  && (SC_COPYSCENE == true))>
    /* Command ZCL COPY SCENE*/
    CMD_ZCL_COPY_SCENE,
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  && (SCC_ADDSCENERESP == true))>
    /* Command ZCL ADD SCENE RESPONSE*/
    CMD_ZCL_ADD_SCENE_RESP,
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  && (SCC_VIEWSCENERES == true))>
    /* Command ZCL VIEW SCENE RESPONSE*/
    CMD_ZCL_VIEW_SCENE_RESP,
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  && (SCC_REMOVESCENERES == true))>
    /* Command ZCL REMOVE SCENE RESPONSE*/
    CMD_ZCL_REMOVE_SCENE_RESP,
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  && (SCC_REMOVESCENEALLRES == true))>
    /* Command ZCL REMOVE ALL SCENE RESPONSE*/
    CMD_ZCL_REMOVE_ALL_SCENES_RESP,
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  && (SCC_STORESCENERES == true))>
    /* Command ZCL STORE SCENE RESPONSE*/
    CMD_ZCL_STORE_SCENE_RESP,
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  && (SCC_SCENEMEMRES == true))>
    /* Command ZCL GET SCENE MEMBERSHIP RESPONSE*/
    CMD_ZCL_GET_SCENE_MEMBERSHIP_RESP,
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  && (SCC_ENHANCEDADDSCENERES == true))>
    /* Command ZCL enhance add scene response*/
    CMD_ZCL_ENHANCED_ADD_SCENE_RESP,
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  && (SCC_ENHANCEDVIEWSCENERES == true))>
    /* Command ZCL ENHANCED VIEW SCENE RESPONSE*/
    CMD_ZCL_ENHANCED_VIEW_SCENE_RESP,
</#if>
<#if ((SCENES_CLUSTER_ENABLE == true) && (SCENES_CLUSTER_CS != "SERVER")  && (SCC_COPYSCENERES == true))>
    /* Command ZCL COPY SCENE RESPONSE*/
    CMD_ZCL_COPY_SCENE_RESP,
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_GETZONESTATUS == true))>
    /* Command ZCL GET ZONE STATUS*/
    CMD_ZCL_ACE_GET_ZONE_STATUS,
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_ARM == true))>
    /* Command ZCL ACE ARM*/
    CMD_ZCL_ACE_ARM,
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_GETZONEINFO == true))>
    /* Command ZCL ACE GET ZONE INFO*/
    CMD_ZCL_ACE_GET_ZONE_INFO,
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_GETZONEIDMAP == true))>
    /* Command ZCL ACE GET ZONE ID MAP*/
    CMD_ZCL_ACE_GET_ZONE_ID_MAP,
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_BYPASS == true))>
    /* Command ZCL ACE BYPASS*/
    CMD_ZCL_ACE_BYPASS,
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_GETBYPASSZONELIST == true))>
    /* Command ZCL ACE_GET BYPASSED ZONE LIST*/
    CMD_ZCL_ACE_GET_BYPASSED_ZONE_LIST,
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_EMERGENCY == true))>
    /* Command ZCL ACE EMERGENCY*/
    CMD_ZCL_ACE_EMERGENCY,
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_FIRE == true))>
    /* Command ZCL ACE FIRE*/
    CMD_ZCL_ACE_FIRE,
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_PANIC == true))>
    /* Command ZCL ACE PANIC*/
    CMD_ZCL_ACE_PANIC,
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "CLIENT")  && (IAC_GETPANELSTATUS == true))>
    /* Command ZCL ACE_GET PANEL STATUS*/
    CMD_ZCL_ACE_GET_PANEL_STATUS,
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONESTATUSRESP == true))>
    /* Command ZCL ACE_GET PANEL STATUS RESP*/
    CMD_ZCL_ACE_GET_PANEL_STATUS_RESP,
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  && (IACC_ARMRESP == true))>
    /* Command ZCL ACE ARM RESP*/
    CMD_ZCL_ACE_ARM_RESP,
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONEIDMAPRESP == true))>
    /* Command ZCL ACE GET ZONE ID MAP RESP*/
    CMD_ZCL_ACE_GET_ZONE_ID_MAP_RESP,
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONESTATUSRESP == true))>
    /* Command ZCL GET ZONE STATUS RESPONSE*/
    CMD_ZCL_ACE_GET_ZONE_STATUS_RESP,
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  && (IACC_PANELSTATUSCHANGED == true))>
    /* Command ZCL ACE PANEL STATUS CHANGED*/
    CMD_ZCL_ACE_PANEL_STATUS_CHANGED,
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  && (IACC_ZONESTATUSCHANGED == true))>
    /* Command ZCL ACE ZONE STATUS CHANGED*/
    CMD_ZCL_ACE_ZONE_STATUS_CHANGED,
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  && (IACC_GETZONEINFORESP == true))>
    /* Command ZCL ACE GET ZONE INFO RESPONSE */
    CMD_ZCL_ACE_GET_ZONE_INFO_RESP,
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  && (IACC_SETBYPASSEDZONELIST == true))>
    /* Command ZCL ACE SET BYPASSED ZONE LIST*/
    CMD_ZCL_ACE_SET_BYPASSED_ZONE_LIST,
</#if>
<#if ((IASACE_CLUSTER_ENABLE == true) && (IASACE_CLUSTER_CS != "SERVER")  && (IACC_BYPASSRESPONSE == true))>
    /* Command ZCL ACE BYPASS RESP*/
    CMD_ZCL_ACE_BYPASS_RESP,
</#if>
<#if ((IASZONE_CLUSTER_ENABLE == true) && (IASZONE_CLUSTER_CS != "SERVER")  && (IZCC_ZONESTATUSCHANGENOTIFICATION == true))>
    /* Command ZCL ZONE STATUS CHANGE NOTIFY*/    
    CMD_ZCL_ZONE_STATUS_CHANGE_NOTIFY,
</#if>
<#if ((IASZONE_CLUSTER_ENABLE == true) && (IASZONE_CLUSTER_CS != "SERVER")  && (IZCC_ZONEENROLLREQ == true))>
    /* Command ZCL ZONE ENROLL REQ*/
    CMD_ZCL_ZONE_ENROLL_REQ,
</#if>
<#if ((IASZONE_CLUSTER_ENABLE == true) && (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_ZONEENROLLRESP == true))>
    /* Command ZCL ZONE ENROLL RESP*/
    CMD_ZCL_ZONE_ENROLL_RESP,
</#if>
<#if ((IASZONE_CLUSTER_ENABLE == true) && (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_INITIATENORMALOPMODE == true))>
    /* Command ZCL ZONE INITIATE OPERATING MODE*/
    CMD_ZCL_ZONE_INITIATE_NORMAL_OPERATING_MODE,
</#if>
<#if ((IASZONE_CLUSTER_ENABLE == true) && (IASZONE_CLUSTER_CS != "CLIENT")  && (IZC_INITIATETESTMODE == true))>
    /* Command ZCL ZONE INITIATE TEST MODE*/
    CMD_ZCL_ZONE_INITIATE_TEST_MODE,
</#if>
<#if (COLORCONTROL_CLUSTER_ENABLE == true)>
    /* Command ZCL ColorControlAttributeEventInd */
    CMD_ZCL_ATTR_COLOR_CONTROL,
</#if>
<#if (IDENTIFY_CLUSTER_ENABLE == true)>
    /* Command ZCL IdentifyAttributeEventInd */
    CMD_ZCL_ATTR_IDENTIFY,
</#if>
<#if (LEVELCONTROL_CLUSTER_ENABLE == true)>
    /* Command ZCL LevelControlAttributeEventInd */
    CMD_ZCL_ATTR_LEVEL_CONTROL,
</#if>
<#if (ONOFF_CLUSTER_ENABLE == true)>
    /* Command ZCL OnOffAttributeEventInd */
    CMD_ZCL_ATTR_ONOFF,
</#if>
<#if (ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE == true)>
    /* Command ZCL IlluminanceAttributeEventInd */
    CMD_ZCL_ATTR_ILLUMINANCE_MEASUREMENT,
</#if>
<#if OCCUPANCYSENSING_CLUSTER_ENABLE == true>
    /* Command ZCL OccupancyAttributeEventInd */
    CMD_ZCL_ATTR_OCCUPANCY,
</#if>
<#if (WATERCONTENTMEASUREMENT_CLUSTER_ENABLE == true)>
    /* Command ZCL_CustomHumidityAttributeEventInd */
    CMD_ZCL_ATTR_HUMIDITY_MEASUREMENT,
</#if>
<#if (TIME_CLUSTER_ENABLE == true)>
    /* Command ZCL_TimeAttrEventInd*/
    CMD_ZCL_ATTR_TIME,
</#if>
<#if (THERMOSTATUI_CLUSTER_ENABLE == true)>
    /* Command ZCL_ThermostatUIConfAttrEventInd*/
    CMD_ZCL_ATTR_THERMOSTAT_UI_CONF,
</#if>
<#if (TEMPERATUREMEASUREMENT_CLUSTER_ENABLE == true)>
    /* Command ZCL_Temperature Measurement Attribute Ind*/
    CMD_ZCL_ATTR_TEMPERATURE_MEASUREMENT,
</#if>
<#if (THERMOSTAT_CLUSTER_ENABLE == true)>
    /* Command ZCL_Thermostat Attribute Ind*/
    CMD_ZCL_ATTR_THERMOSTAT,
</#if>
<#if (FANCONTROL_CLUSTER_ENABLE == true)>
    /* Command ZCL Attribute fancontrol*/
    CMD_ZCL_ATTR_FANCONTROL,
</#if>
<#if (IASZONE_CLUSTER_ENABLE == true)>
    /* Command ZCL Attribute IASACE*/
    CMD_ZCL_ATTR_IASZONE,
</#if>
<#if ((ONOFF_CLUSTER_ENABLE == true) && (ONOFF_CLUSTER_CS != "SERVER"))>
    /* Command ZCL OnOffReportInd */
    CMD_ZCL_REPORTING_ONOFF,
</#if>
<#if ((LEVELCONTROL_CLUSTER_ENABLE == true) && (LEVELCONTROL_CLUSTER_CS != "SERVER"))>
    /* Command ZCL LevelReportInd */
    CMD_ZCL_REPORTING_LEVEL,
</#if>
<#if ((ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE == true) && (ILLUMINANCEMEASUREMENT_CLUSTER_CS != "SERVER"))>
    /* Command ZCL LightSensorReportInd */
    CMD_ZCL_REPORTING_LIGHT_SENSOR,
</#if>
<#if ((OCCUPANCYSENSING_CLUSTER_ENABLE == true) && (OCCUPANCYSENSING_CLUSTER_CS != "SERVER"))>
    /* Command ZCL OccupancySensorReportInd */
    CMD_ZCL_REPORTING_OCCUPANCY,
</#if>
<#if ((COLORCONTROL_CLUSTER_ENABLE == true) && (COLORCONTROL_CLUSTER_CS != "SERVER"))>
    /* Command ZCL Report attribute Indication*/
     CMD_ZCL_REPORTING_COLOR_CONTROL,
</#if>
<#if ((THERMOSTAT_CLUSTER_ENABLE == true) && (THERMOSTAT_CLUSTER_CS != "SERVER"))>
    /* Command ZCL_Thermostat Report Ind */
    CMD_ZCL_REPORTING_THERMOSTAT,
</#if>
<#if ((TEMPERATUREMEASUREMENT_CLUSTER_ENABLE == true) && (TEMPERATUREMEASUREMENT_CLUSTER_CS != "SERVER"))>
    /* Command ZCL_TemperarureMeasurement Report Ind */
    CMD_ZCL_REPORTING_TEMPERATURE_MEASUREMENT,
</#if>
<#if ((WATERCONTENTMEASUREMENT_CLUSTER_ENABLE == true) && (WATERCONTENTMEASUREMENT_CLUSTER_CS != "SERVER"))>
  /* Command ZCL_HumdityMeasurementReportInd*/
    CMD_ZCL_REPORTING_HUMIDITY_MEASUREMENT,
</#if>

<#function isReportable customClusterIndex>
<#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >


<#assign result = false>
<#assign prefixAttribute  = "ZCC" + customClusterIndex + "_CUSTOM_CLUSTER_" + "SERVER" + "_ATTRIBUTES_">

<#list 0..<(prefixAttribute  + "NO")?eval as attributeIndex>
    <#if (prefixAttribute +"PROP_REPORTABLE_"+attributeIndex)?eval>
        <#return true>
    </#if>
</#list>

<#assign prefixAttribute  = "ZCC" + customClusterIndex + "_CUSTOM_CLUSTER_" + "CLIENT" + "_ATTRIBUTES_">

<#list 0..<(prefixAttribute  + "NO")?eval as attributeIndex>
    <#if (prefixAttribute +"PROP_REPORTABLE_"+attributeIndex)?eval>
        <#return true>
    </#if>
</#list>

<#return false>

</#function>
<#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX>
<#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >  
  <#if ( (DEVICE == "CLIENT") || (DEVICE == "BOTH") ) && isReportable(customClusterIndex) >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >  
    /*Command ZCL ${deviceTypeFunctionPrefix}${clusterName}ReportInd*/
    CMD_ZCL_REPORTING_${clusterName?upper_case},
  </#if>
  <#if (DEVICE == "SERVER") || (DEVICE == "BOTH") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >  
    /*Command ZCL ${deviceTypeFunctionPrefix}${clusterName}AttributeEventInd*/
    CMD_ZCL_ATTR_${clusterName?upper_case},
   </#if>  
</#list>


} APP_Zigbee_EventId_t;

/*******************************************************************************
 Application Zigbee Data
******************************************************************************/
typedef union
{
    bool state;
    uint8_t id;
    uint8_t value;
    uint16_t data;
    struct
    {
        uint8_t status;
        uint8_t ep;
        uint16_t shortAddress;
        uint64_t extendedAddress;
        uint64_t extendedPanId;
    }ParentChildInfo;
    struct
    {
        uint16_t hue;
        uint8_t saturation;
    }colorHS;
    struct
    {
        uint16_t x;
        uint16_t y;
    }colorXY;
    struct
    {
        ZCL_Addressing_t *addressing;
        uint8_t payloadLength;
        void *payload;
    }zclEventData;
    struct
    {
        ZCL_Addressing_t *addressing;
        ZCL_AttributeId_t attributeId;
        ZCL_AttributeEvent_t event;
    }zclAttributeData;    
}APP_Zigbee_EventData;

/*******************************************************************************
 Application Zigbee Event Structure
******************************************************************************/
typedef struct
{
    APP_Zigbee_EventGroup_t eventGroup;
    APP_Zigbee_EventId_t eventId;
    APP_Zigbee_EventData eventData;    
}APP_Zigbee_Event_t;

/*******************************************************************************
  Function:
    void APP_Zigbee_Handler(APP_Zigbee_Event_t event)
******************************************************************************/
void APP_Zigbee_Handler(APP_Zigbee_Event_t event);

#endif