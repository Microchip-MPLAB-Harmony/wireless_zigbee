<#assign DEVICE = (NAME + "_CUSTOM_CLUSTER_CS")?eval>
<#assign clusterName = (NAME + "_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','')>

<#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
/*******************************************************************************
  ${NAME?upper_case} Custom Cluster Header File

  Company:
    Microchip Technology Inc.

  File Name:
   ${deviceTypeFunctionPrefix}${clusterName}Cluster.h

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

#include <zcl/include/zcl${clusterName}Cluster.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define ${clusterName?upper_case}_MIN_REPORT_PERIOD ${(NAME + "_CUSTOM_CLUSTER_REPORT_MIN")?eval}
#define ${clusterName?upper_case}_MAX_REPORT_PERIOD ${(NAME + "_CUSTOM_CLUSTER_REPORT_MAX")?eval}

/*******************************************************************************

                    Prototypes section
*******************************************************************************/

void ${deviceTypeFunctionPrefix}${clusterName}Init(void);

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

<#--//FUNCTION PROTOTYPES -->
<#if (DEVICE == "SERVER") || (DEVICE == "BOTH")>
    <#--//SERVER -->
    <#-- Function prototypes for the send commands and indications -->
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
</#if>
<#if (DEVICE == "CLIENT") || (DEVICE == "BOTH") >
    <#--//CLIENT -->
    <#-- Function prototypes for the send commands and indications -->
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

<#if (DEVICE == "SERVER") || (DEVICE == "BOTH") >
//Custom Cluster Attributes
extern ZCL_${clusterName?capitalize}Cluster${"SERVER"?capitalize}Attributes_t ${clusterName?lower_case}${"SERVER"?capitalize}ClusterAttributes;
</#if>

<#if (DEVICE == "CLIENT") || (DEVICE == "BOTH") >
//Custom Cluster Attributes
extern ZCL_${clusterName?capitalize}Cluster${"CLIENT"?capitalize}Attributes_t ${clusterName?lower_case}${"CLIENT"?capitalize}ClusterAttributes;
</#if>

//Custom Cluster Commands
extern PROGMEM_DECLARE (ZCL_${clusterName?capitalize}ClusterCommands_t ${clusterName?lower_case}ClusterCommands);



// Custom Cluster`s backup & Restore Function Declaration
<#if DEVICE_DEEP_SLEEP_ENABLED>
    <#if (DEVICE == "SERVER") || (DEVICE == "BOTH")>
    void ${deviceTypeFunctionPrefix}cc${NAME}BackupAttribute(void);
    </#if>
</#if>

<#if DEVICE_DEEP_SLEEP_ENABLED>
    <#if (DEVICE == "SERVER") || (DEVICE == "BOTH")>
void ${deviceTypeFunctionPrefix}cc${NAME}RestoreAttribute(void);
    </#if>
</#if>
