<#compress>
<#assign deviceType = ZB_DEVICE_TYPE>
<#assign DEVICE = (NAME + "_CUSTOM_CLUSTER_CS")?eval>
<#assign prefix = NAME + "_CUSTOM_CLUSTER_" + DEVICE + "_COMMANDS_">
<#assign clusterName = (NAME + "_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','')>
<#global arraySize = "">

<#switch (deviceType)>
	<#case "ZIGBEE_COLOR_SCENE_CONTROLLER">
		<#assign deviceTypeFunctionPrefix = "csc">
		<#break>
	<#case "ZIGBEE_MULTI_SENSOR">
		<#assign deviceTypeFunctionPrefix = "ms">
		<#break>
	<#case "ZIGBEE_COMBINED_INTERFACE">
		<#assign deviceTypeFunctionPrefix = "ci">
		<#break>
	<#case "ZIGBEE_THERMOSTAT">
		<#assign deviceTypeFunctionPrefix = "th">
		<#break>
	<#case "ZIGBEE_IAS_ACE">
		<#assign deviceTypeFunctionPrefix = "iasACE">
		<#break>
	<#case "ZIGBEE_DIMMABLE_LIGHT">
		<#assign deviceTypeFunctionPrefix = "light">
		<#break>
	<#case "ZIGBEE_COLOR_LIGHT">
		<#assign deviceTypeFunctionPrefix = "light">
		<#break>
	<#case "ZIGBEE_EXTENDED_COLOR_LIGHT">
		<#assign deviceTypeFunctionPrefix = "light">
		<#break>
	<#case "ZIGBEE_TEMPERATURE_COLOR_LIGHT">
		<#assign deviceTypeFunctionPrefix = "light">
		<#break>
	<#case "ZIGBEE_CUSTOM">
		<#assign deviceTypeFunctionPrefix = "custom">
		<#break>
	<#case "ZIGBEE_ON_OFF_LIGHT">
		<#assign deviceTypeFunctionPrefix = "light">
		<#break>
<#default>
	<#assign deviceTypeFunctionPrefix = "">
</#switch>
/*******************************************************************************</#compress>
  ${NAME?upper_case} Custom Cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
   ${deviceTypeFunctionPrefix}${clusterName}Cluster.c

  Summary:
    This file contains the Custom Cluster interface.

  Description:
    This file contains the Custom Cluster interface.
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
<#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
<#assign devicetype = DEVICE_TYPE_FILE_PATH >

#include <z3device/${devicetype}/include/${deviceTypeFunctionPrefix + clusterName}Cluster.h>
#include <zcl/include/zcl${clusterName}Cluster.h>

#include <z3device/clusters/include/haClusters.h>
#include <zcl/include/zclCommandManager.h>
#include <app_zigbee/app_zigbee_handler.h>
#include <app_zigbee/zigbee_console/console.h>


/*******************************************************************************
                    Prototypes section
*******************************************************************************/
<#function getParametersLength prefix commandIndex>
<#return (prefix + "PARAM_NO_" + commandIndex)?eval>
</#function>

<#function parameterVariable prefix commandIndex parameterIndex>
<#-- [ BLOCK datatype] -->
        <#assign arraySize = "">
        <#switch (prefix + "CLASSTYPE_" + commandIndex + "_" + parameterIndex)?eval>
        <#case "General Data">
            <#assign datatype = "uint"+( prefix + "TYPE_GENERAL_" + commandIndex + "_" + parameterIndex)?eval?remove_beginning("data") + "_t" >
            <#break>
        <#case "Enumeration">
            <#assign datatype = "uint8_t" >
            <#break>
        <#case "Unsigned Integer">
            <#assign datatype = (prefix + "TYPE_UNSIGNED_" + commandIndex + "_" + parameterIndex)?eval + "_t">
            <#break>
        <#case "Bitmap">
            <#assign datatype = "uint8_t">
            <#break>
        <#case "Signed Integer">
            <#assign datatype = (prefix + "TYPE_SIGNED_" + commandIndex + "_" + parameterIndex)?eval + "_t">
            <#break>
        <#case "Boolean">
            <#assign datatype = "bool" >
            <#break>
        <#case "String">
            <#assign datatype = "uint8_t">
            <#if (prefix + "TYPE_STRING_" + commandIndex + "_" + parameterIndex)?eval?contains("16")>
                <#assign datatype = "uint16_t">
            </#if>
            <#assign arraySize = "[32]"> <#-- the suffix for array types -->
            <#break>
        <#case "Array">
            <#assign datatype = "uint8_t">
            <#assign arraySize = "["+ (prefix + "TYPE_ARRAY_" + commandIndex + "_" + parameterIndex)?eval + "]">
            <#break>
        <#default>      
                  
        </#switch>

    <#assign parameterName = (prefix + "PARAMNAME_" + commandIndex + "_" + parameterIndex)?eval >

