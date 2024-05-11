	/*******************************************************************************
  Custom Fan Control Cluster Source file

  Company:
    Microchip Technology Inc.

  File Name:
    customFanControlCluster.c

  Summary:
    This file contains Custom Fan Control Cluster Implementation.

  Description:
    This file contains Custom Fan Control Cluster Implementation.
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
#include <z3device/custom/include/customFanControlCluster.h>
#if APP_ENABLE_CONSOLE == 1
#include <app_zigbee/zigbee_console/console.h>
#endif
#include <zcl/include/zclCommandManager.h>
#include <zcl/include/zclAttributes.h>
#include <z3device/clusters/include/haClusters.h>
#include <z3device/common/include/appConsts.h>
#include <app_zigbee/app_zigbee_handler.h>
/******************************************************************************
                    Global variables
******************************************************************************/
<#if (FANCONTROL_CLUSTER_CS != "CLIENT")>
ZCL_FanControlClusterServerAttributes_t customFanControlClusterServerAttributes =
{
  ZCL_DEFINE_FAN_CONTROL_CLUSTER_SERVER_ATTRIBUTES()
};
</#if>

<#if (FANCONTROL_CLUSTER_CS != "SERVER")>
ZCL_FanControlClusterClientAttributes_t customFanControlClusterClientAttributes =
{
  ZCL_DEFINE_FAN_CONTROL_CLUSTER_CLIENT_ATTRIBUTES()
};
</#if>
/******************************************************************************
                    Prototypes section
******************************************************************************/

static void customFanControlAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
<#if (FANCONTROL_CLUSTER_CS != "CLIENT")>
static void customFanControlEventListener(SYS_EventId_t eventId, SYS_EventData_t data);
static void customFanControlsetFanOnOff(ZCL_FanControlFanMode_t fanState);
</#if>

/******************************************************************************
                    Local variables
******************************************************************************/
<#if (FANCONTROL_CLUSTER_CS != "CLIENT")>
static SYS_EventReceiver_t FanControlEvent = { .func = customFanControlEventListener};
static ZCL_FanControlFanMode_t fanMotorControl = ZCL_FC_FAN_MODE_OFF;
</#if>
/*****************************************************************************/

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Fan Control cluster
******************************************************************************/
void customFanControlClusterInit(void)
{
<#if (FANCONTROL_CLUSTER_CS != "CLIENT")>
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, FAN_CONTROL_CLUSTER_ID, ZCL_CLUSTER_SIDE_SERVER);
</#if>
<#if (FANCONTROL_CLUSTER_CS != "SERVER")>  
  ZCL_Cluster_t *fanControlcluster = ZCL_GetCluster(APP_ENDPOINT_CUSTOM, FAN_CONTROL_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT); 
</#if>  

<#if (FANCONTROL_CLUSTER_CS != "CLIENT")>
  if (cluster)
<#else>
  if (fanControlcluster)
</#if>
  {
<#if (FANCONTROL_CLUSTER_CS != "CLIENT")>
    cluster->ZCL_AttributeEventInd = customFanControlAttrEventInd;
<#else>
    fanControlcluster->ZCL_AttributeEventInd = customFanControlAttrEventInd;
</#if>
  }
<#if (FANCONTROL_CLUSTER_CS != "CLIENT")  && (FC_FANMODE == true)>  
  customFanControlClusterServerAttributes.fanMode.value = ZCL_FAN_CONTROL_CL_FAN_MODE_SER_ATTR_DEFAULT_VAL;
</#if>
<#if (FANCONTROL_CLUSTER_CS != "CLIENT")  && (FC_FANMODESEQUENCE == true)>  
  customFanControlClusterServerAttributes.fanModeSequence.value = ZCL_FAN_CONTROL_CL_FAN_SEQUENCE_OPERATION_SER_ATTR_DEFAULT_VAL;
</#if>
<#if (FANCONTROL_CLUSTER_CS != "CLIENT")  && (FC_CLUSTERREVISION == true)>  
  customFanControlClusterServerAttributes.clusterVersion.value = FAN_CONTROL_CLUSTER_VERSION;
</#if>
<#if (FANCONTROL_CLUSTER_CS != "CLIENT")>  
  SYS_SubscribeToEvent(BC_ZCL_EVENT_ACTION_REQUEST, &FanControlEvent);
</#if>
<#if (FANCONTROL_CLUSTER_CS != "SERVER")  && (FCC_CLUSTERREVISION == true)>  
  customFanControlClusterClientAttributes.clusterVersion.value = FAN_CONTROL_CLUSTER_VERSION;
</#if>
<#if (FANCONTROL_CLUSTER_CS != "CLIENT")>
  cluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
<#else>
  fanControlcluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
</#if>  
}

/**************************************************************************//**
\brief Attribute Event indication handler(to indicate when attr values have
        read or written)

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void customFanControlAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
<#if (FANCONTROL_CLUSTER_CS != "CLIENT")>
<#if (FANCONTROL_CLUSTER_CS != "CLIENT")  && (FC_FANMODE == true)>
  if ( (attributeId == ZCL_FAN_CONTROL_CLUSTER_FAN_MODE_SERVER_ATTRIBUTE_ID) 
           && (event == ZCL_WRITE_ATTRIBUTE_EVENT) )
  {
    switch(customFanControlClusterServerAttributes.fanMode.value)
    {
      case ZCL_FC_FAN_MODE_LOW:
      case ZCL_FC_FAN_MODE_MEDIUM:
      case ZCL_FC_FAN_MODE_HIGH:
        fanMotorControl = (ZCL_FanControlFanMode_t)customFanControlClusterServerAttributes.fanMode.value;
        break;
      case ZCL_FC_FAN_MODE_AUTO:
        /*Specification does not define this case, hence setting it to medium
        User may change for actual fan control*/
        fanMotorControl = ZCL_FC_FAN_MODE_MEDIUM;
        break;
      case ZCL_FC_FAN_MODE_OFF:
      case ZCL_FC_FAN_MODE_ON:
        customFanControlsetFanOnOff((ZCL_FanControlFanMode_t)customFanControlClusterServerAttributes.fanMode.value);
        break;
    }
  }
