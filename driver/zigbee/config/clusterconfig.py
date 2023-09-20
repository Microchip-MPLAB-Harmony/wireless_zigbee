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

####################################################################################################
##########################               Cluster CONFIGURATION                 #####################
####################################################################################################


####################################################################################################
###########################  BASIC CLUSTER CONFIGURATION   #########################################
####################################################################################################
# Basic Cluster Configuration
execfile(Module.getPath() +"/driver/zigbee/config/cluster/basiclusterconfig.py")

####################################################################################################
###########################  IDENTIFY CLUSTER CONFIGURATION   ######################################
####################################################################################################
# Identify Cluster Configuration
execfile(Module.getPath() +"/driver/zigbee/config/cluster/identifyclusterconfig.py")

####################################################################################################
###########################  GROUPS CLUSTER CONFIGURATION   ########################################
####################################################################################################
# Groups Cluster Configuration
execfile(Module.getPath() +"/driver/zigbee/config/cluster/groupsclusterconfig.py")


####################################################################################################
###########################  SCENES CLUSTER CONFIGURATION   ########################################
####################################################################################################
# Scenes Cluster Configuration
execfile(Module.getPath() +"/driver/zigbee/config/cluster/scenesclusterconfig.py")

####################################################################################################
###########################  ONOFF CLUSTER CONFIGURATION   #########################################
####################################################################################################
# OnOff Cluster Configuration
execfile(Module.getPath() +"/driver/zigbee/config/cluster/onoffclusterconfig.py")

####################################################################################################
###########################  LEVELCONTROL CLUSTER CONFIGURATION   ##################################
####################################################################################################
# Level Control Cluster Configuration
execfile(Module.getPath() +"/driver/zigbee/config/cluster/levelcontrolclusterconfig.py")

####################################################################################################
###########################  COLORCONTROL CLUSTER CONFIGURATION   ##################################
####################################################################################################
# Color Control Cluster Configuration
execfile(Module.getPath() +"/driver/zigbee/config/cluster/colorcontrolclusterconfig.py")

####################################################################################################
###########################  ALARMS CLUSTER CONFIGURATION   ########################################
####################################################################################################
# Alarms Control Cluster Configuration
execfile(Module.getPath() +"/driver/zigbee/config/cluster/alarmsclusterconfig.py")

####################################################################################################
###########################  TIME CLUSTER CONFIGURATION   ##########################################
####################################################################################################
# Time Cluster Configuration
execfile(Module.getPath() +"/driver/zigbee/config/cluster/timeclusterconfig.py")

####################################################################################################
###########################  THERMOSTAT CLUSTER CONFIGURATION   ####################################
####################################################################################################
# Thermostat Cluster Configuration
execfile(Module.getPath() +"/driver/zigbee/config/cluster/thermostatclusterconfig.py")

####################################################################################################
###########################  FANCONTROL CLUSTER CONFIGURATION   ####################################
####################################################################################################
# FanControl Cluster Configuration
execfile(Module.getPath() +"/driver/zigbee/config/cluster/fancontrolclusterconfig.py")

####################################################################################################
###########################  OCCUPANCY SENSING CLUSTER CONFIGURATION   #############################
####################################################################################################
# OccupancySensing Cluster Configuration
execfile(Module.getPath() +"/driver/zigbee/config/cluster/occupancysensingclusterconfig.py")

####################################################################################################
###########################  ILLUMINANCE MEASUREMENT CLUSTER CONFIGURATION   #######################
####################################################################################################
# Illuminance Measurement Cluster Configuration
execfile(Module.getPath() +"/driver/zigbee/config/cluster/illuminancemeasurementclusterconfig.py")

####################################################################################################
###########################  TEMPERATURE MEASUREMENT CLUSTER CONFIGURATION   #######################
####################################################################################################
# Temperature Measurement Cluster Configuration
execfile(Module.getPath() +"/driver/zigbee/config/cluster/temperaturemeasurementclusterconfig.py")

####################################################################################################
###########################  WATER CONTENT MEASUREMENT CLUSTER CONFIGURATION   #####################
####################################################################################################
# Water Content Measurement Cluster Configuration
execfile(Module.getPath() +"/driver/zigbee/config/cluster/watercontentclusterconfig.py")

####################################################################################################
###########################  THERMOSTAT UI CONFIGURATION CLUSTER CONFIGURATION   ###################
####################################################################################################
# Thermostat UI Configuration Cluster Configuration
execfile(Module.getPath() +"/driver/zigbee/config/cluster/thermostatuiclusterconfig.py")

####################################################################################################
###########################  IAS ZONE CLUSTER CONFIGURATION   ######################################
####################################################################################################
# IAS ZONE Cluster Configuration
execfile(Module.getPath() +"/driver/zigbee/config/cluster/iaszoneclusterconfig.py")

####################################################################################################
###########################  IAS ACE CLUSTER CONFIGURATION   #######################################
####################################################################################################
# IAS ACE Cluster Configuration
execfile(Module.getPath() +"/driver/zigbee/config/cluster/iasaceclusterconfig.py")

####################################################################################################
###########################  DIAGNOSTICS CLUSTER CONFIGURATION   #######################
####################################################################################################
# Diagnostics Cluster Configuration
execfile(Module.getPath() +"/driver/zigbee/config/cluster/diagnosticsclusterconfig.py")

####################################################################################################
###########################  CONSOLE FTL DEFINTIONS RELATED TO CLUSTERS ############################
####################################################################################################
# Console commands FTL files definitions for all device types - All Cluster Specific
execfile(Module.getPath() +"/driver/zigbee/config/cluster/consoleconfig.py")

####################################################################################################
###########################  CUSTOM CLUSTERS  ######################################################
####################################################################################################
# Custom cluster FTL files and addition to souce, header code for device type source files
execfile(Module.getPath() +"/driver/zigbee/config/cluster/customclusterconfig.py")

####################################################################################################
####################################################################################################
