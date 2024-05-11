/*************************************************************************//****
  \file zappsihost.h

  \brief This file defines interface to ZAppSiHostLib Library

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2009, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

*******************************************************************************/
#ifndef _ZAPPSIHOST_H
#define _ZAPPSIHOST_H
/*******************************************************************************
                   Includes section
*******************************************************************************/
#include <systemenvironment/include/sysTypes.h>
#include "ZAppSiCommands.h"
/*******************************************************************************
                   Prototypes section
*******************************************************************************/
/***************************************************************************//**
\brief Requests to add membership in a particular group to an endpoint, so that
frames addressed to the group will be delivered to that endpoint in the future.

\param[in] req - Holds parameters of request.
See ZS_ApsAddGroupReq_t for details.
\param[in] conf - Holds result of request.
See ZS_ApsAddGroupConf_t for details.


\return
*******************************************************************************/
void ZS_ApsAddGroupReq(const ZS_ApsAddGroupReq_t *req,
                    void (*conf)(const ZS_ApsAddGroupConf_t *));
/***************************************************************************//**
\brief Requests to bind two devices together, or to bind a device to a group, by
creating an entry in its local binding table, if supported.

\param[in] req - Holds parameters of request.
See ZS_ApsBindReq_t for details.
\param[in] conf - Holds result of request.
See ZS_ApsBindConf_t for details.

\return
*******************************************************************************/
void ZS_ApsBindReq(const ZS_ApsBindReq_t *req,
                void (*conf)(const ZS_ApsBindConf_t *));
/***************************************************************************//**
\brief Requests to send data.

\param[in] req - Holds parameters of request.
See ZS_ApsDataReq_t for details.
\param[in] conf - Holds result of request.
See ZS_ApsDataConf_t for details.

\return
*******************************************************************************/
void ZS_ApsDataReq(const ZS_ApsDataReq_t *req,
                void (*conf)(const ZS_ApsDataConf_t *));
/***************************************************************************//**
\brief The Function is inovked when data is received.
Implemented by user.

\param[in] ind - Holds received data.
See ZS_ApsDataInd_t for details.

\return
*******************************************************************************/
void ZS_ApsDataInd(const ZS_ApsDataInd_t *ind);
/***************************************************************************//**
\brief Requests to remove membership in a particular group from an endpoint so that
frames addressed to the group will no longer be delivered to that endpoint.

\param[in] req - Holds parameters of request.
See ZS_ApsRemoveAllGroupsReq_t for details.
\param[in] conf - Holds result of request.
See ZS_ApsRemoveAllGroupsConf_t for details.

\return
*******************************************************************************/
void ZS_ApsRemoveAllGroupsReq(const ZS_ApsRemoveAllGroupsReq_t *req,
                              void (*conf)(const ZS_ApsRemoveAllGroupsConf_t *));
/***************************************************************************//**
\brief Requests to remove membership in all groups from an endpoint so that no group
addressed frames will be delivered to that endpoint.

\param[in] req - Holds parameters of request.
See ZS_ApsRemoveGroupReq_t for details.
\param[in] conf - Holds result of request.
See ZS_ApsRemoveGroupConf_t for details.

\return
*******************************************************************************/
void ZS_ApsRemoveGroupReq(const ZS_ApsRemoveGroupReq_t *req,
                          void (*conf)(const ZS_ApsRemoveGroupConf_t *));
/***************************************************************************//**
\brief Requests either the active network key or a new end-to-end application key
(master or link).

\param[in] req - Holds parameters of request.
See ZS_ApsRequestKeyReq_t for details
\param[in] conf - Holds result of request.
See ZS_ApsRequestKeyConf_t for details.

\return
*******************************************************************************/
void ZS_ApsRequestKeyReq(const ZS_ApsRequestKeyReq_t *req,
                         void (*conf)(ZS_ApsRequestKeyConf_t *));
/***************************************************************************//**
\brief Requests that another device switch to a new active network key.

\param[in] req - Holds parameters of request.
See ZS_ApsSwitchKeyReq_t for details.
\param[in] conf - Holds result of request.
See ZS_ApsSwitchKeyConf_t for details.

\return
*******************************************************************************/
void ZS_ApsSwitchKeyReq(const ZS_ApsSwitchKeyReq_t *req,
                        void (*conf)(const ZS_ApsSwitchKeyConf_t *));
/***************************************************************************//**
\brief Reqiests to transport a key to another device.

\param[in] req - Holds parameters of request.
See ZS_ApsTransportKeyReq_t for details.
\param[in] conf - Holds result of request.
See ZS_ApsTransportKeyConf_t for details.

\return
*******************************************************************************/
void ZS_ApsTransportKeyReq(const ZS_ApsTransportKeyReq_t *req,
                           void (*conf)(const ZS_ApsTransportKeyConf_t *));
