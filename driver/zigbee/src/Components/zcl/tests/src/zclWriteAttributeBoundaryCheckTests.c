/*******************************************************************************
  ZCL Write Attribute Boundary Check Tests Source File

  Company:
    Microchip Technology Inc.

  File Name:
    zclWriteAttributeBoundaryCheckTests.c

  Summary:
    This file contains the ZCL boundary check tests implementation.

  Description:
    This file contains the ZCL boundary check tests implementation.
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


/*******************************************************************************
                             Includes section
*******************************************************************************/
#include <stdio.h>
#include "CUnit.h"
#include "Basic.h"
#include <zclUnitTesting.h>
#include <zclParser.h>
#include <clusters.h>
#include <zclThermostatCluster.h>
#include <apsmeBind.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define ENDPOINT 0x10

/*******************************************************************************
                             Types section
*******************************************************************************/

/*******************************************************************************
                        Global variables section
*******************************************************************************/
ZCL_DeviceEndpoint_t testEndpoint;
ZCL_Cluster_t serverClusters[1];
ClusterId_t serverClusterIds[1];
ZCL_ThermostatClusterServerAttributes_t thermostatClusterServerAttributes;

/*******************************************************************************
                        Prototypes section
*******************************************************************************/
static void formZclEndpoint(void);
static void fromZclClusters(void);
static void formZclAttributes(void);

/*******************************************************************************
                             Implementation section
*******************************************************************************/

/* Test Suite Initialization/Setup */ 
int zclWriteAttributeBoundaryCheckTestsSetup(void)
{
  memset(&testEndpoint, 0, sizeof(ZCL_DeviceEndpoint_t));
  memset(&thermostatClusterServerAttributes, 0, sizeof(ZCL_ThermostatClusterServerAttributes_t));
  formZclAttributes();
  fromZclClusters();
  formZclEndpoint();

  ZCL_RegisterEndpoint(&testEndpoint);
  return 0;
}
/* Test Suite Cleanup /Tear down */
int zclWriteAttributeBoundaryCheckTestsTeardown(void)
{
  return 0;
}

