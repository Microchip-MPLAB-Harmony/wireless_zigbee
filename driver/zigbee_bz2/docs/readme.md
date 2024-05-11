
Family: PIC32CX-BZ
Function: Zigbee
---

# Zigbee Driver Library

Zigbee Stack is a full-featured, next generation embedded software stack from Mirochip.
The stack provides a software development platform for reliable and scalable wireless applications running on Microchip microcontrollers and radio transceivers.
 
Zigbee Stack is designed to support a broad ecosystem of user-designed applications addressing diverse requirements and enabling a full spectrum of software customization.
Zigbee Stack is fully compliant with ZigBee PRO and ZigBee standards for wireless sensing and control. 

It provides an augmented set of APIs which, while maintaining 100% compliance with the standard,
offer extended functionality designed with developer's convenience and ease-of-use in mind.

Zigbee Stack's target audience is system designers, embedded programmers and hardware engineers evaluating, prototyping, and deploying wireless solutions and 
products built on on the Microchip hardware platform. 
   
Zigbee Stack is delivered as a software development kit, which includes
   
   - documentation 
   - standard set of libraries comprising multiple components of the stack 
   - sample user applications in source code 
   - a limited set of peripheral drivers for the supported platforms

Zigbee Stack internal architecture follows IEEE 802.15.4 Standard, ZigBee-defined separation of the networking stack into logical layers. 
Besides the core stack containing protocol implementation, zigbee stack contains additional layers implementing shared services 
like task manager, security and power manager ,etc.,.

The topmost of the core stack layers, APS, provides the highest level of networking-related APIs visible to the application.
ZDO provides a set of fully compliant ZigBee Device Object APIs which enable main network management functionality (start, reset, formation, join) and
power management(sleep, wakeup). ZDO also defines ZigBee Device Profile types,device and service discovery commandsimplemented by the stack, and 
provides APIs for unicast, multicast, and broadcast data transmission and acknowledgment.

Refer to the below link for the detail Zigbee Driver Library usage:

* [Zigbee Program Model](usage.md#Zigbee-Program-Model)

* [Initializing the library](usage.md#Zigbee-Library-Usage)

* [Using the library](usage.md#Zigbee-Library-Usage)

* [Library interface](html/index.html)

* [Custom Device](custom.md#Custom-device-type)
