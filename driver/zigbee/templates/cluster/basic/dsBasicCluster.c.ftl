/*******************************************************************************
  Dimmer Switch Basic cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    dsBasicCluster.c

  Summary:
    This file contains the Dimmer Switch Basic cluster interface.

  Description:
    This file contains the Dimmer Switch Basic cluster interface.
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
#include <z3device/clusters/include/haClusters.h>
#include <dsBasicCluster.h>
#include <z3device/clusters/include/basicCluster.h>
#include <dsClusters.h>
#include <commandManager.h>
#include <uartManager.h>
#include <dsClusters.h>
#include <pds/include/wlPdsMemIds.h>
#include <app_zigbee/app_zigbee_handler.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
<#if (BASIC_CLUSTER_CS != "CLIENT")  &&  (BS_RESETTOFNCMD == true) >
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
</#if>
/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_BasicClusterServerAttributes_t dsBasicClusterServerAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER_ATTRIBUTES()
};

#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1

ZCL_BasicClusterClientAttributes_t dsBasicClusterClientAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_CLIENT_ATTRIBUTES()
};

#endif

PROGMEM_DECLARE(ZCL_BasicClusterServerCommands_t dsBasicClusterServerCommands) =
{
<#if (BASIC_CLUSTER_CS != "CLIENT")  &&  (BS_RESETTOFNCMD == true) >
  ZCL_DEFINE_BASIC_CLUSTER_COMMANDS(resetToFactoryDefaultsInd)
</#if>
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Basic cluster
******************************************************************************/
void dsBasicClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_DIMMER_SWITCH, BASIC_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);

<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_CLUSTERREVISION == true) >
  dsBasicClusterServerAttributes.clusterVersion.value      = CLUSTER_VERSION;
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_ZCLVERSION == true) >
  dsBasicClusterServerAttributes.zclVersion.value          = ZCL_VERSION;
/#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_POWERSOURCE == true) >
  dsBasicClusterServerAttributes.powerSource.value         = POWER_SOURCE;
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_PHYENV == true) >
  dsBasicClusterServerAttributes.physicalEnvironment.value = UNKNOWN_ENVIRONMENT;
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_APPLCIATIONVERSION == true) >
  dsBasicClusterServerAttributes.applicationVersion.value  = APP_VERSION;
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_STACKVERSION == true) >
  dsBasicClusterServerAttributes.stackVersion.value        = STACK_VERSION;
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_HWVERSION == true) >
  dsBasicClusterServerAttributes.hwVersion.value           = HW_VERSION;

</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_MANUNAME == true) >
  memcpy(dsBasicClusterServerAttributes.manufacturerName.value, "\x1f Microchip ", 12);

</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_MODELID == true) >
  memcpy(dsBasicClusterServerAttributes.modelIdentifier.value, "\x1f DimmerSwitch", 14);

</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_DATECODE == true) >
  memcpy(dsBasicClusterServerAttributes.dateCode.value, "\xf 20150901", 10);

</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_GENDEVCLASS == true) >
  dsBasicClusterServerAttributes.genericDeviceClass.value  = LIGHTING_DEVICE_CLASS;
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_GENDEVCTYPE == true) >
  dsBasicClusterServerAttributes.genericDeviceType.value   = WALL_SWITCH_DEVICE_TYPE;
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_PRODUCTCODE == true) >
  memcpy(dsBasicClusterServerAttributes.productCode.value, "\x1f\x4XYZ123", 8);
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_PRODUCTURL == true) >
  memcpy(dsBasicClusterServerAttributes.productURL.value, "\x1f  www.microchip.com ", 17);
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_SWBUILDID == true) >
  memcpy(dsBasicClusterServerAttributes.swBuildId.value, "\xf abcdefgh", 10);
  
</#if>
<#if (BASIC_CLUSTER_CS != "SERVER")  && (BS_CLUSTERREVISION == true) >
#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
  dsBasicClusterClientAttributes.clusterVersion.value      = CLUSTER_VERSION;
#endif
</#if>
  cluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
}

<#if (BASIC_CLUSTER_CS != "CLIENT")  &&  (BS_RESETTOFNCMD == true) >
/**************************************************************************//**
\brief Callback on receive of resetToFactoryDefaults command
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  APP_Zigbee_Event_t event;
  event.eventGroup = EVENT_CLUSTER;
  event.eventId = CMD_ZCL_RESET_TO_FACTORY_DEFAULTS;
  event.eventData.zclEventData.addressing = addressing;
  event.eventData.zclEventData.payloadLength = payloadLength;
  event.eventData.zclEventData.payload = payload;

  for (uint8_t i = 0; i < DS_SERVER_CLUSTER_INIT_COUNT; i++)
  {
    if (dsServerClusterInitFunctions[i])
      (dsServerClusterInitFunctions[i])();
  }
  for (uint8_t i = 0; i < DS_CLIENT_CLUSTER_INIT_COUNT; i++)
  {
    if (dsClientClusterInitFunctions[i])
      (dsClientClusterInitFunctions[i])();
  }

  // needs to enable after app directory is created
  PDS_Store(Z3DEVICE_APP_MEMORY_MEM_ID);

  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (BASIC_CLUSTER_CS != "SERVER")  &&  (BC_RESETTOFNCMD == true) >
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

  commandManagerSendCommand(req);
}

#endif //#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
</#if>

#endif // APP_DEVICE_TYPE_DIMMER_SWITCH
// eof dsBasicCluster.c
