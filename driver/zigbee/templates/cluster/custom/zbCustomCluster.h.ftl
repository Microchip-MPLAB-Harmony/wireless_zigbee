<#assign DEVICE = (NAME + "_CUSTOM_CLUSTER_CS")?eval>
<#assign prefix = NAME + "_CUSTOM_CLUSTER_" + DEVICE + "_COMMANDS_">
<#assign clusterName = (NAME + "_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','')>
<#global arraySize = "">
<#function type commandIndex paramIndex>

    <#assign arraySize = "">
    <#switch (prefix + "CLASSTYPE_" + commandIndex + "_" + paramIndex)?eval>
        <#case "General Data">
            <#assign datatype = "uint"+(prefix + "TYPE_GENERAL_" + commandIndex + "_" + paramIndex)?eval?remove_beginning("data") + "_t" >
            <#break>
        <#case "Enumeration">
            <#assign datatype = "uint8_t" >
            <#break>
        <#case "Unsigned Integer">
            <#assign datatype = (prefix + "TYPE_UNSIGNED_" + commandIndex + "_" + paramIndex)?eval + "_t">
            <#break>
        <#case "Bitmap">
            <#assign datatype = "uint8_t">
            <#break>
        <#case "Signed Integer">
            <#assign datatype = (prefix + "TYPE_SIGNED_" + commandIndex + "_" + paramIndex)?eval + "_t">
            <#break>
        <#case "Boolean">
            <#assign datatype = "bool" >
            <#break>
        <#case "String">
            <#assign datatype = "uint8_t">
            <#if (prefix + "TYPE_STRING_" + commandIndex + "_" + paramIndex)?eval?contains("16")>
                <#assign datatype = "uint16_t">
            </#if>
            <#assign arraySize = "[32]"> <#-- the suffix for array types -->
            <#break>
        <#case "Array">
            <#assign datatype = "uint8_t">
            <#assign arraySize = "["+ (prefix + "TYPE_ARRAY_" + commandIndex + "_" + paramIndex)?eval + "]">
            <#break>
    <#default>            
        <#assign datatype = "uint8_t">
    </#switch>

    <#return datatype>
</#function>


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

<#if (DEVICE == "CLIENT")>
    <#assign commandSuffix = "">
    <#assign commandPrefix = "Send">
    <#assign ClientArguments = "APS_AddrMode_t addressMode, ShortAddr_t shortAddress, Endpoint_t endPoint, Endpoint_t sourceEndPoint\n\t">
    
<#else>
    <#assign commandSuffix = "Ind">
    <#assign commandPrefix = "">
    <#assign ClientArguments = "">
</#if>
void ${deviceTypeFunctionPrefix}${clusterName}Init(void);
<#list 0..<(prefix+"NO")?eval as commandIndex>
<#assign CommandName = (prefix+"NAME_"+commandIndex)?eval?capitalize?replace(' ','')>
<#if (commandSuffix == "Ind")>  <#-- SERVER -->
<#assign ClientArguments = "ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_"+ CommandName + "_t *payload">
<#t>ZCL_Status_t ${deviceTypeFunctionPrefix + CommandName + commandPrefix}Command${commandSuffix}(${ClientArguments});
</#if>
<#if (commandSuffix == "")>   <#-- CLIENT -->
<#t>ZCL_Status_t ${deviceTypeFunctionPrefix + CommandName + commandPrefix}Command${commandSuffix}(${ClientArguments}<#list 0..<(prefix+"PARAM_NO_"+commandIndex)?eval as paramIndex>, ${type(commandIndex,paramIndex)} ${((prefix + "PARAMNAME_" + commandIndex + "_" + paramIndex)?eval?capitalize?replace(' ','')!"param") + arraySize }</#list>);
</#if>
</#list>

/******************************************************************************
                    Global variables
******************************************************************************/

//Custom Cluster Attributes
extern ZCL_${clusterName?capitalize}Cluster${DEVICE?capitalize}Attributes_t ${clusterName?lower_case}${DEVICE?capitalize}ClusterAttributes;
//Custom Cluster Commands
extern PROGMEM_DECLARE (ZCL_${clusterName?capitalize}ClusterCommands_t ${clusterName?lower_case}${DEVICE?capitalize}ClusterCommands);



