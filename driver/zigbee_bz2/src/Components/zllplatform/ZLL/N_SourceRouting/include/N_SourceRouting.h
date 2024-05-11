/*******************************************************************************
  ZLL Source Routing Header File

  Company:
    Microchip Technology Inc.

  File Name:
    N_SourceRouting.h

  Summary:
    This file contains the ZLL Source Routing functions.

  Description:
    This file contains the ZLL Source Routing functions.
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


#ifndef N_SOURCEROUTING_H
#define N_SOURCEROUTING_H

/***************************************************************************************************
* INCLUDE FILES
***************************************************************************************************/

#include "infrastructure/N_Types/include/N_Types.h"
#if defined(_NWK_MANY_TO_ONE_ROUTING_) || defined(_NWK_ROUTE_CACHE_)
/***************************************************************************************************
* C++ DECLARATION WRAPPER
***************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************************************
* EXPORTED TYPES
***************************************************************************************************/

/* The maximum possible ammount of concurrent many to one route request requests. */
#ifndef N_MANYTOONEROUTE_REQUESTS_POOL_SIZE
  #define N_MANYTOONEROUTE_REQUESTS_POOL_SIZE 3u
#endif /* N_MANYTOONEROUTE_REQUESTS_POOL_SIZE */

typedef enum N_SourceRouting_Status_t
{
    N_SourceRouting_Status_Success,
    N_SourceRouting_Status_Failure,
    N_SourceRouting_Status_OutOfMemory,
    N_SourceRouting_Status_BufferFull,
    N_SourceRouting_Status_DiscoveryTableFull,
    N_SourceRouting_Status_RelayListTooLong,
} N_SourceRouting_Status_t;

typedef struct N_SourceRouting_Callback_t
{
#if defined _NWK_ROUTE_CACHE_
    /** Received a RouteRecord command.
        \param sourceAddress The network address from which the RouteRecord is received.
        \param relayListLength The length of the relayList.
        \param relayList A list of network addresses by which a unicast command to sourceAddress can be relayed.
    */
    void (*ReceivedRouteRecord)(uint16_t sourceAddress, uint8_t relayListLength, uint16_t relayList[]);

    /** Received a Network Status command with error code 'source route failure' (0x0B).
        \param originalDestinationAddress The destination address of the message which caused the failure.
        \param reporterAddress The network address from the device that reported the failure.
    */
    void (*SourceRouteFailed)(uint16_t originalDestinationAddress, uint16_t reporterAddress);
#endif /* _NWK_ROUTE_CACHE_ */

    /** Received a Network Status command with error code 'many to one route error' (0x0C).
        \param reporterAddress The network address from the device that reported the failure.
    */
    void (*ManyToOneRouteFailed)(uint16_t reporterAddress);

    /** Guard to ensure the initialiser contains all functions. */
    int8_t endOfList;

} N_SourceRouting_Callback_t;

/***************************************************************************************************
* EXPORTED MACROS AND CONSTANTS
***************************************************************************************************/


/***************************************************************************************************
* EXPORTED FUNCTIONS
***************************************************************************************************/

/** Initialise the event.
*/
void N_SourceRouting_Init(void);

/** Subscribe for callbacks from this component.
    \param pCallback Pointer to filled callback structure
*/
void N_SourceRouting_Subscribe(const N_SourceRouting_Callback_t* pCallback);

#if defined _NWK_ROUTE_CACHE_
/** Send a many to one route request, see ZigBee 2007 Specification 3.2.2.31.
    \param noRouteCache TRUE if no route record table should be established. Otherwise FALSE.
  *@retvals N_SourceRouting_Status_Success if the call succeeded.
*/
N_SourceRouting_Status_t N_SourceRouting_SendManyToOneRouteRequest(bool noRouteCache);

/** Set a relay list to use if a message is sent to the destination address.
    \param destinationAddress The destination address for which this relayList is used.
    \param relayListLength The length of the relayList.
    \param relayList A list of network addresses by which a unicast command to the destinationAddress is relayed through the network.
  *@retvals N_SourceRouting_Status_Success if the call succeeded.
*/
N_SourceRouting_Status_t N_SourceRouting_SetRelayList(uint16_t destinationAddress, uint8_t relayListLength, uint16_t relayList[]);

/** Clear a relay list for this destination address.
    \param destinationAddress The destination address for which this relayList should be cleared.
*/
void N_SourceRouting_ClearRelayList(uint16_t destinationAddress);
#endif /* _NWK_ROUTE_CACHE_ */

/***************************************************************************************************
* END OF C++ DECLARATION WRAPPER
***************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* _NWK_MANY_TO_ONE_ROUTING_ || _NWK_ROUTE_CACHE_ */
#endif // N_SOURCEROUTING_H
