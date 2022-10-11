/*******************************************************************************
  IAS-ACE Cluster Header File

  Company:
    Microchip Technology Inc.

  File Name:
   asACECluster.h

  Summary:
    This file contains the IAS-ACE Cluster interface.

  Description:
    This file contains the IAS-ACE Cluster interface.
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

#ifndef _IASACEACECLUSTER_H
#define _IASACEACECLUSTER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <zcl/include/zcl.h>
#include <zcl/include/zclIasACECluster.h>

/******************************************************************************
                    Definition(s) section
******************************************************************************/
extern ZCL_IasAceClusterClientAttributes_t iasACEAceClusterClientAttributes;
/******************************************************************************
                    Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Initializes IAS ACE cluster
******************************************************************************/
void iasACEClusterInit(void);

/**************************************************************************//**
 \brief ACEArmCommand Command
 \param mode - Adress Mode
 \param ep  -  Endpoint of the device
 \param[in] srcEp- source endpoint;
 \param arm -  ARM mode
 \return none
******************************************************************************/
void aceArmCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep , Endpoint_t srcEp, uint8_t arm_mode , char *code , uint8_t zoneid);

/**************************************************************************//**
 \brief GetByPassZoneList Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param[in] srcEp- source endpoint;
 \return none
******************************************************************************/
void getByPassZoneListCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp);

/**************************************************************************//**
 \brief aceByPass Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param[in] srcEp- source endpoint;
 \param zone_numbers -  total zones
 \param zoneId(s) -  index of the zone table
 \return none
******************************************************************************/
void aceByPassCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp, uint8_t zoneNumbers, uint8_t *zone_id, char *armDisarmCode);

/**************************************************************************//**
 \brief aceEmergency Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param[in] srcEp- source endpoint;
 \return none
******************************************************************************/
void aceEmergencyCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp);

/**************************************************************************//**
 \brief aceFire Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param[in] srcEp- source endpoint;
 \return none
******************************************************************************/
void aceFireCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp);

/**************************************************************************//**
 \brief acePanic Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param[in] srcEp- source endpoint;
 \return none
******************************************************************************/
void acePanicCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp);

/**************************************************************************//**
 \brief aceGetZoneInformation Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param[in] srcEp- source endpoint;
 \param zoneId - zoneId offset
 \return none
******************************************************************************/
void aceGetZoneInformationCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp, uint8_t zoneId);

/**************************************************************************//**
 \brief aceGetZoneIdMap Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \return none
******************************************************************************/
void aceGetZoneIdMapCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp);

/**************************************************************************//**
 \brief aceGetPanelStatus Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param[in] srcEp- source endpoint;
 \return none
******************************************************************************/
void aceGetPanelStatusCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp);

/**************************************************************************//**
 \brief aceGetZoneStatus Command
 \param mode - Adress Mode
 \param addr - short addr
 \param ep  -  Endpoint of the device
 \param[in] srcEp- source endpoint;
 \param startingZoneId - starting of the zoneId offset
 \param maxNumberZoneids - maximum zoneIdss
 \param zoneStatusMaskFlag - mask flag
 \param zoneStatusMask - status of the zone
 \return none
******************************************************************************/
void aceGetZoneStatusCommand(APS_AddrMode_t mode, ShortAddr_t addr, Endpoint_t ep, Endpoint_t srcEp, uint8_t startingZoneId, uint8_t maxNumberZoneids, uint8_t zoneStatusMaskFlag, uint16_t zoneStatusMask);
#endif // _IASACECLUSTER_H

// eof iasACECluster.h
