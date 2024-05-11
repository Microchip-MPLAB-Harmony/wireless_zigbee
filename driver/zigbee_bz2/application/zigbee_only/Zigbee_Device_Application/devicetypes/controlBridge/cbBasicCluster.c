/*******************************************************************************
  Control Bridge Basic cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    cbBasicCluster.c

  Summary:
    This file contains the Control Bridge Basic cluster interface.

  Description:
    This file contains the Control Bridge Basic cluster interface.
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
#include <cbBasicCluster.h>
#include <basicCluster.h>
#include <zclCommandManager.h>
#include <cbClusters.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_BasicClusterServerAttributes_t cbBasicClusterServerAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER_ATTRIBUTES()
};

ZCL_BasicClusterClientAttributes_t cbBasicClusterClientAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_CLIENT_ATTRIBUTES()
};

PROGMEM_DECLARE(ZCL_BasicClusterServerCommands_t cbBasicClusterServerCommands) =
{
  ZCL_DEFINE_BASIC_CLUSTER_COMMANDS(resetToFactoryDefaultsInd)
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Basic cluster
******************************************************************************/
void cbBasicClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_CONTROL_BRIDGE, BASIC_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
  cbBasicClusterServerAttributes.clusterVersion.value      = CLUSTER_VERSION;
  cbBasicClusterServerAttributes.zclVersion.value          = ZCL_VERSION;
  cbBasicClusterServerAttributes.powerSource.value         = POWER_SOURCE;
  cbBasicClusterServerAttributes.physicalEnvironment.value = UNKNOWN_ENVIRONMENT;
  cbBasicClusterServerAttributes.applicationVersion.value  = APP_VERSION;
  cbBasicClusterServerAttributes.stackVersion.value        = STACK_VERSION;
  cbBasicClusterServerAttributes.hwVersion.value           = HW_VERSION;

  memcpy(cbBasicClusterServerAttributes.manufacturerName.value, "\x1f Microchip ", 8);
  memcpy(cbBasicClusterServerAttributes.modelIdentifier.value, "\x1f ControlBridge", 15);
  memcpy(cbBasicClusterServerAttributes.dateCode.value, "\xf 20150901", 10);

  cbBasicClusterServerAttributes.genericDeviceClass.value  = LIGHTING_DEVICE_CLASS; //need to be changed
  cbBasicClusterServerAttributes.genericDeviceType.value   = GATEWAY_BRIDGE_DEVICE_TYPE;
  memcpy(cbBasicClusterServerAttributes.productCode.value, "\x1f\x4XYZ123", 8);
  memcpy(cbBasicClusterServerAttributes.productURL.value, "\x1f  ww.microchip.com ", 17);

  memcpy(cbBasicClusterServerAttributes.swBuildId.value, "\xf abcdefgh", 10);
  /* Client side attributes */
  cbBasicClusterClientAttributes.clusterVersion.value      = CLUSTER_VERSION;
  cluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
}

/**************************************************************************//**
\brief Callback on receive of resetToFactoryDefaults command
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  for (uint8_t i=0; i<CB_SERVER_CLUSTER_INIT_COUNT; i++)
  {
    if (cbServerClusterInitFunctions[i])
      (cbServerClusterInitFunctions[i])();
  }

  // needs to enable after app directory is created
  //PDS_Store(HA_APP_MEMORY_MEM_ID);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

/**************************************************************************//**
\brief Sends resetToFactoryDefaults command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
******************************************************************************/
void cbBasicResetToFactoryDefaultsCommand(APS_AddrMode_t mode,ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_BASIC_CLUSTER_SERVER_RESET_TO_FACTORY_DEFAULTS_COMMAND_ID, 0, srcEp);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, BASIC_CLUSTER_ID);

  commandManagerSendCommand(req);
}

#endif // APP_DEVICE_TYPE_CONTROL_BRIDGE

// eof cbBasicCluster.c
