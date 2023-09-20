############################################################################################################
###########################################  CUSTOM CLUSTER CONFIGURATION   #################################
############################################################################################################

############################################################################################################
############################################# Variable Definitions #########################################
############################################################################################################

global dependencyLock
dependencyLock = 0

global MAX_CLUSTER_SIZE
MAX_CLUSTER_SIZE = 10

global MAX_ATTRIBUTE_SIZE
MAX_ATTRIBUTE_SIZE = 10

global MAX_COMMAND_SIZE
MAX_COMMAND_SIZE = 10

global MAX_COMMAND_PARAMS
MAX_COMMAND_PARAMS = 10

# Custom cluster FTL files and menu symbols

global devicename # The deviceName from drvZigbeeLib shows erroneous behavious
                  # hence we define another instance

devicename = Variables.get("__PROCESSOR")

print("CUSTOM CLUSTER EXECUTION ",devicename, devicename in pic32cx_bz2_family)

global CUSTOM_CLUSTER_ENABLED
CUSTOM_CLUSTER_ENABLED = True

#We disable Custom clusters for devices not in bz2 family
if (devicename not in pic32cx_bz2_family):
    MAX_CLUSTER_SIZE, MAX_ATTRIBUTE_SIZE, MAX_COMMAND_SIZE, MAX_COMMAND_PARAMS = 1, 1, 1, 1 
    #The value used is 1 instead of zero because symbols will not be created if it's 0
    #If Custom Cluster symbols are not created, then associated template files won't get generated

    CUSTOM_CLUSTER_ENABLED = False
    #The visiblity of the Custom cluster option in the configurations menu


global devID
devID = drvZigbeeComponent.getID()

global FILE_PREFIX

#Used to decide what the file name prefix of where the custom cluster has to be in
FILE_PREFIX = {
        "ZIGBEE_COLOR_SCENE_CONTROLLER": "csc",
        "ZIGBEE_MULTI_SENSOR": "ms",
        "ZIGBEE_COMBINED_INTERFACE": "ci",
        "ZIGBEE_CONTROL_BRIDGE": "cb", 
        "ZIGBEE_THERMOSTAT": "th",
        "ZIGBEE_IAS_ACE": "iasACE",
        "ZIGBEE_ON_OFF_LIGHT": "light",
        "ZIGBEE_DIMMABLE_LIGHT": "light" ,
        "ZIGBEE_COLOR_LIGHT": "light",
        "ZIGBEE_EXTENDED_COLOR_LIGHT": "light" ,
        "ZIGBEE_TEMPERATURE_COLOR_LIGHT": "light",
        "ZIGBEE_CUSTOM": "custom"
       }

global prefix
prefix = FILE_PREFIX[devID]

#Used to decide where the custom cluster files are supposed to be placed
FILE_PATH = {
        "ZIGBEE_COLOR_SCENE_CONTROLLER": "colorSceneController",
        "ZIGBEE_MULTI_SENSOR": "multiSensor",
        "ZIGBEE_COMBINED_INTERFACE": "combinedInterface",
        #"ZIGBEE_CONTROL_BRIDGE": "light",
        "ZIGBEE_THERMOSTAT": "thermostat",
        "ZIGBEE_IAS_ACE": "ias_ace",
        "ZIGBEE_ON_OFF_LIGHT": "light",
        "ZIGBEE_DIMMABLE_LIGHT": "light" ,
        "ZIGBEE_COLOR_LIGHT": "light",
        "ZIGBEE_EXTENDED_COLOR_LIGHT": "light" ,
        "ZIGBEE_TEMPERATURE_COLOR_LIGHT": "light",
        "ZIGBEE_CUSTOM": "custom"
       }

global TYPES
TYPES = {    
    'General Data' : ['data8','data16','data32','data64'],
    'Boolean': ['bool'],    
    'Bitmap': ['map8','map16','map32','map64'],    
    'Unsigned Integer': ['uint8','uint16','uint32','uint64'],    
    'Signed Integer': ['int8','int16','int32','int64',], 
    'Enumeration': ['enum8','enum16'],
    'String': ['octstr', 'string', 'octstr16', 'string16'],
    'Array': ['uint8',],    
    }

global SYMBOL_TYPES 
SYMBOL_TYPES  = {
        'General Data' : 'GENERAL',
        'Boolean':'BOOLEAN',
        'Bitmap': 'BITMAP',
        'Unsigned Integer': 'UNSIGNED',
        'Signed Integer': 'SIGNED',
        'Enumeration': 'ENUM',
        'String': 'STRING',
        'Array': 'ARRAY',        
        }
############################################################################################################
############################################# Function Definitions #########################################
############################################################################################################

def customClusterCSCheck(symbol, event):

    global dependencyLock

    if(dependencyLock):    
        return
    
    dependencyLock = 1
    try:
        val = event['value'] #Get the value of the enable tick box for a custom cluster
        component = symbol.getComponent()

        number = int(symbol.getID().split('_')[0][3:])
        symName = 'ZCC'+str(number) + "_" + "CUSTOM_CLUSTER_NAME"
        symID = 'ZCC'+str(number) + "_" + "CUSTOM_CLUSTER_ID"

        name = component.getSymbolByID(symName)
        id = component.getSymbolByID(symID)

        name.setVisible(val)
        id.setVisible(val)
        symbol.setVisible(val)
    

        dummy = component.getSymbolByID('DUMMY')
        dummy.setValue("END RECURSION") # used to reset the dependencyLock global variable
    except Exception as e:
        print("EXCEPTION AT CLIENT/SERVER CHOICE ",e)

def customClusterClientCheck(symbol, event):
    val = event['value']
      
    if ((val == False) or (val == "SERVER")):
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

def customClusterServerCheck(symbol, event):
    val = event['value']
 
    if ((val == False) or (val == "CLIENT")): #value of 'val' can either be Bool or String
        symbol.setVisible(False)
    else:
        symbol.setVisible(True)

##START OF IMPLEMENTING CUSTOM ATTRIBUTES FUNCTIONS

def customClusterChangeTypeVisib(symbol, event):
    try:
        val = event["value"]
        if(val==False):
            symbol.setVisible(val) #set visibility depending on bool 

    except Exception as e:
        print('ZCC'+str(cli) + "_" +"EXCEPTION AT customClusterChangeTypeVisib() ", e)

def changeNoOfCustomCluster(symbol, event):
    global MAX_CLUSTER_SIZE
    component = event['source']
    noOfCluster = symbol.getValue()

    global dependencyLock
    if(dependencyLock):    
        return
    
    dependencyLock = 1

    try:
        for clusterIndex in range(MAX_CLUSTER_SIZE):
            symN = 'ZCC'+str(clusterIndex) + "_CUSTOM_CLUSTER_ENABLE"
            display_i = component.getSymbolByID(symN)
            display_i.setVisible(False)

            SourceN = 'ZCC'+str(clusterIndex)+'_'+'CUSTOM_CLUSTER_GENERATION_SOURCE'
            HeaderN = 'ZCC'+str(clusterIndex)+'_'+'CUSTOM_CLUSTER_GENERATION_HEADER'
            ServerHeaderN = 'ZCC'+str(clusterIndex)+'_'+'CUSTOM_CLUSTER_GENERATION_SERVER_HEADER'

            SourceFile = component.getSymbolByID(SourceN)
            SourceFile.setEnabled(False)

            HeaderFile = component.getSymbolByID(HeaderN)
            HeaderFile.setEnabled(False)

            ServerHeader = component.getSymbolByID(ServerHeaderN)
            ServerHeader.setEnabled(False)

        for visibleClusterNo in range(noOfCluster):
            symN = 'ZCC'+str(visibleClusterNo) + "_CUSTOM_CLUSTER_ENABLE"
            display_i = component.getSymbolByID(symN)
            display_i.setVisible(True)

            SourceN = 'ZCC'+str(visibleClusterNo)+'_'+'CUSTOM_CLUSTER_GENERATION_SOURCE'
            HeaderN = 'ZCC'+str(visibleClusterNo)+'_'+'CUSTOM_CLUSTER_GENERATION_HEADER'
            ServerHeaderN = 'ZCC'+str(visibleClusterNo)+'_'+'CUSTOM_CLUSTER_GENERATION_SERVER_HEADER'

            SourceFile = component.getSymbolByID(SourceN)
            SourceFile.setEnabled(True)

            HeaderFile = component.getSymbolByID(HeaderN)
            HeaderFile.setEnabled(True)

            ServerHeader = component.getSymbolByID(ServerHeaderN)
            ServerHeader.setEnabled(True)

            
        dummy = component.getSymbolByID('DUMMY')
        dummy.setValue("END RECURSION") # used to reset the dependencyLock global variable

    except Exception as e:
        print("EXCEPTION AT CHANGING CUSTOM CLUSTER NO ",e)

############################################################################################################
##################################### Command Set dependency functions #####################################
############################################################################################################

