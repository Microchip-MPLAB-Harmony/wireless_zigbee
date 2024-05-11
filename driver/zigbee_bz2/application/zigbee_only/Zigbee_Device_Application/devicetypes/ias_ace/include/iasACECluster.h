/*******************************************************************************
  IAS-ACE Cluster Header File

  Company:
    Microchip Technology Inc.

  File Name:
    iasACECluster.h

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

#ifndef _IASACECLUSTER_H
#define _IASACECLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl/include/zcl.h>
#include <zcl/include/zclIasACECluster.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
/* Zone Table Size for ACE device*/
#define APP_ZONE_TABLE_ENTRY_SIZE                           0x03
#define PAYLOAD_SIZE                                        0x32

/* Some default values for attributes */
#define APP_IAS_ZONE_ZONE_TYPE_ATTRIBUTE_VALUE              0x0000
#define APP_IAS_ZONE_IAS_CIE_ADDRESS_ATTRIBUTE_VALUE        0x0000
#define SUPERVISION_REPORT_STATE                            0x0010

#define IAS_ACE_SERVER_CLUSTERS_COUNT           4
#ifdef OTAU_CLIENT
  #define IAS_ACE_CLIENT_CLUSTERS_COUNT         5
#else
  #define IAS_ACE_CLIENT_CLUSTERS_COUNT         4
#endif

#define IAS_ACE_SERVER_CLUSTER_INIT_COUNT IAS_ACE_SERVER_CLUSTERS_COUNT

#define IAS_ACE_CLIENT_CLUSTER_INIT_COUNT IAS_ACE_CLIENT_CLUSTERS_COUNT
/******************************************************************************
                    Externals
******************************************************************************/
extern ZCL_Cluster_t iasACEServerClusters[IAS_ACE_SERVER_CLUSTERS_COUNT];
extern ClusterId_t iasACEServerClusterIds[IAS_ACE_SERVER_CLUSTERS_COUNT];
extern void (*iasACEServerClusterInitFunctions[IAS_ACE_SERVER_CLUSTER_INIT_COUNT])();

extern ZCL_Cluster_t iasACEClientClusters[IAS_ACE_CLIENT_CLUSTERS_COUNT];
extern ClusterId_t iasACEClientClusterIds[IAS_ACE_CLIENT_CLUSTERS_COUNT];

extern PROGMEM_DECLARE (ZCL_IasACEClusterCommands_t iasACEClusterCommands);

#ifdef OTAU_CLIENT
extern void (*iasACEClientClusterInitFunctions[IAS_ACE_CLIENT_CLUSTER_INIT_COUNT])();
#endif
#endif // _IASACECLUSTER_H

// eof iasACECluster.h
