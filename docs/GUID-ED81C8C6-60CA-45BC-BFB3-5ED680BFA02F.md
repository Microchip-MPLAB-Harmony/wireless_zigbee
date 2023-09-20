# ZDO_FindShortByExt Function

## C

```c
const ShortAddr_t* ZDO_FindShortByExt(const ExtAddr_t *const extAddr);
```

## Description

 Determines NWK address by Extended 64-bit address.
## Parameters

| Param | Description |
|:----- |:----------- |
| extAddr | extended 64-bit IEEE address 

## Returns

 pointer to a valid NWK short address if it has been found, NULL otherwise. 

