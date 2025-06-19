// DOM-IGNORE-BEGIN
/*******************************************************************************
  APSME Key Negotiate Header File

  Company
    Microchip Technology Inc.

  File Name
    apsmeKeyNegotiate.h

  Summary
    Interface of APS Negotiate Key Service.

  Description
    This header file provides service that allow a device to negotiate a link key
    with Trust Center.
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

// DOM-IGNORE-BEGIN
#ifndef _APSME_KEY_NEGOTIATE_H
#define _APSME_KEY_NEGOTIATE_H
// DOM-IGNORE-END

// DOM-IGNORE-BEGIN
/**//**
 *
 *  The APSME provides service that allow a device to verify its TCLK
 * with Trust Center. 
 **/
// DOM-IGNORE-END
/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <aps/include/apsCommon.h>

#ifdef _ZIGBEE_REV_23_SUPPORT_
#include <zdo/include/zdoSecurityStartKeyUpdate.h>

/******************************************************************************
                              Definitions section
 ******************************************************************************/
#define APS_WELLKNOWN_PSK_SIZE   (0x10U)
extern uint8_t apscWellKnownPsk[APS_WELLKNOWN_PSK_SIZE];

/******************************************************************************
                                Types section
 ******************************************************************************/

/** Status of key negotiate request command. */
typedef enum
{
  APS_KEY_NEGOTIATE_ERROR_STATUS                       = 0xFF,  
  APS_KEY_NEGOTIATE_SUCCESS_STATUS                     = 0x00,
  APS_KEY_NEGOTIATE_NEGOTIATION_METHOD_MISMATCH_STATUS = 0x01,
  APS_KEY_NEGOTIATE_DEVICE_NOT_FOUND_STATUS            = 0x02,
  APS_KEY_NEGOTIATE_COMPLETE_STATUS                    = 0x03
} APS_KeyNegotiateStatus_t;

/** Status of key negotiate request command. */
typedef enum
{
  APS_KEY_GENERATE_PUBLIC_KEY                       = 0x00,  
  APS_KEY_GENERATE_LINK_KEY                         = 0x01,
} APS_KeyType_t;


/**
    struct APS_KeyNegotiateRequest_t apsmeKeyNegotiate.h "aps.h"
 
    brief Parameters of APSME-NEGOTIATE-KEY.request primitive.
    */
typedef struct
{
  /* Key negotiation method. */
  uint8_t requestedKeyNegotiationMethod;
  /* pre shared secret. */
  uint8_t requestedPreSharedSecretType;
  /* Partner address - TC in this case */
  ExtAddr_t partnerLongAddress;
  /* Flag for Relay Command. */ 
  bool isRelayCommand;
  /* Address of the relay used.  */
  ExtAddr_t relayLongAddress;
} APS_KeyNegotiationReq_t;

/**
    struct APS_KeyNegotiateIndication_t apsmeKeyNegotiate.h "aps.h"
 
    brief Parameters of APSME-KEY.NEGOTIATION.indication primitive.
    */
typedef struct
{
  /* Key negotiation method. */
  uint8_t requestedKeyNegotiationMethod;
  /* pre shared secret. */
  uint8_t requestedPreSharedSecretType;
  /* Partner address - TC in this case */
  ExtAddr_t partnerLongAddress;
  /* Curve Public Point. */
  uint8_t publicPointData[32];  
  /* Flag for Relay Command. */ 
  bool isRelayCommand;
  /* Address of the relay used.  */
  ExtAddr_t relayLongAddress;
} APS_KeyNegotiationInd_t;

/**
    struct APS_KeyNegotiationResp_t apsmeKeyNegotiate.h "aps.h"
 
    brief Parameters of APSME-KEY.NEGOTIATION.response primitive.
    */
typedef struct
{
  /* Status. */
  uint8_t status;
  /* Key negotiation method. */
  SelectedKeyNegotiationProtocol_t keyNegotiationMethod;
  /* Pre shared secret. */
  uint8_t preSharedSecretType;
  /* Partner Public Point. */
  uint8_t partnerPublicPointData[32];  
  /* Partner address - TC in this case. */
  ExtAddr_t partnerLongAddress;
  /* Flag for Relay Command. */ 
  bool isRelayCommand;
  /* Address of the relay used.  */
  ExtAddr_t relayLongAddress;
} APS_KeyNegotiationResp_t;

/**
    struct APS_KeyNegotiationConf_t apsmeKeyNegotiate.h "aps.h"
 
    brief Parameters of APSME-KEY.NEGOTIATION.confirm primitive.
    */
typedef struct
{
  /* Status. */
  uint8_t status;
  /* Partner Public Point. */
  uint8_t partnerPublicPointData[32];  
  /* Partner address - device/router in this case. */
  ExtAddr_t partnerLongAddress;
  /* Flag for Relay Command. */ 
  bool isRelayCommand;
  /* Address of the relay used.  */
  ExtAddr_t relayLongAddress;
} APS_KeyNegotiationConf_t;

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/*************************************************************************************************************//**
  \brief Request APS security start key negotiation request.
         Implementation as per 4.4.9.1.2 APSME-KEY-NEGOTIATION.request

  \param[in] pApsKeyNegotiationReq - pointer to \ref APS_KeyNegotiationReq_t.

  \return status of the passed parameters:
  \li APS_KEY_NEGOTIATE_NEGOTIATION_METHOD_MISMATCH_STATUS - negotiation method did not match,
  \li APS_KEY_NEGOTIATE_DEVICE_NOT_FOUND_STATUS - device not found in key pair descriptor table,
  \li APS_KEY_NEGOTIATE_ERROR_STATUS  - can't update key negotiation status.
 ****************************************************************************************************************/
APS_KeyNegotiateStatus_t APS_KeyNegotiationReq(const APS_KeyNegotiationReq_t const *pApsKeyNegotiationReq);

/**************************************************************************//**
  \brief Set install code Passphrase to a global variable.

  \param[in] icCode Pointer to install code.

  \return None.
 ******************************************************************************/
void APS_SetInstallCodePassphrase(uint8_t *icCode);
/***************************************************************************//**
  \brief Request ZDO security service key negotiate indication.

  \param[in] pApsKeyNegotiationInd - pointer to \ref APS_KeyNegotiationInd_t.

  \return None.
 ******************************************************************************/
void APS_KeyNegotiationInd(const APS_KeyNegotiationInd_t const *pApsKeyNegotiationInd);

/**************************************************************************//**
  \brief Response function for APS security key negotiation request
         Implementation as per 4.4.9.3 APSME-KEY-NEGOTIATION.response section.

  \param[in] pKeyNegotiationResp Pointer to \ref APS_KeyNegotiationResp_t.

  \return None.
 ******************************************************************************/
void APS_KeyNegotiationResponse(const APS_KeyNegotiationResp_t const *pKeyNegotiationResp);

/**************************************************************************//**
  \brief Confirmation function for APS Key Negotiation Request
        Refer 4.4.9.4.2 Effect On Receipt section

  \param[in] pApsKeyNegotiationConf - APS Key Negotiation Confirmation from ZDO.

  \return None.
 ******************************************************************************/
void APS_KeyNegotiationConf(const APS_KeyNegotiationConf_t const *pApsKeyNegotiationConf);

/*************************************************************************************************************//**
  \brief Send request to start the Key Negotiation

  \return None.
 ****************************************************************************************************************/
void APS_SendKeyNegotiationReq(void);

#endif /* _ZIGBEE_REV_23_SUPPORT_ */

#endif /* _APSME_KEY_NEGOTIATE_H */
/** eof apsmeKeyNegotiate.h */

