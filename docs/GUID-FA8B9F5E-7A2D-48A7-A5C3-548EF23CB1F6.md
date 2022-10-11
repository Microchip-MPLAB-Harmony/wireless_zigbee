# BdbEventSubscriber_t Struct

## C

```c
typedef struct _BdbEventSubscriber_t
{
    struct
    {
        void *next;
    }service;
    /* Indicates the device has been (re)connected to the network */
    void (*connected)(void);
    /* Indicates the device has lost it connection to the network.*/
    void (*disconnected)(void);
    /* Network Formation Completed with Status */
    void (*networkFormationCompleted)(BDB_CommissioningStatus_t status);
    /* Indicates Network Steering is in progress either in network or not in network */
    void (*SteeringNetwork)(void);
    /* Indicates steering completion */
    void (*SteeringCompleted)(BDB_CommissioningStatus_t status);
    /* Indicates Touchlink scanning started */
    void (*scanning)(void);
    /* Indicates Touchlink identifying the target */
    void (*identifying)(void);
    /* Indicates joining during touchlink is in progress */
    void (*joining)(void);
    /* Indicates scan request reception */
    void (*scanIndication)(void);
    /* Requests the application to identify itself with the given timeout */
    void (*identifyStartIndication)(uint16_t timeoutInSec);
    /* Requests the application to stop identifying itself */
    void (*identifyStopIndication)(void);
    /* Requests the application to reset itself to factory defaults */
    void (*ResetToFactoryDefaults)(void);
    /* Indicates that the device has been linked to a new network by the initiator */
    void (*joinNetworkIndication)(uint16_t groupIdFirst, uint16_t groupIdLast);
    /* Touchlink Complete with status */
    void (*touchlinkCompleted)(BDB_CommissioningStatus_t status);
    /* Indication that the network settings of the device have been updated by the initiator.*/
    void (*updateNetworkIndication)(void);
    /* Indicates Trust center exchange procedure started */
    void (*tclkProcedureOngoing)(void);
    /* Indicates Trust center exchange procedure completed */
    void (*tclkProcedureCompleted)(void);
    /* Indicates identify querying for finding and binding */
    void (*querying)(void);
    /* Indicates identify query completed for finding and binding */
    void (*queryingCompleted)(void);
    /*Indicates binding links adding ongoing after touchlinking*/
    void (*addingBindingLinks)(void);
    /*Finding and binding completion with status*/
    void (*findingBindingCompleted)(BDB_CommissioningStatus_t status);
    /*Finding and binding initiator mode completion*/
    void (*findingBindingInitiatorModeCompleted)(void);
} BdbEventSubscriber_t;

```
## Description

Describes the parameters of the BDB_EventsSubscribe () function 
