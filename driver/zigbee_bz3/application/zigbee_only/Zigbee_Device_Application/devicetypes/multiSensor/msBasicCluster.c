/*******************************************************************************
  Multi-Sensor Basic cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    msBasicCluster.c

  Summary:
    This file contains Multi-Sensor Basic cluster implementation.

  Description:
    This file contains Multi-Sensor Basic cluster implementation.
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

#ifdef APP_DEVICE_TYPE_MULTI_SENSOR

/******************************************************************************
                    Includes section
******************************************************************************/
#include <msBasicCluster.h>
#include <basicCluster.h>
#include <msClusters.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_BasicClusterServerAttributes_t msBasicClusterServerAttributes =
{
  ZCL_DEFINE_BASIC_CLUSTER_SERVER_ATTRIBUTES()
};


ZCL_BasicClusterServerCommands_t msBasicClusterServerCommands =
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
  msBasicClusterServerAttributes.zclVersion.value          = 0x01;
  msBasicClusterServerAttributes.powerSource.value         = 0x04;
  msBasicClusterServerAttributes.physicalEnvironment.value = 0x00;
  msBasicClusterServerAttributes.applicationVersion.value  = 2;
  msBasicClusterServerAttributes.stackVersion.value        = 3;
  msBasicClusterServerAttributes.hwVersion.value           = 4;

  memcpy(msBasicClusterServerAttributes.manufacturerName.value, "\x1f Microchip ", 8);
  memcpy(msBasicClusterServerAttributes.modelIdentifier.value, "\x1f MultiSensor", 13);
}

/**************************************************************************//**
\brief Callback on receive of resetToFactoryDefaults command
******************************************************************************/
static ZCL_Status_t resetToFactoryDefaultsInd(ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload)
{

#ifdef OTAU_CLIENT
  for (uint8_t i=0; i<MS_CLIENT_CLUSTER_INIT_COUNT; i++)
  {
    if (msClientClusterInitFunctions[i])
      (msClientClusterInitFunctions[i])();
  }
#endif

  // needs to enable after app directory is created
  //PDS_Store(HA_APP_MEMORY_MEM_ID);

  (void)addressing;
  (void)payloadLength;
  (void)payload;
  return ZCL_SUCCESS_STATUS;
}

#endif // APP_DEVICE_TYPE_MULTI_SENSOR

// eof msBasicCluster.c
