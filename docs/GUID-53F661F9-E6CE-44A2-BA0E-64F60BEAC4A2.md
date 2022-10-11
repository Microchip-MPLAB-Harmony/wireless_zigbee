# ZDO_GetNeibTable Function

## C

```c
void ZDO_GetNeibTable(ZDO_Neib_t *table);
```

## Description

 Retrieves the neighbor table

The function writes the contents of the neighbor table to the buffer specified by a
pointer to it. Note that not all entries of the neighbor table are included, namely
only neighbors with RELATIONSHIP_PARENT, RELATIONSHIP_CHILD, and RELATIONSHIP_NONE_OF_ABOVE
relationships are included (in addtition, this implies that unauthenticated children's
information is not retrieved). The  space for the buffer shall be allocated at compile
time, i.e. a variable for the buffer shall be static. The following code example
demonstrates a typical way to call the function:

```c
static ZDO_Neib_t neighborTable[CS_NEIB_TABLE_SIZE]; // Buffer for the neighbor table
...
ZDO_GetNeibTable(neighborTable);
```

## Parameters

| Param | Description |
|:----- |:----------- |
| [out] table | neighbor table  

## Returns

 None 

