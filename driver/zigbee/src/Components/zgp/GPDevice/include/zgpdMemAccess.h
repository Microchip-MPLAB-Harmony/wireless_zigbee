/*******************************************************************************
  Zigbee green power device memory access Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdMemAccess.h

  Summary:
    This file contains the APIs to access ZGP memory.

  Description:
    This file contains the APIs to access ZGP memory.
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

#ifndef _ZGPDMEMACCESS_H
#define _ZGPDMEMACCESS_H
/******************************************************************************
                        Includes  section.
******************************************************************************/
#include <zgp/GPDevice/include/zgpdMem.h>
/******************************************************************************
                         External variables section
******************************************************************************/
/** Defined in .../ZGP/dStub/src/macMem.c */
extern ZGP_Mem_t zgpMem;

/******************************************************************************
                        Inline static functions prototypes section.
******************************************************************************/
/******************************************************************************
  Gets address of ZGP memory.
  Parameters: none.
  returns: Address of ZGP memory.
******************************************************************************/
INLINE ZGP_Mem_t* zgpGetMem(void)
{
  return &zgpMem;
}
/******************************************************************************
  Stores the pointer to the current request.
  Parameters:
    req - pointer to the current request.
  returns:
    none.
******************************************************************************/
INLINE void zgpStoreReqParams(void *req)
{
  zgpGetMem()->zgpReq = req;
}

/******************************************************************************
  Gets the pointer to the current request.
  Parameters:
    none.
  returns:
    Pointer to the current request.
******************************************************************************/
INLINE void* zgpGetReqParams(void)
{
  return zgpGetMem()->zgpReq;
}

/******************************************************************************
                        Types section.
******************************************************************************/

/******************************************************************************
                        Prototypes section.
******************************************************************************/

#endif //_ZGPDMEMACCESS_H

// eof zgpdMemAccess.h