<#return datatype + " " + parameterName?replace(" ","") + arraySize>

</#function>

<#function isReportable> <#--Function that says if there are reportable attributes -->
<#assign result = false>
<#assign prefixAttribute  = NAME + "_CUSTOM_CLUSTER_" + "SERVER" + "_ATTRIBUTES_">

<#list 0..<(prefixAttribute  + "NO")?eval as attributeIndex>
    <#if (prefixAttribute +"PROP_REPORTABLE_"+attributeIndex)?eval>
        <#return true>
    </#if>
</#list>

<#assign prefixAttribute  = NAME + "_CUSTOM_CLUSTER_" + "CLIENT" + "_ATTRIBUTES_">

<#list 0..<(prefixAttribute  + "NO")?eval as attributeIndex>
    <#if (prefixAttribute +"PROP_REPORTABLE_"+attributeIndex)?eval>
        <#return true>
    </#if>
</#list>

<#return false>

</#function>

<#assign REPORTABLE_CLIENT = (isReportable() && (DEVICE == "CLIENT")) >
<#assign REPORTABLE_SERVER = (isReportable() && (DEVICE == "SERVER")) >

<#if REPORTABLE_CLIENT == true>
static void ${deviceTypeFunctionPrefix}${clusterName}ReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload);
<#elseif DEVICE == "SERVER">
static void ${deviceTypeFunctionPrefix}${clusterName}AttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
</#if>
void ${deviceTypeFunctionPrefix}${clusterName}Init(void);

<#--//FUNCTION PROTOTYPES -->
<#--//SERVER -->
<#if DEVICE == "SERVER">

    <#assign prefix = NAME + "_CUSTOM_CLUSTER_" + "SERVER" + "_COMMANDS_">
    <#list 0..<(prefix+"NO")?eval as commandIndex>
        <#assign CommandName = (prefix+"NAME_"+commandIndex)?eval?capitalize?replace(' ','')>
        <#assign parametersLength = getParametersLength(prefix, commandIndex) >
ZCL_Status_t ${deviceTypeFunctionPrefix}Send${CommandName}(APS_AddrMode_t addressMode, ShortAddr_t shortAddress, Endpoint_t endPoint, Endpoint_t sourceEndPoint<#if (parametersLength == 0) >);
<#else>${''}
    <#list 0..<parametersLength as parameterIndex >,${parameterVariable(prefix,commandIndex,parameterIndex)} </#list>);
</#if>
    </#list>

    <#assign prefix = NAME + "_CUSTOM_CLUSTER_" + "CLIENT" + "_COMMANDS_">
    <#list 0..<(prefix+"NO")?eval as commandIndex>
        <#assign CommandName = (prefix+"NAME_"+commandIndex)?eval?capitalize?replace(' ','')>
ZCL_Status_t ${deviceTypeFunctionPrefix}${CommandName}CommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_${CommandName}_t *payload);
    </#list>

<#--//CLIENT -->
<#elseif DEVICE == "CLIENT">

    <#assign prefix = NAME + "_CUSTOM_CLUSTER_" + "SERVER" + "_COMMANDS_">
    <#list 0..<(prefix+"NO")?eval as commandIndex>
        <#assign CommandName = (prefix+"NAME_"+commandIndex)?eval?capitalize?replace(' ','')>
