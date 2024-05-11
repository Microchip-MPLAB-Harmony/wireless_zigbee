/*******************************************************************************
  Combined Interface clusters Header File

  Company:
    Microchip Technology Inc.

  File Name:
    ciClusters.h

  Summary:
    This file contains the Combined Interface clusters interface.

  Description:
    This file contains the Combined Interface clusters interface.
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

#ifndef CICLUSTER_H
#define CICLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl/include/zcl.h>
#include <z3device/common/include/appConsts.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
<#assign customClusterServerCount = 0>
<#assign customClusterClientCount = 0>

<#list 0..< CUSTOM_CLUSTER_NO as customClusterIndex>
  <#assign DEVICE = ("ZCC"+ customClusterIndex +"_CUSTOM_CLUSTER_CS")?eval >

  <#if (DEVICE == "SERVER")  >
  <#assign customClusterServerCount = customClusterServerCount + 1>

  <#elseif (DEVICE == "CLIENT") >
  <#assign customClusterClientCount = customClusterClientCount + 1>

  <#elseif (DEVICE == "BOTH") >
  <#assign customClusterClientCount = customClusterClientCount + 1>
  <#assign customClusterServerCount = customClusterServerCount + 1>

  </#if>

</#list>

<#function customClusterCount DEVICE>
<#assign count = ("customCluster"+ DEVICE?capitalize +"Count")?eval>

<#if (count != 0) >
<#return "+ "+ count>

<#else>
<#return "">
</#if>

</#function>

<#assign SERVER_CLUSTERS_COUNT = 
4 + 
IASACE_CLUSTER_ENABLE?then(1,0) + 
TIME_CLUSTER_ENABLE?then(1,0)
>
<#assign CLIENT_CLUSTERS_COUNT = 
4 + 
ONOFF_CLUSTER_ENABLE?then(1,0) +
LEVELCONTROL_CLUSTER_ENABLE?then(1,0) +
SCENES_CLUSTER_ENABLE?then(1,0) +
OCCUPANCYSENSING_CLUSTER_ENABLE?then(1,0) +
ILLUMINANCEMEASUREMENT_CLUSTER_ENABLE?then(1,0) +
TEMPERATUREMEASUREMENT_CLUSTER_ENABLE?then(1,0) +
WATERCONTENTMEASUREMENT_CLUSTER_ENABLE?then(1,0) +
COLORCONTROL_CLUSTER_ENABLE?then(1,0) +
THERMOSTAT_CLUSTER_ENABLE?then(1,0) +
THERMOSTATUI_CLUSTER_ENABLE?then(1,0) +
ALARMS_CLUSTER_ENABLE?then(1,0) +
FANCONTROL_CLUSTER_ENABLE?then(1,0) +
IASZONE_CLUSTER_ENABLE?then(1,0) 
>
#ifdef OTAU_SERVER
  #define CI_SERVER_CLUSTERS_COUNT     ${SERVER_CLUSTERS_COUNT + 1}u ${customClusterCount("SERVER")}
  #define CI_SERVER_CLUSTER_INIT_COUNT (CI_SERVER_CLUSTERS_COUNT - 1)
#else
  #define CI_SERVER_CLUSTERS_COUNT     ${SERVER_CLUSTERS_COUNT}u ${customClusterCount("SERVER")}
  #define CI_SERVER_CLUSTER_INIT_COUNT CI_SERVER_CLUSTERS_COUNT
#endif

#define CI_CLIENT_CLUSTER_INIT_COUNT   ${CLIENT_CLUSTERS_COUNT}u ${customClusterCount("CLIENT")}
#define CI_CLIENT_CLUSTERS_COUNT       ${CLIENT_CLUSTERS_COUNT}u ${customClusterCount("CLIENT")}

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_Cluster_t ciServerClusters[CI_SERVER_CLUSTERS_COUNT];
extern ZCL_Cluster_t ciClientClusters[CI_CLIENT_CLUSTERS_COUNT];
extern void (*ciServerClusterInitFunctions[CI_SERVER_CLUSTER_INIT_COUNT])();
extern void (*ciClientClusterInitFunctions[CI_CLIENT_CLUSTER_INIT_COUNT])();
extern ClusterId_t   ciServerClusterIds[CI_SERVER_CLUSTERS_COUNT];
extern ClusterId_t   ciClientClusterIds[CI_CLIENT_CLUSTERS_COUNT];

#endif // CICLUSTER_H

// eof ciClusters.h
