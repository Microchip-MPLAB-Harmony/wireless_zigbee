# ZCL_GetCluster Function

## C

```c
ZCL_Cluster_t * ZCL_GetCluster(Endpoint_t endpointId, ClusterId_t clusterId, uint8_t clusterSide);
```

## Description

 Find cluster descriptor by endpoint id, cluster id.

## Parameters

| Param | Description |
|:----- |:----------- |
| endpointId | endpoint unique identifier. |
| clusterId | cluster unique identifier. |
| clusterSide | cluster side (client or server). 

## Returns

 ZCL cluster descriptor if found, NULL otherwise. 

