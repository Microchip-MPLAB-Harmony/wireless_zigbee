# ZCL_Cluster_t struct

## C

```c
typedef struct
{
    ClusterId_t          id;                 //!< Cluster ID
    ZCL_ClusterOptions_t options;
    uint8_t              attributesAmount;   //!< Number of cluster attributes
    uint8_t             *attributes;         //!< Cluster attribute descriptors
    uint8_t              commandsAmount;     //!< Number of cluster-specific commands
    uint8_t             *commands;           //!< Cluster-specific command descriptors
    uint8_t              isReporting;        //!< Service field - indicates if any automatic attribute reports are in progress
    //! Callback on Report attributes command reception. Can be set to NULL.
    void (*ZCL_ReportInd)(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload);
    //! Callback on Default response command reception. Can be set to NULL.
    void (*ZCL_DefaultRespInd)(ZCL_Request_t *req, ZCL_Addressing_t *addressing, uint8_t payloadLength, uint8_t *payload);
    //! Callback indicates action on cluster's attribute. Can be set to NULL.
    void (*ZCL_AttributeEventInd)(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event);
} ZCL_Cluster_t;

```
## Description

 Type describing ZCL Cluster
