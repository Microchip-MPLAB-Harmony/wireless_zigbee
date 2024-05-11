/*****************************************************************************
  \file composer.c

  \brief Composer module. Contains functions that create buffer to send.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  History:
    19/08/09 D. Kasyanov - Created
*******************************************************************************/
/******************************************************************************
                   Includes section
 ******************************************************************************/
#include <bufferallocator.h>
#include <ZAppSiHost.h>
#include <ZAppSiIdentifiers.h>
#include <ZAppSiSerialManager.h>
#include <sysUtils.h>
#include <parser.h>
/******************************************************************************
                   Extern variables section
*******************************************************************************/
extern SerialManager_t serialManager;
/***************************************************************************//**
                    Globals Section
*******************************************************************************/
/******************************************************************************
                   Implementation section
 ******************************************************************************/
/***************************************************************************//**
\brief Forms and sends frame which not required additional actions for payload.

It is used to prevent code duplication.

\param[in] cmdId - command id
\param[in] buf - pointer to payload
\param[in] size - payload size
\param[in] confId - supposed confirmation identifier
\param[in] conf - pointer to confirmation handler

\return nothing
******************************************************************************/
void generateSimpleFrame(uint16_t cmdId, void* buf, uint8_t size,
                            uint8_t confId, void* conf)
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *ptr = &buffer->commandFrame;

  ptr->commandId = cmdId;
  ptr->length = sizeof(ptr->commandId) + size;

  if ((size != 0) && (buf != NULL))
  {
    SYS_BYTE_MEMCPY(ptr->payload, buf, size);
  }
  setAwaitingReq(confId, conf);
  serialManager.write(buffer);
}

