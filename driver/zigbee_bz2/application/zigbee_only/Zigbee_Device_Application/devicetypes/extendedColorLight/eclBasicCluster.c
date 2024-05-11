/*******************************************************************************
  Extended Color Light Basic cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    eclBasicCluster.c

  Summary:
    This file contains the Extended Color Light Basic cluster interface.

  Description:
    This file contains the Extended Color Light Basic cluster interface.
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

#ifdef APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT

/******************************************************************************
                    Includes section
******************************************************************************/
#include <eclBasicCluster.h>
#include <basicCluster.h>
#include <eclClusters.h>
#include <pdsDataServer.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_BasicClusterServerAttributes_t eclBasicClusterServerAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER_ATTRIBUTES()
};

ZCL_BasicClusterClientAttributes_t eclBasicClusterClientAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_CLIENT_ATTRIBUTES()
};

ZCL_BasicClusterServerCommands_t eclBasicClusterServerCommands =
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
  eclBasicClusterServerAttributes.zclVersion.value          = 0x01;
  eclBasicClusterServerAttributes.powerSource.value         = 0x04;
  eclBasicClusterServerAttributes.physicalEnvironment.value = 0x00;
  eclBasicClusterServerAttributes.applicationVersion.value  = 2;
  eclBasicClusterServerAttributes.stackVersion.value        = 3;
  eclBasicClusterServerAttributes.hwVersion.value           = 4;

  memcpy(eclBasicClusterServerAttributes.manufacturerName.value, "\x7 Microchip ", 8);
  memcpy(eclBasicClusterServerAttributes.modelIdentifier.value, "\x16 Extended Color Light ", 23);

  eclBasicClusterServerAttributes.clusterVersion.value      = 0x0001u;

  eclBasicClusterClientAttributes.clusterVersion.value      = 0x0001u;
}

/**************************************************************************//**
\brief Callback on receive of resetToFactoryDefaults command
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{
  for (uint8_t i=0; i<ECL_SERVER_CLUSTER_INIT_COUNT; i++)
  {
    if (eclServerClusterInitFunctions[i])
      (eclServerClusterInitFunctions[i])();
  }

#ifdef OTAU_CLIENT
  for (uint8_t i=0; i<ECL_CLIENT_CLUSTER_INIT_COUNT; i++)
  {
    if (eclClientClusterInitFunctions[i])
      (eclClientClusterInitFunctions[i])();
  }
#endif
   PDS_Store(HA_APP_MEMORY_MEM_ID);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}


#endif // APP_DEVICE_TYPE_EXTENDED_COLOR_LIGHT

// eof dlBasicCluster.c
