/*******************************************************************************
  ZCL ZCC CUSTOM Cluster Header File

  Company:
    Microchip Technology Inc.

  File Name:
<#assign clusterName = (NAME + "_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','')>
    zcl${clusterName}Cluster.h

  Summary:
    The header file describes the ZCL CUSTOM Cluster and its interface.

  Description:
    The file describes the types and interface of the ZCL CUSTOM Cluster.
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

#ifndef _ZCL${clusterName?upper_case}_H
#define _ZCL${clusterName?upper_case}_H

/*******************************************************************************
                   Includes section
*******************************************************************************/

#include <zcl/include/zcl.h>
#include <zcl/include/clusters.h>
/******************************************************************************
                    Define(s) section
******************************************************************************/
    
//ATTRIBUTE DEFINITION SECTION
<#assign DEVICE = (NAME + "_CUSTOM_CLUSTER_CS")?eval>
<#assign prefix = NAME+"_CUSTOM_CLUSTER_" + DEVICE + "_ATTRIBUTES_">
<#assign clusterName = (NAME + "_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','')>


#define ${clusterName?upper_case}_CLUSTER_ID                                                     0x${(NAME + "_CUSTOM_CLUSTER_ID")?eval}

#define ZCL_${(clusterName)?upper_case}_SERVER_ATTRIBUTES_AMOUNT                      ${(prefix + "NO")?replace("CLIENT","SERVER")?eval}
#define ZCL_${(clusterName)?upper_case}_SERVER_COMMANDS_AMOUNT                        ${(prefix?replace("ATTRIBUTES","COMMANDS") + "NO")?replace("CLIENT","SERVER")?eval} 

#define ZCL_${(clusterName)?upper_case}_CLIENT_ATTRIBUTES_AMOUNT                      ${(prefix + "NO")?replace("SERVER","CLIENT")?eval}
#define ZCL_${(clusterName)?upper_case}_CLIENT_COMMANDS_AMOUNT                        ${(prefix?replace("ATTRIBUTES","COMMANDS") + "NO")?replace("SERVER","CLIENT")?eval}

//Attribute IDs
<#-- //SERVER -->
<#assign prefix = NAME+"_CUSTOM_CLUSTER_" + "SERVER" + "_ATTRIBUTES_">
<#list 0..<(prefix + "NO")?eval as clusterIndex>
${("#define ZCL_" + (clusterName)?upper_case + "_" + (prefix+"NAME_"+clusterIndex)?eval?replace(' ','')?upper_case + "_SERVER_ATTRIBUTE_ID")?right_pad(80)} CCPU_TO_LE16(0X${(prefix+"ID_"+clusterIndex)?eval})
</#list>

<#-- //CLIENT -->
<#assign prefix = NAME+"_CUSTOM_CLUSTER_" + "CLIENT" + "_ATTRIBUTES_">
<#list 0..<(prefix + "NO")?eval as clusterIndex>
${("#define ZCL_" + (clusterName)?upper_case + "_" + (prefix+"NAME_"+clusterIndex)?eval?replace(' ','')?upper_case + "_CLIENT_ATTRIBUTE_ID")?right_pad(80)} CCPU_TO_LE16(0X${(prefix+"ID_"+clusterIndex)?eval})
</#list>

