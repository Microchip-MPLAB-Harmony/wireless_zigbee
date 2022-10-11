# SYS_TaskId_t Enum

## C

```c
typedef enum
{
    MAC_PHY_HWD_TASK_ID = 1 << 0, //!< Task ID of the MAC-PHY-HWD layer
    
    HAL_TASK_ID         = 1 << 1, //!< Task ID of HAL (Hardware Abstraction Layer)
    
    MAC_HWI_TASK_ID     = 1 << 2, //!< Task ID of the MAC-HWI layer (a part of MAC independent of radio)
    
    NWK_TASK_ID         = 1 << 3, //!< Task ID of the NWK layer
    
    ZDO_TASK_ID         = 1 << 4, //!< Task ID of the ZDO layer
    
    APS_TASK_ID         = 1 << 5, //!< Task ID of the APS layer
    
    ZGP_TASK_ID         = 1 << 6, //!< Task ID of the ZGP layer
    
    SSP_TASK_ID         = 1 << 7, //!< Task ID of Security Service Provider
    
    TC_TASK_ID          = 1 << 8, //!< Task ID of the Trust Center component
    
    ZSI_TASK_ID         = 1 << 9, //!< Task ID of the ZAppSI component
    
    ZCL_TASK_ID         = 1 << 10, //!< Task ID of ZigBee Cluster Library
    
    ZLL_TASK_ID         = 1 << 11, //!< Service Task ID
    
    APL_TASK_ID         = 1 << 12, //!< Task ID of the application
    
    ZGP_DSTUB_TASK_ID   = 1 << 13, //!<Task ID of the ZGP Dstub component
    
} SYS_TaskId_t;

```
## Description

 The list of task IDs. The IDs are sorted according to descending priority. For each task ID there is the corresponding task handler function.








