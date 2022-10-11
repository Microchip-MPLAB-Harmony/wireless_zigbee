/*****************************************************************************
  \file demo.h

  \brief Demo application header file: DimmerSwitch

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  History:
    22/12/10 A. Egorov - Created
*******************************************************************************/
#ifndef _DEMO_H
#define	_DEMO_H
/*******************************************************************************
                   Include section
*******************************************************************************/
#include <leds.h>

/*******************************************************************************
                   Defines section
*******************************************************************************/
#define APP_DEV_TYPE ZS_DEVICE_TYPE_ROUTER
#define APP_EXT_PANID 0x0000000000000000LL
#define APP_EXTENDED_ADDR 0x0000000000000003LL//2
#define APP_COORD_EXTENDED_ADDR 0x0000000000000001LL
#define APP_PERMIT_DURATION 0xFF
#define APP_KE_CLUSTER_ENDPOINT 0x0B
#define APP_TRUST_CENTER_ADDRESS 0x0000000000000001LL
#define APP_NETWORK_KEY           {0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc}
#define APP_LINK_KEY {0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb}//{0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa}
#define APP_ICERT_PUBLIC_KEY  {0x02,0x00,0xfd,0xe8,0xa7,0xf3,0xd1,0x08, \
                                     0x42,0x24,0x96,0x2a,0x4e,0x7c,0x54,0xe6, \
                                     0x9a,0xc3,0xf0,0x4d,0xa6,0xb8}
#define APP_ICERT_PRIVATE_KEY   {0x02,0x3c,0x46,0x7a,0x5c,0xea,0x6c,0xc3, \
                                       0x87,0x05,0x92,0x99,0xd1,0xb0,0x0d,0xde, \
                                       0xf8,0xaf,0xd7,0x41,0x6c}
#define APP_ICERT_CERTIFICATE   {0x03,0x07,0x40,0xb0,0x4c,0x50,0xf1,0x83, \
                                       0x59,0xd5,0x28,0xc7,0xab,0x12,0x9b,0x4d, \
                                       0x7f,0x52,0x5e,0x8e,0xf6,0xad,0x00,0x00, \
                                       0x00,0x00,0x00,0x00,0x00,0x02,0x54,0x45, \
                                       0x53,0x54,0x53,0x45,0x43,0x41,0x01,0x09, \
                                       0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
#define APP_DEVICE_DEVICE_ID HA_DIMMER_SWITCH_DEVICE_ID//0x5001 // meter device
#define APP_ENDPOINT 0x12//0x0B
#define APP_PROFILE_ID PROFILE_ID_HOME_AUTOMATION

/*******************************************************************************
                   Types section
*******************************************************************************/
enum
{
  APP_ZCL_START_FAILED            = 0x7100,
  APP_ZCL_SET_FAILED              = 0x7101,
  APP_SYS_SET_FAILED              = 0x7102,
  APP_DEV_TYPE_SET_FAILED         = 0x7103,
  APP_RESET_FAILED                = 0x7104,
  APP_ZCL_GET_FAILED              = 0x7105,
  APP_BINDING_FAILED              = 0x7106,
  APP_BINDMANAGER_0               = 0x7107,
  APP_BINDMANAGER_1               = 0x7108
};

/*****************************************************************************
                      Prototypes section
******************************************************************************/
void bindingConf(bool status);

/*****************************************************************************
                     Global variables section
******************************************************************************/
extern ClusterId_t inClusterList[];
extern ClusterId_t outClusterList[];
extern int inClusterCount;
extern int outClusterCount;
#endif	/* _DEMO_H */
