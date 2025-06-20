/*******************************************************************************
  ZCL ZCC CUSTOM Cluster Header File

  Company:
    Microchip Technology Inc.

  File Name:
    zclWindowCoveringCluster.h

  Summary:
    The header file describes the ZCL CUSTOM Cluster and its interface.

  Description:
    The file describes the types and interface of the ZCL CUSTOM Cluster.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
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
*******************************************************************************/
// DOM-IGNORE-END

#ifndef _ZCLWINDOWCOVERING_H
#define _ZCLWINDOWCOVERING_H

/*******************************************************************************
                   Includes section
*******************************************************************************/

#include <zcl/include/zcl.h>
#include <zcl/include/clusters.h>
/******************************************************************************
                    Define(s) section
******************************************************************************/
    
//ATTRIBUTE DEFINITION SECTION


#define WINDOWCOVERING_CLUSTER_ID                                                     0x102

#define ZCL_WINDOWCOVERING_SERVER_ATTRIBUTES_AMOUNT                      5
#define ZCL_WINDOWCOVERING_SERVER_COMMANDS_AMOUNT                        8

#define ZCL_WINDOWCOVERING_CLIENT_ATTRIBUTES_AMOUNT                      0
#define ZCL_WINDOWCOVERING_CLIENT_COMMANDS_AMOUNT                        8

//Attribute IDs
#define ZCL_WINDOWCOVERING_WINDOWCOVERINGTYPE_SERVER_ATTRIBUTE_ID                CCPU_TO_LE16(0X0)
#define ZCL_WINDOWCOVERING_CONFIG_SERVER_ATTRIBUTE_ID                            CCPU_TO_LE16(0X7)
#define ZCL_WINDOWCOVERING_CURRENTPOSITIONLIFTPERCENTAGE_SERVER_ATTRIBUTE_ID     CCPU_TO_LE16(0X8)
#define ZCL_WINDOWCOVERING_CURRENTPOSITIONTILTPERCENTAGE_SERVER_ATTRIBUTE_ID     CCPU_TO_LE16(0X9)
#define ZCL_WINDOWCOVERING_MODE_SERVER_ATTRIBUTE_ID                              CCPU_TO_LE16(0X17)


#define ZCL_DEFINE_WINDOWCOVERING_CLUSTER_SERVER_ATTRIBUTES(min,max) \
        DEFINE_ATTRIBUTE(Windowcoveringtype, ZCL_READONLY_ATTRIBUTE, ZCL_WINDOWCOVERING_WINDOWCOVERINGTYPE_SERVER_ATTRIBUTE_ID, ZCL_8BIT_ENUM_DATA_TYPE_ID) , \
        DEFINE_ATTRIBUTE(Config, ZCL_READONLY_ATTRIBUTE, ZCL_WINDOWCOVERING_CONFIG_SERVER_ATTRIBUTE_ID, ZCL_8BIT_BITMAP_DATA_TYPE_ID) , \
        DEFINE_REPORTABLE_ATTRIBUTE(Currentpositionliftpercentage, ZCL_READONLY_ATTRIBUTE, ZCL_WINDOWCOVERING_CURRENTPOSITIONLIFTPERCENTAGE_SERVER_ATTRIBUTE_ID, ZCL_U8BIT_DATA_TYPE_ID, min, max) , \
        DEFINE_REPORTABLE_ATTRIBUTE(Currentpositiontiltpercentage, ZCL_READONLY_ATTRIBUTE, ZCL_WINDOWCOVERING_CURRENTPOSITIONTILTPERCENTAGE_SERVER_ATTRIBUTE_ID, ZCL_U8BIT_DATA_TYPE_ID, min, max) , \
        DEFINE_ATTRIBUTE(Mode, ZCL_READWRITE_ATTRIBUTE, ZCL_WINDOWCOVERING_MODE_SERVER_ATTRIBUTE_ID, ZCL_8BIT_BITMAP_DATA_TYPE_ID) 