def customClusterChangeClassType(symbol, event):#This function is triggered when class type is changed
    global dependencyLock # To prevent set Label, set Value from triggering any set dependency function.
    
    if(dependencyLock):    
        return
    
    dependencyLock = 1
    try:
        # THE name of the symbol that can call this function is :  
        #       -> eg: ZCC0_CUSTOM_CLUSTER_CLIENT_COMMANDS_CLASSTYPE_i_j
        
        # THE name of the symbol that this function should affect the visibility and label of :  
        #       -> eg: ZCC0_CUSTOM_CLUSTER_CLIENT_COMMANDS_TYPE_GENERAL_i_j etc..

        value = symbol.getValue()
        
        component = symbol.getComponent() # Get component

        # in this block, we disable the visibility of every type symbol
        for stype in SYMBOL_TYPES .values():
            typeSymID = symbol.getID().replace('CLASSTYPE', 'TYPE_'+str(stype))
            typeSym = component.getSymbolByID(typeSymID)
            typeSym.setVisible(False)

        # here we set the visibility of the type according to the one chosen
        typeSymID = symbol.getID().replace('CLASSTYPE', 'TYPE_'+str(SYMBOL_TYPES [value])) # We get the TYPE symbol equivalent to it
        typeSym = component.getSymbolByID(typeSymID)
        

        typeSym.setLabel('Select Datatype')
        if(str(SYMBOL_TYPES [value])=='ARRAY'):
            typeSym.setLabel('Select Size')
        typeSym.setVisible(symbol.getVisible())         

        # Control visibility of Boundary and it's min, max when incompatible type is chosen

        iValue = symbol.getID().rsplit('_',1)[-1] # To get the trailing number of the command 
        boundarySymID = '_'.join( symbol.getID().split('_')[:5] + ['PROP_BOUNDARY_',] )  + str(iValue)
        boundaryMinSymID = '_'.join( symbol.getID().split('_')[:5] + ['PROP_BOUNDARY_MIN_',] )  + str(iValue)
        boundaryMaxSymID = '_'.join( symbol.getID().split('_')[:5] + ['PROP_BOUNDARY_MAX_',] )  + str(iValue)

        value = symbol.getValue()
        condition = (value == 'General Data' or value == 'Signed Integer' or value == 'Unsigned Integer')

        if('ATTRIBUTES' in symbol.getID()):                
            boundarySym = component.getSymbolByID(boundarySymID)
            boundarySym.setVisible(condition)

            boundaryMinSym = component.getSymbolByID(boundaryMinSymID)
            boundaryMaxSym = component.getSymbolByID(boundaryMaxSymID)

            boundaryMinSym.setVisible(boundarySym.getVisible()*boundarySym.getValue())
            boundaryMaxSym.setVisible(boundarySym.getVisible()*boundarySym.getValue())

        dummy = component.getSymbolByID('DUMMY')
        dummy.setValue("END RECURSION") # used to reset the dependencyLock global variable

    except Exception as e:
        print("EXCEPTION at changing class type ",e)

def customClusterParam(symbol, event): #This function is triggered when param number is increased
    global dependencyLock # To prevent set Label, set Value from triggering any set dependency function.
    
    if(dependencyLock):        
        return
    
    dependencyLock = 1
    try:
        # THE name of the symbol that can call this function is :  
        #       -> eg: ZCC0_CUSTOM_CLUSTER_CLIENT_PARAM_NO_i
        
        # THE name of the symbol that this function should affect the visibility and label of :  
        #       -> eg: ZCC0_CUSTOM_CLUSTER_CLIENT_COMMANDS_CLASSTYPE_i_j
        #       -> eg: ZCC0_CUSTOM_CLUSTER_CLIENT_COMMANDS_TYPE_GENERAL_i_j etc..

        iValue = symbol.getID().rsplit('_',1)[-1] # To get the trailing number of the command 
        
        component = symbol.getComponent()

        paramNo = symbol.getValue()

        for j in range(MAX_COMMAND_PARAMS):
            classSymID = '_'.join( symbol.getID().split('_')[:5] + ['CLASSTYPE_',] )  + str(iValue) + str("_") + str(j)
            paramSymID = '_'.join( symbol.getID().split('_')[:5] + ['PARAMNAME_',] )  + str(iValue) + str("_") + str(j)

            classSym = component.getSymbolByID(classSymID)
            paramSym = component.getSymbolByID(paramSymID)

            if(classSym.getLabel()[:3]=='ZCC'):
                classSym.setLabel('Select Datatype class')
            
            if(paramSym.getLabel()[:3]=='ZCC'):
                paramSym.setLabel('Parameter Name')
                paramSym.setValue("param"+str(j))

            #classSym.setDefaultValue('General Data') # We set the default class value to 'General Data'
            #Removed default type because it works with Enum as default by itself

            key = classSym.getValue()

            typeSymID = '_'.join( symbol.getID().split('_')[:5] + ['TYPE_'+ str(SYMBOL_TYPES [key]) +'_',] )  + str(iValue) + str("_") + str(j)            
            # eg: CUSTOM_CLUSTER_SERVER_COMMANDS_TYPE_GENERAL_i_j
            typeSym = component.getSymbolByID(typeSymID)

            if(typeSym.getLabel()[:3]=='ZCC'):
                typeSym.setLabel('Select Datatype')

            if( j < paramNo):
                classSym.setVisible(True)
                typeSym.setVisible(True)
                paramSym.setVisible(True)
                
            else:
                classSym.setVisible(False)
                typeSym.setVisible(False)
                paramSym.setVisible(False)

        dummy = component.getSymbolByID('DUMMY')
        dummy.setValue("END RECURSION") # used to reset the dependencyLock global variable

    except Exception as e:
        print("EXCEPTION at callback function for changing parameter number ",e)


def customClusterChangeLabel(symbol, event): # This function is triggered when command id, or name is changed
    global dependencyLock # To prevent set Label, set Value from triggering any set dependency function.
    
    if(dependencyLock):
        
        return
    dependencyLock = 1
    try:       
        # THE name of the symbol that can call this function is :  
        #       -> eg: ZCC0_CUSTOM_CLUSTER_CLIENT_COMMANDS_ID_i
        #       -> eg: ZCC0_CUSTOM_CLUSTER_CLIENT_COMMANDS_NAME_i

        # THE name of the symbol that this function should affect the visibility and label of :  
        #       -> eg: ZCC0_CUSTOM_CLUSTER_CLIENT_COMMANDS_DISPLAY_i

        iValue = symbol.getID().rsplit('_',1)[-1] # To get the trailing number of the command        

        # We take the equivalent DISPLAY symbol to modify
        displaySymID = '_'.join( symbol.getID().split('_')[:5] + ['DISPLAY_',] )  + str(iValue)

        component = symbol.getComponent()
        displaySym = component.getSymbolByID(displaySymID)

        # We try to identify whether the calling symbol is a NAME or ID command symbol
        caller = symbol.getID().rsplit('_',2)[-2] # To get whether NAME or ID called this.

        containsWhitespace = displaySym.getLabel().count(' ')

        if(caller == 'NAME' and containsWhitespace):
            value = symbol.getValue().replace(' ','') # We remove whitespace to avoid issues
            # with variable names in generation
            
            existingLabel = displaySym.getLabel().split(' ',1)
            
            existingLabel[1] = value

            newLabel = ' '.join(existingLabel)            
            
            displaySym.setLabel(newLabel)

        elif(caller == 'ID' and containsWhitespace):
            value = symbol.getValue()
            hexN = "{0:#0{1}x}".format(value,4).upper()

            existingLabel = displaySym.getLabel().split(' ',1)                        
            existingLabel[0] = hexN
            
            newLabel = ' '.join(existingLabel)     
            
            displaySym.setLabel(newLabel)

        dummy = component.getSymbolByID('DUMMY')
        dummy.setValue("END RECURSION") # used to reset the dependencyLock global variable


    except Exception as e:
        print("EXCEPTION at callback for changing label ",e, " caused by ", event['id'])
    