ZCL_Status_t ${deviceTypeFunctionPrefix}${CommandName}CommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_${CommandName}_t *payload);
    </#list>

    <#assign prefix = NAME + "_CUSTOM_CLUSTER_" + "CLIENT" + "_COMMANDS_">
    <#list 0..<(prefix+"NO")?eval as commandIndex>
        <#assign CommandName = (prefix+"NAME_"+commandIndex)?eval?capitalize?replace(' ','')>
        <#assign parametersLength = getParametersLength(prefix, commandIndex) >
ZCL_Status_t ${deviceTypeFunctionPrefix}Send${CommandName}(APS_AddrMode_t addressMode, ShortAddr_t shortAddress, Endpoint_t endPoint, Endpoint_t sourceEndPoint<#if (parametersLength == 0) >);
<#else>${''} 
    <#list 0..<parametersLength as parameterIndex >,${parameterVariable(prefix,commandIndex,parameterIndex)} </#list>);
</#if>
    </#list>

</#if>

/******************************************************************************
                    Global variables
******************************************************************************/
<#function attributeParameters>

<#assign attributesCount = (NAME + "_CUSTOM_CLUSTER_" + DEVICE + "_ATTRIBUTES_NO")?eval >
<#list 0..< (attributesCount) as attributeIndex >

    <#assign reportableProperty = (NAME + "_CUSTOM_CLUSTER_" + DEVICE + "_ATTRIBUTES_PROP_REPORTABLE_" + attributeIndex)?eval >

    <#if (reportableProperty) >
        <#return clusterName?upper_case + "_MIN_REPORT_PERIOD," + clusterName?upper_case + "_MAX_REPORT_PERIOD" >
    </#if>
</#list>

<#return "">
</#function>


//Custom Cluster Attributes
ZCL_${clusterName?capitalize}Cluster${DEVICE?capitalize}Attributes_t ${clusterName?lower_case}${DEVICE?capitalize}ClusterAttributes =
{
    ZCL_DEFINE_${(clusterName)?upper_case}_CLUSTER_${DEVICE}_ATTRIBUTES(${attributeParameters()})
};

//Custom Cluster Commands
PROGMEM_DECLARE (ZCL_${clusterName?capitalize}ClusterCommands_t ${clusterName?lower_case}${DEVICE?capitalize}ClusterCommands) =
{
<#--//CLIENT -->

<#if DEVICE == "CLIENT">    
    ZCL_DEFINE_${clusterName?upper_case}_CLUSTER_COMMANDS( <#t>
        <#assign prefix = NAME + "_CUSTOM_CLUSTER_" + "SERVER" + "_COMMANDS_">
        <#assign serverCommandCount = (prefix+"NO")?eval>
        <#list 0..< serverCommandCount as commandIndex>
        <#assign CommandName = (prefix+"NAME_"+commandIndex)?eval?capitalize?replace(' ','')>
${deviceTypeFunctionPrefix + CommandName}CommandInd<#sep>,  <#t></#list><#compress>
        <#assign prefix = NAME + "_CUSTOM_CLUSTER_" + "CLIENT" + "_COMMANDS_">
        </#compress><#list 0..<(prefix+"NO")?eval as commandIndex>
<#if (serverCommandCount!=0 || commandIndex?is_first == false)>,</#if> NULL<#sep> <#t></#list>)        
<#--//SERVER -->

<#elseif DEVICE == "SERVER">
    ZCL_DEFINE_${clusterName?upper_case}_CLUSTER_COMMANDS( <#t>
        <#assign prefix = NAME + "_CUSTOM_CLUSTER_" + "SERVER" + "_COMMANDS_">
        <#assign serverCommandCount = (prefix+"NO")?eval>
        <#list 0..< serverCommandCount as commandIndex>
NULL<#sep>, <#t></#list><#compress>
        <#assign prefix = NAME + "_CUSTOM_CLUSTER_" + "CLIENT" + "_COMMANDS_">
        </#compress><#list 0..<(prefix+"NO")?eval as commandIndex>
        <#assign CommandName = (prefix+"NAME_"+commandIndex)?eval?capitalize?replace(' ','')>
<#if (serverCommandCount!=0 || commandIndex?is_first == false)>,</#if> ${deviceTypeFunctionPrefix + CommandName}CommandInd<#sep> <#t></#list>)
</#if>
};

<#assign prefix = NAME + "_CUSTOM_CLUSTER_" + DEVICE + "_COMMANDS_"> <#-- re-assign old defintion -->

/******************************************************************************
                    Implementation section
******************************************************************************/

/**************************************************************************//**
\brief Initialization function for the cluster
******************************************************************************/
<#assign deviceType = deviceType?remove_beginning("ZIGBEE_")>
<#if deviceType == "MULTI_SENSOR">
    <#assign ENDPOINT = (NAME +"_MULTI_SENSOR_ENDPOINT")?eval >
    <#switch (ENDPOINT)>
        <#case "OCCUPANCY">
            <#assign deviceType = "OCCUPANCY_SENSOR">
            <#break>
        <#case "HUMIDITY">
            <#assign deviceType = "HUMIDITY_SENSOR">
            <#break>
        <#case "TEMPERATURE">
            <#assign deviceType = "TEMPERATURE_SENSOR">
            <#break>
        <#case "ILLUMINANCE">
            <#assign deviceType = "EXTENDED_COLOR_LIGHT_SENSOR">
            <#break>
        <#default>
            <#assign deviceType = "OCCUPANCY_SENSOR">
    </#switch>
</#if>
void ${deviceTypeFunctionPrefix}${clusterName}Init(void)
{    
    <#if REPORTABLE_CLIENT == true>
    /* Executes only for Reportable Client. */
    ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_${deviceType}, ${clusterName?upper_case}_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);

    if (cluster)
    {
        cluster->ZCL_ReportInd = ${deviceTypeFunctionPrefix}${clusterName}ReportInd;
        cluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
    }

    <#elseif DEVICE == "SERVER">
    /* Executes only for Server. */
    ZCL_Cluster_t *cluster =  ZCL_GetCluster(APP_ENDPOINT_${deviceType}, ${clusterName?upper_case}_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);

    if (cluster)
        cluster->ZCL_AttributeEventInd = ${deviceTypeFunctionPrefix}${clusterName}AttributeEventInd;
    <#else>
    /* Executes for non Reportable Client */
    </#if>

    // Fill definition here
}

<#if REPORTABLE_CLIENT == true>
/**************************************************************************//**
\brief Report attribute indication handler

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void ${deviceTypeFunctionPrefix}${clusterName}ReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload)
{
    APP_Zigbee_Event_t eventItem;
    eventItem.eventGroup = EVENT_CLUSTER;
    eventItem.eventId = CMD_ZCL_REPORTING_${clusterName?upper_case}; //defined in app_zigbee_handler
    eventItem.eventData.zclEventData.addressing = addressing;
    eventItem.eventData.zclEventData.payloadLength = reportLength;
    eventItem.eventData.zclEventData.payload = reportPayload;

  APP_Zigbee_Handler(eventItem);
}
<#elseif DEVICE == "SERVER">
/**************************************************************************//**
\brief Attribute event (writing/reading) callback.

\param[in] addressing - incoming request addressing information.
\param[in] attributeId - attribute identifier.
\param[in] event - attribute event (read/write).
******************************************************************************/
static void ${deviceTypeFunctionPrefix}${clusterName}AttributeEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
    APP_Zigbee_Event_t eventItem;
    eventItem.eventGroup = EVENT_CLUSTER;
    eventItem.eventId = CMD_ZCL_ATTR_${clusterName?upper_case}; //defined in app_zigbee_handler
    eventItem.eventData.zclAttributeData.addressing = addressing;
    eventItem.eventData.zclAttributeData.attributeId = attributeId;
    eventItem.eventData.zclAttributeData.event = event;
                        
  APP_Zigbee_Handler(eventItem);
}
</#if>

<#--//FUNCTION DEFINITIONS -->
<#--//SERVER -->
<#if DEVICE == "SERVER">
    <#assign prefix = NAME + "_CUSTOM_CLUSTER_" + "SERVER" + "_COMMANDS_">
    <#list 0..<(prefix+"NO")?eval as commandIndex>
        <#assign CommandName = (prefix+"NAME_"+commandIndex)?eval?capitalize?replace(' ','')>
        <#assign parametersLength = getParametersLength(prefix, commandIndex) >
/**************************************************************************//**
\brief Sends ${CommandName} command

\param[in] mode     - address mode;
\param[in] addr     - short address of destination node;
\param[in] ep       - destination endpoint;
\param[in] srcEp    - source endpoint;
******************************************************************************/
ZCL_Status_t ${deviceTypeFunctionPrefix}Send${CommandName}(APS_AddrMode_t addressMode, ShortAddr_t shortAddress, Endpoint_t endPoint, Endpoint_t sourceEndPoint<#if (parametersLength == 0) >)
<#else>${''} 
    <#list 0..<parametersLength as parameterIndex >,${parameterVariable(prefix,commandIndex,parameterIndex)} </#list>)
</#if>
{
    //fill definition
}
    </#list>
    <#assign prefix = NAME + "_CUSTOM_CLUSTER_" + "CLIENT" + "_COMMANDS_">
    <#list 0..<(prefix+"NO")?eval as commandIndex>
        <#assign CommandName = (prefix+"NAME_"+commandIndex)?eval?capitalize?replace(' ','')>
/**************************************************************************//**
\brief Callback on receiving ${CommandName} command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
ZCL_Status_t ${deviceTypeFunctionPrefix}${CommandName}CommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_${CommandName}_t *payload)
{
    appSnprintf("Commands: ${deviceTypeFunctionPrefix}${CommandName}Ind \r\n");
    //fill definition
}
    </#list>


<#--//CLIENT -->
<#elseif DEVICE == "CLIENT">
    <#assign prefix = NAME + "_CUSTOM_CLUSTER_" + "SERVER" + "_COMMANDS_">
    <#list 0..<(prefix+"NO")?eval as commandIndex>
        <#assign CommandName = (prefix+"NAME_"+commandIndex)?eval?capitalize?replace(' ','')>
/**************************************************************************//**
\brief Callback on receiving ${CommandName} command

\param[in] addressing - pointer to addressing information;
\param[in] payloadLength - data payload length;
\param[in] payload - data pointer

\return status of indication routine
******************************************************************************/
ZCL_Status_t ${deviceTypeFunctionPrefix}${CommandName}CommandInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_${CommandName}_t *payload)
{
    appSnprintf("Commands: ${deviceTypeFunctionPrefix}${CommandName}Ind \r\n");
    //fill definition
}
    </#list>
    <#assign prefix = NAME + "_CUSTOM_CLUSTER_" + "CLIENT" + "_COMMANDS_">
    <#list 0..<(prefix+"NO")?eval as commandIndex>
        <#assign CommandName = (prefix+"NAME_"+commandIndex)?eval?capitalize?replace(' ','')>
        <#assign parametersLength = getParametersLength(prefix, commandIndex) >
/**************************************************************************//**
\brief Sends ${CommandName} command

\param[in] mode     - address mode;
\param[in] addr     - short address of destination node;
\param[in] ep       - destination endpoint;
\param[in] srcEp    - source endpoint;
******************************************************************************/
ZCL_Status_t ${deviceTypeFunctionPrefix}Send${CommandName}(APS_AddrMode_t addressMode, ShortAddr_t shortAddress, Endpoint_t endPoint, Endpoint_t sourceEndPoint<#if (parametersLength == 0) >)
<#else>${''} 
    <#list 0..<parametersLength as parameterIndex >,${parameterVariable(prefix,commandIndex,parameterIndex)} </#list>)
</#if>
{
    //fill definition
}
    </#list>
</#if>

