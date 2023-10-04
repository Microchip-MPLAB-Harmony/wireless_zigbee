
![Microchip logo](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_logo.png)
![Harmony logo small](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_mplab_harmony_logo_small.png)

# Microchip MPLAB® Harmony 3 Release Notes

## Zigbee Release v5.1.1

### New Features

+ All features as v5.1.0
+ Latest XC32 compiler version support XC32 v4.35
+ Linux support

### Changes
  + MCC/Middleware changes :
    + Renamed a folder w.r.t. case sensitive ("stack_Interface" to "stack_interface")

### Development Tools
+ [MPLAB X v6.15](https://www.microchip.com/mplab/mplab-x-ide)
+ [MPLAB® XC32 C/C++ Compiler v4.35](https://www.microchip.com/mplab/compilers)
+ MPLAB® X IDE plug-ins: MPLAB® Code Configurator (MCC) v5.3.7 and above

---

# Zigbee Driver Library Release notes

## Zigbee Release v5.1.0

### New Features

+ Deep Sleep support for Zigbee End devices (with retention RAM)
+ Custom Cluster support
+ Custom Device support with Custom Cluster
+ Device / Stack Tx power handling and backoff implementation.User options to set FCC/ETSI/IC/China/Korea/Taiwan regions with Custom antenna gain.
+ Standby Sleep improvements with Combo(BLE) devices

### Bug Fixes

+ Zigbee Stack Configuration options are not restored properly in MCC Reload
+ Extra Delay in ZED polling intervals during standby sleep in combo application with BLE

### Changes
  + Stack changes:
	+ Handling radiated power input and set the tx power accordingly based on the antenna gain selected (China/Taiwan/Korea/FCC/ETSI/IC)
	+ Created APIs to store and restore critical network paramters to use them before going/after wakingup to/from deep sleep
	+ Standby Sleep improvement to better align with other technologies like BLE.
  + MCC/Middleware changes :
	+ Provided the framework to add the custom cluster on a standard device or custom device with configurable attributes and Commands

### Known Issues/Limitations
  + Max 3 OTAU clients can only be upgraded in parallel by single OTAU Server
  
### Development Tools
+ [MPLAB X v6.15](https://www.microchip.com/mplab/mplab-x-ide)
+ [MPLAB® XC32 C/C++ Compiler v4.21](https://www.microchip.com/mplab/compilers)
+ MPLAB® X IDE plug-ins: MPLAB® Code Configurator (MCC) v5.3.7 and above

---

## Zigbee Release v5.0.0

### Feature sets and Enhancements

+ IEEE 802.15.4 MAC/PHY Certified
+ Zigbee Compliant Platform Certified - R22
+ BDB 3.0.1 specification Implementation 
+ ZCL 8 Specification Implementation
+ Zigbee End Product Certified (Extended Color Light) - BDB 3.0.1/ZCL 8
+ Zigbee Green Power Proxy Basic Certified
+ BDB Commissioning Procedure changes in application w.r.t BDB 3.0.1 - removal of top level commissioning
+ OTAU Server/Client Cluster support with Block mode and Page mode with Auto recovery
+ OTAU Server is compatible with Micorchip OTAU utility tool
+ Zigbee Green Power Sink Cerification ready
+ Zigbee Custom Device Addition
+ Power Save implementation on Zigbee End device - Bug fixes and Improvements
+ RGB Led Light integration through System Services Harmony Component
+ Stability tested in a 10 node network for more than 24 hours
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


### Development Tools
+ [MPLAB X v6.00](https://www.microchip.com/mplab/mplab-x-ide)
+ [MPLAB® XC32 C/C++ Compiler v4.10](https://www.microchip.com/mplab/compilers)
+ MPLAB® X IDE plug-ins: MPLAB® Code Configurator (MCC) v5.1.9 and above
