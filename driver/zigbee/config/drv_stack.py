###############################################################################
######################### Zigbee Stack Configurations #########################
###############################################################################


################################################################################
#### Component ####
################################################################################

def instantiateComponent(zigbeeStackComponent):
    print('ZIGBEE Stack Component')
    configName = Variables.get("__CONFIGURATION_NAME")
    print configName


    ############################################################################
    ### Add System file templates
    ############################################################################

    zbInitTemplates = [('sysInitData', 'system_initialize_data.c.ftl', 'core.LIST_SYSTEM_INIT_C_LIBRARY_INITIALIZATION_DATA'),
        ('sysInitMiddlewareZB', 'system_initialize_middleware.c.ftl', 'core.LIST_SYSTEM_INIT_C_INITIALIZE_MIDDLEWARE'),
        ('sysTaskMiddlewareDefZB', 'system_tasks_def.c.ftl', 'core.LIST_SYSTEM_RTOS_TASKS_C_DEFINITIONS'),
        ('sysTaskMiddlewareZB', 'system_tasks.c.ftl', 'core.LIST_SYSTEM_TASKS_C_CALL_LIB_TASKS'),
        ('sysDefZB', 'system_definitions.h.ftl', 'core.LIST_SYSTEM_DEFINITIONS_H_INCLUDES'),
        ]

    n = 0
    zbInit = []
    for i, f, p in zbInitTemplates:
        zbInit.append( zigbeeStackComponent.createFileSymbol(i, None))
        zbInit[n].setType('STRING')
        zbInit[n].setOutputName(p)
        zbInit[n].setSourcePath('driver/zigbee/templates/system/' + f)
        zbInit[n].setMarkup(True)
        print('{} file: {} pos: {}'.format(n, f, p))
        n = n + 1


    ############################################################################
    ### Add Zigbee static header files
    ############################################################################
    # Add zigbee_stack_stub.h
    HeaderFile = zigbeeStackComponent.createFileSymbol(None, None)
    HeaderFile.setSourcePath('driver/zigbee/src/zigbee_lib/zigbee_stack_stub.h')
    HeaderFile.setOutputName('zigbee_stack.h')
    HeaderFile.setOverwrite(True)
    HeaderFile.setDestPath('/lib/zigbee_lib')
    HeaderFile.setProjectPath('config/' + configName + '/lib_tmp/')
    HeaderFile.setType('HEADER')
    HeaderFile.setEnabled(True)


    ############################################################################
    ### Add Zigbee static source files
    ############################################################################
    # FIXME: this is a stub - replace with the real zigbee stack
    # Add zigbee_stack_stub.c
    HeaderFile = zigbeeStackComponent.createFileSymbol(None, None)
    HeaderFile.setSourcePath('driver/zigbee/src/zigbee_lib/zigbee_stack_stub.c')
    HeaderFile.setOutputName('zigbee_stack.c')
    HeaderFile.setOverwrite(True)
    HeaderFile.setDestPath('/lib/zigbee_lib')
    HeaderFile.setProjectPath('config/' + configName + '/lib_tmp/')
    HeaderFile.setType('HEADER')
    HeaderFile.setEnabled(True)
