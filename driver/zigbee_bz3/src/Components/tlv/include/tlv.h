/*******************************************************************************
  TLV Header File

  Company
    Microchip Technology Inc.

  File Name
    tlv.h

  Summary
    tlv interface.

  Description
    This header file provides the interface to the TLV API's involved in the R23 support
    in a Zigbee stack
 *******************************************************************************/

// DOM-IGNORE-BEGIN
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

#ifndef TLV_H
#define TLV_H

/******************************************************************************
                                 Includes section
 ******************************************************************************/
#include <systemenvironment/include/sysTypes.h>

/******************************************************************************
                    Defines section
******************************************************************************/

#define SIZE_OF_TAG                               1U
#define SIZE_OF_LENGTH                            1U

#define TOTAL_TLV_PAYLOAD_SIZE(value)             (value + 1U)
#define TOTAL_TLV_SIZE(value)                     (TOTAL_TLV_PAYLOAD_SIZE(value) + SIZE_OF_TAG + SIZE_OF_LENGTH)
#define CALC_TLV_LENGTH_VALUE(length)             ((length) - 1U)
#define JOINING_ENCAPSULATION_TLV_SIZE            (SIZE_OF_TAG + SIZE_OF_LENGTH + sizeof(FragmentationParametersTlv_t) + sizeof(KeyNegotiationTlv_t))

/* This value should be used while calling TLV_Decode function, if there is no
  valid cluster id. */
#define DEFAULT_CLUSTER_ID                        0xFFFF

#define LOCAL_TLV_TAG_ID                          0U

/* Default length of Supported Key Negotiation Method Global TLV */
#define SUPPORTED_KEY_NEGOTIATION_METHODS_GLOBAL_TLV_DEFAULT_LENGTH (sizeof(KeyNegotiationTlv_t) - (SIZE_OF_TAG + SIZE_OF_LENGTH))

/* Default length of Fragmentation Parameters Global TLV */
#define FRAGMENTATION_PARAMETERS_GLOBAL_TLV_DEFAULT_LENGTH          (sizeof(FragmentationParametersTlv_t) - (SIZE_OF_TAG + SIZE_OF_LENGTH))

/* Default length of Router Information Global TLV */
#define ROUTER_INFORMATION_GLOBAL_TLV_DEFAULT_LENGTH          (sizeof(RouterInformationTlv_t) - (SIZE_OF_TAG + SIZE_OF_LENGTH))

/* Max number of EUI64(8 bytes) field that can be filled in a ASDU buffer allocated for TLV. */
#define MAX_EUI64_COUNT  7U
/*Beacon appendix tlv count */
#define BEACON_APPENDIX_ENC_TLV_COUNT 2U
#define MAX_EUI64_COUNT	7U
/* Default length of Curve25519 Public Point TLV */
#define CURVE25519_PUBLIC_POINT_LOCAL_TLV_DEFAULT_LENGTH      (sizeof(Curve25519PublicPointTlv_t) - (SIZE_OF_TAG + SIZE_OF_LENGTH))
/* Challenge size */
#define CHALLENGE_SIZE 8U
/* CCM MIC size */
#define CCM_MIC_SIZE 8U
#define APS_FRAME_COUNTER_CHALLENGE_LOCAL_TLV_DEFAULT_LENGTH 16U
#define APS_FRAME_COUNTER_CHALLENGE_LOCAL_TLV_MIN 2U
#define APS_FRAME_COUNTER_CHALLENGE_RESPONSE_LOCAL_TLV_DEFAULT_LENGTH  32U
#define APS_FRAME_COUNTER_CHALLENGE_RESPONSE_LOCAL_TLV_MIN 2U
#define APS_FRAME_GET_AUTH_LEVEL_LOCAL_TLV_MIN 2U
/******************************************************************************
                    Types section
******************************************************************************/

/**************************************************************************//**
\brief  Describes the value of all global TLVs.
 *****************************************************************************/