<#function type attributeIndex> <#-- Type handling for DEFINE ATTRIBUTES parameter type-->
  
    <#switch (prefix + "CLASSTYPE_" + attributeIndex)?eval>
        <#case "General Data">
            <#assign datatype = "ZCL_"+(prefix + "TYPE_GENERAL_" + attributeIndex)?eval?remove_beginning("data") + "BIT_DATA_TYPE_ID" >
            <#break>
        <#case "Enumeration">
            <#assign datatype = "ZCL_"+(prefix + "TYPE_ENUM_" + attributeIndex)?eval?remove_beginning("enum")?remove_beginning("data") + "BIT_ENUM_DATA_TYPE_ID"> 
            <#break>
        <#case "Unsigned Integer">
            <#assign datatype = "ZCL_U"+(prefix + "TYPE_UNSIGNED_" + attributeIndex)?eval?remove_beginning("uint") + "BIT_DATA_TYPE_ID">
            <#break>
        <#case "Bitmap">
            <#assign datatype = "ZCL_"+(prefix + "TYPE_BITMAP_" + attributeIndex)?eval?remove_beginning("map") + "BIT_BITMAP_DATA_TYPE_ID">
            <#break>
        <#case "Signed Integer">
            <#assign datatype = "ZCL_S"+(prefix + "TYPE_SIGNED_" + attributeIndex)?eval?remove_beginning("int") + "BIT_DATA_TYPE_ID">
            <#break>
        <#case "Boolean">
            <#assign datatype = "ZCL_BOOLEAN_DATA_TYPE_ID" >
            <#break>
        <#case "String">            
            <#switch (prefix+"TYPE_STRING_"+attributeIndex)?eval>
                <#case "octstr">
                <#assign stringType = "OCTET">
                <#break>
                <#case "octstr16">
                <#assign stringType = "LONG_OCTET">
                <#break>
                <#case "string">
                <#assign stringType = "CHARACTER">
                <#break>
                <#case "string16">
                <#assign stringType = "LONG_CHARACTER">
                <#break>
                <#default>
                <#assign stringType = "CHARACTER">
                <#break>
            </#switch>
            <#assign datatype = "ZCL_"+stringType+"_STRING_DATA_TYPE_ID">
            <#break>
        <#case "Array">
            <#assign datatype = "ZCL_ARRAY_DATA_TYPE_ID">            
            <#break>
    <#default>            
        <#assign datatype = "ZCL_8BIT_DATA_TYPE_ID">
    </#switch>

    <#return datatype>
</#function>


<#function isReportable> <#--Function that says if there are reportable attributes -->
<#assign result = false>
<#list 0..<(prefix + "NO")?eval as attributeIndex>
    <#if (prefix+"PROP_REPORTABLE_"+attributeIndex)?eval>
        <#assign result = true>
    </#if>
</#list>
<#return result>
</#function>

<#assign prefix = NAME+"_CUSTOM_CLUSTER_" + "SERVER" + "_ATTRIBUTES_">
#define ZCL_DEFINE_${(clusterName)?upper_case}_CLUSTER_SERVER_ATTRIBUTES(<#if (isReportable())>min,max</#if>) \
    <#list 0..<(prefix+"NO")?eval as attributeIndex>
        <#assign name = (prefix+"NAME_"+attributeIndex)?eval?capitalize?replace(' ','')>
        <#assign rw =  "ZCL_"+(prefix+"PROP_RW_"+attributeIndex)?eval?replace(' ','')+"_ATTRIBUTE" >
        <#assign id = "ZCL"  + "_" + (clusterName)?upper_case+ "_" + (prefix+"NAME_"+attributeIndex)?eval?replace(' ','')?upper_case+"_SERVER_ATTRIBUTE_ID">
        <#assign Atrtype = type(attributeIndex)>
        <#if (prefix+"PROP_BOUNDARY_"+attributeIndex)?eval>
        <#assign min = (prefix + "PROP_BOUNDARY_MIN_" + attributeIndex)?eval>
        <#assign max = (prefix + "PROP_BOUNDARY_MAX_" + attributeIndex)?eval>
        </#if>
        <#if ((prefix+"PROP_REPORTABLE_"+attributeIndex)?eval && (prefix+"PROP_BOUNDARY_"+attributeIndex)?eval)>
        DEFINE_REPORTABLE_ATTRIBUTE_WITH_BOUNDARY(${name}, ${rw}, ${id}, ${Atrtype}, min, max, 0x${min}, 0x${max}) <#if (attributeIndex?is_last == false)>, \</#if>
        <#elseif ((prefix+"PROP_REPORTABLE_"+attributeIndex)?eval)>
        DEFINE_REPORTABLE_ATTRIBUTE(${name}, ${rw}, ${id}, ${Atrtype}, min, max) <#if (attributeIndex?is_last == false)>, \</#if>
        <#elseif ((prefix+"PROP_BOUNDARY_"+attributeIndex)?eval)>
        DEFINE_ATTRIBUTE_WITH_BOUNDARY(${name}, ${rw}, ${id}, ${Atrtype}, 0x${min}, 0x${max}) <#if (attributeIndex?is_last == false)>, \</#if>
        <#else>
        DEFINE_ATTRIBUTE(${name}, ${rw}, ${id}, ${Atrtype}) <#if (attributeIndex?is_last == false)>, \</#if>
        </#if>
    </#list>