/***************************************************************************//**
\brief Requests to read attribute value.

\param[in] req - Holds parameters of request.
See ZS_SysGetReq_t for details.
\param[in] conf - Holds result of request.
See ZS_SysGetConf_t for details.

\return
*******************************************************************************/
void ZS_SysGetReq(const ZS_SysGetReq_t *req,
                  void (*conf)(const ZS_SysGetConf_t *));
/***************************************************************************//**
\brief Requests to reset host device.

\param[in] req - Holds parameters of request.
\param[in] conf - Pointer to confirmation callback
See ZS_SysResetReq_t for details.

\return
*******************************************************************************/
void ZS_SysResetReq(const ZS_SysResetReq_t *req,
                    void (*conf)(const ZS_SysResetConf_t *conf));
/***************************************************************************//**
\brief Requests to write attribute with value.

\param[in] req - Holds parameters of request
See ZS_SysSetReq_t for details.
\param[in] conf - Holds result of request.
See ZS_SysSetConf_t for details.

\return
*******************************************************************************/
void ZS_SysSetReq(const ZS_SysSetReq_t *req,
                  void (*conf)(const ZS_SysSetConf_t *));
/***************************************************************************//**
\brief Requests to set device type.

\param[in] req - Holds parameters of request.
See ZS_SysSetDeviceTypeReq_t for details.
\param[in] conf - Holds result of request.
See ZS_SysSetDeviceTypeConf_t for details.

\return
*******************************************************************************/
void ZS_SysSetDeviceTypeReq(const ZS_SysSetDeviceTypeReq_t *req,
                            void (*conf)(const ZS_SysSetDeviceTypeConf_t *));

/***************************************************************************//**
\brief This functions are related to ZDO level.
*******************************************************************************/

