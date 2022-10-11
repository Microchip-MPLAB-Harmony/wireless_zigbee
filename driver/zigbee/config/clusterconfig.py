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
####################################################################################################