<#assign prefix = NAME+"_CUSTOM_CLUSTER_" + "CLIENT" + "_ATTRIBUTES_">
#define ZCL_DEFINE_${(clusterName)?upper_case}_CLUSTER_CLIENT_ATTRIBUTES(<#if (isReportable())>min,max</#if>) \
    <#list 0..<(prefix+"NO")?eval as attributeIndex>
        <#assign name = (prefix+"NAME_"+attributeIndex)?eval?capitalize?replace(' ','')>
        <#assign rw =  "ZCL_"+(prefix+"PROP_RW_"+attributeIndex)?eval?replace(' ','')+"_ATTRIBUTE" >
        <#assign id = "ZCL"  + "_" + (clusterName)?upper_case+ "_" + (prefix+"NAME_"+attributeIndex)?eval?replace(' ','')?upper_case+"_CLIENT_ATTRIBUTE_ID">
        <#assign Atrtype = type(attributeIndex)>
        <#if (prefix+"PROP_BOUNDARY_"+attributeIndex)?eval>
        <#assign min = (prefix + "PROP_BOUNDARY_MIN_" + attributeIndex)?eval>
        <#assign max = (prefix + "PROP_BOUNDARY_MAX_" + attributeIndex)?eval>
        </#if>
        <#if ((prefix+"PROP_REPORTABLE_"+attributeIndex)?eval && (prefix+"PROP_BOUNDARY_"+attributeIndex)?eval)>
        DEFINE_REPORTABLE_ATTRIBUTE_WITH_BOUNDARY(${name}, ${rw}, ${id}, ${Atrtype}, min, max, 0x${min}, 0x${max}) <#if (attributeIndex?is_last == false)>, \</#if>
        <#elseif ((prefix+"PROP_REPORTABLE_"+attributeIndex)?eval)>
        DEFINE_REPORTABLE_ATTRIBUTE(${name}, ${rw}, ${id}, ${Atrtype}, min, max) <#if (attributeIndex?is_last == false)>, \</#if>
        <#elseif ((prefix+"PROP_BOUNDARY_"+attributeIndex)?eval)>
        DEFINE_ATTRIBUTE_WITH_BOUNDARY(${name}, ${rw}, ${id}, ${Atrtype}, 0x${min}, 0x${max}) <#if (attributeIndex?is_last == false)>, \</#if>
        <#else>
        DEFINE_ATTRIBUTE(${name}, ${rw}, ${id}, ${Atrtype}) <#if (attributeIndex?is_last == false)>, \</#if>
        </#if>
    </#list>

<#assign prefix = NAME+"_CUSTOM_CLUSTER_" + DEVICE + "_ATTRIBUTES_">


#define ${(clusterName)?upper_case}_CLUSTER_ZCL_SERVER_CLUSTER_TYPE(clattributes, clcommands)                                                \
  {                                                                                                              \
    .id = ${(clusterName)?upper_case}_CLUSTER_ID,                                                                                      \
    .options = {.type = ZCL_SERVER_CLUSTER_TYPE, .security = ZCL_NETWORK_KEY_CLUSTER_SECURITY},                  \
    .attributesAmount = ZCL_${(clusterName)?upper_case}_SERVER_ATTRIBUTES_AMOUNT,                                              \
    .attributes = (uint8_t *) clattributes,                                                                      \
    .commandsAmount = ZCL_${(clusterName)?upper_case}_SERVER_COMMANDS_AMOUNT,                                                  \
    .commands = (uint8_t *)clcommands                                                                            \
  }

#define ${(clusterName)?upper_case}_CLUSTER_ZCL_CLIENT_CLUSTER_TYPE(clattributes, clcommands)                                                \
  {                                                                                                              \
    .id = ${(clusterName)?upper_case}_CLUSTER_ID,                                                                                      \
    .options = {.type = ZCL_CLIENT_CLUSTER_TYPE, .security = ZCL_NETWORK_KEY_CLUSTER_SECURITY},                  \
    .attributesAmount = ZCL_${(clusterName)?upper_case}_CLIENT_ATTRIBUTES_AMOUNT,                                              \
    .attributes = (uint8_t *) clattributes,                                                                      \
    .commandsAmount = ZCL_${(clusterName)?upper_case}_CLIENT_COMMANDS_AMOUNT,                                                  \
    .commands = (uint8_t *)clcommands                                                                            \
  }


  #define DEFINE_${(clusterName)?upper_case}_CLUSTER(cltype, clattributes, clcommands) \
    ${(clusterName)?upper_case}_CLUSTER_##cltype(clattributes, clcommands)


