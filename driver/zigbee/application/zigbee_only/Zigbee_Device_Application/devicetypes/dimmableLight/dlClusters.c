/*******************************************************************************
  Dimmable Light clusters Source File

  Company:
    Microchip Technology Inc.

  File Name:
    dlClusters.c

  Summary:
    This file contains the Dimmable Light clusters interface.

  Description:
    This file contains the Dimmable Light clusters interface.
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

#ifdef APP_DEVICE_TYPE_DIMMABLE_LIGHT
/******************************************************************************
                    Includes section
******************************************************************************/
#include <basicCluster.h>
#include <identifyCluster.h>
#include <dlClusters.h>
#include <dlBasicCluster.h>
#include <dlIdentifyCluster.h>
#include <dlOnOffCluster.h>
#include <dlLevelControlCluster.h>
#include <dlGroupsCluster.h>
#include <dlScenesCluster.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_Cluster_t dlServerClusters[DL_SERVER_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER(&dlBasicClusterServerAttributes, &dlBasicClusterServerCommands),
  DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &dlIdentifyClusterServerAttributes, &dlIdentifyCommands),
  DEFINE_ONOFF_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &dlOnOffClusterServerAttributes, &dlOnOffCommands),
  DEFINE_LEVEL_CONTROL_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &dlLevelControlClusterServerAttributes, &dlLevelControlCommands),
  DEFINE_GROUPS_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &dlGroupsClusterServerAttributes, &dlGroupsCommands),
  DEFINE_SCENES_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &dlScenesClusterServerAttributes, &dlScenesCommands)
};

void (*dlServerClusterInitFunctions[DL_SERVER_CLUSTER_INIT_COUNT])() =
{
  basicClusterInit,
  identifyClusterInit,
  onOffClusterInit,
  levelControlClusterInit,
  groupsClusterInit,
  scenesClusterInit
};

#ifdef OTAU_CLIENT
void (*dlClientClusterInitFunctions[DL_CLIENT_CLUSTER_INIT_COUNT])() =
{
  NULL // oatu client init fucntion
};
#endif

ClusterId_t dlServerClusterIds[DL_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  ONOFF_CLUSTER_ID,
  LEVEL_CONTROL_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  SCENES_CLUSTER_ID
};

ZCL_Cluster_t dlClientClusters[DL_CLIENT_CLUSTERS_COUNT] =
{
  DEFINE_IDENTIFY_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &dlIdentifyClusterClientAttributes, &dlIdentifyCommands),
  DEFINE_GROUPS_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &dlGroupsClusterClientAttributes, &dlGroupsCommands)
};

ClusterId_t dlClientClusterIds[DL_CLIENT_CLUSTERS_COUNT] =
{
  IDENTIFY_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
#ifdef OTAU_CLIENT
  OTAU_CLUSTER_ID, // Always should be on last position in list of clusters ID.
#endif
};


#endif // APP_DEVICE_TYPE_DIMMABLE_LIGHT

// eof dlClusters.c
