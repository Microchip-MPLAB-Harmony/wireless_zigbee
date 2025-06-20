#include "zigbee/z3device_configs/stackConfig.h"
#include "zigbee/z3device_configs/zigbeeAppConfig.h"
#include "zigbee/z3device/common/include/zgb_task.h"
<#if DEVICE_DEEP_SLEEP_ENABLED>
#include "zigbee/z3device/common/include/z3Device.h"
</#if>
<#if TC_SWAPOUT_ENABLED>  
#ifdef _ZIGBEE_REV_23_SUPPORT_
#include "zigbee/z3device/common/include/app_tcSwapout.h"
#endif /* _ZIGBEE_REV_23_SUPPORT_ */
</#if>
#include "zigbee/lib/inc/pds/include/wlPdsMemIds.h"
#include "zigbee/lib/inc/mac_phy/mac_hwd_phy/RF231_RF212/PHY/include/phyInit.h"
#include "zigbee/lib/inc/systemenvironment/include/sysTaskManager.h"
#include "configserver/include/configserver.h"
#include "systemenvironment/include/sysSleep.h"
