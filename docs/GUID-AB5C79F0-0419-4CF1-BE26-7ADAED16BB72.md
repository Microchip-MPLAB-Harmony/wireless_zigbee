# ZGPH_UpdateLocalSinkEntry Function

## C

```c
ZGP_InfraDeviceStatus_t ZGPH_UpdateLocalSinkEntry(ZGP_SinkTableEntry_t *sinkEntry, ZGP_SinkTableActions_t action);
```

## Description

 To update sink entry locally on NVM based on the given action

## Parameters

| Param | Description |
|:----- |:----------- |
| sinkEntry | entry fields(if proper security key(non-zero) is not provided, this will be derived based on gpsSharedKeyType |
| action | EXTEND_SINKTABLE_ENTRY/REMOVE_GPD supported  

## Returns

 status 

