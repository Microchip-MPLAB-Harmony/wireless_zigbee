// DOM-IGNORE-BEGIN
/*******************************************************************************
  APS Header File

  Company
    Microchip Technology Inc.

  File Name
    aps.h

  Summary
    Interface of APS layer.

  Description
    This header file defines the interface of APS layer.
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
#if !defined APS_H
#define APS_H
// DOM-IGNORE-END

// DOM-IGNORE-BEGIN
/**//**
 * \page Endian
 * \note \b |LE| - parameter in little endian format.
 *
 *   Use macroes CPU_TO_LE* and CCPU_TO_LE* from sysEndian.h to convert from
 * CPU-endian to little-endian format.
 **/
// DOM-IGNORE-END
/******************************************************************************
                                    Includes section
 ******************************************************************************/
#include <aps/include/apsCommon.h>
#include <aps/include/apsdeEndpoint.h>
#include <aps/include/apsdeData.h>
#include <aps/include/apsCommandReq.h>
#include <aps/include/apsmeGroup.h>
#include <aps/include/apsmeBind.h>
#include <aps/include/apsAIB.h>
#include <aps/include/apsCryptoKeys.h>
#include <aps/include/apsmeAuthenticate.h>
#include <aps/include/apsmeEstablishKey.h>
#include <aps/include/apsmeRemoveDevice.h>
#include <aps/include/apsmeRequestKey.h>
#include <aps/include/apsmeSwitchKey.h>
#include <aps/include/apsmeTransportKey.h>
#include <aps/include/apsmeUpdateDevice.h>
#include <aps/include/apsmeVerifyKey.h>
#include <aps/include/apsmeConfirmKey.h>
#include <aps/include/intrpData.h>
#ifdef _ZIGBEE_REV_23_SUPPORT_
#include <aps/include/apsFragmentationCache.h>
#include <aps/include/apsmeKeyNegotiate.h>

#endif /* _ZIGBEE_REV_23_SUPPORT_ */

/******************************************************************************
                                Types section
 ******************************************************************************/
/** External events identifiers. */
typedef enum
{
  APS_EVENT_RESET_ID = 0x19,
  APS_EVENT_START_ID = 0x8a,
  APS_EVENT_STOP_ID  = 0xc5
} APS_EventId_t;

/** Type of external APS event. */
typedef struct
{
  void *next;       /*!< Used for queue support. */
  APS_EventId_t id; /*!< Identifier of APS event. */
} APS_Event_t;

/** Confirmation parameters of APS Reset. */
typedef struct
{
  APS_Status_t status;
} APS_ResetConf_t;

/** Type of APS Reset parameters structure. */
typedef struct
{
  /** \cond SERVICE_FIELDS **/
  struct
  {
    APS_Event_t event;
    /** NLME-RESET request primitive's parameters structure. */
    NWK_ResetReq_t nwkResetReq;
  } service;
  /** \endcond **/

  /** APS reset confirm callback function's pointer. Must not be set to NULL.*/
  void (*APS_ResetConf)(APS_ResetConf_t *conf);
  APS_ResetConf_t confirm; /*!< Parameters are passed to callback function. */
} APS_ResetReq_t;

/** Type of startup confirmation parameters. */
typedef struct
{
  APS_Status_t status; /*!< Status code of APS startup. */
} APS_StartConf_t;

/** Parameters of APS start procedure. */
typedef struct
{
  /** \cond SERVICE_FIELDS **/
  struct
  {
    APS_Event_t event;
  } service;
  /** \endcond **/

  /** APS startup callback function. Must not be set to NULL. */
  void (*APS_StartConf)(APS_StartConf_t *conf);
  APS_StartConf_t confirm; /*!< APS startup confirmation parameters. */
} APS_StartReq_t;

/** Type of APS stoping confirmation parameters. */
typedef struct
{
  APS_Status_t status; /*!< Status code of APS stoping. */
} APS_StopConf_t;

/** Parameters of APS stoping primitive. */
typedef struct
{
  /** \cond SERVICE_FIELDS **/
  struct
  {
    APS_Event_t event;
    uint16_t waitMask; /*! Bit map of stopping components. */
  } service;
  /** \endcond **/

  /** Callback and APS stoping confirmation function. Must not be set to NULL. */
  void (*APS_StopConf)(APS_StopConf_t *conf);
  APS_StopConf_t confirm;
} APS_StopReq_t;

#ifdef _ZIGBEE_REV_23_SUPPORT_
/** Type for APS Key pair backup data. */
BEGIN_PACK
typedef struct PACK
{
  /* Device extended address. */
  ExtAddr_t deviceExtAddr;
  /* APS Key attributes. */
  ApsKeyAttributes_t keyAttributes;
  /* The actual value of the initial key. */
  uint8_t initialJoinKey[SECURITY_KEY_SIZE];
  /* APS Selected key negotiation protocol method. */
  SelectedKeyNegotiationProtocol_t keyNegotiationMethod;
  /* APS Key-pair pass phrase. */
  uint8_t passPhrase[PASSPHRASE_MAX_SIZE];
  /* APS Key-pair flags. */
  uint8_t flagBits;
  /* APS Trust center swap out link key. */
  uint8_t tcSwapOutLinkKey[SECURITY_KEY_SIZE];
} APS_BackupData_t;
END_PACK

