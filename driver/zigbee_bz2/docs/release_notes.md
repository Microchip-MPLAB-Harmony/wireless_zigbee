---
parent: Release notes
title: Zigbee Driver Library
has_children: false
has_toc: false
nav_order: 190

family: PIC32CX-BZ3
function: Zigbee
---

# Zigbee Driver Library Release notes

## Zigbee Release V6.0.0_BZ3_EAP1

### New Features
+ Zigbee Application Device Support
  + Lights ( Extended Color, Dimmable)
  + Combined Interface ( Gateway)
  + Color Scene Controller (without sleep)
+ Zigbee on Harmony 3 Platform.
+ Zigbee Configurator
  + Option to select/ deselect feature set required for Zigbee Application device types by the user.

 

## Family: PIC32CX-BZ
## Function: Zigbee
---
# Zigbee Driver Library Release notes

## Zigbee Release v5.0.0

### Feature sets and Enhancements

+ IEEE 802.15.4 MAC/PHY Certified
+ Zigbee Compliant Platform Certfied - R22
+ BDB 3.0.1 specification Implementation 
+ ZCL 8 Specification Implementation
+ Zigbee End Product Certified (Extended Color Light) - BDB 3.0.1/ZCL 8
+ Zigbee Green Power Proxy Basic Certified
+ BDB Commissioig Procedue changes in application w.r.t BDB 3.0.1 - removal of top level commissioning
+ OTAU Cluster support with Block mode and Page mode with Auto recovery
+ OTAU Server is compatible with Micorchip OTAU utility tool
+ OTAU client parameters made configurable in Harmony
+ Zigbee Green Power Sink Cerification ready
+ Zigbee Custom Device Addition
+ Power Save implementation on Zigbee End device - Bug fixes and Improvements
+ RGB Led Light integration through System Services Harmony Component
+ Stability tested in a 10 node netwrok for more than 24 hours
+ P2P Range tested upto 100 meters
+ Zigbee Harmony component folder structure optimized to reduce the path size & better readability
+ Device / Stack power handling and backoff implemenation.User options to set FCC/ETSI/Custom antenna gain.
+ Zigbee Application Device Support - 
  + Lights ( Extended Color, Dimmable, Temperature Color , OnOff , Color)
  + IAS ( Intruder Alarm System)
  + Thermostat
  + Combined Interface ( Gateway)
  + Color Scene Controller
  + Muti Sensors ( Occupancy , Light, Humidity , Temperature)
  + Green Power Support ( Proxy and Sink)

### Known Issues
+ Zigbee Mesh is not run on a larger node bed / test to verify/fine tune  Netowrk traffic / Mising Acks / Retries.
+ CCA Mode-3 not full verified when Arbiter Mode set as part of the wireless subsystem. However verified with Static and IP mode.

*************************************
## Zigbee Release ZB_V5.0.0_3.1E

### Feature sets and Enhancements
+ Zigbee Custom Device Addition
+ Device / Stack power handling and backoff implemenation.User options to set FCC/ETSI/Custom antenna gain.
+ Power save implementation on end devices.
+ Enhancements / Addition of command sets to the Serial / Console application handling , which includes ZCL attributes and stack level features.
+ Clusters deafault behavior updates w.r.t server and client as part of MHC. 
+ PDS Update w.r.t new CSP and file size limit increased to 2K.
+ Couple of general enhancements as part of MHC configration for the stack and application and log error fix.
+ Multiple read attribute for a given cluster support in the stack.
+ Response callback addition in zigbee application handler file for all ZDO commands.
+ EA3 Feeback, bugs and enhancements.

### Known Issues
+ Zigbee Mesh is not run on a larger node bed / test to verify/fine tune  Netowrk traffic / Mising Acks / Retries.
+ CCA Mode-3 not full verified when Arbiter Mode set as part of the wireless subsystem. However verified with Static and IP mode.

**********************************

## Zigbee Release ZB_V5.0.0_2.1E
### Enhancements
+ Handling of Information Base for MACID.
+ Specific requirements to address Dual Stack needs ( Combo) for detaching the CS default values set outside of the staack
+ Implemenation of new programming model to push all the ZCL and BDB events to the user level.

### Known Issues
+ Zigbee Mesh is not run on a larger node bed / test to verify/fine tune  Netowrk traffic / Mising Acks / Retries.

**********************************

## Zigbee Release ZB_V5.0.0_1.2E
### Bug Fixes
+ Handling of commands from thirpart gateways w.r.t Interoperability.

### Known Issues
+ Zigbee Mesh is not run on a larger node bed / test to verify/fine tune  Netowrk traffic / Mising Acks / Retries.

**********************************

## Zigbee Release ZB_V5.0.0_1.1E

### New Features
+ Zigbee Application Device Support - 
  + Lights ( Extended Color, Dimmable, Temperature Color , OnOff , Color)
  + IAS ( Intruder Alarm System)
  + Thermostat
  + Combined Interface ( Gateway)
  + Color Scene Controller
  + Muti Sensors ( Occupancy , Light, Humidity , Temperature)
  + Green Power Support ( Proxy and Sink)
+ Zigbee on Harmony 3 Platform.
+ Zigbee Configurator
  + Option to select/ deselect feature set required for Zigbee Application device types by the user.

### Known Issues
+ Zigbee Mesh is not run on a larger node bed / test to verify/fine tune  Netowrk traffic / Mising Acks / Retries.
 

### Development Tools
+ [MPLAB X v6.00](https://www.microchip.com/mplab/mplab-x-ide)
+ [MPLAB® XC32 C/C++ Compiler v4.10](https://www.microchip.com/mplab/compilers)
+ MPLAB® X IDE plug-ins: MPLAB® Code Configurator (MCC) v5.1.9 and above
 