/***************************************************************************//**
\brief ZDO Power Management.
*******************************************************************************/
/***************************************************************************//**
\brief Request to start network.

\param[in] conf - pointer to command status handler.
See ZDO_Status_t for detailes.

\return
*******************************************************************************/
void ZS_ZdoStartReq(void (*conf)(ZDO_Status_t*));
/***************************************************************************//**
\brief Start sending sync requests

\param[in] conf - pointer to command status handler.
See ZDO_Status_t for detailes.

\return
*******************************************************************************/
void ZS_ZdoStartSyncReq(void (*conf)(ZDO_Status_t*));
/***************************************************************************//**
\brief Stop sending sync requests

\param[in] conf - pointer to command status handler.
See ZDO_Status_t for detailes.

\return
*******************************************************************************/
void ZS_ZdoStopSyncReq(void (*conf)(ZDO_Status_t*));
/***************************************************************************//**
\brief Setting of tx power

This function sets tx power.

\param[in] req - Determines the parameters of the request.
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdoSetTxPowerReq(ZS_ZdoSetTxPowerReq_t* req,
                         void (*conf)(ZS_ZdoSetTxPowerConf_t*));
/***************************************************************************//**
\brief Puts the device to sleep mode.

This function can be used only when the active period in Config Server is set to 0.
The time of sleep period is determined by CS_END_DEVICE_SLEEP_PERIOD in Config Server.

\param[in] req - Determines the sleep parameters.
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdoSleepReq(ZS_ZdoSleepReq_t* req,
                    void (*conf)(ZS_ZdoSleepConf_t*));
/***************************************************************************//**
\brief Wakeup indication

\param

\return
*******************************************************************************/
void ZS_ZdoWakeupInd(void);
/***************************************************************************//**
\brief ZDO Device discovery.
*******************************************************************************/
/***************************************************************************//**
\brief Request for short NWK address of remote device.

It is request from a Local Device wishing to inquire as to the
16-bit address of the Remote Device based on its known IEEE address. The
destination addressing on this command shall be unicast or broadcast to all
devices for which macRxOnWhenIdle = TRUE.
ZigBee Specification r17, 2.4.3.1.1, NWK_addr_req

\param[in] req - Determines the sleep parameters.
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdoNwkAddrReq(ZS_ZdoNwkAddrReq_t* req,
                      void (*conf)(ZS_ZdoNwkAddrConf_t*));
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
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdoMgmtLeaveReq(ZS_ZdoMgmtLeaveReq_t* req,
                        void (*conf)(ZS_ZdoMgmtLeaveConf_t*));
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
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdoMgmtPermitJoiningReq(ZS_ZdoMgmtPermitJoiningReq_t* req,
    void (*conf)(ZS_ZdoMgmtPermitJoiningConf_t*));

//#if APP_ZDP_REQUESTS != false
/***************************************************************************//**
\brief Request for Remote device to leave network.

It is generated from a Local Device wishing to inquire as to the
64-bit IEEE address of the Remote Device based on their known 16-bit address.
The destination addressing on this command shall be unicast.
ZigBee Specification r17, 2.4.3.1.2 IEEE_addr_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdoIeeeAddrReq_t for details.
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdoIeeeAddrReq(ZS_ZdoIeeeAddrReq_t* req,
                       void (*conf)(ZS_ZdoIeeeAddrConf_t*));
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
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdoNodeDescReq(ZS_ZdoNodeDescReq_t* req,
                       void (*conf)(ZS_ZdoNodeDescConf_t* ));
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
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdpPowerDescReq(ZS_ZdpPowerDescReq_t* req,
                        void (*conf)(ZS_ZdpPowerDescConf_t*));
/***************************************************************************//**
\brief Request for remote device simple description.

It is generated from a local device wishing to
inquire as to the simple descriptor of a remote device on a specified endpoint. This
command shall be unicast either to the remote device itself or to an alternative
device that contains the discovery information of the remote device.
ZigBee Specification r17, 2.4.3.1.5 Simple_Desc_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdpSimpleDescReq_t for details.
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdpSimpleDescReq(ZS_ZdpSimpleDescReq_t* req,
                         void (*conf)(ZS_ZdpSimpleDescConf_t*));
/***************************************************************************//**
\brief Request for remote device active endpoints.

It is generated from a local device wishing to acquire
the list of endpoints on a remote device with simple descriptors. This command
shall be unicast either to the remote device itself or to an alternative device that
contains the discovery information of the remote device.
ZigBee Specification r17, 2.4.3.1.6 Active_EP_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdpActiveEPReq_t for details.
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdpActiveEPReq(ZS_ZdpActiveEPReq_t* req,
                       void (*conf)(ZS_ZdpActiveEPConf_t* ));
/***************************************************************************//**
\brief Request for remote device user description.

It is generated from a local device wishing to inquire
as to the user descriptor of a remote device. This command shall be unicast either
to the remote device itself or to an alternative device that contains the discovery
information of the remote device.
ZigBee Specification r17, 2.4.3.1.9 User_Desc_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdpUserDescReq_t for details.
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdpUserDescReq(ZS_ZdpUserDescReq_t* req,
                       void (*conf)(ZS_ZdpUserDescConf_t*));
/***************************************************************************//**
\brief Request for annoncing new device in network.

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
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdpEndDeviceAnnceReq(ZS_ZdpEnDeviceAnnceReq_t* req,
                             void (*conf)(ZS_ZdpEndDeviceConf_t* ));
/***************************************************************************//**
\brief Request for remote device LQI.

It is generated from a Local Device wishing to obtain a
neighbor list for the Remote Device along with associated LQI values to each
neighbor. The destination addressing on this command shall be unicast only and
the destination address must be that of a ZigBee Coordinator or ZigBee Router.
ZigBee Specification r17, 2.4.3.3.2 Mgmt_Lqi_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdpLqiReq_t for details.
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdpLqiReq(ZS_ZdpLqiReq_t* req,
                  void (*conf)(ZS_ZdpLqiConf_t*));
/***************************************************************************//**
\brief Request for remote device complex description.

It is generated from a local device wishing to
inquire as to the complex descriptor of a remote device. This command shall be
unicast either to the remote device itself or to an alternative device that contains
the discovery information of the remote device.
ZigBee Specification r17, 2.4.3.1.8 Complex_Desc_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdpComplexDescReq_t for details.
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdpComplexDescReq(ZS_ZdpComplexDescReq_t* req,
                          void (*conf)(ZS_ZdpComplexDescConf_t*));
/***************************************************************************//**
\brief Request for remote device user description configuration.

It is generated from a local device wishing to
configure the user descriptor on a remote device. This command shall be unicast
either to the remote device itself or to an alternative device that contains the
discovery information of the remote device.
ZigBee Specification r17, 2.4.3.1.12 User_Desc_set
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\param[in] req - Determines the request parameters.
See description of ZS_ZdpUserDescSetReq_t for details.

\return
*******************************************************************************/
void ZS_ZdpUserDescSetReq(ZS_ZdpUserDescSetReq_t* req,
                          void (*conf)(ZS_ZdpUserDescSetConf_t*));
