#------------------------------------------------------------------------------- 
#  \file  Makefile
#
#  \brief Make file for Security Service Provider.
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
COMPONENTS_PATH = ../..
include $(COMPONENTS_PATH)/Makerules

#***************************** Compiler's flags ********************************

#***************************** Define's flags **********************************
CFLAGS += -D_SSP_USE_FLASH_FOR_CONST_DATA

lib_name = lib$(SSP_LIB).a

# To remove IAR compiler error: wrong if (..) processing.
ifeq ($(COMPILER_AND_MICRO_TYPE), IAR_ARM)
  TMP_CFLAGS:=$(filter-out -O%,$(CFLAGS))
  CFLAGS = $(TMP_CFLAGS) -On
endif

#***************************** Include directories *****************************
ifeq ($(USE_KF_MAC), TRUE)
  CFLAGS += $(addprefix -I,$(KF_INCS))
endif

CFLAGS +=                        \
  -I$(BASE_PATH)                \
  -I$(BSP_PATH)/include          \
  -I$(SE_PATH)/include           \
  -I$(CS_PATH)/include           \
  -I$(NWK_PATH)/include          \
  -I$(ZDO_PATH)/include          \
  -I$(CRYPTO_PATH)               \
  -I$(ZGP_PATH)                  \
  -I$(HAL_PATH)/include          \
  -I$(HAL_HWD_COMMON_PATH)/include      \
  -I$(MAC_PHY_PATH)/include      \
  -I$(HAL_PATH)/../include       \
  -I$(SSP_PATH)/include/private  \
  -I$(SSP_PATH)/include          \
  -I$(SSP_PATH)/../SoftAes       \
  -I$(OSAL_PATH)                   \
  -I$(OSAL_PATH)/osal              \
  -I$(FREE_RTOS_PATH)/portable/GCC/ARM_CM4F \
  -I$(FREE_RTOS_PATH)/include      \
  -I$(RTOS_CONFIG_PATH)            \
  -I$(PARTPACK_PATCH)/include      \
  -I$(PARTPACK_PATCH)/include/soc \
  -I$(CMIS_PATH)  

#***************************** Object files ************************************
objects_ssp =                              \
  $(SSP_PATH)/objs/sspManager.o            \
  $(SSP_PATH)/objs/sspMem.o                \
  $(SSP_PATH)/objs/sspAesHandler.o         \
  $(SSP_PATH)/objs/sspHashHandler.o        \
  $(SSP_PATH)/objs/sspCcmHandler.o         \
  $(SSP_PATH)/objs/sspSfpHandler.o         \
  $(SSP_PATH)/objs/sspSkkeHandler.o        \
  $(SSP_PATH)/objs/sspAuthenticHandler.o   \
  $(SSP_PATH)/objs/sspChallengeGenHandler.o\
  $(SSP_PATH)/objs/sspHash.o               \
  $(SSP_PATH)/objs/sspReset.o

#***************************** Libraries ***************************************
lib_ssp = $(SSP_PATH)/lib/$(lib_name)

#***************************** Targets *****************************************
all: component_label $(lib_ssp) size_ssp
component_label:
	@echo 
	@echo ----------------------------------------------------
	@echo Security Service Provider library creation.
	@echo ----------------------------------------------------
	$(Q)mkdir -p $(SSP_PATH)/objs/
	$(Q)mkdir -p $(SSP_PATH)/lib/
$(objects_ssp): 
	$(CC_MSG)
	$(Q)$(CC) $(CFLAGS) $(CFLAGS_HWD) $^ -o $@
$(SSP_PATH)/objs/sspManager.o:             $(SSP_PATH)/src/sspManager.c
$(SSP_PATH)/objs/sspMem.o:                 $(SSP_PATH)/src/sspMem.c
$(SSP_PATH)/objs/sspAesHandler.o:          $(SSP_PATH)/../SoftAes/sspAesHandler.c
$(SSP_PATH)/objs/sspHashHandler.o:         $(SSP_PATH)/src/sspHashHandler.c
$(SSP_PATH)/objs/sspCcmHandler.o:          $(SSP_PATH)/src/sspCcmHandler.c
$(SSP_PATH)/objs/sspSfpHandler.o:          $(SSP_PATH)/src/sspSfpHandler.c
$(SSP_PATH)/objs/sspSkkeHandler.o:         $(SSP_PATH)/src/sspSkkeHandler.c
$(SSP_PATH)/objs/sspAuthenticHandler.o:    $(SSP_PATH)/src/sspAuthenticHandler.c
$(SSP_PATH)/objs/sspChallengeGenHandler.o: $(SSP_PATH)/src/sspChallengeGenHandler.c
$(SSP_PATH)/objs/sspHash.o:                $(SSP_PATH)/src/sspHash.c
$(SSP_PATH)/objs/sspReset.o:               $(SSP_PATH)/src/sspReset.c

$(lib_ssp): $(objects_ssp)
	$(AR_MSG)
	$(Q)$(AR) $(AR_KEYS) $(lib_ssp) $(objects_ssp)

size_ssp: $(lib_ssp)
	$(SIZE_MSG)
	$(Q)$(SHOW_SIZE) -td $(lib_ssp)

clean:
	@echo 
	@echo ----------------------------------------------------
	@echo Security Service Provider component cleaning is started...
	$(Q)rm -f $(objects_ssp) $(lib_ssp) $(wildcard $(SSP_PATH)/list/*.*)
	@echo Security Service Provider component cleaning is done!
	@echo ----------------------------------------------------
