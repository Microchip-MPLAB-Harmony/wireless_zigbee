/*****************************************************************************
  \file consts.h

  \brief Common definitions set header file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  History:
    19/08/09 A. Kostyukov - Created
*****************************************************************************/
#ifndef CONST_H_
#define CONST_H_
/******************************************************************************
                             Definitions section
 ******************************************************************************/

#define R_LENGTH_FIELD_LENGTH          1
#define R_COMAND_ID_FIELD_LENGTH       2
#define MAX_NEIB_TABLE_SIZE            10

/******************************************************************************
                   Define(s) section
******************************************************************************/
#ifndef R_TEST_DRIVER_APP_DEVICE_ID
#define R_TEST_DRIVER_APP_DEVICE_ID             0x0000
#endif

#ifndef R_DEVICE_UNDER_TEST_APP_DEVICE_ID
#define R_DEVICE_UNDER_TEST_APP_DEVICE_ID       0xaaaa
#endif

#ifndef R_FULL_DEVICE_UNDER_TEST_APP_DEVICE_ID
#define R_FULL_DEVICE_UNDER_TEST_APP_DEVICE_ID  0xffff
#endif

#ifndef R_TEST_PROFILE_DEFAULT
#define R_TEST_PROFILE_DEFAULT               CCPU_TO_LE16(0x7f01)
#endif

#ifndef R_TEST_PROFILE_1
#define R_TEST_PROFILE_1                     R_TEST_PROFILE_DEFAULT
#endif

#ifndef R_TEST_PROFILE_2
#define R_TEST_PROFILE_2                     R_TEST_PROFILE_DEFAULT
#endif

#ifndef R_APP_DEVICE_ID
#define R_APP_DEVICE_ID                     CCPU_TO_LE16(R_FULL_DEVICE_UNDER_TEST_APP_DEVICE_ID)
#endif

#ifndef R_DURATION_BETWEEN_PACKETS
#define R_DURATION_BETWEEN_PACKETS          1000
#endif

#ifndef APP_INCOMING_COMMAND_BUFFERS_AMOUNT
#define APP_INCOMING_COMMAND_BUFFERS_AMOUNT   2
#endif

#ifndef APP_OUTCOMING_COMMAND_BUFFERS_AMOUNT
#define APP_OUTCOMING_COMMAND_BUFFERS_AMOUNT  3
#endif

#define BA_MEMORY_SLOTS_MAX                 (APP_OUTCOMING_COMMAND_BUFFERS_AMOUNT + \
                                            APP_INCOMING_COMMAND_BUFFERS_AMOUNT)
#ifdef APP_MAX_COMMAND_PAYLOAD_SIZE
#define BA_MEMORY_SLOT_SIZE                 APP_MAX_COMMAND_PAYLOAD_SIZE
#endif

#define R_MIN_NWK_DISC_PAYLOAD_SIZE         2
#define R_MAX_NETWORK_DESCRIPTORS           ((APP_MAX_COMMAND_PAYLOAD_SIZE - R_MIN_NWK_DISC_PAYLOAD_SIZE)/sizeof(NWK_NetworkDescriptor_t))

#ifndef _APS_MULTICAST_
#define APS_GROUP_ADDRESS                 0x01
#endif

#define R_TASK_TABLE_SIZE                   (R_PARSER_TASK_ID + 1)

#define R_COMMAND_ID_SIZE                   (sizeof(uint16_t))

#ifdef APP_MAX_ACTIVE_TRANSACTIONS_AMOUNT
#define R_MAX_ACTIVE_TRANSACTIONS_AMOUNT APP_MAX_ACTIVE_TRANSACTIONS_AMOUNT
#else
  #if APP_REDUCED_OTAU_SERVER == 1
    #define R_MAX_ACTIVE_TRANSACTIONS_AMOUNT    2
  #else
    #define R_MAX_ACTIVE_TRANSACTIONS_AMOUNT    4
  #endif /* APP_REDUCED_OTAU_SERVER */
#endif /* APP_MAX_ACTIVE_TRANSACTIONS_AMOUNT */

#endif /* CONST_H_ */
