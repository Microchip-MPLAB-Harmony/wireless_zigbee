/*******************************************************************************
  ZCL Reporting tests Source File

  Company:
    Microchip Technology Inc.

  File Name:
    zclReportingTests.c

  Summary:
    This file contains the ZCL Reporting tests 

  Description:
    This file contains the ZCL Reporting tests.
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
#include <zclLevelControlCluster.h>
#include <zclOnOffCluster.h>
#include <apsmeBind.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
#define ENDPOINT 0x10

/*******************************************************************************
                             Types section
*******************************************************************************/
typedef struct PACK
{
  ZclFrameControlField_t  frameControl;
  uint8_t                 sequenceNumber;
  uint8_t                 commandId;
} ZclFrameHeaderNoManufCode_t;

/*******************************************************************************
                        Global variables section
*******************************************************************************/
ZCL_DeviceEndpoint_t testEndpoint;
ZCL_Cluster_t serverClusters[2];
ClusterId_t serverClusterIds[2];
ZCL_LevelControlClusterServerAttributes_t levelControlClusterServerAttributes;
ZCL_OnOffClusterServerAttributes_t onOffClusterServerAttributes;
APS_DataInd_t apsDataInd;
ZclFrameDescriptor_t frameDescriptor;
ZCL_ConfigureReportingReq_t req;
ZclFrameHeaderNoManufCode_t header;
uint8_t buffer[sizeof(ZclFrameHeaderNoManufCode_t) + sizeof(ZCL_ConfigureReportingReq_t)];
APS_BindReq_t bindReq;

/*******************************************************************************
                        Prototypes section
*******************************************************************************/
static void formZclEndpoint(void);
static void fromZclClusters(void);
static void formZclAttributes(void);
static void formConfigureReportingRequest(ClusterId_t cluster, ZCL_AttributeId_t attr, uint8_t type, uint16_t max, uint8_t dir);
static void formBindRequest(void);
static void formLevelControlConfigureReportingRequest(uint16_t max, uint8_t dir);
static void formOnOffConfigureReportingRequest(uint16_t max);
/*******************************************************************************
                             Implementation section
*******************************************************************************/

/* Test Suite Initialization/Setup */ 
int zclReportingTestsSetup(void)
{
  memset(&testEndpoint, 0, sizeof(ZCL_DeviceEndpoint_t));
  memset(&levelControlClusterServerAttributes, 0, sizeof(ZCL_OnOffClusterServerAttributes_t));
  memset(&onOffClusterServerAttributes, 0, sizeof(ZCL_OnOffClusterServerAttributes_t));
  memset(&frameDescriptor, 0, sizeof(ZclFrameDescriptor_t));
  memset(&req, 0, sizeof(ZCL_ConfigureReportingReq_t));
  memset(&header, 0, sizeof(ZclFrameHeaderNoManufCode_t));
  memset(&bindReq, 0, sizeof(APS_BindReq_t));
  formZclAttributes();
  fromZclClusters();
  formZclEndpoint();
  formBindRequest();

  ZCL_RegisterEndpoint(&testEndpoint);
  halSetTimeOfAppTimer(0);
  return 0;
}
/* Test Suite Cleanup /Tear down */
int zclReportingTestsTeardown(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();
  memset(timer, 0, sizeof(SYS_Timer_t));
  ZCL_ReleaseAllMemBuffers();
  APS_UnbindReq(&bindReq);
  return 0;
}

