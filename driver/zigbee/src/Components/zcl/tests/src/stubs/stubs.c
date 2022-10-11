/*******************************************************************************
  Stubs Source File

  Company:
    Microchip Technology Inc.

  File Name:
    stubs.c

  Summary:
    This file contains generic stub functionality.

  Description:
    This file contains generic stub functionality.
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
#include <configserver.h>
#include <apsdeEndpoint.h>
#include <apsmeBind.h>
#include <apsdeData.h>
#include <nwkAttributes.h>
#include <appTimer.h>
#include <zcl.h>

volatile uint16_t SYS_taskFlag;

static APS_RegisterEndpointReq_t *endpoint;

/******************************************************************************
                    Implementation section
******************************************************************************/
void APS_RegisterEndpointReq(APS_RegisterEndpointReq_t *const req)
{
  endpoint = req;
}

void APS_UnregisterEndpointReq(APS_UnregisterEndpointReq_t *const req)
{
  (void)req;
}

APS_RegisterEndpointReq_t* APS_NextEndpoint(const APS_RegisterEndpointReq_t *const prev)
{
  if (prev)
    return NULL;
  return endpoint;
}

void APS_DataReq(APS_DataReq_t *const req)
{
  (void)req;
}

uint32_t NWK_GetUnicastDeliveryTime(void)
{
  return 1;
}

void halStartAtomic(void)
{}

void halEndAtomic(void)
{}

int HAL_StartAppTimer(HAL_AppTimer_t *appTimer)
{
  (void)appTimer;
}

int HAL_StopAppTimer(HAL_AppTimer_t *appTimer)
{
  (void)appTimer;
}
// eof stubs.c