/***************************************************************************//**
\brief Requests to add membership in a particular group to an endpoint, so that
frames addressed to the group will be delivered to that endpoint in the future.

\param[in] req - Holds parameters of request.
See ZS_ApsAddGroupReq_t for details.

\return
*******************************************************************************/
void ZS_ApsAddGroupReq(const ZS_ApsAddGroupReq_t *req,
                    void (*conf)(const ZS_ApsAddGroupConf_t *))
{
  generateSimpleFrame(R_APSME_ADD_GROUP_REQUEST, (void*)req, sizeof(*req),
                      R_APSME_ADD_GROUP_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Requests to bind two devices together, or to bind a device to a group, by
creating an entry in its local binding table, if supported.

\param[in] req - Holds parameters of request.
See ZS_ApsBindReq_t for details.

\return
*******************************************************************************/
void ZS_ApsBindReq(const ZS_ApsBindReq_t *req,
                void (*conf)(const ZS_ApsBindConf_t *))
{
  generateSimpleFrame(R_APSME_BIND_REQUEST, (void*)req, sizeof(*req),
                      R_APSME_BIND_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Requests to send data.

\param[in] req - Holds parameters of request.
See ZS_ApsDataReq_t for details.

\return
*******************************************************************************/
void ZS_ApsDataReq(const ZS_ApsDataReq_t *req,
                void (*conf)(const ZS_ApsDataConf_t *))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  uint8_t *ptr = (uint8_t*)&buffer->commandFrame;
  uint8_t commandId = R_APSDE_DATA_REQUEST;
  uint8_t length = 0;

  length = sizeof(commandId);
  length += sizeof(req->dstAddrMode);
  length += sizeof(req->dstEndpoint);
  length += sizeof(req->profileId);
  length += sizeof(req->clusterId);
  length += sizeof(req->srcEndpoint);
  length += sizeof(req->asduLength);
  length += req->asduLength;
  length += sizeof(req->txOptions);
  length += sizeof(req->radiusCount);

  ptr += sizeof(length);

  SYS_BYTE_MEMCPY(ptr, &commandId, sizeof(commandId));
  ptr += sizeof(commandId);

  SYS_BYTE_MEMCPY(ptr, &req->dstAddrMode, sizeof(req->dstAddrMode));
  ptr += sizeof(req->dstAddrMode);

  if (req->dstAddrMode == ZS_SHORT_ADDRESS_MODE)
  {
    SYS_BYTE_MEMCPY(ptr,
	            GET_FIELD_PTR(req, ZS_ApsDataReq_t, dstAddr),
		    sizeof(req->dstAddr.shortAddr));
    ptr += sizeof(req->dstAddr.shortAddr);
    length += sizeof(req->dstAddr.shortAddr);
  }
  else if (req->dstAddrMode == ZS_EXTENDED_ADDRESS_MODE)
  {
    SYS_BYTE_MEMCPY(ptr,
	            GET_FIELD_PTR(req, ZS_ApsDataReq_t, dstAddr),
		    sizeof(req->dstAddr.extAddr));
    ptr += sizeof(req->dstAddr.extAddr);
    length += sizeof(req->dstAddr.extAddr);
  }

  SYS_BYTE_MEMCPY(ptr, &req->dstEndpoint, sizeof(req->dstEndpoint));
  ptr += sizeof(req->dstEndpoint);

  SYS_BYTE_MEMCPY(ptr,
                  GET_FIELD_PTR(req, ZS_ApsDataReq_t, profileId),
		  sizeof(req->profileId));
  ptr += sizeof(req->profileId);

  SYS_BYTE_MEMCPY(ptr,
                  GET_FIELD_PTR(req, ZS_ApsDataReq_t, clusterId),
		  sizeof(req->clusterId));
  ptr += sizeof(req->clusterId);

  SYS_BYTE_MEMCPY(ptr, &req->srcEndpoint, sizeof(req->srcEndpoint));
  ptr += sizeof(req->srcEndpoint);

  SYS_BYTE_MEMCPY(ptr, &req->asduLength, sizeof(req->asduLength));
  ptr += sizeof(req->asduLength);

  SYS_BYTE_MEMCPY(ptr, req->asdu, req->asduLength);
  ptr += req->asduLength;

  SYS_BYTE_MEMCPY(ptr, &req->txOptions, sizeof(req->txOptions));
  ptr += sizeof(req->txOptions);

  SYS_BYTE_MEMCPY(ptr, &req->radiusCount, sizeof(req->radiusCount));

  SYS_BYTE_MEMCPY(buffer, &length, sizeof(length));

  setAwaitingReq(R_APSDE_DATA_CONFIRM, (void*)conf);
  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Requests to remove membership in a particular group from an endpoint so that
frames addressed to the group will no longer be delivered to that endpoint.

\param[in] req - Holds parameters of request.
See ZS_ApsRemoveAllGroupsReq_t for details.

\return
*******************************************************************************/
void ZS_ApsRemoveAllGroupsReq(const ZS_ApsRemoveAllGroupsReq_t *req,
                              void (*conf)(const ZS_ApsRemoveAllGroupsConf_t *))
{
  generateSimpleFrame(R_APSME_REMOVE_ALL_GROUPS_REQUEST, (void*)req,
      sizeof(ZS_ApsRemoveAllGroupsReq_t),
      R_APSME_REMOVE_ALL_GROUPS_CONFIRM, (void*)conf);
}

/*
void ApsRemoveDeviceReq(const ZS_ApsRemoveDeviceReq_t *req)
{

}
*/
/***************************************************************************//**
\brief Requests to remove membership in all groups from an endpoint so that no group
addressed frames will be delivered to that endpoint.

\param[in] req - Holds parameters of request.
See ZS_ApsRemoveGroupReq_t for details.

\return
*******************************************************************************/
void ZS_ApsRemoveGroupReq(const ZS_ApsRemoveGroupReq_t *req,
                          void (*conf)(const ZS_ApsRemoveGroupConf_t *))
{
  generateSimpleFrame(R_APSME_REMOVE_GROUP_REQUEST, (void*)req,
      sizeof(ZS_ApsRemoveGroupReq_t),
      R_APSME_REMOVE_GROUP_REQUEST, (void*)conf);
}
/***************************************************************************//**
\brief Requests either the active network key or a new end-to-end application key
(master or link).

\param[in] req - Holds parameters of request.
See ZS_ApsRequestKeyReq_t for details.

\return
*******************************************************************************/
void ZS_ApsRequestKeyReq(const ZS_ApsRequestKeyReq_t *req,
                         void (*conf)(ZS_ApsRequestKeyConf_t *))
{
  generateSimpleFrame(R_APSME_REQUEST_KEY_REQUEST, (void*)req,
      sizeof(ZS_ApsRequestKeyReq_t), R_APSME_REQUEST_KEY_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Requests that another device switch to a new active network key.

\param[in] req - Holds parameters of request.
See ZS_ApsSwitchKeyReq_t for details.

\return
*******************************************************************************/
void ZS_ApsSwitchKeyReq(const ZS_ApsSwitchKeyReq_t *req,
                        void (*conf)(const ZS_ApsSwitchKeyConf_t *))
{
  generateSimpleFrame(R_APSME_SWITCH_KEY_REQUEST, (void*)req,
      sizeof(ZS_ApsSwitchKeyReq_t),
      R_APSME_SWITCH_KEY_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Reqiests to transport a key to another device.

\param[in] req - Holds parameters of request.
See ZS_ApsTransportKeyReq_t for details.

\return
*******************************************************************************/
void ZS_ApsTransportKeyReq(const ZS_ApsTransportKeyReq_t *req,
                           void (*conf)(const ZS_ApsTransportKeyConf_t *))
{
  generateSimpleFrame(R_APSME_TRANSPORT_KEY_REQUEST, (void*)req,
    sizeof(ZS_ApsTransportKeyReq_t), R_APSME_TRANSPORT_KEY_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Requests to read attribute value.

\param[in] req - Holds parameters of request.
See ZS_SysGetReq_t for details.

\return
*******************************************************************************/
void ZS_SysGetReq(const ZS_SysGetReq_t *req,
                  void (*conf)(const ZS_SysGetConf_t *))
{
  generateSimpleFrame(R_SYS_GET_REQUEST, (void*)req,
      sizeof(ZS_SysGetReq_t),
      R_SYS_GET_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Requests to reset host device.

\param[in] req - Holds parameters of request.
See ZS_SysResetReq_t for details.

\return
*******************************************************************************/
void ZS_SysResetReq(const ZS_SysResetReq_t *req,
                    void (*conf)(const ZS_SysResetConf_t *conf))
{
  generateSimpleFrame(R_SYS_RESET_REQUEST, (void*)req,
                         sizeof(ZS_SysResetReq_t),
                         R_SYS_RESET_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Requests to write attribute with value.

\param[in] req - Holds parameters of request
See ZS_SysSetReq_t for details.

\return
*******************************************************************************/
void ZS_SysSetReq(const ZS_SysSetReq_t *req,
                  void (*conf)(const ZS_SysSetConf_t *))
{

  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *commandFrame = &buffer->commandFrame;
  commandFrame->commandId = R_SYS_SET_REQUEST;
  commandFrame->length = sizeof(commandFrame->commandId);
  commandFrame->length += sizeof(req->attributeId);
  commandFrame->length += sizeof(req->attributeLength);
  commandFrame->length += req->attributeLength;

  SYS_BYTE_MEMCPY(commandFrame->payload, req, sizeof(ZS_SysSetReq_t));
  setAwaitingReq(R_SYS_SET_CONFIRM, (void*)conf);
  serialManager.write(buffer);
}

/***************************************************************************//**
\brief Requests to set device type.

\param[in] req - Holds parameters of request.
See ZS_SysSetDeviceTypeReq_t for details.

\return
*******************************************************************************/
void ZS_SysSetDeviceTypeReq(const ZS_SysSetDeviceTypeReq_t *req,
                            void (*conf)(const ZS_SysSetDeviceTypeConf_t *))
{
  generateSimpleFrame(R_SYS_SET_DEVICE_TYPE_REQUEST, (void*)req,
      sizeof(ZS_SysSetDeviceTypeReq_t),
      R_SYS_SET_DEVICE_TYPE_CONFIRM, (void*)conf);
}

void txComplete()
{

}
/***************************************************************************//**
\brief Request to start network.

\return
*******************************************************************************/
void ZS_ZdoStartReq(void (*conf)(ZDO_Status_t*))
{
  generateSimpleFrame(R_SYS_START_REQUEST, 0, 0,
      R_SYS_START_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Request for neighbors table record.

It is used to read NWK neighbor table.

\param

\return
*******************************************************************************/
void ZS_ZdoGetNeibTableReq(void (*conf)(ZS_ZdoGetNeibTableConf_t*))
{
  generateSimpleFrame(R_ZDO_GET_NEIB_TABLE_REQUEST, 0, 0,
                         R_ZDO_GET_NEIB_TABLE_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Request for records amount in neighbors table.

It is used to get records amount from neighbors table.

\param

\return
*******************************************************************************/
void ZS_ZdoGetNeibAmountReq(void (*conf)(ZS_ZdoGetNeibAmountConf_t*))
{
  generateSimpleFrame(R_ZDO_GET_NEIB_AMOUNT_REQUEST, 0, 0,
                      R_ZDO_GET_NEIB_AMOUNT_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Puts the device to sleep mode.

This function can be used only when the active period in Config Server is set to 0.
The time of sleep period is determined by CS_END_DEVICE_SLEEP_PERIOD in Config Server.

\param[in] req - Determines the sleep parameters.

\return
*******************************************************************************/
void ZS_ZdoSleepReq(ZS_ZdoSleepReq_t* req,
                    void (*conf)(ZS_ZdoSleepConf_t*))
{
  generateSimpleFrame(R_ZDO_SLEEP_REQUEST, req, sizeof(ZS_ZdoSleepReq_t),
                      R_ZDO_SLEEP_CONFIRM, (void*)conf);

}
/***************************************************************************//**
\brief Request for short NWK address of remote device.

It is request from a Local Device wishing to inquire as to the
16-bit address of the Remote Device based on its known IEEE address. The
destination addressing on this command shall be unicast or broadcast to all
devices for which macRxOnWhenIdle = TRUE.
ZigBee Specification r17, 2.4.3.1.1, NWK_addr_req

\param[in] req - Determines the sleep parameters.

\return
*******************************************************************************/
void ZS_ZdoNwkAddrReq(ZS_ZdoNwkAddrReq_t* req,
                      void (*conf)(ZS_ZdoNwkAddrConf_t*))
{
  generateSimpleFrame(R_ZDO_NWK_ADDR_REQUEST, req, sizeof(*req),
                      R_ZDO_NWK_ADDR_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Request for Remote device to leave network.

It is generated from a Local Device requesting that a Remote
Device leave the network or to request that another device leave the network. The
Mgmt_Leave_req is generated by a management application which directs the
request to a Remote Device where the NLME-LEAVE.request is to be executed
using the parameter supplied by Mgmt_Leave_req.
ZigBee Specification r17, 2.4.3.3.5 Mgmt_Leave_req

\param[in] req - Determines the leave parameters.
See description of ZS_ZdoMgmtLeaveReq_t for details.

\return
*******************************************************************************/
void ZS_ZdoMgmtLeaveReq(ZS_ZdoMgmtLeaveReq_t* req,
                        void (*conf)(ZS_ZdoMgmtLeaveConf_t*))
{
  generateSimpleFrame(R_ZDO_MGMT_LEAVE_REQUEST, req, sizeof(*req),
                      R_ZDO_MGMT_LEAVE_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Request to configure Remote device net joining.

It is generated from a Local Device requesting that
a remote device or devices allow or disallow association. The
Mgmt_Permit_Joining_req is generated by a management application or
commissioning tool which directs the request to a remote device(s) where the
NLME-PERMIT-JOINING.request is executed using the PermitDuration
parameter supplied by Mgmt_Permit_Joining_req. Additionally, if the remote
device is the Trust Center and TC_Significance is set to 1, the Trust Center
authentication policy will be affected. The addressing may be unicast or
'broadcast to all routers and coordinator'.
ZigBee Specification r17, 2.4.3.3.7 Mgmt_Permit_Joining_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdoMgmtLeaveReq_t for details.

\return
*******************************************************************************/
void ZS_ZdoMgmtPermitJoiningReq(ZS_ZdoMgmtPermitJoiningReq_t* req,
    void (*conf)(ZS_ZdoMgmtPermitJoiningConf_t*))
{
  generateSimpleFrame(R_ZDO_MGMT_PERMIT_JOINING_REQUEST, req, sizeof(*req),
                      R_ZDO_MGMT_PERMIT_JOINING_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Start sending sync requests

\param

\return
*******************************************************************************/
void ZS_ZdoStartSyncReq(void (*conf)(ZDO_Status_t*))
{
  generateSimpleFrame(R_ZDO_START_SYNC_REQUEST, 0, 0,
                      R_ZDO_START_SYNC_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Stop sending sync requests

\param

\return
*******************************************************************************/
void ZS_ZdoStopSyncReq(void (*conf)(ZDO_Status_t*))
{
  generateSimpleFrame(R_ZDO_STOP_SYNC_REQUEST, 0, 0,
                      R_ZDO_STOP_SYNC_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Request for Remote device to leave network.

It is generated from a Local Device wishing to inquire as to the
64-bit IEEE address of the Remote Device based on their known 16-bit address.
The destination addressing on this command shall be unicast.
ZigBee Specification r17, 2.4.3.1.2 IEEE_addr_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdoIeeeAddrReq_t for details.

\return
*******************************************************************************/
void ZS_ZdoIeeeAddrReq(ZS_ZdoIeeeAddrReq_t* req,
                       void (*conf)(ZS_ZdoIeeeAddrConf_t*))
{
  generateSimpleFrame(R_ZDO_IEEE_ADDR_REQUEST, req, sizeof(*req),
                      R_ZDO_IEEE_ADDR_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Request for remote device node description.

It is generated from a local device wishing to inquire
as to the node descriptor of a remote device. This command shall be unicast either
to the remote device itself or to an alternative device that contains the discovery
information of the remote device. The NWKAddrOfInterest field shall contain the network
address of the remote device for which the node descriptor is required.
ZigBee Specification r17, 2.4.3.1.3 Node_Desc_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdoNodeDescReq_t for details.

\return
*******************************************************************************/
void ZS_ZdoNodeDescReq(ZS_ZdoNodeDescReq_t* req,
                       void (*conf)(ZS_ZdoNodeDescConf_t* ))
{
  generateSimpleFrame(R_ZDO_NODE_DESC_REQUEST, req, sizeof(*req),
                      R_ZDO_NODE_DESC_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Request for Remote device power description.

It is generated from a local device wishing to
inquire as to the power descriptor of a remote device. This command shall be
unicast either to the remote device itself or to an alternative device that contains
the discovery information of the remote device.
The NWKAddrOfInterest field shall contain the network
address of the remote device for which the power descriptor is required.
ZigBee Specification r17, 2.4.3.1.4 Power_Desc_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdpPowerDescReq_t for details.

\return
*******************************************************************************/
void ZS_ZdpPowerDescReq(ZS_ZdpPowerDescReq_t* req,
                        void (*conf)(ZS_ZdpPowerDescConf_t*))
{
  generateSimpleFrame(R_ZDO_POWER_DESC_REQUEST, req, sizeof(*req),
                      R_ZDO_POWER_DESC_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Request for remote device simple description.

It is generated from a local device wishing to
inquire as to the simple descriptor of a remote device on a specified endpoint. This
command shall be unicast either to the remote device itself or to an alternative
device that contains the discovery information of the remote device.
ZigBee Specification r17, 2.4.3.1.5 Simple_Desc_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdpSimpleDescReq_t for details.

\return
*******************************************************************************/
void ZS_ZdpSimpleDescReq(ZS_ZdpSimpleDescReq_t* req,
                         void (*conf)(ZS_ZdpSimpleDescConf_t*))
{
  generateSimpleFrame(R_ZDO_SIMPLE_DESC_REQUEST, req, sizeof(*req),
                      R_ZDO_SIMPLE_DESC_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Request for remote device active endpoints.

It is generated from a local device wishing to acquire
the list of endpoints on a remote device with simple descriptors. This command
shall be unicast either to the remote device itself or to an alternative device that
contains the discovery information of the remote device.
ZigBee Specification r17, 2.4.3.1.6 Active_EP_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdpActiveEPReq_t for details.

\return
*******************************************************************************/
void ZS_ZdpActiveEPReq(ZS_ZdpActiveEPReq_t* req,
                       void (*conf)(ZS_ZdpActiveEPConf_t* ))
{
  generateSimpleFrame(R_ZDO_ACTIVE_EP_DESC_REQUEST, req, sizeof(*req),
      R_ZDO_ACTIVE_EP_DESC_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Request for remote device complex description.

It is generated from a local device wishing to
inquire as to the complex descriptor of a remote device. This command shall be
unicast either to the remote device itself or to an alternative device that contains
the discovery information of the remote device.
ZigBee Specification r17, 2.4.3.1.8 Complex_Desc_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdpComplexDescReq_t for details.

\return
*******************************************************************************/
void ZS_ZdpComplexDescReq(ZS_ZdpComplexDescReq_t* req,
                          void (*conf)(ZS_ZdpComplexDescConf_t*))
{
  generateSimpleFrame(R_ZDO_COMPLEX_DESC_REQUEST, req, sizeof(*req),
      R_ZDO_COMPLEX_DESC_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Request for remote device user description.

It is generated from a local device wishing to inquire
as to the user descriptor of a remote device. This command shall be unicast either
to the remote device itself or to an alternative device that contains the discovery
information of the remote device.
ZigBee Specification r17, 2.4.3.1.9 User_Desc_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdpUserDescReq_t for details.

\return
*******************************************************************************/
void ZS_ZdpUserDescReq(ZS_ZdpUserDescReq_t* req,
                       void (*conf)(ZS_ZdpUserDescConf_t*))
{
  generateSimpleFrame(R_ZDO_USER_DESC_REQUEST, req, sizeof(*req),
                      R_ZDO_USER_DESC_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Request for notification of remote devices about network changes.

It is provided to enable ZigBee devices on the network to notify
other ZigBee devices that the device has joined or re-joined the network,
identifying the device's 64-bit IEEE address and new 16-bit NWK address, and
informing the Remote Devices of the capability of the ZigBee device. This
command shall be invoked for all ZigBee end devices upon join or rejoin. This
command may also be invoked by ZigBee routers upon join or rejoin as part of
NWK address conflict resolution. The destination addressing on this primitive is
broadcast to all devices for which macRxOnWhenIdle = TRUE.

ZigBee Specification r17, 2.4.3.1.11 Device_annce

\param[in] req - Determines the request parameters.
See description of ZS_ZdpEnDeviceAnnceReq_t for details.

\return
*******************************************************************************/
void ZS_ZdpEndDeviceAnnceReq(ZS_ZdpEnDeviceAnnceReq_t* req,
                             void (*conf)(ZS_ZdpEndDeviceConf_t* ))
{
  generateSimpleFrame(R_ZDO_END_DEVICE_ANNCE_REQUEST, req, sizeof(*req),
                      R_ZDO_END_DEVICE_ANNCE_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Request for remote device LQI.

It is generated from a Local Device wishing to obtain a
neighbor list for the Remote Device along with associated LQI values to each
neighbor. The destination addressing on this command shall be unicast only and
the destination address must be that of a ZigBee Coordinator or ZigBee Router.
ZigBee Specification r17, 2.4.3.3.2 Mgmt_Lqi_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdpLqiReq_t for details.

\return
*******************************************************************************/
void ZS_ZdpLqiReq(ZS_ZdpLqiReq_t* req,
                  void (*conf)(ZS_ZdpLqiConf_t*))
{
  generateSimpleFrame(R_ZDO_MGMT_LQI_REQUEST, req, sizeof(*req),
                      R_ZDO_MGMT_LQI_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Request for remote device user description configuration.

It is generated from a local device wishing to
configure the user descriptor on a remote device. This command shall be unicast
either to the remote device itself or to an alternative device that contains the
discovery information of the remote device.
ZigBee Specification r17, 2.4.3.1.12 User_Desc_set

\param[in] req - Determines the request parameters.
See description of ZS_ZdpUserDescSetReq_t for details.

\return
*******************************************************************************/
void ZS_ZdpUserDescSetReq(ZS_ZdpUserDescSetReq_t* req,
                          void (*conf)(ZS_ZdpUserDescSetConf_t*))
{
  generateSimpleFrame(R_ZDO_USER_DESC_SET_REQUEST, req, sizeof(*req),
                      R_ZDO_USER_DESC_SET_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Request for remote device to scan network.

It is generated from a Local Device requesting that the
Remote Device execute a Scan to report back networks in the vicinity of the Local
Device. The destination addressing on this command shall be unicast.
ZigBee Specification r17, 2.4.3.3.1 Mgmt_NWK_Disc_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdpNwkUpdateReq_t for details.

\return
*******************************************************************************/
void ZS_ZdoNwkUpdateReq(ZS_ZdpNwkUpdateReq_t* req,
                        void (*conf)(ZS_MgmtNwkUpdateNotf_t*))
{
  generateSimpleFrame(R_ZDO_MGMT_NWK_UPDATE_REQUEST, req, sizeof(*req),
                      R_ZDO_MGMT_NWK_UPDATE_CONFIRM, (void*)conf);
}

/***************************************************************************//**
\brief Broadcast request for servers locations.

It is generated from a Local Device wishing to
discover the location of a particular system server or servers as indicated by the
ServerMask parameter. The destination addressing on this request is 'broadcast to
all devices for which macRxOnWhenIdle = TRUE.'
ZigBee Specification r17, 2.4.3.1.13 System_Server_Discovery_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdpSystemServerDiscoveryReq_t for details.

\return
*******************************************************************************/
void ZS_ZdpSystemServerDiscoveryReq(ZS_ZdpSystemServerDiscoveryReq_t* req,
                              void (*conf)(ZS_ZdpSystemServerDiscoveryConf_t*))
{
  generateSimpleFrame(R_ZDP_SYSTEM_DISCOVERY_REQUEST, req, sizeof(*req),
                      R_ZDP_SYSTEM_DISCOVERY_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Setting of tx power

This function sets tx power.

\param[in] req - Determines the parameters of the request.

\return
*******************************************************************************/
void ZS_ZdoSetTxPowerReq(ZS_ZdoSetTxPowerReq_t* req,
                         void (*conf)(ZS_ZdoSetTxPowerConf_t*))
{
  generateSimpleFrame(R_ZDO_SET_TX_POWER_REQUEST, req, sizeof(*req),
                      R_ZDO_SET_TX_POWER_CONFIRM, (void*)conf);
}
#ifdef _BINDING_
/***************************************************************************//**
\brief Request for find devices by clusters set.

It is generated from a local device wishing to find
remote devices supporting a specific simple descriptor match criterion. This
command shall either be broadcast to all devices for which macRxOnWhenIdle =
TRUE, or unicast. If the command is unicast, it shall be directed either to the
remote device itself or to an alternative device that contains the discovery
information of the remote device
ZigBee Specification r17, 2.4.3.1.7 Match_Desc_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdpMatchDescReq_t for details.

\return
*******************************************************************************/
void ZS_ZdpMatchDescReq(ZS_ZdpMatchDescReq_t* req,
                        void (*conf)(ZS_ZdpMatchDescConf_t*))
{
  ZS_CommandBuffer_t* buffer = (ZS_CommandBuffer_t*)bufferAllocator.allocate();
  ZS_CommandFrame_t *ptr = &buffer->commandFrame;
  ptr->commandId = R_ZDO_MATCH_DESC_REQUEST;
  ptr->length = sizeof(ZS_ZdpMatchDescReq_t) + sizeof(ptr->commandId)
        - sizeof(req->inClusterList) - sizeof(req->outClusterList)
        + sizeof(ClusterId_t) * (req->numInClusters + req->numOutClusters);

  uint8_t* pos = ptr->payload;
  SYS_BYTE_MEMCPY( pos,
      req,
      offsetof(ZS_ZdpMatchDescReq_t, inClusterList));
  pos += offsetof(ZS_ZdpMatchDescReq_t, inClusterList);
  SYS_BYTE_MEMCPY( pos,
      req->inClusterList,
      req->numInClusters * sizeof(ClusterId_t));
  pos += req->numInClusters * sizeof(ClusterId_t);
  *pos++ = req->numOutClusters;
  SYS_BYTE_MEMCPY( pos,
      req->outClusterList,
      req->numOutClusters * sizeof(ClusterId_t));
  setAwaitingReq(R_ZDO_MATCH_DESC_CONFIRM, (void*)conf);
  serialManager.write(buffer);
}
/***************************************************************************//**
\brief Request to add record to remote device binding table.

It is generated from a Local Device wishing to create a Binding Table
entry for the source and destination addresses contained as parameters. The
destination addressing on this command shall be unicast only, and the destination
address shall be that of a Primary binding table cache or to the SrcAddress itself.
The Binding Manager is optionally supported on the source device (unless that
device is also the ZigBee Coordinator) so that device shall issue a
NOT_SUPPORTED status to the Bind_req if not supported.
ZigBee Specification r17, 2.4.3.2.2 Bind_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdpBindReq_t for details.

\return
*******************************************************************************/
void ZS_ZdpBindReq(ZS_ZdpBindReq_t* req,
                   void (*conf)(ZS_ZdpBindConf_t*))
{
  generateSimpleFrame(R_ZDO_BIND_REQUEST, req, sizeof(*req),
                      R_ZDO_BIND_CONFIRM, (void*)conf);
}
/***************************************************************************//**
\brief Request to delete record from remote device binding table.

It is generated from a Local Device wishing to remove a Binding
Table entry for the source and destination addresses contained as parameters. The
destination addressing on this command shall be unicast only and the destination
address must be that of the a Primary binding table cache or the SrcAddress.
ZigBee Specification r17, 2.4.3.2.3 Unbind_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdpUnbindReq_t for details.

\return
*******************************************************************************/
void ZS_ZdpUnbindReq(ZS_ZdpUnbindReq_t* req,
                     void (*conf)(ZS_ZdpUnbindConf_t*))
{
  generateSimpleFrame(R_ZDO_UNBIND_REQUEST, req, sizeof(*req),
                      R_ZDO_UNBIND_CONFIRM, (void*)conf);
}
#endif //_BINDING_

