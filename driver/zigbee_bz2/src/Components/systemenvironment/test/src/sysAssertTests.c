/*******************************************************************************
  System Environment Assert tests Source File

  Company:
    Microchip Technology Inc.

  File Name:
   sysAssertTest.c

  Summary:
    This file containss system Environment Assert tests implementation.

  Description:
    This file contains system Environment Assert tests implementation.
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
#include <stdint.h>
#include "CUnit.h"
#include "Basic.h"
#include <sysAssert.h>
#include <stdbool.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/

int g_test_level;
/*******************************************************************************
                        Prototypes section
*******************************************************************************/
int test_sysAssertTestSetup(void);
int test_sysAssertTestTeardown(void);
#ifndef MAP_ALL_ASSERT_LEVEL_TO_SYSASSERT
void test_SYS_AssertCallback(SYS_AssertParam_t *ptr);
#endif
//static 

#ifdef USE_WARN_ASSERTS
static int test_sysEnvAssert_WARN_RET(int condition);
#endif
#ifdef USE_ERROR_ASSERTS
static int test_sysEnvAssert_ERROR_RET(int condition);
#endif
#ifdef USE_FATAL_ASSERTS
static int test_sysEnvAssert_FATAL_RET(int condition);
#endif

/*******************************************************************************
                             Implementation section
*******************************************************************************/

/* Test Suite Initialization/Setup */ 
int test_sysAssertTestSetup(void)
{
#ifndef MAP_ALL_ASSERT_LEVEL_TO_SYSASSERT
  SYS_AssertSubscribe(test_SYS_AssertCallback);
#endif
  return 0;
}
/* Test Suite Cleanup /Tear down */
int test_sysAssertTestTeardown(void)
{
  return 0;
}



/**************************************************************************//**
  \brief test_sysEnvAssert_WARN test function to test WARN LEVEL ASSERTS
  when WARN Asserts are enabled, This function tests the WARN assert
  macro SYS_E_ASSERT_WARN, for true and false condition.  This is done with 
  helper test function. When condition is false assert happens, When its true 
  assert does not happen. When assert happens callback is invoked.

  \param[in] None
  \return None
******************************************************************************/
void test_sysEnvAssert_WARN(void)
{
#ifdef USE_WARN_ASSERTS
  CU_ASSERT_EQUAL(WARN_LEVEL, test_sysEnvAssert_WARN_RET(false));
  CU_ASSERT_EQUAL(0, test_sysEnvAssert_WARN_RET(true));
#endif
}


/**************************************************************************//**
  \brief test_sysEnvAssert_ERROR test function to test  ERROR LEVEL ASSERTS
  when ERROR Asserts are enabled, This function tests the error assert 
  macro SYS_E_ASSERT_ERROR for true and false condition with two return types.
  (pointer return and error code return).This is done with helper test functions
  When condition is false NULL is returned for pointer return case.
  When condition is true non NULL is returned for pointer return case.
  When condition is false TEST_ASSERT_INT_RET is returned .
  When condition is true 0 is returned.When assert happens callback is invoked

  \param[in] None
  \return None
******************************************************************************/
void test_sysEnvAssert_ERROR(void)
{
#ifdef USE_ERROR_ASSERTS
  CU_ASSERT_EQUAL(ERROR_LEVEL, test_sysEnvAssert_ERROR_RET(false));
  CU_ASSERT_EQUAL(0,test_sysEnvAssert_ERROR_RET(true));
#endif
}

/**************************************************************************//**
  \brief test_sysEnvAssert_FATAL test function to test FATAL LEVEL ASSERTS
  when FATAL Asserts are enabled, This function tests the FATAL assert
  macro SYS_E_ASSERT_FATAL, for true and false condition.  This is done with 
  helper test function. When condition is false assert happens, When its true 
  assert does not happen. When assert happens callback is invoked.

  \param[in] None
  \return None
******************************************************************************/
void test_sysEnvAssert_FATAL(void)
{
#ifdef USE_FATAL_ASSERTS
  CU_ASSERT_EQUAL(FATAL_LEVEL, test_sysEnvAssert_FATAL_RET(false));
  CU_ASSERT_EQUAL(0, test_sysEnvAssert_FATAL_RET(true));
#endif
}


#ifdef USE_WARN_ASSERTS
static int test_sysEnvAssert_WARN_RET(int condition)
{
  g_test_level = 0;
  SYS_E_ASSERT_WARN(condition, 0xB);
  return g_test_level;
}
#endif

#ifdef USE_ERROR_ASSERTS

static int test_sysEnvAssert_ERROR_RET(int condition)
{
  g_test_level = 0;
  SYS_E_ASSERT_ERROR(condition, 0xC);
  return g_test_level;
}

#endif

#ifdef USE_FATAL_ASSERTS
static int test_sysEnvAssert_FATAL_RET(int condition)
{
  g_test_level = 0;
  SYS_E_ASSERT_FATAL(condition, 0xD);
  return g_test_level;
}

#endif
#ifndef MAP_ALL_ASSERT_LEVEL_TO_SYSASSERT
void test_SYS_AssertCallback(SYS_AssertParam_t *assert_p)
{
  printf("\n test_SYS_AssertCallback invoked with ");
#ifdef  USE_DBGCODE 
  printf(" dbgCode = %d ", assert_p->dbgCode);
#endif

  printf("level %d ", assert_p->level);

  g_test_level = assert_p->level;
  
#ifdef USE_COMPID
  printf("Comp id = %d ", assert_p->componentId); 
#endif
#ifdef USE_FILENAME
  printf(" Filename %s ",  assert_p->file);
#endif
 
#ifdef USE_LINENUM
  printf("Linenume %d ",  assert_p->line);
#endif
  printf("\n ");
}
#endif
// eof sysAssertTests.c
