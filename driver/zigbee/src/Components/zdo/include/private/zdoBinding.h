/*******************************************************************************
  Zigbee device object binding Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zdoBinding.h

  Summary:
    This file contains the Internal interface of ZDO binding functionality.

  Description:
    This file contains the Internal interface of ZDO binding functionality.
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

#if !defined _ZDO_BINDING_H
#define _ZDO_BINDING_H

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
#if defined _BINDING_
/**************************************************************************//**
  \brief Prepare APS_DataReq_t structure for Bind/Unbind ZDP request.

  \param[in] zdpReq - the pointer to ZDP request for Bind (Unbind) request.
  \return None.
 ******************************************************************************/
ZDO_PRIVATE void zdoUnbindBindRequestCreate(ZDO_ZdpReq_t *const zdpReq);

/**************************************************************************//**
  \brief Process an incoming Bind or Unbind request and send response.

  \param[in] apsDataInd - pointer to APSDE-DATA indication structure of 
                          the received Mgmt Bind request command.
  \return None.
 ******************************************************************************/
ZDO_PRIVATE void zdoUnbindBindInd(const APS_DataInd_t *const apsDataInd);

/**************************************************************************//**
  \brief Prepare APS_DataReq_t structure for ZDP Mgmt Bind request.
  \param[in] zdpReq - the pointer to ZDP request's structure
                      for the Mgmt Bind Request.
  \return None.
 ******************************************************************************/
ZDO_PRIVATE void zdoMgmtBindRequestCreate(ZDO_ZdpReq_t *const zdpReq);

/**************************************************************************//**
  \brief Process an incoming Mgmt Bind request and send response.

  \param[in] apsDataInd - pointer to APSDE-DATA indication structure of 
                          the received Mgmt Bind request command.
  \return None.
 ******************************************************************************/
ZDO_PRIVATE void zdoMgmtBindInd(const APS_DataInd_t *const apsDataInd);

#endif /* _BINDING_ */
#endif /* _ZDO_BINDING_H */
/** eof zdoBinding.h */
