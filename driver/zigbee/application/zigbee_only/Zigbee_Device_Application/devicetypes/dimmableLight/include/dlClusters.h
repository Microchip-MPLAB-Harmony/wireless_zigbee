/*******************************************************************************
  Dimmable Light clusters Header File

  Company:
    Microchip Technology Inc.

  File Name:
    dlClusters.h

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

#define _DLCLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl.h>

/******************************************************************************
                    Definitions section
******************************************************************************/
#define DL_SERVER_CLUSTERS_COUNT     6

#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
  #ifdef OTAU_CLIENT
    #define DL_CLIENT_CLUSTERS_COUNT   4
  #else
    #define DL_CLIENT_CLUSTERS_COUNT   3
  #endif
#else // no extra clusters
  #ifdef OTAU_CLIENT
    #define DL_CLIENT_CLUSTERS_COUNT   3
  #else
    #define DL_CLIENT_CLUSTERS_COUNT   2
  #endif
#endif // ZLO_EXTRA_CLUSTERS_SUPPORT == 1

#define DL_SERVER_CLUSTER_INIT_COUNT DL_SERVER_CLUSTERS_COUNT

#ifdef OTAU_CLIENT
  #define DL_CLIENT_CLUSTER_INIT_COUNT    1
#else
  #define DL_CLIENT_CLUSTER_INIT_COUNT    0
#endif

/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_Cluster_t dlServerClusters[DL_SERVER_CLUSTERS_COUNT];
extern ClusterId_t dlServerClusterIds[DL_SERVER_CLUSTERS_COUNT];
extern void (*dlServerClusterInitFunctions[DL_SERVER_CLUSTER_INIT_COUNT])();

extern ZCL_Cluster_t dlClientClusters[DL_CLIENT_CLUSTERS_COUNT];
extern ClusterId_t dlClientClusterIds[DL_CLIENT_CLUSTERS_COUNT];
#ifdef OTAU_CLIENT
extern void (*dlClientClusterInitFunctions[DL_CLIENT_CLUSTER_INIT_COUNT])();
#endif

#endif // _DLCLUSTER_H

// eof dlClusters.h
