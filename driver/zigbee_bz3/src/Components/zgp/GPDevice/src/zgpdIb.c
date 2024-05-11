/*******************************************************************************
  Zigbee green power device Information base Source File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdIb.c

  Summary:
    This file contains the implementation of zgpd information base.

  Description:
    This file contains the implementation of zgpd information base.
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

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zgp/GPDevice/include/zgpdMem.h>
#include <mac_phy/include/mac.h>
/******************************************************************************
                    Define(s) section
******************************************************************************/

/******************************************************************************
                    Types section
******************************************************************************/
/******************************************************************************
                    Extern variables section
******************************************************************************/
extern ZGIB_t csZGIB;
/******************************************************************************
                    Constants section
******************************************************************************/

/******************************************************************************
                    Prototypes section
******************************************************************************/
/******************************************************************************
                    Static functions prototypes section
******************************************************************************/

/******************************************************************************
                    Global variables section
******************************************************************************/
// By default it is FN
// On powerOn, It is restored from NVM
bool isFactoryNew = true;

/******************************************************************************
                    Implementations section
******************************************************************************/
/**************************************************************************//**
  \brief to reset all configuration parameters of dStub
  \param none
  \return none
******************************************************************************/
void zgpResetZgib(void)
{
  zgpGetDeviceParams()->srcID = CCPU_TO_LE64(CS_ZGP_SRCID);
  zgpGetDeviceParams()->appId = CS_ZGP_APPID;
  zgpGetDeviceParams()->commissioningType = CS_ZGP_COMMISSIONING_TYPE;
  zgpGetDeviceParams()->useIncSeqNum = CS_ZGP_USE_INC_SEQ_NUM;
  zgpGetDeviceParams()->useCsmaCA = CS_ZGP_USE_CSMA_CA;
  zgpGetStackParams()->numOfFramesInSeq = CS_ZGP_NO_OF_FRAMES_IN_SEQ;
  findNextSupportedChannel(&zgpGetStackParams()->Channel,CS_CHANNEL_MASK);
  zgpGetDeviceParams()->rxAfterTx = CS_ZGP_RX_AFTER_TX;
  zgpGetDeviceParams()->secLevel = CS_ZGP_SECURITY_LEVEL;
  zgpGetDeviceParams()->ieeeAddr = CS_UID;
#ifdef ZGP_SECURITY_ENABLE
  zgpGetSecParams()->secKey.keyType = CS_ZGP_SECURITY_KEY_TYPE;
#endif //ZGP_SECURITY_ENABLE

  setCommissioningState(sCommIdle);
}

/**************************************************************************//**
  \brief To reset to factory new
  \param factorynew - To set FN or NFN
  \return none
******************************************************************************/
void setFactoryNew(bool factoryNew)
{
  isFactoryNew = factoryNew;
#ifdef _COMMISSIONING_
  PDS_Store(ZGP_FACTORYNEW_MEM_ID);
#ifdef _ENABLE_PERSISTENT_SERVER_
  PDS_DeleteAll(false);
#endif
#endif
}

/**************************************************************************//**
  \brief To set the source ID in device params
  \param uint32_t - newSrcID
  \return none
******************************************************************************/
void setSrcID(uint32_t newSrcID)
{
  zgpGetDeviceParams()->srcID = newSrcID;
#ifdef _COMMISSIONING_
  PDS_Store(ZGP_DEVICEPARAMS_MEM_ID);
#endif
}

/**************************************************************************//**
  \brief To set IeeeAddr in device params
  \param newIeeeAddr
  \return none
******************************************************************************/
void setIeeeAddr(ExtAddr_t newIeeeAddr)
{
  zgpGetDeviceParams()->ieeeAddr = newIeeeAddr;
#ifdef _COMMISSIONING_
  PDS_Store(ZGP_DEVICEPARAMS_MEM_ID);
#endif
}

/**************************************************************************//**
  \brief To set endPoint in device params
  \param newEndPoint
  \return none
******************************************************************************/
void setEndPoint(uint8_t endPoint)
{
  zgpGetDeviceParams()->endPoint = endPoint;
#ifdef _COMMISSIONING_
  PDS_Store(ZGP_DEVICEPARAMS_MEM_ID);
#endif
}

#ifdef _COMMISSIONING_
/**************************************************************************//**
  \brief Restore all the zgp parameters from NVM
  \param none
  \return none
******************************************************************************/
void restoreAllParamsFromNvm(void)
{
  PDS_Restore(ZGP_STACKPARAMS_MEM_ID);
#ifdef ZGP_SECURITY_ENABLE
  PDS_Restore(ZGP_SECURITYKEYS_MEM_ID);
  if (PDS_Restore(ZGP_OUTGOINGFRAMECOUNTER_MEM_ID))
  {
    zgpGetSecParams()->outFrmCntr += ZGP_SECURITY_OUTGOING_FRAMECNTR_WINDOW_SIZE;
  }
#endif
  PDS_Restore(ZGP_DEVICEPARAMS_MEM_ID);
  PDS_Store(ZGP_COUNTERS_ID);
}
#endif

/**************************************************************************//**
  \brief check for factory new status
  \param none
  \return bool FN/NFN status
******************************************************************************/
bool ZGP_IsDeviceFactoryNew(void)
{
  return isFactoryNew;
}

#ifdef ZGP_SECURITY_ENABLE
/**************************************************************************//**
  \brief Increment and store outgoing frame counter
  \param none
  \return none
******************************************************************************/
void incAndStoreOutgngFrameCntr(void)
{
  zgpGetSecParams()->outFrmCntr++;
#ifdef _COMMISSIONING_
  if (!(zgpGetSecParams()->outFrmCntr % ZGP_SECURITY_OUTGOING_FRAMECNTR_WINDOW_SIZE))
    PDS_Store(ZGP_OUTGOINGFRAMECOUNTER_MEM_ID);
#endif  
}

#endif
//eof zgpIb.c



