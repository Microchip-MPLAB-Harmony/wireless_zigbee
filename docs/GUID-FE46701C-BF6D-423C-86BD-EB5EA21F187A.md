# APS_RemoveGroupReq_t Struct

## C

```c
typedef struct
{
    /**  Endian "[LE]" The 16-bit address of the group being removed. */
  GroupAddr_t groupAddress;
    /** The endpoint at which the given group is being removed. */
    Endpoint_t endpoint;
    
    /** The confirm primitive containing the result of the function call. */
    APS_RemoveGroupConf_t confirm;
} APS_RemoveGroupReq_t;

```
## Description

  struct APS_RemoveGroupReq_t apsmeGroup.h "aps.h"
  Parameters of the APS_RemoveGroupReq() function.







