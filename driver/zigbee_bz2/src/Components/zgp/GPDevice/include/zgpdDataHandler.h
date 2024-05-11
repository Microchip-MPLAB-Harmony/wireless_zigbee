/*******************************************************************************
  Zigbee green power Data handler Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdDataHandler.h

  Summary:
    This file contains the zgpDataHandler header file.

  Description:
    This file contains the zgpDataHandler header file.
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

#ifndef ZGPDDATAHANDLER_H
#define ZGPDDATAHANDLER_H
/******************************************************************************
                        Includes  section.
******************************************************************************/
#include <zgp/GPDevice/include/zgpdCommon.h>
#include <mac_phy/include/mac.h>
#include <zgp/GPDevice/include/zgpdSecurity.h>

/******************************************************************************
                        Types section.
******************************************************************************/
/******************************************************************************
                               ZGP Data Request
                   Please refer A.1.3.2 for details.
******************************************************************************/
//Based on device type and energy budget Tx-Options will be selected.
BEGIN_PACK
typedef struct PACK
{
  uint8_t   performCsma   :1;
  uint8_t   requireMacAck :1;
  /** Reserved. Should always be zero. */
  uint8_t   reserved :6;
} ZGPD_TxOptions_t;
END_PACK

 /* ZGP_Data confirm primitive's parameters structure declaration*/
BEGIN_PACK
typedef struct _ZGP_Dataconf_t
{
  ZGP_Status_t status;
  uint8_t handle;
}ZGP_DataConf_t;
END_PACK

///* This will be used for ZGP data request*/
typedef struct _ZGP_DataReq_t
{
    /** \cond SERVICE_FIELDS **/
    //!< Service fields for internal use only, should not be touched by user
    ZGP_Service_t service;
  /** \endcond **/
    
    //bool action;
    ZGPD_TxOptions_t txOptions;
    ZGP_ApplicationId_t appId;
    uint8_t eppHandle;
    ZgpSourceId_t srcId;
    uint64_t zgpIEEEAddr;
    uint8_t endPoint;
    uint8_t asduLength;
    uint8_t *asdu;
    uint16_t zgpTxQueueEntryLifetime;
    //! ZGP confirm callback function's pointer.
    void (*ZGP_DataConf)(ZGP_DataConf_t *conf);
    //! ZGP confirm argument structure. Shall not be filled by user.
    ZGP_DataConf_t confirm;
}ZGP_DataReq_t;

BEGIN_PACK
/** ZGP packet type. */
typedef struct _ZGP_Packet_t
{
    uint8_t header[ZGP_MAX_ASDU_OFFSET];
    uint8_t payload[ZGP_MAX_ASDU_SIZE];
    uint8_t footer[ZGP_MAX_AFFIX_LENGTH - ZGP_MAX_ASDU_OFFSET];
}ZGP_Packet_t;
END_PACK

/******************************************************************************
                                 ZGP Data indication
                           Please refer A.1.3.1 for details.
******************************************************************************/
///* This will be used for ZGP data indication*/
BEGIN_PACK
typedef enum _ZGP_DataInd_Status_t
{
    ZGP_SECURITY_SUCCESS,  
    ZGP_NO_SECURITY,
    ZGP_COUNTER_FAILURE,
    ZGP_AYTH_FAILURE,
    ZGP_UNPROCESSEED
}ZGP_DataInd_Status_t;
END_PACK

///* This will be used for ZGP data indication*/
typedef struct _ZGP_DataInd_t
{
  ZGP_DataInd_Status_t status;
  uint8_t LQI;
  uint8_t seqNum;
  uint8_t srcAddrMode;
  uint16_t srcPANID;
  ZgpSourceId_t srcAddr;
  ZGP_ApplicationId_t appId;
  ZGP_SecLevel_t gpdfSecLevel;
  ZGP_SecKeyType_t zgpKeyType;
  bool autoCommissioning;
  bool rxAfterTx;
  uint32_t srcId;
  uint8_t endPoint;
  uint32_t zgpdSecFrameCounter;
  uint8_t cmdID;
  uint8_t zgpAsduLen;
  uint8_t *zgpAsdu;
  uint32_t mic;
}ZGP_DataInd_t;
/******************************************************************************
                    ZGP Attribute Reporting command structure
                       Please refer A.4.2.3.1 for details.
******************************************************************************/
BEGIN_PACK
typedef struct
{
    uint16_t attributeId;
    uint8_t attributeDataType;
    uint16_t attributeData;  
}zgpAttrField_t;
END_PACK

//! Attribute reporting field
typedef struct
{
    zgpAttrField_t zgpAttrField;
    uint8_t attrStatus;
}ZGP_AttrReportField_t;

//! Attribute reporting command
BEGIN_PACK
typedef struct
{
    uint8_t cmdID;
    uint16_t zigbeeClusterID;
    zgpAttrField_t attrReport[NO_OF_ATTRIBUTE_REPORT_FIELD];
}ZGP_AttrReportCmd_t;
END_PACK
/******************************************************************************
                    ZGP device Attribute list 
******************************************************************************/
// Write Attribute command structures
typedef struct
{
    uint16_t                 clusterId;
    uint8_t                  lengthOfRecordList;
    ZGP_AttrReportField_t    attributeRecords[NO_OF_ATTR_RECORDS];
}ZGP_ClusterRecord_t;

typedef struct
{
    uint8_t                 options;
    uint16_t                manufacturerId;
    uint16_t                clusterId;
    uint8_t                 lengthOfRecordList;
    zgpAttrField_t          zgpAttrField;
}ZGP_WriteAttributeInd_t;

typedef struct
{
    uint16_t readAttributeId;
    uint8_t  readAttributeStatus;
    uint8_t  readAttributeDataType;
    uint16_t  readAttributeData;
}ZGP_ReadAttrRecField_t;

typedef struct
{
    uint8_t                cmdId;
    uint8_t                options;
    uint16_t               manufacturerID;
    uint16_t               clusterId;
    uint8_t                lengthOfRecList;
    ZGP_ReadAttrRecField_t zgpReadAttrRecField;
}ZGP_ReadAttrResponse_t;
/******************************************************************************
  \brief   The callback will be used to indicate the commissioning replies.
           
  \param   zgpInd - Zgp commissioning indication parameters
  \return  none.
******************************************************************************/
typedef void (*commissioningCallback_t)(ZGP_DataInd_t *zgpInd);

/******************************************************************************
                        Prototypes section.
******************************************************************************/\
/**************************************************************************//**
  \brief zgp internal Data request handler 
  \param none
  \return none.
******************************************************************************/
void zgpDataReqHandler(void);
/**************************************************************************//**
  \brief to request zgp to do data transmission 
  \param zgp_datareq - pointer to ZGP_DataReq_t structure which has inputs for data req
  \return none.
******************************************************************************/ 
ZGP_Status_t ZGP_DataReq(ZGP_DataReq_t *zgpDataReq);

void zgpTxReq(MAC_DataReq_t *reqParams);
#endif // ZGPDDATAHANDLER_H

// eof zgpdDataHandler.h