typedef enum 
{
  //!< Manufacturer specific global tlv
  MANUFACTURER_SPECIFIC = 64U,
  //!< Supported key negotiation global tlv
  SUPPORTED_KEY_NEGOTIATION = 65U,
  //!< Pan Id conflict report global tlv
  PAN_ID_CONFLICT_REPORT = 66U,
  //!< Next Pan Id change global tlv
  NEXT_PAN_ID_CHANGE = 67U,
  //!< Next channel change global tlv
  NEXT_CHANNEL_CHANGE = 68U,
  //!< Symmetric passphrase global tlv
  SYMMETRIC_PASSPHRASE = 69U,
  //!< Router information global tlv
  ROUTER_INFORMATION = 70U,
  //!< Fragmentation parameter global tlv
  FRAGMENTATION_PARAMETER = 71U,
  //!< Joiner encapsulation global tlv
  JOINER_ENCAPSULATION = 72U,
  //!< Beacon appendix encapsulation global tlv
  BEACON_APPENDIX_ENCAPSULATION = 73U,
  // RESERVED = 74U,
  //!< Configutaion parameters global tlv
  CONFIGURATION_PARAMETER = 75U,
  //!< Device capability extension global tlv
  DEVICE_CAPABILITY_EXTENSION = 76U,

  //RESERVED = 77U-255U

    GLOBAL_TLV_MAX
} Global_Tlv_t;

/**************************************************************************//**
\brief  Describes the category of a TLV.
 *****************************************************************************/
typedef enum
{
  //!< Standalone / independant tlv
  STANDALONE = 1U,
  //!< Encapsulation global tlv
  ENCAPSULATION = 2U,
  //!< Tlv under encapsulation
  ENCAPSULATED_CHILD = 3U,

  INVALID_CATEGORY
} TLV_Category_t;

/**************************************************************************//**
\brief  Describes the status of TLV validation.
 *****************************************************************************/
typedef enum 
{
  //!< All the Tlvs are successfully validated in a incoming buffer
    VALIDATION_SUCCESS = 0U,
  //!< Validation failed due to malformed tlv / truncated data 
    INVALID_TLV,

    TLV_STATUS_MAX
} TLV_Status_t;

/**************************************************************************//**
\brief  specifies the generic format of a TLV
 *****************************************************************************/
BEGIN_PACK
typedef struct PACK
{
  /* Type or tag id of a Tlv. */
    uint8_t tagId;
  /* Data length of the Tlv. */
    uint8_t length;
  /* First data element of the Tlv. */
    uint8_t dataOffset;
} TLV_t;
END_PACK

/**************************************************************************//**
\brief  Describes the information of a TLV.
 *****************************************************************************/
typedef struct
{
  struct
  {
    uint8_t tagId;
    TLV_Category_t tlvCategory;
    TLV_Status_t status;
  } metadata;
  /* Pointer to refer the tlv from the incoming buffer. */
  TLV_t * tlvPointer;

} TlvInfo_t;

/**************************************************************************//**
\brief  specifies the return response structure from the decode function
 *****************************************************************************/
typedef struct
{
  /* Total no of standalone or encapsulation tlv. */
  uint8_t tlvCount;
  /* Overall processing status of the tlvs in the buffer. */
  TLV_Status_t overallStatus;
  /* Pointer to the validated tlv array. */
  TlvInfo_t* tlvInfo;
} TLV_Decode_Resp_t;

/******************************************************************************
                           Global TLV Structures
 ******************************************************************************/

/**************************************************************************//**
\brief  specifies the structure of manufacturer specific global tlv
 *****************************************************************************/
BEGIN_PACK
typedef struct PACK
{
  /* Type or tag id of a Tlv. */
  uint8_t tagId;
  /* Data lenght of the Tlv. */
  uint8_t length;
  /* Manufacturer specific Id. */
  uint16_t manufacturerId;
  /* Manufacturer specific additional data. */
  uint8_t manufacturerData;
} ManufacturerSpecificTlv_t;

