# SYS_EventId_t Typedef

## C

```c
typedef uint8_t SYS_EventId_t;

```
## Description

  The type for event identifier Note that identifiers of events raised by the stack are defined in the ::BcEvents_t enumeration. The user can define its own set of
  event IDs in the application, subscribe to them and raise them,though the over all number of event IDs defined by both the stack and the application can not be greater than ::SYS_MAX_EVENTS, and an event ID value must not be greater than ::SYS_MAX_EVENTS.