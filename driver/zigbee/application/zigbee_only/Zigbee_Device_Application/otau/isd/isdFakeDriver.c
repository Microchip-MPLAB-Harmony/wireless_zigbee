/*******************************************************************************
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
*******************************************************************************/

/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <zcl/include/zclOTAUCluster.h>
#include <zcl/include/zcl.h>
#include <z3device/otau/isd/isdFakeDriver.h>
#include <app_zigbee/zigbee_console/console.h>
#include <crypto.h>

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */

#define OTA_HEADER_STRING   "Sample Test File"
#define OTA_IMAGE_TYPE      OTAU_IMAGE_TYPE_MANU_SPEC_ENCRYPT_IMAGE_NO_MIC
#define OTA_FILE_VERSION    0xbadbeef

#define AES_BLOCK_SIZE 16
#define AES_ENCRYPTION 0
#define OTAU_MAX_BLOCK_SIZE AES_BLOCK_SIZE * 2 // (AES_BLOCK_SIZE *2) // 32 bytes
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */
typedef struct PACK
{
    uint32_t otaUpgradeFileID;
    uint16_t otaHeaderVersion;
    uint16_t otaHeaderLength;
    uint16_t otaHeaderFeildControl;
    uint16_t manufacturerCode;
    uint16_t imageType;
    uint32_t fileVersion;
    uint16_t zbStackVersion;
    uint8_t  otaHeaderString[32];
    uint32_t totalImageSize;
}OTA_HeaderStruct_t;

static uint8_t otauSampleImage[256 + sizeof(OTA_HeaderStruct_t)];

OTA_HeaderStruct_t sampleOtaHeader = {
    .otaUpgradeFileID = 0x0BEEF11E,
    .otaHeaderVersion =  0x0100,
    .otaHeaderLength = sizeof(OTA_HeaderStruct_t),
    .otaHeaderFeildControl = 0,
    .manufacturerCode = CS_MANUFACTURER_CODE,
    .imageType = OTA_IMAGE_TYPE,
    .fileVersion = OTA_FILE_VERSION,
    .zbStackVersion = 0,
    .totalImageSize = sizeof(otauSampleImage),
};

//Instance of Crypto
CRYPT_AES_CTX aes;

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */
void ISD_QueryNextImageReq(ZCL_Addressing_t *addressing, ZCL_OtauQueryNextImageReq_t *data, IsdQueryNextImageCb_t cb)
{
    (void)addressing;
    (void)data;
    ZCL_OtauQueryNextImageResp_t imageQueryResp;
    
    memcpy(sampleOtaHeader.otaHeaderString,(OTA_HEADER_STRING),sizeof(OTA_HEADER_STRING));
    memcpy(otauSampleImage,&sampleOtaHeader,sizeof(sampleOtaHeader));
    memset((otauSampleImage + sizeof(sampleOtaHeader)),
                                        0xA5,
                    (sizeof(otauSampleImage) - sizeof(sampleOtaHeader)));
    imageQueryResp.status = ZCL_SUCCESS_STATUS;
    imageQueryResp.manufacturerId = CS_MANUFACTURER_CODE;
    imageQueryResp.imageType = OTA_IMAGE_TYPE;
    imageQueryResp.currentFirmwareVersion.versionId = (OTA_FILE_VERSION);
    imageQueryResp.imageSize = sampleOtaHeader.totalImageSize;

    uint8_t otauAesEncKey[] = IMAGE_KEY;
    
    CRYPT_AES_KeySet(&aes, (const unsigned char*)&otauAesEncKey, AES_BLOCK_SIZE, NULL/*IV - For ECB*/, AES_ENCRYPTION);
    
//    appSnprintf("B ");
//    for (uint8_t i = 0; i< imageQueryResp.imageSize; i++ )        
//        appSnprintf("0x%x ",otauSampleImage[i]);
//    appSnprintf("\r\n");
    for(int dataCount = sizeof(OTA_HeaderStruct_t); dataCount < imageQueryResp.imageSize; dataCount += AES_BLOCK_SIZE)
    {
        if(dataCount + AES_BLOCK_SIZE > imageQueryResp.imageSize)
        {
            appSnprintf("Dead");
            while(1);
        }
        CRYPT_AES_DIRECT_Encrypt(&aes,(unsigned char*)&otauSampleImage[dataCount], &otauSampleImage[dataCount]);
    }

//    appSnprintf("A ");
//    for (uint8_t i = 0; i< imageQueryResp.imageSize; i++ )     
//        appSnprintf("0x%x ",otauSampleImage[i]);
//    appSnprintf("\r\n");

    cb(&imageQueryResp);
}

void ISD_ImageBlockReq(ZCL_Addressing_t *addressing, ZCL_OtauImageBlockReq_t *data, IsdImageBlockCb_t cb)
{
    (void)addressing;
    (void)data;
    ZCL_OtauImageBlockResp_t blockResp = {};    
    if ((data->fileOffset + data->maxDataSize) > sizeof(otauSampleImage))
        while(1);

    blockResp.status = ZCL_SUCCESS_STATUS;
    blockResp.manufacturerId    = data->manufacturerId;
    blockResp.imageType         = data->imageType;
    blockResp.blockRequestDelay = data->blockRequestDelay;
    blockResp.fileOffset        = data->fileOffset;
    blockResp.firmwareVersion   = data->firmwareVersion;
    
    blockResp.dataSize = (data->maxDataSize > OTAU_MAX_BLOCK_SIZE) ? OTAU_MAX_BLOCK_SIZE : data->maxDataSize;

    memcpy(blockResp.imageData,&otauSampleImage[data->fileOffset],blockResp.dataSize);
    cb(&blockResp);
}

void ISD_UpgradeEndReq(ZCL_Addressing_t *addressing, ZCL_OtauUpgradeEndReq_t *data, IsdUpgradeEndCb_t cb)
{
    (void)addressing;
    (void)data;
    
    ZCL_OtauUpgradeEndResp_t upgradeEndResp;
    
    upgradeEndResp.manufacturerId   = data->manufacturerId;
    upgradeEndResp.imageType        = data->imageType ;
    upgradeEndResp.firmwareVersion  = data->firmwareVersion;
    upgradeEndResp.currentTime      = 1000;
    upgradeEndResp.upgradeTime      = 1005;
    cb(&upgradeEndResp);
}
/* *****************************************************************************
 End of File
 */
