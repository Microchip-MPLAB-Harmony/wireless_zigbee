/*******************************************************************************
  Control Bridge clusters Source File

  Company:
    Microchip Technology Inc.

  File Name:
   cbClusters.c

  Summary:
    This file contains the Control Bridge clusters interface.

  Description:
    This file contains the Control Bridge clusters interface.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_CONTROL_BRIDGE)
/******************************************************************************
                    Includes section
******************************************************************************/
#include <haClusters.h>
#include <cbClusters.h>
#include <basicCluster.h>
#include <identifyCluster.h>
#include <cbBasicCluster.h>
#include <cbIdentifyCluster.h>
#include <cbOnOffCluster.h>
#include <cbCommissioningCluster.h>
#include <cbLevelControlCluster.h>
#include <cbGroupsCluster.h>
#include <cbScenesCluster.h>
#include <cbOccupancySensingCluster.h>
#include <cbIlluminanceMeasurementCluster.h>
#include <cbColorControlCluster.h>

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_Cluster_t cbServerClusters[CB_SERVER_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER(&cbBasicClusterServerAttributes, &cbBasicClusterServerCommands),
  DEFINE_IDENTIFY_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &cbIdentifyClusterServerAttributes, &cbIdentifyCommands),
   // Optional
  DEFINE_COMMISSIONING_CLUSTER(ZCL_SERVER_CLUSTER_TYPE, &cbCommissioningClusterServerAttributes, &cbCommissioningClusterCommands)
};

void (*cbServerClusterInitFunctions[CB_SERVER_CLUSTER_INIT_COUNT])() =
{
  cbBasicClusterInit,
  cbIdentifyClusterInit,
  // Optional
  cbCommissioningServerClusterInit
};

ZCL_Cluster_t cbClientClusters[CB_CLIENT_CLUSTERS_COUNT] =
{
  ZCL_DEFINE_BASIC_CLUSTER_CLIENT(&cbBasicClusterClientAttributes),
  DEFINE_IDENTIFY_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &cbIdentifyClusterClientAttributes, &cbIdentifyCommands),
  DEFINE_ONOFF_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &cbOnOffClusterClientAttributes, NULL),
  DEFINE_LEVEL_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &cbLevelControlClusterClientAttributes, NULL),
  DEFINE_COLOR_CONTROL_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &cbColorControlClusterClientAttributes, &cbColorControlCommands),
  DEFINE_GROUPS_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &cbGroupsClusterClientAttributes, &cbGroupsCommands),
  DEFINE_SCENES_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &cbScenesClusterClientAttributes, &cbScenesCommands),
  DEFINE_OCCUPANCY_SENSING_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL, NULL),
  DEFINE_ILLUMINANCE_MEASUREMENT_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, NULL),
  DEFINE_COMMISSIONING_CLUSTER(ZCL_CLIENT_CLUSTER_TYPE, &cbCommissioningClusterClientAttributes, &cbCommissioningClusterCommands)
};

ClusterId_t   cbServerClusterIds[CB_SERVER_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
   // Optional
  ZLL_COMMISSIONING_CLUSTER_ID,
  
#ifdef OTAU_SERVER
  OTAU_CLUSTER_ID, // Always should be on last position in list of clusters ID.
#endif // OTAU_SERVER
};

ClusterId_t   cbClientClusterIds[CB_CLIENT_CLUSTERS_COUNT] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  ONOFF_CLUSTER_ID,
  LEVEL_CONTROL_CLUSTER_ID,
  COLOR_CONTROL_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  SCENES_CLUSTER_ID,
  OCCUPANCY_SENSING_CLUSTER_ID,
  ILLUMINANCE_MEASUREMENT_CLUSTER_ID,
  ZLL_COMMISSIONING_CLUSTER_ID
};

#endif // APP_DEVICE_TYPE_CONTROL_BRIDGE

// eof cbClusters.c