void attributeValueNoRefAttributeWithinRange(void)
{
  ZCL_Status_t zclStatus;
  int16_t attrVal = -20000;
  zclStatus = ZCL_WriteAttributeValue(ENDPOINT,
                                     THERMOSTAT_CLUSTER_ID,
                                     ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
                                     ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,
                                     (uint8_t *)&attrVal);

  CU_ASSERT_EQUAL(ZCL_SUCCESS_STATUS, zclStatus);
}
void attributeValueNoRefAttributeLessThanMin(void)
{
  ZCL_Status_t zclStatus;
  int16_t attrVal = -30000;
  zclStatus = ZCL_WriteAttributeValue(ENDPOINT,
                                     THERMOSTAT_CLUSTER_ID,
                                     ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
                                     ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,
                                     (uint8_t *)&attrVal);

  CU_ASSERT_EQUAL(ZCL_INVALID_VALUE_STATUS, zclStatus);
}
void attributeValueNoRefAttributeEqualToMin(void)
{
  ZCL_Status_t zclStatus;
  int16_t attrVal = -27315;
  zclStatus = ZCL_WriteAttributeValue(ENDPOINT,
                                     THERMOSTAT_CLUSTER_ID,
                                     ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
                                     ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,
                                     (uint8_t *)&attrVal);

  CU_ASSERT_EQUAL(ZCL_SUCCESS_STATUS, zclStatus);
}
void attributeValueNoRefAttributeGreaterThanMax(void)
{
  ZCL_Status_t zclStatus;
  int16_t attrVal = 32768;
  zclStatus = ZCL_WriteAttributeValue(ENDPOINT,
                                     THERMOSTAT_CLUSTER_ID,
                                     ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
                                     ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,
                                     (uint8_t *)&attrVal);

  CU_ASSERT_EQUAL(ZCL_INVALID_VALUE_STATUS, zclStatus);
}
void attributeValueNoRefAttributeEqualToMax(void)
{
  ZCL_Status_t zclStatus;
  int16_t attrVal = 32767;
  zclStatus = ZCL_WriteAttributeValue(ENDPOINT,
                                     THERMOSTAT_CLUSTER_ID,
                                     ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
                                     ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,
                                     (uint8_t *)&attrVal);

  CU_ASSERT_EQUAL(ZCL_SUCCESS_STATUS, zclStatus);
}
void attributeValueRefAttributeWithinRange1(void)
{
  ZCL_Status_t zclStatus;
  int16_t attrVal = 10000;

  // minCoolSetpointLimit = -20000;
  // maxCoolSetpointLimit = 20000;

  zclStatus = ZCL_WriteAttributeValue(ENDPOINT,
                                     THERMOSTAT_CLUSTER_ID,
                                     ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
                                     ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,
                                     (uint8_t *)&attrVal);

  CU_ASSERT_EQUAL(ZCL_SUCCESS_STATUS, zclStatus);
}
void attributeValueRefAttributeLessThanMin1(void)
{
  ZCL_Status_t zclStatus;
  int16_t attrVal = -30001;

  // minCoolSetpointLimit = -20000;
  // maxCoolSetpointLimit = 20000;

  zclStatus = ZCL_WriteAttributeValue(ENDPOINT,
                                     THERMOSTAT_CLUSTER_ID,
                                     ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
                                     ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,
                                     (uint8_t *)&attrVal);

  CU_ASSERT_EQUAL(ZCL_INVALID_VALUE_STATUS, zclStatus);
}
void attributeValueRefAttributeEqualToMin1(void)
{
  ZCL_Status_t zclStatus;
  int16_t attrVal = -20000;

  // minCoolSetpointLimit = -20000;
  // maxCoolSetpointLimit = 20000;
  zclStatus = ZCL_WriteAttributeValue(ENDPOINT,
                                     THERMOSTAT_CLUSTER_ID,
                                     ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
                                     ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,
                                     (uint8_t *)&attrVal);

  CU_ASSERT_EQUAL(ZCL_SUCCESS_STATUS, zclStatus);
}
void attributeValueRefAttributeGreaterThanMax1(void)
{
  ZCL_Status_t zclStatus;
  int16_t attrVal = 20001;

  // minCoolSetpointLimit = -20000;
  // maxCoolSetpointLimit = 20000;

  zclStatus = ZCL_WriteAttributeValue(ENDPOINT,
                                     THERMOSTAT_CLUSTER_ID,
                                     ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
                                     ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,
                                     (uint8_t *)&attrVal);

  CU_ASSERT_EQUAL(ZCL_INVALID_VALUE_STATUS, zclStatus);
}
void attributeValueRefAttributeEqualToMax1(void)
{
  ZCL_Status_t zclStatus;
  int16_t attrVal = 20000;

  // minCoolSetpointLimit = -20000;
  // maxCoolSetpointLimit = 20000;

  zclStatus = ZCL_WriteAttributeValue(ENDPOINT,
                                     THERMOSTAT_CLUSTER_ID,
                                     ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
                                     ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,
                                     (uint8_t *)&attrVal);

  CU_ASSERT_EQUAL(ZCL_SUCCESS_STATUS, zclStatus);
}
void attributeValueRefAttributeDoesNotExist(void)
{
  ZCL_Status_t zclStatus;
  int16_t attrVal = 30000;
 
  thermostatClusterServerAttributes.minCoolSetpointLimit.value = -10000;
  thermostatClusterServerAttributes.maxCoolSetpointLimit.value = 10000;
  
  thermostatClusterServerAttributes.occupiedCoolingSetpoint.minVal = 0x1d;
  thermostatClusterServerAttributes.occupiedCoolingSetpoint.maxVal = 0x1b;

  zclStatus = ZCL_WriteAttributeValue(ENDPOINT,
                                     THERMOSTAT_CLUSTER_ID,
                                     ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
                                     ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,
                                     (uint8_t *)&attrVal);

  CU_ASSERT_EQUAL(ZCL_SUCCESS_STATUS, zclStatus);
}
void attributeValueRefAttributeWithinRange2(void)
{
  ZCL_Status_t zclStatus;
  int16_t attrVal = 5000;

  thermostatClusterServerAttributes.minCoolSetpointLimit.value = -10000;
  thermostatClusterServerAttributes.maxCoolSetpointLimit.value = 10000;

  zclStatus = ZCL_WriteAttributeValue(ENDPOINT,
                                     THERMOSTAT_CLUSTER_ID,
                                     ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
                                     ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,
                                     (uint8_t *)&attrVal);

  CU_ASSERT_EQUAL(ZCL_SUCCESS_STATUS, zclStatus);
}
void attributeValueRefAttributeLessThanMin2(void)
{
  ZCL_Status_t zclStatus;
  int16_t attrVal = -10100;

  thermostatClusterServerAttributes.minCoolSetpointLimit.value = -10000;
  thermostatClusterServerAttributes.maxCoolSetpointLimit.value = 10000;

  zclStatus = ZCL_WriteAttributeValue(ENDPOINT,
                                     THERMOSTAT_CLUSTER_ID,
                                     ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
                                     ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,
                                     (uint8_t *)&attrVal);

  CU_ASSERT_EQUAL(ZCL_INVALID_VALUE_STATUS, zclStatus);
}
void attributeValueRefAttributeEqualToMin2(void)
{
  ZCL_Status_t zclStatus;
  int16_t attrVal = -10000;

  thermostatClusterServerAttributes.minCoolSetpointLimit.value = -10000;
  thermostatClusterServerAttributes.maxCoolSetpointLimit.value = 10000;

  zclStatus = ZCL_WriteAttributeValue(ENDPOINT,
                                     THERMOSTAT_CLUSTER_ID,
                                     ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
                                     ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,
                                     (uint8_t *)&attrVal);

  CU_ASSERT_EQUAL(ZCL_SUCCESS_STATUS, zclStatus);
}
void attributeValueRefAttributeWithinRange3(void)
{
  ZCL_Status_t zclStatus;
  int16_t attrVal = 0;

  thermostatClusterServerAttributes.minCoolSetpointLimit.value = -10000;
  thermostatClusterServerAttributes.maxCoolSetpointLimit.value = 10000;

  zclStatus = ZCL_WriteAttributeValue(ENDPOINT,
                                     THERMOSTAT_CLUSTER_ID,
                                     ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
                                     ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,
                                     (uint8_t *)&attrVal);

  CU_ASSERT_EQUAL(ZCL_SUCCESS_STATUS, zclStatus);
}
void attributeValueRefAttributeEqualToMax3(void)
{
  ZCL_Status_t zclStatus;
  int16_t attrVal = 10000;

  thermostatClusterServerAttributes.minCoolSetpointLimit.value = -10000;
  thermostatClusterServerAttributes.maxCoolSetpointLimit.value = 10000;

  zclStatus = ZCL_WriteAttributeValue(ENDPOINT,
                                     THERMOSTAT_CLUSTER_ID,
                                     ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
                                     ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,
                                     (uint8_t *)&attrVal);

  CU_ASSERT_EQUAL(ZCL_SUCCESS_STATUS, zclStatus);
}
void attributeValueRefAttributeGreaterThanMax3(void)
{
  ZCL_Status_t zclStatus;
  int16_t attrVal = 10001;

  thermostatClusterServerAttributes.minCoolSetpointLimit.value = -10000;
  thermostatClusterServerAttributes.maxCoolSetpointLimit.value = 10000;

  zclStatus = ZCL_WriteAttributeValue(ENDPOINT,
                                     THERMOSTAT_CLUSTER_ID,
                                     ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
                                     ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID,
                                     ZCL_S16BIT_DATA_TYPE_ID,
                                     (uint8_t *)&attrVal);

  CU_ASSERT_EQUAL(ZCL_INVALID_VALUE_STATUS, zclStatus);
}

