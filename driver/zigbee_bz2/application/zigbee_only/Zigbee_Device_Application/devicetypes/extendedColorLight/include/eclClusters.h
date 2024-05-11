/*******************************************************************************
  Extended Color Light clusters Header File

  Company:
    Microchip Technology Inc.

  File Name:
    eclClusters.h

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

#ifndef DLCLUSTER_H
#define DLCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#define ECL_SERVER_CLUSTERS_COUNT            8

#ifdef OTAU_CLIENT
  #define ECL_CLIENT_CLUSTERS_COUNT          4
#else
  #define ECL_CLIENT_CLUSTERS_COUNT          3
#endif

#define ECL_SERVER_CLUSTER_INIT_COUNT        ECL_SERVER_CLUSTERS_COUNT
#define ECL_CLIENT_CLUSTER_INIT_COUNT        ECL_CLIENT_CLUSTERS_COUNT

/******************************************************************************
                    Externals
******************************************************************************/
// Clusters
extern ZCL_Cluster_t eclServerClusters[ECL_SERVER_CLUSTERS_COUNT];
extern ZCL_Cluster_t eclClientClusters[ECL_CLIENT_CLUSTERS_COUNT];

// Cluster indentifers
extern ClusterId_t eclServerClusterIds[ECL_SERVER_CLUSTERS_COUNT];
extern ClusterId_t eclClientClusterIds[ECL_CLIENT_CLUSTERS_COUNT];

// Cluster initialization functions
extern void (*eclServerClusterInitFunctions[ECL_SERVER_CLUSTER_INIT_COUNT])();
#ifdef OTAU_CLIENT
extern void (*eclClientClusterInitFunctions[ECL_CLIENT_CLUSTER_INIT_COUNT])();
#endif

#endif // DLCLUSTER_H

// eof eclClusters.h
