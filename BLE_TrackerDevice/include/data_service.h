#ifndef DATA_SERVICE_H__
#define DATA_SERVICE_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"
#include "nrf_ble_gatt.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DATA_SERVICE_BASE_UUID {{0x3A, 0x22, 0x4D, 0x70, 0x29, 0x49, 0xA9, 0x93, 0x45, 0x49, 0x40, 0xA8, 0xA9, 0x21, 0xA5, 0x7F}} // 128-bit base UUID Little Endian format

#define DATA_SERVICE 0x0000
#define INDEX_CHARACTERISTC 0x0001
#define LONGITUDE_CHARACTERISTC 0x0002
#define LATITUDE_CHARACTERISTC 0x0003
#define TIME_CHARACTERISTC 0x0004

/**@brief   Macro for defining a data service instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define DATA_SERVICE_DEF(_name)                                                                 \
static data_service_t _name;                                                                    \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                             \
                     DATA_SERVICE_OBSERVER_PRIO,                                                \
                     data_service_on_ble_evt, &_name)

typedef enum {
    INDEX_NOTIFICATION_ENABLED,
    INDEX_NOTIFICATION_DISABLED
} index_notification_t;

typedef enum {
    LONGITUDE_NOTIFICATION_ENABLED,
    LONGITUDE_NOTIFICATION_DISABLED
} longitude_notification_t;

typedef enum {
    LATITUDE_NOTIFICATION_ENABLED,
    LATITUDE_NOTIFICATION_DISABLED
} latitude_notification_t;

/**@brief Data Service structure. This contains various status information for the service. */
typedef struct {
    uint16_t                        conn_handle;
    uint16_t                        service_handle;            
    uint8_t                         uuid_type;
    ble_gatts_char_handles_t        index_handles;
    ble_gatts_char_handles_t        longitude_handles;
    ble_gatts_char_handles_t        latitude_handles;
    ble_gatts_char_handles_t        time_handles;
    index_notification_t            index_notification;
    longitude_notification_t        longitude_notification;
    latitude_notification_t         latitude_notification;
} data_service_t;

ret_code_t data_service_init(data_service_t* p_data_service);

void data_service_on_ble_evt(ble_evt_t const* p_ble_evt, void* p_context);

void index_characteristic_notify(data_service_t* p_data_service, uint16_t* index);

void longitude_characteristic_notify(data_service_t* p_data_service, float* longitude);

void latitude_characteristic_notify(data_service_t* p_data_service, float* latitude);

// TODO Handling of GATT MTU update might be necessary to obtain higher data rates
// void data_service_on_gatt_evt(data_service_t * p_data_service, nrf_ble_gatt_evt_t const * p_gatt_evt);

#ifdef __cplusplus
}
#endif

#endif
