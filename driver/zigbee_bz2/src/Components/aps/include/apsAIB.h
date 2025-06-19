/*******************************************************************************
  APS AIB Header File

  Company
    Microchip Technology Inc.

  File Name
    apsAIB.h

  Summary
    Interface of APS information base.

  Description
    This header file comprises the attributes required to manage the APS
    layer of a device.
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

// DOM-IGNORE-BEGIN
/**//**
 *
 *  The APS information base comprises the attributes required to manage the APS
 * layer of a device. The attributes of the AIB are listed in ZigBee spec r19,
 * Table 2.24, page 61. The securityrelated AIB attributes are described in
 * sub-clause 4.4.10, page 489.
 **/
#if !defined APS_AIB_H
#define APS_AIB_H
// DOM-IGNORE-END
/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <systemenvironment/include/sysEndian.h>
#include <nwk/include/nwk.h>
#include <aps/include/apsCommon.h>
#include <aps/include/apsCommandReq.h>
#include <configserver/include/configserver.h>

/******************************************************************************
                             Definitions section
 ******************************************************************************/

#define APS_AIB_NONMEMBER_RADIUS_DEFAULT_VALUE 2
/** Bit masks for APS_SecurityPolicy_t type. */
/** The bit permits (1) (or prohibits(0)) processing of an unsecured APS command
 * for which there is no link key associated with the device that sent the command. */
#define APS_NO_SEC_CMD_NO_KEY      (1U << 0)
/** The bit permits (1) (or prohibits(0)) processing of an unsecured command when
 * the GLOBAL link key exists. */
#define APS_NO_SEC_CMD_GLOBAL_KEY  (1U << 1)
/** The bit permits (1) (or prohibits(0)) processing of an unsecured command when
 * there is a UNIQUE link key for the device that sent the command. */
#define APS_NO_SEC_CMD_UNIQUE_KEY  (1U << 2)
/** The bit permits (1) (or prohibits(0)) processing of a secured command that
 * was encrypted with the GLOBAL link key. */
#define APS_SEC_CMD_GLOBAL_KEY     (1U << 3)
/** The bit permits (1) (or prohibits(0)) processing of a secured command that
 * was encrypted with a UNIQUE link key. */
#define APS_SEC_CMD_UNIQUE_KEY     (1U << 4)
/** The bit indicates that the APS layer should encrypt an APS command with the GLOBAL link key. */
#define APS_ENCRYPT_OUT_CMD_BY_GLOBAL_KEY  (1U << 5)
/** The bit indicates that the APS layer should encrypt an APS command with a UNIQUE link key. */
#define APS_ENCRYPT_OUT_CMD_BY_UNIQUE_KEY  (1U << 6)
/** The bit controls transmission of unsecured duplicate command. */
#define APS_IS_DUP_CMD_REQUIRED  (1U << 7)

#define APS_ENCRYPT_OUT_CMD \
  (APS_ENCRYPT_OUT_CMD_BY_GLOBAL_KEY | APS_ENCRYPT_OUT_CMD_BY_UNIQUE_KEY)
/** APS Challenge size */
#define APS_CHALLENGE_SIZE 8

/******************************************************************************
                                Types section
 ******************************************************************************/

/** Type defining security policy for an APS command. */
typedef uint8_t APS_SecurityPolicy_t;

#ifdef _ZIGBEE_REV_23_SUPPORT_
/** Type defining R23 TC security policy. Ref R23 Spec: Table 4-42. Trust Center Policy Values */
typedef enum
{
  DO_NOT_SUPPORT_INSTALL_CODES = 0x00,
  SUPPORT_BUT_DO_NOT_REQUIRE_USE_INSTALL_CODES_OR_PRESET_PASSPHRASES = 0x01,
  REQUIRE_USE_INSTALL_CODES_OR_PRESET_PASSPHRASES = 0x02
} TC_POLICY_INSTALL_CODES_OR_PASSPHRASE;
#endif // _ZIGBEE_REV_23_SUPPORT_

/** Type defining TC security policy. */
typedef struct _APS_TCSecurityPolicy_t
{
  struct PACK
  {
    LITTLE_ENDIAN_OCTET(7, (
    BitField_t allowJoins : 1,
    BitField_t allowRejoins : 1,
    BitField_t useWhiteList : 1,
    BitField_t updateTCLKRequired : 1,
    BitField_t allowRemoteTCPolicyChange : 1,
    BitField_t allowInstallCodes : 1,
    BitField_t reserved : 2
    ))
  }flags;

#ifdef _ZIGBEE_REV_23_SUPPORT_
  uint8_t requireInstallCodesOrPresetPassphrase;
  bool allowRejoinsWithWellKnownKey;
  uint8_t allowTCLinkKeyRequests;
  uint32_t networkKeyUpdatePeriod;
  uint8_t networkKeyUpdateMethod;
  uint8_t allowApplicationKeyRequests;
  bool allowVirtualDevices;
#endif // _ZIGBEE_REV_23_SUPPORT_
  /* Other TC security policies will be brought in, soon */
}APS_TCSecurityPolicy_t;