def customClusterCommandVis(symbol, event): # This function is triggered when command tickbox is selected/unselected
    #This function is reponsible for making Command id, name, no of parameters visible and set their label if unset.
    global dependencyLock # To prevent set Label, set Value from triggering any set dependency function.
    
    if(dependencyLock):
        
        return
    
    dependencyLock = 1
    
    try:
        # THE name of the symbol that can call this function is :  
        #       -> eg: ZCC0_CUSTOM_CLUSTER_CLIENT_COMMANDS_DISPLAY_i
        #       -> eg: ZCC0_CUSTOM_CLUSTER_SERVER_COMMANDS_DISPLAY_i

        # THE name of the symbol that this function should affect the visibility and label of :  
        #       -> eg: ZCC0_CUSTOM_CLUSTER_CLIENT_COMMANDS_ID_i
        #       -> eg: ZCC0_CUSTOM_CLUSTER_CLIENT_COMMANDS_NAME_i
        #       -> eg: ZCC0_CUSTOM_CLUSTER_CLIENT_COMMANDS_PARAM_NO_i
                

        iValue = symbol.getID().rsplit('_',1)[-1] # To get the trailing number of the command
        
        # We take the equivalent DISPLAY symbol to modify 
        idSymID = '_'.join( symbol.getID().split('_')[:5] + ['ID_',] )  + str(iValue)
        nameSymID = '_'.join( symbol.getID().split('_')[:5] + ['NAME_',] ) + str(iValue)
        paramSymID = '_'.join( symbol.getID().split('_')[:5] + ['PARAM_NO_',] ) + str(iValue)
        # ctsSymID = '_'.join( symbol.getID().split('_')[:5] + ['CTS_',] ) + str(iValue) #Commented in case of reimplementing devices that can act both as client and server
        responseSymID = '_'.join( symbol.getID().split('_')[:5] + ['RESPONSE_',] ) + str(iValue)
        ackSymID = '_'.join( symbol.getID().split('_')[:5] + ['ACK_',] ) + str(iValue)
        # Returns symbol ID of format ZCCi_CUSTOM_CLUSTER_CLIENT/SERVER_COMMANDS_[id,name,param]_]

        component = symbol.getComponent() # We use this to get the component to access DISPLAY vars
        
        idSym = component.getSymbolByID(idSymID)
        idSym.setVisible(symbol.getValue())
        if(idSym.getLabel()[:3] == 'ZCC' ): #  comparison to check if Label has been set already, as setLabel costs performance
            idSym.setLabel('Command ID')
            idSym.setMin(0) #setting mininum and maximum for command IDs
            idSym.setMax(int('ff',16))
        
        nameSym = component.getSymbolByID(nameSymID)
        nameSym.setVisible(symbol.getValue())
        if(nameSym.getLabel()[:3] == 'ZCC' ): #  comparison to check if Label has been set already, as setLabel costs performance
            nameSym.setLabel('Command Name')
        
        paramSym = component.getSymbolByID(paramSymID)
        paramSym.setVisible(symbol.getValue())
        if(paramSym.getLabel()[:3] == 'ZCC' ): #  comparison to check if Label has been set already, as setLabel costs performance
            paramSym.setLabel('Command Parameter No ')
            paramSym.setMax(MAX_COMMAND_PARAMS)
            paramSym.setMin(0)

        # ctsSym = component.getSymbolByID(ctsSymID)
        # ctsSym.setVisible(symbol.getValue())
        # if(ctsSym.getLabel()[:3] == 'ZCC' ): #  comparison to check if Label has been set already, as setLabel costs performance
        #     ctsSym.setLabel('Direction of data')

        responseSym = component.getSymbolByID(responseSymID)
        responseSym.setVisible(symbol.getValue())
        if(responseSym.getLabel()[:3] == 'ZCC' ): #  comparison to check if Label has been set already, as setLabel costs performance
            responseSym.setLabel('Response type')

        ackSym = component.getSymbolByID(ackSymID)
        ackSym.setVisible(symbol.getValue())
        if(ackSym.getLabel()[:3] == 'ZCC' ): #  comparison to check if Label has been set already, as setLabel costs performance
            ackSym.setLabel('Acknowledgement')

        
        dummy = component.getSymbolByID('DUMMY')
        dummy.setValue("END RECURSION") # used to reset the dependencyLock global variable


    except Exception as e:
        print("EXCEPTION at callback for command tickbox (customClusterCommandVis) ", e)


def customClusterAttributesVis(symbol, event): # This function is triggered when Attributes tickbox is selected/unselected
    #This function is reponsible for making Attributes id, name, no of parameters visible and set their label if unset.
    global dependencyLock # To prevent set Label, set Value from triggering any set dependency function.
    
    if(dependencyLock):
        
        return
    dependencyLock = 1
    try:
        # THE name of the symbol that can call this function is :  
        #       -> eg: ZCC0_CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_DISPLAY_i
        #       -> eg: ZCC0_CUSTOM_CLUSTER_SERVER_ATTRIBUTES_DISPLAY_i

        # THE name of the symbol that this function should affect the visibility and label of :  
        #       -> eg: ZCC0_CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_ID_i
        #       -> eg: ZCC0_CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_NAME_i        

        iValue = symbol.getID().rsplit('_',1)[-1] # To get the trailing number of the command

        # We take the equivalent DISPLAY symbol to modify 
        idSymID = '_'.join( symbol.getID().split('_')[:5] + ['ID_',] )  + str(iValue)
        nameSymID = '_'.join( symbol.getID().split('_')[:5] + ['NAME_',] ) + str(iValue)
        classSymID = '_'.join( symbol.getID().split('_')[:5] + ['CLASSTYPE_',] ) + str(iValue)       

        boundarySymID = '_'.join( symbol.getID().split('_')[:5] + ['PROP_BOUNDARY_',] ) + str(iValue)
        reportSymID = '_'.join( symbol.getID().split('_')[:5] + ['PROP_REPORTABLE_',] ) + str(iValue)
        rwSymID = '_'.join( symbol.getID().split('_')[:5] + ['PROP_RW_',] ) + str(iValue)

        # Returns symbol ID of format ZCCi_CUSTOM_CLUSTER_CLIENT/SERVER_ATTRIBUTES_[id,name,param]_]

        component = symbol.getComponent() # We use this to get the component to access DISPLAY vars

        idSym = component.getSymbolByID(idSymID)
        idSym.setVisible(symbol.getValue())
        if(idSym.getLabel()[:3] == 'ZCC' ): #  comparison to check if Label has been set already, as setLabel costs performance
            idSym.setLabel('Attribute ID')
            idSym.setMin(0) #setting mininum and maximum for command IDs
            idSym.setMax(int('ffff',16))
        
        nameSym = component.getSymbolByID(nameSymID)
        nameSym.setVisible(symbol.getValue())
        if(nameSym.getLabel()[:3] == 'ZCC' ): #  comparison to check if Label has been set already, as setLabel costs performance
            nameSym.setLabel('Attribute Name')

        classSym = component.getSymbolByID(classSymID)
        classSym.setVisible(symbol.getValue())     
        
        if(classSym.getLabel()[:3] == 'ZCC'):
            classSym.setLabel('Select Datatype class')
            classSym.setValue('Enumeration')

            dataType = SYMBOL_TYPES[classSym.getValue()] 
            typeSym = component.getSymbolByID('_'.join( symbol.getID().split('_')[:5] + ['TYPE_'+ dataType +'_',] ) + str(iValue))            
            typeSym.setVisible(symbol.getValue()) 
            typeSym.setLabel('Select Datatype') # We set label
        else:
            dataType = SYMBOL_TYPES[classSym.getValue()]
            typeSymbol = component.getSymbolByID('_'.join( symbol.getID().split('_')[:5] + ['TYPE_' + dataType + "_", ] ) + str(iValue))
            typeSymbol.setVisible(symbol.getValue())

        boundarySym = component.getSymbolByID(boundarySymID)
        boundarySym.setVisible(symbol.getValue())        
        if(boundarySym.getLabel()[:3] == 'ZCC'):
            boundarySym.setLabel('Enable Boundary property')
            boundarySym.setVisible(False) #false by default for enumeration
        
        reportSym = component.getSymbolByID(reportSymID)
        reportSym.setVisible(symbol.getValue())        
        if(reportSym.getLabel()[:3] == 'ZCC'):
            reportSym.setLabel('Enable Reportable property')       

        rwSym = component.getSymbolByID(rwSymID)
        rwSym.setVisible(symbol.getValue())        
        if(rwSym.getLabel()[:3] == 'ZCC'):
            rwSym.setLabel('Choose read write property')      

        dummy = component.getSymbolByID('DUMMY')
        dummy.setValue("END RECURSION") # used to reset the dependencyLock global variable



    except Exception as e:
        print("EXCEPTION at callback for Attributes tickbox (customClusterAttributesVis) ", e)

def customClusterBoundary(symbol, event):
    
    try:
        # THE name of the symbol that can call this function is :  
        #       -> 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_PROP_BOUNDARY_"
        #       -> eg: ZCC0_CUSTOM_CLUSTER_SERVER_ATTRIBUTES_PROP_BOUNDARY_
        
        iValue = symbol.getID().rsplit('_',1)[-1] # To get the trailing number of the command

        minSymID = '_'.join( symbol.getID().split('_')[:7] + ['MIN_',]) + str(iValue) # Get min boundary symbol
        maxSymID = '_'.join( symbol.getID().split('_')[:7] + ['MAX_',]) + str(iValue)

        
        component = symbol.getComponent()


        minSym = component.getSymbolByID(minSymID)
        minSym.setVisible(symbol.getValue()) 

        if(minSym.getLabel()[:3] == 'ZCC'):
            minSym.setLabel('Select Minimum')
        
        maxSym = component.getSymbolByID(maxSymID)
        maxSym.setVisible(symbol.getValue())  
        

        if(maxSym.getLabel()[:3] == 'ZCC'):
            maxSym.setLabel('Select Maximum')

    except Exception as e:
        print("EXCEPTION at Boundary callback function ",e)


