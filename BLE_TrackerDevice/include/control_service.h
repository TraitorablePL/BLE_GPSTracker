#ifndef CONTROL_SERVICE_H__
#define CONTROL_SERVICE_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"
#include "nrf_ble_gatt.h"

#ifdef __cplusplus 
extern "C" {
#endif

#define CONTROL_SERVICE_BASE_UUID {{0xBA, 0x9F, 0xE0, 0x3D, 0x4E, 0x59, 0xA0, 0x9E, 0x09, 0x4B, 0x7C, 0x53, 0xB4, 0xD9, 0xDE, 0x54}}

#define CONTROL_SERVICE 0x0000
#define RESET_CHARACTERISTC 0x0001
#define RECORD_CHARACTERISTC 0x0002
#define DOWNLOAD_CHARACTERISTC 0x0003

/**@brief   Macro for defining a control service instance.
 *
 * @param   _name   Name of the instance.
 */
#define CONTROL_SERVICE_DEF(_name)                                                                 \
static control_service_t _name;                                                                    \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                \
                     CONTROL_SERVICE_OBSERVER_PRIO,                                                \
                     control_service_on_ble_evt, &_name)

struct control_service_s {
    uint16_t                        conn_handle;
    uint16_t                        service_handle;
    uint8_t                         uuid_type;
    ble_gatts_char_handles_t        reset_handles;
    ble_gatts_char_handles_t        record_handles;
    ble_gatts_char_handles_t        download_handles;
};

// Forward declaration of the control_service_t type.
typedef struct control_service_s control_service_t;

/**@brief Function for initializing the Control Service.
 *
 * @param[out]  p_control_service       Control Service structure. This structure will have to be supplied by
*                                       the application. It will be initialized by this function, and will later
*                                       be used to identify this particular service instance.
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
ret_code_t control_service_init(control_service_t * p_control_service);

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Control Service.
 *
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 * @param[in]   p_context   Control Service structure.
 */
void control_service_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);

#ifdef __cplusplus
}
#endif

#endif // CONTROL_SERVICE_H__
