/*******************************************************************************
  Zigbee device object parent announce Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zdoParentAnnounce.h

  Summary:
    This file contains the Internal interface of ZDO Parent Announce module.

  Description:
    This file contains the Internal interface of ZDO Parent Announce module.
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

#if !defined _ZDO_PARENT_ANNCE_H
#define _ZDO_PARENT_ANNCE_H

#ifdef _PARENT_ANNCE_

/******************************************************************************
                                Includes section
 ******************************************************************************/

/******************************************************************************
                               Definition section
 ******************************************************************************/

/******************************************************************************
                                 Types section
 ******************************************************************************/

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
void zdoSendParentAnnceTimerFired(void);
void zdoSetupParentAnnce(void);
void zdoTearParentAnnce(void);
void zdoSendParentAnnce(void (*parentAnnceConf)(ZDO_ZdpResp_t *zdpResp), ZdoCommand_t *const zdoCommand);
uint8_t ZDO_GetEndDevices(ZDO_ParentAnnceReq_t *parentAnnounce, bool ParentAnnceReq);
void zdoParentAnnceInd(const APS_DataInd_t *const apsDataInd);
void zdoPrepareParentAnnceRsp(const APS_DataInd_t *const apsDataInd, ZdoCommand_t *const zdoCommand);
void zdoSendParentAnnceRsp(void (*parentAnnceConf)(ZDO_ZdpResp_t *zdpResp));

typedef struct
{
  ZdoCommand_t *zdoCommand;
  uint8_t lastNeighbor;
  bool moreNeighbor;
  bool isTimerRunning;
}ParentAnnceReqCtrl_t;



#endif /* _PARENT_ANNCE_ */
#endif /* _ZDO_PARENT_ANNCE_H */
/** eof zdoParentAnnounce.h */
