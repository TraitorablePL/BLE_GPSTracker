#ifndef FLASH_STORAGE_H__
#define FLASH_STORAGE_H__

void init_flash_storage(void);

void flash_storage_write(void const* data, uint32_t data_size, uint32_t addr);

void flash_storage_read(void* data, uint32_t data_size, uint32_t addr);

void flash_storage_page_erase(uint32_t addr);

#endif