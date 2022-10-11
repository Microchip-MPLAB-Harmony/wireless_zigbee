/*******************************************************************************
   Main function Source File

  Company:
    Microchip Technology Inc.

  File Name:
   allTests.c

  Summary:
    This file contains  main function implementation.

  Description:
    This file contains  main function implementation.
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

extern int test_sysAssertTestSetup(void);
extern int test_sysAssertTestTeardown(void);

extern void test_sysEnvAssert_WARN(void);
extern void test_sysEnvAssert_ERROR(void);
extern void test_sysEnvAssert_FATAL(void);
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
  pSuite = CU_add_suite( "sysEnvAssert_test_suite", test_sysAssertTestSetup, test_sysAssertTestTeardown);
  if ( NULL == pSuite ) {
    CU_cleanup_registry();
    return CU_get_error();
   }
  /* Add the tests to the suite */
  if ( (NULL == CU_add_test(pSuite, "sysEnvAssert_INFO",  test_sysEnvAssert_WARN)) ||
       (NULL == CU_add_test(pSuite, "sysEnvAssert_ERROR", test_sysEnvAssert_ERROR)) ||
       (NULL == CU_add_test(pSuite, "sysEnvAssert_FATAL", test_sysEnvAssert_FATAL)) 
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