#define ZCL_DEFINE_WINDOWCOVERING_CLUSTER_CLIENT_ATTRIBUTES() \



#define WINDOWCOVERING_CLUSTER_ZCL_SERVER_CLUSTER_TYPE(clattributes, clcommands)                                                \
  {                                                                                                              \
    .id = WINDOWCOVERING_CLUSTER_ID,                                                                                      \
    .options = {.type = ZCL_SERVER_CLUSTER_TYPE, .security = ZCL_NETWORK_KEY_CLUSTER_SECURITY},                  \
    .attributesAmount = ZCL_WINDOWCOVERING_SERVER_ATTRIBUTES_AMOUNT,                                              \
    .attributes = (uint8_t *) clattributes,                                                                      \
    .commandsAmount = ZCL_WINDOWCOVERING_SERVER_COMMANDS_AMOUNT,                                                  \
    .commands = (uint8_t *)clcommands                                                                            \
  }

#define WINDOWCOVERING_CLUSTER_ZCL_CLIENT_CLUSTER_TYPE(clattributes, clcommands)                                                \
  {                                                                                                              \
    .id = WINDOWCOVERING_CLUSTER_ID,                                                                                      \
    .options = {.type = ZCL_CLIENT_CLUSTER_TYPE, .security = ZCL_NETWORK_KEY_CLUSTER_SECURITY},                  \
    .attributesAmount = ZCL_WINDOWCOVERING_CLIENT_ATTRIBUTES_AMOUNT,                                              \
    .attributes = (uint8_t *) clattributes,                                                                      \
    .commandsAmount = ZCL_WINDOWCOVERING_CLIENT_COMMANDS_AMOUNT,                                                  \
    .commands = (uint8_t *)clcommands                                                                            \
  }


  #define DEFINE_WINDOWCOVERING_CLUSTER(cltype, clattributes, clcommands) \
    WINDOWCOVERING_CLUSTER_##cltype(clattributes, clcommands)


// ATTRIBUTE DEFINITION END
//COMMAND DEFINITION SECTION

//Server Commands
#define ZCL_WINDOWCOVERING_DEFAULTRESPONSE_COMMAND_ID                            0x0

//Client Commands
#define ZCL_WINDOWCOVERING_UP_COMMAND_ID                                         0x0
#define ZCL_WINDOWCOVERING_DOWN_COMMAND_ID                                       0x1
#define ZCL_WINDOWCOVERING_STOP_COMMAND_ID                                       0x2
#define ZCL_WINDOWCOVERING_GOTOLIFTVALUE_COMMAND_ID                              0x4
#define ZCL_WINDOWCOVERING_GOTOLIFTPERCENTAGE_COMMAND_ID                         0x5
#define ZCL_WINDOWCOVERING_GOTOTILTVALUE_COMMAND_ID                              0x7
#define ZCL_WINDOWCOVERING_GOTOTILTPERCENTAGE_COMMAND_ID                         0x8

