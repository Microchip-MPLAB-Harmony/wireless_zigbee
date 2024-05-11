/*******************************************************************************
  Color Scene Remote Basic cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cscBasicCluster.c

  Summary:
    This file contains the Color Scene Remote device Basic cluster interface.

  Description:
    This file contains the Color Scene Remote device Basic cluster interface.
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
#include <z3device/clusters/include/haClusters.h>
#include <z3device/common/include/appConsts.h>
#include <z3device/colorSceneController/include/cscBasicCluster.h>
#include <z3device/clusters/include/basicCluster.h>
#include <z3device/colorSceneController/include/cscClusters.h>
#include <zcl/include/zclCommandManager.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing,
                                       uint8_t payloadLength, uint8_t *payload);
/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_BasicClusterServerAttributes_t cscBasicClusterServerAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER_ATTRIBUTES()
};

#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1

ZCL_BasicClusterClientAttributes_t cscBasicClusterClientAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_CLIENT_ATTRIBUTES()
};

#endif

ZCL_BasicClusterServerCommands_t cscBasicClusterServerCommands =
{
  ZCL_DEFINE_BASIC_CLUSTER_COMMANDS(resetToFactoryDefaultsInd)
};

/******************************************************************************
                    Implementations section
******************************************************************************/

/**************************************************************************//**
\brief Initialize Basic cluster.
******************************************************************************/
void cscBasicClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_COLOR_SCENE_CONTROLLER, BASIC_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
  cscBasicClusterServerAttributes.hwVersion.value = HW_VERSION;
  memcpy(cscBasicClusterServerAttributes.manufacturerName.value,
                                                  "\x1f Microchip ", 12);
  memcpy(cscBasicClusterServerAttributes.modelIdentifier.value,
                                 "\x1f Color scene controller ", 25);
  memcpy(cscBasicClusterServerAttributes.dateCode.value, "\xf 20150901", 10);
  cscBasicClusterServerAttributes.powerSource.value = POWER_SOURCE; // Battery
  cscBasicClusterServerAttributes.zclVersion.value = ZCL_VERSION;
  cscBasicClusterServerAttributes.applicationVersion.value = APP_VERSION;

  cscBasicClusterServerAttributes.stackVersion.value = STACK_VERSION;
  cscBasicClusterServerAttributes.clusterVersion.value = BASIC_CLUSTER_VERSION;
  cscBasicClusterServerAttributes.physicalEnvironment.value
                                                       = UNKNOWN_ENVIRONMENT;

  cscBasicClusterServerAttributes.genericDeviceClass.value
                                                      = LIGHTING_DEVICE_CLASS;
  cscBasicClusterServerAttributes.genericDeviceType.value   =
                               GENERIC_CONTROLLER_REMOTE_CONTROLLER_DEVICE_TYPE;
  memcpy(cscBasicClusterServerAttributes.productCode.value, "\x1f\x4XYZ123", 8);
  memcpy(cscBasicClusterServerAttributes.productURL.value,
                                                   "\x1f  www.microchip.com ", 17);
  memcpy(cscBasicClusterServerAttributes.swBuildId.value, "\xf Phoenix", 9);
  
#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
  cscBasicClusterClientAttributes.clusterVersion.value      = BASIC_CLUSTER_VERSION;
#endif
  if (cluster)
    cluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
}

/**************************************************************************//**
\brief Callback on receive of resetToFactoryDefaults command
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing,
                                       uint8_t payloadLength, uint8_t *payload)
{
  for (uint8_t i=0; i < CSC_SERVER_CLUSTER_INIT_COUNT; i++)
  {
    if (cscServerClusterInitFunctions[i])
      (cscServerClusterInitFunctions[i])();
  }

  // needs to enable after app directory is created
  //PDS_Store(Z3DEVICE_APP_MEMORY_MEM_ID);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}
#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
/**************************************************************************//**
\brief Sends resetToFactoryDefaults command unicastly

\param[in] mode  - address mode;
\param[in] addr  - short address of destination node;
\param[in] ep    - destination endpoint;
\param[in] srcEp - source endpoint;
******************************************************************************/
void basicResetToFactoryDefaultsCommand(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_BASIC_CLUSTER_SERVER_RESET_TO_FACTORY_DEFAULTS_COMMAND_ID, 0, srcEp);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, BASIC_CLUSTER_ID);

  ZCL_CommandManagerSendCommand(req);
}

#endif //#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
#endif // APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_COLOR_SCENE_CONTROLLER

// eof cscBasicCluster.c