typedef struct PACK
{
  LITTLE_ENDIAN_OCTET(4, (
    /* Static key request (Zigbee 3.0 Mechanism) bit field. */
    uint8_t staticKey           : 1,
    /* SPEKE using Curve25519 with Hash AES-MMO-128 bit field. */
    uint8_t aesKey              : 1,
    /* SPEKE using Curve25519 with Hash SHA-256 bit field. */
    uint8_t shaKey              : 1,
    /* Reserved bit fields. */
    uint8_t reserved            : 5
  ))
} KeyNegotiationProtocolBitmask_t;

typedef struct PACK
{
  LITTLE_ENDIAN_OCTET(6, (
    /* Symmetric authentication token bit field. */
    uint8_t symmetricTokenKey   : 1,
    /* Install code key bit field. */
    uint8_t installCodeKey      : 1,
    /* Passcde key bit field. */
    uint8_t passcodeKey         : 1,
    /* Basic access key bit field. */
    uint8_t basicAccessKey      : 1,
    /* Administrative access key bit field. */
    uint8_t adminAccessKey      : 1,
    /* Reserved bit field. */
    uint8_t reserved            : 3
  ))
} PreSharedSecretBitmask_t;

/**************************************************************************//**
\brief  specifies the structure of Key Negotiation Global TLV
 *****************************************************************************/
typedef struct PACK
{
  /* Type or tag id of a Tlv. */
  uint8_t tagId;
  /* Data length of the Tlv. */
  uint8_t length;
  /* Bitmask for key negotiation protocol. */
  KeyNegotiationProtocolBitmask_t keyNegotiationProtocolBitmask;
  /* Bitmask for pre shared secret. */
  PreSharedSecretBitmask_t preSharedSecretBitmask;
  /* Extended UID of source device. */
  uint64_t sourceDeviceEUI64;
} KeyNegotiationTlv_t;

/**************************************************************************//**
\brief  specifies the structure of pan id conflict report global tlv
 *****************************************************************************/
typedef struct PACK
{
  /* Type or tag id of a Tlv. */
  uint8_t tagId;
  /* Data lenght of the Tlv. */
  uint8_t length;
  /* Network pan id conflict count. */
  uint16_t nwkPanIdConflictCount;
} PanIdConflicReportTlv_t;

/**************************************************************************//**
\brief  specifies the structure of next pan id change global tlv
 *****************************************************************************/
typedef struct PACK
{
  /* Type or tag id of a Tlv. */
  uint8_t tagId;
  /* Data lenght of the Tlv. */
  uint8_t length;
  /* Next pan id. */
  uint16_t nextPanIdChange;
} NextPanIdChangeTlv_t;

/**************************************************************************//**
\brief  specifies the structure of next channel change global tlv
 *****************************************************************************/
typedef struct PACK
{
  /* Type or tag id of a Tlv. */
  uint8_t tagId;
  /* Data lenght of the Tlv. */
  uint8_t length;
  /* Next channel. */
  uint32_t channelField;
} NextChannelChangeTlv_t;

/**************************************************************************//**
\brief  specifies the structure of symmetric passphrase global tlv
 *****************************************************************************/
typedef struct PACK
{
  /* Type or tag id of a Tlv. */
  uint8_t tagId;
  /* Data lenght of the Tlv. */
  uint8_t length;
  /* 128 bit symmetric passphrase. */
  uint8_t passPhrase[16];
} SymmetricPassphraseTlv_t;

/**************************************************************************//**
\brief  specifies the structure of router information global tlv value
 *****************************************************************************/