// ATTRIBUTE DEFINITION END
<#assign DEVICE = (NAME + "_CUSTOM_CLUSTER_CS")?eval>
<#assign prefix = NAME+"_CUSTOM_CLUSTER_" + DEVICE + "_COMMANDS_">
<#assign clusterName = (NAME + "_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','')>
//COMMAND DEFINITION SECTION

//Server Commands
<#assign prefix = NAME+"_CUSTOM_CLUSTER_" + "SERVER" + "_COMMANDS_">
<#list 0..<(prefix + "NO")?eval as commandIndex>
${("#define ZCL_" + clusterName?upper_case + "_" + (prefix + "NAME_"+commandIndex)?eval?upper_case?replace(" ","") + "_COMMAND_ID")?right_pad(80)} 0x${(prefix + "ID_"+commandIndex)?eval?upper_case}
</#list>

//Client Commands
<#assign prefix = NAME+"_CUSTOM_CLUSTER_" + "CLIENT" + "_COMMANDS_">
<#list 0..<(prefix + "NO")?eval as commandIndex>
${("#define ZCL_" + clusterName?upper_case + "_" + (prefix + "NAME_"+commandIndex)?eval?upper_case?replace(" ","") + "_COMMAND_ID")?right_pad(80)} 0x${(prefix + "ID_"+commandIndex)?eval?upper_case}
</#list>
<#assign prefix = NAME+"_CUSTOM_CLUSTER_" + DEVICE + "_COMMANDS_">

<#--


-->

<#assign clientCommandsCount = (NAME+"_CUSTOM_CLUSTER_" + "CLIENT" + "_COMMANDS_NO")?eval  >
<#assign loopEnd = (clientCommandsCount != 0) >

<#assign prefix = NAME+"_CUSTOM_CLUSTER_" + "SERVER" + "_COMMANDS_">

#define ZCL_DEFINE_${clusterName?upper_case}_CLUSTER_COMMANDS(<#if ((prefix + "NO")?eval > 0 || loopEnd) >\<#else>)</#if>
    <#--//SERVER -->
    <#assign prefix = NAME+"_CUSTOM_CLUSTER_" + "SERVER" + "_COMMANDS_">
    <#list 0..<(prefix + "NO")?eval as commandIndex>           
        ${(prefix + "NAME_"+commandIndex)?eval?capitalize?replace(" ","")}CommandInd <#if (commandIndex?has_next || loopEnd)  >,<#else>)</#if> \
    </#list>
    <#--//CLIENT -->
    <#assign prefix = NAME+"_CUSTOM_CLUSTER_" + "CLIENT" + "_COMMANDS_">
    <#list 0..<(prefix + "NO")?eval as commandIndex>           
        ${(prefix + "NAME_"+commandIndex)?eval?capitalize?replace(" ","")}CommandInd <#if (commandIndex?has_next )  >,<#else>)</#if> \
    </#list>
    <#--//SERVER -->
    <#assign prefix = NAME+"_CUSTOM_CLUSTER_" + "SERVER" + "_COMMANDS_">
    <#list 0..<(prefix + "NO")?eval as commandIndex>
    ${"DEFINE_COMMAND(" + (prefix + "NAME_"+commandIndex)?eval?capitalize?replace(" ","") + "Command, ZCL_" + clusterName?upper_case + "_" + (prefix + "NAME_"+commandIndex)?eval?upper_case?replace(" ","") + "_COMMAND_ID, "} \
        ${"COMMAND_OPTIONS(" + "SERVER_TO_CLIENT" + " , ZCL_" + (prefix + "RESPONSE_"+commandIndex)?eval?replace(' ','_') + " , ZCL_COMMAND_" + (prefix + "ACK_"+commandIndex)?eval?replace(' ','_') + "), " +  (prefix + "NAME_"+commandIndex)?eval?capitalize?replace(" ","") + "CommandInd)"}<#if (commandIndex?has_next || loopEnd)>, \</#if>
    </#list>
    <#--//CLIENT -->
    <#assign prefix = NAME+"_CUSTOM_CLUSTER_" + "CLIENT" + "_COMMANDS_">
    <#list 0..<(prefix + "NO")?eval as commandIndex>
    ${"DEFINE_COMMAND(" + (prefix + "NAME_"+commandIndex)?eval?capitalize?replace(" ","") + "Command, ZCL_" + clusterName?upper_case + "_" + (prefix + "NAME_"+commandIndex)?eval?upper_case?replace(" ","") + "_COMMAND_ID, "} \
        ${"COMMAND_OPTIONS(" + "CLIENT_TO_SERVER" + " , ZCL_" + (prefix + "RESPONSE_"+commandIndex)?eval?replace(' ','_') + " , ZCL_COMMAND_" + (prefix + "ACK_"+commandIndex)?eval?replace(' ','_') + "), " +  (prefix + "NAME_"+commandIndex)?eval?capitalize?replace(" ","") + "CommandInd)"}<#if (commandIndex?has_next)>, \</#if>
    </#list>
    

