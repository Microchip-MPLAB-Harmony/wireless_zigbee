# SimpleDescriptor_t Struct

## C

```c
typedef struct PACK
{
    /*! ID of the endpoint within the node to which this description refers.
    Applications shall only use endpoints 1-240. */
    Endpoint_t   endpoint;
    /*! Profile that is supported on this endpoint. */
    ProfileId_t  AppProfileId;
    /*! Device description supported on this endpoint. */
    uint16_t     AppDeviceId;
    /*! Version of the device description supported on this endpoint. */
    uint8_t      AppDeviceVersion : 4;
    /*! Reserved. */
    uint8_t      Reserved         : 4;
    /*! Number of input clusters supported on this endpoint. If 0, the
    application input cluster list field shall not be included. */
    uint8_t      AppInClustersCount;
    /*! List of input clusters supported on this endpoint. */
    ClusterId_t* AppInClustersList;
    /*! Number of output clusters supported on this endpoint. If 0, the
    application output cluster list field shall not be included. */
    uint8_t      AppOutClustersCount;
    /*! List of output clusters supported on this endpoint. */
    ClusterId_t* AppOutClustersList;
} SimpleDescriptor_t;

```
## Description

  Simple Descriptor
  Mandatory for each endpoint present in the node. 




