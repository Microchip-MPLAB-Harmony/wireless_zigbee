
## Family: PIC32CX-BZ
## Function: Zigbee
---
# Zigbee Driver Library Release notes

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
+ Device / Stack power handling and backoff implemenation.User options to set FCC/ETSI/Custom antenna gain.
+ Zigbee Application Device Support - 
  + Lights ( Extended Color, Dimmable, Temperature Color , OnOff , Color)
  + IAS ( Intruder Alarm System)
  + Thermostat
  + Combined Interface ( Gateway)
  + Color Scene Controller
  + Muti Sensors ( Occupancy , Light, Humidity , Temperature)
  + Green Power Support ( Proxy and Sink)

### Known Issues/Limitations
+ CCA Mode-3 not fully verified when Arbiter Mode set as part of the wireless subsystem. However verified with Static and IP mode.


### Development Tools
+ [MPLAB X v6.00](https://www.microchip.com/mplab/mplab-x-ide)
+ [MPLAB® XC32 C/C++ Compiler v4.10](https://www.microchip.com/mplab/compilers)
+ MPLAB® X IDE plug-ins: MPLAB® Code Configurator (MCC) v5.1.9 and above
