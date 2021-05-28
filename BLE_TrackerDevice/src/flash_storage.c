#include "nrf.h"
#include "nrf_soc.h"
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "nrf_fstorage.h"
#include "nrf_fstorage_sd.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_pwr_mgmt.h"
#include "app_util.h"
#include "nordic_common.h"
#include "flash_storage.h"

static void fstorage_evt_handler(nrf_fstorage_evt_t * p_evt);

NRF_FSTORAGE_DEF(nrf_fstorage_t fstorage) = {
    /* Set a handler for fstorage events. */
    .evt_handler = fstorage_evt_handler,

    /* These below are the boundaries of the flash space assigned to this instance of fstorage.
     * You must set these manually, even at runtime, before nrf_fstorage_init() is called.
     * The function nrf5_flash_end_addr_get() can be used to retrieve the last address on the
     * last page of flash available to write data. */
    .start_addr = 0x44000,
    .end_addr   = 0x47fff,
};

static void fstorage_evt_handler(nrf_fstorage_evt_t * p_evt) {
    
    if (p_evt->result != NRF_SUCCESS) {
        NRF_LOG_INFO("--> Event received: ERROR while executing an fstorage operation.");
        return;
    }

    switch (p_evt->id) {
        case NRF_FSTORAGE_EVT_WRITE_RESULT:
            NRF_LOG_INFO("--> Event received: wrote %d bytes at address 0x%x.",
                         p_evt->len, p_evt->addr);
            break;

        case NRF_FSTORAGE_EVT_ERASE_RESULT:
            NRF_LOG_INFO("--> Event received: erased %d page from address 0x%x.",
                         p_evt->len, p_evt->addr);
            break;

        default:
            break;
    }
}

/**@brief   Helper function to obtain the last address on the last page of the on-chip flash that
 *          can be used to write user data.
 */
uint32_t nrf5_flash_end_addr_get() {
    uint32_t const bootloader_addr = BOOTLOADER_ADDRESS;
    uint32_t const page_sz         = NRF_FICR->CODEPAGESIZE;
    uint32_t const code_sz         = NRF_FICR->CODESIZE;

    return (bootloader_addr != 0xFFFFFFFF ?
            bootloader_addr : (code_sz * page_sz));
}



void print_flash_info(nrf_fstorage_t * p_fstorage) {
    NRF_LOG_INFO("========| flash info |========");
    NRF_LOG_INFO("erase unit: \t%d bytes",      p_fstorage->p_flash_info->erase_unit);
    NRF_LOG_INFO("program unit: \t%d bytes",    p_fstorage->p_flash_info->program_unit);
    NRF_LOG_INFO("==============================");
}

static void wait_for_flash_ready(nrf_fstorage_t const * p_fstorage) {
    /* While fstorage is busy, sleep and wait for an event. */
    while (nrf_fstorage_is_busy(p_fstorage)) {
        if (NRF_LOG_PROCESS() == false) {
            nrf_pwr_mgmt_run();
        }
    }
}

void init_flash_storage(void){

    ret_code_t err;
    nrf_fstorage_api_t* p_fs_api;

    p_fs_api = &nrf_fstorage_sd;

    err = nrf_fstorage_init(&fstorage, p_fs_api, NULL);
    APP_ERROR_CHECK(err);

    print_flash_info(&fstorage);
} 

void flash_storage_read(void* data, uint32_t data_size, uint32_t addr){

    NRF_LOG_INFO("Reading from flash.");

    ret_code_t err = nrf_fstorage_read(&fstorage, addr, data, data_size);
    APP_ERROR_CHECK(err);

    // err = nrf_fstorage_read(&fstorage, addr, data, 10);
    // if (err == NRF_SUCCESS) {
    //     for(uint8_t i = 0; i<10; i++){
    //         NRF_LOG_INFO("Byte %d value: %x", i, data[i]);
    //     }
    // }
}

void flash_storage_write(void const* data, uint32_t data_size, uint32_t addr){
    
    ret_code_t err;

    NRF_LOG_INFO("Writing \"%x\" to flash.", *(uint32_t*)data);
    err = nrf_fstorage_write(&fstorage, addr, data, data_size, NULL);
    APP_ERROR_CHECK(err);

    wait_for_flash_ready(&fstorage);
    NRF_LOG_INFO("Done.");
}

void flash_storage_page_erase(uint32_t addr){
    NRF_LOG_INFO("Erasing page at address 0x%x.", addr);
    ret_code_t err = nrf_fstorage_erase(&fstorage, addr, 1, NULL);
    APP_ERROR_CHECK(err);

    NRF_LOG_INFO("Done.");
}