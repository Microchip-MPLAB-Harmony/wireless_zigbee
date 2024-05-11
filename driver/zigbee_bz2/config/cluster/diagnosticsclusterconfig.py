"""*****************************************************************************
* Copyright (C) 2022 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*****************************************************************************"""

############################################################################################################
###########################################  DIAGONSTICS CLUSTER CONFIGURATION   ###########################
############################################################################################################

############################################################################################################
############################################# Function Definitions #########################################
############################################################################################################
def diagnosticsClusterCsCheck(symbol, event):
    if (diagnosticsCluster.getValue() == False):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def diagnosticsClusterEnableCheck(symbol, event):
    if (diagnosticsCluster.getValue() == False):
        symbol.setEnabled(False)
    else:
        symbol.setEnabled(True)

def customDiagnosticsClusterEnableCheck(symbol, event):
    if ((zigbeeDeviceType.getValue() == 'ZIGBEE_CUSTOM') and (diagnosticsCluster.getValue() == True)):
        symbol.setEnabled(True)
    else:
        symbol.setEnabled(False)

def diagnosticsClusterClientCheck(symbol, event):
    if ((diagnosticsCluster.getValue() == False) or diagnosticsClusterCS.getValue() == "SERVER"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def diagnosticsClusterServerCheck(symbol, event):
    if ((diagnosticsCluster.getValue() == False) or diagnosticsClusterCS.getValue() == "CLIENT"):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def diagnosticsClusterHandling():

    getDevice = zigbeeDeviceType.getValue()

    if ((getDevice == "ZIGBEE_COLOR_SCENE_CONTROLLER")
        or (getDevice == "ZIGBEE_CONTROL_BRIDGE")
        or (getDevice == "ZIGBEE_IAS_ACE")
        or (getDevice == "ZIGBEE_ON_OFF_LIGHT")
        or (getDevice == "ZIGBEE_DIMMABLE_LIGHT")
        or (getDevice == "ZIGBEE_COLOR_LIGHT")
        or (getDevice == "ZIGBEE_EXTENDED_COLOR_LIGHT")
        or (getDevice == "ZIGBEE_TEMPERATURE_COLOR_LIGHT")
        or (getDevice == "ZIGBEE_COMBINED_INTERFACE")
        or (getDevice == "ZIGBEE_THERMOSTAT")
        ):
        diagnosticsCluster.setVisible(False)
        diagnosticsCluster.setValue(False)
    elif ((getDevice == "ZIGBEE_MULTI_SENSOR")):
        diagnosticsCluster.setVisible(True)
        diagnosticsCluster.setValue(True)
        diagnosticsCluster.setReadOnly(True)
        diagnosticsClusterCS.setValue("SERVER")
        diagnosticsClusterCS.setReadOnly(True)
    elif ((getDevice == "ZIGBEE_CUSTOM")):
        diagnosticsCluster.setVisible(True)
        diagnosticsCluster.setValue(False)
        diagnosticsClusterCS.setValue("SERVER")
        diagnosticsClusterCS.setReadOnly(True)
        diagnosticsClusterClientMenu.setVisible(False) 
        diagnosticsClusterServerMenu.setVisible(True)
    else:
        diagnosticsCluster.setVisible(False)

def diagnosticsClusterServerAttributeCountUpdate(symbol, event):
    count = 0
    # if (diagnosticsClusterServerAttributeNumberOfResets.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributePersistentMemoryWrites.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeMacRxBcast.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeMacTxBcast.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeMacRxUcast.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeMacTxUcast.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeMacTxUcastRetry.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeMacTxUcastFail.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeAPSTxBcast.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeAPSRxUcast.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeAPSTxUcast.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeAPSTxUcastSuccess.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeAPSTxUcastRetry.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeAPSTxUcastFail.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeRouteDiscInitiated.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeNeighborAdded.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeNeighborRemoved.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeNeighborStale.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeJoinIndication.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeChildMoved.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeNWKFCFailure.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeAPSFCFailure.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeAPSUnauthorizedKey.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeNWKDecryptFailures.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeAPSDecryptFailures.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributePacketBufferAllocateFailures.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributeRelayedUcast.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributePhyToMACQueueLimitReached.getValue()):
        # count += 1
    # if (diagnosticsClusterServerAttributePacketValidateDropCount.getValue()):
        # count += 1
    if (diagnosticsClusterServerAttributeAverageMACRetryPerAPSMessageSent.getValue()):
        count += 1
    if (diagnosticsClusterServerAttributeLastMessageLQI.getValue()):
        count += 1
    if (diagnosticsClusterServerAttributeLastMessageRSSI.getValue()):
        count += 1
    if (diagnosticsClusterServerAttributeClusterRevision.getValue()):
        count += 1
    diagnosticsClusterServerAttributeCount.setValue(count) 
    return count

def diagnosticsClusterClientAttributeCountUpdate(symbol, event):
    count = 0
    if (diagnosticsClusterClientAttributeClusterRevision.getValue()):
        count += 1
    diagnosticsClusterClientAttributeCount.setValue(count)
    return count
############################################################################################################
##################################### Configuration Item Definitions #######################################
############################################################################################################

global diagnosticsCluster
diagnosticsCluster = drvZigbeeComponent.createBooleanSymbol("DIAGONSTICS_CLUSTER_ENABLE", clusterConfigMenu)
diagnosticsCluster.setLabel("0x0B05 Diagnostics Cluster")
diagnosticsCluster.setDefaultValue(False)
diagnosticsCluster.setVisible(False)
diagnosticsCluster.setDescription("DIAGONSTICS CLUSTER- check the box to enable")
diagnosticsCluster.setReadOnly(False)

global diagnosticsClusterCS
diagnosticsClusterCS = drvZigbeeComponent.createComboSymbol("DIAGONSTICS_CLUSTER_CS",  diagnosticsCluster, ["CLIENT","SERVER", "BOTH"])
diagnosticsClusterCS.setLabel("Supported Implementation")
diagnosticsClusterCS.setDefaultValue("BOTH")
#diagnosticsClusterCS.setVisible(False)
diagnosticsClusterCS.setDescription("Diagnostics Cluster Supported Implementation- Select the option")
diagnosticsClusterCS.setDependencies(diagnosticsClusterCsCheck,["DIAGONSTICS_CLUSTER_ENABLE"])

global diagnosticsClusterClientMenu
diagnosticsClusterClientMenu = drvZigbeeComponent.createMenuSymbol("DIAGONSTICS_CLUSTER_CLIENT_MENU", diagnosticsCluster)
diagnosticsClusterClientMenu.setLabel("Client")
#diagnosticsClusterClientMenu.setVisible(False)
diagnosticsClusterClientMenu.setDescription("DIAGONSTICS CLUSTER CLIENT")
diagnosticsClusterClientMenu.setDependencies(diagnosticsClusterClientCheck,["DIAGONSTICS_CLUSTER_CS","DIAGONSTICS_CLUSTER_ENABLE"])

global diagnosticsClusterServerMenu
diagnosticsClusterServerMenu = drvZigbeeComponent.createMenuSymbol("DIAGONSTICS_CLUSTER_SERVER_MENU", diagnosticsCluster)
diagnosticsClusterServerMenu.setLabel("Server")
#diagnosticsClusterServerMenu.setVisible(False)
diagnosticsClusterServerMenu.setDescription("DIAGONSTICS CLUSTER SERVER")
diagnosticsClusterServerMenu.setDependencies(diagnosticsClusterServerCheck,["DIAGONSTICS_CLUSTER_CS","DIAGONSTICS_CLUSTER_ENABLE"])

diagnosticsClusterClientAttributes = drvZigbeeComponent.createMenuSymbol("DIAGONSTICS_CLUSTER_CLIENT__ATTRIBUTES_MENU", diagnosticsClusterClientMenu)
diagnosticsClusterClientAttributes.setLabel("Attributes")
#diagnosticsClusterClientAttributes.setVisible(False)
diagnosticsClusterClientAttributes.setDescription("DIAGONSTICS CLUSTER CLIENT ATTRIBUTES")
diagnosticsClusterClientAttributes.setDependencies(diagnosticsClusterClientCheck,["DIAGONSTICS_CLUSTER_CS"])

#diagnosticsClusterClientCommands = drvZigbeeComponent.createMenuSymbol("DIAGONSTICS_CLUSTER_CLIENT__COMMANDS_MENU", diagnosticsClusterClientMenu)
#diagnosticsClusterClientCommands.setLabel("Commands")
##diagnosticsClusterClientCommands.setVisible(False)
#diagnosticsClusterClientCommands.setDescription("DIAGONSTICS CLUSTER CLIENT COMMANDS")
#diagnosticsClusterClientCommands.setDependencies(diagnosticsClusterClientCheck,["DIAGONSTICS_CLUSTER_CS"])

diagnosticsClusterServerAttributes = drvZigbeeComponent.createMenuSymbol("DIAGONSTICS_CLUSTER_SERVER__ATTRIBUTES_MENU", diagnosticsClusterServerMenu)
diagnosticsClusterServerAttributes.setLabel("Attributes")
#diagnosticsClusterServerAttributes.setVisible(False)
diagnosticsClusterServerAttributes.setDescription("DIAGONSTICS CLUSTER SERVER ATTRIBUTES")
diagnosticsClusterServerAttributes.setDependencies(diagnosticsClusterServerCheck,["DIAGONSTICS_CLUSTER_CS"])

#diagnosticsClusterServerCommands = drvZigbeeComponent.createMenuSymbol("DIAGONSTICS_CLUSTER_SERVER__COMMANDS_MENU", diagnosticsClusterServerMenu)
#diagnosticsClusterServerCommands.setLabel("Commands")
##diagnosticsClusterServerCommands.setVisible(False)
#diagnosticsClusterServerCommands.setDescription("DIAGONSTICS CLUSTER SERVER COMMANDS")
#diagnosticsClusterServerCommands.setDependencies(diagnosticsClusterServerCheck,["DIAGONSTICS_CLUSTER_CS"])

#################               Server Attributes                                 ###############

global diagnosticsClusterServerAttributeNumberOfResets 
diagnosticsClusterServerAttributeNumberOfResets = drvZigbeeComponent.createBooleanSymbol("DC_NUMBEROFRESETS", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeNumberOfResets.setLabel("0x0000 NumberOfResets")
diagnosticsClusterServerAttributeNumberOfResets.setDefaultValue(True)
diagnosticsClusterServerAttributeNumberOfResets.setDescription("NumberOfResets - check the box to enable")
diagnosticsClusterServerAttributeNumberOfResets.setVisible(False)

global diagnosticsClusterServerAttributePersistentMemoryWrites
diagnosticsClusterServerAttributePersistentMemoryWrites = drvZigbeeComponent.createBooleanSymbol("DC_PERSISTENTMEMORYWRITES", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributePersistentMemoryWrites.setLabel("0x0001 PersistentMemoryWrites")
diagnosticsClusterServerAttributePersistentMemoryWrites.setDefaultValue(True)
diagnosticsClusterServerAttributePersistentMemoryWrites.setDescription("PersistentMemoryWrites - check the box to enable")
diagnosticsClusterServerAttributePersistentMemoryWrites.setVisible(False)

global diagnosticsClusterServerAttributeMacRxBcast
diagnosticsClusterServerAttributeMacRxBcast = drvZigbeeComponent.createBooleanSymbol("DC_MACRXBCAST", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeMacRxBcast.setLabel("0x0100 MacRxBcast")
diagnosticsClusterServerAttributeMacRxBcast.setDefaultValue(True)
diagnosticsClusterServerAttributeMacRxBcast.setDescription("MacRxBcast - check the box to enable")
diagnosticsClusterServerAttributeMacRxBcast.setVisible(False)

global diagnosticsClusterServerAttributeMacTxBcast
diagnosticsClusterServerAttributeMacTxBcast = drvZigbeeComponent.createBooleanSymbol("DC_MACTXBCAST", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeMacTxBcast.setLabel("0x0101 MacTxBcast")
diagnosticsClusterServerAttributeMacTxBcast.setDefaultValue(True)
diagnosticsClusterServerAttributeMacTxBcast.setDescription("MacTxBcast - check the box to enable")
diagnosticsClusterServerAttributeMacTxBcast.setVisible(False)

global diagnosticsClusterServerAttributeMacRxUcast
diagnosticsClusterServerAttributeMacRxUcast = drvZigbeeComponent.createBooleanSymbol("DC_MACRXUCAST", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeMacRxUcast.setLabel("0x0102 MacRxUcast")
diagnosticsClusterServerAttributeMacRxUcast.setDefaultValue(True)
diagnosticsClusterServerAttributeMacRxUcast.setDescription("MacRxUcast - check the box to enable")
diagnosticsClusterServerAttributeMacRxUcast.setVisible(False)

global diagnosticsClusterServerAttributeMacTxUcast
diagnosticsClusterServerAttributeMacTxUcast = drvZigbeeComponent.createBooleanSymbol("DC_MACTXUCAST", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeMacTxUcast.setLabel("0x0103 MacTxUcast")
diagnosticsClusterServerAttributeMacTxUcast.setDefaultValue(True)
diagnosticsClusterServerAttributeMacTxUcast.setDescription("MacTxUcast - check the box to enable")
diagnosticsClusterServerAttributeMacTxUcast.setVisible(False)

global diagnosticsClusterServerAttributeMacTxUcastRetry
diagnosticsClusterServerAttributeMacTxUcastRetry = drvZigbeeComponent.createBooleanSymbol("DC_MACTXUCASTRETRY", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeMacTxUcastRetry.setLabel("0x0104 MacTxUcastRetry")
diagnosticsClusterServerAttributeMacTxUcastRetry.setDefaultValue(True)
diagnosticsClusterServerAttributeMacTxUcastRetry.setDescription("MacTxUcastRetry - check the box to enable")
diagnosticsClusterServerAttributeMacTxUcastRetry.setVisible(False)

global diagnosticsClusterServerAttributeMacTxUcastFail
diagnosticsClusterServerAttributeMacTxUcastFail = drvZigbeeComponent.createBooleanSymbol("DC_MACTXUCASTFAIL", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeMacTxUcastFail.setLabel("0x0105 MacTxUcastFail")
diagnosticsClusterServerAttributeMacTxUcastFail.setDefaultValue(True)
diagnosticsClusterServerAttributeMacTxUcastFail.setDescription("MacTxUcastFail - check the box to enable")
diagnosticsClusterServerAttributeMacTxUcastFail.setVisible(False)

global diagnosticsClusterServerAttributeAPSTxBcast
diagnosticsClusterServerAttributeAPSTxBcast = drvZigbeeComponent.createBooleanSymbol("DC_APSTXBCAST", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeAPSTxBcast.setLabel("0x0106 APSTxBcast")
diagnosticsClusterServerAttributeAPSTxBcast.setDefaultValue(True)
diagnosticsClusterServerAttributeAPSTxBcast.setDescription("APSTxBcast - check the box to enable")
diagnosticsClusterServerAttributeAPSTxBcast.setVisible(False)

global diagnosticsClusterServerAttributeAPSRxUcast
diagnosticsClusterServerAttributeAPSRxUcast = drvZigbeeComponent.createBooleanSymbol("DC_APSRXUCAST", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeAPSRxUcast.setLabel("0x0107 APSRxUcast")
diagnosticsClusterServerAttributeAPSRxUcast.setDefaultValue(True)
diagnosticsClusterServerAttributeAPSRxUcast.setDescription("APSRxUcast - check the box to enable")
diagnosticsClusterServerAttributeAPSRxUcast.setVisible(False)

global diagnosticsClusterServerAttributeAPSTxUcast
diagnosticsClusterServerAttributeAPSTxUcast = drvZigbeeComponent.createBooleanSymbol("DC_APSTXUCAST", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeAPSTxUcast.setLabel("0x0108 APSTxUcast")
diagnosticsClusterServerAttributeAPSTxUcast.setDefaultValue(True)
diagnosticsClusterServerAttributeAPSTxUcast.setDescription("APSTxUcast - check the box to enable")
diagnosticsClusterServerAttributeAPSTxUcast.setVisible(False)

global diagnosticsClusterServerAttributeAPSTxUcastSuccess
diagnosticsClusterServerAttributeAPSTxUcastSuccess = drvZigbeeComponent.createBooleanSymbol("DC_APSTXUCASTSUCCESS", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeAPSTxUcastSuccess.setLabel("0x0109 APSTxUcastSuccess")
diagnosticsClusterServerAttributeAPSTxUcastSuccess.setDefaultValue(True)
diagnosticsClusterServerAttributeAPSTxUcastSuccess.setDescription("APSTxUcastSuccess - check the box to enable")
diagnosticsClusterServerAttributeAPSTxUcastSuccess.setVisible(False)

global diagnosticsClusterServerAttributeAPSTxUcastRetry
diagnosticsClusterServerAttributeAPSTxUcastRetry = drvZigbeeComponent.createBooleanSymbol("DC_APSTXUCASTRETRY", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeAPSTxUcastRetry.setLabel("0x010A APSTxUcastRetry")
diagnosticsClusterServerAttributeAPSTxUcastRetry.setDefaultValue(True)
diagnosticsClusterServerAttributeAPSTxUcastRetry.setDescription("APSTxUcastRetry - check the box to enable")
diagnosticsClusterServerAttributeAPSTxUcastRetry.setVisible(False)

global diagnosticsClusterServerAttributeAPSTxUcastFail
diagnosticsClusterServerAttributeAPSTxUcastFail = drvZigbeeComponent.createBooleanSymbol("DC_APSTXUCASTFAIL", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeAPSTxUcastFail.setLabel("0x010B APSTxUcastFail")
diagnosticsClusterServerAttributeAPSTxUcastFail.setDefaultValue(True)
diagnosticsClusterServerAttributeAPSTxUcastFail.setDescription("APSTxUcastFail - check the box to enable")
diagnosticsClusterServerAttributeAPSTxUcastFail.setVisible(False)

global diagnosticsClusterServerAttributeRouteDiscInitiated
diagnosticsClusterServerAttributeRouteDiscInitiated = drvZigbeeComponent.createBooleanSymbol("DC_ROUTEDISCINITIATED", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeRouteDiscInitiated.setLabel("0x010C RouteDiscInitiated")
diagnosticsClusterServerAttributeRouteDiscInitiated.setDefaultValue(True)
diagnosticsClusterServerAttributeRouteDiscInitiated.setDescription("RouteDiscInitiated - check the box to enable")
diagnosticsClusterServerAttributeRouteDiscInitiated.setVisible(False)

global diagnosticsClusterServerAttributeNeighborAdded
diagnosticsClusterServerAttributeNeighborAdded = drvZigbeeComponent.createBooleanSymbol("DC_NEIGHBORADDED", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeNeighborAdded.setLabel("0x010D NeighborAdded")
diagnosticsClusterServerAttributeNeighborAdded.setDefaultValue(True)
diagnosticsClusterServerAttributeNeighborAdded.setDescription("NeighborAdded - check the box to enable")
diagnosticsClusterServerAttributeNeighborAdded.setVisible(False)

global diagnosticsClusterServerAttributeNeighborRemoved
diagnosticsClusterServerAttributeNeighborRemoved = drvZigbeeComponent.createBooleanSymbol("DC_NEIGHBORREMOVED", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeNeighborRemoved.setLabel("0x010E NeighborRemoved")
diagnosticsClusterServerAttributeNeighborRemoved.setDefaultValue(True)
diagnosticsClusterServerAttributeNeighborRemoved.setDescription("NeighborRemoved - check the box to enable")
diagnosticsClusterServerAttributeNeighborRemoved.setVisible(False)

global diagnosticsClusterServerAttributeNeighborStale
diagnosticsClusterServerAttributeNeighborStale = drvZigbeeComponent.createBooleanSymbol("DC_NEIGHBORSTALE", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeNeighborStale.setLabel("0x010F NeighborStale")
diagnosticsClusterServerAttributeNeighborStale.setDefaultValue(True)
diagnosticsClusterServerAttributeNeighborStale.setDescription("NeighborStale - check the box to enable")
diagnosticsClusterServerAttributeNeighborStale.setVisible(False)

global diagnosticsClusterServerAttributeJoinIndication
diagnosticsClusterServerAttributeJoinIndication = drvZigbeeComponent.createBooleanSymbol("DC_JOININDICATION", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeJoinIndication.setLabel("0x0110 JoinIndication")
diagnosticsClusterServerAttributeJoinIndication.setDefaultValue(True)
diagnosticsClusterServerAttributeJoinIndication.setDescription("JoinIndication - check the box to enable")
diagnosticsClusterServerAttributeJoinIndication.setVisible(False)

global diagnosticsClusterServerAttributeChildMoved
diagnosticsClusterServerAttributeChildMoved = drvZigbeeComponent.createBooleanSymbol("DC_CHILDMOVED", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeChildMoved.setLabel("0x0111 ChildMoved")
diagnosticsClusterServerAttributeChildMoved.setDefaultValue(True)
diagnosticsClusterServerAttributeChildMoved.setDescription("ChildMoved - check the box to enable")
diagnosticsClusterServerAttributeChildMoved.setVisible(False)

global diagnosticsClusterServerAttributeNWKFCFailure
diagnosticsClusterServerAttributeNWKFCFailure = drvZigbeeComponent.createBooleanSymbol("DC_NWKCFAILURE", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeNWKFCFailure.setLabel("0x0112 NWKFCFailure")
diagnosticsClusterServerAttributeNWKFCFailure.setDefaultValue(True)
diagnosticsClusterServerAttributeNWKFCFailure.setDescription("NWKFCFailure - check the box to enable")
diagnosticsClusterServerAttributeNWKFCFailure.setVisible(False)

global diagnosticsClusterServerAttributeAPSFCFailure
diagnosticsClusterServerAttributeAPSFCFailure = drvZigbeeComponent.createBooleanSymbol("DC_APSCFAILURE", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeAPSFCFailure.setLabel("0x0113 APSFCFailure")
diagnosticsClusterServerAttributeAPSFCFailure.setDefaultValue(True)
diagnosticsClusterServerAttributeAPSFCFailure.setDescription("APSFCFailure - check the box to enable")
diagnosticsClusterServerAttributeAPSFCFailure.setVisible(False)

global diagnosticsClusterServerAttributeAPSUnauthorizedKey
diagnosticsClusterServerAttributeAPSUnauthorizedKey = drvZigbeeComponent.createBooleanSymbol("DC_APSUNAUTHORIZEDKEY", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeAPSUnauthorizedKey.setLabel("0x0114 APSUnauthorizedKey")
diagnosticsClusterServerAttributeAPSUnauthorizedKey.setDefaultValue(True)
diagnosticsClusterServerAttributeAPSUnauthorizedKey.setDescription("APSUnauthorizedKey - check the box to enable")
diagnosticsClusterServerAttributeAPSUnauthorizedKey.setVisible(False)

global diagnosticsClusterServerAttributeNWKDecryptFailures
diagnosticsClusterServerAttributeNWKDecryptFailures = drvZigbeeComponent.createBooleanSymbol("DC_NWKDECRYPTFAILURES", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeNWKDecryptFailures.setLabel("0x0115 NWKDecryptFailures")
diagnosticsClusterServerAttributeNWKDecryptFailures.setDefaultValue(True)
diagnosticsClusterServerAttributeNWKDecryptFailures.setDescription("NWKDecryptFailures - check the box to enable")
diagnosticsClusterServerAttributeNWKDecryptFailures.setVisible(False)

global diagnosticsClusterServerAttributeAPSDecryptFailures
diagnosticsClusterServerAttributeAPSDecryptFailures = drvZigbeeComponent.createBooleanSymbol("DC_APSDECRYPTFAILURES", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeAPSDecryptFailures.setLabel("0x0116 APSDecryptFailures")
diagnosticsClusterServerAttributeAPSDecryptFailures.setDefaultValue(True)
diagnosticsClusterServerAttributeAPSDecryptFailures.setDescription("APSDecryptFailures - check the box to enable")
diagnosticsClusterServerAttributeAPSDecryptFailures.setVisible(False)

global diagnosticsClusterServerAttributePacketBufferAllocateFailures
diagnosticsClusterServerAttributePacketBufferAllocateFailures = drvZigbeeComponent.createBooleanSymbol("DC_PACKETBUFFERALLOCATEFAILURES", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributePacketBufferAllocateFailures.setLabel("0x0117 PacketBufferAllocateFailures")
diagnosticsClusterServerAttributePacketBufferAllocateFailures.setDefaultValue(True)
diagnosticsClusterServerAttributePacketBufferAllocateFailures.setDescription("PacketBufferAllocateFailures - check the box to enable")
diagnosticsClusterServerAttributePacketBufferAllocateFailures.setVisible(False)

global diagnosticsClusterServerAttributeRelayedUcast
diagnosticsClusterServerAttributeRelayedUcast = drvZigbeeComponent.createBooleanSymbol("DC_RELAYEDUCAST", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeRelayedUcast.setLabel("0x0118 RelayedUcast")
diagnosticsClusterServerAttributeRelayedUcast.setDefaultValue(True)
diagnosticsClusterServerAttributeRelayedUcast.setDescription("RelayedUcast - check the box to enable")
diagnosticsClusterServerAttributeRelayedUcast.setVisible(False)

global diagnosticsClusterServerAttributePhyToMACQueueLimitReached
diagnosticsClusterServerAttributePhyToMACQueueLimitReached = drvZigbeeComponent.createBooleanSymbol("DC_PHYTOMACQUEUELIMITREACHED", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributePhyToMACQueueLimitReached.setLabel("0x0119 PhyToMACQueueLimitReached")
diagnosticsClusterServerAttributePhyToMACQueueLimitReached.setDefaultValue(True)
diagnosticsClusterServerAttributePhyToMACQueueLimitReached.setDescription("PhyToMACQueueLimitReached - check the box to enable")
diagnosticsClusterServerAttributePhyToMACQueueLimitReached.setVisible(False)

global diagnosticsClusterServerAttributePacketValidateDropCount
diagnosticsClusterServerAttributePacketValidateDropCount = drvZigbeeComponent.createBooleanSymbol("DC_PACKETVALIDATEDROPCOUNT", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributePacketValidateDropCount.setLabel("0x011A PacketValidateDropCount")
diagnosticsClusterServerAttributePacketValidateDropCount.setDefaultValue(True)
diagnosticsClusterServerAttributePacketValidateDropCount.setDescription("PacketValidateDropCount - check the box to enable")
diagnosticsClusterServerAttributePacketValidateDropCount.setVisible(False)

global diagnosticsClusterServerAttributeAverageMACRetryPerAPSMessageSent
diagnosticsClusterServerAttributeAverageMACRetryPerAPSMessageSent = drvZigbeeComponent.createBooleanSymbol("DC_AVGMACRETRYPERAPSMESSAGESENT", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeAverageMACRetryPerAPSMessageSent.setLabel("0x011B AverageMACRetryPerAPSMessageSent")
diagnosticsClusterServerAttributeAverageMACRetryPerAPSMessageSent.setDefaultValue(True)
diagnosticsClusterServerAttributeAverageMACRetryPerAPSMessageSent.setDescription("AverageMACRetryPerAPSMessageSent - check the box to enable")

global diagnosticsClusterServerAttributeLastMessageLQI
diagnosticsClusterServerAttributeLastMessageLQI = drvZigbeeComponent.createBooleanSymbol("DC_LASTMESSAGELQI", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeLastMessageLQI.setLabel("0x011C LastMessageLQI")
diagnosticsClusterServerAttributeLastMessageLQI.setDefaultValue(True)
diagnosticsClusterServerAttributeLastMessageLQI.setDescription("LastMessageLQI - check the box to enable")

global diagnosticsClusterServerAttributeLastMessageRSSI
diagnosticsClusterServerAttributeLastMessageRSSI = drvZigbeeComponent.createBooleanSymbol("DC_LASTMESSAGERSSI", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeLastMessageRSSI.setLabel("0x011D LastMessageRSSI")
diagnosticsClusterServerAttributeLastMessageRSSI.setDefaultValue(True)
diagnosticsClusterServerAttributeLastMessageRSSI.setDescription("LastMessageRSSI - check the box to enable")

global diagnosticsClusterServerAttributeClusterRevision
diagnosticsClusterServerAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("DC_CLUSTERREVISION", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
diagnosticsClusterServerAttributeClusterRevision.setDefaultValue(True)
diagnosticsClusterServerAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
diagnosticsClusterServerAttributeClusterRevision.setReadOnly(True)

global diagnosticsClusterServerAttributeCount
diagnosticsClusterServerAttributeCount = drvZigbeeComponent.createIntegerSymbol("DC_SERVERATTRIBUTECOUNT", diagnosticsClusterServerAttributes)
diagnosticsClusterServerAttributeCount.setLabel("Attributes Count")
diagnosticsClusterServerAttributeCount.setDefaultValue(diagnosticsClusterServerAttributeCountUpdate(0,0))
diagnosticsClusterServerAttributeCount.setVisible(True)
diagnosticsClusterServerAttributeCount.setDescription("Attributes Count")
diagnosticsClusterServerAttributeCount.setReadOnly(True)
diagnosticsClusterServerAttributeCount.setDependencies(diagnosticsClusterServerAttributeCountUpdate,["DC_NUMBEROFRESETS","DC_PERSISTENTMEMORYWRITES","DC_MACRXBCAST","DC_MACTXBCAST",
                                                                                         "DC_MACRXUCAST","DC_MACTXUCAST","DC_MACTXUCASTRETRY","DC_MACTXUCASTFAIL",
                                                                                         "DC_APSTXBCAST","DC_APSRXUCAST","DC_APSTXUCAST","DC_APSTXUCASTSUCCESS",
                                                                                         "DC_APSTXUCASTRETRY","DC_APSTXUCASTFAIL","DC_ROUTEDISCINITIATED",
                                                                                         "DC_NEIGHBORADDED","DC_NEIGHBORREMOVED","DC_NEIGHBORSTALE","DC_JOININDICATION",
                                                                                         "DC_CHILDMOVED","DC_NWKCFAILURE","DC_APSCFAILURE","DC_APSUNAUTHORIZEDKEY",
                                                                                         "DC_NWKDECRYPTFAILURES","DC_APSDECRYPTFAILURES","DC_PACKETBUFFERALLOCATEFAILURES",   
                                                                                         "DC_RELAYEDUCAST","DC_PHYTOMACQUEUELIMITREACHED","DC_PACKETVALIDATEDROPCOUNT","DC_AVGMACRETRYPERAPSMESSAGESENT",
                                                                                         "DC_LASTMESSAGELQI","DC_LASTMESSAGERSSI","DC_CLUSTERREVISION",                                                                                                                                                                                
                                                                                        ])

#################               Server Commands                                 ###############

# Commands received
# The server receives no commands

# Commands generated
# The server generates no cluster specific commands.

#################               Client Attributes                                 ###############
global diagnosticsClusterClientAttributeClusterRevision
diagnosticsClusterClientAttributeClusterRevision = drvZigbeeComponent.createBooleanSymbol("DCC_CLUSTERREVISION", diagnosticsClusterClientAttributes)
diagnosticsClusterClientAttributeClusterRevision.setLabel("0xFFFD ClusterRevision")
diagnosticsClusterClientAttributeClusterRevision.setDefaultValue(True)
diagnosticsClusterClientAttributeClusterRevision.setDescription("cluster revision - check the box to enable")
diagnosticsClusterClientAttributeClusterRevision.setReadOnly(True)

global diagnosticsClusterClientAttributeCount
diagnosticsClusterClientAttributeCount = drvZigbeeComponent.createIntegerSymbol("DC_CLIENTATTRIBUTECOUNT", diagnosticsClusterClientAttributes)
diagnosticsClusterClientAttributeCount.setLabel("Attributes Count")
diagnosticsClusterClientAttributeCount.setDefaultValue(diagnosticsClusterClientAttributeCountUpdate(0,0))
diagnosticsClusterClientAttributeCount.setVisible(True)
diagnosticsClusterClientAttributeCount.setDescription("Attributes Count")
diagnosticsClusterClientAttributeCount.setReadOnly(True)
diagnosticsClusterClientAttributeCount.setDependencies(diagnosticsClusterClientAttributeCountUpdate,["DCC_CLUSTERREVISION"])

#################               Client Commands                                 ###############

# Commands received
# The Client receives no commands

# Commands generated
# The Client generates no cluster specific commands.
############################################################################################################
# Default Values Settings based on device type
diagnosticsClusterHandling()

############################################################################################################
##################################### FTL Files Definitions ################################################
############################################################################################################

# DIAGONSTICS CLUSTER Common header
diagnosticsClusterConf = drvZigbeeComponent.createFileSymbol("ZIGBEE_DIAGONSTICS_CLUSTER_CONF", None)
diagnosticsClusterConf.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/diagnostics/zclDiagnosticsCluster.h.ftl")
diagnosticsClusterConf.setOutputName("zclDiagnosticsCluster.h")
diagnosticsClusterConf.setDestPath("/zigbee/lib/inc/zcl/include")
diagnosticsClusterConf.setProjectPath("config/" + configName + "/zigbee/lib/inc/zcl/include")
diagnosticsClusterConf.setType("HEADER")
diagnosticsClusterConf.setOverwrite(True)
diagnosticsClusterConf.setMarkup(True)

# DIAGONSTICS CLUSTER - MultiSensor
diagnosticsClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_DIAGONSTICS_CLUSTER_CONF_SRC_MS", None)
diagnosticsClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/diagnostics/msDiagnosticsCluster.c.ftl")
diagnosticsClusterConfSrc.setOutputName("msDiagnosticsCluster.c")
diagnosticsClusterConfSrc.setDestPath("/zigbee/z3device/multiSensor")
diagnosticsClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/multiSensor/")
diagnosticsClusterConfSrc.setType("SOURCE")
diagnosticsClusterConfSrc.setOverwrite(True)
diagnosticsClusterConfSrc.setMarkup(True)
diagnosticsClusterConfSrc.setEnabled(checkDevTypeMultiSensor)

# DIAGONSTICS CLUSTER - Custom
diagnosticsClusterConfSrc = drvZigbeeComponent.createFileSymbol("ZIGBEE_DIAGONSTICS_CLUSTER_CONF_SRC_CUSTOM", None)
diagnosticsClusterConfSrc.setSourcePath("/driver/zigbee" + suffix + "/templates/cluster/diagnostics/customDiagnosticsCluster.c.ftl")
diagnosticsClusterConfSrc.setOutputName("customDiagnosticsCluster.c")
diagnosticsClusterConfSrc.setDestPath("/zigbee/z3device/custom")
diagnosticsClusterConfSrc.setProjectPath("config/" + configName + "/zigbee/z3device/custom/")
diagnosticsClusterConfSrc.setType("SOURCE")
diagnosticsClusterConfSrc.setOverwrite(True)
diagnosticsClusterConfSrc.setMarkup(True)
diagnosticsClusterConfSrc.setEnabled(checkDevTypeCustom and diagnosticsCluster.getValue())
diagnosticsClusterConfSrc.setDependencies(customDiagnosticsClusterEnableCheck,["DIAGONSTICS_CLUSTER_ENABLE"])
############################################################################################################