typedef struct PACK _RouterInformationValue_t
{
  LITTLE_ENDIAN_OCTET(8, (
    /* Hub Connectivity */
    uint8_t  hubConnectivity : 1,
    /* Up Time */
    uint8_t  upTime : 1,
    /* Preferred Parent */
    uint8_t  preferredParent : 1,
    /* Battery Backup */
    uint8_t  batteryBackUp : 1,
    /* Enhanced Beacon Request Support */
    uint8_t  enhancedBeaconRequestSupport : 1,
    /* MAC Data Poll Keepalive Support */
    uint8_t  macDataPollKeepAliveSupport : 1,
    /* End Device Keepalive Support */
    uint8_t  endDeviceKeepAliveSupport : 1,
    /* Power Negotiation Support */
    uint8_t  powerNegotiationSupport : 1
  ))
  LITTLE_ENDIAN_OCTET(1, (
    /* Reserved */
    uint8_t  reserved : 8
  ))
} RouterInformationBitMask_t;

/**************************************************************************//**
\brief  specifies the structure of router information global tlv
 *****************************************************************************/
typedef struct PACK
{
  /* Type or tag id of a Tlv. */
  uint8_t tagId;
  /* Data lenght of the Tlv. */
  uint8_t length;
  /* Local router bitmask. */
  RouterInformationBitMask_t routerBitMask;
} RouterInformationTlv_t;

/**************************************************************************//**
\brief  specifies the structure of fragmentation parameter global tlv
 *****************************************************************************/
typedef struct PACK
{
  /* Type or tag id of a Tlv. */
  uint8_t tagId;
  /* Data lenght of the Tlv. */
  uint8_t length;
  /* Node id. */
  uint16_t nodeId;
  /* Fragmentation options. */
  uint8_t fragmentationOption;
  /* Maximum incoming transfer units. */
  uint16_t incomingTransferUnits;
} FragmentationParametersTlv_t;

/**************************************************************************//**
\brief  specifies the structure of configuration parameters global tlv
 *****************************************************************************/
typedef struct PACK
{
  /* Type or tag id of a Tlv. */
  uint8_t tagId;
  /* Data lenght of the Tlv. */
  uint8_t length;
  /* Configuration parameters. */
  uint16_t configurationParameters;
} ConfigurationParametersTlv_t;
END_PACK

/**************************************************************************//**
\brief  specifies the generic structure of an encapsulation tlv
 *****************************************************************************/
typedef struct 
{
  /* Type or tag id of a Tlv. */
  uint8_t tagId;
  /* Data lenght of the Tlv. */
  uint8_t length;
  /* No. of child tlvs that are encapsulated. */
  uint8_t noOfChildTlvs;
  /* Array that contains the address of the address of the child tlv. */
  uint8_t **childTlvList;
} EncapsulationTlv_t;

/******************************************************************************
                           Local TLV Structures
 ******************************************************************************/

/**************************************************************************//**
\brief  specifies the structure of potentail parent list Local tlv
 *****************************************************************************/
/* parameters of potentialParentStructure */
BEGIN_PACK
typedef struct PACK _PotentialParentTableList_t
{
/* Potential parent Short Address. */
  uint16_t devShortAddr;
/* Potential parent LQA. */
  uint8_t lqa;
} PotentialParentTableList_t;

/**************************************************************************//**
\brief  specifies the structure of potentail parent Local tlv
 *****************************************************************************/
/** Parameters of Potentail Parents TLV */
typedef struct PACK _PotentialParents_TLV_t
{
/* Type or tag id of a Tlv. */
  uint8_t tlvID;
/* Data lenght of the Tlv. */
  uint8_t tlvLength;
/* Current Parent short Address. */
  uint16_t currentParentShortAddr;
/* Current parent LQA. */
  uint8_t lqa_CurrentParent;
/* No of Potential Parents. */
  uint8_t potentialParentsCount;
 /* potential parent List. */
  PotentialParentTableList_t potentialParentList[5]; 
}PotentialParents_TLV_t;

/**************************************************************************//**
\brief  specifies the structure of Beacon Survey Results Local tlv
 *****************************************************************************/
