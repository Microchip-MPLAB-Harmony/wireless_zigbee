# BDB_InvokeCommissioningReq t

## C

```c
typedef struct
{
    /** Commissioning options to be executed */
    BDB_CommissioningMode_t mode;
    
    /** Parameters used in f&b and touchlink. Ignore if touchlink or finding and binding is
    not set in mode */
    BDB_InitiatorReq_t* initiatorReq;
    
    /** Parameters of the confirm being returned in BDB_InvokeCommissioningConf() */
    BDB_InvokeCommissioningConf_t confirm;
    
    /** The callback function to be called to confirm the request. Must not be set to NULL. */
    void (*BDB_InvokeCommissioningConf)(BDB_InvokeCommissioningConf_t *conf);
} BDB_InvokeCommissioningReq_t;

```
## Description

 Describes the parameters of the BDB_InvokeCommissioningReq() function