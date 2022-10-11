/*******************************************************************************
  APS SmSsp Header File

  Company
    Microchip Technology Inc.

  File Name
    apsSmSsp.h

  Summary
    APS SSP features header file.

  Description
    This header file defines the APS SSP features available.
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

#ifndef _APSSMSSP_H
#define _APSSMSSP_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <aps.h>
#include <private/apsMemoryManager.h>

/******************************************************************************
                   Types section
******************************************************************************/
typedef enum
{
  APS_SM_SSPE_SUCCESS_STATUS  = 0x00,
  APS_SM_SSPE_START_STATUS,
  APS_SM_SSPE_FAIL_STATUS,
} ApsSspeStatus_t;


#if defined _SECURITY_ && defined _LINK_SECURITY_
typedef enum
{
  APS_SM_SSPD_SUCCESS_STATUS  = 0x00,
  APS_SM_SSPD_START_STATUS,
  APS_SM_SSPD_FAIL_STATUS,
} ApsSspdStatus_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/*****************************************************************************
  APS Frame Encrypt Function
  Parameters: buffer      - APS Security Manager buffer pointer
              dstExtAddr  - destination extended address pointer
              apduLength  - APDU length
  Returns:    APS_SM_SSPE_START_STATUS - encryption process started
              APS_SM_SSPE_FAIL_STATUS - encryption failed
              APS_SM_SSPE_SUCCESS_STATUS - encryption not required
                                                   (not needed)
*****************************************************************************/
/**
 * \brief request for encryption of data buffer
 */
APS_PRIVATE void apsEncryptDataFrame(ApsDataBuffer_t *buffer, uint8_t headerLength);

APS_PRIVATE void apsSecurityTaskHandler(void);
APS_PRIVATE  void apsSecuredNwkDataIndHandler(NWK_DataInd_t *ind);

/*****************************************************************************
  Make a search of key-pair descriptor for extended address specified
  Parameters: address - 64-bit IEEE device address pointer
  Returns:    NULL - key-pair descriptor not found
              valid key-pair descriptor pointer - in other case
*****************************************************************************/
APS_PRIVATE void apsDecryptSentFrame(ApsDataBuffer_t *buffer);

APS_PRIVATE void apsResetSmSsp(void);
#else
#define apsSecurityTaskHandler NULL
#endif //_SECURITY_ and _LINK_SECURITY_
#endif  //#ifndef _APSSMSSP_H
//eof apsSmSsp.h
