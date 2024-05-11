/*******************************************************************************
  Custom Diagnostics Cluster Source file

  Company:
    Microchip Technology Inc.

  File Name:
    customDiagnosticsCluster.c

  Summary:
    This file contains Custom Diagnostics Cluster Implementation.

  Description:
    This file contains Custom Diagnostics Cluster Implementation.
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
#include <zcl/include/zclDiagnosticsCluster.h>
#include <z3device/clusters/include/haClusters.h>
#include <app_zigbee/zigbee_console/console.h>
#include <zcl/include/zclCommandManager.h>
#include <pds/include/wlPdsMemIds.h>
#include <z3device/common/include/z3Device.h>


/******************************************************************************
                    Definition(s) section
******************************************************************************/


/******************************************************************************
                    Prototypes section
******************************************************************************/
<#if (DIAGONSTICS_CLUSTER_CS != "CLIENT")>
static void customDiagnosticsEventListener(SYS_EventId_t eventId, SYS_EventData_t data);
</#if>
/******************************************************************************
                    Global variables section
******************************************************************************/
<#if (DIAGONSTICS_CLUSTER_CS != "CLIENT")>
ZCL_DiagnosticsClusterServerAttributes_t customDiagnosticsClusterServerAttributes =
{
  ZCL_DEFINE_DIAGNOSTICS_CLUSTER_SERVER_ATTRIBUTES()
};
</#if>
/******************************************************************************
                    Static variables section
******************************************************************************/
<#if (DIAGONSTICS_CLUSTER_CS != "CLIENT")>
static SYS_EventReceiver_t customEventReceiver = { .func = customDiagnosticsEventListener};
</#if>
/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes diagnostics cluster
******************************************************************************/
void customDiagnosticsClusterInit(void)
{
<#if (DIAGONSTICS_CLUSTER_CS != "CLIENT")>
<#if (DIAGONSTICS_CLUSTER_CS != "CLIENT")  && (DC_AVGMACRETRYPERAPSMESSAGESENT == true)>  
  customDiagnosticsClusterServerAttributes.averageMACRetryPerAPSMessageSent.value = 0;
</#if>
<#if (DIAGONSTICS_CLUSTER_CS != "CLIENT")  && (DC_LASTMESSAGELQI == true)>
  customDiagnosticsClusterServerAttributes.lastMessageLQI.value = 0;
</#if>
<#if (DIAGONSTICS_CLUSTER_CS != "CLIENT")  && (DC_LASTMESSAGERSSI == true)>
  customDiagnosticsClusterServerAttributes.lastMessageRSSI.value = 0;
</#if>
  SYS_SubscribeToEvent(BC_EVENT_APS_DATA_INDICATION, &customEventReceiver);
  SYS_SubscribeToEvent(BC_EVENT_NWK_DATA_CONFIRM, &customEventReceiver);
</#if>
}

<#if (DIAGONSTICS_CLUSTER_CS != "CLIENT")>
static void customDiagnosticsEventListener(SYS_EventId_t eventId, SYS_EventData_t data)
{
  switch(eventId)
  {
    case BC_EVENT_APS_DATA_INDICATION:
      if(NULL != (APS_DataQualityIndicator_t *)data)
      {
        APS_DataQualityIndicator_t *apsDataQualityIndicator = (APS_DataQualityIndicator_t *)data;
<#if (DIAGONSTICS_CLUSTER_CS != "CLIENT")  && (DC_LASTMESSAGELQI == true)>        
        customDiagnosticsClusterServerAttributes.lastMessageLQI.value = apsDataQualityIndicator->linkQuality;
</#if>
<#if (DIAGONSTICS_CLUSTER_CS != "CLIENT")  && (DC_LASTMESSAGERSSI == true)>        
        customDiagnosticsClusterServerAttributes.lastMessageRSSI.value = apsDataQualityIndicator->rssi;
</#if>
      }
      break;

    case BC_EVENT_NWK_DATA_CONFIRM:
      if(NULL != (uint16_t*)data)
      {
        static bool firstPacket = 1;
        if(firstPacket)
        {
<#if (DIAGONSTICS_CLUSTER_CS != "CLIENT")  && (DC_AVGMACRETRYPERAPSMESSAGESENT == true)>           
          customDiagnosticsClusterServerAttributes.averageMACRetryPerAPSMessageSent.value
            = *(uint16_t*)data;
</#if>            
          firstPacket = 0;
        }
<#if (DIAGONSTICS_CLUSTER_CS != "CLIENT")  && (DC_AVGMACRETRYPERAPSMESSAGESENT == true)>        
        else
        {
           
          customDiagnosticsClusterServerAttributes.averageMACRetryPerAPSMessageSent.value
            = (customDiagnosticsClusterServerAttributes.averageMACRetryPerAPSMessageSent.value 
              + *(uint16_t*)data) / 2;           
        }
</#if>
      }
      break;
    default:
      break;
  }
}
</#if>
// eof customDiagnosticsCluster.c

