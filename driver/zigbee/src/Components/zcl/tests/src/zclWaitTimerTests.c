/*******************************************************************************
  ZCL Wait Timer Tests Source File

  Company:
    Microchip Technology Inc.

  File Name:
    zclWaitTimerTests.c

  Summary:
    This file contains the zcl wait timer tests implementation..

  Description:
    This file contains the zcl wait timer tests implementation.
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

/*******************************************************************************
                        Global variables section
*******************************************************************************/
ZclMmBuffer_t *buffer1, *buffer2;
ZCL_Request_t req1, req2;
ZclMmBufferDescriptor_t *descriptor1, *descriptor2;

/*******************************************************************************
                        Prototypes section
*******************************************************************************/
static void initZclMemDescriptors(void);
/*******************************************************************************
                             Implementation section
*******************************************************************************/

/* Test Suite Initialization/Setup */
int zclWaitTimerTestSetup(void)
{
  halSetTimeOfAppTimer(0);
  initZclMemDescriptors();
  return 0;
}

/* Test Suite Cleanup /Tear down */
int zclWaitTimerTestTeardown(void)
{
  SYS_Timer_t *timer = ZCL_GetWaitTimer();

  memset(timer, 0, sizeof(SYS_Timer_t));

  zclMmFreeMem(buffer1);
  zclMmFreeMem(buffer2);
  return 0;
}

/* This tests that zcl wait timer is in stopped state and uniniialized after zcl is reset. */
void defaultWaitTimerStateAfterZclReset(void)
{
  SYS_Timer_t *timer;

  ZCL_ResetReq();

  timer = ZCL_GetWaitTimer();
  CU_ASSERT_EQUAL(SYS_TIMER_STOPPED, timer->state);
  CU_ASSERT_EQUAL(0, timer->timer.interval);
}

/* This tests that wait timer interval is equal to request timeout if request is the only one. */
void setTimerOnce(void)
{
  SYS_Timer_t *timer;

  ZCL_StartWaitResponseTimer(descriptor1);

  timer = ZCL_GetWaitTimer();
  CU_ASSERT_EQUAL(SYS_TIMER_STARTED, timer->state);
  CU_ASSERT_EQUAL(1000, timer->timer.interval);
  CU_ASSERT_EQUAL(1000, descriptor1->timeout);
}

/* This tests that if two request to set timer are done in a short time, that no both requests have the same timeout. */
void twoRequests_atTheSameMomentOfTime(void)
{
  SYS_Timer_t *timer;

  ZCL_StartWaitResponseTimer(descriptor1);
  ZCL_StartWaitResponseTimer(descriptor2);

  timer = ZCL_GetWaitTimer();
  CU_ASSERT_EQUAL(1000, timer->timer.interval);
  CU_ASSERT_EQUAL(1000, descriptor1->timeout);
  CU_ASSERT_EQUAL(1000, descriptor2->timeout);
}

/* This tests that if the second request fires later than the first one,
  timeout of the first request and interval of wait timer are adjusted accordingly. */
void twoRequests_differentTime_secondIsLater(void)
{
  SYS_Timer_t *timer;

  ZCL_StartWaitResponseTimer(descriptor1);
  halSetTimeOfAppTimer(5);
  ZCL_StartWaitResponseTimer(descriptor2);

  timer = ZCL_GetWaitTimer();
  CU_ASSERT_EQUAL(995, timer->timer.interval);
  CU_ASSERT_EQUAL(995, descriptor1->timeout);
  CU_ASSERT_EQUAL(1000, descriptor2->timeout);
}

/* This tests that if the second request fires earlier than the first one,
  timeout of the first request and interval of wait timer are adjusted accordingly. */
void twoRequests_differentTime_secondIsEarlier(void)
{
  SYS_Timer_t *timer;

  descriptor2->timeout = 500;
  ZCL_StartWaitResponseTimer(descriptor1);
  halSetTimeOfAppTimer(5);
  ZCL_StartWaitResponseTimer(descriptor2);

  timer = ZCL_GetWaitTimer();
  CU_ASSERT_EQUAL(500, timer->timer.interval);
  CU_ASSERT_EQUAL(995, descriptor1->timeout);
  CU_ASSERT_EQUAL(500, descriptor2->timeout);
}

/* This tests timer is set to 0 if the first request has already expired when the second one is issued. */
void twoRequests_differentTime_firstAlreadyExpired(void)
{
  SYS_Timer_t *timer;

  descriptor1->timeout = 5;

  ZCL_StartWaitResponseTimer(descriptor1);
  halSetTimeOfAppTimer(5);
  ZCL_StartWaitResponseTimer(descriptor2);

  timer = ZCL_GetWaitTimer();
  CU_ASSERT_EQUAL(0, timer->timer.interval);
  CU_ASSERT_EQUAL(0, descriptor1->timeout);
  CU_ASSERT_EQUAL(1000, descriptor2->timeout);
}

