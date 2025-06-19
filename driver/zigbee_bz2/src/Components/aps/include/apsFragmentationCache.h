// DOM-IGNORE-BEGIN
/*******************************************************************************
  APS Fragmentation Cache Header File

  Company
    Microchip Technology Inc.

  File Name
    apsFragmentationCache.h

  Summary
    Interface of APS fragmentation cache.

  Description
    This header file defines the interface to the APS fragmentation cache
    related functions.
 *******************************************************************************/


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

#if !defined APS_FRAGMENTATION_CACHE_H
#define APS_FRAGMENTATION_CACHE_H

#if defined _ZIGBEE_REV_23_SUPPORT_
/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <systemenvironment/include/sysTypes.h>

/******************************************************************************
                               Definitions section
 ******************************************************************************/
typedef uint16_t APS_FragmentationCacheAmount_t;

/******************************************************************************
                                Types section
 ******************************************************************************/

/* Type of fragmentation cache descriptor. */
typedef struct _ApsFragmentationCacheDescriptor_t
{
  /* Identifies the address of the destination device. */
  ExtAddr_t deviceAddress;
  /* Represents the fragmentation support for the destination device.*/
  bool fragmentationSupport;
  /* Represents the destination's max incoming transfer size. */
  uint16_t maxIncomingTxSize;
} ApsFragmentationCacheDescriptor_t;

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Init APS fragmentation cache.

  \param None.

  \return None.
 ******************************************************************************/
void APS_InitFragmentationCache(void);

/**************************************************************************//**
  \brief Update existing cache record or create a new cache record

  \param deviceAddress \ref Endian "[LE]" - pointer to extended IEEE
                                                device address.
         isFragmentationSupported - variable to represent whether fragmentation
                                     is supported or not
         transferUnitSize - maximum incoming transfer unit that the device
                             supports

  \return True - If the operations is successful
          False - If the table is full / if the incoming device address is 
                  invalid
 ******************************************************************************/
bool APS_UpdateFragmentationCacheDetails(const ExtAddr_t *const deviceAddress, bool isFragmentationSupported, uint16_t transferUnitSize);

/**************************************************************************//**
  \brief Delete existing cache record

  \param deviceAddress \ref Endian "[LE]" - pointer to extended IEEE
                                                device address.

  \return True - If the operations is successful.
          False - If the record is not found.
 ******************************************************************************/
bool APS_DeleteFragmentationCacheDetails(const ExtAddr_t *const deviceAddress);

#endif /* _ZIGBEE_REV_23_SUPPORT_ */

#endif /* APS_FRAGMENTATION_CACHE_H */