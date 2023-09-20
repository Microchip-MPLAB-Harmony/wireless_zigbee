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

#####################################################################################################
#################               TIMER CONFIGURATION                                   ###############
#####################################################################################################
global devicename
devicename = Variables.get("__PROCESSOR")

def enableTCC2(symbol, event):
    try:
        comp = event['source']
        if(event['value'] == 'TCC2'): #if TCC ENABLED box is ticked
            comp.setDependencyEnabled('TCC2_PWM_Zigbee', True) #Enabling TCC2 dependency
            comp.setDependencyEnabled('TC0_TMR_Zigbee', False) #Disabling TC0 dependency
            
            Database.deactivateComponents(['tc0'])
            Database.activateComponents(['tcc2'])
            Database.connectDependencies([[drvComponent.getID(),'TCC2_PWM_Zigbee', 'tcc2', 'TCC2_PWM']])
            
            comp.getSymbolByID('HALAPPCLOCK_C_TC0').setEnabled(False) #Disabling TC0 zigbee source/header files
            #comp.getSymbolByID('HALAPPCLOCK_H_TC0').setEnabled(False)
            comp.getSymbolByID('HALMACISR_C_TC0').setEnabled(False)
            #comp.getSymbolByID('HALMACISR_H_TC0').setEnabled(False)

            
            comp.getSymbolByID('HALAPPCLOCK_C_TCC2').setEnabled(True) #Enabling TCC2 zigbee source/header files
            #comp.getSymbolByID('HALAPPCLOCK_H_TCC2').setEnabled(True)
            comp.getSymbolByID('HALMACISR_C_TCC2').setEnabled(True)
            #comp.getSymbolByID('HALMACISR_H_TCC2').setEnabled(True)
           
        else:
            comp.setDependencyEnabled('TC0_TMR_Zigbee', True) #Enabling TC0 dependency
            comp.setDependencyEnabled('TCC2_PWM_Zigbee', False) #Disabling TCC2 dependency             
            
            Database.deactivateComponents(['tcc2'])
            Database.activateComponents(['tc0'])
            Database.connectDependencies([[drvComponent.getID(),'TC0_TMR_Zigbee', 'tc0', 'TC0_TMR']])
                        
            comp.getSymbolByID('HALAPPCLOCK_C_TC0').setEnabled(True)  #Enabling TC0 zigbee source/header files
            #comp.getSymbolByID('HALAPPCLOCK_H_TC0').setEnabled(True)
            comp.getSymbolByID('HALMACISR_C_TC0').setEnabled(True)
            #comp.getSymbolByID('HALMACISR_H_TC0').setEnabled(True)


            comp.getSymbolByID('HALAPPCLOCK_C_TCC2').setEnabled(False) #Disabling TCC2 zigbee source/header files
            #comp.getSymbolByID('HALAPPCLOCK_H_TCC2').setEnabled(False)
            comp.getSymbolByID('HALMACISR_C_TCC2').setEnabled(False)
            #comp.getSymbolByID('HALMACISR_H_TCC2').setEnabled(False)
           
    except Exception as e:
        print("Exception at enableTCC2 ",e)

