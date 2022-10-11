# ZDO_ResolveAddrReq Function

## C

```c
void ZDO_ResolveAddrReq(ZDO_ResolveAddrReq_t *req);
```

## Description

 Determines the missing short address corresponding to the given extended
address or the missing extended address corresponding to the given short address

The function sends a ZDP request: either an IEEE address ZDP request if the extended
address should be determined, or a short address ZDP request if the short address
should be determined. The callback function reports the result of ZDP request
execution. If the request has completed successfully, the requested addressing
info is provided in the argument.

The function is called by the stack in several cases when one element in a pair of
short and extended addresses of the same device is unknown. These cases include
sending a data request when soome information about destination is lacking:

-APS_EXT_ADDRESS or -APS_NO_ADDRESS (send to bound devices) addressing modes are used,

but the short address is not known; short address addressing
is used, and link key security is used, but the extended address to find out the
link key is not known. The stack also checks if the extended address is known
when it receives an encrypted frame.

Response statuses:
Accessed via the ZDO_ResolveAddrConf_t-status field of the
ZDO_ResolveAddrReq_t-ZDO_ResolveAddrConf callback's argument 


-ZDO_SUCCESS_STATUS (0x00) - the requested short or extended address has been

successfully determined 


-ZDO_INVALID_REQUEST_STATUS (0x80) - the address resolving module is disabled \n

Any of error codes reported by the ZDO_ZdpReq() function

## Parameters

| Param | Description |
|:----- |:----------- |
| req | request structure to pass attribute id  

## Returns

 None 

