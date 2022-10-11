/*
 Demo app for using PDS
 */

#include <xc.h>
#include <stddef.h>
#include <string.h>
#include <osal/osal_freertos.h>
#include <nvm\plib_nvm.h>
#include <pds.h>

static uint8_t sampleData[512];
static uint8_t offsetData[50];
enum
{
    APP_ITEM_ID_1  = (PDS_MODULE_APP_OFFSET),
    APP_ITEM_ID_2,
    APP_ITEM_ID_3,
    APP_MAX_ITEMS
};

#define APP_MAX_PDS_ITEMS   (APP_MAX_ITEMS - APP_ITEM_ID_1)

#define MAX_PDS_ITEMS   APP_MAX_PDS_ITEMS

PDS_DECLARE_ITEM(APP_ITEM_ID_1, sizeof(sampleData), sampleData, NULL, NO_ITEM_FLAGS);
PDS_DECLARE_ITEM(APP_ITEM_ID_2, sizeof(sampleData), sampleData, NULL, NO_ITEM_FLAGS);

extern bool PDS_storeOffset(PDS_Operation_Offset_t *item);

void CMCC_Init_icdis_dcdis(uint8_t icdis, uint8_t dcdis)
{
    // Disable CMCC first
    CMCC_REGS->CMCC_CTRL = CMCC_CTRL_CEN(0);
    //cc->CMCC_CTRL = CMCC_CTRL_CEN(0);
  
    // Cache Controller Software Reset and wait the reset done (check status bit)
    CMCC_REGS->CMCC_MCTRL = CMCC_MCTRL_SWRST(1);
    while((CMCC_REGS->CMCC_SR & CMCC_SR_CSTS_Msk) == 1);

    // Enable I & D cache, set cache size to 4KB
    CMCC_REGS->CMCC_CFG = (CMCC_CFG_ICDIS(icdis)  
                    |CMCC_CFG_DCDIS(dcdis)
                    |CMCC_CFG_CSIZESW(CMCC_CFG_CSIZESW_CONF_CSIZE_4KB_Val ));

    // Enable CMCC again
    CMCC_REGS->CMCC_CTRL = CMCC_CTRL_CEN(1);
}

bool IsPDS_OkToWrite(uint16_t bytesToWrite)
{
  bool ret = false;
  //ret = IsBLEOkay(bytes);    // To be implemented in the BLE stack
  //ret = IsZigbeeOkay(bytes); // To be implemented in the ZB stack
  return ret;
}

void pdsDataStoreCallback(PDS_MemId_t memoryId)
{
    /*Indication call back once the Item is written into flash*/
    return;
}

bool pdsUpdateMemoryCallback(PDS_UpdateMemory_t *item)
{
    return true;
}

void vApplicationIdleHook(void)
{
  //if( IsPDS_OkToWrite(BytestoWrite)) //Bytes can be sent via Queue
  //This function performs the actual flash write 
  PDS_StoreItemTaskHandler(); // Do the FLASH write operation
}

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName) {
    (void) pcTaskName;
    (void) pxTask;
 
    /* Run time task stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
    called if a task stack overflow is detected. Note the system/interrupt
    stack is not checked. */
    taskDISABLE_INTERRUPTS();
    for (;;);
}

void appTask(void *p)
{
    while(1)
    {   
        if (PDS_IsAbleToRestore(APP_ITEM_ID_1)) // Check if the item already exits
        {
          // Clearing RAM content, for testing purpose
            memset(sampleData,0,sizeof(sampleData));
          // If it already exists, restore it directly
          if (PDS_Restore(APP_ITEM_ID_1))
          {
              // Successfully restored, Check variable "sampleData" here
            memset(sampleData,(~sampleData[0]),sizeof(sampleData));
            PDS_Store(APP_ITEM_ID_1); // Modify the item and write it again
            PDS_Store(APP_ITEM_ID_2);

            PDS_DeleteAll(false);
              // Reset the board and shall able to restore the data
          }
          else
          {
              // Restore fails
              memset(sampleData,0xa5,sizeof(sampleData));
              PDS_Store(APP_ITEM_ID_1);
          }
        }
        else
        {
            // Item cannot be restored, perform store operation again
            // Execution comes here for the first time
            memset(sampleData,0xa5,sizeof(sampleData));
            
            PDS_Store(APP_ITEM_ID_1);

            PDS_Operation_Offset_t offset;
            offset.id = APP_ITEM_ID_1;
            offset.size = sizeof(offsetData);
            offset.offset = 8;
            offset.ramAddr = offsetData;
            memset(offsetData,0xbd,sizeof(offsetData));
            PDS_storeOffset(&offset);
        }
        vTaskDelay(100); // Release task for 100ms
    }
    
}

int main (void)
{
  CMCC_Init_icdis_dcdis(0, 1);

  NVM_Initialize();
  /* Step 1 - Common to system*/
  PDS_Init(MAX_PDS_ITEMS, 0);

  /*Step 2 - Specific to modules, Registering the call backs*/
  PDS_RegisterWriteCompleteCallback(pdsDataStoreCallback);
  PDS_RegisterUpdateMemoryCallback(pdsUpdateMemoryCallback);
  PDS_AddItemExcpetionFromDeleteAll(APP_ITEM_ID_1);

  if (xTaskCreate(appTask, "PDS W", 0x100, NULL, 1, NULL) != pdPASS)
      while (1);

  vTaskStartScheduler();

  while (1);
  
  return 0;
}
/* *****************************************************************************
 End of File
 */
