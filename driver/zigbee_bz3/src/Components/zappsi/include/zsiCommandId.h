/*******************************************************************************
  ZAppSI Commands ID Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zsiCommandId.h

  Summary:
    This file contains the ZAppSI command identifiers.

  Description:
    This file contains the ZAppSI command identifiers.
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


#ifndef _ZSICOMMANDID_H
#define _ZSICOMMANDID_H

/******************************************************************************
                              Defines section
******************************************************************************/

/* SYS domain */
#define ZSI_SYS_READ_PARAMETER_REQUEST  0x00U
#define ZSI_SYS_READ_PARAMETER_CONFIRM  0x01U
#define ZSI_SYS_WRITE_PARAMETER_REQUEST 0x02U
#define ZSI_SYS_WRITE_PARAMETER_CONFIRM 0x03U
#define ZSI_SYS_POST_EVENT_REQUEST      0x04U
#define ZSI_SYS_POST_EVENT_CONFIRM      0x05U
#define ZSI_SYS_POWER_OFF_REQUEST       0x06U
#define ZSI_SYS_POWER_OFF_CONFIRM       0x07U

/* APS domain */
#define ZSI_APS_REGISTER_ENDPOINT_REQUEST              0x00U
#define ZSI_APS_REGISTER_ENDPOINT_CONFIRM              0x01U
#define ZSI_APS_DATA_INDICATION                        0x02U
#define ZSI_APS_DATA_REQUEST                           0x03U
#define ZSI_APS_DATA_CONFIRM                           0x04U
#define ZSI_APS_SET_LINK_KEY_REQUEST                   0x05U
#define ZSI_APS_SET_LINK_KEY_CONFIRM                   0x06U
#define ZSI_APS_GET_LINK_KEY_REQUEST                   0x07U
#define ZSI_APS_GET_LINK_KEY_CONFIRM                   0x08U
#define ZSI_APS_FIND_KEYS_REQUEST                      0x09U
#define ZSI_APS_FIND_KEYS_CONFIRM                      0x0AU
#define ZSI_APS_BIND_REQUEST                           0x0BU
#define ZSI_APS_BIND_CONFIRM                           0x0CU
#define ZSI_APS_GET_KEY_PAIR_DEV_ADDR_REQUEST          0x0DU
#define ZSI_APS_GET_KEY_PAIR_DEV_ADDR_CONFIRM          0x0EU
#define ZSI_APS_NEXT_KEYS_REQUEST                      0x0FU
#define ZSI_APS_NEXT_KEYS_CONFIRM                      0x10U
#define ZSI_APS_MARK_TC_KEY_REQUEST                    0x11U
#define ZSI_APS_MARK_TC_KEY_CONFIRM                    0x12U
#define ZSI_APS_SET_AUTHORIZED_STATUS_REQUEST          0x13U
#define ZSI_APS_SET_AUTHORIZED_STATUS_CONFIRM          0x14U
#define ZSI_APS_SET_DEFAULT_KEY_PAIR_STATUS_REQUEST    0x15U
#define ZSI_APS_SET_DEFAULT_KEY_PAIR_STATUS_CONFIRM    0x16U
#define ZSI_APS_ARE_KEYS_AUTHORIZED_REQUEST            0x17U
#define ZSI_APS_ARE_KEYS_AUTHORIZED_CONFIRM            0x18U
#define ZSI_APS_GET_TRUST_CENTRE_ADDRESS_REQUEST       0x19U
#define ZSI_APS_GET_TRUST_CENTRE_ADDRESS_CONFIRM       0x1AU
#define ZSI_APS_NEXT_BINDING_ENTRY_REQUEST             0x1BU
#define ZSI_APS_NEXT_BINDING_ENTRY_CONFIRM             0x1CU
#define ZSI_TC_SET_ALLOW_INSTALL_CODES_REQUEST         0x1DU
#define ZSI_TC_SET_ALLOW_INSTALL_CODES_CONFIRM         0x1EU