void attributeBecomesReportableOnConfigure_ifMaxReportTimeIsNot0xFFFF(void)
{
  formLevelControlConfigureReportingRequest(20, ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  CU_ASSERT_TRUE(levelControlClusterServerAttributes.currentLevel.properties & ZCL_REPORTING_CONFIGURED);
}

void attributeDoesNotBecomesReportableOnConfigure_ifMaxReportTimeIs0xFFFF(void)
{
  formLevelControlConfigureReportingRequest(0xFFFF, ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  CU_ASSERT_FALSE(levelControlClusterServerAttributes.currentLevel.properties & ZCL_REPORTING_CONFIGURED);
}

void attributeDoesNotBecomesReportableOnConfigure_ifNonZeroMaxReportTimeIsLessThanMinReportTime(void)
{
  formLevelControlConfigureReportingRequest(5, ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  CU_ASSERT_FALSE(levelControlClusterServerAttributes.currentLevel.properties & ZCL_REPORTING_CONFIGURED);
}

void attributeDoesNotBecomesReportableOnConfigure_ifDirectionIsFromServer(void)
{
  formLevelControlConfigureReportingRequest(20, ZCL_FRAME_CONTROL_DIRECTION_SERVER_TO_CLIENT);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  CU_ASSERT_FALSE(levelControlClusterServerAttributes.currentLevel.properties & ZCL_REPORTING_CONFIGURED);
}

void reportTimerIsStartedForMaxTimeOnConfigure_IfmaxTimeIsNot0xFFFF(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();

  formLevelControlConfigureReportingRequest(20, ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  CU_ASSERT_EQUAL(20000, timer->timer.interval);
  CU_ASSERT_EQUAL(SYS_TIMER_STARTED, timer->state);
}

void reportTimerIsNotStartedForMaxTimeOnConfigure_IfmaxTimeIs0xFFFF(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();

  formLevelControlConfigureReportingRequest(0xFFFF, ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  CU_ASSERT_EQUAL(0, timer->timer.interval);
  CU_ASSERT_EQUAL(SYS_TIMER_STOPPED, timer->state);
}

void restartReportingOfTheSameAttributeAtOneMomentOfTime(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();

  formLevelControlConfigureReportingRequest(20, ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  formLevelControlConfigureReportingRequest(30, ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  CU_ASSERT_EQUAL(30000, timer->timer.interval);
  CU_ASSERT_EQUAL(SYS_TIMER_STARTED, timer->state);
}

void restartReportingOfTheSameAttributeAtDifferentMomentsOfTime(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();

  formLevelControlConfigureReportingRequest(20, ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  halSetTimeOfAppTimer(1000);
  formLevelControlConfigureReportingRequest(30, ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  CU_ASSERT_EQUAL(29000, timer->timer.interval);
  CU_ASSERT_EQUAL(SYS_TIMER_STARTED, timer->state);
}

void twoAttributesConfiguredOneByOne_minTimeoutIsChosen_theSecondTimeoutIsBiggerSimultaneously(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();

  formLevelControlConfigureReportingRequest(20, ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  formOnOffConfigureReportingRequest(30);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  CU_ASSERT_EQUAL(20000, timer->timer.interval);
  CU_ASSERT_EQUAL(0, levelControlClusterServerAttributes.currentLevel.reportCounter);
  CU_ASSERT_EQUAL(0, onOffClusterServerAttributes.onOff.reportCounter);
}

void twoAttributesConfiguredOneByOne_minTimeoutIsChosen_theSecondTimeoutIsBiggerDifferentTime(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();

  formLevelControlConfigureReportingRequest(20, ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  halSetTimeOfAppTimer(2000);
  formOnOffConfigureReportingRequest(30);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  CU_ASSERT_EQUAL(18000, timer->timer.interval);
  CU_ASSERT_EQUAL(2, levelControlClusterServerAttributes.currentLevel.reportCounter);
  CU_ASSERT_EQUAL(2, onOffClusterServerAttributes.onOff.reportCounter);
}

void twoAttributesConfiguredOneByOne_minTimeoutIsChosen_theSecondTimeoutIsSmallerSimultaneously(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();

  formLevelControlConfigureReportingRequest(20, ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  formOnOffConfigureReportingRequest(10);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  CU_ASSERT_EQUAL(10000, timer->timer.interval);
  CU_ASSERT_EQUAL(0, levelControlClusterServerAttributes.currentLevel.reportCounter);
  CU_ASSERT_EQUAL(0, onOffClusterServerAttributes.onOff.reportCounter);
}

void twoAttributesConfiguredOneByOne_minTimeoutIsChosen_theSecondTimeoutIsSmallerDifferentTime(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();

  formLevelControlConfigureReportingRequest(20, ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  halSetTimeOfAppTimer(2000);
  formOnOffConfigureReportingRequest(10);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  CU_ASSERT_EQUAL(8000, timer->timer.interval);
  CU_ASSERT_EQUAL(2, levelControlClusterServerAttributes.currentLevel.reportCounter);
  CU_ASSERT_EQUAL(2, onOffClusterServerAttributes.onOff.reportCounter);
}

void oneAttributeReporting_reportTimerFired(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();

  formLevelControlConfigureReportingRequest(20, ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  halSetTimeOfAppTimer(20000);
  ZCL_ReportTimerFired();
  CU_ASSERT_EQUAL(20000, timer->timer.interval);
  CU_ASSERT_EQUAL(0, levelControlClusterServerAttributes.currentLevel.reportCounter);
}

void twoAttributeReporting_reportTimerFiredForOneOfThem(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();

  formLevelControlConfigureReportingRequest(20, ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  formOnOffConfigureReportingRequest(12);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  halSetTimeOfAppTimer(12000);
  ZCL_ReportTimerFired();
  CU_ASSERT_EQUAL(8000, timer->timer.interval);
  CU_ASSERT_EQUAL(12, levelControlClusterServerAttributes.currentLevel.reportCounter);
  CU_ASSERT_EQUAL(0, onOffClusterServerAttributes.onOff.reportCounter);
}

void twoAttributeReporting_timerFiresSeveralTimes(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();

  formLevelControlConfigureReportingRequest(20, ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  formOnOffConfigureReportingRequest(12);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);

  halSetTimeOfAppTimer(12000);
  ZCL_ReportTimerFired();
  CU_ASSERT_EQUAL(8000, timer->timer.interval);
  CU_ASSERT_EQUAL(12, levelControlClusterServerAttributes.currentLevel.reportCounter);
  CU_ASSERT_EQUAL(0, onOffClusterServerAttributes.onOff.reportCounter);

  halSetTimeOfAppTimer(20000);
  ZCL_ReportTimerFired();
  CU_ASSERT_EQUAL(4000, timer->timer.interval);
  CU_ASSERT_EQUAL(0, levelControlClusterServerAttributes.currentLevel.reportCounter);
  CU_ASSERT_EQUAL(8, onOffClusterServerAttributes.onOff.reportCounter);

  halSetTimeOfAppTimer(24000);
  ZCL_ReportTimerFired();
  CU_ASSERT_EQUAL(12000, timer->timer.interval);
  CU_ASSERT_EQUAL(4, levelControlClusterServerAttributes.currentLevel.reportCounter);
  CU_ASSERT_EQUAL(0, onOffClusterServerAttributes.onOff.reportCounter);


  halSetTimeOfAppTimer(26000);
  ZCL_ReportTimerFired();
  CU_ASSERT_EQUAL(4000, timer->timer.interval);
  CU_ASSERT_EQUAL(16, levelControlClusterServerAttributes.currentLevel.reportCounter);
  CU_ASSERT_EQUAL(0, onOffClusterServerAttributes.onOff.reportCounter);
}

void zclReportOnChangeIfNeeded_processesNullPointerCorrectly(void)
{
  CU_ASSERT_EQUAL(ZCL_UNSUPPORTED_ATTRIBUTE_STATUS, ZCL_ReportOnChangeIfNeeded(NULL));
}

void zclReportOnChangeIfNeeded_processesNotNullPointerCorrectly(void)
{
  CU_ASSERT_EQUAL(ZCL_SUCCESS_STATUS, ZCL_ReportOnChangeIfNeeded(&levelControlClusterServerAttributes.currentLevel));
}

void startReporting_noBindEntry_noReporting_attrPropertiesAreNotUpdated(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();

  ZCL_StartReporting();
  CU_ASSERT_EQUAL(SYS_TIMER_STOPPED, timer->state);
  CU_ASSERT_FALSE(levelControlClusterServerAttributes.currentLevel.properties & ZCL_REPORTING_CONFIGURED);
}

void startReporting_bindEntryExisting_reportingStarts_attrPropertiesAreUpdated(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();

  APS_BindReq(&bindReq);

  ZCL_StartReporting();
  CU_ASSERT_EQUAL(SYS_TIMER_STARTED, timer->state);
  CU_ASSERT_EQUAL(60000, timer->timer.interval);
  CU_ASSERT_TRUE(levelControlClusterServerAttributes.currentLevel.properties & ZCL_REPORTING_CONFIGURED);
}

void zclReportOnChangeIfNeeded_noReportIsIssued_sinceReportingIsOff(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();

  ZCL_ReportOnChangeIfNeeded(&levelControlClusterServerAttributes.currentLevel);
  CU_ASSERT_EQUAL(SYS_TIMER_STOPPED, timer->state);
}

void zclReportOnChangeIfNeeded_timerIsNotUpdated_sinceAttrValueIsNotChanged(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();

  APS_BindReq(&bindReq);

  ZCL_StartReporting();
  CU_ASSERT_EQUAL(SYS_TIMER_STARTED, timer->state);
  CU_ASSERT_EQUAL(60000, timer->timer.interval);

  ZCL_ReportOnChangeIfNeeded(&levelControlClusterServerAttributes.currentLevel);
  CU_ASSERT_EQUAL(SYS_TIMER_STARTED, timer->state);
  CU_ASSERT_EQUAL(60000, timer->timer.interval);
}

void zclReportOnChangeIfNeeded_reportIsIssued_sinceAttrValueWasChangedBeforeMinInterval(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();

  APS_BindReq(&bindReq);

  ZCL_StartReporting();
  CU_ASSERT_EQUAL(SYS_TIMER_STARTED, timer->state);
  CU_ASSERT_EQUAL(60000, timer->timer.interval);
  levelControlClusterServerAttributes.currentLevel.value = 15;
  ZCL_ReportOnChangeIfNeeded(&levelControlClusterServerAttributes.currentLevel);
  CU_ASSERT_EQUAL(SYS_TIMER_STARTED, timer->state);
  CU_ASSERT_EQUAL(30000, timer->timer.interval);
}

void zclReportOnChangeIfNeeded_reportIsIssued_sinceAttrValueWasChangedBeforeMinInterval_someTimePassed(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();

  levelControlClusterServerAttributes.currentLevel.properties &= ~ZCL_ON_CHANGE_REPORT;
  APS_BindReq(&bindReq);

  ZCL_StartReporting();
  CU_ASSERT_EQUAL(SYS_TIMER_STARTED, timer->state);
  CU_ASSERT_EQUAL(60000, timer->timer.interval);

  levelControlClusterServerAttributes.currentLevel.value = 15;
  halSetTimeOfAppTimer(5000);
  ZCL_ReportOnChangeIfNeeded(&levelControlClusterServerAttributes.currentLevel);
  CU_ASSERT_EQUAL(SYS_TIMER_STARTED, timer->state);
  CU_ASSERT_EQUAL(25000, timer->timer.interval);
}

void zclReportOnChangeIfNeeded_reportIsIssued_sinceAttrValueWasChangedAfterMinInterval(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();
  levelControlClusterServerAttributes.currentLevel.properties &= ~ZCL_ON_CHANGE_REPORT;

  APS_BindReq(&bindReq);

  ZCL_StartReporting();
  CU_ASSERT_EQUAL(SYS_TIMER_STARTED, timer->state);
  CU_ASSERT_EQUAL(60000, timer->timer.interval);

  levelControlClusterServerAttributes.currentLevel.value = 15;
  halSetTimeOfAppTimer(35000);
  ZCL_ReportOnChangeIfNeeded(&levelControlClusterServerAttributes.currentLevel);
  CU_ASSERT_EQUAL(SYS_TIMER_STARTED, timer->state);
  CU_ASSERT_EQUAL(0, timer->timer.interval);
}

void zclReportOnChangeIfNeeded_reportOnChangeThenByTimeout(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();

  APS_BindReq(&bindReq);

  ZCL_StartReporting();
  levelControlClusterServerAttributes.currentLevel.value = 15;
  ZCL_ReportOnChangeIfNeeded(&levelControlClusterServerAttributes.currentLevel);
  halSetTimeOfAppTimer(30000);
  ZCL_ReportTimerFired();
  CU_ASSERT_EQUAL(60000, timer->timer.interval);
}

void zclReportOnChangeIfNeeded_causedByAttributeWriting(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();
  uint8_t attrValue = 45;

  APS_BindReq(&bindReq);

  ZCL_StartReporting();
  ZCL_WriteAttributeValue(ENDPOINT, LEVEL_CONTROL_CLUSTER_ID,
    ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
    ZCL_LEVEL_CONTROL_CLUSTER_CURRENT_LEVEL_ATTRIBUTE_ID, ZCL_U8BIT_DATA_TYPE_ID,
    &attrValue);
  CU_ASSERT_EQUAL(30000, timer->timer.interval);
}

void zclReportOnChangeIfNeeded_ReportChangeHappendsMoreThanOnceInMinTime(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();
  uint8_t attrValue = 45;

  APS_BindReq(&bindReq);

  ZCL_StartReporting();
  ZCL_WriteAttributeValue(ENDPOINT, LEVEL_CONTROL_CLUSTER_ID,
    ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
    ZCL_LEVEL_CONTROL_CLUSTER_CURRENT_LEVEL_ATTRIBUTE_ID, ZCL_U8BIT_DATA_TYPE_ID,
    &attrValue);
  CU_ASSERT_EQUAL(SYS_TIMER_STARTED, timer->state);
  CU_ASSERT_EQUAL(30000, timer->timer.interval);
  CU_ASSERT_EQUAL(0, levelControlClusterServerAttributes.currentLevel.reportCounter);

  attrValue = 50;
  ZCL_WriteAttributeValue(ENDPOINT, LEVEL_CONTROL_CLUSTER_ID,
    ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
    ZCL_LEVEL_CONTROL_CLUSTER_CURRENT_LEVEL_ATTRIBUTE_ID, ZCL_U8BIT_DATA_TYPE_ID,
    &attrValue);
  CU_ASSERT_EQUAL(30000, timer->timer.interval);
  CU_ASSERT_EQUAL(0, levelControlClusterServerAttributes.currentLevel.reportCounter);

  attrValue = 55;
  ZCL_WriteAttributeValue(ENDPOINT, LEVEL_CONTROL_CLUSTER_ID,
    ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
    ZCL_LEVEL_CONTROL_CLUSTER_CURRENT_LEVEL_ATTRIBUTE_ID, ZCL_U8BIT_DATA_TYPE_ID,
    &attrValue);
  CU_ASSERT_EQUAL(30000, timer->timer.interval);
  CU_ASSERT_EQUAL(0, levelControlClusterServerAttributes.currentLevel.reportCounter);

}

void zclReportOnChangeIfNeeded_MinIntervalChangingWhereItisAlreadyRunning(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();
  uint8_t attrValue = 45;

  APS_BindReq(&bindReq);

  ZCL_StartReporting();
  ZCL_WriteAttributeValue(ENDPOINT, LEVEL_CONTROL_CLUSTER_ID,
    ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER,
    ZCL_LEVEL_CONTROL_CLUSTER_CURRENT_LEVEL_ATTRIBUTE_ID, ZCL_U8BIT_DATA_TYPE_ID,
    &attrValue);
  CU_ASSERT_EQUAL(SYS_TIMER_STARTED, timer->state);
  CU_ASSERT_EQUAL(30000, timer->timer.interval);
  CU_ASSERT_EQUAL(0, levelControlClusterServerAttributes.currentLevel.reportCounter);

  halSetTimeOfAppTimer(8000);
  // we are sending min. value as 10
  formLevelControlConfigureReportingRequest(60, ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  CU_ASSERT_EQUAL(2000, timer->timer.interval);

}

void zclReportTimerFired_MinAndMaxValueBecomesZeroMaxIntervalIgnored(void)
{
  SYS_Timer_t *timer = ZCL_GetReportTimer();

  formOnOffConfigureReportingRequest(40);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  CU_ASSERT_EQUAL(40000, timer->timer.interval);
  formLevelControlConfigureReportingRequest(50, ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  CU_ASSERT_EQUAL(40000, timer->timer.interval);


  formLevelControlConfigureReportingRequest(0, ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER);
  zclConfigureReportingHandler(&apsDataInd, &frameDescriptor);
  levelControlClusterServerAttributes.currentLevel.minReportInterval = 0;
  levelControlClusterServerAttributes.currentLevel.maxReportInterval = 0;

  halSetTimeOfAppTimer(40000);
  ZCL_ReportTimerFired();
  CU_ASSERT_EQUAL(40000, timer->timer.interval);
  CU_ASSERT_EQUAL(40, levelControlClusterServerAttributes.currentLevel.reportCounter);
  CU_ASSERT_EQUAL(0, onOffClusterServerAttributes.onOff.reportCounter);

}
/*******************************************************************************
                        Static Functions section
*******************************************************************************/
static void formZclEndpoint(void)
{
  testEndpoint.simpleDescriptor.endpoint            = ENDPOINT;
  testEndpoint.simpleDescriptor.AppProfileId        = PROFILE_ID_HOME_AUTOMATION;
  testEndpoint.simpleDescriptor.AppDeviceId         = HA_DIMMABLE_LIGHT_DEVICE_ID;
  testEndpoint.simpleDescriptor.AppInClustersCount  = ARRAY_SIZE(serverClusterIds);
  testEndpoint.simpleDescriptor.AppInClustersList   = serverClusterIds;
  testEndpoint.simpleDescriptor.AppOutClustersCount = 0;
  testEndpoint.simpleDescriptor.AppOutClustersList  = NULL;
  testEndpoint.serverCluster = serverClusters;
  testEndpoint.clientCluster = NULL;
}

static void fromZclClusters(void)
{
  serverClusterIds[0] = LEVEL_CONTROL_CLUSTER_ID;
  serverClusterIds[1] = ONOFF_CLUSTER_ID;

  serverClusters[0].id = LEVEL_CONTROL_CLUSTER_ID;
  serverClusters[0].options.type = ZCL_SERVER_CLUSTER_TYPE;
  serverClusters[0].options.security = ZCL_NETWORK_KEY_CLUSTER_SECURITY;
  serverClusters[0].attributesAmount = ZCL_LEVEL_CONTROL_CLUSTER_SERVER_ATTRIBUTES_AMOUNT;
  serverClusters[0].attributes = (uint8_t *)&levelControlClusterServerAttributes;
  serverClusters[0].commandsAmount = ZCL_LEVEL_CONTROL_CLUSTER_COMMANDS_AMOUNT;
  serverClusters[0].commands = NULL;

  serverClusters[1].id = ONOFF_CLUSTER_ID;
  serverClusters[1].options.type = ZCL_SERVER_CLUSTER_TYPE;
  serverClusters[1].options.security = ZCL_NETWORK_KEY_CLUSTER_SECURITY;
  serverClusters[1].attributesAmount = ZCL_ONOFF_CLUSTER_SERVER_ATTRIBUTES_AMOUNT;
  serverClusters[1].attributes = (uint8_t *)&onOffClusterServerAttributes;
  serverClusters[1].commandsAmount = ZCL_ONOFF_CLUSTER_COMMANDS_AMOUNT;
  serverClusters[1].commands = NULL;
}

static void formZclAttributes(void)
{
  levelControlClusterServerAttributes.currentLevel.id = ZCL_LEVEL_CONTROL_CLUSTER_CURRENT_LEVEL_ATTRIBUTE_ID;
  levelControlClusterServerAttributes.currentLevel.type = ZCL_U8BIT_DATA_TYPE_ID;
  levelControlClusterServerAttributes.currentLevel.properties = ZCL_REPORTABLE_ATTRIBUTE | ZCL_READONLY_ATTRIBUTE;
  levelControlClusterServerAttributes.currentLevel.minReportInterval = 30;
  levelControlClusterServerAttributes.currentLevel.maxReportInterval = 60;
  levelControlClusterServerAttributes.currentLevel.value = 10;
  levelControlClusterServerAttributes.currentLevel.lastReportedValue = 10;
  levelControlClusterServerAttributes.currentLevel.reportableChange = 1;

  onOffClusterServerAttributes.onOff.id = ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID;
  onOffClusterServerAttributes.onOff.type = ZCL_BOOLEAN_DATA_TYPE_ID;
  onOffClusterServerAttributes.onOff.properties = ZCL_REPORTABLE_ATTRIBUTE | ZCL_READONLY_ATTRIBUTE;
  onOffClusterServerAttributes.onOff.minReportInterval = 12;
  onOffClusterServerAttributes.onOff.maxReportInterval = 24;
}

static void formConfigureReportingRequest(ClusterId_t cluster, ZCL_AttributeId_t attr, uint8_t type, uint16_t max, uint8_t dir)
{
  header.frameControl.defaultResponse = 1;
  header.sequenceNumber = 1;
  header.commandId      = ZCL_CONFIGURE_REPORTING_COMMAND_ID;

  req.direction            = dir;
  req.attributeId          = attr;
  req.attributeType        = type;
  req.minReportingInterval = 10;
  req.maxReportingInterval = max;
  req.reportableChange[0]  = 1;

  memcpy(buffer, &header, sizeof(ZclFrameHeaderNoManufCode_t));
  memcpy(buffer + 3, &req, sizeof(ZCL_ConfigureReportingReq_t));

  apsDataInd.dstEndpoint = ENDPOINT;
  apsDataInd.profileId   = PROFILE_ID_HOME_AUTOMATION;
  apsDataInd.clusterId   = cluster;
  apsDataInd.asduLength  = 3 + sizeof(ZCL_ConfigureReportingReq_t);
  apsDataInd.asdu        = buffer;

  // look at parseZclHeader (zclParser.c)
  frameDescriptor.headerLength         = 3;
  frameDescriptor.payloadLength        = apsDataInd.asduLength - 3;
  frameDescriptor.frameType            = 0;
  frameDescriptor.direction            = 0;
  frameDescriptor.defaultResponse      = 1;
  frameDescriptor.manufacturerSpecific = 0;
  frameDescriptor.manufacturerCode     = 0;
  frameDescriptor.sequenceNumber       = 1;
  frameDescriptor.commandId            = 6;
  frameDescriptor.header               = apsDataInd.asdu;
  frameDescriptor.payload              = apsDataInd.asdu + 3;
}

static void formBindRequest(void)
{
  bindReq.srcAddr = 1;
  bindReq.srcEndpoint = ENDPOINT;
  bindReq.clusterId = LEVEL_CONTROL_CLUSTER_ID;
  bindReq.dstAddrMode = APS_EXT_ADDRESS;
  bindReq.dst.unicast.extAddr = 2;
  bindReq.dst.unicast.endpoint = ENDPOINT;
  bindReq.confirm.status = ACTIVE_BINDING_ENTRY_STATUS;
}

static void formLevelControlConfigureReportingRequest(uint16_t max, uint8_t dir)
{
  formConfigureReportingRequest(LEVEL_CONTROL_CLUSTER_ID, ZCL_LEVEL_CONTROL_CLUSTER_CURRENT_LEVEL_ATTRIBUTE_ID,
   ZCL_U8BIT_DATA_TYPE_ID, max, dir);
}

static void formOnOffConfigureReportingRequest(uint16_t max)
{
  formConfigureReportingRequest(ONOFF_CLUSTER_ID, ZCL_ONOFF_CLUSTER_ONOFF_SERVER_ATTRIBUTE_ID,
    ZCL_BOOLEAN_DATA_TYPE_ID, max, ZCL_FRAME_CONTROL_DIRECTION_CLIENT_TO_SERVER);
}

// eof zclWaitTimerTests.c
