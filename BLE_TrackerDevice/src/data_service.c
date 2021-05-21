#include "sdk_common.h"
#include "data_service.h"
#include <string.h>
#include "ble_srv_common.h"
#include "ble_conn_state.h"

#include "nrf_log.h"
//NRF_LOG_MODULE_REGISTER();

/**@brief Function for handling the Write event.
 *
 * @param[in]   p_bas       Battery Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
// static void on_write(data_service_t * p_data_service, ble_evt_t const * p_ble_evt) {

//     ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

//     // Normal write on characteristic
//     if (p_evt_write->handle == p_data_service->download_handles.value_handle) {
//         //Check what value is set and perform proper job
//     }
// }

void data_service_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context) {
    if ((p_context == NULL) || (p_ble_evt == NULL)) {
        return;
    }

    data_service_t* p_data_service = (data_service_t *)p_context;

    switch (p_ble_evt->header.evt_id) {

        case BLE_GATTS_EVT_WRITE:
            //on_write(p_data_service, p_ble_evt);
            break;

        default:
            // No implementation needed.
            break;
    }
}

static ret_code_t index_char_add(data_service_t * p_data_service) {
    ret_code_t              err_code;
    ble_add_char_params_t   add_char_params;
    ble_add_descr_params_t  add_descr_params;
    ble_gatts_char_pf_t     char_pf = {
        .format = BLE_GATT_CPF_FORMAT_UINT16
    };
    uint16_t                 index_value;

    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid                    = INDEX_CHARACTERISTC;
    add_char_params.uuid_type               = p_data_service->uuid_type;
    add_char_params.max_len                 = sizeof(uint16_t);
    add_char_params.init_len                = sizeof(uint16_t);
    add_char_params.p_init_value            = (uint8_t*)&index_value;
    add_char_params.char_props.read         = 1;
    add_char_params.char_props.notify       = 1;
    add_char_params.read_access             = SEC_OPEN;
    add_char_params.write_access            = SEC_OPEN;
    add_char_params.cccd_write_access       = SEC_OPEN;
    add_char_params.p_presentation_format   = &char_pf;

    err_code = characteristic_add(p_data_service->service_handle,
                                  &add_char_params,
                                  &(p_data_service->index_handles));
    if (err_code != NRF_SUCCESS){
        return err_code;
    }
    return NRF_SUCCESS;
}

static ret_code_t longitude_char_add(data_service_t * p_data_service) {
    ret_code_t              err_code;
    ble_add_char_params_t   add_char_params;
    ble_add_descr_params_t  add_descr_params;
    ble_gatts_char_pf_t     char_pf = {
        .format = BLE_GATT_CPF_FORMAT_FLOAT32
    };
    float                   longitude_value = 0;

    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid                    = LONGITUDE_CHARACTERISTC;
    add_char_params.uuid_type               = p_data_service->uuid_type;
    add_char_params.max_len                 = sizeof(float);
    add_char_params.init_len                = sizeof(float);
    add_char_params.p_init_value            = (uint8_t*)&longitude_value;
    add_char_params.char_props.read         = 1;
    add_char_params.char_props.notify       = 1;
    add_char_params.read_access             = SEC_OPEN;
    add_char_params.write_access            = SEC_OPEN;
    add_char_params.cccd_write_access       = SEC_OPEN;    
    add_char_params.p_presentation_format   = &char_pf;

    err_code = characteristic_add(p_data_service->service_handle,
                                  &add_char_params,
                                  &(p_data_service->longitude_handles));
    if (err_code != NRF_SUCCESS){
        return err_code;
    }
    return NRF_SUCCESS;
}

static ret_code_t latitude_char_add(data_service_t * p_data_service) {
    ret_code_t              err_code;
    ble_add_char_params_t   add_char_params;
    ble_add_descr_params_t  add_descr_params;
    ble_gatts_char_pf_t     char_pf = {
        .format = BLE_GATT_CPF_FORMAT_FLOAT32
    };
    float                   latitude_value = 0;

    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid                    = LATITUDE_CHARACTERISTC;
    add_char_params.uuid_type               = p_data_service->uuid_type;
    add_char_params.max_len                 = sizeof(float);
    add_char_params.init_len                = sizeof(float);
    add_char_params.p_init_value            = (uint8_t*)&latitude_value;
    add_char_params.char_props.read         = 1;
    add_char_params.char_props.notify       = 1;
    add_char_params.read_access             = SEC_OPEN;
    add_char_params.write_access            = SEC_OPEN;
    add_char_params.cccd_write_access       = SEC_OPEN;
    add_char_params.p_presentation_format   = &char_pf;
; 

    err_code = characteristic_add(p_data_service->service_handle,
                                  &add_char_params,
                                  &(p_data_service->latitude_handles));
    if (err_code != NRF_SUCCESS){
        return err_code;
    }
    return NRF_SUCCESS;
}

static ret_code_t time_char_add(data_service_t * p_data_service) {
    ret_code_t              err_code;
    ble_add_char_params_t   add_char_params;
    ble_add_descr_params_t  add_descr_params;
    ble_gatts_char_pf_t     char_pf = {
        .format = BLE_GATT_CPF_FORMAT_UTF8S
    };
    char time_value[] = "04:45:00 01.09.1939";

    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid                    = TIME_CHARACTERISTC;
    add_char_params.uuid_type               = p_data_service->uuid_type;
    add_char_params.max_len                 = 20*sizeof(char);
    add_char_params.init_len                = 20*sizeof(char);
    add_char_params.p_init_value            = (uint8_t*)time_value;
    add_char_params.char_props.read         = 1;
    add_char_params.read_access             = SEC_OPEN;
    add_char_params.p_presentation_format   = &char_pf;

    err_code = characteristic_add(p_data_service->service_handle,
                                  &add_char_params,
                                  &(p_data_service->time_handles));
    if (err_code != NRF_SUCCESS){
        return err_code;
    }
    return NRF_SUCCESS;
}

ret_code_t data_service_init(data_service_t* p_data_service) {

    if (p_data_service == NULL){
        return NRF_ERROR_NULL;
    }

    ret_code_t err_code;
    ble_uuid_t ble_uuid;

    ble_uuid128_t base_uuid = DATA_SERVICE_BASE_UUID;
    sd_ble_uuid_vs_add(&base_uuid, &p_data_service->uuid_type);

    ble_uuid.type = p_data_service->uuid_type;
    ble_uuid.uuid = DATA_SERVICE;

    NRF_LOG_INFO("Data service");

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_data_service->service_handle);
    VERIFY_SUCCESS(err_code);

    index_char_add(p_data_service);
    longitude_char_add(p_data_service);
    latitude_char_add(p_data_service);
    time_char_add(p_data_service);

    return err_code;
}