def customClusterCommandsNoCallback(symbol, event): #This function is triggered when command count is changed

    # THE name of the symbol that can call this function is :  
    #       -> 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_COMMANDS_NO"
    #       -> eg: ZCC0_CUSTOM_CLUSTER_SERVER_COMMANDS_NO

    # We take the equivalent DISPLAY symbol to modify 

    # We have to process symbols of this format
    #    'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_COMMANDS_DISPLAY_"  + str(i)
    #    'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_COMMANDS_DISPLAY_"  + str(i)

    global dependencyLock
        
    if(dependencyLock):
        
        return
    dependencyLock = 1

    try:
        displaySymID = '_'.join( symbol.getID().split('_')[:5] + ['DISPLAY_',] )

        device = event['id'].split('_')[3]

        # Returns symbol ID of format ZCCi_CUSTOM_CLUSTER_CLIENT/SERVER_COMMANDS_DISPLAY_

        iterTill = symbol.getValue() # This gets the current value of the command count

        component = symbol.getComponent() # We use this to get the component to access DISPLAY vars
        
        for commandIndex in range(MAX_COMMAND_SIZE): # We have as many display symbols as there are commands
            displaySym = component.getSymbolByID(displaySymID + str(commandIndex))
           
            if(displaySym.getLabel()[:3]=='ZCC'):
                hexN = "{0:#0{1}x}".format(commandIndex,4).upper() #We format the looping variable in hex to set the ID for the command
                AttN = " CUSTOM "+ device + " COMMAND"
                label = hexN + AttN          
                displaySym.setLabel(str(label))
                # We initialize name and ID for the command
                nameSymID = '_'.join( symbol.getID().split('_')[:5] + ['NAME_',] )
                idSymID = '_'.join( symbol.getID().split('_')[:5] + ['ID_',] )
                nameSym = component.getSymbolByID(nameSymID + str(commandIndex))
                nameSym.setValue("custom"+device.capitalize()+"Command"+str(commandIndex))
                idSym = component.getSymbolByID(idSymID + str(commandIndex))
                idSym.setValue(commandIndex)

            if(commandIndex < iterTill): #  comparison to check if Label has been set already, as setLabel costs performance
                # To put in setdependency                
                displaySym.setVisible(True)
                # We make display symbol visible if its within range of the command count symbol inputted
                # We now check if the display symbol that has to be visible now has its label set
                # The reason we do this instead of having it set statically is because of huge performance drops in
                # instantiating the component 
            else:                
                displaySym.setVisible(False)

        dummy = component.getSymbolByID('DUMMY')
        dummy.setValue("END RECURSION") # used to reset the dependencyLock global variable

    except Exception as e:
        print("EXCEPTION at callback for customClusterCommandsNoCallback ", e)

def customClusterAttributesNoCallback(symbol, event): #This function is triggered when Attributes count is changed

    # THE name of the symbol that can call this function is :  
    #       -> 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_NO"
    #       -> eg: ZCC0_CUSTOM_CLUSTER_SERVER_ATTRIBUTES_NO
    global dependencyLock    
    if(dependencyLock):
        
        return
    dependencyLock = 1
    # We take the equivalent DISPLAY symbol to modify 
    displaySymID = '_'.join( symbol.getID().split('_')[:5] + ['DISPLAY_',] )
    # Returns symbol ID of format ZCCi_CUSTOM_CLUSTER_CLIENT/SERVER_ATTRIBUTES_DISPLAY_

    iterTill = symbol.getValue() # This gets the current value of the Attributes count
    device = event['id'].split('_')[3]
    component = symbol.getComponent() # We use this to get the component to access DISPLAY vars
    
    try:
        for attributeIndex in range(MAX_ATTRIBUTE_SIZE): # We have as many display symbols as there are Attributes
            displaySym = component.getSymbolByID(displaySymID + str(attributeIndex))
            
            if(displaySym.getLabel()[:3]=='ZCC'):
                hexN = "{0:#0{1}x}".format(attributeIndex,4).upper() #We format the looping variable in hex to set the ID for the Attribute
                AttN = " CUSTOM "+device+" ATTRIBUTE "
                label = hexN + AttN          

                displaySym.setLabel(str(label))
                # We initialize name and ID for the command
                nameSymID = '_'.join( symbol.getID().split('_')[:5] + ['NAME_',] )
                idSymID = '_'.join( symbol.getID().split('_')[:5] + ['ID_',] )
                nameSym = component.getSymbolByID(nameSymID + str(attributeIndex))
                nameSym.setValue("custom"+device.capitalize()+"Attribute"+str(attributeIndex))
                idSym = component.getSymbolByID(idSymID + str(attributeIndex))
                idSym.setValue(attributeIndex)

            if(attributeIndex < iterTill): #  comparison to check if Label has been set already, as setLabel costs performance
                # To put in setdependency
                                    
                displaySym.setVisible(True)
                # We make display symbol visible if its within range of the Attributes count symbol inputted
                # We now check if the display symbol that has to be visible now has its label set
                # The reason we do this instead of having it set statically is because of huge performance drops in
                # instantiating the component 
            else:

                displaySym.setVisible(False)

        # We have to process symbols of this format
        #    'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_DISPLAY_"  + str(attributeIndex)
        #    'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_DISPLAY_"  + str(attributeIndex)
        dummy = component.getSymbolByID('DUMMY')
        dummy.setValue("END RECURSION") # used to reset the dependencyLock global variable

    except Exception as e:
        print("EXCEPTION at callback for customClusterAttributesNoCallback ", e)


def customClusterClientServerCheck(symbol, event):

    #The client menu should only be visible when the Enable button is True, and the combo symbol is client

    #Symbol ID that calls this function
    # 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CS
    # 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_ENABLE

    #Symbol ID of this function
    # 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_MENU

    symName = symbol.getID().split('_')[-2]

    component = symbol.getComponent()
    enableSymID = '_'.join( symbol.getID().split('_')[:-2] + ["ENABLE",] )
    csSymID = '_'.join( symbol.getID().split('_')[:-2] + ["CS",] )
    clientSymID = '_'.join( symbol.getID().split('_')[:-2] + ["CLIENT_MENU",] )
    serverSymID = '_'.join( symbol.getID().split('_')[:-2] + ["SERVER_MENU",] )

    enableSym = component.getSymbolByID(enableSymID)
    csSym = component.getSymbolByID(csSymID)
    clientSym = component.getSymbolByID(clientSymID)
    serverSym = component.getSymbolByID(serverSymID)
    

    if( csSym.getValue() == "CLIENT" and enableSym.getValue() == True):
        clientSym.setVisible(True)
    else:
        clientSym.setVisible(False)

    if( csSym.getValue() == "SERVER" and enableSym.getValue() == True):
        serverSym.setVisible(True)
    else:
        serverSym.setVisible(False)

def customClusterFilegen(symbol, event):
    # We check if the configuration option was Server
    val = event['value']

    number = int(symbol.getID().split('_')[0][3:])
    
    component = symbol.getComponent()

    

    ClusterNo = component.getSymbolByID('CUSTOM_CLUSTER_NO').getValue()

    boolIs = (number < ClusterNo)
    
    if(val == 'SERVER'):
        symbol.setEnabled(True and boolIs)
        
    else:
        symbol.setEnabled(False)

def customClusterLabel(symbol, event): #Custom cluster dependency callback for changing ID,Name for cluster

    try:
        
        global dependencyLock

        if(dependencyLock):        
            return
        
        dependencyLock = 1
        # START OF FUNCTION DEFINITION

        choice = symbol.getID().rsplit('_',1)[-1] #Choice contains either name or id.

        component = symbol.getComponent()

        number = int(symbol.getID().split('_')[0][3:])

        clusterSym = component.getSymbolByID('ZCC'+str(number)+'_CUSTOM_CLUSTER_ENABLE')

        headerSym = component.getSymbolByID('ZCC'+str(number)+'_'+'CUSTOM_CLUSTER_GENERATION_SERVER_HEADER')
        sourceSym = component.getSymbolByID('ZCC'+str(number)+'_''CUSTOM_CLUSTER_GENERATION_SOURCE')
        zclheaderSym = component.getSymbolByID('ZCC'+str(number)+'_''CUSTOM_CLUSTER_GENERATION_HEADER')

        global prefix     

        if(choice == 'NAME'):
            clusterLabel = clusterSym.getLabel().split(' ',1)
            clusterLabel[1] = symbol.getValue().replace(' ','')
            name = ''.join([i.capitalize() for i in clusterLabel[1].split(' ')])
            clusterSym.setLabel(' '.join(clusterLabel))
            # Symbols that are event['symbol'] and symbol in this function at a time
            #'ZCC'+str(cli)+'_'+'CUSTOM_CLUSTER_GENERATION_SERVER_HEADER'
            #'ZCC'+str(cli)+'_'+'CUSTOM_CLUSTER_GENERATION_SOURCE'
            #'ZCC'+str(cli)+'_'+'CUSTOM_CLUSTER_GENERATION_HEADER'
            
            sourceSym.setOutputName(prefix + name +"Cluster.c")
            headerSym.setOutputName(prefix + name +"Cluster.h")
            zclheaderSym.setOutputName("zcl" + name + "Cluster.h" )

            clusterSym.setLabel(' '.join(clusterLabel))
        
        elif(choice == 'ID'):
            clusterLabel = clusterSym.getLabel().split(' ',1)
            clusterLabel[0] = "{0:#0{1}x}".format(symbol.getValue(),4).upper()
            clusterSym.setLabel(' '.join(clusterLabel))
            

        # END OF FUNCTION DEFINITION

        dummy = component.getSymbolByID('DUMMY')
        dummy.setValue("END RECURSION") # used to reset the dependencyLock global variable
    except Exception as e:
        print("EXCEPTION AT CHANGING CLUSTER LABEL ",e)

def customClusterReportableInterval(symbol, event):
    #The reportable menu should only be visible any attribute has ticked reportable atleast once

    #Symbol ID that calls this function
    #'ZCC'+str(cli)+"_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_PROP_REPORTABLE_"""+str(i)
    #'ZCC'+str(cli)+"_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_PROP_REPORTABLE_"""+str(i)

    #Symbol ID of this function
    #'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_REPORT_MIN"
    #'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_REPORT_MAX"

    try:
        global dependencyLock

        if(dependencyLock):        
            return
        #We don't set dependency lock here since this section won't generate
        
        number = int(symbol.getID().split('_')[0][3:]) #The cluster number
        minID = 'ZCC'+str(number) + "_" + "CUSTOM_CLUSTER_REPORT_MIN"
        maxID = 'ZCC'+str(number) + "_" + "CUSTOM_CLUSTER_REPORT_MAX"

        component = symbol.getComponent()
        min = component.getSymbolByID(minID)
        max = component.getSymbolByID(maxID)

        min.setVisible(True)
        max.setVisible(True)

    except Exception as e:
        print("EXCEPTION AT ENABLING REPORTING RANGE ",e)


