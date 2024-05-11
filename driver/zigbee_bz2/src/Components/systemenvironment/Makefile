COMPONENTS_PATH = ..
include $(COMPONENTS_PATH)/Makerules

###########
CFLAGS += -DSYS_LOG_UART
CFLAGS += -D_RF_RND_

##### PATHS FLAGS OF INCLUDES #########
ifeq ($(USE_KF_MAC), TRUE)
  CFLAGS += $(addprefix -I,$(KF_INCS))
endif

CFLAGS += -I./include
CFLAGS += -I$(BASE_PATH)
CFLAGS += -I$(ZDO_PATH)/include
CFLAGS += -I$(APS_PATH)/include
CFLAGS += -I$(ZCL_PATH)/include
CFLAGS += -I$(PDS_PATH)/include
CFLAGS += -I$(PDS_PATH)/wl/include
CFLAGS += -I$(PDS_PATH)/std/include
CFLAGS += -I$(NWK_PATH)/include
CFLAGS += -I$(HAL_PATH)/include
CFLAGS += -I$(HAL_HWD_COMMON_PATH)/include
CFLAGS += -I$(MAC_PHY_PATH)/include
CFLAGS += -I$(MAC_PHY_PATH)/MAC_HWD_PHY/RF231_RF212/PHY/include
CFLAGS += -I$(CS_PATH)/include
CFLAGS += -I$(CS_PATH)/include/private
CFLAGS += -I$(BSP_PATH)/include
CFLAGS += -I$(SSP_PATH)/include
CFLAGS += -I$(TC_PATH)/include
ifeq ($(BUILD_TARGET), TARGET_ZSE)
  CFLAGS += -I$(ZSE_PATH)/include
endif
ifeq ($(OS), FREE_RTOS)
  CFLAGS += -I$(FREE_RTOS_PATH)/portable/GCC/ARM_CM4F
  CFLAGS += -I$(FREE_RTOS_PATH)/include
  CFLAGS += -I$(AF_PATH)/
  CFLAGS += -I$(RTOS_CONFIG_PATH)
  CFLAGS += -I$(OSAL_PATH)
  CFLAGS += -I$(OSAL_PATH)/osal
endif

###############
BUILDDIR = .
LIBDIR = $(BUILDDIR)/lib
LDFLAGS = -L$(LIBDIR)
LIB_SYSTEM_ENVIRONMENT = $(LIBDIR)/libSystemEnvironment.a
LIB_MAIN = $(LIBDIR)/lib$(MAIN_LIB).a

objects =                             \
$(BUILDDIR)/objs/dbg.o                \
$(BUILDDIR)/objs/sysQueue.o           \
$(BUILDDIR)/objs/sysSleep.o           \
$(BUILDDIR)/objs/sysUtils.o           \
$(BUILDDIR)/objs/sysDuplicateTable.o  \
$(BUILDDIR)/objs/sysTimer.o           \
$(BUILDDIR)/objs/sysStat.o            \
$(BUILDDIR)/objs/sysEventsHandler.o   \
$(BUILDDIR)/objs/sysTaskManager.o     \
$(BUILDDIR)/objs/sysAssert.o          \
$(BUILDDIR)/objs/sysMutex.o

###### TARGETS ################
all: component_label $(LIB_SYSTEM_ENVIRONMENT)

component_label:
	@echo 
	@echo ----------------------------------------------------
	@echo System Environment library creation.
	@echo ----------------------------------------------------
	$(Q)mkdir -p $(BUILDDIR)/objs/
	$(Q)mkdir -p $(BUILDDIR)/lib/
vpath %.c src

$(BUILDDIR)/objs/%.o: %.c 
	$(CC_MSG)
	$(Q)$(CC) $(CFLAGS) $< -o $@

$(LIB_SYSTEM_ENVIRONMENT): $(objects)
	$(AR_MSG)
	$(Q)$(AR) $(AR_KEYS) $(LIB_SYSTEM_ENVIRONMENT) $(objects)
	$(SIZE_MSG)
	$(Q)$(SHOW_SIZE) -td $(LIB_SYSTEM_ENVIRONMENT)

clean:
	@echo 
	@echo ----------------------------------------------------
	@echo 'System Environment & Main common component cleaning is started...'
	$(Q)rm -f $(PROG) $(objects) $(BUILDDIR)/objs/main.o $(LIB_MAIN) $(LIB_SYSTEM_ENVIRONMENT) $(wildcard $(SE_PATH)/list/*.*)
	@echo 'System Environment & Main component cleaning is done!'
	@echo ----------------------------------------------------
