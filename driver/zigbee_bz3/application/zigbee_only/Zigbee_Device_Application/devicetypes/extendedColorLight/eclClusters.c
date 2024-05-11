/*******************************************************************************
  Extended Color Light clusters Source File

  Company:
    Microchip Technology Inc.

  File Name:
    eclClusters.c

  Summary:
    This file contains the Extended Color Light clusters interface.

  Description:
    This file contains the Extended Color Light clusters interface.
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

#ifdef APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT
/******************************************************************************
                    Includes section
******************************************************************************/
#include <basicCluster.h>
#include <identifyCluster.h>

#include <eclClusters.h>

#include <eclBasicCluster.h>
#include <eclIdentifyCluster.h>

#include <eclOnOffCluster.h>
#include <eclLevelControlCluster.h>

#include <eclColorControlCluster.h>
#include <eclCommissioningCluster.h>

#include <eclGroupsCluster.h>
#include <eclScenesCluster.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_Cluster_t eclServerClusters[ECL_SERVER_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER(&eclBasicClusterServerAttributes, &eclBasicClusterServerCommands),
  DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &eclIdentifyClusterServerAttributes, &eclIdentifyCommands),

  DEFINE_ONOFF_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &eclOnOffClusterServerAttributes, &eclOnOffCommands),
  DEFINE_LEVEL_CONTROL_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &eclLevelControlClusterServerAttributes, &eclLevelControlCommands),

  DEFINE_COLOR_CONTROL_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &eclColorControlClusterServerAttributes, &eclColorControlClusterServerCommands),
  DEFINE_COMMISSIONING_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &eclCommissioningClusterServerAttributes, &eclCommissioningClusterCommands),

  DEFINE_GROUPS_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &eclGroupsClusterServerAttributes, &eclGroupsCommands),
  DEFINE_SCENES_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &eclScenesClusterServerAttributes, &eclScenesCommands),
};

void (*eclServerClusterInitFunctions[ECL_SERVER_CLUSTER_INIT_COUNT])() =
{
  basicClusterInit,
  identifyClusterInit,
  onOffClusterInit,
  levelControlClusterInit,
  colorControlClusterInit,
  commissioningClusterInit,
  groupsClusterInit,
  scenesClusterInit
};

#ifdef OTAU_CLIENT
void (*eclClientClusterInitFunctions[ECL_CLIENT_CLUSTER_INIT_COUNT])() =
{
  NULL // oatu client init fucntion
};
#endif

ClusterId_t eclServerClusterIds[ECL_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  ONOFF_CLUSTER_ID,
  LEVEL_CONTROL_CLUSTER_ID,
  COLOR_CONTROL_CLUSTER_ID,
  ZLL_COMMISSIONING_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  SCENES_CLUSTER_ID
};

ZCL_Cluster_t eclClientClusters[ECL_CLIENT_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_CLIENT(&eclBasicClusterClientAttributes),
  DEFINE_IDENTIFY_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &eclIdentifyClusterClientAttributes, &eclIdentifyCommands),
  DEFINE_GROUPS_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &eclGroupsClusterClientAttributes, &eclGroupsCommands)
};

ClusterId_t eclClientClusterIds[ECL_CLIENT_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
#ifdef OTAU_CLIENT
  OTAU_CLUSTER_ID, // Always should be on last position in list of clusters ID.
#endif
};


#endif // APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT

// eof eclClusters.c