<#-- [ END OF BLOCK A ]-->

/******************************************************************************
                    Types section
******************************************************************************/
//ATTRIBUTE's TYPES SECTION
<#assign DEVICE = (NAME + "_CUSTOM_CLUSTER_CS")?eval>
<#assign prefix = NAME+"_CUSTOM_CLUSTER_" + DEVICE + "_ATTRIBUTES_">
<#assign clusterName = (NAME + "_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','')>

<#--//BITMAP -->
<#--//SERVER -->
<#assign prefix = NAME+"_CUSTOM_CLUSTER_" + "SERVER" + "_ATTRIBUTES_">
<#list 0..<(prefix+"NO")?eval as attributeIndex>
<#if ( (prefix+"CLASSTYPE_"+attributeIndex)?eval == "Bitmap") >
typedef struct PACK _ZCL_${clusterName?upper_case}_${(prefix+"NAME_"+attributeIndex)?eval?upper_case?replace(' ','')}Bitmap_t
{
    
}ZCL_${clusterName?upper_case}${(prefix+"NAME_"+attributeIndex)?eval?capitalize?replace(' ','')}Bitmap_t;

</#if>
</#list>
<#--//CLIENT -->
<#assign prefix = NAME+"_CUSTOM_CLUSTER_" + "CLIENT" + "_ATTRIBUTES_">
<#list 0..<(prefix+"NO")?eval as attributeIndex>
<#if ( (prefix+"CLASSTYPE_"+attributeIndex)?eval == "Bitmap") >
typedef struct PACK _ZCL_${clusterName?upper_case}_${(prefix+"NAME_"+attributeIndex)?eval?upper_case?replace(' ','')}Bitmap_t
{
    
}ZCL_${clusterName?upper_case}${(prefix+"NAME_"+attributeIndex)?eval?capitalize?replace(' ','')}Bitmap_t;

</#if>
</#list>
<#--//ENUMERATION -->
<#--//SERVER -->
<#assign prefix = NAME+"_CUSTOM_CLUSTER_" + "SERVER" + "_ATTRIBUTES_">
<#list 0..<(prefix+"NO")?eval as attributeIndex>
<#if ( (prefix+"CLASSTYPE_"+attributeIndex)?eval == "Enumeration") >
typedef enum _ZCL_${clusterName?capitalize}${(prefix+"NAME_"+attributeIndex)?eval?capitalize?replace(' ','')}Enum_t
{
    ${clusterName?upper_case}_${(prefix+"NAME_"+attributeIndex)?eval?upper_case}_${attributeIndex} = 0x00
}ZCL_${clusterName?capitalize}${(prefix+"NAME_"+attributeIndex)?eval?capitalize?replace(' ','')}Enum_t;

</#if>
</#list>
<#--//CLIENT -->
<#assign prefix = NAME+"_CUSTOM_CLUSTER_" + "CLIENT" + "_ATTRIBUTES_">
<#list 0..<(prefix+"NO")?eval as attributeIndex>
<#if ( (prefix+"CLASSTYPE_"+attributeIndex)?eval == "Enumeration") >
typedef enum _ZCL_${clusterName?capitalize}${(prefix+"NAME_"+attributeIndex)?eval?capitalize?replace(' ','')}Enum_t
{
    ${clusterName?upper_case}_${(prefix+"NAME_"+attributeIndex)?eval?upper_case}_${attributeIndex} = 0x00
}ZCL_${clusterName?capitalize}${(prefix+"NAME_"+attributeIndex)?eval?capitalize?replace(' ','')}Enum_t;