#define ZSI_APS_GET_OWN_TCMODE_REQUEST                 0x1FU
#define ZSI_APS_GET_OWN_TCMODE_CONFIRM                 0x20U
#define ZSI_APS_UPDATE_SECURITY_POLICY_REQUEST         0x21U
#define ZSI_APS_UPDATE_SECURITY_POLICY_CONFIRM         0x22U
#define ZSI_APS_UNBIND_REQUEST                         0x23U
#define ZSI_APS_UNBIND_CONFIRM                         0x24U
#define ZSI_APS_FREE_BINDING_ENTRY_REQUEST             0x25U
#define ZSI_APS_FREE_BINDING_ENTRY_CONFIRM             0x26U
#define ZSI_APS_SET_TRUST_CENTER_ADDRESS_REQUEST       0x27U
#define ZSI_APS_SET_TRUST_CENTER_ADDRESS_CONFIRM       0x28U
#define ZSI_APS_IS_BOUND_TO_ANY_GROUP_REQUEST          0x29U
#define ZSI_APS_IS_BOUND_TO_ANY_GROUP_CONFIRM          0x2AU
#define ZSI_APS_INIT_KEYPAIR_SET_REQUEST               0x2BU
#define ZSI_APS_INIT_KEYPAIR_SET_CONFIRM               0x2CU
/* ZDO domain */
#define ZSI_ZDO_START_NETWORK_REQUEST  0x00U
#define ZSI_ZDO_START_NETWORK_CONFIRM  0x01U
#define ZSI_ZDO_RESET_NETWORK_REQUEST  0x02U
#define ZSI_ZDO_RESET_NETWORK_CONFIRM  0x03U
#define ZSI_ZDO_MGMT_NWK_UPDATE_NOTIFY 0x04U
#define ZSI_ZDO_GET_LQI_RSSI_REQUEST   0x05U
#define ZSI_ZDO_GET_LQI_RSSI_CONFIRM   0x06U
#define ZSI_ZDO_SLEEP_REQUEST          0x07U
#define ZSI_ZDO_SLEEP_CONFIRM          0x08U
#define ZSI_ZDO_WAKEUP_INDICATION      0x09U
#define ZSI_ZDO_BIND_INDICATION        0x0AU
#define ZSI_ZDO_UNBIND_INDICATION      0x0BU
#define ZSI_ZDO_START_SYNC_REQUEST     0x0CU
#define ZSI_ZDO_START_SYNC_CONFIRM     0x0DU
#define ZSI_ZDO_STOP_SYNC_REQUEST      0x0EU
#define ZSI_ZDO_STOP_SYNC_CONFIRM      0x0FU
#define ZSI_ZDO_NETWORK_STATUS_REQUEST 0x10U
#define ZSI_ZDO_NETWORK_STATUS_CONFIRM 0x11U
#define ZSI_ZDO_FIND_EXT_BY_SHORT_REQUEST  0x12U
#define ZSI_ZDO_FIND_EXT_BY_SHORT_CONFIRM  0x13U

