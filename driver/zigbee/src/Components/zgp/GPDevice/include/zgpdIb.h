/*******************************************************************************
  Zigbee green power device Information base Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdIb.h

  Summary:
    This file contains the Zgp device information base and access.

  Description:
    This file contains the Zgp device information base and access.
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

#ifndef _ZGPDIB_H_
#define _ZGPDIB_H_
/******************************************************************************
                                  Header Files
******************************************************************************/
#include <systemenvironment/include/sysTypes.h>
#include <configserver/include/configserver.h>
#include <mac_phy/include/macAddr.h>
#include <zgp/GPDevice/include/zgpdSecurity.h>
#include <zgp/GPDevice/include/zgpdCommissioningHandler.h>
#include <zgp/GPDevice/include/zgpdChannelConfig.h>

/******************************************************************************
                               ZGP Data Structures
******************************************************************************/
typedef struct _ZgpDeviceParams_t
{
  ExtAddr_t ieeeAddr;                        //IEEE address; will be used when Application ID = 0b010
  uint32_t srcID;                            //4B source id; will be used when Application ID = 0b000
  ZGP_ApplicationId_t appId;                 //Application ID, defines whether to
  uint8_t endPoint;                          //Endpoint
  ZGP_SecLevel_t secLevel;                   //Security level
  bool useIncSeqNum;                         //States usage of incremental sequence number
  bool useCsmaCA;                            //States usage of CSMA-CA
  uint8_t commissioningType;                 //Type of commissioning used
  bool rxAfterTx;                            //States usage of RxAfterTx
  uint32_t rxWindow;                         //duration of the reception window of an Rx-capable ZGPD
}zgpDeviceParams_t;

typedef struct _ZgpStackParams_t
{
  uint16_t panId;                            //PANId of the ZigBee network in which this device associated
  uint8_t Channel;                           //Operating channel of the device
  uint16_t identicalFrameTxDelay;            //time interval to be kept between consecutive frames in the sequence 
  uint8_t numOfFramesInSeq;                  //Number of frames in ZGP frame sequence
  zgpChannelConfigState_t   channelConfigState;  //channelConfigState
  zgpCommissionState_t      commissioningState;  //CommissioningState
  zgpCommissioningEvents_t  commissioningEvent;  //CommissioningEvent
}zgpStackParams_t;

/* ZGPD Information Base */
typedef struct _ZgpIb_t
{
  bool zgpdSpecific;
  zgpDeviceParams_t deviceParams;
  zgpStackParams_t stackparams;
#ifdef ZGP_SECURITY_ENABLE
  zgpdSecMaterialSet_t secParams;
#endif //ZGP_SECURITY_ENABLE
}ZGIB_t;

/******************************************************************************
                    Extern variables section
******************************************************************************/
extern ZGIB_t csZGIB;
extern uint8_t macSeqNo;
extern bool isFactoryNew;
/******************************************************************************
                                 ZGP Macros
******************************************************************************/

#define ZGP_SECURITY_OUTGOING_FRAMECNTR_WINDOW_SIZE 512
#define ZGP_MAC_SEQ_WINDOW_SIZE 64
/******************************************************************************
                          Functions prototypes section
******************************************************************************/
void zgpResetZgib(void);
/**************************************************************************//**
  \brief Reset to factory new
  \param none
  \return none
******************************************************************************/
void setFactoryNew(bool factoryNew);

/**************************************************************************//**
  \brief To set the source ID in device params
  \param uint32_t - newSrcID
  \return none
******************************************************************************/
void setSrcID(uint32_t newSrcID);

/**************************************************************************//**
  \brief To set IeeeAddr in device params
  \param newIeeeAddr
  \return none
******************************************************************************/
void setIeeeAddr(ExtAddr_t newIeeeAddr);

/**************************************************************************//**
  \brief To set endPoint in device params
  \param newEndPoint
  \return none
******************************************************************************/
void setEndPoint(uint8_t endPoint);

#ifdef _COMMISSIONING_ 
/**************************************************************************//**
  \brief Restore all the zgp parameters from NVM
  \param none
  \return none
******************************************************************************/
void restoreAllParamsFromNvm(void);
#endif

/**************************************************************************//**
  \brief check for factory new status
  \param none
  \return bool FN/NFN status
******************************************************************************/
bool ZGP_IsDeviceFactoryNew(void);

#ifdef ZGP_SECURITY_ENABLE
/**************************************************************************//**
  \brief Increment and store outgoing frame counter
  \param none
  \return none
******************************************************************************/
void incAndStoreOutgngFrameCntr(void);
#endif

inline zgpDeviceParams_t *zgpGetDeviceParams(void)
{
  return(&csZGIB.deviceParams);
}

inline zgpStackParams_t *zgpGetStackParams(void)
{
  return(&csZGIB.stackparams);
}
#ifdef ZGP_SECURITY_ENABLE
inline zgpdSecMaterialSet_t *zgpGetSecParams()
{
  return(&csZGIB.secParams);
}
#endif //ZGP_SECURITY_ENABLE

#endif /*_ZGPDIB_H_*/
//eof zgpdIb.h
