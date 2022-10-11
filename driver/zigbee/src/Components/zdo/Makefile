###########################################################################//##
# \file  Makefile
#
# \brief Main makefile of ZDO-layer.
#
# \author
#   Microchip Corporation: http://ww.microchip.com \n
#   Support email: support@microchip.com
#
# Copyright (c) 2008-2015, Microchip Corporation. All rights reserved.
# Licensed under Microchip's Limited License Agreement.
#
# \internal
#  History:
#   2010-11-18 Max Gekk - Created.
#  Last change:
#   $Id: Makefile 28547 2015-09-10 13:10:16Z mukesh.basrani $
################################################################################

COMPONENTS_PATH = ..
include $(COMPONENTS_PATH)/Makerules

# Build ZDO layer as whole file
ZDO_WHOLE_BUILD = 1

#ifeq ($(COMPILER_AND_MICRO_TYPE), IAR_ARM)
#  TMP_CFLAGS:=$(patsubst -Ohz,,$(CFLAGS))
#  CFLAGS = $(TMP_CFLAGS) -On
#endif

###### ZDO MODULES #########
modules =                 \
  zdoAddrResolving        \
  zdoBinding              \
  zdoCommands             \
  zdoServiceDiscovery     \
  zdoEndDeviceBinding     \
  zdoInit                 \
  zdoIntraPanPortability  \
  zdoLeaveNetwork         \
  zdoMem                  \
  zdoMgmtNwkUpdate        \
  zdoNodeManager          \
  zdoNotify               \
  zdoNwkManager           \
  zdoPermissionsTable     \
  zdoPowerManager         \
  zdoReset                \
  zdoSecurityManager      \
  zdoStartNetwork         \
  zdoStateMachine         \
  zdoTaskManager          \
  zdoZib                  \
  zdoParentAnnounce                  \
  zdoZdpReq

include_path =                   \
  $(BASE_PATH)                   \
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
  $(NWK_PATH)/include            \
  $(HAL_HWD_COMMON_PATH)/include \
  $(HAL_HWI_PATH)/include        \
  $(HAL_PATH)/include            \
  $(TC_PATH)/include             \
  $(ZCL_PATH)/include            \
  $(ZAPPSI_PATH)/include         \
  $(ZDO_PATH)/include            \
  $(COMPONENTS_PATH)/PersistDataServer/wl/include  \
  $(ZDO_PATH)/include/private    \
  $(OSAL_PATH)                   \
  $(OSAL_PATH)/osal              \
  $(FREE_RTOS_PATH)/portable/GCC/ARM_CM4F \
  $(FREE_RTOS_PATH)/include      \
  $(RTOS_CONFIG_PATH)            \
  $(PARTPACK_PATCH)/include      \
  $(PARTPACK_PATCH)/include/soc  \
  $(CMIS_PATH)                   \
  

ifeq ($(COMPILER_TYPE), GCC) # GCC flags -------------------------------
  CFLAGS += -Werror
  CFLAGS += -pedantic -Wextra
  CFLAGS += -Wstrict-overflow -Wstrict-overflow=5 -Wmissing-noreturn
  CFLAGS += -Wpointer-arith -Wswitch-default  -Wredundant-decls
  #CFLAGS += -Wuninitialized -Winit-self -Wdeclaration-after-statement
  CFLAGS += -Wundef -Wshadow -Wunsafe-loop-optimizations
  CFLAGS += -Wdisabled-optimization -Wstrict-prototypes
  #CFLAGS += -Wmissing-prototypes -Wmissing-declarations
  #CFLAGS += -Wbad-function-cast -Wcast-qual -Wnested-externs
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

CFLAGS += --misrac2004=4,~4.1,5,~5.1,~5.3,~5.4,6,~6.3,~6.4,8,~8.1,~8.5,~8.11,9,~9.3,10,~10.1,~10.3,~10.5,~10.6
CFLAGS += --misrac2004=11.1,~11.3,13,~13.5,15,~15.2,~15.4,16,~16.3,~16.5,17,~17.4,18.1,20,~20.1,~20.2,~20.6
CFLAGS += --misrac_verbose

##### PATHS FLAGS OF SYSTEM INCLUDES #########
CFLAGS += $(addprefix -I,$(include_path))
endif

###### LIB #########
BUILDDIR = .
LIBDIR = $(BUILDDIR)/lib
LDFLAGS = -L$(LIBDIR)
LIBNAME=lib$(ZDO_LIB).a
LIB = $(LIBDIR)/$(LIBNAME)

cmodules = $(addsuffix .c,$(addprefix $(BUILDDIR)/src/,$(modules)))

ifeq ($(ZDO_WHOLE_BUILD), 1)
CFLAGS +=-DZDO_PRIVATE=static
sources = $(BUILDDIR)/src/zdo.c
objects = $(BUILDDIR)/objs/zdo.o
else
CFLAGS +=-DZDO_PRIVATE=
sources = $(cmodules)
objects = $(addsuffix .o,$(addprefix $(BUILDDIR)/objs/,$(modules)))
endif

###### TARGETS ################
all: component_label $(LIB)
component_label:
	@echo
	@echo ----------------------------------------------------
	@echo ZDO library creation.
	@echo ----------------------------------------------------
	$(Q)mkdir -p $(BUILDDIR)/objs/
	$(Q)mkdir -p $(BUILDDIR)/lib/
################
$(BUILDDIR)/src/zdo.c: $(cmodules)
	$(Q)cat $^ > $@

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
	@echo ZDO component cleaning is started...
	$(Q)rm -f $(objects) $(LIB) $(wildcard $(ZDO_PATH)/list/*.*)
	$(Q)rm -f $(BUILDDIR)/src/zdo.c
	@echo ZDO component cleaning is done!
	@echo ----------------------------------------------------

