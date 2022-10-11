/*******************************************************************************
  APS Binding Source File

  Company:
    Microchip Technology Inc.

  File Name:
    apsBinding.c

  Summary:
    This file contains APS binding related test functions.

  Description:
    This file contains APS binding related test functions.
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
#include <apsmeBind.h>

/******************************************************************************
                    Local variables section
******************************************************************************/
static APS_BindReq_t bindReq;
static bool wasRegistered;

/******************************************************************************
                    Implementation section
******************************************************************************/
void APS_BindReq(APS_BindReq_t *const req)
{
  bindReq = *req;
  wasRegistered = true;
}

ApsBindingEntry_t* APS_NextBindingEntry(ApsBindingEntry_t *entry)
{
  if (!entry && wasRegistered)
    return &bindReq;
  return NULL;
}

void APS_UnbindReq(APS_UnbindReq_t *const req)
{
  wasRegistered = false;
}
// eof halAppClock.c
