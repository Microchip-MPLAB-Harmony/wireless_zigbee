# SYS_EventReceiver_t struct

## C

```c
typedef struct _SYS_EventReceiver_t
{
    // Internal service fields for handler.
    // Do not rely on them.
    // They may be changed at future releases.
    //\cond internal
  SYS_EventService_t service;
    SYS_EventService_t service;
    //\endcond

    
    /** Function to be called on event. Must not be set to NULL. */
    void (*func)(SYS_EventId_t id, SYS_EventData_t data);
} SYS_EventReceiver_t;

```
## Description

Structure for declaring an event receiver