/** Parameters of BeaconSurvey results TLV */
typedef struct PACK _BconSurveyResults_TLV_t
{
/* Type or tag id of a Tlv. */
  uint8_t tlvID;
/* Data lenght of the Tlv. */
  uint8_t tlvLength;
/* Total Beacons received on Scan. */
  uint8_t totalBeaconsReceived;
/* No of same Newtork Beacons. */
  uint8_t onNetworkBeacon;
/* No of potential parent beacon. */
  uint8_t potentialParentBeacon;
/* No of parents from different network. */
  uint8_t otherNetworkBeacons;
}BconSurveyResults_TLV_t;

/**************************************************************************//**
\brief  Specifies the structure of Selected Key Negotiation Method Local tlv.
 *****************************************************************************/
typedef struct PACK
{
  /* Type or tag id of the TLV. */
  uint8_t tagId;
  /* Data length of the TLV. */
  uint8_t length;
  /* Key negotiation protocol. */
  uint8_t keyNegotiationProtocol;
  /* pre shared secret. */
  uint8_t preSharedSecret;
  /* Extended UID of source device. */
  uint64_t sourceDeviceEUI64;
} SelectedKeyNegotiationMethodTlv_t;

/**************************************************************************//**
\brief  Specifies the generic structure of a curve25519 public point tlv
 *****************************************************************************/
typedef struct PACK
{
  /* Type or tag id of a Tlv. */
  uint8_t tagId;
  /* Data length of the Tlv. */
  uint8_t length;
  /* Extended UID of source device. */
  uint64_t sourceDeviceEUI64;
  /* Curve Public Point. */
  uint8_t publicPoint[32];
} Curve25519PublicPointTlv_t;

/**************************************************************************//**
\brief  Specifies the structure of Device EUI64 List tlv.
 *****************************************************************************/
typedef struct PACK
{
  /* Type or Tag Id of TLV */
  uint8_t tagId;
  /* Data length of TLV */
  uint8_t length;
  /* The number of EUI64 fields within the TLV */
  uint8_t extAddrCount;
  /* An EUI64 that SHALL trigger corresponding bindings to be deleted */
  uint64_t extAddrList[MAX_EUI64_COUNT];
} DeviceEUI64ListTlv_t;

/**************************************************************************//**
\brief  Specifies the structure of Authentication Token ID tlv.
 *****************************************************************************/
typedef struct PACK
{
  /* Type or Tag Id of TLV */
  uint8_t tagId;
  /* Data length of TLV */
  uint8_t length;
  /* The type type ids of the requesting authentication token */
  uint8_t tlvTypeId;
} AuthenticationTokenIdTlv_t;
/**************************************************************************//**
\brief  Specifies the structure of APS Frame Counter Challenge Local TLV.
 *****************************************************************************/
typedef struct PACK
{
  /* Type or tag ID of the TLV. */
  uint8_t tagId;
  /* Data length of the TLV. */
  uint8_t length;
  /* Extended UID of the sender (device that generated the frame). */
  uint64_t senderEUI64;
  /* Challenge value - A randomly generated 64-bit value. */
  uint8_t challengeValue[CHALLENGE_SIZE];
} ApsFrameCounterChallengeTlv_t;

/**************************************************************************//**
\brief  Specifies the structure of APS Frame Counter Response Local TLV.
 *****************************************************************************/
typedef struct PACK
{
  /* Type or tag ID of the TLV. */
  uint8_t tagId;
  /* Data length of the TLV. */
  uint8_t length;
  /* Extended UID of the responder (device that replies to challenge). */
  uint64_t responderEUI64;
  /* Received challenge value - A randomly generated 64-bit value. */
  uint8_t receivedChallengeValue[CHALLENGE_SIZE];
  /* Current outgoing APS security frame counter from Responder */
  uint32_t apsOutgoingFrameCounter;
  /* AES-CCM-128 outgoing frame counter which is used for MIC over all previous fields in this */
  uint32_t challengeSecurityFrameCounter;
  /* MIC - AES-128-CCM 64-bit MIC on all fields except challengeSecurityFrameCounter */
  uint8_t mic[CCM_MIC_SIZE];
} ApsFrameCounterResponseTlv_t;