/* ZDP domain */
#define ZSI_ZDP_MATCH_DESCRIPTOR_REQUEST  0x00U
#define ZSI_ZDP_MATCH_DESCRIPTOR_RESPONSE 0x01U
#define ZSI_ZDP_IEEE_ADDRESS_REQUEST      0x02U
#define ZSI_ZDP_IEEE_ADDRESS_RESPONSE     0x03U
#define ZSI_ZDP_BIND_REQUEST              0x04U
#define ZSI_ZDP_BIND_RESPONSE             0x05U
#define ZSI_ZDP_PERMIT_JOINING_REQUEST    0x06U
#define ZSI_ZDP_PERMIT_JOINING_RESPONSE   0x07U
#define ZSI_ZDP_SIMPLE_DESCRIPTOR_REQUEST  0x08U
#define ZSI_ZDP_SIMPLE_DESCRIPTOR_RESPONSE 0x09U
#define ZSI_ZDP_DEVICE_ANNCE_REQUEST       0x0AU
#define ZSI_ZDP_DEVICE_ANNCE_CONF          0x0BU
#define ZSI_ZDP_ACTIVE_ENDPOINTS_REQUEST   0x0CU
#define ZSI_ZDP_ACTIVE_ENDPOINTS_RESPONSE  0x0DU
#define ZSI_ZDP_NWK_ADDRESS_REQUEST        0x0EU
#define ZSI_ZDP_NWK_ADDRESS_RESPONSE       0x0FU
#define ZSI_ZDP_NODE_DESCRIPTOR_REQUEST    0x10U
#define ZSI_ZDP_NODE_DESCRIPTOR_RESPONSE   0x11U
#define ZSI_ZDP_MGMT_BIND_REQUEST          0x12U
#define ZSI_ZDP_MGMT_BIND_RESPONSE         0x13U
#define ZSI_ZDP_MGMT_LQI_REQUEST           0x14U
#define ZSI_ZDP_MGMT_LQI_RESPONSE          0x15U
#define ZSI_ZDP_MGMT_LEAVE_REQUEST         0x16U
#define ZSI_ZDP_MGMT_LEAVE_RESPONSE        0x17U
#define ZSI_ZDP_MGMT_UPDATE_REQUEST        0X18U
#define ZSI_ZDP_MGMT_UPDATE_NOTIFY         0x19U
#define ZSI_ZDP_UNBIND_REQUEST             0x1AU
#define ZSI_ZDP_UNBIND_RESPONSE            0x1BU
/* NWK domain */
#define ZSI_NWK_GET_SHORT_BY_EXT_ADDRESS_REQUEST  0x00U
#define ZSI_NWK_GET_SHORT_BY_EXT_ADDRESS_CONFIRM  0x01U
#define ZSI_NWK_GET_NEXT_HOP_REQUEST              0x02U
#define ZSI_NWK_GET_NEXT_HOP_CONFIRM              0x03U
#define ZSI_NWK_GET_UNICAST_DELIVERY_TIME_REQUEST 0x04U
#define ZSI_NWK_GET_UNICAST_DELIVERY_TIME_CONFIRM 0x05U
#define ZSI_NWK_GET_EXT_BY_SHORT_ADDRESS_REQUEST  0x06U
#define ZSI_NWK_GET_EXT_BY_SHORT_ADDRESS_CONFIRM  0x07U
#define ZSI_NWK_GET_SHORT_ADDRESS_REQUEST         0x08U
#define ZSI_NWK_GET_SHORT_ADDRESS_CONFIRM         0x09U
#define ZSI_NWK_SET_KEY_REQUEST                   0x0AU
#define ZSI_NWK_SET_KEY_CONFIRM                   0x0BU
#define ZSI_NWK_ACTIVATE_KEY_REQUEST              0x0CU
#define ZSI_NWK_ACTIVATE_KEY_CONFIRM              0x0DU
#define ZSI_NWK_ISGROUP_MEMBER_REQUEST            0x0EU
#define ZSI_NWK_ISGROUP_MEMBER_CONFIRM            0x0FU
#define ZSI_NWK_ADD_GROUP_REQUEST                 0x10U
#define ZSI_NWK_ADD_GROUP_CONFIRM                 0x11U
#define ZSI_NWK_REMOVE_GROUP_REQUEST              0x12U
#define ZSI_NWK_REMOVE_GROUP_CONFIRM              0x13U
#define ZSI_NWK_REMOVE_ALL_GROUPS_REQUEST         0x14U
#define ZSI_NWK_REMOVE_ALL_GROUPS_CONFIRM         0x15U
#define ZSI_NWK_GET_UPDATE_ID_REQUEST             0x16U
#define ZSI_NWK_GET_UPDATE_ID_CONFIRM             0x17U
#define ZSI_NWK_NEXT_GROUP_REQUEST                0x18U
#define ZSI_NWK_NEXT_GROUP_CONFIRM                0x19U
#define ZSI_NWK_GROUP_CAPACITY_REQUEST            0x1AU
#define ZSI_NWK_GROUP_CAPACITY_CONFIRM            0x1BU
#define ZSI_NWK_LEAVE_REQUEST                     0x1CU
#define ZSI_NWK_LEAVE_CONFIRM                     0x1DU
#define ZSI_NWK_GET_PARENT_SHORT_ADDRESS_REQUEST  0x1EU
#define ZSI_NWK_GET_PARENT_SHORT_ADDRESS_CONFIRM  0x1FU
#define ZSI_NWK_GET_PANID_REQUEST                 0x20U
#define ZSI_NWK_GET_PANID_CONFIRM                 0x21U
#define ZSI_NWK_FORCE_CHANGE_OWN_ADDR_REQUEST     0x22U
#define ZSI_NWK_FORCE_CHANGE_OWN_ADDR_CONFIRM     0x23U
#define ZSI_NWK_GET_LOGICAL_CHANNEL               0x24U
#define ZSI_NWK_GET_LOGICAL_CHANNEL_CONFIRM       0x25U
#define ZSI_NWK_GET_ACTIVE_KEY_REQUEST            0x26U
#define ZSI_NWK_GET_ACTIVE_KEY_CONFIRM            0x27U

