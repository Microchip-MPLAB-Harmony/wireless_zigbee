# ZCL_WriteAttributeValue Function

## C

```c
ZCL_Status_t ZCL_WriteAttributeValue(Endpoint_t endpointId, ClusterId_t clusterId,uint8_t clusterSide,
                                    ZCL_AttributeId_t attrId, uint8_t attrType, uint8_t *attrValue);
```

## Description

 Finds an attribute in ZCL and rewrites its value by the new one

The function may be used to set or rewrite only local attributes.
Affects attribute reporting on change.
To set a new value to an attribute on a remote device, send a write attributes
general cluster command via the ZCL_AttributeReq() function.

## Parameters

| Param | Description |
|:----- |:----------- |
| endpointId | endpoint on which cluster is registered |
| clusterId | cluster unique identifier |
| clusterSide | detects the cluster's side (client or server) |
| attrId | attribute unique identifier |
| attrType | type of the attribute to be set |
| attrValue | pointer to attribute value to be set  

## Returns

 The status of the operation:
*::ZCL_SUCCESS_STATUS (0x00)* - new value has been written successfully

*::ZCL_UNSUPPORTED_ATTRIBUTE_STATUS (0x86)* - the specified attribute is not supported 

*::ZCL_INVALID_PARAMETER_STATUS (0xFF)* - NULL has been provided as the attribute's value

*::ZCL_INVALID_DATA_TYPE_STATUS (0x8D)* - the attribute's type is not the same as specified
in the argument
*::ZCL_READ_ONLY_STATUS (0x88)* - the attribute's value cannot be changed,
because the attribute is read-only 

