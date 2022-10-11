/*******************************************************************************
  All tests Source File

  Company:
    Microchip Technology Inc.

  File Name:
    allTests.c

  Summary:
    This file contains main function implementation.

  Description:
    This file contains main function implementation.
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
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include <zclUnitTesting.h>
/*******************************************************************************
                             Global variables section
*******************************************************************************/
/* This is needed for Cunit Lib linking. Do not remove this*/
int print_copywrite = 1;
/*******************************************************************************
                             Implementation section
*******************************************************************************/
int main ( void )
{
  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if ( CUE_SUCCESS != CU_initialize_registry() )
    return CU_get_error();

  /* Add Zcl Wait Timer suite to the registry */
  pSuite = CU_add_suite( "zclWaitTimer_test_suite", zclWaitTimerTestSetup, zclWaitTimerTestTeardown );
  if ( NULL == pSuite ) {
      CU_cleanup_registry();
      return CU_get_error();
   }

  /* Add the tests to the suite */
  if ( (NULL == CU_add_test(pSuite, "Zcl_WaitTimer_1", defaultWaitTimerStateAfterZclReset)) ||
       (NULL == CU_add_test(pSuite, "Zcl_WaitTimer_2", setTimerOnce)) ||
       (NULL == CU_add_test(pSuite, "Zcl_WaitTimer_3", twoRequests_atTheSameMomentOfTime)) ||
       (NULL == CU_add_test(pSuite, "Zcl_WaitTimer_4", twoRequests_differentTime_secondIsLater)) ||
       (NULL == CU_add_test(pSuite, "Zcl_WaitTimer_5", twoRequests_differentTime_secondIsEarlier)) ||
       (NULL == CU_add_test(pSuite, "Zcl_WaitTimer_6", twoRequests_differentTime_firstAlreadyExpired)) ||
       (NULL == CU_add_test(pSuite, "Zcl_WaitTimer_7", twoRequests_differentTime_firstAlreadyExpired2)) ||
       (NULL == CU_add_test(pSuite, "Zcl_WaitTimer_8", oneRequest_timerExpired)) ||
       (NULL == CU_add_test(pSuite, "Zcl_WaitTimer_9", twoRequests_secondIsLater_timerExpired)) ||
       (NULL == CU_add_test(pSuite, "Zcl_WaitTimer_10", twoRequests_secondIsEarlier_timerExpired))
      )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

  /* add ZclReporting suite to the registry */
  pSuite = CU_add_suite( "zclReporting_test_suite", zclReportingTestsSetup, zclReportingTestsTeardown );
  if ( NULL == pSuite ) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the Zcl Reporting tests to the suite */
  if ((NULL == CU_add_test(pSuite, "Zcl_Reporting_1", attributeBecomesReportableOnConfigure_ifMaxReportTimeIsNot0xFFFF)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_2", attributeDoesNotBecomesReportableOnConfigure_ifMaxReportTimeIs0xFFFF)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_3", attributeDoesNotBecomesReportableOnConfigure_ifDirectionIsFromServer)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_4", reportTimerIsStartedForMaxTimeOnConfigure_IfmaxTimeIsNot0xFFFF)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_5", reportTimerIsNotStartedForMaxTimeOnConfigure_IfmaxTimeIs0xFFFF)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_6", restartReportingOfTheSameAttributeAtOneMomentOfTime)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_7", restartReportingOfTheSameAttributeAtDifferentMomentsOfTime)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_8", twoAttributesConfiguredOneByOne_minTimeoutIsChosen_theSecondTimeoutIsBiggerSimultaneously)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_9", twoAttributesConfiguredOneByOne_minTimeoutIsChosen_theSecondTimeoutIsBiggerDifferentTime)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_10", twoAttributesConfiguredOneByOne_minTimeoutIsChosen_theSecondTimeoutIsSmallerSimultaneously)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_11", twoAttributesConfiguredOneByOne_minTimeoutIsChosen_theSecondTimeoutIsSmallerDifferentTime)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_12", oneAttributeReporting_reportTimerFired)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_13", twoAttributeReporting_reportTimerFiredForOneOfThem)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_14", twoAttributeReporting_timerFiresSeveralTimes)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_15", zclReportOnChangeIfNeeded_processesNullPointerCorrectly)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_16", zclReportOnChangeIfNeeded_processesNotNullPointerCorrectly)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_17", startReporting_noBindEntry_noReporting_attrPropertiesAreNotUpdated)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_18", startReporting_bindEntryExisting_reportingStarts_attrPropertiesAreUpdated)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_19", zclReportOnChangeIfNeeded_noReportIsIssued_sinceReportingIsOff)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_20", zclReportOnChangeIfNeeded_timerIsNotUpdated_sinceAttrValueIsNotChanged)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_21", zclReportOnChangeIfNeeded_reportIsIssued_sinceAttrValueWasChangedBeforeMinInterval)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_22", zclReportOnChangeIfNeeded_reportIsIssued_sinceAttrValueWasChangedBeforeMinInterval_someTimePassed)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_23", zclReportOnChangeIfNeeded_reportIsIssued_sinceAttrValueWasChangedAfterMinInterval)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_24", zclReportOnChangeIfNeeded_reportOnChangeThenByTimeout)) ||
      (NULL == CU_add_test(pSuite, "Zcl_Reporting_25", zclReportOnChangeIfNeeded_causedByAttributeWriting))
      )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

  /* add Zcl write attribute operation suite to the registry */
  pSuite = CU_add_suite( "zclWriteAttributeBoundaryCheck_test_suite", zclWriteAttributeBoundaryCheckTestsSetup, zclWriteAttributeBoundaryCheckTestsTeardown );
  if ( NULL == pSuite ) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the Zcl Reporting tests to the suite */
  if ((NULL == CU_add_test(pSuite, "Zcl_WriteAttributeBoundaryCheck_1", attributeValueNoRefAttributeWithinRange)) ||
      (NULL == CU_add_test(pSuite, "Zcl_WriteAttributeBoundaryCheck_2", attributeValueNoRefAttributeLessThanMin)) ||
      (NULL == CU_add_test(pSuite, "Zcl_WriteAttributeBoundaryCheck_3", attributeValueNoRefAttributeEqualToMin)) ||
      (NULL == CU_add_test(pSuite, "Zcl_WriteAttributeBoundaryCheck_4", attributeValueNoRefAttributeGreaterThanMax)) ||
      (NULL == CU_add_test(pSuite, "Zcl_WriteAttributeBoundaryCheck_5", attributeValueNoRefAttributeEqualToMax)) ||
      (NULL == CU_add_test(pSuite, "Zcl_WriteAttributeBoundaryCheck_6", attributeValueRefAttributeWithinRange1)) ||
      (NULL == CU_add_test(pSuite, "Zcl_WriteAttributeBoundaryCheck_7", attributeValueRefAttributeLessThanMin1)) ||
      (NULL == CU_add_test(pSuite, "Zcl_WriteAttributeBoundaryCheck_8", attributeValueRefAttributeEqualToMin1)) ||
      (NULL == CU_add_test(pSuite, "Zcl_WriteAttributeBoundaryCheck_9", attributeValueRefAttributeGreaterThanMax1)) ||
      (NULL == CU_add_test(pSuite, "Zcl_WriteAttributeBoundaryCheck_10", attributeValueRefAttributeEqualToMax1)) ||
      (NULL == CU_add_test(pSuite, "Zcl_WriteAttributeBoundaryCheck_11", attributeValueRefAttributeWithinRange2)) ||
      (NULL == CU_add_test(pSuite, "Zcl_WriteAttributeBoundaryCheck_12", attributeValueRefAttributeLessThanMin2)) ||
      (NULL == CU_add_test(pSuite, "Zcl_WriteAttributeBoundaryCheck_13", attributeValueRefAttributeEqualToMin2)) ||
      (NULL == CU_add_test(pSuite, "Zcl_WriteAttributeBoundaryCheck_14", attributeValueRefAttributeWithinRange3)) ||
      (NULL == CU_add_test(pSuite, "Zcl_WriteAttributeBoundaryCheck_15", attributeValueRefAttributeEqualToMax3)) ||
      (NULL == CU_add_test(pSuite, "Zcl_WriteAttributeBoundaryCheck_16", attributeValueRefAttributeGreaterThanMax3)) ||
	  (NULL == CU_add_test(pSuite, "Zcl_WriteAttributeBoundaryCheck_17", attributeValueRefAttributeDoesNotExist))
      )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

#ifdef CONSOLE_OUTPUT
  // Run all tests using the basic interface
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
#endif

#ifdef XML_OUTPUT
  // Run all tests using the automated interface
  CU_automated_run_tests();
  CU_list_tests_to_file();
#endif

#ifdef CONSOLE_INPUT_OUTPUT
  // Run all tests using the console interface
  CU_console_run_tests();
#endif
   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
}

