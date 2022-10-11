# ZGPH_SendProxyTableRequest Function

## C

```c
ZCL_Status_t ZGPH_SendProxyTableRequest(uint16_t addr, uint8_t options, uint64_t gpdId_Ieee, uint8_t ep, uint8_t index);
```

## Description

 Sending proxy table request.

## Parameters

| Param | Description |
|:----- |:----------- |
| addr | dst addr |
| options | options field |
| gpdId_Ieee | gpdId / IEEE addr |
| ep | ep for IEEE addr gpd |
| index | index field  

## Returns

 zcl status 

