/*******************************************************************************
  Combined Interface Thermostat cluster Source File

  Company:
    Microchip Technology Inc.

  File Name:
    ciThermostatCluster.c

  Summary:
    This file contains the Combined Interface Thermostat cluster interface.

  Description:
    This file contains the Combined Interface Thermostat cluster interface.
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

#if (APP_Z3_DEVICE_TYPE == APP_DEVICE_TYPE_COMBINED_INTERFACE)

/******************************************************************************
                    Includes section
******************************************************************************/
#include <z3device/common/include/appConsts.h>
#include <z3device/combinedInterface/include/ciThermostatCluster.h>
#include <zcl/include/zclCommandManager.h>
#include <z3device/clusters/include/haClusters.h>
#include <app_zigbee/zigbee_console/console.h>

/******************************************************************************
//                      defines section
*****************************************************************************/

typedef struct PACK
{
  ZCL_AttributeId_t id;
  uint8_t type;
  uint8_t properties;
  int16_t value;
} setPoint_t;


/******************************************************************************
                    Prototypes section
******************************************************************************/
static void ciThermostatReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload);
static void ciThermostatAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);

/******************************************************************************
                    Global variables
******************************************************************************/
ZCL_ThermostatClusterClientAttributes_t ciThermostatClusterClientAttributes =
{  
  ZCL_DEFINE_THERMOSTAT_MEASUREMENT_CLUSTER_CLIENT_ATTRIBUTES()
};

/******************************************************************************
                    Implementation section
******************************************************************************/
/**************************************************************************//**
\brief Initializes Thermostat cluster
******************************************************************************/
void ciThermostatClusterInit(void)
{
  ZCL_Cluster_t *cluster = ZCL_GetCluster(APP_ENDPOINT_COMBINED_INTERFACE, THERMOSTAT_CLUSTER_ID, ZCL_CLUSTER_SIDE_CLIENT);
  ciThermostatClusterClientAttributes.clusterVersion.value = THERMOSTAT_CLUSTER_VERSION;
  
  if (cluster)
  {
    cluster->ZCL_ReportInd = ciThermostatReportInd;
    cluster->ZCL_AttributeEventInd = ciThermostatAttrEventInd;
  }
  cluster->ZCL_DefaultRespInd = ZCL_CommandZclDefaultResp;
}

/**************************************************************************//**
\brief Report attribute indication handler

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void ciThermostatReportInd(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload)
{
  ZCL_Report_t *rep = (ZCL_Report_t *)reportPayload;
  int16_t reportValue = 0;
  if(rep->id == ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID || (rep->id == ZCL_THERMOSTAT_CLUSTER_PI_COOLING_DEMAND_SERVER_ATTRIBUTE_ID)
     || (rep->id == ZCL_THERMOSTAT_CLUSTER_PI_HEATING_DEMAND_SERVER_ATTRIBUTE_ID))
  {
    if(rep->id == ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID)
    {
      memcpy(&reportValue, &rep->value[0], sizeof(int16_t));
      appSnprintf("<-Thermostat Attr (0x%x) Report: t = %d.%dC\r\n", rep->id, (int)(reportValue/THERMOSTAT_LOCAL_TEMPERATURE_SCALE),(int)(reportValue%THERMOSTAT_LOCAL_TEMPERATURE_SCALE));
    }
    else
    {
      memcpy(&reportValue, &rep->value[0], sizeof(uint8_t));
      appSnprintf("<-Thermostat Attr (0x%x) Report: t = %d\r\n", rep->id, (uint8_t)reportValue);
    }
  }
  else if(rep->id == ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID)
  {
    setPoint_t *payload = (setPoint_t*)rep;
    
    appSnprintf("<-Setpoints changed on Thermostat:\r\n");
    memcpy(&reportValue, &rep->value[1], sizeof(int16_t));

    appSnprintf("#cool setpoint: t = %d.%d\r\n", (int)(reportValue/THERMOSTAT_LOCAL_TEMPERATURE_SCALE),(int)(reportValue%THERMOSTAT_LOCAL_TEMPERATURE_SCALE));
    payload++;

    memcpy(&reportValue, &payload->value, sizeof(int16_t));
    appSnprintf("#heat setpoint: t = %d.%d\r\n", (int)(reportValue/THERMOSTAT_LOCAL_TEMPERATURE_SCALE),(int)(reportValue%THERMOSTAT_LOCAL_TEMPERATURE_SCALE));
  }

  (void)addressing, (void)reportLength;
}

/**************************************************************************//**
\brief Attribute Event indication handler(to indicate when attr values have
        read or written)

\param[in] addressing - pointer to addressing information;
\param[in] reportLength - data payload length;
\param[in] reportPayload - data pointer
******************************************************************************/
static void ciThermostatAttrEventInd(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event)
{
#if (APP_ENABLE_CONSOLE == 1)

  appSnprintf("<-Attr ID 0x%x event 0x%x\r\n", attributeId, event);
#else
  (void)attributeId;
  (void)event;
#endif
  (void)addressing;
}

/**************************************************************************//**
\brief Setpoint Raise/Lower command payload fillup

\param[out] payload - pointer to command structure;
\param[in] group - group id;
\param[in] scene - scene id
******************************************************************************/
static void ciFillsendSetPointRaiseLowerPayload(ZCL_SetpointRaiseLower_t *payload, int8_t setPointMode, int8_t amount)
{
  payload->mode = setPointMode;
  payload->amount = amount;
}

/**************************************************************************//**
  \brief Sends Setpoint Raise/Lower command
  \param[in] mode - address mode;
  \param[in] addr - short address of destination node;
  \param[in] ep   - destination endpoint;
  \param[in] srcEp- source endpoint;
  \param mode - set points to be adjusted
  \param amount - amount of increase/decrease to setpoint value
        (in steps of 0.1°C.)
  \return none
******************************************************************************/
void ciSendSetpointRaiseLowerCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp,
  int8_t setPointMode, int8_t amount)
{
  ZCL_Request_t *req;

  if (!(req = getFreeCommand()))
    return;

  fillCommandRequest(req, ZCL_THERMOSTAT_CLUSTER_SETPOINT_RAISE_LOWER_COMMAND_ID, sizeof(ZCL_SetpointRaiseLower_t), srcEp);
  ciFillsendSetPointRaiseLowerPayload((ZCL_SetpointRaiseLower_t *)req->requestPayload, setPointMode, amount);
  fillDstAddressing(&req->dstAddressing, mode, addr, ep, THERMOSTAT_CLUSTER_ID);
  ZCL_CommandManagerSendCommand(req);
}

#endif // APP_DEVICE_TYPE_COMBINED_INTERFACE

// eof ciThermostatCluster.c