/*******************************************************************************
                        Static Functions section
*******************************************************************************/
static void formZclEndpoint(void)
{
  testEndpoint.simpleDescriptor.endpoint            = ENDPOINT;
  testEndpoint.simpleDescriptor.AppProfileId        = PROFILE_ID_HOME_AUTOMATION;
  testEndpoint.simpleDescriptor.AppDeviceId         = HA_THERMOSTAT_DEVICE_ID;
  testEndpoint.simpleDescriptor.AppInClustersCount  = ARRAY_SIZE(serverClusterIds);
  testEndpoint.simpleDescriptor.AppInClustersList   = serverClusterIds;
  testEndpoint.simpleDescriptor.AppOutClustersCount = 0;
  testEndpoint.simpleDescriptor.AppOutClustersList  = NULL;
  testEndpoint.serverCluster = serverClusters;
  testEndpoint.clientCluster = NULL;
}

static void fromZclClusters(void)
{
  serverClusterIds[0] = THERMOSTAT_CLUSTER_ID;

  serverClusters[0].id = THERMOSTAT_CLUSTER_ID;
  serverClusters[0].options.type = ZCL_SERVER_CLUSTER_TYPE;
  serverClusters[0].options.security = ZCL_NETWORK_KEY_CLUSTER_SECURITY;
  serverClusters[0].attributesAmount = ZCL_THERMOSTAT_CLUSTER_SERVER_ATTRIBUTES_AMOUNT;
  serverClusters[0].attributes = (uint8_t *)&thermostatClusterServerAttributes;
  serverClusters[0].commandsAmount = ZCL_THERMOSTAT_CLUSTER_COMMANDS_AMOUNT;
  serverClusters[0].commands = NULL;

}