</#if>
</#list>


<#-- //END OF IMPLEMENTATION FOR BITMAP AND ENUM STRUCTS -->
<#global string = "">
<#function dtype attributeIndex> <#-- function to handle datatype of value inside struct-->
   
    <#assign string = "">
    <#switch (prefix + "CLASSTYPE_" + attributeIndex)?eval>
        <#case "General Data">
            <#assign datatype = "uint"+(prefix + "TYPE_GENERAL_" + attributeIndex)?eval?remove_beginning("data") + "_t" >
            <#break>
        <#case "Enumeration">
            <#assign datatype = "uint8_t" >
            <#break>
        <#case "Unsigned Integer">
            <#assign datatype = (prefix + "TYPE_UNSIGNED_" + attributeIndex)?eval + "_t">
            <#break>
        <#case "Bitmap">
            <#assign datatype = "uint8_t">
            <#break>
        <#case "Signed Integer">
            <#assign datatype = (prefix + "TYPE_SIGNED_" + attributeIndex)?eval + "_t">
            <#break>
        <#case "Boolean">
            <#assign datatype = "bool" >
            <#break>
        <#case "String">
            <#assign datatype = "uint8_t">
            <#if (prefix + "TYPE_STRING_" + attributeIndex)?eval?contains("16")>
                <#assign datatype = "uint16_t">
            </#if>
            <#assign string = "[32]"> <#-- the suffix for array types -->
            <#break>
        <#case "Array">
            <#assign datatype = "uint8_t">
            <#assign string = "["+ (prefix + "TYPE_ARRAY_" + attributeIndex)?eval + "]">
            <#break>
    <#default>            
        <#assign datatype = "uint8_t">
    </#switch>

    <#return datatype>
</#function>
<#-- //start of attribute struct implementation -->
typedef struct PACK
{
<#--//SERVER -->
<#assign prefix = NAME+"_CUSTOM_CLUSTER_" + "SERVER" + "_ATTRIBUTES_">
<#list 0..<(prefix+"NO")?eval as attributeIndex>
struct PACK
  {
    ZCL_AttributeId_t   id;
    uint8_t             type;
    uint8_t             properties;
    <#assign datatype= dtype(attributeIndex)>
    ${datatype?right_pad(20)}value${string};
    <#if (prefix+"PROP_REPORTABLE_"+attributeIndex)?eval>
    ZCL_ReportTime_t    reportCounter;     //!<For internal use only
    ZCL_ReportTime_t    minReportInterval; //!<Minimum reporting interval field value
    ZCL_ReportTime_t    maxReportInterval; //!<Maximum reporting interval field value
    ${datatype?right_pad(20)} reportableChange${string};  //!<Reporting change field value
    ZCL_ReportTime_t    timeoutPeriod;     //!<Timeout period field value
    ${datatype?right_pad(20)} lastReportedValue${string}; //!<Last reported value
    </#if>
    <#if (prefix+"PROP_BOUNDARY_"+attributeIndex)?eval>
    ${datatype?right_pad(20)} minVal${string};
    ${datatype?right_pad(20)} maxVal${string};
    </#if>
   } ${(prefix+"NAME_"+attributeIndex)?eval?capitalize?replace(' ','')};

</#list>
}ZCL_${clusterName?capitalize}Cluster${"SERVER"?capitalize}Attributes_t;

