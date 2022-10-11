/*******************************************************************************
  MAC Debug Header File

  Company:
    Microchip Technology Inc.

  File Name:
    macDbg.h

  Summary:
    This file contains the MAC Debug and Assert Codes.

  Description:
    This file contains the MAC Debug and Assert Codes.
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

#ifndef _MACDBG_H
#define _MACDBG_H

/*********************************************************************************
 ASSERT is used for debugging wrong conditions

 Types of messages:


*********************************************************************************/

/***************************************************************
  Defines with 1 in the high-order bit should not be used as enum is signed int type
***************************************************************/
typedef enum
{
  /***********************************
    MAC & PHY section. Range 0x1000 - 0x1FFFF
  ***********************************/
  // PHY asserts' ID.
  PHYRFIRQDISPATCHER_RFINTERRUPTSUBROUTINE_0        = 0x1001,
  PHYTXFRAME_DATAREQ_0                              = 0x1002,
  PHYPIB_PHYSETPIBPARAM_0                           = 0x1003,
  PHYPIB_PHYGETPIBPARAM_0                           = 0x1004,
  PHYTXFRAME_PHYDATAREQ_0                           = 0x1005,
  PHYRXFRAME_PHYDOWNLOADFRAME_0                     = 0x1006,
  MACPHYMACENV_GETSYMBOLPEROCTET_0                  = 0x1007,
  MACPHYMACENV_GETPHYSYMBOLDURATION_0               = 0x1008,
  PHYSET_PHYSETREQ_0                                = 0x1009,
  PHYSETTRXSTATE_PHYSETTRXSTATEREQ_0                = 0x100A,
  PHYRFSPIPROTO_PHYENCRYPTBYSPI_0                   = 0x100B,
  MACPHYPIBSERVER_STORETXPOWER_0                    = 0x100C,
  PHYTXPOWERCONVERTER_CONVERTTXPOWERFROMDBM_0       = 0x100D,
  PHYSET_PHYSETREQ_1                                = 0x100E,
  MACPHYMACENV_SETPIBATTR_0                         = 0x100F,
  MACPHYMACENV_GETPIBATTR_0                         = 0x1010,
  HALMACISRC_DISPATHRTIMEREVENT_0                   = 0x1011,
  PHYRFTXRX_CANNOT_BE_ENABLED                       = 0x1012,
  PHYRFTXRX_CANNOT_BE_DISABLED                      = 0x1013,
  PHYRFIRQDISPATCHER_WRONGSTATE_0                   = 0x1014,
  PHYRFIRQDISPATCHER_WRONGSTATE_1                   = 0x1015,
  PHYSET_PHYSETREQ_2                                = 0x1016,
  PHYANTEXTSW_CANNOT_BE_ENABLED                     = 0x1017,
  PHYANTEXTSW_CANNOT_BE_DISABLED                    = 0x1018,

  PHYRFIRQ_UNREASONABLE_IRQ                         = 0x1019,
  PHYRFIRQ_UNKNOWN_RX_STATUS                        = 0x101A,
  PHYRFIRQ_UNKNOWN_TX_STATUS                        = 0x101B,
  PHYRFIRQ_OTHER_IRQ                                = 0x101C,
  PHYRF_EXTRA_RX_FRAME                              = 0x101D,
  PHYRXFRAME_PHYDOWNLOADFRAME_1                     = 0x101E,
  PHYSET_PHYSETREQ_3                                = 0x101F,
  PHYTXFRAME_PHYDATAREQ_1                           = 0x1020,

  // MAC_HWD asserts' ID.
  MACHWDFRAMEROUTINE_MACHWDCOMPOSEFRAME_0           = 0x1021,
  MACHWDPIB_MACHWDGETPIBPARAM_0                     = 0x1022,
  MACHWDGETHANDLER_MACHWDGETREQHANDLER_0            = 0x1023,
  MACHWDRXFRAMEHANDLER_GETCURRENTCHANNEL_0          = 0x1024,
  MACHWDMANAGER_TASKHANDLER_0                       = 0x1025,
  MACHWDMANAGER_TASKHANDLER_1                       = 0x1026,
  MACHWDMANAGER_TASKHANDLER_2                       = 0x1027,
  MACHWDMANAGER_SENDREQTOHANDLER_0                  = 0x1028,
  MACHWDMANAGER_DISPATCHETASKTOHANDLER_0            = 0x1029,
  MACHWDEDHNDLR_MACHWDEDHANDLER_0                   = 0x102A,
  MACHWDEDHNDLR_MACHWDEDHANDLER_1                   = 0x102B,
  MACHWDEDHNDLR_MACHWDEDTASKHANDLER_0               = 0x102C,
  MACHWDTRXHANDLER_MACHWDTRXREQHANDLER_0            = 0x102D,
  MACHWDTRXHANDLER_TRXTASKHANDLER_0                 = 0x102E,
  MACHWDSETHANDLER_MACHWDSETREQHANDLER_0            = 0x102F,
  MACHWDSETHANDLER_MACHWDSETREQHANDLER_1            = 0x1030,
  MACHWDSETHANDLER_MACHWDSETTASKHANDLER_0           = 0x1031,
  MACHWDSETHANDLER_MACHWDSETTASKHANDLER_1           = 0x1032,
  MACHWDSETHANDLER_EXECUTESETREQ_0                  = 0x1033,
  MACHWDSETHANDLER_EXECUTEPHYSETREQ_0               = 0x1034,
  MACHWDSETHANDLER_SETRXONSTATE_0                   = 0x1035,
  MACHWDTXFRAMEHANDLER_MACHWDTXFRAMEREQHANDLER_0    = 0x1036,
  MACHWDTXFRAMEHANDLER_MACHWDTXFRAMETASKHANDLER_0   = 0x1037,
  MACHWDTXFRAMEHANDLER_EXECUTEPHYDATAREQ_0          = 0x1038,
  MACHWDTXFRAMEHANDLER_SETRXONSTATE_0               = 0x1039,
  MACHWDRESETHANDLER_MACHWDRESETREQHANDLER_0        = 0x1040,
  MACHWDTXFRAMEHANDLER_EXECUTEDATAREQ_0             = 0x1041,
  MACHWDTXFRAMEHANDLER_MACHWDTXFRAMETASKHANDLER_1   = 0x1042,
  MACHWDGETHANDLER_MACHWDGETREQHANDLER_1            = 0x1043,
  MACHWDSETHANDLER_MACHWDSETREQHANDLER_2            = 0x1044,
  MACHWDTRXCTRL_GETPHYTRXCMD_0                      = 0x1045,
  MACHWDTRXCTRL_CONVERTTRXCMDTOTRXSTATE_0           = 0x1046,
  MACHWDEDHANDLER_MACHWDEDREQHANDLER_2              = 0x1047,
  MACHWDTXFRAMEHANDLER_GETDATASTATUS_0              = 0x1048,
  MACHWDENCRYPTHANDLER_MACHWDENCRYPTREQHANDLER_0    = 0x1049,
  MACHWDENCRYPTHANDLER_MACHWDENCRYPTREQHANDLER_1    = 0x104A,
  MACHWDENCRYPTHANDLER_MACHWDENCRYPTTASKHANDLER_0   = 0x104B,
  MACHWDRNDHANDLER_MACHWDRNDREQHANDLER_0            = 0x104C,
  MACHWDRNDHANDLER_MACHWDRNDREQHANDLER_1            = 0x104D,
  MACHWDRNDHANDLER_MACHWDRNDTASKHANDLER_0           = 0x104E,
  MACHWDBATMONHANDLER_MACHWDBATMONREQHANDLER_0      = 0x104F,
  MACHWDBATMONHANDLER_MACHWDBATMONREQHANDLER_1      = 0x1050,
  MACHWDBATMONHANDLER_MACHWDBATMONTASKHANDLER_0     = 0x1051,
  MACHWDBATMONHANDLER_MACHWDBATMONTASKHANDLER_1     = 0x1052,
  MACHWDTRXCTRL_CONVERTTRXSTATETOTRXCMD_0           = 0x1053,
  MACHWDRXBUFFER_CHECKBUFFERSPACE_0                 = 0x1054,
  MACHWDRXBUFFER_COMMITRXBUFFER_0                   = 0x1055,
  MACHWDRXBUFFER_ROLLBACKRXBUFFER_0                 = 0x1056,
  MACHWDRXBUFFER_GETBUFFER_0                        = 0x1057,
  MACHWDRXBUFFER_NEXTBUFFER_0                       = 0x1058,
  MACHWDRXBUFFER_NEXTBUFFER_1                       = 0x1059,
  MACHWDSETHANDLER_MACHWDSETREQHANDLER_3            = 0x105A,
  MACHWDTRXHANDLER_MACHWDTRXREQHANDLER_1            = 0x105B,
  MACHWDTXFRAMEHANDLER_MACHWDTXFRAMETASKHANDLER_2   = 0x105C,
  MACHWDMANAGER_SENDCONFTOUPPERLAYER_0              = 0x105D,
  MACHWDMANAGER_SENDCONFTOUPPERLAYER_1              = 0x105E,
  MACHWDRNDHANDLER_MACHWDCALIBREQHANDLER_0          = 0x105F,
  MACHWDRNDHANDLER_MACHWDCALIBREQHANDLER_1          = 0x1060,
  MACHWDCALIBHANDLER_MACHWDCALIBTASKHANDLER_0       = 0x1061,
  MACHWDREGACCESSREQHANDLER_0                       = 0x1062,
  MACHWDREGACCESSREQHANDLER_1                       = 0x1063,
  MACHWDREGACCESSREQHANDLER_2                       = 0x1064,
  MACHWDREGACCESSTASKHANDLER_0                      = 0x1065,
  MACHWDREGACCESSTASKHANDLER_1                      = 0x1066,
  MACHWDMANAGER_TASKHANDLER_3                       = 0x1067,
  MACHWD_BATTERYMONOTOR_NULLCALLBACK0               = 0x1068,
  MACHWD_BATTERYMONOTOR_NULLCALLBACK1               = 0x1069,
  MACHWD_BATTERYMONOTOR_NULLCALLBACK2               = 0x106A,
  MACHWD_BATTERYMONOTOR_NULLCALLBACK3               = 0x106B,
  MACHWD_CALIBRATION_NULLCALLBACK0                  = 0x106C,
  MACHWD_CALIBRATION_NULLCALLBACK1                  = 0x106D,
  MACHWD_CALIBRATION_NULLCALLBACK2                  = 0x106E,
  MACHWD_CALIBRATION_NULLCALLBACK3                  = 0x106F,
  MACHWD_ENCRYPT_NULLCALLBACK0                      = 0x1070,
  MACHWD_ENCRYPT_NULLCALLBACK1                      = 0x1071,
  MACHWD_ENCRYPT_NULLCALLBACK2                      = 0x1072,
  MACHWD_ENCRYPT_NULLCALLBACK3                      = 0x1073,
  MACHWD_RANDOM_NULLCALLBACK0                       = 0x1074,
  MACHWD_RANDOM_NULLCALLBACK1                       = 0x1075,
  MACHWD_RANDOM_NULLCALLBACK2                       = 0x1076,
  MACHWD_RANDOM_NULLCALLBACK3                       = 0x1077,
  MACHWD_RANDOM_NULLCALLBACK4                       = 0x1078,
  MACHWD_RANDOM_NULLCALLBACK5                       = 0x1079,
  MACHWD_RANDOM_NULLCALLBACK6                       = 0x107A,
  MACHWD_REGACCESS_NULLCALLBACK0                    = 0x107B,
  MACHWD_REGACCESS_NULLCALLBACK1                    = 0x107C,
  MACHWD_REGACCESS_NULLCALLBACK2                    = 0x107D,
  MACHWD_REGACCESS_NULLCALLBACK3                    = 0x107E,
  MACHWD_DATA_NULLCALLBACK0                         = 0x107F,
  MACHWD_DATA_NULLCALLBACK1                         = 0x10C1,
  MACHWD_DATA_NULLCALLBACK2                         = 0x10C2,
  MACHWD_DATA_NULLCALLBACK3                         = 0x10C3,
  MACHWD_ED_NULLCALLBACK0                           = 0x10C4,
  MACHWD_ED_NULLCALLBACK1                           = 0x10C5,
  MACHWD_ED_NULLCALLBACK2                           = 0x10C6,
  MACHWD_ED_NULLCALLBACK3                           = 0x10C7,
  MACHWD_SET_NULLCALLBACK0                          = 0x10C8,
  MACHWD_SET_NULLCALLBACK1                          = 0x10C9,
  MACHWD_SET_NULLCALLBACK2                          = 0x10CA,
  MACHWD_SET_NULLCALLBACK3                          = 0x10CB,
  MACHWD_SET_NULLCALLBACK4                          = 0x10CC,
  MACHWD_SET_NULLCALLBACK5                          = 0x10CD,
  MACHWD_SETTRXSTATE_NULLCALLBACK0                  = 0x10CE,
  MACHWD_SETTRXSTATE_NULLCALLBACK1                  = 0x10CF,
  MACHWD_SETTRXSTATE_NULLCALLBACK2                  = 0x10D1,
  MACHWD_SETTRXSTATE_NULLCALLBACK3                  = 0x10D2,
  MACHWD_SETTRXSTATE_NULLCALLBACK4                  = 0x10D3,
  MACHWD_SETTRXSTATE_NULLCALLBACK5                  = 0x10D4,
  MACHWD_SETTRXSTATE_NULLCALLBACK6                  = 0x10D5,
  MACHWD_SETTRXSTATE_NULLCALLBACK7                  = 0x10D6,
  MACHWD_BATTERYMONOTOR_NULLCALLBACK4               = 0x10D7,
  MACHWDRXBUFFER_RELEASEBUFFER_0                    = 0x10D8,
  MACHWDRXBUFFER_RELEASEBUFFER_1                    = 0x10D9,
  MACHWDFRAMEROUTINE_COMPOSEFRAME_0                 = 0x10DA,

  // MAC_HWI asserts' ID.
  MACHWIDATAHANDLER_CONVERTMACHWDDATACONFIRMTYPES_0 = 0x1080,
  MACHWIMANAGER_SENDREQTOHANDLER_0                  = 0x1083,
  MACHWIMANAGER_TASKHANDLER_0                       = 0x1084,
  MACHWIMANAGER_TASKHANDLER_1                       = 0x1085,
  MACHWISCANHANDLER_MACHWDSETCONFIRM_0              = 0x1086,
  MACHWISCANHANDLER_MACHWDSETCONFIRM_1              = 0x1087,
  MACHWISCANHANDLER_MACHWIBEACONINDICATION_0        = 0x1088,
  MACHWIASSOCIATEHANDLER_MACHWDSETCONFIRM_0         = 0x1089,
  MACHWIASSOCIATEHANDLER_MACHWDSETTRXSTATECONFIRM_0 = 0x108A,
  MACHWIASSOCIATEHANDLER_MACHWDDATACONFIRM_0        = 0x108B,
  MACHWIASSOCIATEHANDLER_MACHWDDATACONFIRM_1        = 0x108C,
  MACHWIASSOCIATEHANDLER_MACHWDDATACONFIRM_2        = 0x108D,
  MACHWIASSOCIATEHANDLER_ASSOCIATETIMERFIRED_0      = 0x108E,
  MACHWITRANSACTIONQUEUE_GETDSTADDRINFO_0           = 0x108F,
  MACHWITRANSACTIONQUEUE_GETDSTADDRINFO_1           = 0x1090,
  MACHWITRANSACTIONHANDLER_MACHWDDATACONFIRM_0      = 0x1091,
  MACHWITRANSACTIONHANDLER_MACHWDDATACONFIRM_1      = 0x1092,
  MACHWITRANSACTIONHANDLER_SENDTRANSACTIONEVENT_0   = 0x1093,
  MACHWITRANSACTIONHANDLER_SENDTRANSACTIONEVENT_1   = 0x1094,
  MACHWITRANSACTIONQUEUE_GETACTIVATEDTRANSACTION_0  = 0x1095,
  MACHWISTARTHANDLER_MACHWDSETCONFIRM_0             = 0x1096,
  MACHWISTARTHANDLER_MACHWDSETCONFIRM_1             = 0x1097,
  MACHWISCANHANDLER_MACHWDSETTRXSTATECONFIRM_0      = 0x1098,
  MACHWIPOLLHANDLER_MACHWDDATACONFIRM_0             = 0x1099,
  MACHWIPOLLHANDLER_ISITREQUESTEDDATA_0             = 0x109A,
  MACHWISCANHANDLER_MACHWDSETTRXSTATECONFIRM_1      = 0x109B,
  MACHWISCANHANDLER_MACHWDSETTRXSTATECONFIRM_2      = 0x109C,
  MACHWISCANHANDLER_MACHWISCANREQHANDLER_0          = 0x109D,
  MACHWISCANHANDLER_MACHWDSETCONFIRM_2              = 0x109E,
  MACHWISCANHANDLER_MACHWDSETCONFIRM_3              = 0x109F,
  MACHWISCANHANDLER_MACHWDSETCONFIRM_4              = 0x10A0,
  MACHWIDISASSOCIATEHANDLER_MACHWDDATACONFIRM_0     = 0x10A1,
  MACHWISWITCHRXCTRL_SWITCHRXONWHENIDLE_0           = 0x10A2,
  MACHWIMANAGER_MACHWISENDCONFTOUPPERLAYER_0        = 0x10A3,
  MACHWISETHANDLER_MACHWDSETCONFIRM_0               = 0x10A4,
  MACHWIGETHANDLER_MACHWDGETCONFIRM_0               = 0x10A5,
  MACHWISTARTHANDLER_MACHWISTARTREQHANDLER_0        = 0x10A6,
  MACHWIRESETHANDLER_MACHWDSETCONFIRM_0             = 0x10A7,
  MACHWIDISASSOCIATEHANDLER_MACHWDSETCONFIRM_0      = 0x10A8,
  MACHWISTARTHANDLER_MACHWDDATACONFIRM_0            = 0x10A9,
  MACHWIENCRYPTHANDLER_MACHWISETKEYREQ_0            = 0x10AA,
  MACHWIENCRYPTHANDLER_MACHWDENCRYPTCONF_0          = 0x10AB,
  MACHWIENCRYPTHANDLER_MACHWIENCRYPTREQHANDLER_0    = 0x10AC,
  MACHWIASSOCIATEHANDLER_SETHANDLING_0              = 0x10AD,
  MACHWIASSOCIATEHANDLER_MACHWDSETCONFIRM_1         = 0x10AE,
  MACHWIASSOCIATEHANDLER_ASSOCIATETIMERFIRED_1      = 0x10AF,
  MACHWIDISASSOCIATEHANDLER_SETHANDLING_0           = 0x10B0,
  MACHWIRESETHANDLER_SETHANDLING_0                  = 0x10B1,
  MACHWISCANHANDLER_SETHANDLING_0                   = 0x10B2,
  MACHWISCANHANDLER_MACHWDEDCONFIRM_0               = 0x10B3,
  MACHWISCANHANDLER_TRXSTATEHANDLING_0              = 0x10B4,
  MACHWISTARTHANDLER_MACHWDSETCONFIRM_2             = 0x10B5,
  MACHWISWITCHRXCTRL_SWITCHRXONWHENIDLE_1           = 0x10B6,
  MACHWISTARTHANDLER_SETHANDLING_0                  = 0x10B7,
  MACHWISCANHANDLERC_MACHWDEDCONFIRM_0              = 0x10B8,
  MACHWISCANHANDLERC_TRXSTATEHANDLING_0             = 0X10b9,
  PHYRFIRQDISPATCHER_RFINTERRUPTSUBROUTINE_1        = 0x10ba,
  MACHWITRANSACTIONQUEUE_TESTANDKICKQUEUETRANS_0    = 0x10bb,
  MACHWIMANAGER_PROCEEDPOSTPONEDACTIONS_0           = 0x10bc,
  MACHWITRANSACTIONHANDLER_SENDTRANSACTIONEVENT_2   = 0x10bd,
  MACHWITRANSACTIONHANDLER_SENDTRANSACTIONEVENT_3   = 0x10be,
  MACHWITRANSACTIONHANDLER_SENDTRANSACTIONEVENT_4   = 0x10bf,
  MACHWIBANNODE_MACBANNODE0                         = 0x10c0,
  MACHWITRANSACTIONHASH_WRONG_REQ                   = 0x10d0,
  MACHWI_ASSOCIATE_NULLCALLBACK_0                   = 0x1100,
  MACHWI_ASSOCIATE_NULLCALLBACK_1                   = 0x1101,
  MACHWI_ASSOCIATE_NULLCALLBACK_2                   = 0x1102,
  MACHWI_ASSOCIATE_NULLCALLBACK_3                   = 0x1103,
  MACHWI_ASSOCIATE_NULLCALLBACK_4                   = 0x1104,
  MACHWI_ASSOCIATE_NULLCALLBACK_5                   = 0x1105,
  MACHWI_ASSOCIATE_NULLCALLBACK_6                   = 0x1106,
  MACHWI_DATACONF_NULLCALLBACK0                     = 0x1107,
  MACHWI_DATACONF_NULLCALLBACK1                     = 0x1108,
  MACHWI_DATACONF_NULLCALLBACK2                     = 0x1109,
  MACHWI_DATACONF_NULLCALLBACK3                     = 0x110A,
  MACHWI_DISASSOCIATE_NULLCALLBACK0                 = 0x110B,
  MACHWI_DISASSOCIATE_NULLCALLBACK1                 = 0x110C,
  MACHWI_DISASSOCIATE_NULLCALLBACK2                 = 0x110D,
  MACHWI_DISASSOCIATE_NULLCALLBACK3                 = 0x110E,
  MACHWI_POLL_NULLCALLBACK0                         = 0x110F,
  MACHWI_POLL_NULLCALLBACK1                         = 0x1110,
  MACHWI_POLL_NULLCALLBACK2                         = 0x1111,
  MACHWI_POLL_NULLCALLBACK3                         = 0x1112,
  MACHWI_POLL_NULLCALLBACK4                         = 0x1113,
  MACHWI_PURGE_NULLCALLBACK0                        = 0x1114,
  MACHWI_PURGE_NULLCALLBACK1                        = 0x1115,
  MACHWI_PURGE_NULLCALLBACK2                        = 0x1116,
  MACHWI_PURGE_NULLCALLBACK3                        = 0x1117,
  MACHWI_RESET_NULLCALLBACK0                        = 0x1118,
  MACHWI_RESET_NULLCALLBACK1                        = 0x1119,
  MACHWI_RESET_NULLCALLBACK2                        = 0x111A,
  MACHWI_RESET_NULLCALLBACK3                        = 0x111B,
  MACHWI_RXENABLE_NULLCALLBACK0                     = 0x111C,
  MACHWI_RXENABLE_NULLCALLBACK1                     = 0x111D,
  MACHWI_RXENABLE_NULLCALLBACK2                     = 0x111E,
  MACHWI_RXENABLE_NULLCALLBACK3                     = 0x111F,
  MACHWI_SCAN_NULLCALLBACK0                         = 0x1120,
  MACHWI_SCAN_NULLCALLBACK1                         = 0x1121,
  MACHWI_SCAN_NULLCALLBACK2                         = 0x1122,
  MACHWI_SCAN_NULLCALLBACK3                         = 0x1123,
  MACHWI_SET_NULLCALLBACK0                          = 0x1124,
  MACHWI_SET_NULLCALLBACK1                          = 0x1125,
  MACHWI_SET_NULLCALLBACK2                          = 0x1126,
  MACHWI_SET_NULLCALLBACK3                          = 0x1127,
  MACHWI_GET_NULLCALLBACK0                          = 0x1128,
  MACHWI_GET_NULLCALLBACK1                          = 0x1129,
  MACHWI_GET_NULLCALLBACK2                          = 0x112A,
  MACHWI_GET_NULLCALLBACK3                          = 0x112B,
  MACHWI_GET_NULLCALLBACK4                          = 0x112C,
  MACHWI_START_NULLCALLBACK0                        = 0x112D,
  MACHWI_START_NULLCALLBACK1                        = 0x112E,
  MACHWI_START_NULLCALLBACK2                        = 0x112F,
  MACHWI_START_NULLCALLBACK3                        = 0x1130,
  PHYRFTXFLTON_CANNOT_BE_ENABLED                    = 0x1131,
  PHYRFTXFLTON_CANNOT_BE_DISABLED                   = 0x1132,
  PHYPLLON_ATTEMPT_FAILURE1                         = 0x1133,
  PHYPLLON_ATTEMPT_FAILURE2                         = 0x1134,
  PHYRFIRQDISPATCHER_RXAACKON_WRONGSTATE            = 0x1135,
  PHYTXPOWERCONVERTER_CONVERTTXPOWERTODBM_0         = 0x1136,
  MACHWI_REQ_PROCESSING_TIMEOUT                     = 0x1137,

  MACHWDTXFRAMEHANDLER_RETRYHANDLER_0               = 0x1ff6,
  PHY_DOWNLOAD_FRAME_TIME_LIMIT                     = 0x1ff7,
  PHY_ED_REQ_TIME_LIMIT                             = 0x1ff8,
  MACHWD_RX_RELEASE_BUFFER_LIMIT                    = 0x1ff9,
  MACHWD_POST_TASK_TIME_LIMIT                       = 0x1ffa,
  MACHWD_RESET_TIME_LIMIT                           = 0x1ffb,
  MACHWD_SETHANDLER_ID_1_TIME_LIMIT                 = 0x1ffc,
  MACHWD_SETHANDLER_ID_2_TIME_LIMIT                 = 0x1ffd,
  MACHWD_SETHANDLER_ID_3_TIME_LIMIT                 = 0x1ffe,
  MACHWD_SETHANDLER_ID_4_TIME_LIMIT                 = 0x1fff
} MacDbgCode_t;

typedef enum
{
  LOG_MAC_MAC_DATA_REQ,
  LOG_MAC_SEND_REQ_TO_HANDLER,
  LOG_MAC_SEND_CONF_TO_UPPER,
  LOG_MAC_SEND_TRANSAC_EVENT,
  LOG_MAC_SEND_TRANSAC_EVENT2
} MacLogCodeId_t;

#endif /* _MACDBG_H */

//end of macDbg.h

