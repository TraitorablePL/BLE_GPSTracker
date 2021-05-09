#include "sdk_common.h"
#include "include/control_service.h"
#include <string.h>
#include "ble_srv_common.h"
#include "ble_conn_state.h"

#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@brief Function for handling the Write event.
 *
 * @param[in]   p_bas       Battery Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_write(control_service_t * p_control_service, ble_evt_t const * p_ble_evt) {

    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

    // Normal write on characteristic
    if (p_evt_write->handle == p_control_service->download_handles.value_handle) {
        //Check what value is set and perform proper job
    }
}

void control_service_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context) {
    if ((p_context == NULL) || (p_ble_evt == NULL)) {
        return;
    }

    control_service_t* p_control_service = (control_service_t *)p_context;

    switch (p_ble_evt->header.evt_id) {

        case BLE_GATTS_EVT_WRITE:
            on_write(p_control_service, p_ble_evt);
            break;

        default:
            // No implementation needed.
            break;
    }
}

static ret_code_t reset_char_add(control_service_t * p_control_service) {
    ret_code_t              err_code;
    ble_add_char_params_t   add_char_params;
    ble_add_descr_params_t  add_descr_params;
    uint8_t                 reset_value;

    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid                = BLE_UUID_BATTERY_LEVEL_CHAR;
    add_char_params.max_len             = sizeof(uint8_t);
    add_char_params.init_len            = sizeof(uint8_t);
    add_char_params.p_init_value        = &reset_value;
    add_char_params.char_props.read     = 1;
    add_char_params.char_props.write    = 1;
    add_char_params.read_access         = SEC_OPEN;
    add_char_params.write_access        = SEC_OPEN;

    err_code = characteristic_add(p_control_service->service_handle,
                                  &add_char_params,
                                  &(p_control_service->reset_handles));
    if (err_code != NRF_SUCCESS){
        return err_code;
    }
    return NRF_SUCCESS;
}

static ret_code_t record_char_add(control_service_t * p_control_service) {
    ret_code_t              err_code;
    ble_add_char_params_t   add_char_params;
    ble_add_descr_params_t  add_descr_params;
    uint8_t                 record_value = 0;

    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid                = BLE_UUID_BATTERY_LEVEL_CHAR;
    add_char_params.max_len             = sizeof(uint8_t);
    add_char_params.init_len            = sizeof(uint8_t);
    add_char_params.p_init_value        = &record_value;
    add_char_params.char_props.read     = 1;
    add_char_params.char_props.write    = 1;
    add_char_params.read_access         = SEC_OPEN;
    add_char_params.write_access        = SEC_OPEN;

    err_code = characteristic_add(p_control_service->service_handle,
                                  &add_char_params,
                                  &(p_control_service->record_handles));
    if (err_code != NRF_SUCCESS){
        return err_code;
    }
    return NRF_SUCCESS;
}

static ret_code_t download_char_add(control_service_t * p_control_service) {
    ret_code_t              err_code;
    ble_add_char_params_t   add_char_params;
    ble_add_descr_params_t  add_descr_params;
    uint8_t                 download_value = 0;

    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid                = BLE_UUID_BATTERY_LEVEL_CHAR;
    add_char_params.max_len             = sizeof(uint8_t);
    add_char_params.init_len            = sizeof(uint8_t);
    add_char_params.p_init_value        = &download_value;
    add_char_params.char_props.read     = 1;
    add_char_params.char_props.write    = 1;
    add_char_params.read_access         = SEC_OPEN;
    add_char_params.write_access        = SEC_OPEN;

    err_code = characteristic_add(p_control_service->service_handle,
                                  &add_char_params,
                                  &(p_control_service->reset_handles));
    if (err_code != NRF_SUCCESS){
        return err_code;
    }
    return NRF_SUCCESS;
}

ret_code_t control_service_init(control_service_t* p_control_service) {

    if (p_control_service == NULL){
        return NRF_ERROR_NULL;
    }

    ret_code_t err_code;
    ble_uuid_t ble_uuid;

    ble_uuid128_t base_uuid = {CONTROL_SERVICE_BASE_UUID};
    sd_ble_uuid_vs_add(&base_uuid, &p_control_service->uuid_type);

    ble_uuid.type = p_control_service->uuid_type;
    ble_uuid.uuid = CONTROL_SERVICE;

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_control_service->service_handle);
    VERIFY_SUCCESS(err_code);

    reset_char_add(p_control_service);
    record_char_add(p_control_service);
    download_char_add(p_control_service);

    return err_code;
}
