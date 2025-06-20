// DOM-IGNORE-BEGIN
/*******************************************************************************
  Zigbee green power device commissioning Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zgpdCommissioning.h

  Summary:
    This file contains the zgpd commissioning declarations.

  Description:
    This file contains the zgpd commissioning declarations.
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
#ifndef ZGPDCOMMISSIONING_H
#define ZGPDCOMMISSIONING_H
// DOM-IGNORE-END

/******************************************************************************
                    Includes section
 ******************************************************************************/
 
#include <zgp/GPDevice/include/zgpdCommon.h>
#include <zgp/GPDevice/include/zgpdSecurity.h>
#include <zgp/GPDevice/include/zgpdDataHandler.h>
#include <zgp/GPDevice/include/zgpdCommissioningHandler.h>
/******************************************************************************
                        Defines  section.
 ******************************************************************************/



/******************************************************************************
                        Types section.
 ******************************************************************************/
 
/** Key request or present; will be used in Commissioning Request */
typedef enum _zgpCommissioningKeyReq_t
{
  noKey,
  keyReq,
  keyPresent
}zgpCommissioningKeyReq_t;

/** Commissioning confirmation */
BEGIN_PACK
typedef struct _ZGP_CommissionConf_t
{
  ZGP_Status_t status;
}ZGP_CommissionConf_t;
END_PACK

/** Success GPDF confirmation */
BEGIN_PACK
typedef struct _ZGP_SuccessGpdfConf_t
{
  ZGP_Status_t status;
}ZGP_SuccessGpdfConf_t;
END_PACK

/** Decommissioning confirmation */
BEGIN_PACK
typedef struct _ZGP_DecommissioningConf_t
{
  ZGP_Status_t status;
}ZGP_DecommissioningConf_t;
END_PACK

/** Commissioning Request parameters */
BEGIN_PACK
typedef struct _ZGP_CommissioningReq_t
{
  ZGP_Service_t service;
  ZGP_DeviceId_t deviceId;
  bool panIdReq;
  bool keyReq;
  bool keyEnc;
  bool fixedLocation;
  void (*ZGP_CommissionConf)(ZGP_CommissionConf_t *conf);
  ZGP_CommissionConf_t confirm;  
}ZGP_CommissioningReq_t;
END_PACK

/** Success GPDF Request parameters */
BEGIN_PACK
typedef struct _ZgpSuccessGpdfReq_t
{
  ZGP_Service_t service;
  void (*ZGP_SuccessGpdfConf)(ZGP_SuccessGpdfConf_t *conf);
  ZGP_SuccessGpdfConf_t confirm;
}ZgpSuccessGpdfReq_t;
END_PACK

/** Decommissioning Request parameters */
BEGIN_PACK
typedef struct _ZGP_DecommissioningReq_t
{
  ZGP_Service_t service;
  void (*ZGP_DecommissioningConf)(ZGP_DecommissioningConf_t *conf);
  ZGP_DecommissioningConf_t confirm;
}ZGP_DecommissioningReq_t;
END_PACK


/******************************************************************************
                            Globals
 ******************************************************************************/


/******************************************************************************
                        Prototypes section.
 ******************************************************************************/

/***************************************************************************//**
  \brief    This will initiate the commissioning request command
  \param    panIdReq - panId required
            keyReq - key required/none
            keyEnc - device has capability to encrypt/decrypt the key
            key - which will be shared with sink
            ZGP_CommissionConf - commissioning confirmation callback
            confirm - confirmation status
  \return   None.
 ******************************************************************************/
ZGP_Status_t ZGP_CommissionReq(ZGP_CommissioningReq_t *commReq);

/***************************************************************************//**
  \brief    This will initiate the commissioning request command
  \param    callback - commissioning confirmation callback
  \return  None.
 ******************************************************************************/
ZGP_Status_t ZGP_SendCommissioningReq(zgpCommissioningCmdConf callback);

/***************************************************************************//**
  \brief   This subscription will be used to register a commissioning callback,
              which will be used in Bidirectional commissioning
  \param   commissioningCB - Zgp commissioning callback
  \return  None.
 ******************************************************************************/
ZGP_Status_t ZGP_SubscribeCommissioning(commissioningCallback_t zgpCommissioningCB);

/***************************************************************************//**
  \brief   This unsubscription will be used to deregister a commissioning  callback, which will be used in Bidirectional commissioning
  \param   None.
  \return  None.
 ******************************************************************************/
void ZGP_UnsubscribeCommissioning(void);

/***************************************************************************//**
  \brief    This will initiate the success GPDF command
            key - which will be used for Success gpdf encription
            ZGP_SuccessGpdfConf - Success gpdf confirmation callback
            confirm - confirmation status
  \param None
  \return  None.
 ******************************************************************************/
ZGP_Status_t ZGP_SuccessGpdfReq(ZgpSuccessGpdfReq_t *zgpSuccessReq);

/**************************************************************************//**
  \brief    This will initiate the success GPDF command
            key - which will be used for Success gpdf encription
            ZGP_SuccessGpdfConf - Success gpdf confirmation callback
            confirm - confirmation status
  \param None
  \return  None.
 ******************************************************************************/
ZGP_Status_t ZGP_DecommissioningReq(ZGP_DecommissioningReq_t *zgpDecommissioningReq);


#endif //ZGPDCOMMISSIONING_H
//eof zgpdCommissioning.h
