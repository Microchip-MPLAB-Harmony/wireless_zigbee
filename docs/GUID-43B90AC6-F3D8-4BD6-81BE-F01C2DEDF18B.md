# ZGPL_FrameCounterReadorUpdateOnNvm Function

## C

```c
bool ZGPL_FrameCounterReadorUpdateOnNvm(uint32_t *frameCounter, ZGP_TableOperationField_t  tableOperationField , ZGP_GpdId_t *gpdId, uint8_t endPoint, \
```

## Description

 To read/update frameCounter

## Parameters

| Param | Description |
|:----- |:----------- |
| frameCounter | pointer to frameCounter |
| tableOperationField | filter field for frame counter operation |
| gpdId | address info |
| endPoint | GPD end point |
| isUpdateOperation | true for update false for read  

## Returns

   true for successful operation false otherwise 