/** Attributes in APS Information Base. **/
typedef struct
{
  /** Indicates how many hops of non-member nodes a multicast APS command
   * may go through after leaving the group (used in NWK-layer multicasting).
   * Valid range: 0 - 7, default value - 2. */
  NwkRadius_t nonMemberRadius;
  uint8_t maxFrameRetries;
#if defined _SECURITY_
  /** \ref Endian "[LE]" Identifies the Trust Center address. */
  ExtAddr_t  trustCenterAddress;
  /** \ref Endian "[LE]" Network address of the Trust Center. */
  ShortAddr_t tcNwkAddr;
#if defined _LINK_SECURITY_
#ifdef _ZIGBEE_REV_23_SUPPORT_
  bool apsZdoRestrictedMode;
  bool requireLinkKeyEncryptionForApsTransportKey;
  uint8_t apsJoinerTLVsUnfragmentedMaxSize;
#endif
  /** Security policy for incoming and outgoing APS commands. */
  APS_SecurityPolicy_t securityPolicy[APS_MAX_SPID];
#if defined _TRUST_CENTRE_
  /** Security policy values */
  APS_TCSecurityPolicy_t tcSecurityPolicy;
#endif //#if defined _TRUST_CENTRE_
#endif /* _LINK_SECURITY_ */
#endif /* _SECURITY_ */
#ifdef _APS_FRAGMENTATION_
  uint8_t fragWindowSize;
#ifdef _CERTIFICATION_
  uint8_t txFragDropMask;
  uint8_t rxFragDropMask;
#endif /* _CERTIFICATION_  */
#endif /* _APS_FRAGMENTATION_ */
#ifdef _ZIGBEE_REV_23_SUPPORT_
  /** Key Negotiation Protocols */
  uint8_t suppKeyNegotiationProtocol;
  /** Pre-shared Secrets */
  uint8_t supportedPreSharedSecrets;
  /** Maximum Incoming Transfer Unit */
  uint16_t apsMaxSizeASDU;
  /* curve25519 public point */
  uint8_t curve25519PublicPoint[CURVE25519_PUBLIC_KEY_SIZE];
  /** APS Challenge timeout period in sec */
  uint16_t apsChallengePeriodTimeoutSec;
  /** APS Challenge remaining period in sec */
  uint16_t apsChallengePeriodRemainingSec;
  /** APS Challenge value */
  uint8_t apsChallengeValue[APS_CHALLENGE_SIZE];
  /** Rev R23 network join flag */
  bool isJoinedInRev23Network;
  /* Perform device interview flag */
  bool performDeviceInterviewProcedure;
#endif
} AIB_t;

/** The type used to specify if the device is a trust center and what
  type of the trust center, if it is indeed a trust center. */
typedef enum _APS_TcMode_t
{
  /** The device is not a trust center.*/
  APS_NOT_TRUST_CENTER,
  /** The device is the common trust center for the whole network.*/
  APS_CENTRALIZED_TRUST_CENTER,
  /** The device is one of multiple trust centers (this may happen when the network
   * configuration allows any router to serve as a trust center). */
  APS_DISTRIBUTED_TRUST_CENTER
} APS_TcMode_t;

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
#if defined _SECURITY_
/**************************************************************************//**
  \brief Set the Trust Center address

  \param[in] addr - pointer to the extended address to set

  \return none
 ******************************************************************************/
void APS_SetTrustCenterAddress(const ExtAddr_t *addr);

/**************************************************************************//**
  \brief Set the Trust Center NWK address

  \param[in] addr - NWK address of Trust Center

  \return none
 ******************************************************************************/
void APS_SetTrustCenterNwkAddress(const ShortAddr_t addr);

/**************************************************************************//**
  \brief Check whether supplied extended address is the address of Trust Center

  \param[in] addr - pointer to an extended address

  \return true, if the provided address is the TC's address, \c false - otherwise
 ******************************************************************************/
bool APS_IsTcAddress(const ExtAddr_t *addr);

/**************************************************************************//**
  \brief Get a pointer to the Trust Center address

  \return pointer to the Trust Center extended address
 ******************************************************************************/
ExtAddr_t* APS_GetTrustCenterAddress(void);

/**************************************************************************//**
  \brief Get a pointer to the Trust Center Network address

  \return pointer to the Trust Center network address
 ******************************************************************************/
ShortAddr_t* APS_GetTrustCenterNwkAddress(void);

/**************************************************************************//**
  \brief Gets the trust center role of the current device.

  \return The device's role as a trust Center:
  
    - APS_NOT_TRUST_CENTER - not a trust center,
	
    - APS_CENTRALIZED_TRUST_CENTER - a single trust center in the network,
	
    - APS_DISTRIBUTED_TRUST_CENTER  - one of multiple trust centers (each router can
        be a trust center).
 ******************************************************************************/
