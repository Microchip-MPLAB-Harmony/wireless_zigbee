/*******************************************************************************
  APS group Header File

  Company
    Microchip Technology Inc.

  File Name
    apsGroup.h

  Summary
    Interface of APS Multicast Transmission.

  Description
    This header file defines the interface to APS multicast transmission.
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

#if !defined _APS_GROUP_H
#define _APS_GROUP_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <aps.h>
#include <private/apsMemoryManager.h>

#if defined _APS_MULTICAST_
/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/*****************************************************************************
  \brief Group indication (APSDE-DATA.indication) to all group members.

  \param[in] apsDataInd - pointer to APSDE-DATA.indication's parameters.
  \return None.
 *****************************************************************************/
APS_PRIVATE void apsGroupIndication(APS_DataInd_t *const apsDataInd);

/*****************************************************************************
  \brief Process multicast packets from NWK layer.

  \param[in] nwkDataInd - pointer to NLDE-DATA.indication parameters.
  \param[in] securityStatus - kind of used security.

  \return true  - response for NWK_DataInd requered,
          false - response for NWK_DataInd not required
                  and will be made in the future.
 *****************************************************************************/
APS_PRIVATE bool apsGroupPacketHandler(const NWK_DataInd_t *const nwkDataInd,
  const APS_Status_t securityStatus);

/*****************************************************************************
  \brief Process APSDE-DATA.request with Group Addressing Mode

  \param[in] apsDataReq - pointer to APSDE-DATA.request's parameters
  \param[in] apsBuffer - pointer to APS buffer with NLDE-DATA.request.

  \return APS_SUCCESS_STATUS
 *****************************************************************************/
APS_PRIVATE APS_Status_t apsProcessGroupAddrModeDataReq(APS_DataReq_t *apsDataReq,
  ApsDataBuffer_t *apsBuffer);

#endif /* _APS_MULTICAST_ */
#endif /* _APS_GROUP_H */
/** eof apsGroup.h */
