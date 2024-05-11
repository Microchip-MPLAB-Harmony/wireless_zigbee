/*******************************************************************************
  Color Scene Controller clusters Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cscClusters.c

  Summary:
    This file contains the Color Scene Controller device clusters interface.

  Description:
    This file contains the Color Scene Controller device clusters interface.
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


#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_CONTROLLER)

/******************************************************************************
                    Includes section
******************************************************************************/

#include <z3device/colorSceneController/include/cscClusters.h>
#include <z3device/clusters/include/basicCluster.h>
#include <zcl/clusters/include/identifyCluster.h>
#include <z3device/colorSceneController/include/cscBasicCluster.h>
#include <z3device/colorSceneController/include/cscIdentifyCluster.h>
#include <z3device/colorSceneController/include/cscOnOffCluster.h>
#include <z3device/colorSceneController/include/cscLevelControlCluster.h>
#include <z3device/colorSceneController/include/cscGroupsCluster.h>
#include <z3device/colorSceneController/include/cscScenesCluster.h>
#include <z3device/colorSceneController/include/cscColorControlCluster.h>
#include <z3device/colorSceneController/include/cscCommissioningCluster.h>
#include <zcl/include/clusters.h>
//#include <z3device/colorSceneController/include/cscOtaCluster.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_Cluster_t cscServerClusters[CSC_SERVER_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER(&cscBasicClusterServerAttributes,&cscBasicClusterServerCommands),
  DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &cscIdentifyClusterServerAttributes, &cscIdentifyClusterCommands),
  DEFINE_COMMISSIONING_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &cscCommissioningClusterServerAttributes, &cscCommissioningClusterCommands)
};

void (*cscServerClusterInitFunctions[CSC_SERVER_CLUSTER_INIT_COUNT])() =
{
  cscBasicClusterInit,
  cscIdentifyClusterInit,
  // Optional
  cscCommissioningServerClusterInit,
};

ZCL_Cluster_t cscClientClusters[CSC_CLIENT_CLUSTERS_COUNT] =
{
#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
  ZCL_DEFINE_BASIC_CLUSTER_CLIENT(&cscBasicClusterClientAttributes),
#endif  
  DEFINE_IDENTIFY_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, 
                          &cscIdentifyClusterClientAttributes, 
                          &cscIdentifyClusterCommands),
  DEFINE_SCENES_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE,
                          &cscScenesClusterClientAttributes,
                          &cscScenesClusterCommands),
  DEFINE_ONOFF_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE,
                          &cscOnOffClusterClientAttributes,
                          &cscOnOffClusterCommands),
  DEFINE_LEVEL_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE,
                              &cscLevelControlClusterClientAttributes,
                              &cscLevelControlClusterCommands),
  DEFINE_COLOR_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE,
                               &cscColorControlClusterClientAttributes,
                               &cscColorControlClusterCommands),
  DEFINE_GROUPS_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE,
                        &cscGroupsClusterClientAttributes,
                        &cscGroupsClusterCommands),
  DEFINE_COMMISSIONING_CLUSTER(ZCL_SERVER_CLUSTER_TYPE,
                               &cscCommissioningClusterClientAttributes,
                               &cscCommissioningClusterCommands),
 // OTAU
};

ClusterId_t cscServerClusterIds[CSC_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  ZLL_COMMISSIONING_CLUSTER_ID,
};

ClusterId_t cscClientClusterIds[CSC_CLIENT_CLUSTERS_COUNT] =
{
#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
  BASIC_CLUSTER_ID,
#endif
  IDENTIFY_CLUSTER_ID,
  SCENES_CLUSTER_ID,
  ONOFF_CLUSTER_ID,
  LEVEL_CONTROL_CLUSTER_ID,
  COLOR_CONTROL_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  ZLL_COMMISSIONING_CLUSTER_ID,
#ifdef OTAU_CLIENT
  OTAU_CLUSTER_ID, // Always should be on last position in list of clusters ID.
#endif // OTAU_CLIENT
};

/******************************************************************************
                    Implementations section
******************************************************************************/

#endif // #if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_CONTROLLER)

// eof cscClusters.c
