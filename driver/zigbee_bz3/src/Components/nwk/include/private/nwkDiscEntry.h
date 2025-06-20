/*******************************************************************************
  NWK Discovery Entry Header File

  Company:
    Microchip Technology Inc.

  File Name:
    nwkDiscEntry.h

  Summary:
    This file provides the Interface of the NWK Discovery Entry structure.

  Description:
    This file provides the Interface of the NWK Discovery Entry structure.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2024 Microchip Technology Inc. and its subsidiaries.
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

#ifndef NWK_DISC_ENTRY_H
#define NWK_DISC_ENTRY_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <nwk/include/nlmeNetworkDiscovery.h>
/******************************************************************************
                    Types section
******************************************************************************/

/* Type of size of the Discovery table. */
typedef uint8_t NwkSizeOfDiscoveryTable_t;

/**************************************************************************//**
\brief  specifies the structure of Discovery Table Entry
 *****************************************************************************/
typedef struct NwkDiscoveryTableEntry_t_
{
/* Extended PAN ID of the received beacon. */
  uint64_t extendedPANId;
/* channel of beacon reception. */
  uint8_t channel;
/* defines the parent priority of the beacon. */
  uint8_t parentPriority;
/* short address of the the beacon sender. */
  uint16_t shortAddr;
/* lqa of the beacon received. */
  uint8_t lqa;
/* Update ID of the beacon capacity. */
  uint8_t updateID;
#ifdef _ZIGBEE_REV_23_SUPPORT_
/* Beacon appendix information of the beacon. */
  NwkBeaconAppendix_t beaconAppendixTLV;
#endif //_ZIGBEE_REV_23_SUPPORT_
/* defines the end device capacity of the beacon. */
  bool endDeviceCapacity;
/*Introduced for internal purpose*/
  bool isEntryOccupied;
/* Beacon appendix information present flag */
  bool beaconAppendixPresent;
}NwkDiscoveryTableEntry_t;

/**************************************************************************//**
\brief  specifies the structure of Discovery table
 *****************************************************************************/
typedef struct NwkDiscoveryTable_t_
{
  /* The array of a discovery entry. */
  NwkDiscoveryTableEntry_t *table;
  /* Pointer to memory area after last entry of the discovery table. */
  NwkDiscoveryTableEntry_t *end;
  /* Current size of the discovery table. */
  NwkSizeOfDiscoveryTable_t size;
} NwkDiscoveryTable_t;

/**************************************************************************//**
  \brief Access function to the discovery table.
  \param [in] None.
  \return Pointer to the discovery table.
 ******************************************************************************/
NwkDiscoveryTable_t* NWK_GetDiscoveryTable(void);

/**************************************************************************//**
  \brief Function returns a pointer to memory area after last entry of the
    discovery table.
  \param [in] None.
  \return Pointer to the last entry of discovery table. 
 ******************************************************************************/
NwkDiscoveryTableEntry_t* NWK_DtEnd(void);

/**************************************************************************//**
  \brief Function return a total size of the discovery table.
  \param [in] None.
  \return Pointer to the size of discovery table.
 ******************************************************************************/
NwkSizeOfDiscoveryTable_t NWK_DtSize(void);

/**************************************************************************//**
  \brief First entry of the discovery table.
  \param [in] None.
  \return Pointer to the first entry of discovery table.
 ******************************************************************************/
NwkDiscoveryTableEntry_t* NWK_DtBegin(void);

#ifdef _ZIGBEE_REV_23_SUPPORT_
/**************************************************************************//**
  \brief Reset the discovery table.
  \param [in] None.
  \return None.
 ******************************************************************************/
void NWK_ResetDiscoveryTable(void);

/**************************************************************************//**
  \brief Reset the discovery table.
  \param[in] None.
  \return None.
 ******************************************************************************/
void NWK_ClearDiscoveryTable(void);
#endif //_ZIGBEE_REV_23_SUPPORT_
#endif /* NWK_DISC_ENTRY_H */