// DOM-IGNORE-BEGIN
/*******************************************************************************
  APSME ConfirmKey Header File

  Company
    Microchip Technology Inc.

  File Name
    apsmeConfirmKey.h

  Summary
    Interface of APS Verify Key Service.

  Description
    This header file defines the interface to the verify and confirm key layer of APS.
 *******************************************************************************/


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

// DOM-IGNORE-BEGIN
#if !defined APSME_CONFIRM_KEY_H
#define APSME_CONFIRM_KEY_H
// DOM-IGNORE-END

// DOM-IGNORE-BEGIN
/**//**
 *
 *  The APSME provides service that allow a TC to verify the TCLK
 * of a device. 
 **/
// DOM-IGNORE-END

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <aps/include/apsCommon.h>

#if defined _SECURITY_ && defined _LINK_SECURITY_
/******************************************************************************
                                Types section
 ******************************************************************************/
/**
    The type of key being requested:
    \li Trust Center Link Key,
    \li 0x00, 0x02 and 0x05 – 0xFF = Reserved.
 **/
typedef enum
{
  APS_CONFIRM_APP_LINK_KEY_TYPE = 0x03,
  APS_CONFIRM_TC_LINK_KEY_TYPE = 0x04,
} APS_ConfirmKeyType_t;

/** Status of creating and sending a Confirm key command frame. */
typedef enum
{
  APS_CONFIRM_KEY_SUCCESS_STATUS  = 0x00,
  APS_CONFIRM_KEY_FAIL_STATUS = 0x01,
} APS_ConfirmKeyStatus_t;

/**
    struct APS_ConfirmKeyConf_t apsmeConfirmKey.h "aps.h"
 
    brief Parameters of APSME-CONFIRM-KEY.confirm primitive.
    */
typedef struct
{
  APS_ConfirmKeyStatus_t status; //!< The status of the Confirm key
} APS_ConfirmKeyConf_t;

/**
    struct APS_ConfirmKeyReq_t apsmeConfirmKey.h "aps.h"
 
    brief Parameters of APSME-CONFIRM-KEY.request primitive.
    */
typedef struct
{
  /** \cond SERVICE_FIELDS **/
  struct
  {
    /** Service field, used for queue support */
    QueueElement_t qelem;
    /** Request to send APS Confirm Key command. */
    ApsCommandReq_t commandReq;
    uint32_t ttl;
  } service;
  /** \endcond **/

  /** \ref Endian "[LE]" The extended 64-bit address of the device to which
   * the Confirm-Key command should be sent. */
  ExtAddr_t destAddress;
  /** The type of key been confirm:
   * \li 0x04 = Trust Center Link Key. */
  APS_ConfirmKeyType_t keyType;
  /** The status of TCLK verification done. */
  APS_ConfirmKeyStatus_t status;
  /** Canfirmation parameters. \sa APS_VerifyKeyConf_t */
  APS_ConfirmKeyConf_t confirm;
  /** Callback function pointer as a handler of corresponding
   * confirm primitive. Must not be set to NULL. */
#ifdef _ZIGBEE_REV_23_SUPPORT_
  struct
  {  
    /* Flag for Relay Command. */
    uint8_t relayCmd;
    /** Extended Address of Device to Authorise */
    ExtAddr_t unAuthDevExtAdd;
  } relayMsgInfo;
#endif // _ZIGBEE_REV_23_SUPPORT_
  void (*APS_ConfirmKeyConf)(APS_ConfirmKeyConf_t *conf);
} APS_ConfirmKeyReq_t;

/**
    struct APS_VerifyKeyInd_t apsmeVerifyKey.h "aps.h"
 
    brief Parameters of APSME-VERIFY-KEY.indication primitive.
    */
typedef struct
{
  /** The type of key being Verify. Valid values:
   * \li APS_CONFIRM_TC_LINK_KEY_TYPE
   **/
  APS_ConfirmKeyType_t keyType;
  /** \ref Endian "[LE]" The extended 64-bit address of the device that sent
   * the Verify-Key command. */
  ExtAddr_t srcAddress;
  /** Hask value of TCLK received from remote device. */
  uint8_t hashValue[SECURITY_KEY_SIZE];
    /* The status of the TCLK verification done by TC */
  uint8_t status;
#ifdef _ZIGBEE_REV_23_SUPPORT_
  /* Extended Address of Destination Device */
  ExtAddr_t destAddress;
   struct
    {
      /** Flag for indicating the given request to be process and send via APS Relay Command */
      uint8_t isRelayCmd;
      /** Extended Address of Device to Authorise */
      ExtAddr_t unAuthDevExtAdd;
    } relayMsgInfo;
#endif /* _ZIGBEE_REV_23_SUPPORT_ */ 
} APS_VerifyKeyInd_t;

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Process the Confirm key request.

  \param[in] req - pointer to APSME-CONFIRM-KEY.request's parameters.
                   \sa APS_ConfirmKeyReq_t
  \return None.
 ******************************************************************************/
void APS_ConfirmKeyReq(APS_ConfirmKeyReq_t *req);

/**************************************************************************//**
  \brief Generate this primitive when APS receives a Verify-Key command frame

  Upon receipt of the APSME-VERIFY-KEY.indication primitive, the ZDO shall
  be informed that the device (Trust Center) referenced by the SrcAddress parameter is
  done a key verification.

  \param[in] indParams - pointer to APSME-VERIFY-KEY.indication's parameters.
                   \sa APS_VerifyKeyInd_t
  \return None.
 ******************************************************************************/
void APS_VerifyKeyInd(APS_VerifyKeyInd_t *indParams);

#endif /* _SECURITY_ and _LINK_SECURITY_ */

#endif /* APSME_CONFIRM_KEY_H */
/** eof apsmeConfirmKey.h */

