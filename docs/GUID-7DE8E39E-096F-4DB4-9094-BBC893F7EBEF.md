# ZCL_NextElement_t struct

## C

```c
typedef struct
{
    uint8_t id; //!< Element's ID. Can be either ::ZCL_GeneralCommandId_t value or a special cluster command ID
    uint8_t payloadLength; //!< Payload's length after adding of a new element
    uint8_t *payload; //!< Payload's pointer to the place where an element is added
    void    *content; //!< Pointer to content (memory) which shall be added/filled to/from the payload
} ZCL_NextElement_t;

```
## Description
  Type describing information which is necessary for put/get element to/from payload