#define ZCL_DEFINE_WINDOWCOVERING_CLUSTER_COMMANDS(\
        DefaultresponseCommandInd , \
        UpCommandInd , \
        DownCommandInd , \
        StopCommandInd , \
        GotoliftvalueCommandInd , \
        GotoliftpercentageCommandInd , \
        GototiltvalueCommandInd , \
        GototiltpercentageCommandInd ) \
    DEFINE_COMMAND(DefaultresponseCommand, ZCL_WINDOWCOVERING_DEFAULTRESPONSE_COMMAND_ID,  \
        COMMAND_OPTIONS(SERVER_TO_CLIENT , ZCL_THERE_IS_NO_RELEVANT_RESPONSE , ZCL_COMMAND_NO_ACK), DefaultresponseCommandInd), \
    DEFINE_COMMAND(UpCommand, ZCL_WINDOWCOVERING_UP_COMMAND_ID,  \
        COMMAND_OPTIONS(CLIENT_TO_SERVER , ZCL_THERE_IS_NO_RELEVANT_RESPONSE , ZCL_COMMAND_NO_ACK), UpCommandInd), \
    DEFINE_COMMAND(DownCommand, ZCL_WINDOWCOVERING_DOWN_COMMAND_ID,  \
        COMMAND_OPTIONS(CLIENT_TO_SERVER , ZCL_THERE_IS_NO_RELEVANT_RESPONSE , ZCL_COMMAND_NO_ACK), DownCommandInd), \
    DEFINE_COMMAND(StopCommand, ZCL_WINDOWCOVERING_STOP_COMMAND_ID,  \
        COMMAND_OPTIONS(CLIENT_TO_SERVER , ZCL_THERE_IS_NO_RELEVANT_RESPONSE , ZCL_COMMAND_NO_ACK), StopCommandInd), \
    DEFINE_COMMAND(GotoliftvalueCommand, ZCL_WINDOWCOVERING_GOTOLIFTVALUE_COMMAND_ID,  \
        COMMAND_OPTIONS(CLIENT_TO_SERVER , ZCL_THERE_IS_NO_RELEVANT_RESPONSE , ZCL_COMMAND_NO_ACK), GotoliftvalueCommandInd), \
    DEFINE_COMMAND(GotoliftpercentageCommand, ZCL_WINDOWCOVERING_GOTOLIFTPERCENTAGE_COMMAND_ID,  \
        COMMAND_OPTIONS(CLIENT_TO_SERVER , ZCL_THERE_IS_NO_RELEVANT_RESPONSE , ZCL_COMMAND_NO_ACK), GotoliftpercentageCommandInd), \
    DEFINE_COMMAND(GototiltvalueCommand, ZCL_WINDOWCOVERING_GOTOTILTVALUE_COMMAND_ID,  \
        COMMAND_OPTIONS(CLIENT_TO_SERVER , ZCL_THERE_IS_NO_RELEVANT_RESPONSE , ZCL_COMMAND_NO_ACK), GototiltvalueCommandInd), \
    DEFINE_COMMAND(GototiltpercentageCommand, ZCL_WINDOWCOVERING_GOTOTILTPERCENTAGE_COMMAND_ID,  \
        COMMAND_OPTIONS(CLIENT_TO_SERVER , ZCL_THERE_IS_NO_RELEVANT_RESPONSE , ZCL_COMMAND_NO_ACK), GototiltpercentageCommandInd)



/******************************************************************************
                    Types section
******************************************************************************/
//ATTRIBUTE's TYPES SECTION
typedef struct PACK _ZCL_WINDOWCOVERING_CONFIGBitmap_t
{
    uint8_t operational : 1;
    uint8_t online : 1;
    uint8_t openUp_reversed : 1;
    uint8_t lift_closed_loop : 1;
    uint8_t tilt_closed_loop : 1;
    uint8_t lift_encoder_controlled : 1;
    uint8_t lilt_encoder_controlled : 1;
}ZCL_WINDOWCOVERINGConfigBitmap_t;

typedef struct PACK _ZCL_WINDOWCOVERING_MODEBitmap_t
{
    uint8_t reversed : 1;
    uint8_t calibration : 1;
    uint8_t maintenance : 1;
    uint8_t led_feedback : 1;
}ZCL_WINDOWCOVERINGModeBitmap_t;

typedef enum _ZCL_WindowcoveringWindowcoveringtypeEnum_t
{
    WINDOWCOVERING_WINDOWCOVERINGTYPE_ROLLERSHADE = 0x00,
    WINDOWCOVERING_WINDOWCOVERINGTYPE_ROLLERSHADE_2MOTOR,
    WINDOWCOVERING_WINDOWCOVERINGTYPE_EXTERIOR,
    WINDOWCOVERING_WINDOWCOVERINGTYPE_EXTERIOR_2MOTOR,
    WINDOWCOVERING_WINDOWCOVERINGTYPE_DRAPERY,
    WINDOWCOVERING_WINDOWCOVERINGTYPE_AWNING,
    WINDOWCOVERING_WINDOWCOVERINGTYPE_SHUTTER,
    WINDOWCOVERING_WINDOWCOVERINGTYPE_TILTBLIND_TILTONLY,
    WINDOWCOVERING_WINDOWCOVERINGTYPE_TILTBLIND_TILTANDLIFT,
    WINDOWCOVERING_WINDOWCOVERINGTYPE_PROJECTORSCREEN
}ZCL_WindowcoveringWindowcoveringtypeEnum_t;