/* KE domain */
#define ZSI_KE_ECC_GENERATE_KEY_REQ               0x00U
#define ZSI_KE_ECC_GENERATE_KEY_CONF              0x01U
#define ZSI_KE_ECC_KEY_BIT_GENERATE_REQ           0x02U
#define ZSI_KE_ECC_KEY_BIT_GENERATE_CONF          0x03U
#define ZSI_KE_SSP_BCB_HASH_REQ                   0x04U
#define ZSI_KE_SSP_BCB_HASH_CONF                  0x05U
#define ZSI_KE_SSP_KEYED_HASH_MAC_REQ             0x06U
#define ZSI_KE_SSP_KEYED_HASH_MAC_CONF            0x07U
#define ZSI_KE_SSP_ZGP_ENCRYPT_FRAME_REQ          0x08U
#define ZSI_KE_SSP_ZGP_ENCRYPT_FRAME_CONF         0x09U
#define ZSI_KE_SSP_ZGP_DECRYPT_FRAME_REQ          0x0AU
#define ZSI_KE_SSP_ZGP_DECRYPT_FRAME_CONF         0x0BU

/* MAC domain */
#define ZSI_MAC_IS_OWN_EXT_ADDR_REQ               0x00U
#define ZSI_MAC_IS_OWN_EXT_ADDR_CONF              0x01U
#define ZSI_MAC_GET_EXT_ADDR_REQ                  0x02U
#define ZSI_MAC_GET_EXT_ADDR_CONF                 0x03U
#define ZSI_RF_RANDOM_REQ                         0x04U
#define ZSI_RF_RANDOM_CONF                        0x05U
#define ZSI_MAC_SET_REQ_REQ                       0x06U
#define ZSI_MAC_SET_REQ_CONF                      0x07U

/* HAL Domain */
#define ZSI_HAL_RESET_REQUEST                     0x00U
#define ZSI_HAL_RESET_CONFIRM                     0x01U

/* BSP Domain */
#define ZSI_BSP_READ_UID_REQUEST                  0x00U
#define ZSI_BSP_READ_UID_CONFIRM                  0x01U


/*PDS domain*/
#define ZSI_PDS_STORE_REQUEST                        0x00U
#define ZSI_PDS_STORE_CONFIRM                        0x01U
#define ZSI_PDS_RESTORE_REQUEST                      0x02U
#define ZSI_PDS_RESTORE_CONFIRM                      0x03U
#define ZSI_PDS_DELETE_REQUEST                       0x04U
#define ZSI_PDS_DELETE_CONFIRM                       0x05U
#define ZSI_PDS_DELETE_ALL_REQUEST                   0x06U
#define ZSI_PDS_DELETE_ALL_CONFIRM                   0x07U
#define ZSI_PDS_STORE_BY_EVENTS_REQUEST              0x08U
#define ZSI_PDS_STORE_BY_EVENTS_CONFIRM              0x09U
#define ZSI_PDS_IS_ABLE_TO_RESTORE_REQUEST           0x0AU
#define ZSI_PDS_IS_ABLE_TO_RESTORE_CONFIRM           0x0BU
#define ZSI_PDS_INIT_ITEMS_REQUEST                   0x0CU
#define ZSI_PDS_INIT_ITEMS_CONFIRM                   0x0DU
#define ZSI_PDS_SUBSCRIBE_TO_STORE_COMPLETION_REQ    0x0EU
#define ZSI_PDS_SUBSCRIBE_TO_STORE_COMPLETION_CONF   0x0FU

