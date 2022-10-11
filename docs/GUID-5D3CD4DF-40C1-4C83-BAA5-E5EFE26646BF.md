# ZDO_ZdpReq_t struct

## C

```c
typedef struct
{
  //\cond internal
  struct
  {
    void *next;
#ifdef _ZAPPSI_
    /* to be compatible with MAC and SSP service. */
    uint8_t requestId;
    /* Sequence number to identify request-response pair. */
    uint8_t sequenceNumber;
    union
    {
      /* Callback wrapper routine pointer */
      void (*callback)(void*);
      /* Processing routine pointer to call after required memory will become free */
      void (*process)(void*);
    } zsi;
#endif /* _ZAPPSI_ */
    uint32_t ttl;
    uint8_t state;
    uint8_t seqNumCopy;  //used to prevent seq number encription
    APS_DataReq_t apsDataReq;
  } service;
  //\endcond

  // Address fields
  uint16_t   reqCluster; //!< Request's type; takes values from the \ref ZdpClustersList "enumeration"
  APS_AddrMode_t dstAddrMode; //!< Destination address mode, either short (network) address, group or extended address mode
  APS_Address_t dstAddress;
  // ZDP frame for sending out
  ZDO_ZdpFrame_t req; //!< ZDP request parameters
  //Callback and Response
  void (*ZDO_ZdpResp)(ZDO_ZdpResp_t *zdpResp); //!< Response callback. Must not be set to NULL.
  ZDO_ZdpResp_t resp; //!< ZDP response parameters
} ZDO_ZdpReq_t;

```
## Description

ZDP request Describes the parameters of the ZDO_ZdpReq() function.