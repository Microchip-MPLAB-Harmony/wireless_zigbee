/*******************************************************************************
  \file stubs.c

  \brief stubs file contains function the user free to redefine.
 This file should be linked to user's application.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2015, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  History:
    19/08/09 D. Kasyanov - Created
*******************************************************************************/
/***************************************************************************//**
                         Include section
*******************************************************************************/
#include <ZAppSiCommands.h>
/***************************************************************************//**
                         Functions section
*******************************************************************************/
/***************************************************************************//**
\brief The Function is inovked in response to SysGetReq call.
Implemented by user.

\param[in] conf - Holds result of request.
See ZS_SysGetConf_t for details.

\return
*******************************************************************************/
void ZS_SysGetConf(const ZS_SysGetConf_t *conf)
{
   // Insert your code here
}
/***************************************************************************//**
\brief The Function is invoked in response to SysResetReq call.
Implemented by user.

\param[in] conf - Holds result of request.
See ZS_SysResetConf_t for details.

\return
*******************************************************************************/
void ZS_SysResetConf(const ZS_SysResetConf_t *conf)
{
    // Insert your code here
}
/***************************************************************************//**
\brief The Function is invoked in response to SysSetReq call.

\param[in] conf - Holds result of request.
See ZS_SysSetConf_t for details.

\return
*******************************************************************************/
void ZS_SysSetConf(const ZS_SysSetConf_t *conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The Function is inovked in response to SysSetDeviceTypeReq call.

\param[in] conf - Holds result of request.
See ZS_SysSetDeviceTypeConf_t for details.

\return
*******************************************************************************/
void ZS_SysSetDeviceTypeConf(const ZS_SysSetDeviceTypeConf_t *conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The Function is inovked in response to ZS_ApsAddGroupReq call.
Implemented by user.

\param[in] conf - Holds result of request.
See ZS_ApsAddGroupConf_t for details.

\return
*******************************************************************************/
void ZS_ApsAddGroupConf(const ZS_ApsAddGroupConf_t *conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The Function is inovked in response to ZS_ApsBindReq call.
Implemented by user.

\param[in] conf - Holds result of request.
See ZS_ApsBindConf_t for details.

\return
*******************************************************************************/
void ZS_ApsBindConf(const ZS_ApsBindConf_t *conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The Function is inovked in response to ZS_ApsDataReq call.
Implemented by user.

\param[in] conf - Holds result of request.
See ZS_ApsDataConf_t for details.

\return
*******************************************************************************/
void ZS_ApsDataConf(const ZS_ApsDataConf_t *conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The Function is inovked when data is received.
Implemented by user.

\param[in] ind - Holds received data.
See ZS_ApsDataInd_t for details.

\return
*******************************************************************************/
void ZS_ApsDataInd(const ZS_ApsDataInd_t *ind)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The Function is invoked in response to ZS_ApsRemoveAllGroupsReq call.
Implemented by user.

\param[in] conf - Holds result of request.
See ZS_ApsRemoveAllGroupsConf_t for details.

\return
*******************************************************************************/
void ZS_ApsRemoveAllGroupsConf(const ZS_ApsRemoveAllGroupsConf_t *conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The Function is invoked in response to ZS_ApsRemoveGroupReq call.
Implemented by user.

\param[in] conf - Holds result of request.
See ZS_ApsRemoveGroupConf_t for details.

\return
*******************************************************************************/
void ZS_ApsRemoveGroupConf(const ZS_ApsRemoveGroupConf_t *conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The Function is invoked in response to ZS_ApsRequestKeyReq call.
Implemented by user.

\param[in] conf - Holds result of request.
See ZS_ApsRequestKeyConf_t for details.
\return
*******************************************************************************/
void ZS_ApsRequestKeyConf(const ZS_ApsRequestKeyConf_t *conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The Function is invoked in response to ZS_ApsSwitchKeyReq call.
Implemented by user.

\param[in] conf - Holds result of request.
See ZS_ApsSwitchKeyConf_t for details.

\return
*******************************************************************************/
void ZS_ApsSwitchKeyConf(const ZS_ApsSwitchKeyConf_t *conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The Function is invoked in response to ZS_ApsTransportKeyReq call.
Implemented by user.

\param[i] conf - Holds result of request.
See ZS_ApsTransportKeyConf_t for details.

\return
*******************************************************************************/
void ZS_ApsTransportKeyConf(const ZS_ApsTransportKeyConf_t *conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief This function is invoked in response to ZS_ZdoStartReq.

\param status - Holds the result of request.
The values are enumerated in ZDO_Status_t in zdo.h

\return
*******************************************************************************/
void ZS_ZdoStartConf(uint8_t status)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZdoGetNeibTableReq with request status.

Returns all records from neighbors table.

\param[in] records - Pointer to array of table records.
See description of ZS_ZdoGetNeibTableConf_t for details.
\param[in] recordsAmount - Table records amount

\return
*******************************************************************************/
void ZS_ZdoGetNeibTableConf(ZS_ZdoGetNeibTableConf_t* records, uint8_t recordsAmount)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZdoGetNeibAmountReq with request status.

Returns neighbors table records amount.

\param[in] conf - Response status.
See description of ZS_ZdoGetNeibAmountConf_t for details.

\return
*******************************************************************************/
void ZS_ZdoGetNeibAmountConf(ZS_ZdoGetNeibAmountConf_t * conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback for notification about network changes.

The local device is notified of the local channel conditions at the transmitting
device, or of its attempt to update network configuration parameters.
ZigBee Specification r17, 2.4.4.3.9 Mgmt_NWK_Update_notify

\param[in] notf - Response status.
See description of ZS_MgmtNwkUpdateNotf_t for details.

\return
*******************************************************************************/
void ZS_ZdoMgmtNwkUpdateNotify(ZS_MgmtNwkUpdateNotf_t* notf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZdoNwkUpdateReq with request status.

The local device is notified of the results of its attempt to perform a remote
network discovery.
ZigBee Specification r17, 2.4.4.3.1 Mgmt_NWK_Disc_rsp

\param[in] conf - Response status.
See description of ZS_MgmtNwkUpdateNotf_t for details.

\return
*******************************************************************************/
void ZS_ZdoNwkUpdateConf(ZS_MgmtNwkUpdateNotf_t* notf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Confirmation ZS_ZdoSleepReq.

\param[in] conf - Status of command.

\return
*******************************************************************************/
void ZS_ZdoSleepConf(ZS_ZdoSleepConf_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Wakeup indication

\param

\return
*******************************************************************************/
void ZS_ZdoWakeupInd()
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZdoNwkAddrReq with request status.

Notify of the
status of its attempt to discover a NWK address from an IEEE address or notified
of an error. If the NWK_addr_rsp command is received with a Status of
SUCCESS, the remaining fields of the command contain the appropriate
discovery information, according to the RequestType as specified in the original
NWK_Addr_req command. Otherwise, the Status field indicates the error and the
NumAssocDev, StartIndex, and NWKAddrAssocDevList fields shall not be
included.
ZigBee Specification r17, 2.4.4.1.1, NWK_addr_resp

\param[in] conf - Response data. See description of ZS_ZdoNwkAddrConf_t for details.

\return
*******************************************************************************/
void ZS_ZdoNwkAddrConf(ZS_ZdoNwkAddrConf_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZdoMgmtLeaveReq with request status.

The local device is notified of the results of its attempt to cause a remote device to
leave the network.
ZigBee Specification r17, 2.4.4.3.5 Mgmt_Leave_rsp

\param[in] conf - Response data.
See description of ZS_ZdoMgmtLeaveConf_t for details.

\return
*******************************************************************************/
void ZS_ZdoMgmtLeaveConf(ZS_ZdoMgmtLeaveConf_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZdoMgmtPermitJoiningReq with request status.

The status of the Mgmt_Permit_Joining_req command is notified to the requester.
ZigBee Specification r17, 2.4.4.3.7 Mgmt_Permit_Joining_rsp

\param[in] conf - Response status.
See description of ZS_ZdoMgmtPermitJoiningConf_t for details.

\return
*******************************************************************************/
void ZS_ZdoMgmtPermitJoiningConf(ZS_ZdoMgmtPermitJoiningConf_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Start sending sync confirm

\return - ZDO status. The primitive returns one of following values:
   - ZDO_SUCCESS_STATUS
   - ZDO_BUSY_STATUS
*******************************************************************************/
void ZS_ZdoStartSyncConf(ZS_Status_t status)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Stop sending sync confirm

\param[in] conf - ZDO status. The primitive returns one of following values:
   - ZDO_SUCCESS_STATUS
   - ZDO_INVALID_REQUEST_STATUS

\return
*******************************************************************************/
void ZS_ZdoStopSyncConf(ZS_Status_t status)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZdoIeeeAddrReq with request status.

Notify of the
status of its attempt to discover an IEEE address from an NWK address or notified
of an error. If the IEEE_addr_rsp command is received with a Status of
SUCCESS, the remaining fields of the command contain the appropriate
discovery information, according to the RequestType as specified in the original
IEEE_Addr_req command. Otherwise, the Status field indicates the error and the
NumAssocDev, StartIndex, and NWKAddrAssocDevList fields shall not be
included.
ZigBee Specification r17, 2.4.4.1.2 IEEE_addr_rsp

\param[in] conf - Response status.
See description of ZS_ZdoIeeeAddrConf_t for details.

\return
*******************************************************************************/
void ZS_ZdoIeeeAddrConf(ZS_ZdoIeeeAddrConf_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZdoNodeDescReq with request status.

Notify of the
node descriptor of the remote device indicated in the original Node_Desc_req
command or notified of an error. If the Node_Desc_rsp command is received with
a Status of SUCCESS, the NodeDescriptor field shall contain the requested node
descriptor. Otherwise, the Status field indicates the error and the NodeDescriptor
field shall not be included.
ZigBee Specification r17, 2.4.4.1.3 Node_Desc_rsp

\param[in] conf - Response status.
See description of ZS_ZdoNodeDescConf_t for details.

\return
*******************************************************************************/
void ZS_ZdoNodeDescConf(ZS_ZdoNodeDescConf_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZdoNodeDescReq with request status.

Notify of the
power descriptor of the remote device indicated in the original Power_Desc_req
command or notified of an error. If the Power_Desc_rsp command is received
with a Status of SUCCESS, the PowerDescriptor field shall contain the requested
power descriptor. Otherwise, the Status field indicates the error and the
PowerDescriptor field shall not be included.
ZigBee Specification r17, 2.4.4.1.4 Power_Desc_rsp

\param[in] conf - Response status.
See description of ZS_ZdpPowerDescConf_t for details.

\return
*******************************************************************************/
void ZS_ZdpPowerDescConf(ZS_ZdpPowerDescConf_t* conf)
{
 // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZdpSimpleDescReq with request status.

Notify of
the simple descriptor on the endpoint of the remote device indicated in the original
Simple_Desc_req command or notified of an error. If the Simple_Desc_rsp
command is received with a Status of SUCCESS, the SimpleDescriptor field shall
contain the requested simple descriptor. Otherwise, the Status field indicates the
error and the SimpleDescriptor field shall not be included.
ZigBee Specification r17, 2.4.4.1.5 Simple_Desc_rsp

\param[in] conf - Response status.
See description of ZS_ZdpSimpleDescConf_t for details.

\return
*******************************************************************************/
void ZS_ZdpSimpleDescConf(ZS_ZdpSimpleDescConf_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZdpActiveEPReq with request status.

Notify of the
active endpoints of the remote device indicated in the original Active_EP_req
command or notified of an error. If the Active_EP_rsp command is received with
a Status of SUCCESS, the ActiveEPCount field indicates the number of entries in
the ActiveEPList field. Otherwise, the Status field indicates the error and the
ActiveEPList field shall not be included.
ZigBee Specification r17,2.4.4.1.6 Active_EP_rsp

\param[in] conf - Response status.
See description of ZS_ZdpActiveEPConf_t for details.

\return
*******************************************************************************/
void ZS_ZdpActiveEPConf(ZS_ZdpActiveEPConf_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZdpComplexDescReq with request status.

Notify of
the complex descriptor of the remote device indicated in the original
Complex_Desc_req command or notified of an error. If the Complex_Desc_rsp
command is received with a Status of SUCCESS, the ComplexDescriptor field
shall contain the requested complex descriptor. Otherwise, the Status field
indicates the error and the ComplexDescriptor field shall not be included.
ZigBee Specification r17, 2.4.4.1.8 Complex_Desc_rsp

\param[in] conf - Response status.
See description of ZS_ZdpComplexDescConf_t for details.

\return
*******************************************************************************/
void ZS_ZdpComplexDescConf(ZS_ZdpComplexDescConf_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZdpUserDescReq with request status.

Notify of the
user descriptor of the remote device indicated in the original User_Desc_req
command or notified of an error. If the User_Desc_rsp command is received with
a Status of SUCCESS, the UserDescriptor field shall contain the requested user
descriptor. Otherwise, the Status field indicates the error and the UserDescriptor
field shall not be included.
ZigBee Specification r17, 2.4.4.1.9 User_Desc_rsp

\param[in] conf - Response status.
See description of ZS_ZdpUserDescConf_t for details.

\return
*******************************************************************************/
void ZS_ZdpUserDescConf(ZS_ZdpUserDescConf_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZdpEndDeviceAnnceReq with request status.

The local device is notified of the results of its attempt to make Annce request.

\param[in] conf - Response status.
See description of structure type for details.

\return
*******************************************************************************/
void ZS_ZdpEndDeviceAnnceConf(ZS_ZdpEndDeviceConf_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZdpLqiReq with request status.

The local device is notified of the results of its attempt to obtain the neighbor
table.
ZigBee Specification r17, 2.4.4.3.2 Mgmt_Lqi_rsp

\param[in] conf - Response status.
See description of ZS_ZdpLqiConf_t for details.

\return
*******************************************************************************/
void ZS_ZdpLqiConf(ZS_ZdpLqiConf_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZdpUserDescSetReq with request status.

The local device is notified of the results of its attempt to configure the user
descriptor on a remote device.
ZigBee Specification r17, 2.4.4.1.11 User_Desc_conf

\param[in] conf - Response status.
See description of ZS_ZdpUserDescSetConf_t for details.

\return
*******************************************************************************/
void ZS_ZdpUserDescSetConf(ZS_ZdpUserDescSetConf_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZdpSystemServerDiscoveryReq with request status.

The requesting device is notified that this device has some of the system server
functionality that the requesting device is seeking.
If the Network Manager bit was set in the System_Server_Discovery_rsp, then the
Remote Device's NWK address shall be set into the nwkManagerAddr of the NIB.
ZigBee Specification r17, 2.4.4.1.10 System_Server_Discovery_rsp

\param[in] conf - Response status.
See description of ZS_ZdpSystemServerDiscoveryConf_t for details.

\return
*******************************************************************************/
void ZS_ZdpSystemServerDiscoveryConf(ZS_ZdpSystemServerDiscoveryConf_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZdpMatchDescReq with request status.

Notify of the
results of its match criterion query indicated in the original Match_Desc_req
command or notified of an error. If the Match_Desc_rsp command is received
with a Status of SUCCESS, the MatchList field shall contain the list of endpoints
containing simple descriptors that matched the criterion. Otherwise, the Status
field indicates the error and the MatchList field shall not be included.
ZigBee Specification r17, 2.4.4.1.7 Match_Desc_rsp

\param[in] conf - Response status.
See description of ZS_ZdpMatchDescConf for details.

\return
*******************************************************************************/
void ZS_ZdpMatchDescConf(ZS_ZdpMatchDescConf_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZdpBindReq with request status.

If the Bind_req is processed
and the Binding Table entry committed on the Remote Device, a Status of
SUCCESS is returned. If the Remote Device is not a Primary binding table cache
or the SrcAddress, a Status of NOT_SUPPORTED is returned. The supplied
endpoint shall be checked to determine whether it falls within the specified range.
If it does not, a Status of INVALID_EP shall be returned. If the Remote Device is
the Primary binding table cache or SrcAddress but does not have Binding Table
resources for the request, a Status of TABLE_FULL is returned.
ZigBee Specification r17, 2.4.4.2.2 Bind_rsp

\param[in] conf - Response status.
See description of ZS_ZdpBindConf_t for details.

\return
*******************************************************************************/
void ZS_ZdpBindConf(ZS_ZdpBindConf_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZdpUnbindReq with request status.

If the status is
SUCCESS, the device has successfully removed the binding entry for the
parameters specified in the Unbind_req.
ZigBee Specification r17, 2.4.4.2.3 Unbind_rsp

\param[in] conf - Response status.
See description of ZS_ZdpUnbindConf_t for details.

\return
*******************************************************************************/
void ZS_ZdpUnbindConf(ZS_ZdpUnbindConf_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Setting of tx power confirm

This function confirm setting operation.

\param[in] conf - Determines the parameters of the request.

\return
*******************************************************************************/
void ZS_ZdoSetTxPowerConf(ZS_ZdoSetTxPowerConf_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The Function is invoked in response to ZS_ZclReadAttributeReq call.
Implemented by user.

\param[in] resp - Holds result of request.
See ZS_ZclReadAttributeResp_t for details.

\return
*******************************************************************************/
void ZS_ZclReadAttributeResp(const ZS_ZclReadAttributeResp_t *resp)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The Function is invoked in response to ZS_ZclWriteAttributeReq call.
Implemented by user.

\param[in]
See ZS_ZclWriteAttributeResp_t for details.

\return
*******************************************************************************/
void ZS_ZclWriteAttributeResp(const ZS_ZclWriteAttributeResp_t *resp)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The Function is invoked in response to ZS_ZclConfigureReportingReq call.
Implemented by user.

\param[in]
See ZS_ZclConfigureReportingResp_t for details.

\return
*******************************************************************************/
void ZS_ZclConfigureReportingResp(const ZS_ZclConfigureReportingResp_t *resp)
{
 // Insert your code here
}
/***************************************************************************//**
\brief The Function is invoked in response to ZS_ZclDiscoverAttributesReq call.
Implemented by user.

\param[in]
See ZS_ZclDiscoverAttributesResp_t for details.

\return
*******************************************************************************/
void ZS_ZclDiscoverAttributesResp(const ZS_ZclDiscoverAttributesResp_t *resp)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The Function is invoked in response to ZS_ZclReadReportingConfigReq call.
Implemented by user.

\param[in]
See ZS_ZclReadReportingConfigResp_t for details.

\return
*******************************************************************************/
void ZS_ZclReadReportingConfigResp(const ZS_ZclReadReportingConfigResp_t *resp)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZseCommandReq with request status.

Returns status of command sending.

\param[in] conf - Request status.
See description of RZseCommandConfirm_t for details.

\return
*******************************************************************************/
void ZS_ZseCommandConf(RZseCommandConfirm_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The Function is invoked when an Identify command is received.
Implemented by user.

\param[in]
See ZS_ZclIdentifyInd_t for details.

\return
*******************************************************************************/
void ZS_ZclIdentifyInd(const ZS_ZclIdentifyInd_t *ind)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The Function is invoked when an Identify Query command is received.
Implemented by user.

\param[in]
See ZS_ZclIdentifyQueryInd_t for details.

\return
*******************************************************************************/
void ZS_ZclIdentifyQueryInd(const ZS_ZclIdentifyQueryInd_t *ind)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The Function is invoked when an Identify Query Response command is received.
Implemented by user.

\param[in]
See ZS_ZclIdentifyQueryResponseInd_t for details.

\return
*******************************************************************************/
void ZS_ZclIdentifyQueryResponseInd(const ZS_ZclIdentifyQueryResponseInd_t *ind)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Function is invoked when Get Current Price command is received.
Implemented by user.

\param[in]
See ZS_ZseGetCurrentPriceInd_t for details.

\return
*******************************************************************************/
void ZS_ZseGetCurrentPriceInd(const ZS_ZseGetCurrentPriceInd_t *ind)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Function is invoked when a Publish Price command is received.
Implemented by user.

\param[in]
See ZS_ZsePublishPriceInd_t for details.

\return
*******************************************************************************/
void ZS_ZsePublishPriceInd(const ZS_ZsePublishPriceInd_t *ind)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Function is invoke when a Report Event Status command is received.
Implemented by user.

\param[in]
See ZS_ZseReportEventStatusInd_t for details.

\return
*******************************************************************************/
void ZS_ZseReportEventStatusInd(const ZS_ZseReportEventStatusInd_t *ind)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Function is invoked when a Get Scheduled Events command is received.
Implemented by user.

\param[in]
See ZS_ZseGetScheduledEventsInd_t for details.

\return
*******************************************************************************/
void ZS_ZseGetScheduledEventsInd(const ZS_ZseGetScheduledEventsInd_t *ind)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Function is invoked when a Load Control Event command is received.
Implemented by user.

\param[in]
See ZS_ZseLoadControlEventInd_t for details.

\return
*******************************************************************************/
void ZS_ZseLoadControlEventInd(const ZS_ZseLoadControlEventInd_t *ind)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Function is invoke when a Cancel Load Control Event command is received.
Implemented by user.

\param[in]
See ZS_ZseCancelLoadControlEventInd_t for details.

\return
*******************************************************************************/
void ZS_ZseCancelLoadControlEventInd(const ZS_ZseCancelLoadControlEventInd_t *ind)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Function is invoked when a Cancel All Load Control Events command is
received.
Implemented by user.

\param[in]
See ZS_ZseCancelAllLoadControlEventsInd_t for details.

\return
*******************************************************************************/
void ZS_ZseCancelAllLoadControlEventsInd(const ZS_ZseCancelAllLoadControlEventsInd_t *ind)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The function is invoked when a Get Last Message command is received.
Implemented by user.

\param[in]
See ZS_ZseGetLastMessageInd_t for details.

\return
*******************************************************************************/
void ZS_ZseGetLastMessageInd(const ZS_ZseGetLastMessageInd_t *ind)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The function is invoked when a Message Confirmation command is received.
Implemented by user.

\param[in]
See ZS_ZseMessageConfirmationInd_t for details.

\return
*******************************************************************************/
void ZS_ZseMessageConfirmationInd(const ZS_ZseMessageConfirmationInd_t *ind)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The function is inoked when a Display Message command is received.
Implemented by user.

\param[in]
See ZS_ZseDisplayMessageInd_t for details.

\return
*******************************************************************************/
void ZS_ZseDisplayMessageInd(const ZS_ZseDisplayMessageInd_t *ind)
{
  // Insert your code here
}
/***************************************************************************//**
\brief The function is invoked when a Cancel Message command is received.
Implemented by user.

\param[in]
See ZS_ZseCancelMessageInd_t for details.

\return
*******************************************************************************/
void ZS_ZseCancelMessageInd(const ZS_ZseCancelMessageInd_t *ind)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZseStartReq with request status.

Returns status of start request.

\param[in] conf - Response status.
See description of RZseStartConfirm_t for details.

\return
*******************************************************************************/
void ZS_ZseStartConf(RZseStartConfirm_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Attribute reporting indication.

Notify of the latest values of one or more
of the attributes of another device.

ZigBee_Cluster_Library_Specification 075123r02ZB, 2.4.11.1 Report Attributes Command Frame Format

\param[in] ind - Indication details.
See description of ZS_ZseReportIndication_t for details.

\return
*******************************************************************************/
void ZS_ZseReportInd(ZS_ZseReportIndication_t* ind)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Attribute event indication.

Notifes about the actions take place on cluster's attribute.

\param[in] ind - Indication details.
See sescription of ZS_ZclAttributeEventInd_t for details.

\return
*******************************************************************************/
void ZS_ZclAttributeEventInd(ZS_ZclAttributeEventInd_t* ind)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZseGetReq with request status.

Returns requested option.

\param[in] conf - Response status.
See description of ZS_ZseGetConfirm_t for details.

\return
*******************************************************************************/
void ZS_ZseGetConf(ZS_ZseGetConfirm_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZseSetReq with request status.

Returns status of set operation.

\param[in] conf - Response status.
See description of RZseSetConfirm_t for details.

\return
*******************************************************************************/
void ZS_ZseSetConf(RZseSetConfirm_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZseReadAttributeValueReq with request status.

Returns values of requested attributes.

\param[in] conf - Request status.
See description of ZS_ZseReadAttributeValueConfirm_t for details.

\return
*******************************************************************************/
void ZS_ZseReadAttributeValueConf(ZS_ZseReadAttributeValueConfirm_t* conf)
{
  // Insert your code here
}
/***************************************************************************//**
\brief Callback on ZS_ZseWriteAttributeValueReq with request status.

Returns status of write operation.

\param[in] conf - Request status.
See description of ZS_ZseWriteAttributeValueConfirm_t for details.

\return
*******************************************************************************/
void ZS_ZseWriteAttributeValueConf(ZS_ZseWriteAttributeValueConfirm_t* conf)
{
  // Insert your code here
}

