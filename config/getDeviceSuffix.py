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
processor = Variables.get('__PROCESSOR')

print("READING DEVICE SUFFIX")
global suffix 
suffix = ""

if  ( processor in pic32cx_bz2_family):
    suffix = "_bz2"    
elif( processor in pic32cx_bz3_family):
    suffix = "_bz3"    
