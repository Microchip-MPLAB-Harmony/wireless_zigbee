# ZGPL_IsValidSrcId Function

## C

```c
bool ZGPL_IsValidSrcId(uint32_t srcId, ZGP_FrameType_t frameType, bool isPairingConfig);
```

## Description

 To check whether the SrcID is valid or not considering the Frame Type

## Parameters

| Param | Description |
|:----- |:----------- |
| srcId | GPD srcId |
| frameType | Maintanence Frame/Data Frame |
| isPairingConfig | srcId received in PairingConfig/Commissioning  

## Returns

   true if srcId is Valid false otherwise 

