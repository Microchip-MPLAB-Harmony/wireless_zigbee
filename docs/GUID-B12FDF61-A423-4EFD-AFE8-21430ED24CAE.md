# ZDO_ZdpReq Function

## C

```c
void ZDO_ZdpReq(ZDO_ZdpReq_t *zdpReq);
```

## Description

 Sends a ZDP request

This function is used by an application to send a ZigBee Device Profile (ZDP)
request. Request's type is  determined by the argument's ZDO_ZdpReq_t-reqCluster
field. Possible values are listed \ref ZdpClustersList "here". Specific
request's parameters are set in the req.reqPayload field.

Response statuses:
Accessed via the ZDO_ZdpRespFrame_t-status field of the ZDO_ZdpResp_t-respPayload
field of the ZDO_ZdpReq_t-ZDO_ZdpResp callback's argument 

All requests

-ZDO_SUCCESS_STATUS (0x00) - the request executed successfully \n
-ZDO_FAIL_STATUS (0x07) - unknown error occured \n
-ZDO_RESPONSE_WAIT_TIMEOUT_STATUS (0x02) - response has not been received

in required time. This status is not valid for the match descriptor
request. 


-ZDO_NOT_SUPPORTED_STATUS (0x84) - the requested feature is not

supported by the destination node 


-ZDO_NOT_AUTHORIZED_STATUS (0x8D) - the node is not authorized to make such request \n\n

Match descriptor request

-ZDO_CMD_COMPLETED_STATUS (0x0D) - response timer has expired - not more responses

for the current request will be processed 

Binding request

-ZDO_NO_ENTRY_STATUS (0x88) - unbinding request is unsuccessful, because the requested

entry has not been found in the binding table 


-ZDO_TABLE_FULL_STATUS (0x8C) - the destination binding table is full
-ZDO_INVALID_REQUEST_STATUS (0x80) - invalid parameters have been provided (endpoint ID is

out of range, incorrect destination addressing mode is used - APS_EXT_ADDRESS is
expected, etc.) 

Simple descriptor and complex descriptor requests

-ZDO_INVALID_EP_STATUS (0x82) - the specified endpoint has not been found on the

destination node 

End device binding request

-ZDO_NOT_PERMITTED_STATUS (0x8B) - indicates that the coordinator has already

received end device binding requests from two other devices and cannot process one
more request 

## Parameters

| Param | Description |
|:----- |:----------- |
| zdpReq | Determines the parameters of the ZDP request 

## Returns

 None 

