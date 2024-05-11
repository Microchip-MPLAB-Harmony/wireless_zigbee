/*******************************************************************************
  Zigbee device object node manager Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zdoNodeManager.h

  Summary:
    The header file describes the constants, types and internal interface
    of ZDO node manager.

  Description:
    The header file describes the constants, types and internal interface
    of ZDO node manager.

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

#if !defined _ZDO_NODE_MANAGER_H
#define _ZDO_NODE_MANAGER_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <aps.h>
#include <zdo.h>

/******************************************************************************
                               Defines section
 ******************************************************************************/

#define MGMT_LQI_REQ_SIZE 1
#define MGMT_LEAVE_REQ_SIZE 9
#define MGMT_PERMIT_JOINING_REQ_SIZE 2
#define MGMT_LQI_RESP_SIZE 3
#define MGMT_LEAVE_RESP_SIZE 0
#define MGMT_PERMIT_JOINING_RESP_SIZE 0
#define NEIGHBOR_TABLE_ENTRY_SIZE 22
#define MGMT_RTG_REQ_SIZE 1
#define MGMT_RTG_RESP_SIZE 3
#define ROUTING_TABLE_ENTRY_SIZE 5

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/******************************************************************************
  \brief Prepare ZDP request to be sent.
  \param[in] zdpReq - the pointer to the ZDP request's structure for
                      the Node ZDP request.
  \return None.
 ******************************************************************************/
ZDO_PRIVATE void zdoZdpNodeRequestCreate(ZDO_ZdpReq_t *zdpReq);

/******************************************************************************
  \brief Process ZDP Node Manager request.

  \param[in] apsDataInd - pointer to APSDE-DATA indication structure of
                          the received ZDP command.
  \return None.
 ******************************************************************************/
ZDO_PRIVATE void zdoZdpNodeMessageInd(const APS_DataInd_t *const apsDataInd);

#endif /* _ZDO_NODE_MANAGER_H */
/** eof zdoNodeManager.h */
