/*******************************************************************************
  TrustCentre Key Update Header File

  Company:
    Microchip Technology Inc.

  File Name:
    tcKeyUpdate.h

  Summary:
    This file contains the Security Trust Centre key update primitive.

  Description:
    This file contains the Security Trust Centre key update primitive.
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


#ifndef _TCKEYUPDATEH
#define _TCKEYUPDATEH

/******************************************************************************
                             Includes section.
******************************************************************************/
#include <systemenvironment/include/sysTypes.h>
#include <security/TrustCentre/include/tcCommon.h>

/******************************************************************************
                             Types section.
******************************************************************************/

/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef struct
{
  uint8_t status;
} TC_KeyUpdateConf_t;

/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef enum
{
  NWK_SEC_KEY_UPDATE_IDLE,
  NWK_SEC_KEY_UPDATE_IN_PROGRESS,
  NWK_SEC_KEY_UPDATE_DEFERRED,
}TC_KeyUpdateState_t;

/**************************************************************************//**
  \brief TBD.

  TBD
******************************************************************************/
typedef struct
{
  TC_Service_t service;
  TC_KeyUpdateState_t state;
  void (*TC_KeyUpdateConf)(TC_KeyUpdateConf_t *conf);
  TC_KeyUpdateConf_t confirm; //!< Callback function's pointer. Must not be set to NULL.
} TC_KeyUpdateReq_t;

/******************************************************************************
                             Functions prototypes section.
******************************************************************************/
/**************************************************************************//**
  \brief Peforms trust centre key updating procedure in the network.

  \param reqParam - parameters of operation (for detailed description refer to
                    TC_KeyUpdateReq_t type declaration).
  \return none.
******************************************************************************/
void TC_KeyUpdateReq(TC_KeyUpdateReq_t *reqParam);

/**************************************************************************//**
  \brief Initiate a key update if the node is a Trust center.

  \param None.
  \return None.
******************************************************************************/
void tcSecFrameCntrReachMax(void);

#endif //_TCKEYUPDATEH
// eof tcKeyUpdate.h