# Fix for recursion in set dependency
def dummyFunc(symbol, event):
    
    global dependencyLock
    dependencyLock = 0
    
    #used for recursion problem




############################################################################################################
##################################### Configuration Item Definitions #######################################
############################################################################################################

global dummy #used for recursion problem in set dependency functions.
dummy = drvZigbeeComponent.createStringSymbol("DUMMY", None)
dummy.setDependencies(dummyFunc, ["DUMMY",])
dummy.setVisible(False)

#FILE_PREFIX[devID]
deviceTypeFilePrefix = drvZigbeeComponent.createStringSymbol("DEVICE_TYPE_FILE_PREFIX", None)
deviceTypeFilePrefix.setValue(FILE_PREFIX[devID])
deviceTypeFilePrefix.setVisible(False)

#FILE_PATH[devID]
deviceTypeFilePath = drvZigbeeComponent.createStringSymbol("DEVICE_TYPE_FILE_PATH", None)
deviceTypeFilePath.setValue(FILE_PATH[devID])
deviceTypeFilePath.setVisible(False)

customClusterNo = drvZigbeeComponent.createIntegerSymbol("CUSTOM_CLUSTER_NO",clusterConfigMenu)
customClusterNo.setLabel("Custom Cluster Count")
customClusterNo.setDefaultValue(0)
customClusterNo.setMin(0)
customClusterNo.setMax(MAX_CLUSTER_SIZE)
customClusterNo.setDependencies(changeNoOfCustomCluster, ["CUSTOM_CLUSTER_NO",])
customClusterNo.setVisible(CUSTOM_CLUSTER_ENABLED)