typedef struct PACK
{
<#--//CLIENT -->
<#assign prefix = NAME+"_CUSTOM_CLUSTER_" + "CLIENT" + "_ATTRIBUTES_">
<#list 0..<(prefix+"NO")?eval as attributeIndex>
struct PACK
  {
    ZCL_AttributeId_t   id;
    uint8_t             type;
    uint8_t             properties;
    <#assign datatype= dtype(attributeIndex)>
    ${datatype?right_pad(20)}value${string};
    <#if (prefix+"PROP_REPORTABLE_"+attributeIndex)?eval>
    ZCL_ReportTime_t    reportCounter;     //!<For internal use only
    ZCL_ReportTime_t    minReportInterval; //!<Minimum reporting interval field value
    ZCL_ReportTime_t    maxReportInterval; //!<Maximum reporting interval field value
    ${datatype?right_pad(20)}reportableChange${string};  //!<Reporting change field value
    ZCL_ReportTime_t    timeoutPeriod;     //!<Timeout period field value
    ${datatype?right_pad(20)}lastReportedValue${string}; //!<Last reported value
    </#if>
    <#if (prefix+"PROP_BOUNDARY_"+attributeIndex)?eval>
    ${datatype?right_pad(20)} minVal${string};
    ${datatype?right_pad(20)} maxVal${string};
    </#if>
   } ${(prefix+"NAME_"+attributeIndex)?eval?capitalize?replace(' ','')};

</#list>
}ZCL_${clusterName?capitalize}Cluster${"CLIENT"?capitalize}Attributes_t;


// COMMANDS TYPE DEFINITION
<#assign DEVICE = (NAME + "_CUSTOM_CLUSTER_CS")?eval>
<#assign clusterName = (NAME + "_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','')>

<#-- //Enumeration structs for command parameter Enumeration types -->

<#--//SERVER -->
<#assign prefix = NAME +"_CUSTOM_CLUSTER_" + "SERVER" + "_COMMANDS">
<#list 0..<((prefix + "_NO")?eval) as commandIndex >
    <#list 0..<((prefix + "_PARAM_NO_" + commandIndex )?eval) as paramIndex>
    <#if ((prefix + "_CLASSTYPE_" + commandIndex + "_" + paramIndex)?eval == "Enumeration")>
    <#assign commandName = (prefix + "_NAME_" + commandIndex)>
typedef struct 
{
    //Fill enum here
} ZCL_${commandName}${(prefix +"_PARAMNAME_" + commandIndex + "_" + paramIndex)?eval?capitalize?replace(" ","")}CommandEnum_t;

    </#if>
    </#list>
</#list>

<#--//CLIENT -->
<#assign prefix = NAME +"_CUSTOM_CLUSTER_" + "SERVER" + "_COMMANDS">
<#list 0..<((prefix + "_NO")?eval) as commandIndex >
    <#list 0..<((prefix + "_PARAM_NO_" + commandIndex )?eval) as paramIndex>
    <#if ((prefix + "_CLASSTYPE_" + commandIndex + "_" + paramIndex)?eval == "Enumeration")>
    <#assign commandName = (prefix + "_NAME_" + commandIndex)?eval?capitalize>
typedef struct 
{
    //Fill enum here
} ZCL_${commandName}${(prefix +"_PARAMNAME_" + commandIndex + "_" + paramIndex)?eval?capitalize?replace(" ","")}CommandEnum_t;

    </#if>
    </#list>
</#list>

<#-- //Command structs, given for the parameters in every command as a structure datatype -->

<#-- //SERVER -->
<#assign prefix = NAME +"_CUSTOM_CLUSTER_" + "SERVER" + "_COMMANDS">
<#list 0..<((prefix +"_NO")?eval) as commandIndex >
typedef struct PACK
{
    <#list 0..<((prefix + "_PARAM_NO_" + commandIndex )?eval) as paramIndex>
        <#-- [ BLOCK datatype] -->
        <#assign string = "">
        <#switch (prefix + "_CLASSTYPE_" + commandIndex + "_" + paramIndex)?eval>
        <#case "General Data">
            <#assign datatype = "uint"+( prefix + "_TYPE_GENERAL_" + commandIndex + "_" + paramIndex)?eval?remove_beginning("data") + "_t" >
            <#break>
        <#case "Enumeration">
            <#assign datatype = "uint8_t" >
            <#break>
        <#case "Unsigned Integer">
            <#assign datatype = (prefix + "_TYPE_UNSIGNED_" + commandIndex + "_" + paramIndex)?eval + "_t">
            <#break>
        <#case "Bitmap">
            <#assign datatype = "uint8_t">
            <#break>
        <#case "Signed Integer">
            <#assign datatype = (prefix + "_TYPE_SIGNED_" + commandIndex + "_" + paramIndex)?eval + "_t">
            <#break>
        <#case "Boolean">
            <#assign datatype = "bool" >
            <#break>
        <#case "String">
            <#assign datatype = "uint8_t">
            <#if (prefix + "_TYPE_STRING_" + commandIndex + "_" + paramIndex)?eval?contains("16")>
                <#assign datatype = "uint16_t">
            </#if>
            <#assign string = "[32]"> <#-- the suffix for array types -->
            <#break>
        <#case "Array">
            <#assign datatype = "uint8_t">
            <#assign string = "["+ (prefix + "_TYPE_ARRAY_" + commandIndex + "_" + paramIndex)?eval + "]">
            <#break>
        <#default>      
                  
        </#switch>
        <#-- [ end of BLOCK datatype]-->
        ${datatype} ${(prefix + "_PARAMNAME_" + commandIndex + "_" + paramIndex)?eval?capitalize?replace(' ','')}${string};
    </#list>

}ZCL_${(prefix + "_NAME_"+commandIndex)?eval?capitalize?replace(" ","")}_t;