if(devicename in pic32cx_bz2_family):
    
    try:
       
        timerSelect = drvComponent.createComboSymbol("TCC2_ENABLE", timerConfigMenu, ["TC0", "TCC2"])
        timerSelect.setLabel("Timer in use")
        timerSelect.setDefaultValue("TC0")
        timerSelect.setDescription("Timer select timer to use (TC0/TCC2)")

        # Timer TCC2 Enable
        timerTCC2Fire = drvComponent.createBooleanSymbol(None, None)
        timerTCC2Fire.setVisible(False)
        timerTCC2Fire.setDependencies(enableTCC2, ['TCC2_ENABLE'])

        #TC0 HEADER halAppClock.h and halMacIsr.h Enabled by default
        # halAppHeaderFile = drvComponent.createFileSymbol('HALAPPCLOCK_H_TC0', None)
        # halAppHeaderFile.setSourcePath('driver/zigbee/src/Components/hal/cortexm4/pic32cx_bz2/include/halAppClock_tc0.h')
        # halAppHeaderFile.setOutputName('halAppClock.h')
        # halAppHeaderFile.setDestPath('/zigbee/lib/inc/hal/cortexm4/pic32cx/include/')
        # halAppHeaderFile.setProjectPath('config/default/zigbee/lib/inc/hal/cortexm4/pic32cx/include/')
        # halAppHeaderFile.setType('HEADER')
        # halAppHeaderFile.setOverwrite(True)
        # halAppHeaderFile.setEnabled(True)

        # halAppHeaderFile = drvComponent.createFileSymbol('HALMACISR_H_TC0', None)
        # halAppHeaderFile.setSourcePath('driver/zigbee/src/Components/hal/cortexm4/pic32cx_bz2/include/halMacIsr_tc0.h')
        # halAppHeaderFile.setOutputName('halMacIsr.h')
        # halAppHeaderFile.setDestPath('/zigbee/lib/inc/hal/cortexm4/pic32cx/include/')
        # halAppHeaderFile.setProjectPath('config/default/zigbee/lib/inc/hal/cortexm4/pic32cx/include/')
        # halAppHeaderFile.setType('HEADER')
        # halAppHeaderFile.setOverwrite(True)
        # halAppHeaderFile.setEnabled(True)

        # #TCC2 HEADER halAppClock.h and halMacIsr.h Disabled by default
        # halAppHeaderFile = drvComponent.createFileSymbol('HALAPPCLOCK_H_TCC2', None)
        # halAppHeaderFile.setSourcePath('driver/zigbee/src/Components/hal/cortexm4/pic32cx_bz2/include/halAppClock_tcc2.h')
        # halAppHeaderFile.setOutputName('halAppClock.h')
        # halAppHeaderFile.setDestPath('/zigbee/lib/inc/hal/cortexm4/pic32cx/include/')
        # halAppHeaderFile.setProjectPath('config/default/zigbee/lib/inc/hal/cortexm4/pic32cx/include/')
        # halAppHeaderFile.setType('HEADER')
        # halAppHeaderFile.setOverwrite(True)
        # halAppHeaderFile.setEnabled(False)

        # halAppHeaderFile = drvComponent.createFileSymbol('HALMACISR_H_TCC2', None)
        # halAppHeaderFile.setSourcePath('driver/zigbee/src/Components/hal/cortexm4/pic32cx_bz2/include/halMacIsr_tcc2.h')
        # halAppHeaderFile.setOutputName('halMacIsr.h')
        # halAppHeaderFile.setDestPath('/zigbee/lib/inc/hal/cortexm4/pic32cx/include/')
        # halAppHeaderFile.setProjectPath('config/default/zigbee/lib/inc/hal/cortexm4/pic32cx/include/')
        # halAppHeaderFile.setType('HEADER')
        # halAppHeaderFile.setOverwrite(True)
        # halAppHeaderFile.setEnabled(False)


        #TC0 HEADER generate halAppClock.c Enabled by default
        halAppSourceFile = drvComponent.createFileSymbol('HALAPPCLOCK_C_TC0', None)
        halAppSourceFile.setSourcePath('driver/zigbee/src/Components/hal/cortexm4/pic32cx_bz2/src/halAppClock_tc0.c')
        halAppSourceFile.setOutputName('halAppClock.c')
        halAppSourceFile.setDestPath('/zigbee/systemresource/hal/cortexm4/pic32cx/src/')
        halAppSourceFile.setProjectPath('config/default/zigbee/systemresource/hal/cortexm4/pic32cx/src/')
        halAppSourceFile.setType('SOURCE')
        halAppSourceFile.setOverwrite(True)
        halAppSourceFile.setEnabled(True)

        halAppSourceFile = drvComponent.createFileSymbol('HALMACISR_C_TC0', None)
        halAppSourceFile.setSourcePath('driver/zigbee/src/Components/hal/cortexm4/pic32cx_bz2/src/halMacIsr_tc0.c')
        halAppSourceFile.setOutputName('halMacIsr.c')
        halAppSourceFile.setDestPath('/zigbee/systemresource/hal/cortexm4/pic32cx/src/')
        halAppSourceFile.setProjectPath('config/default/zigbee/systemresource/hal/cortexm4/pic32cx/src/')
        halAppSourceFile.setType('SOURCE')
        halAppSourceFile.setOverwrite(True)
        halAppSourceFile.setEnabled(True)

        #TCC2 HEADER halAppClock.c and halMacIsr.c Disabled by default
        halAppSourceFile = drvComponent.createFileSymbol('HALAPPCLOCK_C_TCC2', None)
        halAppSourceFile.setSourcePath('driver/zigbee/src/Components/hal/cortexm4/pic32cx_bz2/src/halAppClock_tcc2.c')
        halAppSourceFile.setOutputName('halAppClock.c')
        halAppSourceFile.setDestPath('/zigbee/systemresource/hal/cortexm4/pic32cx/src/')
        halAppSourceFile.setProjectPath('config/default/zigbee/systemresource/hal/cortexm4/pic32cx/src/')
        halAppSourceFile.setType('SOURCE')
        halAppSourceFile.setOverwrite(True)
        halAppSourceFile.setEnabled(False)

        halAppSourceFile = drvComponent.createFileSymbol('HALMACISR_C_TCC2', None)
        halAppSourceFile.setSourcePath('driver/zigbee/src/Components/hal/cortexm4/pic32cx_bz2/src/halMacIsr_tcc2.c')
        halAppSourceFile.setOutputName('halMacIsr.c')
        halAppSourceFile.setDestPath('/zigbee/systemresource/hal/cortexm4/pic32cx/src/')
        halAppSourceFile.setProjectPath('config/default/zigbee/systemresource/hal/cortexm4/pic32cx/src/')
        halAppSourceFile.setType('SOURCE')
        halAppSourceFile.setOverwrite(True)
        halAppSourceFile.setEnabled(False)
    except Exception as e:
        print("Exception at adding Timer configuration ",e )