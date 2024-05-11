/*******************************************************************************
   Dimmer Switch clusters Source File

  Company:
    Microchip Technology Inc.

  File Name:
    dsClusters.c

  Summary:
    This file contains the Dimmer Switch clusters interface.

  Description:
    This file contains the Dimmer Switch clusters interface.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_DIMMER_SWITCH)

/******************************************************************************
                    Includes section
******************************************************************************/
#include <dsClusters.h>

#include <basicCluster.h>
#include <identifyCluster.h>
#include <dsBasicCluster.h>
#include <dsIdentifyCluster.h>
#include <dsBasicCluster.h>
#include <dsIdentifyCluster.h>
#include <dsOnOffCluster.h>
#include <dsLevelControlCluster.h>
#include <dsGroupsCluster.h>
#include <dsScenesCluster.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_Cluster_t dsServerClusters[DS_SERVER_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER(&dsBasicClusterServerAttributes, &dsBasicClusterServerCommands),
  DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &dsIdentifyClusterServerAttributes, &dsIdentifyCommands),
};

void (*dsServerClusterInitFunctions[DS_SERVER_CLUSTER_INIT_COUNT])() =
{
  dsBasicClusterInit,
  dsIdentifyClusterInit,
};	

ZCL_Cluster_t dsClientClusters[DS_CLIENT_CLUSTERS_COUNT] =
{
  
#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
  ZCL_DEFINE_BASIC_CLUSTER_CLIENT(&dsBasicClusterClientAttributes),
#endif
  
  DEFINE_IDENTIFY_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &dsIdentifyClusterClientAttributes, &dsIdentifyCommands),
  DEFINE_ONOFF_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &dsOnOffClusterClientAttributes, NULL),
  DEFINE_LEVEL_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &dsLevelControlClusterClientAttributes, NULL),
  
  /* Groups and Scenes cluster */
  DEFINE_GROUPS_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &dsGroupsClusterClientAttributes, &dsGroupsCommands),
  DEFINE_SCENES_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &dsScenesClusterClientAttributes, &dsScenesCommands),
};

void (*dsClientClusterInitFunctions[DS_CLIENT_CLUSTER_INIT_COUNT])() =
{
#if (ZLO_EXTRA_CLUSTERS_SUPPORT == 1)
  dsBasicClusterInit,
#endif
  dsIdentifyClusterInit,
  dsGroupsClusterInit,
  dsScenesClusterInit,
  dsOnOffClusterInit,
  dsLevelControlClusterInit,
#ifdef  OTAU_CLIENT 
  NULL    //Need to be added for OTAU
#endif
};

ClusterId_t   dsServerClusterIds[DS_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
};

ClusterId_t   dsClientClusterIds[DS_CLIENT_CLUSTERS_COUNT] =
{
  /* Mandatory clusters */
  IDENTIFY_CLUSTER_ID,
  ONOFF_CLUSTER_ID,
  LEVEL_CONTROL_CLUSTER_ID,
  
  /* Optional clusters */
  GROUPS_CLUSTER_ID,
  SCENES_CLUSTER_ID,
  
#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
  BASIC_CLUSTER_ID,
#endif
  
#ifdef OTAU_CLIENT
  OTAU_CLUSTER_ID // Always should be on last position in list of clusters ID.
#endif

};

#endif // APP_DEVICE_TYPE_DIMMER_SWITCH

// eof dsClusters.c