</#list>

<#-- //CLIENT -->
<#assign prefix = NAME +"_CUSTOM_CLUSTER_" + "CLIENT" + "_COMMANDS">
<#list 0..<((prefix +"_NO")?eval) as commandIndex >
typedef struct PACK
{
    <#list 0..<((prefix + "_PARAM_NO_" + commandIndex )?eval) as paramIndex>
        <#-- [ BLOCK datatype] -->
        <#assign string = "">
        <#switch (prefix + "_CLASSTYPE_" + commandIndex + "_" + paramIndex)?eval>
        <#case "General Data">
            <#assign datatype = "uint"+( prefix + "_TYPE_GENERAL_" + commandIndex + "_" + paramIndex)?eval?remove_beginning("data") + "_t" >
            <#break>
        <#case "Enumeration">
            <#assign datatype = "uint8_t" >
            <#break>
        <#case "Unsigned Integer">
            <#assign datatype = (prefix + "_TYPE_UNSIGNED_" + commandIndex + "_" + paramIndex)?eval + "_t">
            <#break>
        <#case "Bitmap">
            <#assign datatype = "uint8_t">
            <#break>
        <#case "Signed Integer">
            <#assign datatype = (prefix + "_TYPE_SIGNED_" + commandIndex + "_" + paramIndex)?eval + "_t">
            <#break>
        <#case "Boolean">
            <#assign datatype = "bool" >
            <#break>
        <#case "String">
            <#assign datatype = "uint8_t">
            <#if (prefix + "_TYPE_STRING_" + commandIndex + "_" + paramIndex)?eval?contains("16")>
                <#assign datatype = "uint16_t">
            </#if>
            <#assign string = "[32]"> <#-- the suffix for array types -->
            <#break>
        <#case "Array">
            <#assign datatype = "uint8_t">
            <#assign string = "["+ (prefix + "_TYPE_ARRAY_" + commandIndex + "_" + paramIndex)?eval + "]">
            <#break>
        <#default>      
                  
        </#switch>
        <#-- [ end of BLOCK datatype]-->
        ${datatype} ${(prefix + "_PARAMNAME_" + commandIndex + "_" + paramIndex)?eval?capitalize?replace(' ','')}${string};
    </#list>

}ZCL_${(prefix + "_NAME_"+commandIndex)?eval?capitalize?replace(" ","")}_t;

</#list>

typedef struct
{
    <#--//SERVER -->
    <#assign prefix = NAME +"_CUSTOM_CLUSTER_" + "SERVER" + "_COMMANDS">
    <#list 0..<((prefix + "_NO")?eval) as commandIndex> 
    <#assign commandNamei = (prefix +"_NAME_"+commandIndex)?eval?capitalize?replace(" ","") >
struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*${commandNamei}Command)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_${commandNamei}_t *payload);
  } ${commandNamei}Command;

    </#list>

    <#--//CLIENT -->
    <#assign prefix = NAME +"_CUSTOM_CLUSTER_" + "CLIENT" + "_COMMANDS">
    <#list 0..<((prefix + "_NO")?eval) as commandIndex> 
    <#assign commandNamei = (prefix +"_NAME_"+commandIndex)?eval?capitalize?replace(" ","") >
struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*${commandNamei}Command)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_${commandNamei}_t *payload);
  } ${commandNamei}Command;

    </#list>

} ZCL_${clusterName?capitalize}ClusterCommands_t;

#endif