/***************************************************************************//**
\brief Request for remote device to scan network.

It is generated from a Local Device requesting that the
Remote Device execute a Scan to report back networks in the vicinity of the Local
Device. The destination addressing on this command shall be unicast.
ZigBee Specification r17, 2.4.3.3.1 Mgmt_NWK_Disc_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdpNwkUpdateReq_t for details.
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdoNwkUpdateReq(ZS_ZdpNwkUpdateReq_t* req,
                        void (*conf)(ZS_MgmtNwkUpdateNotf_t*));
/***************************************************************************//**
\brief Request to start trust center swap out mechanism.

The function is used to initiate the trust center swap out mechanism.

\param[in] conf - pointer to command status handler.
See according type description for details.

\return
*******************************************************************************/
void ZS_ZdoSwapOutReq(void (*conf)(uint8_t *status));
/***************************************************************************//**
\brief Broadcast request for servers locations.

It is generated from a Local Device wishing to
discover the location of a particular system server or servers as indicated by the
ServerMask parameter. The destination addressing on this request is 'broadcast to
all devices for which macRxOnWhenIdle = TRUE.'
ZigBee Specification r17, 2.4.3.1.13 System_Server_Discovery_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdpSystemServerDiscoveryReq_t for details.
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdpSystemServerDiscoveryReq(ZS_ZdpSystemServerDiscoveryReq_t* req,
                              void (*conf)(ZS_ZdpSystemServerDiscoveryConf_t*));

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
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdpMatchDescReq(ZS_ZdpMatchDescReq_t* req,
                        void (*conf)(ZS_ZdpMatchDescConf_t*));
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
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdpBindReq(ZS_ZdpBindReq_t* req,
                   void (*conf)(ZS_ZdpBindConf_t*));
/***************************************************************************//**
\brief Request to delete record from remote device binding table.

It is generated from a Local Device wishing to remove a Binding
Table entry for the source and destination addresses contained as parameters. The
destination addressing on this command shall be unicast only and the destination
address must be that of the a Primary binding table cache or the SrcAddress.
ZigBee Specification r17, 2.4.3.2.3 Unbind_req

\param[in] req - Determines the request parameters.
See description of ZS_ZdpUnbindReq_t for details.
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdpUnbindReq(ZS_ZdpUnbindReq_t* req,
                     void (*conf)(ZS_ZdpUnbindConf_t*));
#endif //_BINDING_

//#endif //APP_ZDP_REQUESTS
/***************************************************************************//**
\brief Callback for notification about network changes.

The local device is notified of the local channel conditions at the transmitting
device, or of its attempt to update network configuration parameters.
ZigBee Specification r17, 2.4.4.3.9 Mgmt_NWK_Update_notify

\param[in] notf - Response status.
See description of ZS_MgmtNwkUpdateNotf_t for details.

\return
*******************************************************************************/
void ZS_ZdoMgmtNwkUpdateNotify(ZS_MgmtNwkUpdateNotf_t* notf);
/***************************************************************************//**
\brief ZDO additional functions
*******************************************************************************/
/***************************************************************************//**
\brief Request for neighbors table record.

It is used to read NWK neighbor table.

\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdoGetNeibTableReq(void (*conf)(ZS_ZdoGetNeibTableConf_t*));
/***************************************************************************//**
\brief Request for records amount in neighbors table.

It is used to get records amount from neighbors table.

\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZdoGetNeibAmountReq(void (*conf)(ZS_ZdoGetNeibAmountConf_t*));
/***************************************************************************//**
\brief ZCL functions
*******************************************************************************/
#ifdef _ZCL_SUPPORT_ 
/***************************************************************************//**
\brief Request to start Smart Energy profile.

It should called before using ZCL functions. This command also initiates key
establishment.

\param[in] req - Determines the request parameters.
See description of ZS_ZclStartRequest_t for details.
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZclStartReq(ZS_ZclStartRequest_t* req,
                    void (*conf)(RZclStartConfirm_t*));
/***************************************************************************//**
\brief Attribute reporting indication.

Notify of the latest values of one or more
of the attributes of another device.

ZigBee_Cluster_Library_Specification 075123r02ZB, 2.4.11.1 Report Attributes Command Frame Format

\param[in] ind - Indication details.
See description of ZS_ZclReportInd_t for details.

\return
*******************************************************************************/
void ZS_ZclReportInd(ZS_ZclReportInd_t* ind);
/***************************************************************************//**
\brief Attribute event indication.

Notifes about the actions take place on cluster's attribute.

\param[in] ind - Indication details.
See sescription of ZS_ZclAttributeEventInd_t for details.

\return
*******************************************************************************/
void ZS_ZclAttributeEventInd(ZS_ZclAttributeEventInd_t* ind);
/***************************************************************************//**
\brief Request to read Smart Energy profile options for local device.

This function allows to get profile options for local device (certificates,
keys, endpoints and so on)

\param[in] req - Determines the request parameters.
See description of ZS_ZclGetRequest_t for details.
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZclGetReq(ZS_ZclGetRequest_t* req,
                  void (*conf)(ZS_ZclGetConfirm_t*));
/***************************************************************************//**
\brief Request to set Smart Energy profile options for local device.

This function allows to set profile options for local device (certificates,
keys, endpoints and so on)

\param[in] req - Determines the request parameters.
See description of ZS_ZclSetRequest_t for details.
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZclSetReq(ZS_ZclSetRequest_t* req,
                  void (*conf)(RZclSetConfirm_t*));
/***************************************************************************//**
\brief Request to read attributes values for local device.

Use this functions to read values of attributes in Smart Energy cluster.

\param[in] req - Determines the request parameters.
See description of ZS_ZclReadAttributeValue_t for details.
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZclReadAttributeValueReq(ZS_ZclReadAttributeValue_t* req,
                              void (*conf)(ZS_ZclReadAttributeValueConfirm_t*));
/***************************************************************************//**
\brief Request to write attributes values for local device.

Use this functions to write values of attributes in Smart Energy cluster.

\param[in] req - Determines the request parameters.
See description of ZS_ZclReadAttributeValue_t for details.
\param[in] conf - pointer to command status handler.
See according type description for detailes.

\return
*******************************************************************************/
void ZS_ZclWriteAttributeValueReq(ZS_ZclWriteAttributeValue_t* req,
                             void (*conf)(ZS_ZclWriteAttributeValueConfirm_t*));

