# ZDO_BindIndication Function

## C

```c
void ZDO_BindIndication(ZDO_BindInd_t *bindInd);
```

## Description

 Indicates that a new binding has been added to the local binding table

The function must be implemented by the application (the body may be left empty).
The function is called by the stack when a ZDP binding request initiated either
by a remote device or by the local device is executed (a new binding entry is
added).

When the APS_BindReq() function is called to add a new entry to the local binding
table the indication function is not called.

## Parameters

| Param | Description |
|:----- |:----------- |
| bindInd | ZDO bind indication parameters structure pointer. For details go to ZDO_BindInd_t declaration. 

## Returns

 None  