typedef struct PACK
{
struct PACK
  {
    ZCL_AttributeId_t   id;
    uint8_t             type;
    uint8_t             properties;
    uint8_t             value;
   } Windowcoveringtype;

struct PACK
  {
    ZCL_AttributeId_t   id;
    uint8_t             type;
    uint8_t             properties;
    uint8_t             value;
   } Config;

struct PACK
  {
    ZCL_AttributeId_t   id;
    uint8_t             type;
    uint8_t             properties;
    uint8_t             value;
    ZCL_ReportTime_t    reportCounter;     //!<For internal use only
    ZCL_ReportTime_t    minReportInterval; //!<Minimum reporting interval field value
    ZCL_ReportTime_t    maxReportInterval; //!<Maximum reporting interval field value
    uint8_t              reportableChange;  //!<Reporting change field value
    ZCL_ReportTime_t    timeoutPeriod;     //!<Timeout period field value
    uint8_t              lastReportedValue; //!<Last reported value
   } Currentpositionliftpercentage;

struct PACK
  {
    ZCL_AttributeId_t   id;
    uint8_t             type;
    uint8_t             properties;
    uint8_t             value;
    ZCL_ReportTime_t    reportCounter;     //!<For internal use only
    ZCL_ReportTime_t    minReportInterval; //!<Minimum reporting interval field value
    ZCL_ReportTime_t    maxReportInterval; //!<Maximum reporting interval field value
    uint8_t              reportableChange;  //!<Reporting change field value
    ZCL_ReportTime_t    timeoutPeriod;     //!<Timeout period field value
    uint8_t              lastReportedValue; //!<Last reported value
   } Currentpositiontiltpercentage;

struct PACK
  {
    ZCL_AttributeId_t   id;
    uint8_t             type;
    uint8_t             properties;
    uint8_t             value;
   } Mode;

}ZCL_WindowcoveringClusterServerAttributes_t;

typedef struct PACK
{
}ZCL_WindowcoveringClusterClientAttributes_t;


// COMMANDS TYPE DEFINITION


typedef struct PACK
{

}ZCL_Defaultresponse_t;


typedef struct PACK
{

}ZCL_Up_t;

typedef struct PACK
{

}ZCL_Down_t;

typedef struct PACK
{

}ZCL_Stop_t;

typedef struct PACK
{
    uint8_t value;
}ZCL_Gotoliftvalue_t;

typedef struct PACK
{
    uint8_t percentage;
}ZCL_Gotoliftpercentage_t;

typedef struct PACK
{
    uint8_t value;
}ZCL_Gototiltvalue_t;

typedef struct PACK
{
    uint8_t percentage;
}ZCL_Gototiltpercentage_t;


typedef struct
{
struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*DefaultresponseCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Defaultresponse_t *payload);
  } DefaultresponseCommand;


struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*UpCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Up_t *payload);
  } UpCommand;

struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*DownCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Down_t *payload);
  } DownCommand;

struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*StopCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Stop_t *payload);
  } StopCommand;

struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*GotoliftvalueCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Gotoliftvalue_t *payload);
  } GotoliftvalueCommand;

struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*GotoliftpercentageCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Gotoliftpercentage_t *payload);
  } GotoliftpercentageCommand;

struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*GototiltvalueCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Gototiltvalue_t *payload);
  } GototiltvalueCommand;

struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*GototiltpercentageCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_Gototiltpercentage_t *payload);
  } GototiltpercentageCommand;


} ZCL_WindowcoveringClusterCommands_t;

#endif
