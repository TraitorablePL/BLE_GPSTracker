#include "string.h"
#include "stdlib.h"
#include "gps.h"
#include "app_uart.h"
#include "flash_storage.h"
#include "sdk_common.h"
#include "app_fifo.h"
#include "nrf_uart.h"
#include "boards.h"
#include "nrf_error.h"

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

static gps_data_t gps_data;
static uint32_t flash_index;
const uint32_t route_begin_addr = 0x50000;

float latitude_conv(char* token_val, char* token_dir) {
    
    float decimal_degree, degree, minutes, seconds;
    char buffer[20];

    strncpy(buffer, token_val, 2);
    buffer[2] = '\0';
    degree = strtol(buffer, NULL, 10);

    strncpy(buffer, token_val + 2, 2);
    buffer[2] = '\0';
    minutes = strtol(buffer, NULL, 10);

    strncpy(buffer, token_val + 3, 4);
    buffer[0] = '0';
    seconds = 60*strtof(buffer, NULL);
    
    if(token_dir[0] = 'E')
        return degree + minutes/60 + seconds/3600;
    else
        return (degree + minutes/60 + seconds/3600)*(-1);
}

float longitude_conv(char* token_val, char* token_dir) {
    
    float degree, minutes, seconds;
    char buffer[20];

    strncpy(buffer, token_val, 3);
    buffer[3] = '\0';
    degree = strtol(buffer, NULL, 10);

    strncpy(buffer, token_val + 3, 2);
    buffer[3] = '\0';
    minutes = strtol(buffer, NULL, 10);

    strncpy(buffer, token_val + 3, 4);
    buffer[0] = '0';
    seconds = (float)(60*strtof(buffer, NULL));
    
    if(token_dir[0] = 'N')
        return degree + minutes/60 + seconds/3600;
    else
        return (degree + minutes/60 + seconds/3600)*(-1);
}

void set_time_date(char* token_time, char* token_date, char* time_date){
    
    // Hours
    strncpy(time_date, token_time, 2); 
    time_date[2] = ':';

    // Minutes
    strncpy(time_date + 3, token_time + 2, 2);
    time_date[5] = ':';

    // Seconds
    strncpy(time_date + 6, token_time + 4, 2);
    time_date[8] = ' ';

    // Day
    strncpy(time_date + 9, token_date, 2); 
    time_date[11] = '.';

    // Month
    strncpy(time_date + 12, token_date + 2, 2);
    time_date[14] = '.';

    // Year
    time_date[15] = '2';
    time_date[16] = '0';
    strncpy(time_date + 17, token_date + 4, 2);
    time_date[19] = '\0';
}

uint8_t gps_convert_output(uint8_t* str_in, gps_data_t* p_gps_data) {

    char time[] = "215911";
    char date[] = "100621";
    char* p_tokens[13];
    const char delimiter[2] = ",";
    uint8_t index = 0;

    p_tokens[index] = strtok(str_in, delimiter);

    while(p_tokens[index] != NULL) {
        if(index < 10){
            //NRF_LOG_INFO("%d. %s", index, p_tokens[index]);
        }
        p_tokens[++index] = strtok(NULL, delimiter);
    }

    if(!strcmp(p_tokens[2], "A")) {
        // Enable when GPS could connect
        // gps_data->latitude = latitude_conv("5003.8517", "N");
        // gps_data->longitude = longitude_conv("02001.3251", "E");
        // set_time_date(p_tokens[1], p_tokens[9], gps_data->time);
        // NRF_LOG_INFO("Valid GPS Data");
    }
    else {
        //NRF_LOG_INFO("Invalid GPS Data");
    }

    // Test data
    p_gps_data->latitude = latitude_conv("5003.8517", "N");
    p_gps_data->longitude = longitude_conv("02001.3251", "E");
    set_time_date(time, date, p_gps_data->time);

    return 0;
}

void uart_event_handle(app_uart_evt_t * p_event) {
    
    static uint8_t data_array[64];
    static uint8_t index;

    switch (p_event->evt_type){

        case APP_UART_DATA_READY:
            app_uart_get(&data_array[index++]);

            if (data_array[index - 1] == '\n'){
                if (index > 1){
                    if (gps_convert_output(data_array, &gps_data) == NRF_SUCCESS){
                        flash_storage_write(&gps_data, sizeof(gps_data), route_begin_addr + (sizeof(gps_data)*flash_index++));
                        NRF_LOG_INFO("Saved data to flash");
                        //NRF_LOG_INFO("Latitude " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(gps_data.latitude));
                        //NRF_LOG_INFO("Longitude " NRF_LOG_FLOAT_MARKER, NRF_LOG_FLOAT(gps_data.longitude));
                        //NRF_LOG_INFO("Time %s", gps_data.time);
                    }
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

    // TODO Create proper function for sending UART Strings 
    uint8_t counter = 0;
    char init_str1[] = "$PMTK314,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*2B\r\n";
    char init_str2[] = "$PMTK220,10000*2F\r\n";

    while(init_str1[counter] != '\n'){
        while (app_uart_put(init_str1[counter++]) != NRF_SUCCESS);
    }
    while (app_uart_put('\n') != NRF_SUCCESS);

    counter = 0;
    while(init_str2[counter] != '\n'){
        while (app_uart_put(init_str2[counter++]) != NRF_SUCCESS);
    }
    while (app_uart_put('\n') != NRF_SUCCESS);

    NRF_LOG_INFO("Initialization message sent");
}