for cli in range(MAX_CLUSTER_SIZE):

    global customCluster
    customCluster = drvZigbeeComponent.createBooleanSymbol('ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_ENABLE", clusterConfigMenu)
    CUSTOMCLUSTERNUMBER = 0xfc00 + cli
    num = "{0:#0{1}x}".format(CUSTOMCLUSTERNUMBER,6).upper()
    customCluster.setLabel(str(num) + " CUSTOM Cluster")
    customCluster.setDefaultValue(False)
    customCluster.setVisible(False)
    customCluster.setDescription("CUSTOM CLUSTER- check the box to enable")
    customCluster.setReadOnly(False)

    customClusterID = drvZigbeeComponent.createHexSymbol('ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_ID",  customCluster)
    customClusterID.setLabel("Cluster ID")
    customClusterID.setVisible(customCluster.getValue())
    customClusterID.setDefaultValue(0xfc00 + cli)
    customClusterID.setMin(0x0000)
    customClusterID.setMax(0xffff)
    customClusterID.setDependencies(customClusterLabel,['ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_ID",])

    customClusterName = drvZigbeeComponent.createStringSymbol('ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_NAME",  customCluster)
    customClusterName.setLabel("Cluster Name")
    customClusterName.setVisible(customCluster.getValue())
    customClusterName.setDefaultValue('customCluster'+str(cli))
    customClusterName.setDependencies(customClusterLabel,['ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_NAME",])

    global customClusterCS
    customClusterCS = drvZigbeeComponent.createComboSymbol('ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CS",  customCluster, ["CLIENT","SERVER"])
    customClusterCS.setLabel("Supported Implementation")
    customClusterCS.setDefaultValue("CLIENT")
    customClusterCS.setVisible(customCluster.getValue())
    customClusterCS.setDescription("CUSTOM Cluster Supported Implementation- Select the option")
    customClusterCS.setDependencies(customClusterCSCheck,['ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_ENABLE"])

    #TODO
    customClusterReportInterval = drvZigbeeComponent.createIntegerSymbol('ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_REPORT_MIN", customCluster)
    customClusterReportInterval.setLabel("Report interval minimum")
    customClusterReportInterval.setDefaultValue(0)
    customClusterReportInterval.setMin(0)   
    customClusterReportInterval.setVisible(False)

    customClusterReportInterval = drvZigbeeComponent.createIntegerSymbol('ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_REPORT_MAX", customCluster)
    customClusterReportInterval.setLabel("Report interval maximum")
    customClusterReportInterval.setDefaultValue(0)
    customClusterReportInterval.setMin(0)
    customClusterReportInterval.setVisible(False)

    customClusterClientMenu = drvZigbeeComponent.createMenuSymbol('ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_MENU", customCluster)
    customClusterClientMenu.setLabel("Client")    
    customClusterClientMenu.setDescription("CUSTOM CLUSTER CLIENT")    

    customClusterServerMenu = drvZigbeeComponent.createMenuSymbol('ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_MENU", customCluster)
    customClusterServerMenu.setLabel("Server")    
    customClusterServerMenu.setDescription("CUSTOM CLUSTER SERVER")    

    #MENU FOR ATTRIBUTES
    #===================

    customClusterClientAttributes = drvZigbeeComponent.createMenuSymbol('ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT__ATTRIBUTES_MENU", customClusterClientMenu)
    customClusterClientAttributes.setLabel("Attributes")    
    customClusterClientAttributes.setDescription("CUSTOM CLUSTER CLIENT ATTRIBUTES")    

    customClusterServerAttributes = drvZigbeeComponent.createMenuSymbol('ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER__ATTRIBUTES_MENU", customClusterServerMenu)
    customClusterServerAttributes.setLabel("Attributes")
    customClusterServerAttributes.setDescription("CUSTOM CLUSTER SERVER ATTRIBUTES")

    #ATTRIBUTES COUNT
    #================

    global customClusterServerAttributesNo 
    customClusterServerAttributesNo = drvZigbeeComponent.createIntegerSymbol('ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_NO", customClusterServerAttributes)
    customClusterServerAttributesNo.setMin(0)
    customClusterServerAttributesNo.setMax(MAX_ATTRIBUTE_SIZE)
    customClusterServerAttributesNo.setDefaultValue(0)
    customClusterServerAttributesNo.setLabel("Attributes Count")
    customClusterServerAttributesNo.setDescription("Use this to set number of attributes for the custom cluster server")
    customClusterServerAttributesNo.setDependencies(customClusterAttributesNoCallback, ['ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_NO"])


    global customClusterClientAttributesNo 
    customClusterClientAttributesNo = drvZigbeeComponent.createIntegerSymbol('ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_NO", customClusterClientAttributes)
    customClusterClientAttributesNo.setMin(0)
    customClusterClientAttributesNo.setMax(MAX_ATTRIBUTE_SIZE)
    customClusterClientAttributesNo.setDefaultValue(0)
    customClusterClientAttributesNo.setLabel("Attributes Count")
    customClusterClientAttributesNo.setDescription("Use this to set number of attributes for the custom cluster client")
    customClusterClientAttributesNo.setDependencies(customClusterAttributesNoCallback, ['ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_NO"])



    
    #MENU FOR COMMANDS
    #=================

    customClusterClientCommands = drvZigbeeComponent.createMenuSymbol('ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT__COMMANDS_MENU", customClusterClientMenu)
    customClusterClientCommands.setLabel("Commands")
    customClusterClientCommands.setDescription("CUSTOM CLUSTER CLIENT COMMANDS")

    customClusterServerCommands = drvZigbeeComponent.createMenuSymbol('ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER__COMMANDS_MENU", customClusterServerMenu)
    customClusterServerCommands.setLabel("Commands")
    customClusterServerCommands.setDescription("CUSTOM CLUSTER SERVER COMMANDS")

    #COMMANDS COUNT
    #================

    global customClusterServerCommandsNo 
    customClusterServerCommandsNo = drvZigbeeComponent.createIntegerSymbol('ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_COMMANDS_NO", customClusterServerCommands)
    customClusterServerCommandsNo.setMin(0)
    customClusterServerCommandsNo.setMax(MAX_COMMAND_SIZE)
    customClusterServerCommandsNo.setDefaultValue(0)
    customClusterServerCommandsNo.setLabel("Commands Count")
    customClusterServerCommandsNo.setDescription("Use this to set number of Commands for the custom cluster server")
    customClusterServerCommandsNo.setDependencies(customClusterCommandsNoCallback, ['ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_COMMANDS_NO"])
    


    global customClusterClientCommandsNo 
    customClusterClientCommandsNo = drvZigbeeComponent.createIntegerSymbol('ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_COMMANDS_NO", customClusterClientCommands)
    customClusterClientCommandsNo.setMin(0)
    customClusterClientCommandsNo.setMax(MAX_COMMAND_SIZE)
    customClusterClientCommandsNo.setDefaultValue(0)
    customClusterClientCommandsNo.setLabel("Commands Count")
    customClusterClientCommandsNo.setDescription("Use this to set number of Commands for the custom cluster client")
    customClusterClientCommandsNo.setDependencies(customClusterCommandsNoCallback, ['ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_COMMANDS_NO"])


    ##START OF IMPLEMENTING CUSTOM ATTRIBUTES AND COMMANDS

    ##########################################################################################################################
    ############################################### ATTRIBUTES CLIENT ########################################################
    ##########################################################################################################################

    # setDependency contains various initializing parameters like
    # setLabel
    # setDefaultValue
    # setMin
    # setMax
    # To optimize speed of MCC component loading time
    
    try:
        for attributeIndex in range(MAX_ATTRIBUTE_SIZE):

            # Attribute CLIENT
            # ===============
    
            # The commented parts of setLabel and setDependencies are interntional and act as reference
            # on the kind of values they would have when they become visible through user interaction
            # via setdependency callback functions

            name = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_DISPLAY_"  + str(attributeIndex)        
            customClusterClientAttributesSym = drvZigbeeComponent.createBooleanSymbol(name, customClusterClientAttributes)              
            customClusterClientAttributesSym.setVisible(False)
            customClusterClientAttributesSym.setDependencies(customClusterAttributesVis, [name,])
            # Setdependency contains the following initialization
            # hexN = "{0:#0{1}x}".format(attributeIndex,6).upper()
            # AttN = " CUSTOM_ATTRIBUTE_"+str(attributeIndex)
            # label = hexN+AttN

            name_ID = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_"
            nameID = name_ID + "ID_" +str(attributeIndex)
            customClusterClientAttributesSymid = drvZigbeeComponent.createHexSymbol(nameID, customClusterClientAttributesSym)    
            customClusterClientAttributesSymid.setVisible(False)
            customClusterClientAttributesSymid.setDependencies(customClusterChangeLabel, [nameID,])


            nameSymbolID = name_ID + "NAME_" +str(attributeIndex)
            customClusterClientAttributesSymid = drvZigbeeComponent.createStringSymbol(nameSymbolID, customClusterClientAttributesSym)    
            customClusterClientAttributesSymid.setVisible(False)            
            customClusterClientAttributesSymid.setDependencies(customClusterChangeLabel, [nameSymbolID,])

            # DATA TYPE START
            classN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_CLASSTYPE_" + str(attributeIndex) 
            customClusterClientAttributesSymType = drvZigbeeComponent.createComboSymbol(classN, customClusterClientAttributesSym, list(TYPES.keys()))  
            customClusterClientAttributesSymType.setVisible(False)
            customClusterClientAttributesSymType.setDependencies(customClusterChangeClassType, [classN, ])

            typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_TYPE_GENERAL_" + str(attributeIndex) 
            customClusterClientAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterClientAttributesSym, TYPES['General Data'])  
            customClusterClientAttributesSymDType.setVisible(False)

            typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_TYPE_BOOLEAN_" + str(attributeIndex) 
            customClusterClientAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterClientAttributesSym, TYPES['Boolean'])  
            customClusterClientAttributesSymDType.setVisible(False)

            typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_TYPE_BITMAP_" + str(attributeIndex) 
            customClusterClientAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterClientAttributesSym, TYPES['Bitmap'])  
            customClusterClientAttributesSymDType.setVisible(False)

            typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_TYPE_UNSIGNED_" + str(attributeIndex) 
            customClusterClientAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterClientAttributesSym, TYPES['Unsigned Integer'])  
            customClusterClientAttributesSymDType.setVisible(False)

            typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_TYPE_SIGNED_" + str(attributeIndex) 
            customClusterClientAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterClientAttributesSym, TYPES['Signed Integer'])  
            customClusterClientAttributesSymDType.setVisible(False)

            typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_TYPE_ENUM_" + str(attributeIndex) 
            customClusterClientAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterClientAttributesSym, TYPES['Enumeration'])  
            customClusterClientAttributesSymDType.setVisible(False)

            typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_TYPE_STRING_" + str(attributeIndex) 
            customClusterClientAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterClientAttributesSym, TYPES['String'])  
            customClusterClientAttributesSymDType.setVisible(False)

            typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_TYPE_ARRAY_" + str(attributeIndex) 
            customClusterClientAttributesSymDType = drvZigbeeComponent.createIntegerSymbol(typeN, customClusterClientAttributesSym)  
            customClusterClientAttributesSymDType.setVisible(False)

            # DATA TYPE END
                    
            # PROPERTIES, BOUNDARY AND REPORTABLE            
            propN = 'ZCC'+str(cli)+"_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_PROP_RW_"""+str(attributeIndex)
            customClusterClientAttributesSymProp = drvZigbeeComponent.createComboSymbol(propN, customClusterClientAttributesSym, ['READ ONLY', 'READ WRITE'])  
            customClusterClientAttributesSymProp.setVisible(False)

            propN = 'ZCC'+str(cli)+"_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_PROP_REPORTABLE_"""+str(attributeIndex)
            customClusterClientAttributesSymProp = drvZigbeeComponent.createBooleanSymbol(propN, customClusterClientAttributesSym)  
            customClusterClientAttributesSymProp.setVisible(False)
            customClusterClientAttributesSymProp.setDependencies(customClusterReportableInterval, [propN,])

            propN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_PROP_BOUNDARY_" + str(attributeIndex)
            
            customClusterClientAttributesSymPropB = drvZigbeeComponent.createBooleanSymbol(propN, customClusterClientAttributesSym)  
            customClusterClientAttributesSymPropB.setVisible(False)            
            customClusterClientAttributesSymPropB.setDependencies(customClusterBoundary, [propN,])

            propN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_PROP_BOUNDARY_MIN_" + str(attributeIndex)
            
            customClusterClientAttributesSymProp = drvZigbeeComponent.createHexSymbol(propN, customClusterClientAttributesSymPropB)  
            customClusterClientAttributesSymProp.setVisible(False)

            propN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_ATTRIBUTES_PROP_BOUNDARY_MAX_" + str(attributeIndex)
            
            customClusterClientAttributesSymProp = drvZigbeeComponent.createHexSymbol(propN, customClusterClientAttributesSymPropB)  
            customClusterClientAttributesSymProp.setVisible(False)
            
    except Exception as e:
        print("THE EXCEPTION ATTRIBUTES-CLIENT DISPLAY IS ",e)

    
       
##############################################################################################################################
################################################### ATTRIBUTES SERVER ########################################################
##############################################################################################################################   
    try:
        for attributeIndex in range(MAX_ATTRIBUTE_SIZE):

            # ATTRIBUTES SERVER
            # ===============
        
            # The commented parts of setLabel and setDependencies are intentional and act as reference
            # on the kind of values they would have when they become visible through user interaction
            # via setdependency callback functions

            name = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_DISPLAY_"  + str(attributeIndex)        
            customClusterServerAttributesSym = drvZigbeeComponent.createBooleanSymbol(name, customClusterServerAttributes)    
            # To put in setdependency
            # hexN = "{0:#0{1}x}".format(attributeIndex,6).upper()
            # AttN = " CUSTOM_ATTRIBUTE_"+str(attributeIndex)
            # label = hexN+AttN
            # customClusterServerCommandsSym.setLabel(label)
            customClusterServerAttributesSym.setVisible(False)
            customClusterServerAttributesSym.setDependencies(customClusterAttributesVis, [name,])

            name_ID = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_"
            nameID = name_ID + "ID_" +str(attributeIndex)
            customClusterServerAttributesSymid = drvZigbeeComponent.createHexSymbol(nameID, customClusterServerAttributesSym)    
            customClusterServerAttributesSymid.setVisible(False)
            customClusterServerAttributesSymid.setDependencies(customClusterChangeLabel, [nameID,])

            nameSymbolID = name_ID + "NAME_" +str(attributeIndex)
            customClusterServerAttributesSymid = drvZigbeeComponent.createStringSymbol(nameSymbolID, customClusterServerAttributesSym)    
            customClusterServerAttributesSymid.setVisible(False)
            customClusterServerAttributesSymid.setDependencies(customClusterChangeLabel, [nameSymbolID,])


            # DATA TYPE START
            classN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_CLASSTYPE_" + str(attributeIndex)
            customClusterServerAttributesSymType = drvZigbeeComponent.createComboSymbol(classN, customClusterServerAttributesSym, list(TYPES.keys()))  
            customClusterServerAttributesSymType.setDependencies(customClusterChangeClassType, [classN, ])
            customClusterServerAttributesSymType.setVisible(False)

            typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_TYPE_GENERAL_" + str(attributeIndex)
            customClusterServerAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterServerAttributesSym, TYPES['General Data'])  
            customClusterServerAttributesSymDType.setVisible(False)


            typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_TYPE_BOOLEAN_" + str(attributeIndex)
            customClusterServerAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterServerAttributesSym, TYPES['Boolean'])  
            customClusterServerAttributesSymDType.setVisible(False)

            typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_TYPE_BITMAP_" + str(attributeIndex)
            customClusterServerAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterServerAttributesSym, TYPES['Bitmap'])  
            customClusterServerAttributesSymDType.setVisible(False)

            typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_TYPE_UNSIGNED_" + str(attributeIndex)
            customClusterServerAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterServerAttributesSym, TYPES['Unsigned Integer'])  
            customClusterServerAttributesSymDType.setVisible(False)

            typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_TYPE_SIGNED_" + str(attributeIndex)
            customClusterServerAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterServerAttributesSym, TYPES['Signed Integer'])  
            customClusterServerAttributesSymDType.setVisible(False)

            typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_TYPE_ENUM_" + str(attributeIndex)
            customClusterServerAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterServerAttributesSym, TYPES['Enumeration'])  
            customClusterServerAttributesSymDType.setVisible(False)
            

            typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_TYPE_STRING_" + str(attributeIndex)
            customClusterServerAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterServerAttributesSym, TYPES['String'])  
            customClusterServerAttributesSymDType.setVisible(False)

            typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_TYPE_ARRAY_" + str(attributeIndex)
            customClusterServerAttributesSymDType = drvZigbeeComponent.createIntegerSymbol(typeN, customClusterServerAttributesSym)  
            customClusterServerAttributesSymDType.setVisible(False)
            
            # DATA TYPE END

            propN = 'ZCC'+str(cli)+"_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_PROP_RW_"""+str(attributeIndex)
            customClusterServerAttributesSymProp = drvZigbeeComponent.createComboSymbol(propN, customClusterServerAttributesSym, ['READ ONLY', 'READ WRITE'])  
            customClusterServerAttributesSymProp.setVisible(False)

            # PROPERTIES, BOUNDARY AND REPORTABLE            
            propN = 'ZCC'+str(cli)+"_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_PROP_REPORTABLE_"""+str(attributeIndex)
            customClusterServerAttributesSymProp = drvZigbeeComponent.createBooleanSymbol(propN, customClusterServerAttributesSym)  
            customClusterServerAttributesSymProp.setVisible(False)
            customClusterServerAttributesSymProp.setDependencies(customClusterReportableInterval, [propN,])

            propN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_PROP_BOUNDARY_" + str(attributeIndex)
            customClusterServerAttributesSymPropB = drvZigbeeComponent.createBooleanSymbol(propN, customClusterServerAttributesSym)  
            customClusterServerAttributesSymPropB.setVisible(False)
            customClusterServerAttributesSymPropB.setDependencies(customClusterBoundary, [propN,])

            propN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_PROP_BOUNDARY_MIN_" + str(attributeIndex)
            customClusterServerAttributesSymProp = drvZigbeeComponent.createHexSymbol(propN, customClusterServerAttributesSymPropB)  
            customClusterServerAttributesSymProp.setVisible(False)


            propN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_ATTRIBUTES_PROP_BOUNDARY_MAX_" + str(attributeIndex)
            customClusterServerAttributesSymProp = drvZigbeeComponent.createHexSymbol(propN, customClusterServerAttributesSymPropB)  
            customClusterServerAttributesSymProp.setVisible(False)

    except Exception as e:
        print("THE EXCEPTION ATTRIBUTES-SERVER DISPLAY IS ",e)

##################################################################################################################
################################################### COMMANDS CLIENT/SERVER
##################################################################################################################

    
    try:
        for commandIndex in range(MAX_COMMAND_SIZE):

            # COMMANDS CLIENT
            # ===============

            # The commented parts of setLabel and setDependencies are interntional and act as reference
            # on the kind of values they would have when they become visible through user interaction
            # via setdependency callback functions

            name = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_COMMANDS_DISPLAY_"  + str(commandIndex)        
            customClusterClientCommandsSym = drvZigbeeComponent.createBooleanSymbol(name, customClusterClientCommands)    
            # To put in setdependency
            # hexN = "{0:#0{1}x}".format(commandIndex,6).upper()
            # AttN = " CUSTOM_ATTRIBUTE_"+str(commandIndex)
            # label = hexN+AttN
            customClusterClientCommandsSym.setVisible(False)
            customClusterClientCommandsSym.setDependencies(customClusterCommandVis, [name,])

            name_ID = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_COMMANDS_"
            nameID = name_ID + "ID_" +str(commandIndex)
            customClusterClientCommandsSymid = drvZigbeeComponent.createHexSymbol(nameID, customClusterClientCommandsSym)    
            customClusterClientCommandsSymid.setVisible(False)
            customClusterClientCommandsSymid.setDependencies(customClusterChangeLabel, [nameID,])


            nameSymbolID = name_ID + "NAME_" +str(commandIndex)
            customClusterClientCommandsSymid = drvZigbeeComponent.createStringSymbol(nameSymbolID, customClusterClientCommandsSym)    
            customClusterClientCommandsSymid.setVisible(False)
            customClusterClientCommandsSymid.setDependencies(customClusterChangeLabel, [nameSymbolID,])
            
            # nameSymbolID = name_ID + "CTS_" +str(commandIndex) #Commented in case of reimplementing devices that can act both as client and server
            # customClusterClientCommandsSymid = drvZigbeeComponent.createComboSymbol(nameSymbolID, customClusterClientCommandsSym, ['CLIENT TO SERVER', 'SERVER TO CLIENT'])                
            # customClusterClientCommandsSymid.setVisible(False)            
            
            nameSymbolID = name_ID + "RESPONSE_" +str(commandIndex)
            customClusterClientCommandsSymid = drvZigbeeComponent.createComboSymbol(nameSymbolID, customClusterClientCommandsSym, ['THERE IS RELEVANT RESPONSE', 'THERE IS NO RELEVANT RESPONSE', 'RESPONSE CONTROLLED BY PAYLOAD'])            
            customClusterClientCommandsSymid.setVisible(False)           

            nameSymbolID = name_ID + "ACK_" +str(commandIndex)
            customClusterClientCommandsSymid = drvZigbeeComponent.createComboSymbol(nameSymbolID, customClusterClientCommandsSym, ['NO ACK', 'ACK'])
            customClusterClientCommandsSymid.setVisible(False)
            
            nameSymbolID = name_ID + "PARAM_NO_" +str(commandIndex)
            customClusterClientCommandsSymid = drvZigbeeComponent.createIntegerSymbol(nameSymbolID, customClusterClientCommandsSym)    
            customClusterClientCommandsSymid.setVisible(False)
            customClusterClientCommandsSymid.setDependencies(customClusterParam, [nameSymbolID,])


            for paramIndex in range(MAX_COMMAND_PARAMS):
                # DATA TYPE START
                paramN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_COMMANDS_PARAMNAME_" + str(commandIndex) + '_' + str(paramIndex)
                customClusterClientCommandsSymP = drvZigbeeComponent.createStringSymbol(paramN, customClusterClientCommandsSym)  
                customClusterClientCommandsSymP.setVisible(False)
                
                classN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_COMMANDS_CLASSTYPE_" + str(commandIndex) + '_' + str(paramIndex)
                customClusterClientAttributesSymType = drvZigbeeComponent.createComboSymbol(classN, customClusterClientCommandsSymP, list(TYPES.keys()))  
                customClusterClientAttributesSymType.setDependencies(customClusterChangeClassType, [classN, ])
                customClusterClientAttributesSymType.setVisible(False)

                typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_COMMANDS_TYPE_GENERAL_" + str(commandIndex) + '_' + str(paramIndex)
                customClusterClientAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterClientCommandsSymP, TYPES['General Data'])  
                customClusterClientAttributesSymDType.setVisible(False)

                typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_COMMANDS_TYPE_BOOLEAN_" + str(commandIndex) + '_' + str(paramIndex)
                customClusterClientAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterClientCommandsSymP, TYPES['Boolean'])  
                customClusterClientAttributesSymDType.setVisible(False)

                typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_COMMANDS_TYPE_BITMAP_" + str(commandIndex) + '_' + str(paramIndex)
                customClusterClientAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterClientCommandsSymP, TYPES['Bitmap'])  
                customClusterClientAttributesSymDType.setVisible(False)

                typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_COMMANDS_TYPE_UNSIGNED_" + str(commandIndex) + '_' + str(paramIndex)
                customClusterClientAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterClientCommandsSymP, TYPES['Unsigned Integer'])  
                customClusterClientAttributesSymDType.setVisible(False)

                typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_COMMANDS_TYPE_SIGNED_" + str(commandIndex) + '_' + str(paramIndex)
                customClusterClientAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterClientCommandsSymP, TYPES['Signed Integer'])  
                customClusterClientAttributesSymDType.setVisible(False)

                typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_COMMANDS_TYPE_ENUM_" + str(commandIndex) + '_' + str(paramIndex)
                customClusterClientAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterClientCommandsSymP, TYPES['Enumeration'])  
                customClusterClientAttributesSymDType.setVisible(False)

                typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_COMMANDS_TYPE_STRING_" + str(commandIndex) + '_' + str(paramIndex)
                customClusterClientAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterClientCommandsSymP, TYPES['String'])  
                customClusterClientAttributesSymDType.setVisible(False)

                typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_CLIENT_COMMANDS_TYPE_ARRAY_" + str(commandIndex) + '_' + str(paramIndex)
                customClusterClientAttributesSymDType = drvZigbeeComponent.createIntegerSymbol(typeN, customClusterClientCommandsSymP)  
                customClusterClientAttributesSymDType.setVisible(False)

                # DATA TYPE END
                

    except Exception as e:
        print("EXCEPTION AT CREATING CLIENT COMMANDS SYMBOLS ",e)

    


##############################################################################################################################
###################################### COMMANDS SERVER #######################################################################
##############################################################################################################################
    try:
        for commandIndex in range(MAX_COMMAND_SIZE):

            # COMMANDS SERVER
            # ===============

            # The commented parts of setLabel and setDependencies are interntional and act as reference
            # on the kind of values they would have when they become visible through user interaction
            # via setdependency callback functions

            name = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_COMMANDS_DISPLAY_"  + str(commandIndex)        
            customClusterServerCommandsSym = drvZigbeeComponent.createBooleanSymbol(name, customClusterServerCommands)    
            # To put in setdependency
            # hexN = "{0:#0{1}x}".format(commandIndex,6).upper()
            # AttN = " CUSTOM_ATTRIBUTE_"+str(commandIndex)
            # label = hexN+AttN
            customClusterServerCommandsSym.setVisible(False)
            customClusterServerCommandsSym.setDependencies(customClusterCommandVis, [name,])

            name_ID = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_COMMANDS_"
            nameID = name_ID + "ID_" +str(commandIndex)
            customClusterServerCommandsSymid = drvZigbeeComponent.createHexSymbol(nameID, customClusterServerCommandsSym)    
            customClusterServerCommandsSymid.setVisible(False)
            customClusterServerCommandsSymid.setDependencies(customClusterChangeLabel, [nameID,])


            nameSymbolID = name_ID + "NAME_" +str(commandIndex)
            customClusterServerCommandsSymid = drvZigbeeComponent.createStringSymbol(nameSymbolID, customClusterServerCommandsSym)    
            customClusterServerCommandsSymid.setVisible(False)
            customClusterServerCommandsSymid.setDependencies(customClusterChangeLabel, [nameSymbolID,])

            # nameSymbolID = name_ID + "CTS_" +str(commandIndex)  #Commented in case of reimplementing devices that can act both as client and server
            # customClusterServerCommandsSymid = drvZigbeeComponent.createComboSymbol(nameSymbolID, customClusterServerCommandsSym, ['CLIENT TO SERVER', 'SERVER TO CLIENT'])                
            # customClusterServerCommandsSymid.setVisible(False)            
            
            nameSymbolID = name_ID + "RESPONSE_" +str(commandIndex)
            customClusterServerCommandsSymid = drvZigbeeComponent.createComboSymbol(nameSymbolID, customClusterServerCommandsSym, ['THERE IS RELEVANT RESPONSE', 'THERE IS NO RELEVANT RESPONSE', 'RESPONSE CONTROLLED BY PAYLOAD'])            
            customClusterServerCommandsSymid.setVisible(False)           

            nameSymbolID = name_ID + "ACK_" +str(commandIndex)
            customClusterServerCommandsSymid = drvZigbeeComponent.createComboSymbol(nameSymbolID, customClusterServerCommandsSym, ['NO ACK', 'ACK'])
            customClusterServerCommandsSymid.setVisible(False)
            
            nameSymbolID = name_ID + "PARAM_NO_" +str(commandIndex)
            customClusterServerCommandsSymid = drvZigbeeComponent.createIntegerSymbol(nameSymbolID, customClusterServerCommandsSym)    
            customClusterServerCommandsSymid.setVisible(False)
            customClusterServerCommandsSymid.setDependencies(customClusterParam, [nameSymbolID,])

            for paramIndex in range(MAX_COMMAND_PARAMS):
                
                paramN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_COMMANDS_PARAMNAME_" + str(commandIndex) + '_' + str(paramIndex)
                customClusterServerCommandsSymP = drvZigbeeComponent.createStringSymbol(paramN, customClusterServerCommandsSym)  
                customClusterServerCommandsSymP.setVisible(False)

                classN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_COMMANDS_CLASSTYPE_" + str(commandIndex) + '_' + str(paramIndex)
                customClusterServerCommandsSymType = drvZigbeeComponent.createComboSymbol(classN, customClusterServerCommandsSymP, list(TYPES.keys()))  
                customClusterServerCommandsSymType.setDependencies(customClusterChangeClassType, [classN, ])
                customClusterServerCommandsSymType.setVisible(False)

                typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_COMMANDS_TYPE_GENERAL_" + str(commandIndex) + '_' + str(paramIndex)
                customClusterServerCommandsSymType = drvZigbeeComponent.createComboSymbol(typeN, customClusterServerCommandsSymP, TYPES['General Data'])  
                customClusterServerCommandsSymType.setVisible(False)

                typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_COMMANDS_TYPE_BOOLEAN_" + str(commandIndex) + '_' + str(paramIndex)
                customClusterServerCommandsSymType = drvZigbeeComponent.createComboSymbol(typeN, customClusterServerCommandsSymP, TYPES['Boolean'])  
                customClusterServerCommandsSymType.setVisible(False)

                typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_COMMANDS_TYPE_BITMAP_" + str(commandIndex) + '_' + str(paramIndex)
                customClusterServerCommandsSymType = drvZigbeeComponent.createComboSymbol(typeN, customClusterServerCommandsSymP, TYPES['Bitmap'])  
                customClusterServerCommandsSymType.setVisible(False)

                typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_COMMANDS_TYPE_UNSIGNED_" + str(commandIndex) + '_' + str(paramIndex)
                customClusterServerCommandsSymType = drvZigbeeComponent.createComboSymbol(typeN, customClusterServerCommandsSymP, TYPES['Unsigned Integer'])  
                customClusterServerCommandsSymType.setVisible(False)

                typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_COMMANDS_TYPE_SIGNED_" + str(commandIndex) + '_' + str(paramIndex)
                customClusterServerCommandsSymType = drvZigbeeComponent.createComboSymbol(typeN, customClusterServerCommandsSymP, TYPES['Signed Integer'])  
                customClusterServerCommandsSymType.setVisible(False)

                typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_COMMANDS_TYPE_ENUM_" + str(commandIndex) + '_' + str(paramIndex)
                customClusterServerCommandsSymType = drvZigbeeComponent.createComboSymbol(typeN, customClusterServerCommandsSymP, TYPES['Enumeration'])  
                customClusterServerCommandsSymType.setVisible(False)

                typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_COMMANDS_TYPE_STRING_" + str(commandIndex) + '_' + str(paramIndex)
                customClusterServerAttributesSymDType = drvZigbeeComponent.createComboSymbol(typeN, customClusterServerCommandsSymP, TYPES['String'])  
                customClusterServerAttributesSymDType.setVisible(False)

                typeN = 'ZCC'+str(cli) + "_" + "CUSTOM_CLUSTER_SERVER_COMMANDS_TYPE_ARRAY_" + str(commandIndex) + '_' + str(paramIndex)
                customClusterServerAttributesSymDType = drvZigbeeComponent.createIntegerSymbol(typeN, customClusterServerCommandsSymP)
                customClusterServerAttributesSymDType.setVisible(False)

              
                # DATA TYPE END


    except Exception as e:
        print("EXCEPTION AT CREATING SERVER COMMANDS SYMBOLS ",e)


#############################################################################################################
################################      File Generation                 #######################################
#############################################################################################################

    try:
        #ZCL HEADER FILE

        File = drvZigbeeComponent.createFileSymbol('ZCC'+str(cli)+'_'+'CUSTOM_CLUSTER_GENERATION_HEADER',None)
        File.setSourcePath('/driver/zigbee/templates/cluster/custom/zclCustomCluster.h.ftl')
        File.setDestPath("/zigbee/lib/inc/zcl/include/")
        File.setType('HEADER')
        File.setProjectPath("/config/" + configName + "/zigbee/lib/inc/zcl/include/")
        outputName = 'zcl' + 'customCluster'+str(cli) + 'Cluster.h'
        File.addMarkupVariable("FILE_NAME", outputName)
        File.setOutputName(outputName)
        File.addMarkupVariable("NAME", "ZCC"+str(cli) )
        File.setMarkup(True)
        File.setEnabled(False)

        File = drvZigbeeComponent.createFileSymbol('ZCC'+str(cli)+'_'+'CUSTOM_CLUSTER_GENERATION_SOURCE',None)
        File.setSourcePath('/driver/zigbee/templates/cluster/custom/zbCustomCluster.c.ftl')    
        File.setDestPath("/zigbee/z3device/" + str(FILE_PATH[drvZigbeeComponent.getID()]))
        File.setType('SOURCE')
        File.setProjectPath("/config/" + configName + "/zigbee/z3device/" + str(FILE_PATH[drvZigbeeComponent.getID()]))
        outputName = prefix + 'customCluster' +str(cli) + 'Cluster.c'
        File.addMarkupVariable("FILE_NAME", outputName)
        File.setOutputName(outputName)
        File.addMarkupVariable("NAME", "ZCC"+str(cli))
        File.setMarkup(True)
        File.setEnabled(False)

        File = drvZigbeeComponent.createFileSymbol('ZCC'+str(cli)+'_'+'CUSTOM_CLUSTER_GENERATION_SERVER_HEADER',None)
        File.setSourcePath('/driver/zigbee/templates/cluster/custom/zbCustomCluster.h.ftl')    
        File.setDestPath("/zigbee/z3device/" + str(FILE_PATH[drvZigbeeComponent.getID()]) + "/include/" )
        File.setType('HEADER')  
        File.setProjectPath("/config/" + configName + "/zigbee/z3device/" + str(FILE_PATH[drvZigbeeComponent.getID()]) + "/include/" ) 
        outputName = prefix + 'customCluster'+str(cli) + 'Cluster.h'
        File.addMarkupVariable("FILE_NAME", outputName)
        File.setOutputName(outputName)
        File.addMarkupVariable("NAME", "ZCC"+str(cli))
        File.setMarkup(True)
        File.setEnabled(False)
        

    except Exception as e:
        print("Exception at generating cluster file ",e)
