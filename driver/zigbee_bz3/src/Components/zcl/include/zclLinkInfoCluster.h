/*******************************************************************************
  Zigbee Cluster Library Link Info Cluster Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zclLinkInfoCluster.h

  Summary:
    The header file describes the Link Info Cluster and its interface.

  Description:
    The header file describes the Link Info Cluster and its interface.
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

#ifndef _ZCLLINKINFOCLUSTER_H
#define _ZCLLINKINFOCLUSTER_H
/*******************************************************************************
                   Includes section
*******************************************************************************/
#include <zcl/include/zcl.h>
#include <zcl/include/clusters.h>
#include <sysRepeatMacro.h>

/*******************************************************************************
                   Define(s) section
*******************************************************************************/
/* Maximum amount of attributes */
#define ZCL_LINK_INFO_CLUSTER_CLIENT_SIDE_ATTRIBUTES_AMOUNT 7

/* Size of attribute value in octets */
#define ATTR_LENGTH 19

/* Link info cluster commands amount */
#define ZCL_LINK_INFO_COMMANDS_AMOUNT 1

/* Link Info cluster server side commands identifiers */
#define ZCL_LINK_INFO_CLUSTER_READY_TO_TRANSMIT_COMMAND_ID 0x00

/* Defines Attribute type */
#define ZCL_LINK_INFO_ATTRIBUTE(i, j) \
  DEFINE_ATTRIBUTE(linkInfo##j, ZCL_READONLY_ATTRIBUTE, j, ZCL_OCTET_STRING_DATA_TYPE_ID),

/* Cluster client side attributes */
#define ZCL_DEFINE_LINK_INFO_CLUSTER_CLIENT_ATTRIBUTES() \
  REPEAT_MACRO(ZCL_LINK_INFO_ATTRIBUTE, 0, ZCL_LINK_INFO_CLUSTER_CLIENT_SIDE_ATTRIBUTES_AMOUNT)

/* Cluster's commands */
#define ZCL_DEFINE_LINK_INFO_CLUSTER_COMMANDS(readyToTransmitInd)                            \
  DEFINE_COMMAND(readyToTransmitCommand, ZCL_LINK_INFO_CLUSTER_READY_TO_TRANSMIT_COMMAND_ID, \
    COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK),   \
    readyToTransmitInd)

/* Server side cluster's commands */
#define ZCL_DEFINE_LINK_INFO_SERVER_SIDE_CLUSTER_COMMANDS(readyToTransmitInd) \
  ZCL_DEFINE_LINK_INFO_CLUSTER_COMMANDS(readyToTransmitInd)

/* Client side cluster's commands */
#define ZCL_DEFINE_LINK_INFO_CLIENT_SIDE_CLUSTER_COMMANDS() \
  ZCL_DEFINE_LINK_INFO_CLUSTER_COMMANDS(NULL)

/* Cluster server side definition */
#define LINK_INFO_CLUSTER_ZCL_SERVER_CLUSTER_TYPE(clattributes, clcommands)                   \
{                                                                                             \
  .id = LINK_INFO_CLUSTER_ID,                                                                 \
  .options = {.type = ZCL_SERVER_CLUSTER_TYPE, .security = ZCL_NETWORK_KEY_CLUSTER_SECURITY}, \
  .attributesAmount = 0,                                            \
  .attributes = (uint8_t *)clattributes,                                                      \
  .commandsAmount = ZCL_LINK_INFO_COMMANDS_AMOUNT,                                            \
  .commands = (uint8_t *)clcommands                                                           \
}

/* Cluster client side definition */
#define LINK_INFO_CLUSTER_ZCL_CLIENT_CLUSTER_TYPE(clattributes, clcommands)                   \
{                                                                                             \
  .id = LINK_INFO_CLUSTER_ID,                                                                 \
  .options = {.type = ZCL_CLIENT_CLUSTER_TYPE, .security = ZCL_NETWORK_KEY_CLUSTER_SECURITY}, \
  .attributesAmount = ZCL_LINK_INFO_CLUSTER_CLIENT_SIDE_ATTRIBUTES_AMOUNT,                                                                      \
  .attributes = (uint8_t *)clattributes,                                                      \
  .commandsAmount = ZCL_LINK_INFO_COMMANDS_AMOUNT,                                            \
  .commands = (uint8_t *)clcommands                                                           \
}

/* Cluster definition */
#define DEFINE_LINK_INFO_CLUSTER(cltype, clattributes, clcommands) \
  LINK_INFO_CLUSTER_##cltype(clattributes, clcommands)

/* Defines attribute struct */
#define LINK_INFO_CLUSTER_ATTRIBUTE_STRUCT(i, j) \
  struct PACK                                    \
  {                                              \
    ZCL_AttributeId_t id;                        \
    uint8_t type;                                \
    uint8_t properties;                          \
    uint8_t value[ATTR_LENGTH];                  \
  } linkInfo##j;

/* Defines cluster's attribute set */
#define LINK_INFO_CLUSTER_ATTRIBUTES_SET() \
  REPEAT_MACRO(LINK_INFO_CLUSTER_ATTRIBUTE_STRUCT, 0, ZCL_LINK_INFO_CLUSTER_CLIENT_SIDE_ATTRIBUTES_AMOUNT)

/*******************************************************************************
                   Types section
*******************************************************************************/
BEGIN_PACK

/* Link Info cluster attribute type */
typedef struct PACK
{
  ZCL_AttributeId_t id;
  uint8_t type;
  uint8_t properties;
  uint8_t value[ATTR_LENGTH];
} ZclLinkInfoAttr_t;

/* Link Info cluster attribute value type.
   An attribute with string type shall contain its length in the
   first byte of the value field. */
typedef struct PACK
{
  uint8_t length;
  uint8_t payload[];
} ZclLinkInfoAttrValue_t;

/* Link Info cluster client side attributes */
typedef struct PACK
{
  LINK_INFO_CLUSTER_ATTRIBUTES_SET()
} ZCL_LinkInfoClusterClientAttributes_t;

/* Ready To Transmit command payload */
typedef struct PACK
{
  uint8_t boundDevicesAmount;
} ZCL_ReadyToTransmit_t;

END_PACK

/*Link Info cluster commands */
typedef struct
{
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t (*readyToTransmitCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ReadyToTransmit_t *payload);
  } readyToTransmitCommand;
} ZCL_LinkInfoClusterCommands_t;

#endif // #ifndef _ZCLLINKINFOCLUSTER_H

//eof zclLinkInfoCluster.h
