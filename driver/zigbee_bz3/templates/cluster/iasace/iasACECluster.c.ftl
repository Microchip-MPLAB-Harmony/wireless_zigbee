/*******************************************************************************
  IAS-ACE Cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    iasACECluster.c

  Summary:
    This file contains the IAS-ACE Cluster interface.

  Description:
    This file contains the IAS-ACE Cluster interface.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_IAS_ACE)

/******************************************************************************
                    Includes section
******************************************************************************/
#include <z3device/ias_ace/include/iasACECluster.h>
#include <z3device/ias_ace/include/iasACEAceCluster.h>
#if APP_ENABLE_CONSOLE == 1
#include <app_zigbee/zigbee_console/console.h>
#endif
#include <z3device/ias_ace/include/iasACEZoneCluster.h>
#include <zcl/clusters/include/identifyCluster.h>
#include <z3device/clusters/include/basicCluster.h>
#include <z3device/ias_ace/include/iasacebasiccluster.h>
#include <z3device/ias_ace/include/iasacebasiccluster.h>
#include <z3device/ias_ace/include/iasaceidentifycluster.h>
#include <z3device/ias_ace/include/iasACEGroupsCluster.h>
#include <zcl/include/zclIasZoneCluster.h>
#include <zcl/include/zclIasACECluster.h>
#include <zcl/include/zclZllBasicCluster.h>
#include <zcl/include/zclZllIdentifyCluster.h>
#include <z3device/clusters/include/haClusters.h>
#include <zcl/include/zclCommandManager.h>

<#compress>
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >

  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  <#assign devicetype = DEVICE_TYPE_FILE_PATH >
#include <z3device/${devicetype}/include/${deviceTypeFunctionPrefix + clusterName}Cluster.h>
#include <zcl/include/zcl${clusterName}Cluster.h>

  </#list>

</#compress>

/******************************************************************************
                    Prototypes section
******************************************************************************/
/******************************************************************************
                    Global variables
******************************************************************************/
//IAS ACE Server Clusters
ZCL_Cluster_t iasACEServerClusters[IAS_ACE_SERVER_CLUSTERS_COUNT] =
{
   ZCL_DEFINE_BASIC_CLUSTER_SERVER(&iasACEBasicClusterServerAttributes,&iasACEBasicClusterServerCommands),
   DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &iasACEIdentifyClusterServerAttributes, &iasACEIdentifyCommands),
   DEFINE_IAS_ZONE_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &iasACEZoneClusterServerAttributes, &iasACEZoneClusterServerCommands),
   DEFINE_GROUPS_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &iasACEgroupsClusterServerAttributes, &iasACEGroupsCommands),
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER") || (DEVICE == "BOTH") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
   DEFINE_${(clusterName)?upper_case}_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &${clusterName?lower_case}${"SERVER"?capitalize}ClusterAttributes, &${clusterName?lower_case}ClusterCommands),
  </#if>
  </#list>
};

//IAS ACE Server Cluster Init Functions
void (*iasACEServerClusterInitFunctions[IAS_ACE_SERVER_CLUSTER_INIT_COUNT])() =
{
  iasBasicClusterInit,
  iasIdentifyClusterInit,
  iasZoneClusterInit,
  iasGroupsClusterInit,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER") || (DEVICE == "BOTH") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${deviceTypeFunctionPrefix}${clusterName}Init,
  </#if>
  </#list>
};

//IAS ACE Server Cluster lists
ClusterId_t iasACEServerClusterIds[IAS_ACE_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  IAS_ZONE_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "SERVER") || (DEVICE == "BOTH") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${clusterName?upper_case}_CLUSTER_ID,
  </#if>
  </#list>
};

//IAS ACE Client Cluster lists
ZCL_Cluster_t iasACEClientClusters[IAS_ACE_CLIENT_CLUSTERS_COUNT] =
{
   ZCL_DEFINE_BASIC_CLUSTER_SERVER(&iasACEBasicClusterClientAttributes, NULL),
   DEFINE_GROUPS_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &iasACEgroupsClusterClientAttributes, &iasACEGroupsCommands),
   DEFINE_IDENTIFY_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &iasACEIdentifyClusterClientAttributes, &iasACEIdentifyCommands),
   DEFINE_IAS_ACE_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &iasACEAceClusterClientAttributes , &iasACEClusterCommands),
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT") || (DEVICE == "BOTH") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
   DEFINE_${(clusterName)?upper_case}_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &${clusterName?lower_case}${"CLIENT"?capitalize}ClusterAttributes, &${clusterName?lower_case}ClusterCommands),
  </#if>
  </#list>
};

void (*iasACEClientClusterInitFunctions[IAS_ACE_CLIENT_CLUSTERS_COUNT])() =
{
  iasBasicClusterInit,
  iasIdentifyClusterInit,
  iasACEClusterInit,
  iasGroupsClusterInit,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT") || (DEVICE == "BOTH") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${deviceTypeFunctionPrefix}${clusterName}Init,
  </#if>
  </#list>
#ifdef OTAU_CLIENT
  NULL // oatu client init fucntion
#endif
};

//IAS ACE Client Cluster IDs
ClusterId_t iasACEClientClusterIds[IAS_ACE_CLIENT_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  IAS_ACE_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  <#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >
  <#if (DEVICE == "CLIENT") || (DEVICE == "BOTH") >
  <#assign clusterName = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_NAME")?eval?capitalize?replace(' ','') >
  <#assign deviceTypeFunctionPrefix = DEVICE_TYPE_FILE_PREFIX >
  ${clusterName?upper_case}_CLUSTER_ID,
  </#if>
  </#list>
#ifdef OTAU_CLIENT
  OTAU_CLUSTER_ID,
#endif    
};

/******************************************************************************
                    Implementation section
******************************************************************************/
#endif // APP_DEVICE_TYPE_IAS_ACE
//// eof iasACECluster.c