APS_TcMode_t APS_GetOwnTcMode(void);

/**************************************************************************//**
  \brief Check whether the node is the Trust Center or not.

  \return true, if the node is one of distributed trust centers or the centralized
    trust center; otherwise return false.
 ******************************************************************************/
bool APS_IsTrustCenter(void);

/**************************************************************************//**
  \brief Check whether the provided extended address is a trusted address

  \param[in] addr - a pointer to an extended address to check

  \return \c true, if the argument is the address of the centralized Trust Center
        or there are multiple trust centers in the network (distributed TC mode enabled),
        otherwise return \c false.
 ******************************************************************************/
bool APS_IsTrustedAddress(const ExtAddr_t *addr);

#if defined _LINK_SECURITY_
#ifdef _ZIGBEE_REV_23_SUPPORT_
/**************************************************************************//**
  \brief Enable restricted mode.

  \param[in] restrictedMode - restricted mode (0/1)

  \return None
 ******************************************************************************/
void APS_EnableRestrictedMode(bool restrictedMode);

/**************************************************************************//**
  \brief Is restricted mode.

  \return true/false
 ******************************************************************************/
bool APS_IsRestrictedMode(void);

/**************************************************************************//**
  \brief Enable Link Key Encryption for APS Transport Key.

  \param[in] linkKey - link key encryption

  \return None
 ******************************************************************************/
void APS_EnableLinkKeyEncryptionForApsTransportKey(bool linkKey);

/**************************************************************************//**
  \brief Is Link Key Encryption required for APS Transport Key.

  \return true/false
 ******************************************************************************/
bool APS_IsLinkKeyEncryptionForApsTransportKey();

/**************************************************************************//**
  \brief Sets curve2519 public point if size is CURVE25519_PUBLIC_KEY_SIZE

  \param[in] curve25519PublicPoint - curve25519 public point
  \param[in] size - size of key
  \return True - If key is of CURVE25519_PUBLIC_KEY_SIZE
          False - If key size is not of CURVE25519_PUBLIC_KEY_SIZE
 ******************************************************************************/
bool APS_SetCurve25519PublicPoint(const uint8_t *curve25519PublicPoint, uint8_t size);

/**************************************************************************//**
  \brief Provides curve2519 public point pointer

  \param[in] None.
  \return  curve2519 public point pointer.
 ******************************************************************************/
uint8_t* APS_GetCurve25519PublicPoint(void);

/**************************************************************************//**
  \brief Store APS Challenge Value.

  \param[in] challengeVal - challenge value.
  \param[in] size - size of challenge.

  \return None.
 ******************************************************************************/
void APS_StoreChallenge(uint8_t *challengeVal, uint8_t size);

/**************************************************************************//**
  \brief Set APS Challenge Remaining Period.

  \param challengePeriodSec - Challenge period in sec

  \return None.
 ******************************************************************************/
void APS_SetChallengeRemainingPeriod(uint16_t challengePeriodSec);

/**************************************************************************//**
  \brief Get APS Challenge Remaining Period.

  \return csAIB.apsChallengePeriodRemainingSec.
 ******************************************************************************/
uint16_t APS_GetChallengeRemainingPeriod(void);

/**************************************************************************//**
  \brief Get APS Challenge Timeout Period.

  \return csAIB.apsChallengePeriodTimeoutSec.
 ******************************************************************************/
uint16_t APS_GetChallengeTimeoutPeriod(void);

/**************************************************************************/ /**
  \brief Set the joining flag for Rev R23 network
  \param[in] isRev23Network - Rev R23 network
  \return None
  ******************************************************************************/
void APS_SetJoinRev23NetworkFlag(bool isRev23Network);

/**************************************************************************/ /**
  \brief Check whether the network join is Rev R23 or not
  \return True if the network is Rev R23, otherwise false 
  ******************************************************************************/
bool APS_IsJoinedInRev23Network(void);

/**************************************************************************//**
  \brief Get APS Challenge used in Challenge request command.

  \param[in] challengeVal - challenge value.
  \param[in] size - size of challenge.

  \return None.
 ******************************************************************************/
void APS_GetChallenge(uint8_t *challengeVal, uint8_t size);

#endif //_ZIGBEE_REV_23_SUPPORT_

/**************************************************************************//**
  \brief Updates security policy for the command with a given security policy ID

  \param[in] spid - security policy identifier of the command
             policy - bit map where each bit permits or prohibits processing
                      of an incoming command and determines how to encrypt
                      an outgoing command with the given spid

  \return None
 ******************************************************************************/
void APS_UpdateSecurityPolicy(const APS_SecurityPolicyId_t spid,
  const APS_SecurityPolicy_t policy);

#endif /* _LINK_SECURITY_ */
#endif /* _SECURITY_ */

#ifdef _PARENT_ANNCE_
uint32_t APS_GetParentAnnounceTimer(void);
#endif /* _PARENT_ANNCE_ */
#endif /* APS_AIB_H */
/** eof apsAIB.h */