#endif /* _ZIGBEE_REV_23_SUPPORT_ */

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Initialization internal state and main variables of APS-layer.

     The function can be called only by ZDO.
     It must be called before any operation with APS.

  \return None.
 ******************************************************************************/
void APS_Init(void);

/**************************************************************************//**
  \brief Resets APS to default state.

     The function can be called only by ZDO and only after APS_Init().

  \param[in] req - pointer to reset parameters.
  \return None.
 *****************************************************************************/
void APS_ResetReq(APS_ResetReq_t *const req);

/**************************************************************************//**
  \brief Makes APS allow processing of incoming packets.

   After this function is called, APS is ready to process incoming packets.

  \param[in] req - pointer to startup parameters.
  \return None.
 ******************************************************************************/
void APS_StartReq(APS_StartReq_t *const req);

/**************************************************************************//**
  \brief Makes APS disallow processing of incoming packets.

   After this function is called, APS does not process incoming packets.

  \param[in] req - pointer to stopping parameters.
  \return None.
 ******************************************************************************/
void APS_StopReq(APS_StopReq_t *const req);

/**************************************************************************//**
  \brief Check if APS is started.

  \return 'true' if APS is started otherwise return 'false'
 ******************************************************************************/
bool APS_IsStarted(void);

/**************************************************************************//**
  \brief Check if there are any active requests in progress.

  \return 'true' if there are any active requests in progress otherwise - 'false'
 ******************************************************************************/
bool APS_IsActiveTransaction(void);

/**************************************************************************//**
  \brief Resetting choosed tables.
  
  \param[in] ctrl - set of flags to checking.
  \return None
 ******************************************************************************/
void APS_HandleLeave(NWK_LeaveControl_t *const ctrl);

/**************************************************************************//**
  \brief Delete the specified element in APS Data request queue.

  \param[in] apsDataReq - element to be deleted
 ******************************************************************************/
void APS_ApsDataReqDeleteQueueElem(APS_DataReq_t *apsDataReq);

#ifdef _CUSTOM_NWK_HEADER_
/**************************************************************************//**
  \brief Update IEEE addresses if NWK_DataReq.

  \param[in] req - nwk data req to be updated
 ******************************************************************************/
void apsUpdateIEEEaddr(NWK_DataReq_t *const req);

/**************************************************************************//**
  \brief Update NULL IEEE addresses if NWK_DataReq.

  \param[in] req - nwk data req to be updated
 ******************************************************************************/
INLINE void apsUpdateNullIEEEaddr(NWK_DataReq_t *const req)
{
  COPY_EXT_ADDR(req->srcExtAddr, APS_INVALID_EXT_ADDRESS);
  COPY_EXT_ADDR(req->dstExtAddr, APS_INVALID_EXT_ADDRESS);
}
#endif

#ifdef _ZIGBEE_REV_23_SUPPORT_
/**************************************************************************//**
  \brief Retrieve the APS key pair value of the particular index and store
         it in the backup buffer.

  \param[in] keyPairIndex - index value of the APS key pair set
  \param[out] backupBuffer - pointer to the buffer to which the data to be 
                             copied.

  \return - The no of bytes written into the backup buffer.
 ******************************************************************************/
uint16_t APS_FillBackup(APS_KeyPairIndex_t keyPairIndex, uint8_t *backupBuffer);

/**************************************************************************//**
  \brief Restore the Trust center aps key pair table from the backup data.

  \param[in] keyPairIndex - index position of the key pair table to where the
                            data to be restored.
  \param[in] backupBuffer - pointer to the buffer from where the data can
                            be copied.

  \return True - If the restore is successful.
          False - Otherwise.
 ******************************************************************************/
bool APS_RestoreBackup(APS_KeyPairIndex_t keyPairIndex, uint8_t *restoreBuffer);

/**************************************************************************//**
  \brief Update the aps key pair record of the trust cetner.

  \param[in] previousTcAddress - Extended address of old trust center.
  \param[in] newTcAddress - Extended address of new trust center.
  \param[in] updateLinkKey - Flag to decide whether to update the link key
                             or not.

  \return APS Key Handle of swapout tc record.
 ******************************************************************************/
APS_KeyHandle_t APS_UpdateTcSwapRecord(const ExtAddr_t *const previousTcAddress, const ExtAddr_t *const newTcAddress, bool updateLinkKey);

#endif /* _ZIGBEE_REV_23_SUPPORT_ */
#endif  /* APS_H */
/** eof aps.h */