/***************************************************************************//**
\brief Requests to read the values of one or more attributes located on another
device. Each attribute identifier field shall contain the identifier of the
attribute to be read.

\param[in] req - Holds parameters of the request.
See ZS_ZclReadAttributeReq_t for details.
\param[in] resp - Holds result of the response.
See ZS_ZclReadAttributeResp_t for details.

\return
*******************************************************************************/
void ZS_ZclReadAttributeReq(const ZS_ZclReadAttributeReq_t *req,
                            void (*resp)(const ZS_ZclReadAttributeResp_t *));
/***************************************************************************//**
\brief Requests to write the values of one or more attributes located on another
device. Each write attribute record shall contain the identifier and the actual
value of the attribute to be written.

\param[in] req - Holds parameters of the request.
See ZS_ZclWriteAttributeReq_t for details.
\param[in] resp - Holds parameters of the request.
See ZS_ZclWriteAttributeResp_t for details.
\return
*******************************************************************************/
void ZS_ZclWriteAttributeReq(const ZS_ZclWriteAttributeReq_t *req,
                             void (*resp)(const ZS_ZclWriteAttributeResp_t *));
/***************************************************************************//**
\brief Requests to configure a device to automatically report the values of one
or more of its attributes, or to receive such reports.

\param[in] req - Holds parameters of the request.
See ZS_ZclConfigureReportingReq_t for details.
\param[in] resp - Holds parameters of the response.
See ZS_ZclConfigureReportingResp_t for details.

\return
*******************************************************************************/
void ZS_ZclConfigureReportingReq(const ZS_ZclConfigureReportingReq_t *req,
                          void (*resp)(const ZS_ZclConfigureReportingResp_t *));
/***************************************************************************//**
\brief Requests to discover the identifiers and types of the attributes
on a device which are supported within the cluster to which this command is
directed.

\param[in] req - Holds parameters of the request.
See ZS_ZclDiscoverAttributesReq_t for details.
\param[in] resp - Holds parameters of the response.
See ZS_ZclDiscoverAttributesResp_t for details.

\return
*******************************************************************************/
void ZS_ZclDiscoverAttributesReq(const ZS_ZclDiscoverAttributesReq_t *req,
                          void (*resp)(const ZS_ZclDiscoverAttributesResp_t *));
/***************************************************************************//**
\brief Requests to read the configuration details of the reporting mechanism
for one or more of the attributes of a cluster.

\param[in] req - Holds parameters of the request.
See ZS_ZclReadReportingConfigReq_t for details.
\param[in] resp - Holds parameters of the response.
See ZS_ZclReadReportingConfigResp_t for details.

\return
*******************************************************************************/
void ZS_ZclReadReportingConfigReq(const ZS_ZclReadReportingConfigReq_t *req,
                         void (*resp)(const ZS_ZclReadReportingConfigResp_t *));
