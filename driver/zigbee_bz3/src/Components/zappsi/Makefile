###########################################################################//##
# \file  Makefile
#
# \brief Main makefile of ZAppSI-layer.
#
# \author
#   Microchip Corporation: http://ww.microchip.com \n
#   Support email: support@microchip.com
#
# Copyright (c) 2008-2011, Microchip Corporation. All rights reserved.
# Licensed under Microchip's Limited License Agreement.
#
# \internal
#  History:
#   2011-08-10 A. Razinkov - Created.
#  Last change:
#   $Id: Makefile 18049 2011-07-20 13:08:36Z mgekk $
################################################################################

COMPONENTS_PATH = ..
include $(COMPONENTS_PATH)/Makerules

#ifeq ($(COMPILER_AND_MICRO_TYPE), IAR_AVR)
#  TMP_CFLAGS:=$(patsubst -Ohz,,$(CFLAGS))
#  CFLAGS = $(TMP_CFLAGS) -Om
#endif

###### ZAppSI MODULES #########
modules =                \
  zsiInit                \
  zsiNotify              \
  zsiMem                 \
  zsiTaskManager         \
  zsiMemoryManager       \
  zsiDriver              \
  zsiSerialController    \
  zsiSerializer          \
  zsiSys                 \
  zsiAps                 \
  zsiZdo                 \
  zsiZdp                 \
  zsiNwk                 \
  zsiSysSerialization    \
  zsiApsSerialization    \
  zsiZdoSerialization    \
  zsiZdpSerialization    \
  zsiNwkSerialization    \
  zsiStubs
  
include_path =                   \
  $(KF_INCS)                     \
  $(SSP_PATH)/include            \
  $(SE_PATH)/include             \
  $(MAC_PHY_PATH)/include        \
  $(MAC_HWI_PATH)/include        \
  $(MAC_HWD_PATH)/include        \
  $(MAC_ENV_PATH)/include        \
  $(CS_PATH)/include             \
  $(CS_PATH)/include/private     \
  $(APS_PATH)/include            \
  $(ZCL_PATH)/include            \
  $(ZDO_PATH)/include            \
  $(NWK_PATH)/include            \
  $(HAL_HWD_COMMON_PATH)/include \
  $(HAL_HWI_PATH)/include        \
  $(HAL_PATH)/include            \
  $(ZCL_PATH)/include

ifeq ($(COMPILER_TYPE), GCC) # GCC flags -------------------------------
  CFLAGS += -Wextra -Wfatal-errors -Werror
  CFLAGS += -Wstrict-overflow -Wstrict-overflow=5 -Wmissing-noreturn
  CFLAGS += -Wpointer-arith -Wswitch-default  -Wredundant-decls
  CFLAGS += -Wuninitialized -Winit-self -Wdeclaration-after-statement
  CFLAGS += -Wundef -Wshadow -Wunsafe-loop-optimizations
  CFLAGS += -Wdisabled-optimization -Wstrict-prototypes
  CFLAGS += -Wbad-function-cast
  CFLAGS += -Winline -Wno-multichar
#  CFLAGS += -Wsign-conversion
ifeq ($(CROSS_COMPILER), avr-)
  CFLAGS += -Wpadded
  CFLAGS += -Wlogical-op  -Wcast-align -Wpacked
##### OPTIMIZATION OPTIONS #####
  CFLAGS += -fsee
endif
ifeq ($(CROSS_COMPILER), arm-none-eabi-)
  CFLAGS += -Wjump-misses-init
endif
##### PATHS FLAGS OF SYSTEM INCLUDES #########
CFLAGS += $(addprefix -isystem ,$(include_path))
else

#TMP_CFLAGS:=$(patsubst -e,,$(CFLAGS))
#CFLAGS = $(TMP_CFLAGS) --strict_ansi

CFLAGS += --misrac2004=4,5,~5.1,~5.3,~5.4,6,~6.3,~6.4,8,~8.1,~8.5,~8.11,9,~9.2,~9.3,10,~10.1,~10.3,~10.5,~10.6
CFLAGS += --misrac2004=13,~13.5,15,~15.2,~15.4,16,~16.3,~16.5,17,~17.4,18.1,20,~20.1,~20.2,~20.6
CFLAGS += --misrac_verbose

##### PATHS FLAGS OF SYSTEM INCLUDES #########
CFLAGS += $(addprefix -I,$(include_path))
endif

##### PATHS FLAGS OF ZAPPSI INCLUDES #########
CFLAGS += -I$(ZAPPSI_PATH)/include

###### LIB #########
BUILDDIR = .
LIBDIR = $(BUILDDIR)/lib
LDFLAGS = -L$(LIBDIR)
LIBNAME=lib$(ZAPPSI_LIB).a
LIB = $(LIBDIR)/$(LIBNAME)

cmodules = $(addsuffix .c,$(addprefix $(BUILDDIR)/src/,$(modules)))

sources = $(cmodules)
objects = $(addsuffix .o,$(addprefix $(BUILDDIR)/objs/,$(modules)))

###### TARGETS ################
all: component_label $(LIB)
component_label:
	@echo
	@echo ----------------------------------------------------
	@echo ZAppSI library creation.
	@echo ----------------------------------------------------

################
$(BUILDDIR)/objs/%.o: $(BUILDDIR)/src/%.c
	$(CC_MSG)
	$(Q)$(CC) $(CFLAGS) $^ -o $@

################
$(LIB): $(objects)
	$(AR_MSG)
	$(Q)$(AR) $(AR_KEYS) $(LIB) $(objects)
	$(SIZE_MSG)
	$(Q)$(SHOW_SIZE) -td $(LIB)

################
clean:
	@echo
	@echo ----------------------------------------------------
	@echo ZAppSI component cleaning is started...
	$(Q)rm -f $(objects) $(LIB) $(wildcard $(ZAppSI_PATH)/list/*.*)
	@echo ZAppSI component cleaning is done!
	@echo ----------------------------------------------------