/**************************************************************************//**
\brief  Specifies the structure of Target IEEE Address tlv.
 *****************************************************************************/
typedef struct PACK
{
  /* Type or Tag Id of TLV */
  uint8_t tagId;
  /* Data length of TLV */
  uint8_t length;
  /* Extended UID of device whose security level is requested. */
  uint64_t targetDeviceEUI64;
} TargetIeeeAddrTlv_t;

/**************************************************************************//**
\brief  Specifies the structure of Get Device Authentication Level tlv.
 *****************************************************************************/
typedef struct PACK
{
  /* Type or Tag Id of TLV */
  uint8_t tagId;
  /* Data length of TLV */
  uint8_t length;
  /* Extended UID of remote node (which initiated get authentication level req). */
  uint64_t remoteNodeEUI64;
  /* This indicates the joining method that was used when the device joined the network. */
  uint8_t initialJoinMethod;
  /* This indicates what Link Key update method was used to create the current active Link Key. */
  uint8_t activeLinkKeyType;
} DeviceAuthLevelTlv_t;
END_PACK

/******************************************************************************
                           Functions prototypes section
 ******************************************************************************/

/**************************************************************************//**
\brief Decode the Tlvs from the incoming buffer; validate according to the type
    and store it in the TLV array list

\param incomingDataBuffer - Pointer to the incoming buffer
     bufferLength - Buffer length to be processed
     clusterId - command/cluster id of the command
  Note: If there is no valid command/cluster id, the calling function shall use
  the DEFAULT_CLUSTER_ID macro for calling this function.

\return Tlv Decode response object - contains TLV count, overall status and
    pointer to the tlv info array 
 ******************************************************************************/
TLV_Decode_Resp_t TLV_Decode(uint8_t *incomingDataBuffer, uint16_t bufferLength, uint16_t clusterId);

/**************************************************************************//**
\brief Get the tlv data from the user and encode it with the raw buffer

\param outgoingDataBuffer - Pointer to the outgoing buffer
     tlvObject - Pointer to the tlv that has to be encoded

\return Pointer to the next memory location of outgoing buffer to append 
    another tlv.
 ******************************************************************************/
void * TLV_Encode(void *outgoingDataBuffer, void *tlvObject);

/**************************************************************************//**
\brief Construct an encapsulation TLV from the list of child tlvs

\param tlvList - List containts pointers to the child tlvs
     noOfTlvs - No of child tlvs that should be encapsulated
     encapsulationTypeId - Represents the type of Encapsulation tlv
     encTlv - Pointer to store the resultant encapsulation tlv

\return none
 ******************************************************************************/
void TLV_Encapsulate(void* tlvList, uint8_t noOfTlvs, uint8_t encapsulationTypeId, EncapsulationTlv_t *encTlv);

/**************************************************************************//**
\brief Clear the TLV array list

\param none

\return none
 ******************************************************************************/
void TLV_ResetTlvArray(void);

/**************************************************************************/ /**
 \brief Retrieve the TLV associated with the specified tagId from the provided TLV array.

 \param pTlvDecodeResp -  Pointer to the \ref TLV_Decode_Resp_t
 \param tagId -    Requested tag ID

 \return Pointer to TLV \ref TLV_t if TLV of requested tagId found, otherwise NULL

 \note  This function should be invoked after \ref TLVDecode().
 ******************************************************************************/
TLV_t *TLV_GetTlvByTagId(TLV_Decode_Resp_t *pTlvDecodeResp, uint8_t tagId);

#endif /* TLV_H */
