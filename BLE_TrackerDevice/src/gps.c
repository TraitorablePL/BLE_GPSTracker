#include "string.h"
#include "gps.h"
#include "app_uart.h"
#include "flash_storage.h"
#include "sdk_common.h"
#include "app_fifo.h"
#include "nrf_uart.h"
#include "boards.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

// GPS Module Connection
// VIN  ->  VDD
// GND  ->  GND
// TX   ->  P0.08
// RX   ->  P0.06

#define UART_TX_BUF_SIZE                256                                         /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE                256                                         /**< UART RX buffer size. */

// NS EW indicator is not needed when using decimal degree format
typedef struct {
    float latitude;
    float longitude;
    //ns_ew_type_t ns_ew_indicator;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} gps_data_t;

// Converts degree, minutes, seconds value into decimal degree format
uint8_t dms_to_dd_converter(){

}

/* $GPRMC, Time (hhmmss.sss), Status (A - Valid, V - Invalid), Latitude, N/S, Longitude, W/E, don't care, don't care, Date (ddmmyy), don't care, don't care * Checksum \r\n */

uint8_t gps_convert_output(uint8_t* str_in, gps_data_t* gps_data) {

    char* p_tokens[13];
    const char delimiter[2] = ",";
    uint8_t index = 0;

    p_tokens[index] = strtok(str_in, delimiter);

    while( p_tokens[index] != NULL ) {
        if(index < 6){
            NRF_LOG_INFO("%d. %s", index, p_tokens[index]);
        }
        p_tokens[++index] = strtok(NULL, delimiter);
    }

    if(!strcmp(p_tokens[2], "A")) {
        NRF_LOG_INFO("Valid GPS Data");
    }
    else {
        NRF_LOG_INFO("Invalid GPS Data");
    }

    return 0;
}

void uart_event_handle(app_uart_evt_t * p_event) {
    
    static uint8_t data_array[64];
    static uint8_t index;
    // static uint32_t flash_addr = 0x00044000;
    gps_data_t gps_data;

    switch (p_event->evt_type){

        case APP_UART_DATA_READY:
            app_uart_get(&data_array[index++]);

            if (data_array[index - 1] == '\n'){
                if (index > 1){
                    //NRF_LOG_INFO("%s", data_array);
                    gps_convert_output(data_array, &gps_data);
                    // if (gps_convert_output(data_array, &gps_data) == NRF_SUCCESS) {
                    //      flash_storage_write(data_array, index, flash_addr);
                    // }
                }
                index = 0;
            }
            break;

        case APP_UART_COMMUNICATION_ERROR:
            NRF_LOG_ERROR("APP_UART_COMMUNICATION_ERROR")
            APP_ERROR_HANDLER(p_event->data.error_communication);
            break;

        case APP_UART_FIFO_ERROR:
            NRF_LOG_ERROR("APP_UART_FIFO_ERROR")
            APP_ERROR_HANDLER(p_event->data.error_code);
            break;

        default:
            break;
    }
}

/**@brief  Function for initializing the UART module.
 */
void uart_init(void){

    uint32_t                     err_code;
    
    app_uart_comm_params_t const comm_params = {
        .rx_pin_no    = RX_PIN_NUMBER,
        .tx_pin_no    = TX_PIN_NUMBER,
        .rts_pin_no   = RTS_PIN_NUMBER,
        .cts_pin_no   = CTS_PIN_NUMBER,
        .flow_control = APP_UART_FLOW_CONTROL_DISABLED,
        .use_parity   = false,
#if defined (UART_PRESENT)
        .baud_rate    = NRF_UART_BAUDRATE_9600
#else
        .baud_rate    = NRF_UARTE_BAUDRATE_9600
#endif
    };

    APP_UART_FIFO_INIT(&comm_params,
                       UART_RX_BUF_SIZE,
                       UART_TX_BUF_SIZE,
                       uart_event_handle,
                       APP_IRQ_PRIORITY_LOWEST,
                       err_code);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_INFO("Init UART");

    uint8_t counter = 0;
    char init_str[] = "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n";
    while(init_str[counter] != '\n'){
        while (app_uart_put(init_str[counter++]) != NRF_SUCCESS);
    }
    while (app_uart_put('\n') != NRF_SUCCESS);

    NRF_LOG_INFO("Initialization message sent");
}
