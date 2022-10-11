/*******************************************************************************
  Combined Interface Source File

  Company:
    Microchip Technology Inc.

  File Name:
    controlBridge.c

  Summary:
    This file contains Combined Interface implementation

  Description:
    This file contains Combined Interface implementation
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
#include <cbClusters.h>
#include <cbBasicCluster.h>
#include <identifyCluster.h>
#include <cbIdentifyCluster.h>
#include <cbOnOffCluster.h>
#include <cbLevelControlCluster.h>
#include <cbGroupsCluster.h>
#include <cbOccupancySensingCluster.h>
#include <cbIlluminanceMeasurementCluster.h>
#include <cbColorControlCluster.h>
#include <cbScenesCluster.h>
#include <cbCommissioningCluster.h>
#include <z3Device.h>
#include <console.h>
#include <zclSecurityManager.h>
#include <resetReason.h>
#include <zclCommandManager.h>
#include <otauService.h>
#include <mac.h>
/******************************************************************************
                    Local variables section
******************************************************************************/
static ZCL_DeviceEndpoint_t cbEndpoint =
{
  .simpleDescriptor =
  {
    .endpoint            = APP_ENDPOINT_CONTROL_BRIDGE,
    .AppProfileId        = PROFILE_ID_HOME_AUTOMATION,
    .AppDeviceId         = APP_Z3DEVICE_ID,
    .AppDeviceVersion    = 0x1,
    .AppInClustersCount  = ARRAY_SIZE(cbServerClusterIds),
    .AppInClustersList   = cbServerClusterIds,
    .AppOutClustersCount = ARRAY_SIZE(cbClientClusterIds),
    .AppOutClustersList  = cbClientClusterIds,
  },
  .serverCluster = cbServerClusters,
  .clientCluster = cbClientClusters,
};

static ClusterId_t cbClientClusterToBindIds[] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID,
  ONOFF_CLUSTER_ID,
  LEVEL_CONTROL_CLUSTER_ID,
  GROUPS_CLUSTER_ID,
  SCENES_CLUSTER_ID,
  OCCUPANCY_SENSING_CLUSTER_ID,
  ILLUMINANCE_MEASUREMENT_CLUSTER_ID,
  ZLL_COMMISSIONING_CLUSTER_ID,
  COLOR_CONTROL_CLUSTER_ID
};
static ClusterId_t cbServerClusterToBindIds[] =
{
  BASIC_CLUSTER_ID,
  IDENTIFY_CLUSTER_ID
};
static AppBindReq_t cbBindReq =
{
  .remoteServers     = cbClientClusterToBindIds,
  .remoteServersCnt  = ARRAY_SIZE(cbClientClusterToBindIds),
  .remoteClients     = cbServerClusterToBindIds,
  .remoteClientsCnt  = ARRAY_SIZE(cbServerClusterToBindIds),
  .groupId           = 0xffff,
  .srcEndpoint       = APP_ENDPOINT_CONTROL_BRIDGE,
  .callback          = NULL,
  .startIdentifyingFn= cbIdetifyStartIdentifyingCb
};

static ZCL_LinkKeyDesc_t lightKeyDesc = {CCPU_TO_LE64(APS_UNIVERSAL_EXTENDED_ADDRESS), HA_LINK_KEY};

/******************************************************************************
                        Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Device initialization routine
******************************************************************************/
void appDeviceInit(void)
{
#if (APP_ENABLE_CONSOLE == 1) || (APP_DEVICE_EVENTS_LOGGING == 1)
  uartInit();
#endif
#if APP_ENABLE_CONSOLE == 1
  initConsole();
#endif
  /* Bind request with clusters to bind for initiator device */
 APP_RegisterEndpoint(&cbEndpoint, &cbBindReq);
  commandManagerInit();

  cbBasicClusterInit();
  cbIdentifyClusterInit();
  cbOnOffClusterInit();
  cbLevelControlClusterInit();
  cbColorControlClusterInit();
  cbGroupsClusterInit();
  cbScenesClusterInit();
  cbOccupancySensingClusterInit();
  cbIlluminanceMeasurementClusterInit();
  cbCommissioningServerClusterInit();
}

/**************************************************************************//**
\brief Performs security initialization actions
******************************************************************************/
void appSecurityInit(void)
{
  ZCL_Set_t zclSet;
  ExtAddr_t trustCenterAddress;
  ExtAddr_t macAddr;
  APS_TcMode_t tcMode;
  DeviceType_t deviceType;
  // Setup security parameters
  bool securityOn;

  CS_ReadParameter(CS_SECURITY_ON_ID, &securityOn);
  if (securityOn)
  {
    uint8_t preconfiguredStatus;
    CS_ReadParameter(CS_APS_TRUST_CENTER_ADDRESS_ID, &trustCenterAddress);
    CS_ReadParameter(CS_UID_ID, &macAddr);
    if (IS_EQ_EXT_ADDR(macAddr, trustCenterAddress))
      tcMode = APS_CENTRALIZED_TRUST_CENTER;
    else
      tcMode = APS_NOT_TRUST_CENTER;

    CS_ReadParameter(CS_ZDO_SECURITY_STATUS_ID, &preconfiguredStatus);
    CS_ReadParameter(CS_DEVICE_TYPE_ID, &deviceType);

    if ((PRECONFIGURED_NETWORK_KEY == preconfiguredStatus)
      || (APS_CENTRALIZED_TRUST_CENTER == tcMode)
    )
    {
      uint8_t nwkDefaultKey[SECURITY_KEY_SIZE];

      CS_ReadParameter(CS_NETWORK_KEY_ID, &nwkDefaultKey);
      NWK_SetKey(nwkDefaultKey, NWK_STARTUP_ACTIVE_KEY_SEQUENCE_NUMBER);
      NWK_ActivateKey(NWK_STARTUP_ACTIVE_KEY_SEQUENCE_NUMBER);
    }
  }

  ZCL_ResetSecurity();

  //Setting the Link Key Descriptor
  zclSet.attr.id = ZCL_LINK_KEY_DESC_ID;
  zclSet.attr.value.linkKeyDesc = &lightKeyDesc;
  ZCL_Set(&zclSet);
}

/**************************************************************************//**
\brief Device common task handler
******************************************************************************/
void appDeviceTaskHandler(void)
{
  switch (appDeviceState) // Actual device state when one joined network
  {
    case DEVICE_INITIAL_STATE:
      {
        appDeviceState = DEVICE_ACTIVE_IDLE_STATE;
        startOtauServer(&cbServerClusters[CB_SERVER_CLUSTERS_COUNT - 1]);
      }
      break;
    case DEVICE_ACTIVE_IDLE_STATE:
    default:
      break;
  }
}

/**************************************************************************//**
\brief Stops identifying on endpoints
******************************************************************************/
void appIdentifyStart(uint16_t identifyTime, bool colorEffect, uint16_t enhancedHue)
{
  cbIdentifyStart(identifyTime);
  
  (void)colorEffect,(void)enhancedHue;
}

/**************************************************************************//**
\brief Stops identifying on endpoints
******************************************************************************/
void appIdentifyStop(void)
{
  cbIdentifyStop();
}

#endif // APP_DEVICE_TYPE_CONTROL_BRIDGE
// eof combinedInterface.c