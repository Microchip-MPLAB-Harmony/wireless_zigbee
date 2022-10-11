# SYS_MutexOwner_t struct

## C

```c
typedef struct _SYS_MutexOwner_t
{
    /** Service fields - for internal needs. */
    struct
    {
        QueueElement_t qelem; /**< link used for queuing */
    } service;
    /** Purpose of this parameter is to save owner's execution context. It's up
    to the owner how to use this parameter. Mutex implementation must not
    modify this parameter. */
    void *context;
    /** This function is called in the case when the SYS_MutexLock() operation
    was postponed and now the mutex is locked by the owner. */
    void (*SYS_MutexLockConf)(SYS_Mutex_t *const mutex, void *context);
} SYS_MutexOwner_t;

```
## Description

Type of mutex owner.




