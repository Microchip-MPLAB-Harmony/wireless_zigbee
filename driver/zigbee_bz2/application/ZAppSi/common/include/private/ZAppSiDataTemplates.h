/*******************************************************************************
  \file ZAppSiDataTemplates.h

  \brief Template structures to payload decoding

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  History:
    19/08/09 A. Kostyukov - Created
*******************************************************************************/

#ifndef ZAPPSIDATATEMPLATES_H_
#define ZAPPSIDATATEMPLATES_H_

BEGIN_PACK
typedef struct PACK
{
  uint8_t srcAddrMode;
  ShortAddr_t srcShortAddress;
  ExtAddr_t srcExtAddress;
  ProfileId_t srcProfileId;
  Endpoint_t srcEndpointId;
  ClusterId_t srcClusterId;
  uint8_t sequenceNumber;

  ClusterId_t clusterId;
  uint8_t direction;
  uint8_t commandId;
  uint8_t payload[1];
} RZclCommandIndication_t;
END_PACK

#endif /* ZAPPSIDATATEMPLATES_H_ */