</#if>
</#if>  
  APP_Zigbee_Event_t eventItem;
  eventItem.eventGroup = EVENT_CLUSTER;
  eventItem.eventId = CMD_ZCL_ATTR_FANCONTROL;
  eventItem.eventData.zclAttributeData.addressing = addressing;
  eventItem.eventData.zclAttributeData.attributeId = attributeId;
  eventItem.eventData.zclAttributeData.event = event;
  APP_Zigbee_Handler(eventItem);
}

<#if (FANCONTROL_CLUSTER_CS != "CLIENT")>
/**************************************************************************//**
  \brief  ZCL action request event handler, 
          handles the ZCL_ACTION_WRITE_ATTR_REQUEST for attribute specific validation

  \param[in] ev - must be BC_ZCL_EVENT_ACTION_REQUEST.
  \param[in] data - this field must contain pointer to the BcZCLActionReq_t structure,

  \return None.
 ******************************************************************************/
static void customFanControlEventListener(SYS_EventId_t eventId, SYS_EventData_t data)
{
  BcZCLActionReq_t *const actionReq = (BcZCLActionReq_t*)data;  
  ZCL_FanControlFanMode_t requestedValue = (ZCL_FanControlFanMode_t)0;

  if (BC_ZCL_EVENT_ACTION_REQUEST != eventId)
    return;
  
  if (ZCL_ACTION_WRITE_ATTR_REQUEST != actionReq->action)
    return;

  ZCLActionWriteAttrReq_t *const zclWriteAttrReq = (ZCLActionWriteAttrReq_t*)actionReq->context;
  if( (FAN_CONTROL_CLUSTER_ID != zclWriteAttrReq->clusterId) || 
          (ZCL_CLUSTER_SIDE_SERVER != zclWriteAttrReq->clusterSide))
    return;

  requestedValue = (ZCL_FanControlFanMode_t)(*((uint8_t*)(zclWriteAttrReq->attrValue)));
  if(ZCL_FAN_CONTROL_CLUSTER_FAN_MODE_SERVER_ATTRIBUTE_ID != zclWriteAttrReq->attrId)
    return;
<#if (FANCONTROL_CLUSTER_CS != "CLIENT")  && (FC_FANMODESEQUENCE == true)>
  switch(customFanControlClusterServerAttributes.fanModeSequence.value)
  {
    case ZCL_FC_FAN_SEQUENCE_OPERATION_LOW_MED_HIGH:
      if(ZCL_FC_FAN_MODE_AUTO == requestedValue)
        actionReq->denied = 1U;
      break;
    case ZCL_FC_FAN_SEQUENCE_OPERATION_LOW_HIGH:
      if((ZCL_FC_FAN_MODE_AUTO == requestedValue) || (ZCL_FC_FAN_MODE_MEDIUM == requestedValue))
        actionReq->denied = 1U;
      break;
    case ZCL_FC_FAN_SEQUENCE_OPERATION_LOW_MED_HIGH_AUTO:
      actionReq->denied = 0U;
      break;
    case ZCL_FC_FAN_SEQUENCE_OPERATION_LOW_HIGH_AUTO:
      if(ZCL_FC_FAN_MODE_MEDIUM == requestedValue)
        actionReq->denied = 1U;
      break;
    case ZCL_FC_FAN_SEQUENCE_OPERATION_ON_AUTO:
      if(ZCL_FC_FAN_MODE_AUTO != requestedValue)
        actionReq->denied = 1U;
      break;
    default:
      actionReq->denied = 0U;
      break;
  }
</#if>  
}

/**************************************************************************//**
\brief Occupancy notification from Occupancy (client/server) cluster

\param[in] occupied - 0 - Not occupied, 1- occupied
\param[out] - None
******************************************************************************/
void customFanControlOccupancyNotify(bool occupied)
{
  if(ZCL_FC_FAN_MODE_SMART == customFanControlClusterServerAttributes.fanMode.value)
  {
    if(occupied)    customFanControlsetFanOnOff(ZCL_FC_FAN_MODE_ON);
    else    customFanControlsetFanOnOff(ZCL_FC_FAN_MODE_OFF);
  }
}

/**************************************************************************//**
\brief Set the fan to ON or OFF (need to modified by the user)

\param[in] fanState : 0 - off, non zero - ON
\param[out] - None
******************************************************************************/
static void customFanControlsetFanOnOff(ZCL_FanControlFanMode_t fanState)
{ 
  /*The user has to implement the functionality to control the actual fan*/
  if(fanState)
  {
#if APP_ENABLE_CONSOLE == 1
    appSnprintf("Fan is turned ON at speed 0x%x\r\n",fanMotorControl);
#else
    (void)fanMotorControl;
#endif
  }
#if APP_ENABLE_CONSOLE == 1
  else
    appSnprintf("Fan is turned OFF\r\n");
#endif
}
</#if>
// eof customFanControlCluster.c