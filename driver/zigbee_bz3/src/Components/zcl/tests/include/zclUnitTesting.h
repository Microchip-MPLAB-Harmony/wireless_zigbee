/*******************************************************************************
  Zigbee Cluster Library Unit Testing Cluster Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zclUnitTesting.h

  Summary:
    This file contains Interface for ZCL unit tests.

  Description:
    This file contains Interface for ZCL unit tests.
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

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ZCLUNITTESTING_H
#define _ZCLUNITTESTING_H
#ifdef UNIT_TESTING

/******************************************************************************
                    Includes section
******************************************************************************/
#include <sysTypes.h>
#include <sysTimer.h>
#include <zclMemoryManager.h>

/******************************************************************************
                    Prototypes section
******************************************************************************/
/*************************************************************************//**
\brief Starts wait response timer. Only for testing purposes.
*****************************************************************************/
void ZCL_StartWaitResponseTimer(ZclMmBufferDescriptor_t *descriptor);

/*************************************************************************//**
\brief Returns wait response timer. Only for testing purposes.
*****************************************************************************/
SYS_Timer_t* ZCL_GetWaitTimer(void);

/*************************************************************************//**
\brief Returns report timer. Only for testing purposes.
*****************************************************************************/
SYS_Timer_t* ZCL_GetReportTimer(void);

/*************************************************************************//**
\brief Calls wait response timer callback. Only for testing purposes.
*****************************************************************************/
void ZCL_WaitTimerFired(void);

/*************************************************************************//**
\brief Releases all memory buffers. Only for testing purposes.
*****************************************************************************/
void ZCL_ReleaseAllMemBuffers(void);

/*************************************************************************//**
\brief Calls report response timer callback. Only for testing purposes.
*****************************************************************************/
void ZCL_ReportTimerFired(void);

/*************************************************************************//**
\brief Setup/Init Suite Routine
*****************************************************************************/
int zclReportingTestsSetup(void);
int zclWaitTimerTestSetup(void);
int zclWriteAttributeBoundaryCheckTestsSetup(void);

/*************************************************************************//**
\brief TearDown/Clean Suite Routine
*****************************************************************************/
int zclReportingTestsTeardown(void);
int zclWaitTimerTestTeardown(void);
int zclWriteAttributeBoundaryCheckTestsTeardown(void);

/*************************************************************************//**
\brief TestCases Prototypes
*****************************************************************************/
/* ZCL Reporting */
void attributeBecomesReportableOnConfigure_ifMaxReportTimeIsNot0xFFFF(void);
void attributeDoesNotBecomesReportableOnConfigure_ifMaxReportTimeIs0xFFFF(void);
void attributeDoesNotBecomesReportableOnConfigure_ifNonZeroMaxReportTimeIsLessThanMinReportTime(void);
void attributeDoesNotBecomesReportableOnConfigure_ifDirectionIsFromServer(void);
void reportTimerIsStartedForMaxTimeOnConfigure_IfmaxTimeIsNot0xFFFF(void);
void reportTimerIsNotStartedForMaxTimeOnConfigure_IfmaxTimeIs0xFFFF(void);
void restartReportingOfTheSameAttributeAtOneMomentOfTime(void);
void restartReportingOfTheSameAttributeAtDifferentMomentsOfTime(void);
void twoAttributesConfiguredOneByOne_minTimeoutIsChosen_theSecondTimeoutIsBiggerSimultaneously(void);
void twoAttributesConfiguredOneByOne_minTimeoutIsChosen_theSecondTimeoutIsBiggerDifferentTime(void);
void twoAttributesConfiguredOneByOne_minTimeoutIsChosen_theSecondTimeoutIsSmallerSimultaneously(void);
void twoAttributesConfiguredOneByOne_minTimeoutIsChosen_theSecondTimeoutIsSmallerDifferentTime(void);
void oneAttributeReporting_reportTimerFired(void);
void twoAttributeReporting_reportTimerFiredForOneOfThem(void);
void twoAttributeReporting_timerFiresSeveralTimes(void);
void zclReportOnChangeIfNeeded_processesNullPointerCorrectly(void);
void zclReportOnChangeIfNeeded_processesNotNullPointerCorrectly(void);
void startReporting_noBindEntry_noReporting_attrPropertiesAreNotUpdated(void);
void startReporting_bindEntryExisting_reportingStarts_attrPropertiesAreUpdated(void);
void zclReportOnChangeIfNeeded_noReportIsIssued_sinceReportingIsOff(void);
void zclReportOnChangeIfNeeded_timerIsNotUpdated_sinceAttrValueIsNotChanged(void);
void zclReportOnChangeIfNeeded_reportIsIssued_sinceAttrValueWasChangedBeforeMinInterval(void);
void zclReportOnChangeIfNeeded_reportIsIssued_sinceAttrValueWasChangedBeforeMinInterval_someTimePassed(void);
void zclReportOnChangeIfNeeded_reportIsIssued_sinceAttrValueWasChangedAfterMinInterval(void);
void zclReportOnChangeIfNeeded_reportOnChangeThenByTimeout(void);
void zclReportOnChangeIfNeeded_causedByAttributeWriting(void);
void zclReportOnChangeIfNeeded_ReportChangeHappendsMoreThanOnceInMinTime(void);
void zclReportOnChangeIfNeeded_MinIntervalChangingWhereItisAlreadyRunning(void);
void zclReportTimerFired_MinAndMaxValueBecomesZeroMaxIntervalIgnored(void);
/* ZCL WaitTimer */
void defaultWaitTimerStateAfterZclReset(void);
void setTimerOnce(void);
void twoRequests_atTheSameMomentOfTime(void);
void twoRequests_differentTime_secondIsLater(void);
void twoRequests_differentTime_secondIsEarlier(void);
void twoRequests_differentTime_firstAlreadyExpired(void);
void twoRequests_differentTime_firstAlreadyExpired2(void);
void oneRequest_timerExpired(void);
void twoRequests_secondIsLater_timerExpired(void);
void twoRequests_secondIsEarlier_timerExpired(void);
/*ZCL write attribute testing */
void attributeValueNoRefAttributeWithinRange(void);
void attributeValueNoRefAttributeLessThanMin(void);
void attributeValueNoRefAttributeEqualToMin(void);
void attributeValueNoRefAttributeGreaterThanMax(void);
void attributeValueNoRefAttributeEqualToMax(void);
void attributeValueRefAttributeWithinRange1(void);
void attributeValueRefAttributeLessThanMin1(void);
void attributeValueRefAttributeEqualToMin1(void);
void attributeValueRefAttributeGreaterThanMax1(void);
void attributeValueRefAttributeEqualToMax1(void);
void attributeValueRefAttributeDoesNotExist(void);
void attributeValueRefAttributeWithinRange2(void);
void attributeValueRefAttributeLessThanMin2(void);
void attributeValueRefAttributeEqualToMin2(void);
void attributeValueRefAttributeWithinRange3(void);
void attributeValueRefAttributeEqualToMax3(void);
void attributeValueRefAttributeGreaterThanMax3(void);
#endif // UNIT_TESTING
#endif // _ZCLUNITTESTING_H
#ifdef __cplusplus
}
#endif
// eof zclUnitTesting.h