/* This tests timer is set to 0 if the first request has already expired when the second one is issued. */
void twoRequests_differentTime_firstAlreadyExpired2(void)
{
  SYS_Timer_t *timer;

  descriptor1->timeout = 5;

  ZCL_StartWaitResponseTimer(descriptor1);
  halSetTimeOfAppTimer(10);
  ZCL_StartWaitResponseTimer(descriptor2);

  timer = ZCL_GetWaitTimer();
  CU_ASSERT_EQUAL(0, timer->timer.interval);
  CU_ASSERT_EQUAL(0, descriptor1->timeout);
  CU_ASSERT_EQUAL(1000, descriptor2->timeout);
}

/* This tests that request timeout is set to zero and request is released when timer for this request fires. */
void oneRequest_timerExpired(void)
{
  SYS_Timer_t *timer;

  ZCL_StartWaitResponseTimer(descriptor1);
  halSetTimeOfAppTimer(1000);
  ZCL_WaitTimerFired();

  timer = ZCL_GetWaitTimer();
  CU_ASSERT_EQUAL(0, descriptor1->timeout);
  CU_ASSERT_EQUAL(ZCL_UNKNOWN_BUFFER, descriptor1->type);
  CU_ASSERT_EQUAL(SYS_TIMER_STOPPED, timer->state);
}

/* This tests that timeout of not expired request is adjusted properly when another requests expires. */
void twoRequests_secondIsLater_timerExpired(void)
{
  SYS_Timer_t *timer;

  ZCL_StartWaitResponseTimer(descriptor1);
  halSetTimeOfAppTimer(5);
  ZCL_StartWaitResponseTimer(descriptor2);
  halSetTimeOfAppTimer(1000);
  ZCL_WaitTimerFired();

  timer = ZCL_GetWaitTimer();
  CU_ASSERT_EQUAL(0, descriptor1->timeout);
  CU_ASSERT_EQUAL(ZCL_UNKNOWN_BUFFER, descriptor1->type);
  CU_ASSERT_EQUAL(5, timer->timer.interval);
  CU_ASSERT_EQUAL(ZCL_OUTPUT_DATA_BUFFER, descriptor2->type);
  CU_ASSERT_EQUAL(5, descriptor2->timeout);
  CU_ASSERT_EQUAL(SYS_TIMER_STARTED, timer->state);
}

/* This tests that timeout of not expired request is adjusted properly when another requests expires. */
void twoRequests_secondIsEarlier_timerExpired(void)
{
  SYS_Timer_t *timer;

  ZCL_StartWaitResponseTimer(descriptor1);
  halSetTimeOfAppTimer(5);
  descriptor2->timeout = 500;
  ZCL_StartWaitResponseTimer(descriptor2);
  halSetTimeOfAppTimer(505);
  ZCL_WaitTimerFired();

  timer = ZCL_GetWaitTimer();
  CU_ASSERT_EQUAL(0, descriptor2->timeout);
  CU_ASSERT_EQUAL(ZCL_UNKNOWN_BUFFER, descriptor2->type);
  CU_ASSERT_EQUAL(495, timer->timer.interval);
  CU_ASSERT_EQUAL(ZCL_OUTPUT_DATA_BUFFER, descriptor1->type);
  CU_ASSERT_EQUAL(495, descriptor1->timeout);
  CU_ASSERT_EQUAL(SYS_TIMER_STARTED, timer->state);
}

/*******************************************************************************
                        Static Functions section
*******************************************************************************/
static void initZclMemDescriptors(void)
{
  buffer1 = zclMmGetMem(ZCL_OUTPUT_DATA_BUFFER);
  buffer2 = zclMmGetMem(ZCL_OUTPUT_DATA_BUFFER);

  //CU_ASSERT_PTR_NOT_NULL(buffer1);
  //CU_ASSERT_PTR_NOT_NULL(buffer2);
  if( buffer1 && buffer2 )
  {
    req1.service.statusflags = ZCL_REQ_FLAG_CONF_RCVD;
    req2.service.statusflags = ZCL_REQ_FLAG_CONF_RCVD;

    descriptor1 = GET_STRUCT_BY_FIELD_POINTER(ZclMmBufferDescriptor_t, buf, buffer1);
    descriptor1->timeout = 1000;
    descriptor1->link = &req1;
    descriptor2 = GET_STRUCT_BY_FIELD_POINTER(ZclMmBufferDescriptor_t, buf, buffer2);
    descriptor2->timeout = 1000;
    descriptor2->link = &req2;
  }
}
// eof zclWaitTimerTests.cpp