static void formZclAttributes(void)
{
  thermostatClusterServerAttributes.localTemperature.id = ZCL_THERMOSTAT_CLUSTER_LOCAL_TEMPERATURE_SERVER_ATTRIBUTE_ID;
  thermostatClusterServerAttributes.localTemperature.type = ZCL_S16BIT_DATA_TYPE_ID;
  thermostatClusterServerAttributes.localTemperature.properties = ZCL_REPORTABLE_ATTRIBUTE | ZCL_READONLY_ATTRIBUTE | ZCL_BOUNDARY_CHECK;
  thermostatClusterServerAttributes.localTemperature.minReportInterval = 30;
  thermostatClusterServerAttributes.localTemperature.maxReportInterval = 60;
  thermostatClusterServerAttributes.localTemperature.value = 1000;
  thermostatClusterServerAttributes.localTemperature.lastReportedValue = 10;
  thermostatClusterServerAttributes.localTemperature.reportableChange = 1;
  thermostatClusterServerAttributes.localTemperature.minVal = -27315;  // 0x954D in hex
  thermostatClusterServerAttributes.localTemperature.maxVal = 32767; // 0x7FFF in hex
 
  thermostatClusterServerAttributes.occupiedCoolingSetpoint.id = ZCL_THERMOSTAT_CLUSTER_OCCUPIED_COOLING_SETPOINT_SERVER_ATTRIBUTE_ID;
  thermostatClusterServerAttributes.occupiedCoolingSetpoint.type = ZCL_S16BIT_DATA_TYPE_ID;
  thermostatClusterServerAttributes.occupiedCoolingSetpoint.properties = ZCL_READWRITE_ATTRIBUTE | ZCL_BOUNDARY_CHECK | ZCL_CHECK_OTHER_ATTR;
  thermostatClusterServerAttributes.occupiedCoolingSetpoint.value = 1000;
  thermostatClusterServerAttributes.occupiedCoolingSetpoint.minVal = ZCL_THERMOSTAT_CLUSTER_MIN_COOL_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID;
  thermostatClusterServerAttributes.occupiedCoolingSetpoint.maxVal = ZCL_THERMOSTAT_CLUSTER_MAX_COOL_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID;

  thermostatClusterServerAttributes.occupiedHeatingSetpoint.id = ZCL_THERMOSTAT_CLUSTER_OCCUPIED_HEATING_SETPOINT_SERVER_ATTRIBUTE_ID;
  thermostatClusterServerAttributes.occupiedHeatingSetpoint.type = ZCL_S16BIT_DATA_TYPE_ID;
  thermostatClusterServerAttributes.occupiedHeatingSetpoint.properties = ZCL_READWRITE_ATTRIBUTE | ZCL_BOUNDARY_CHECK | ZCL_CHECK_OTHER_ATTR;
  thermostatClusterServerAttributes.occupiedHeatingSetpoint.value = 1000;
  thermostatClusterServerAttributes.occupiedHeatingSetpoint.minVal = ZCL_THERMOSTAT_CLUSTER_MIN_HEAT_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID;
  thermostatClusterServerAttributes.occupiedHeatingSetpoint.maxVal = ZCL_THERMOSTAT_CLUSTER_MAX_HEAT_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID;

  thermostatClusterServerAttributes.minCoolSetpointLimit.id = ZCL_THERMOSTAT_CLUSTER_MIN_COOL_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID;
  thermostatClusterServerAttributes.minCoolSetpointLimit.type = ZCL_S16BIT_DATA_TYPE_ID;
  thermostatClusterServerAttributes.minCoolSetpointLimit.properties = ZCL_READWRITE_ATTRIBUTE | ZCL_BOUNDARY_CHECK;
  thermostatClusterServerAttributes.minCoolSetpointLimit.value = -20000;
  thermostatClusterServerAttributes.minCoolSetpointLimit.minVal = -27315;  // 0x954D in hex
  thermostatClusterServerAttributes.minCoolSetpointLimit.maxVal = 32767; // 0x7FFF in hex

  thermostatClusterServerAttributes.maxCoolSetpointLimit.id = ZCL_THERMOSTAT_CLUSTER_MAX_COOL_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID;
  thermostatClusterServerAttributes.maxCoolSetpointLimit.type = ZCL_S16BIT_DATA_TYPE_ID;
  thermostatClusterServerAttributes.maxCoolSetpointLimit.properties = ZCL_READWRITE_ATTRIBUTE | ZCL_BOUNDARY_CHECK;
  thermostatClusterServerAttributes.maxCoolSetpointLimit.value = 20000;
  thermostatClusterServerAttributes.maxCoolSetpointLimit.minVal = -27315;  // 0x954D in hex
  thermostatClusterServerAttributes.maxCoolSetpointLimit.maxVal = 32767; // 0x7FFF in hex

  thermostatClusterServerAttributes.minHeatSetpointLimit.id = ZCL_THERMOSTAT_CLUSTER_MIN_HEAT_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID;
  thermostatClusterServerAttributes.minHeatSetpointLimit.type = ZCL_S16BIT_DATA_TYPE_ID;
  thermostatClusterServerAttributes.minHeatSetpointLimit.properties = ZCL_READWRITE_ATTRIBUTE | ZCL_BOUNDARY_CHECK;
  thermostatClusterServerAttributes.minHeatSetpointLimit.value = 0x200;
  thermostatClusterServerAttributes.minHeatSetpointLimit.minVal = -27315;  // 0x954D in hex
  thermostatClusterServerAttributes.minHeatSetpointLimit.maxVal = 32767; // 0x7FFF in hex

  thermostatClusterServerAttributes.maxHeatSetpointLimit.id = ZCL_THERMOSTAT_CLUSTER_MAX_HEAT_SETPOINT_LIMIT_SERVER_ATTRIBUTE_ID;
  thermostatClusterServerAttributes.maxHeatSetpointLimit.type = ZCL_S16BIT_DATA_TYPE_ID;
  thermostatClusterServerAttributes.maxHeatSetpointLimit.properties = ZCL_READWRITE_ATTRIBUTE | ZCL_BOUNDARY_CHECK;
  thermostatClusterServerAttributes.maxHeatSetpointLimit.value = 0x200;
  thermostatClusterServerAttributes.maxHeatSetpointLimit.minVal = -27315;  // 0x954D in hex
  thermostatClusterServerAttributes.maxHeatSetpointLimit.maxVal = 32767; // 0x7FFF in hex

}

// eof zclWriteAttributeCheckTests.c
