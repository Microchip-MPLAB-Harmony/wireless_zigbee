# ZCL_Set Function

## C

```c
void ZCL_Set(ZCL_Set_t *req);
```

## Description

 Sets security parameters in ZCL

The function is used in profile-based applications to set various security
parameters including link keys, network key, and Key Establishment cluster's
data. The type of security parameter set by the funciton depends on the
value of the argument's \c attr.id field. Possible values are given by the
ZCL_SecurityAttrId_t enumeration type.

The function is executed synchronously.

Response statuses:
Accessed via the argument's ZCL_Set_t-status field


-ZCL_SUCCESS_STATUS (0x00) - operation completed successfully \n
-ZCL_INVALID_ATTRIBUTE_VALUE_STATUS (0x02) - the provided endpoint is invalid,

or null certificate description is provided  


-ZCL_TC_PERMISSION_TABLE_ERROR_STATUS (0x03) - adding the device to the TC

permission table has failed 


-ZCL_APS_LINK_KEY_ERROR_STATUS (0x04) - setting the link key via APS has failed \n
-ZCL_UNSUPPORTED_ATTRIBUTE_STATUS (0x86) - an unsupported value has been set

to the argument's \c attr.id field 


## Parameters

| Param | Description |
|:----- |:----------- |
| req | request structure to pass attribute id  

## Returns

 None 

