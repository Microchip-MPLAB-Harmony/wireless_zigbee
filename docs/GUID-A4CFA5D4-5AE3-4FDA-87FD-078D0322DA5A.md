# ZCL_WriteAttributeReq t

## C

```c
typedef struct PACK
{
    ZCL_AttributeId_t id;       //!< requested attribute id
    uint8_t           type;     //!< requested attribute type
    uint8_t           value[1]; //!< requested attribute value
} ZCL_WriteAttributeReq_t;

```

## Description
   Type describing payload element of write request commands.
   This type can be used to add one attribute entry to the write request payload.

