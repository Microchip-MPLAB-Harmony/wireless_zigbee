# ZDO_StartNetworkConf_t Struct

## C

```c
typedef struct
{
    uint8_t       activeChannel; //!< Current channel on which the device has connected.
    ShortAddr_t   shortAddr;     //!< Assigned short address.
    PanId_t       PANId;         //!< Received short network PANId.
    uint64_t      extPANId;      //!< Received extended PANId if it was not determined during startup
    ShortAddr_t   parentAddr;    //!< Parent short address
    //Resulting status of a network start operation
    //See StartNwkStatuses "details".*/
    ZDO_Status_t  status;
} ZDO_StartNetworkConf_t;

```
## Description

  Describes the parameters of the ZDO_StartNetworkConf() function. 