/***************************************************************************//**
\brief Requests to send an Identify command. The Identify command starts or stops
the receiving device identifying itself.

\param[in] req - Holds parameters of the request.
See ZS_ZclIdentifyReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclIdentifyReq(const ZS_ZclIdentifyReq_t *req,
                       void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send an Identify Query command. The Identify Query command
allows the sending device to request the target or targets to respond
if they are currently identifying themselves.

\param[in] req - Holds parameters of the request.
See ZS_ZclIdentifyQueryReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclIdentifyQueryReq(const ZS_ZclIdentifyQueryReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send an Identify Qurey Response command.The Identify Query
Response command is generated in response to receiving an
Identify Query command, in the case that the device is currently
identifying itself.

\param[in] req - Holds parameters of the request.
See ZS_ZclIdentifyQueryResponseReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclIdentifyQueryResponseReq(const ZS_ZclIdentifyQueryResponseReq_t *req,
                                    void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief The Function is invoked when an Identify command is received.
Implemented by user.

\param[in] ind - Holds command's parameters and payload.
See ZS_ZclIdentifyInd_t for details.

\return
*******************************************************************************/
void ZS_ZclIdentifyInd(const ZS_ZclIdentifyInd_t *ind);
/***************************************************************************//**
\brief The Function is invoked when an Identify Query command is received.
Implemented by user.

\param[in] ind - Holds command's parameters and payload.
See ZS_ZclIdentifyQueryInd_t for details.

\return
*******************************************************************************/
void ZS_ZclIdentifyQueryInd(const ZS_ZclIdentifyQueryInd_t *ind);
/***************************************************************************//**
\brief The Function is invoked when an Identify Query Response command is received.
Implemented by user.

\param[in] ind - Holds command's parameters and payload.
See ZS_ZclIdentifyQueryResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclIdentifyQueryResponseInd(const ZS_ZclIdentifyQueryResponseInd_t *ind);
/***************************************************************************//**
\brief Requests to send a Get Current Price command. This command is generated
when the client device wishes to verify the available Price Events or after
a loss of power/reset occurs and the client device needs to recover currently
active or scheduled Price Events.

\param[in] req - Holds parameters of the request.
See ZS_ZclGetCurrentPriceReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclGetCurrentPriceReq(const ZS_ZclGetCurrentPriceReq_t *req,
                              void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Publish Price command. The Publish Price command is
generated in response to receiving a Get Current Price command,
a Get Scheduled Prices command or when an update to the pricing information is
available from the commodity provider.

\param[in] req - Holds parameters of the request.
See ZS_ZclPublishPriceReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclPublishPriceReq(const ZS_ZclPublishPriceReq_t *req,
                           void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Function is invoked when Get Current Price command is received.
Implemented by user.

\param[in] ind - Holds command's parameters and payload.
See ZS_ZclGetCurrentPriceInd_t for details.

\return
*******************************************************************************/
void ZS_ZclGetCurrentPriceInd(const ZS_ZclGetCurrentPriceInd_t *ind);
/***************************************************************************//**
\brief Function is invoked when a Publish Price command is received.
Implemented by user.

\param[in] ind - Holds command's parameters and payload.
See ZS_ZclPublishPriceInd_t for details.

\return
*******************************************************************************/
void ZS_ZclPublishPriceInd(const ZS_ZclPublishPriceInd_t *ind);
/***************************************************************************//**
\brief Requests to send a Report Event Status command. This command is generated
when the client device detects a change of state for an active
Load Control event.

\param[in] req - Holds parameters of the request.
See ZS_ZclReportEventStatusReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclReportEventStatusReq(const ZS_ZclReportEventStatusReq_t *req,
                                void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Get Scheduled Events command. This command is generated
when the client device wishes to verify the available Load Control Events or
after a loss of power/reset occurs and the client device needs to recover
currently active or scheduled Load Control Events.

\param[in] req - Holds parameters of the request.
See ZS_ZclGetScheduledEventsReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclGetScheduledEventsReq(const ZS_ZclGetScheduledEventsReq_t *req,
                                 void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Load Control Event command. This command is generated
when the ESP wants to control one or more load control device(s), usually as
the result of an energy curtailment command from the Smart Energy network.

\param[in] req - Holds parameters of the request.
See ZS_ZclLoadControlEventReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclLoadControlEventReq(const ZS_ZclLoadControlEventReq_t *req,
                               void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Cancel Load Control Event command. This command is
generated when the ESP wants to cancel previously scheduled control of one or
more load control device(s), usually as the result of an energy curtailment
command from the Smart Energy network.

\param[in] req - Holds parameters of the request.
See ZS_ZclCancelLoadControlEventReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclCancelLoadControlEventReq(const ZS_ZclCancelLoadControlEventReq_t *req,
                                     void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Cancel All Load Control Events. This command is
generated when the ESP wants to cancel all events for control device(s).

\param[in] req - Holds parameters of the request.
See ZS_ZclCancelAllLoadControlEventsReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclCancelAllLoadControlEventsReq(const ZS_ZclCancelAllLoadControlEventsReq_t *req,
                                         void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Function is invoke when a Report Event Status command is received.
Implemented by user.

\param[in] ind - Holds command's parameters and payload.
See ZS_ZclReportEventStatusInd_t for details.

\return
*******************************************************************************/
void ZS_ZclReportEventStatusInd(const ZS_ZclReportEventStatusInd_t *ind);
/***************************************************************************//**
\brief Function is invoked when a Get Scheduled Events command is received.
Implemented by user.

\param[in] ind - Holds command's parameters and payload.
See ZS_ZclGetScheduledEventsInd_t for details.

\return
*******************************************************************************/
void ZS_ZclGetScheduledEventsInd(const ZS_ZclGetScheduledEventsInd_t *ind);
/***************************************************************************//**
\brief Function is invoked when a Load Control Event command is received.
Implemented by user.

\param[in] ind - Holds command's parameters and payload.
See ZS_ZclLoadControlEventInd_t for details.

\return
*******************************************************************************/
void ZS_ZclLoadControlEventInd(const ZS_ZclLoadControlEventInd_t *ind);
/***************************************************************************//**
\brief Function is invoke when a Cancel Load Control Event command is received.
Implemented by user.

\param[in] ind - Holds command's parameters and payload.
See ZS_ZclCancelLoadControlEventInd_t for details.

\return
*******************************************************************************/
void ZS_ZclCancelLoadControlEventInd(const ZS_ZclCancelLoadControlEventInd_t *ind);
/***************************************************************************//**
\brief Function is invoked when a Cancel All Load Control Events command is
received.
Implemented by user.

\param[in] ind - Holds command's parameters and payload.
See ZS_ZclCancelAllLoadControlEventsInd_t for details.

\return
*******************************************************************************/
void ZS_ZclCancelAllLoadControlEventsInd(const ZS_ZclCancelAllLoadControlEventsInd_t *ind);
/***************************************************************************//**
\brief Requests to send a Get Last Message command. This command causes
the recepient to generate a Display Message command.

\param[in] req - Holds parameters of the request.
See ZS_ZclGetLastMessageReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclGetLastMessageReq(const ZS_ZclGetLastMessageReq_t *req,
                             void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Message Confirmation command. The Message Confirmation
command provides the ability to acknowledge a previously sent message.

\param[in] req - Holds parameters of the request.
See ZS_ZclMessageConfirmationReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclMessageConfirmationReq(const ZS_ZclMessageConfirmationReq_t *req,
                                  void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Display Message command.

\param[in] req - Holds parameters of the request.
See ZS_ZclDisplayMessageReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclDisplayMessageReq(const ZS_ZclDisplayMessageReq_t *req,
                             void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Cancel Message command. The Cancel Message command
provides the ability to cancel the sending or acceptance of previously sent
messages.

\param[in] req - Holds parameters of the request.
See ZS_ZclCancelMessageReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclCancelMessageReq(const ZS_ZclCancelMessageReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief The function is invoked when a Get Last Message command is received.
Implemented by user.

\param[in] ind - Holds command's parameters and payload.
See ZS_ZclGetLastMessageInd_t for details.

\return
*******************************************************************************/
void ZS_ZclGetLastMessageInd(const ZS_ZclGetLastMessageInd_t *ind);
/***************************************************************************//**
\brief The function is invoked when a Message Confirmation command is received.
Implemented by user.

\param[in] ind - Holds command's parameters and payload.
See ZS_ZclMessageConfirmationInd_t for details.

\return
*******************************************************************************/
void ZS_ZclMessageConfirmationInd(const ZS_ZclMessageConfirmationInd_t *ind);
/***************************************************************************//**
\brief The function is inoked when a Display Message command is received.
Implemented by user.

\param[in] ind - Holds command's parameters and payload.
See ZS_ZclDisplayMessageInd_t for details.

\return
*******************************************************************************/
void ZS_ZclDisplayMessageInd(const ZS_ZclDisplayMessageInd_t *ind);
/***************************************************************************//**
\brief The function is invoked when a Cancel Message command is received.
Implemented by user.

\param[in] ind - Holds command's parameters and payload.
See ZS_ZclCancelMessageInd_t for details.

\return
*******************************************************************************/
void ZS_ZclCancelMessageInd(const ZS_ZclCancelMessageInd_t *ind);
/***************************************************************************//**
\brief The function is invoked when a Add Group Response command is received.
Implemented by user.

\param[in] ind - Indication details.
See ZS_ZclAddGroupResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclAddGroupResponseInd(ZS_ZclAddGroupResponseInd_t* ind);
/***************************************************************************//**
\brief The function is invoked when a View Group Response command is received.
Implemented by user.

\param[in] ind - Indication details.
See ZS_ZclViewGroupResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclViewGroupResponseInd(ZS_ZclViewGroupResponseInd_t* ind);
/***************************************************************************//**
\brief The function is invoked when a Get Group Membership Response command is received.
Implemented by user.

\param[in] ind - Indication details.
See ZS_ZclGetGroupMembershipResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclGetGroupMembershipResponseInd(ZS_ZclGetGroupMembershipResponseInd_t* ind);
/***************************************************************************//**
\brief The function is invoked when a Remove Group Response command is received.
Implemented by user.

\param[in] ind - Indication details.
See ZS_ZclRemoveGroupResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclRemoveGroupResponseInd(ZS_ZclRemoveGroupResponseInd_t* ind);
/***************************************************************************//**
\brief The function is invoked when a Add Scene Response command is received.
Implemented by user.

\param[in] ind - Indication details.
See ZS_ZclAddSceneResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclAddSceneResponseInd(ZS_ZclAddSceneResponseInd_t* ind);
/***************************************************************************//**
\brief The function is invoked when a View Scene Response command is received.
Implemented by user.

\param[in] ind - Indication details.
See ZS_ZclViewSceneResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclViewSceneResponseInd(ZS_ZclViewSceneResponseInd_t* ind);
/***************************************************************************//**
\brief The function is invoked when a Remove All Scenes Response command is received.
Implemented by user.

\param[in] ind - Indication details.
See ZS_ZclRemoveAllScenesResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclRemoveAllScenesResponseInd(ZS_ZclRemoveAllScenesResponseInd_t* ind);
/***************************************************************************//**
\brief The function is invoked when a Store Scene Response command is received.
Implemented by user.

\param[in] ind - Indication details.
See ZS_ZclStoreSceneResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclStoreSceneResponseInd(ZS_ZclStoreSceneResponseInd_t* ind);
/***************************************************************************//**
\brief The function is invoked when a Get Scene Membership Response command is received.
Implemented by user.

\param[in] ind - Indication details.
See ZS_ZclGetSceneMembershipResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclGetSceneMembershipResponseInd(ZS_ZclGetSceneMembershipResponseInd_t *ind);
/***************************************************************************//**
\brief Requests to send a Add Group command.

\param[in] req - Holds parameters of the request.
See ZS_ZclAddGroupReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclAddGroupReq(const ZS_ZclAddGroupReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Add Scene command.

\param[in] req - Holds parameters of the request.
See ZS_ZclAddSceneReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclAddSceneReq(const ZS_ZclAddSceneReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a View Group command.

\param[in] req - Holds parameters of the request.
See ZS_ZclViewGroupReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclViewGroupReq(const ZS_ZclViewGroupReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a View Scene command.

\param[in] req - Holds parameters of the request.
See ZS_ZclViewSceneReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclViewSceneReq(const ZS_ZclViewSceneReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Get Group Membership command.

\param[in] req - Holds parameters of the request.
See ZS_ZclGetGroupMembershipReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclGetGroupMembershipReq(const ZS_ZclGetGroupMembershipReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Get Scene Membership command.

\param[in] req - Holds parameters of the request.
See ZS_ZclGetSceneMembershipReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclGetSceneMembershipReq(const ZS_ZclGetSceneMembershipReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a On command.

\param[in] req - Holds parameters of the request.
See ZS_ZclEmptyPayloadReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclOnReq(const ZS_ZclEmptyPayloadReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Off command.

\param[in] req - Holds parameters of the request.
See ZS_ZclEmptyPayloadReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclOffReq(const ZS_ZclEmptyPayloadReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Toggle command.

\param[in] req - Holds parameters of the request.
See ZS_ZclEmptyPayloadReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclToggleReq(const ZS_ZclEmptyPayloadReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Move To Level command.

\param[in] req - Holds parameters of the request.
See ZS_ZclMoveToLevelReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclMoveToLevelReq(const ZS_ZclMoveToLevelReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Move command.

\param[in] req - Holds parameters of the request.
See ZS_ZclMoveReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclMoveReq(const ZS_ZclMoveReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Step command.

\param[in] req - Holds parameters of the request.
See ZS_ZclStepReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclStepReq(const ZS_ZclStepReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Stop command.

\param[in] req - Holds parameters of the request.
See ZS_ZclEmptyPayloadReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclStopReq(const ZS_ZclEmptyPayloadReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Remove All Groups command.

\param[in] req - Holds parameters of the request.
See ZS_ZclEmptyPayloadReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclRemoveAllGroupsReq(const ZS_ZclEmptyPayloadReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Remove All Scenes command.

\param[in] req - Holds parameters of the request.
See ZS_ZclRemoveAllScenesReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclRemoveAllScenesReq(const ZS_ZclRemoveAllScenesReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Recall Scenes command.

\param[in] req - Holds parameters of the request.
See ZS_ZclRecallSceneReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclRecallSceneReq(const ZS_ZclRecallSceneReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*));
/***************************************************************************//**
\brief Requests to send a Store command.

\param[in] req - Holds parameters of the request.
See ZS_ZclStoreSceneReq_t for details.
\param[in] conf - pointer to command status handler.
See RZclCommandConfirm_t for detailes.

\return
*******************************************************************************/
void ZS_ZclStoreSceneReq(const ZS_ZclStoreSceneReq_t *req,
                            void (*conf)(RZclCommandConfirm_t*));

/***************************************************************************//**
\brief Default Response indication handler

\param[in] ind - indication parameters
*******************************************************************************/
void ZS_ZclDefaultResponseInd(const RZclDefaultResponseInd_t *ind);

/**************************************************************************//**
\brief Sends next sequence number request
******************************************************************************/
void ZS_ZclNextSeqNumberReq(void);

/**************************************************************************//**
\brief Next zcl sequence number response handler

\param[in] ind - indication parameters
******************************************************************************/
void ZS_ZclNextSeqNumberRespInd(const RZclNextSequenceNumberResp_t *ind);

#endif // ZCL_SUPPORT == 1

/***************************************************************************//**
\brief This function prepare lib for working. It should be called before using
commands.

\param[in] interfaceID - Holds command's parameters and payload.

\return none
*******************************************************************************/
void ZS_Open(uint8_t interfaceID);

#endif //_ZAPPSIHOST_H
