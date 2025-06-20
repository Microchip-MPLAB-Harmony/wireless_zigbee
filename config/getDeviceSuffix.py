pic32cx_bz2_family = {'PIC32CX1012BZ25048',
                        'PIC32CX1012BZ25032',
                        'PIC32CX1012BZ24032',
                        'WBZ451',
                        'WBZ450',
                        'WBZ451H',
                        }

pic32cx_bz3_family = {'PIC32CX5109BZ31048',
                        'PIC32CX5109BZ31032',
                        'WBZ351',
                        'WBZ350',
                        }

pic32cx_bz36_family = {'PIC32CX5109BZ36048',
                       'PIC32CX5109BZ36032',
                       'PIC32WM_BZ3601',
                       'PIC32WM_BZ3602',
                       }
                      
pic32cx_bz6_family = {'PIC32CX2051BZ60048',
                      'PIC32CX2051BZ62064',
                      'PIC32CX2051BZ62132',
                      'WBZ650',
                      'WbZ651',
                      'WBZ652',
                      'WBZ653',
                      'PIC32WM_BZ6204',
                      'PIC32WM_BZ6203',
                      'PIC32WM_BZ6602',                      
                      'PIC32CX2051BZ62132_FPGA',
                      
                    }

processor = Variables.get('__PROCESSOR')

print("READING DEVICE SUFFIX")
global suffix 
suffix = ""

if  ( processor in pic32cx_bz2_family):
    suffix = "_bz2"    
elif( (processor in pic32cx_bz3_family) or (processor in pic32cx_bz36_family)):
    suffix = "_bz3"    
elif( processor in pic32cx_bz6_family):
    suffix = "_bz6"
