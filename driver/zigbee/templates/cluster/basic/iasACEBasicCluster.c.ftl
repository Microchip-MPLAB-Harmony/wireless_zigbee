/*******************************************************************************
  IAS ACE Basic cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    iasACEBasicCluster.c

  Summary:
    This file contains the IAS ACE Basic cluster interface.

  Description:
    This file contains the IAS ACE Basic cluster interface.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_IAS_ACE)

/******************************************************************************
                    Includes section
******************************************************************************/
#include <z3device/ias_ace/include/iasacebasiccluster.h>
#include <z3device/ias_ace/include/iasACECluster.h>
#include <z3device/clusters/include/basicCluster.h>
#include <z3device/clusters/include/haClusters.h>
#include <zcl/include/zclCommandManager.h>
#include <z3device/common/include/appConsts.h>
#include <app_zigbee/app_zigbee_handler.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
<#if (BASIC_CLUSTER_CS != "CLIENT")  &&  (BS_RESETTOFNCMD == true) >
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
</#if>
/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_BasicClusterServerAttributes_t  iasACEBasicClusterServerAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER_ATTRIBUTES()
};

ZCL_BasicClusterClientAttributes_t iasACEBasicClusterClientAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_CLIENT_ATTRIBUTES()
};

PROGMEM_DECLARE (ZCL_BasicClusterServerCommands_t iasACEBasicClusterServerCommands) =
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
void iasBasicClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_IAS_ACE, BASIC_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_CLUSTERREVISION == true) >
  iasACEBasicClusterServerAttributes.clusterVersion.value      = BASIC_CLUSTER_VERSION;
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_ZCLVERSION == true) >
  iasACEBasicClusterServerAttributes.zclVersion.value          = ZCL_VERSION;
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_POWERSOURCE == true) >
  iasACEBasicClusterServerAttributes.powerSource.value         = POWER_SOURCE;
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_PHYENV == true) >
  iasACEBasicClusterServerAttributes.physicalEnvironment.value = UNKNOWN_ENVIRONMENT;
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_APPLCIATIONVERSION == true) >
  iasACEBasicClusterServerAttributes.applicationVersion.value  = APP_VERSION;
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_STACKVERSION == true) >
  iasACEBasicClusterServerAttributes.stackVersion.value        = STACK_VERSION;
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_HWVERSION == true) >
  iasACEBasicClusterServerAttributes.hwVersion.value           = HW_VERSION;
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_MANUNAME == true) >
  memcpy(iasACEBasicClusterServerAttributes.manufacturerName.value, "\x1f Microchip ", 12);
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_MODELID == true) >
  memcpy(iasACEBasicClusterServerAttributes.modelIdentifier.value, "\x1f ZLODevice", 12);
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_DATECODE == true) >
  memcpy(iasACEBasicClusterServerAttributes.dateCode.value, "\xf 20150901", 10);
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_SWBUILDID == true) >
  memcpy(iasACEBasicClusterServerAttributes.swBuildId.value, "\xf abcdefgh", 10);
</#if>
#if ZLO_CLUSTER_ENHANCEMENTS == 1
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_GENDEVCLASS == true) >
  iasACEBasicClusterServerAttributes.genericDeviceClass.value  = LIGHTING_DEVICE_CLASS;
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_GENDEVCTYPE == true) >
  iasACEBasicClusterServerAttributes.genericDeviceType.value   = LED_BULB_DEVICE_TYPE;
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_PRODUCTCODE == true) >
  memcpy(iasACEBasicClusterServerAttributes.productCode.value, "\x1f\x4XYZ123", 8);
</#if>
<#if (BASIC_CLUSTER_CS != "CLIENT")  && (BC_PRODUCTURL == true) >
  memcpy(iasACEBasicClusterServerAttributes.productURL.value, "\x1f www.microchip.com", 15);
</#if>
#endif
  

<#if (BASIC_CLUSTER_CS != "CLEINT")  && (BS_CLUSTERREVISION == true) >
#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
  iasACEBasicClusterServerAttributes.clusterVersion.value      = BASIC_CLUSTER_VERSION;
#endif
</#if>
<#if (BASIC_CLUSTER_CS != "SERVER")  && (BC_CLUSTERREVISION == true) >
  iasACEBasicClusterClientAttributes.clusterVersion.value      = BASIC_CLUSTER_VERSION;
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

  for (uint8_t i=0; i<IAS_ACE_SERVER_CLUSTER_INIT_COUNT; i++)
  {
     if (iasACEServerClusterInitFunctions[i])
      (iasACEServerClusterInitFunctions[i])();
  }

#ifdef OTAU_CLIENT 
  for (uint8_t i=0; i<IAS_ACE_CLIENT_CLUSTER_INIT_COUNT; i++)
  {
    if (iasACEClientClusterInitFunctions[i])
      (iasACEClientClusterInitFunctions[i])();
  }
#endif 
  APP_Zigbee_Handler(event);
  return ZCL_SUCCESS_STATUS;
}
</#if>
<#if (BASIC_CLUSTER_CS != "SERVER")  &&  (BC_RESETTOFNCMD == true) >
#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
/**************************************************************************//**
\brief Sends resetToFactoryDefaults command unicastly

\param[in] mode - address mode;
\param[in] addr - short address of destination node;
\param[in] ep   - destination endpoint;
\param[in] srcEp- source endpoint;
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
</#if>

#endif // APP_DEVICE_TYPE_IAS_ACE

// eof iasACEBasicCluster.c
