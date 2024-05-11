#------------------------------------------------------------------------------- 
#  \file  Makefile
#
#  \brief Make file for Security Trust Centre.
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

lib_name = lib$(TC_LIB).a

#***************************** Include directories *****************************
ifeq ($(USE_KF_MAC), TRUE)
  CFLAGS += $(addprefix -I,$(KF_INCS))
endif

CFLAGS +=                          \
  -I$(BASE_PATH)                \
  -I$(SE_PATH)/include             \
  -I$(CS_PATH)/include             \
  -I$(CS_PATH)/include/private     \
  -I$(NWK_PATH)/include            \
  -I$(APS_PATH)/include            \
  -I$(ZCL_PATH)/include            \
  -I$(PDS_PATH)/include            \
  -I$(PDS_PATH)/wl/include         \
  -I$(ZDO_PATH)/include            \
  -I$(ZDO_PATH)/include/private    \
  -I$(MAC_PHY_PATH)/include        \
  -I$(MAC_HWI_PATH)/include        \
  -I$(MAC_HWD_PATH)/include        \
  -I$(MAC_ENV_PATH)/include        \
  -I$(HAL_PATH)/include            \
  -I$(HAL_HWD_COMMON_PATH)/include \
  -I$(SSP_PATH)/include            \
  -I$(TC_PATH)/include/private     \
  -I$(TC_PATH)/include             \
  -I$(OSAL_PATH)                   \
  -I$(OSAL_PATH)/osal              \
  -I$(FREE_RTOS_PATH)/portable/GCC/ARM_CM4F \
  -I$(FREE_RTOS_PATH)/include      \
  -I$(RTOS_CONFIG_PATH)            \
  -I$(PARTPACK_PATCH)/include      \
  -I$(PARTPACK_PATCH)/include/soc  \
  -I$(CMIS_PATH)

#***************************** Object files ************************************
objects_tc =                                 \
  $(TC_PATH)/objs/tcAuthenticHandler.o       \
  $(TC_PATH)/objs/tcIndInput.o               \
  $(TC_PATH)/objs/tcKeyEstablishHandler.o    \
  $(TC_PATH)/objs/tcKeyUpdateHandler.o       \
  $(TC_PATH)/objs/tcRemoveHandler.o          \
  $(TC_PATH)/objs/tcResetHandler.o           \
  $(TC_PATH)/objs/tcTaskManager.o            \
  $(TC_PATH)/objs/tcDeviceTableCtrlHandler.o \
  $(TC_PATH)/objs/tcMem.o                    \
  $(TC_PATH)/objs/tcPromiscuousMode.o        \
  $(TC_PATH)/objs/tcPermissions.o

#***************************** Libraries ***************************************
lib_tc = $(TC_PATH)/lib/$(lib_name)

#***************************** Targets *****************************************
all: component_label $(lib_tc) size_tc

component_label:
	@echo 
	@echo ----------------------------------------------------
	@echo Trust Centre library creation.
	@echo ----------------------------------------------------
	$(Q)mkdir -p $(TC_PATH)/objs/
	$(Q)mkdir -p $(TC_PATH)/lib/
$(objects_tc): 
	$(CC_MSG)
	$(Q)$(CC) $(CFLAGS) $(CFLAGS_HWD) $^ -o $@
$(TC_PATH)/objs/tcTasakManager.o:          $(TC_PATH)/src/tcTaskManager.c
$(TC_PATH)/objs/tcMem.o:                   $(TC_PATH)/src/tcMem.c      
$(TC_PATH)/objs/tcAuthenticHandler.o:      $(TC_PATH)/src/tcAuthenticHandler.c
$(TC_PATH)/objs/tcCommon.o:                $(TC_PATH)/src/tcCommon.c
$(TC_PATH)/objs/tcIndInput.o:              $(TC_PATH)/src/tcIndInput.c
$(TC_PATH)/objs/tcKeyEstablishHandler.o:   $(TC_PATH)/src/tcKeyEstablishHandler.c
$(TC_PATH)/objs/tcKeyUpdateHandler.o:      $(TC_PATH)/src/tcKeyUpdateHandler.c
$(TC_PATH)/objs/tcRemoveHandler.o:         $(TC_PATH)/src/tcRemoveHandler.c
$(TC_PATH)/objs/tcResetHandler.o:          $(TC_PATH)/src/tcResetHandler.c
$(TC_PATH)/objs/tcTaskManager.o:           $(TC_PATH)/src/tcTaskManager.c
$(TC_PATH)/objs/tcDeviceTableCtrlHandler.o:$(TC_PATH)/src/tcDeviceTableCtrlHandler.c
$(TC_PATH)/objs/tcMem.o:                   $(TC_PATH)/src/tcMem.c
$(TC_PATH)/objs/tcPromiscuousMode.o:       $(TC_PATH)/src/tcPromiscuousMode.c
$(TC_PATH)/objs/tcPermissions.o:           $(TC_PATH)/src/tcPermissions.c

$(lib_tc): $(objects_tc)
	$(AR_MSG)
	$(Q)$(AR) $(AR_KEYS) $(lib_tc) $(objects_tc)

size_tc: $(lib_tc)
	$(SIZE_MSG)
	$(Q)$(SHOW_SIZE) -td $(lib_tc)

clean:
	@echo 
	@echo ----------------------------------------------------
	@echo Trust Centre component cleaning is started...
	$(Q)rm -f $(objects_tc) $(lib_tc) $(wildcard $(TC_PATH)/list/*.*)
	@echo Trust Centre component cleaning is done!
	@echo ----------------------------------------------------