/*BDB domain*/
#define ZSI_BDB_GET_NODE_IS_ON_NETWORK_REQUEST       0x0U
#define ZSI_BDB_GET_NODE_IS_ON_NETWORK_CONFIRM       0x1U
#define ZSI_BDB_SET_NODE_IS_ON_NETWORK_REQUEST       0x2U
#define ZSI_BDB_SET_NODE_IS_ON_NETWORK_CONFIRM       0x3U

/*ZGP domain*/
#define ZSI_ZGPL_NVM_TABLE_INIT_REQUEST                    0x1U
#define ZSI_ZGPL_NVM_TABLE_INIT_CONFIRM                    0x2U
#define ZSI_ZGPL_RESET_TABLE_ENTRY_REQUEST                 0x3U
#define ZSI_ZGPL_RESET_TABLE_ENTRY_CONFIRM                 0x4U
#define ZSI_ZGPL_TOTAL_NON_EMPTY_ENTRIES_REQUEST           0x5U
#define ZSI_ZGPL_TOTAL_NON_EMPTY_ENTRIES_CONFIRM           0x6U
#define ZSI_ZGPL_ADD_UPDATE_NVM_TABLE_ENTRY_REQUEST        0x7U
#define ZSI_ZGPL_ADD_UPDATE_NVM_TABLE_ENTRY_CONFIRM        0x8U
#define ZSI_ZGPL_READ_TABLE_ENTRY_FROM_NVM_REQUEST         0x9U
#define ZSI_ZGPL_READ_TABLE_ENTRY_FROM_NVM_CONFIRM         0xAU
#define ZSI_ZGPL_DELETE_TABLE_ENTRY_FROM_NVM_REQUEST       0xBU
#define ZSI_ZGPL_DELETE_TABLE_ENTRY_FROM_NVM_CONFIRM       0xCU
#define ZSI_ZGPL_FRAME_COUNTER_READ_UPDATE_NVM_REQUEST     0xDU
#define ZSI_ZGPL_FRAME_COUNTER_READ_UPDATE_NVM_CONFIRM     0xEU
#define ZSI_ZGPL_RESET_TABLE_TO_FN_REQUEST                 0x11U
#define ZSI_ZGPL_RESET_TABLE_TO_FN_CONFIRM                 0x12U
#define ZSI_ZGPL_SET_DEVICE_MODE_REQUEST                   0x13U
#define ZSI_ZGPL_SET_DEVICE_MODE_CONFIRM                   0x14U
#define ZSI_ZGPL_GET_DEVICE_MODE_REQUEST                   0x15U
#define ZSI_ZGPL_GET_DEVICE_MODE_CONFIRM                   0x16U
#define ZSI_ZGPL_ENABLE_DISABLE_DIRECT_MODE_REQUEST        0x17U
#define ZSI_ZGPL_ENABLE_DISABLE_DIRECT_MODE_CONFIRM        0x18U
#define ZSI_ZGPL_INIT_REQUEST                              0x19U
#define ZSI_ZGPL_INIT_CONFIRM                              0x20U
#define ZSI_ZGPL_FLUSH_TX_QUEUE_REQUEST                    0x21U
#define ZSI_ZGPL_FLUSH_TX_QUEUE_CONFIRM                    0x22U
#define ZSI_ZGPL_GPDF_DATA_REQ_REQUEST                     0x23U
#define ZSI_ZGPL_GPDF_DATA_REQ_CONFIRM                     0x24U
#define ZSI_ZGPL_CHECK_FOR_DUPLICATE_REQUEST               0x25U
#define ZSI_ZGPL_CHECK_FOR_DUPLICATE_CONFIRM               0x26U
#endif /* _ZSICOMMANDID_H */
/* eof zsiCommandId.h */
