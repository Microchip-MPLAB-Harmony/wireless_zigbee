/*******************************************************************************
  TrustCentre Device Table Control Header File

  Company:
    Microchip Technology Inc.

  File Name:
    tcDeviceTableCtrl.h

  Summary:
    This file contains the Security Trust Centre devices' control declarations.

  Description:
    This file contains the Security Trust Centre devices' control declarations.
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


#ifndef _TCDEVICETABLECTRLH
#define _TCDEVICETABLECTRLH

/******************************************************************************
                             Includes section.
******************************************************************************/
#include <systemenvironment/include/sysTypes.h>
#include <mac_phy/include/mac.h>
#include <aps/include/aps.h>
#include <security/serviceprovider/include/sspCommon.h>

#ifdef _PERMISSIONS_
/******************************************************************************
                             Functions prototypes section.
******************************************************************************/
/**************************************************************************//**
  \brief Adds new device to Trust Centre device permission table.

  \param extAddr - new device's address.
  \return true in case if operation is successful - false if there is no free
  space in Trust Centre device permission table.
******************************************************************************/
bool TC_AddDeviceToPermissionTable(ExtAddr_t *extAddr);


/**************************************************************************//**
  \brief Removes device from Trust Centre device permission table.

  \param extAddr - address of the device to remove.
  \return true in case if operation is successful - false if there is no such
  device in Trust Centre device permission table.
******************************************************************************/
bool TC_RemoveDeviceFromPermissionTable(ExtAddr_t *extAddr);
#endif // _PERMISSIONS_

/******************************************************************************
                             Types section.
******************************************************************************/
/**************************************************************************//**
  \brief Possible key types which could be stored for each device.

   Used in TC_SetDeviceKey primitive - to fill device table with particular
   values.
******************************************************************************/
typedef enum
{
  //! Master key type.
  KEY_TYPE_MASTER,
  //! Link key type.
  KEY_TYPE_LINK
} TC_KeyType_t;

/**************************************************************************//**
  \brief Trust Centre set device key primitive paramemtrs.

   Used in TC_SetDeviceKey primitive - to fill device table with particular
   values.
******************************************************************************/
typedef struct
{
  //! Device extended address.
  ExtAddr_t    *deviceAddr;
  //! Key value - 16 bytes array.
  uint8_t      (*key)[SECURITY_KEY_SIZE];
  //! Key type.
  TC_KeyType_t keyType;
} TC_SetDeviceKey_t;

/******************************************************************************
                             Functions prototypes section.
******************************************************************************/
/**************************************************************************//**
  \brief Sets device parameters in device table - extended address associated
  with particular key.

  \param params -  request parameters' structure pointer.
  \return true in case if operation is successful - false otherwise.
******************************************************************************/
bool TC_SetDeviceKey(TC_SetDeviceKey_t *param);

/**************************************************************************//**
  \brief Deletes whole information about device with extended address equeal to
         deviceAddr from APS_KeyPairSet_t table.
  \param deviceAddr - device address.

  \return true - if device with extended address deviceAddr was found and its
          entry was deleted, false - otherwise.
******************************************************************************/
bool TC_DeleteDeviceEntry(ExtAddr_t *deviceAddr);

#endif // _TCDEVICETABLECTRLH

// eof tcDeviceTableCtrl.h
