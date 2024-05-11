/** \file

$Id: N_TrustCenter.h 16461 2015-09-27 19:41:54Z rob.houtepen@philips.com $

Copyright (c) 2011 Koninklijke Philips N.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of Koninklijke Philips N.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of Koninklijke Philips N.V.
*/

#ifndef N_TRUSTCENTER_H
#define N_TRUSTCENTER_H

/***************************************************************************************************
* INCLUDE FILES
***************************************************************************************************/

#include "infrastructure/N_Types/include/N_Types.h"
#include "infrastructure/N_Address/include/N_Address.h"

/***************************************************************************************************
* C++ DECLARATION WRAPPER
***************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************************************
* EXPORTED TYPES
***************************************************************************************************/

/** UpdateDevice status field. See ZigBee r20 table 4.22 */
typedef enum N_TrustCenter_DeviceStatus_t
{
    N_TrustCenter_DeviceStatus_StandardSecuredRejoin = 0x00u,
    N_TrustCenter_DeviceStatus_StandardUnsecuredRejoin = 0x01u,
    N_TrustCenter_DeviceStatus_DeviceLeft = 0x02u,
    N_TrustCenter_DeviceStatus_StandardTrustCenterRejoin = 0x03u,
    N_TrustCenter_DeviceStatus_HighSecuritySecuredRejoin = 0x04u,
    N_TrustCenter_DeviceStatus_HighSecurityUnsecuredRejoin = 0x05u,
    N_TrustCenter_DeviceStatus_Reserved = 0x06u,
    N_TrustCenter_DeviceStatus_HighSecurityTrustCenterRejoin = 0x07u,
} N_TrustCenter_DeviceStatus_t;

/** Callbacks of this component. */
typedef struct N_TrustCenter_Callback_t
{
    /** APSME-UPDATE-DEVICE.indication (successfully decrypted and authenticated update-device command received)
        \param networkAddress The 16-bit network address of the device whose status is being updated
        \param ieeeAddress The extended 64-bit address of the device whose status is being updated
        \param parentNetworkAddress The 16-bit address of the device that shall be sent the update information
        \param deviceStatus Status of the device.
    */
    void (*ReceivedApsUpdateDevice)(uint16_t networkAddress, N_Address_Extended_t ieeeAddress, uint16_t parentNetworkAddress, N_TrustCenter_DeviceStatus_t deviceStatus);

    int8_t endOfList; // guard, should always be -1
} N_TrustCenter_Callback_t;

/***************************************************************************************************
* EXPORTED MACROS AND CONSTANTS
***************************************************************************************************/


/***************************************************************************************************
* EXPORTED FUNCTIONS
***************************************************************************************************/

/** Subscribe for events from this component.
*/
void N_TrustCenter_Subscribe(const N_TrustCenter_Callback_t* pSubscriber);

/** Transport the network key to an unauthorized device. Issues APSME-TRANSPORT-KEY.request() to the stack.
    \param networkAddress The 16-bit network address of the unauthorized device.
    \param ieeeAddress The IEEE address of the unauthorized device.
    \param parentNetworkAddress The network address of the parent of the to-be-unauthorized device.
*/
void N_TrustCenter_ApsTransportNetworkKey(uint16_t networkAddress, N_Address_Extended_t ieeeAddress, uint16_t parentNetworkAddress);


/***************************************************************************************************
* END OF C++ DECLARATION WRAPPER
***************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif // N_TRUSTCENTER_H
