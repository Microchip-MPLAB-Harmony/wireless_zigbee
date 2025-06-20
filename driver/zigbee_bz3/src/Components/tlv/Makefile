#------------------------------------------------------------------------------- 
#  \file  Makefile
#
#  \brief Make file for TLV.
#
#  \author
#    Microchip Corporation: http://ww.microchip.com \n
#    Support email: support@microchip.com
#
#  Copyright (c) 2009, Microchip Corporation. All rights reserved.
#  Licensed under Microchip's Limited License Agreement.
#
#------------------------------------------------------------------------------- 

#***************************** Macro definitions *******************************
COMPONENTS_PATH = ..
include $(COMPONENTS_PATH)/Makerules

#***************************** Compiler's flags ********************************

#***************************** Define's flags **********************************

lib_name = lib$(TLV_LIB).a

# To remove IAR compiler error: wrong if (..) processing.
ifeq ($(COMPILER_AND_MICRO_TYPE), IAR_ARM)
  TMP_CFLAGS:=$(filter-out -O%,$(CFLAGS))
  CFLAGS = $(TMP_CFLAGS) -On
endif

#***************************** Include directories *****************************
ifeq ($(USE_KF_MAC), TRUE)
  CFLAGS += $(addprefix -I,$(KF_INCS))
endif
# DEFINES = \
    # -DBDB_NWKFORMATION_SUPPORT \
    # -DBDB_FINDINGANDBINDING_SUPPORT
		  
		  
CFLAGS +=                        \
  -I$(BASE_PATH)                \
  -I$(BSP_PATH)/include          \
  -I$(SE_PATH)/include           \
  -I$(CS_PATH)/include           \
  -I$(CS_PATH)/include/private   \
  -I$(CRYPTO_PATH)               \
  -I$(COMPONENTS_PATH)/PDS/include\
  -I$(PDS_PATH)/lib              \
  -I$(MAC_HWD_PATH)/             \
  -I$(MAC_HWD_PATH)/RF231_RF212/PHY/include  \
  -I$(MAC_HWD_PATH)/include      \
  -I$(NWK_PATH)/include          \
  -I$(NWK_PATH)/include/private  \
  -I$(APS_PATH)/include          \
  -I$(APS_PATH)/include/private  \
  -I$(TC_PATH)/include           \
  -I$(ZDO_PATH)/include          \
  -I$(ZDO_PATH)/include/private  \
  -I$(ZGP_PATH)/include          \
  -I$(BDB_PATH)/include          \
  -I$(TLV_PATH)/include          \
  -I$(ZCL_PATH)/include          \
  -I$(ZCL_PATH)/include          \
  -I$(ZCL_CLUSTER_PATH)/include  \
  -I$(ZLL_PLATFORM_PATH)         \
  -I$(ZLL_PATH)/N_AddressManager/include     \
  -I$(ZLL_PATH)/N_Beacon/include     \
  -I$(ZLL_PATH)/N_Binding/include     \
  -I$(ZLL_PATH)/N_Cmi/include     \
  -I$(ZLL_PATH)/N_Connection/include     \
  -I$(ZLL_PATH)/N_DeviceInfo/include     \
  -I$(ZLL_PATH)/N_EndDeviceRobustness/include     \
  -I$(ZLL_PATH)/N_InterPan/include     \
  -I$(ZLL_PATH)/N_LinkInitiator/include     \
  -I$(ZLL_PATH)/N_LinkTarget/include     \
  -I$(ZLL_PATH)/N_PacketDistributor/include     \
  -I$(ZLL_PATH)/N_Radio/include     \
  -I$(ZLL_PATH)/N_ReconnectHandler/include     \
  -I$(ZLL_PATH)/N_Security/include     \
  -I$(ZLL_PATH)/N_Zdp/include     \
  -I$(ZLL_PATH)/N_Zcl_Framework/include   \
  -I$(ZLL_INFRA_PATH)/N_Address/include     \
  -I$(ZLL_INFRA_PATH)/N_Beacon/include     \
  -I$(ZLL_INFRA_PATH)/N_ErrH/include     \
  -I$(ZLL_INFRA_PATH)/N_Fsm/include     \
  -I$(ZLL_INFRA_PATH)/N_Log/include     \
  -I$(ZLL_INFRA_PATH)/N_Memory/include     \
  -I$(ZLL_INFRA_PATH)/N_Task/include     \
  -I$(ZLL_INFRA_PATH)/N_Init/include     \
  -I$(ZLL_INFRA_PATH)/N_Timer/include     \
  -I$(ZLL_INFRA_PATH)/N_Types/include     \
  -I$(ZLL_INFRA_PATH)/N_Util/include     \
  -I$(HAL_PATH)/include          \
  -I$(HAL_HWD_COMMON_PATH)/include      \
  -I$(MAC_PHY_PATH)/include      \
  -I$(MAC_ENV_PATH)/include      \
  -I$(HAL_PATH)/../include       \
  -I$(SSP_PATH)/include/private  \
  -I$(SSP_PATH)/include          \
  -I$(SSP_PATH)/../SoftAes       \
  -I$(OSAL_PATH)                   \
  -I$(OSAL_PATH)/osal              \
  -I$(FREE_RTOS_PATH)/include      \
  -I$(FREE_RTOS_PATH)/portable/GCC/ARM_CM4F \
  -I$(RTOS_CONFIG_PATH)            \
  -I$(PARTPACK_PATCH)/include      \
  -I$(PARTPACK_PATCH)/include/soc  \
  -I$(CMIS_PATH)                   \
  -I$(UTILS_PATH)                  \
  -I$(UTILS_PATH)/preprocessor

#***************************** Object files ************************************
objects_tlv =                              \
  $(TLV_PATH)/objs/tlv.o            \
  
  
#***************************** Libraries ***************************************
lib_tlv = $(TLV_PATH)/lib/$(lib_name)

#***************************** Targets *****************************************
all: component_label $(lib_tlv) size_tlv
component_label:
	@echo 
	@echo ----------------------------------------------------
	@echo TLV library creation.
	@echo ----------------------------------------------------
	$(Q)mkdir -p $(TLV_PATH)/objs/
	$(Q)mkdir -p $(TLV_PATH)/lib/
$(objects_tlv): 
	$(CC_MSG)
	$(Q)$(CC) $(CFLAGS) $(CFLAGS_HWD) $^ -o $@
$(TLV_PATH)/objs/tlv.o:                          $(TLV_PATH)/src/tlv.c


$(lib_tlv): $(objects_tlv)
	$(AR_MSG)
	$(Q)$(AR) $(AR_KEYS) $(lib_tlv) $(objects_tlv)

size_tlv: $(lib_tlv)
	$(SIZE_MSG)
	$(Q)$(SHOW_SIZE) -td $(lib_tlv)

clean:
	@echo 
	@echo ----------------------------------------------------
	@echo TLV component cleaning is started...
	$(Q)rm -f $(objects_tlv) $(lib_tlv) $(wildcard $(TLV_PATH)/list/*.*)
	@echo TLV component cleaning is done!
	@echo ----------------------------------------------------
