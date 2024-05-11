/*******************************************************************************
  Dimmable Light Basic cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    dlBasicCluster.c

  Summary:
    This file contains the Dimmable Light Basic cluster interface.

  Description:
    This file contains the Dimmable Light Basic cluster interface.
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

#ifdef APP_DEVICE_TYPE_DIMMABLE_LIGHT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <dlBasicCluster.h>
#include <basicCluster.h>
#include <dlClusters.h>
#include <pdsDataServer.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_BasicClusterServerAttributes_t dlBasicClusterServerAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER_ATTRIBUTES()
};

#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
ZCL_BasicClusterClientAttributes_t dlBasicClusterClientAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_CLIENT_ATTRIBUTES()
};
#endif

ZCL_BasicClusterServerCommands_t dlBasicClusterServerCommands =
{
  ZCL_DEFINE_BASIC_CLUSTER_COMMANDS(resetToFactoryDefaultsInd)
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Basic cluster
******************************************************************************/
void basicClusterInit(void)
{
  memcpy(&dlBasicClusterServerAttributes.swBuildId.value, 0x00, 16);
  memcpy(&dlBasicClusterServerAttributes.dateCode.value, 0x00, 16);
  memcpy(&dlBasicClusterServerAttributes.manufacturerName.value, 0x00, 32);
  memcpy(&dlBasicClusterServerAttributes.modelIdentifier.value, 0x00, 32);
  memcpy(&dlBasicClusterServerAttributes.productCode.value, 0x00, 32);
  memcpy(&dlBasicClusterServerAttributes.productURL.value, 0x00, 32);
  
  dlBasicClusterServerAttributes.clusterVersion.value      = 0x0001u;
  dlBasicClusterServerAttributes.zclVersion.value          = 0x01;
  dlBasicClusterServerAttributes.powerSource.value         = 0x04;
  dlBasicClusterServerAttributes.physicalEnvironment.value = 0x00;
  dlBasicClusterServerAttributes.applicationVersion.value  = 2;
  dlBasicClusterServerAttributes.stackVersion.value        = 3;
  dlBasicClusterServerAttributes.hwVersion.value           = 4;
  
  memcpy(dlBasicClusterServerAttributes.manufacturerName.value, "\x1f Microchip ", 8);
  memcpy(dlBasicClusterServerAttributes.modelIdentifier.value, "\x1f ZLODevice", 11);
  memcpy(dlBasicClusterServerAttributes.dateCode.value, "\xf 20150901", 10);
  dlBasicClusterServerAttributes.genericDeviceClass.value  = LIGHTING_DEVICE_CLASS;
  dlBasicClusterServerAttributes.genericDeviceType.value   = LED_BULB;  
  memcpy(dlBasicClusterServerAttributes.productCode.value, "\x1f\x4XYZ123", 8);
  memcpy(dlBasicClusterServerAttributes.productURL.value, "\x1f ww.microchip.com", 15);
  memcpy(dlBasicClusterServerAttributes.swBuildId.value, "\xf abcdefgh", 10);
#if ZLO_EXTRA_CLUSTERS_SUPPORT == 1
  dlBasicClusterClientAttributes.clusterVersion.value      = 1;
#endif
}

/**************************************************************************//**
\brief Callback on receive of resetToFactoryDefaults command
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  for (uint8_t i=0; i<DL_SERVER_CLUSTER_INIT_COUNT; i++)
  {
    if (dlServerClusterInitFunctions[i])
      (dlServerClusterInitFunctions[i])();
  }

#ifdef OTAU_CLIENT	
  for (uint8_t i=0; i<DL_CLIENT_CLUSTER_INIT_COUNT; i++)
  {
    if (dlClientClusterInitFunctions[i])
      (dlClientClusterInitFunctions[i])();
  }
#endif
   PDS_Store(HA_APP_MEMORY_MEM_ID);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}


#endif // APP_DEVICE_TYPE_DIMMABLE_LIGHT

// eof dlBasicCluster.c
