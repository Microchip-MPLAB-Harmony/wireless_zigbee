/*******************************************************************************
  Custom Diagnostic cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    customDiagnosticsCluster.c

  Summary:
    This file contains the Custom Diagnostic Cluster implementation.

  Description:
    This file contains the Custom Diagnostic Cluster implementation.
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
/******************************************************************************
                    Includes section
******************************************************************************/
#include <zclDiagnosticsCluster.h>
#include <haClusters.h>
#include <console.h>
#include <commandManager.h>
#include <wlPdsMemIds.h>
#include <z3Device.h>


/******************************************************************************
                    Definition(s) section
******************************************************************************/


/******************************************************************************
                    Prototypes section
******************************************************************************/
static void customDiagnosticsEventListener(SYS_EventId_t eventId, SYS_EventData_t data);

/******************************************************************************
                    Global variables section
******************************************************************************/
ZCL_DiagnosticsClusterServerAttributes_t DiagnosticsClusterServerAttributes =
{
  ZCL_DEFINE_DIAGNOSTICS_CLUSTER_SERVER_ATTRIBUTES()
};

/******************************************************************************
                    Static variables section
******************************************************************************/
static SYS_EventReceiver_t customEventReceiver = { .func = customDiagnosticsEventListener};
/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes diagnostics cluster
******************************************************************************/
void diagnosticsClusterInit(void)
{
  DiagnosticsClusterServerAttributes.averageMACRetryPerAPSMessageSent.value = 0;
  DiagnosticsClusterServerAttributes.lastMessageLQI.value = 0;
  DiagnosticsClusterServerAttributes.lastMessageRSSI.value = 0;
  SYS_SubscribeToEvent(BC_EVENT_APS_DATA_INDICATION, &customEventReceiver);
  SYS_SubscribeToEvent(BC_EVENT_NWK_DATA_CONFIRM, &customEventReceiver);
}

static void customDiagnosticsEventListener(SYS_EventId_t eventId, SYS_EventData_t data)
{
  switch(eventId)
  {
    case BC_EVENT_APS_DATA_INDICATION:
      if(NULL != (APS_DataQualityIndicator_t *)data)
      {
        APS_DataQualityIndicator_t *apsDataQualityIndicator = (APS_DataQualityIndicator_t *)data;
        DiagnosticsClusterServerAttributes.lastMessageLQI.value = apsDataQualityIndicator->linkQuality;
        DiagnosticsClusterServerAttributes.lastMessageRSSI.value = apsDataQualityIndicator->rssi;
      }
      break;

    case BC_EVENT_NWK_DATA_CONFIRM:
      if(NULL != (uint16_t*)data)
      {
        static bool firstPacket = 1;
        if(firstPacket)
        {
          DiagnosticsClusterServerAttributes.averageMACRetryPerAPSMessageSent.value
            = *(uint16_t*)data;
          firstPacket = 0;
        }
        else
        {
           
          DiagnosticsClusterServerAttributes.averageMACRetryPerAPSMessageSent.value
            = (DiagnosticsClusterServerAttributes.averageMACRetryPerAPSMessageSent.value 
              + *(uint16_t*)data) / 2;           
        }
      }
      break;
    default:
      break;
  }
}

// eof customDiagnosticsCluster.c

