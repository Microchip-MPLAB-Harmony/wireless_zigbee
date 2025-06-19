// DOM-IGNORE-BEGIN
/*******************************************************************************
  Zigbee device object security manager Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zdoSecurityServiceManager.h

  Summary:
    The header file describes the constants, types and internal interface
    of ZDO security manager

  Description:
    The header file describes the constants, types and internal interface
    of ZDO security manager

 *******************************************************************************/


/*******************************************************************************
* Copyright (C) 2024 Microchip Technology Inc. and its subsidiaries.
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

#ifndef ZDO_SECURITY_SERVICE_MANAGER_H
#define ZDO_SECURITY_SERVICE_MANAGER_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <zdo/include/zdo.h>
#include <zdo/include/private/zdoCommands.h>
#ifdef _ZIGBEE_REV_23_SUPPORT_
#include <security/serviceprovider/include/sspCurve25519Handler.h>
#endif //_ZIGBEE_REV_23_SUPPORT_

/******************************************************************************
                        Definitions section.
******************************************************************************/
#define MESSAGE_LEN        23U

/******************************************************************************
                                Types section
 ******************************************************************************/

#ifdef _ZIGBEE_REV_23_SUPPORT_
typedef struct _ZdoSecurityServiceStartKeyUpdate_t
{
  /* Security Start Key Update Zdp Request */
  ZDO_ZdpReq_t zdpReq;

  /* Response callback to notify the upper layer */
  void (*callback)(uint8_t status, ExtAddr_t deviceExtAddr);

  ZDO_Status_t status;

  /* Flag for Relay Command. */ 
  bool isRelayCommand;

  /* Address of the relay. */
  ExtAddr_t extAddress;

  SelectedKeyNegotiationMethodTlv_t selectedKeyNegotiationTlv;

} ZdoSecurityServiceStartKeyUpdate_t;

typedef struct _ZdoSecurityServiceStartKeyNegotiation_t
{
  /* Security start key negotiation zdp request. */
  ZDO_ZdpReq_t zdpReq;

  /* APS start key negotiaion request. */
  APS_KeyNegotiationReq_t apsKeyNegotiationReq;

  /* APS start key negotiaion indication. */
  APS_KeyNegotiationInd_t apsKeyNegotiationInd;

  /* APS start key negotiaion response. */
  APS_KeyNegotiationResp_t apsKeyNegotiationResp;
  
  /* APS start key negotiaion confirmation. */  
  APS_KeyNegotiationConf_t apsKeyNegotiationConf;

  /* Generate key using curve25519. */
  APS_KeyType_t keyType;

  APS_DataInd_t apsDataInd;
  
  ZdoCommand_t *zdoCommand;

  SspCurve25519GenerateLinkKeyReq_t sspReq;

  /* callback to notify the upper layer */
  void (*reqInd)(ExtAddr_t deviceExtAddr);
} ZdoSecurityServiceStartKeyNegotiation_t;

/** Describes the Retrieve Auth token memory structure */
typedef struct _ZdoSecurityRetrieveAuthTokenMem_t
{
  /* Security Retrieve Auth token zdp request. */
  ZDO_ZdpReq_t zdpReq;
  /* Callback function after receving response. */
  void (*retrieveCallback)(void);
} ZdoSecurityRetrieveAuthTokenMem_t;

/** Describes the Security Challenge memory structure */
typedef struct _ZdoSecurityChallenge_t
{
  /* Security Challenge ZDP Request. */
  ZDO_ZdpReq_t zdpReq;

  /* HAL_AppTimer_t structure */
  HAL_AppTimer_t challengePeriodTimer;

  ZdoCommand_t *zdoCommand;

  APS_DataInd_t apsDataInd;

  uint8_t ccmMessage[MESSAGE_LEN];

  uint8_t ccmMic[CCM_MIC_SIZE];

  ApsFrameCounterChallengeTlv_t apsFrameCounterChallengeTlv;
 
  /* Current outgoing APS security frame counter from Responder */
  uint32_t apsOutgoingFrameCounter;

  /* CCM Req object for encryption, decryptin  */
  SSP_CcmReq_t apsCcmReq;

  /** Challenge Target EUI64 (64-bit Extended IEEE address) */
  ExtAddr_t challengeTargetEui64;

  ApsFrameCounterResponseTlv_t apsFrameCounterChallengeRespTlv;
} ZdoSecurityChallenge_t;

/** Describes the Security Challenge memory structure */
typedef struct _ZdoSecurityAuthLevel_t
{
  /* Security Challenge ZDP Request. */
  ZDO_ZdpReq_t zdpReq;

  ZdoCommand_t *zdoCommand;

  APS_DataInd_t apsDataInd;

} ZdoSecurityAuthLevel_t;

typedef struct _ZdoSecurityServiceManager_t
{

  /* Wait to receive the request */
  HAL_AppTimer_t waitTimer;

  union
  {
    /* Security Start Key Update */
    ZdoSecurityServiceStartKeyUpdate_t startKeyUpdate;

    /* Security Start Key Negotiation */
    ZdoSecurityServiceStartKeyNegotiation_t startKeyNegotiation;

    /* Security retrieve auth token memory. */
    ZdoSecurityRetrieveAuthTokenMem_t retrieveAuthTokenMem;

    /* Security Challenge */
    ZdoSecurityChallenge_t securityChallenge;

    /* Security Authentication Level */
    ZdoSecurityAuthLevel_t securityAuthLevel;
  };
} ZdoSecurityServiceManager_t;

#endif //_ZIGBEE_REV_23_SUPPORT_

/*****************************************************************************************************************
                                Prototypes section
 ****************************************************************************************************************/

#ifdef _ZIGBEE_REV_23_SUPPORT_

void zdoZdpSecurityRequestCreate(ZDO_ZdpReq_t *zdpReq);

/*************************************************************************************************************//**
  \brief Prepare Start Key Update Response.

    Validate the incoming Start Key Update Request and prepare and send response.

  \param[in] apsDataInd - pointer to APSDE-DATA indication structure of
                          received ZDP command.

  \param[in] zdoCommand - a pointer to allocated memory to perform a stack
                          request or to send ZDP command.
  \return None.
 ***************************************************************************************************************/
void zdoPrepareStartKeyUpdateResponse(const APS_DataInd_t *const apsDataInd, ZdoCommand_t *const zdoCommand);

/*************************************************************************************************************//**
  \brief Check access for security incompatible frame
         This function checks whether to allow/accept the security incompatible frame or not.

  \param[in] addressMode - Address Mode.

  \param[in] deviceAddress - Sender device address.

  \return true to allow/accept the frame otherwise false.
 ***************************************************************************************************************/
bool zdoAllowSecurityInCompatibleFrame(APS_AddrMode_t addressMode, APS_Address_t deviceAddress);

/*************************************************************************************************************//**
  \brief Prepare Start Key Negotiation Response.

    Validate the incoming Start Key Negotiation Request and prepare and send response.

  \param[in] apsDataInd - pointer to APSDE-DATA indication structure of
                          received ZDP command.

  \param[in] zdoCommand - a pointer to allocated memory to perform a stack
                          request or to send ZDP command.
  \return None.
 ***************************************************************************************************************/
void zdoPrepareStartKeyNegotiationResponse(const APS_DataInd_t *const apsDataInd, ZdoCommand_t *const zdoCommand);

#endif /* _ZIGBEE_REV_23_SUPPORT_ */
#endif /* ZDO_SECURITY_SERVICE_MANAGER_H */
