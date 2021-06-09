#include "string.h"
#include "gps.h"
#include "app_uart.h"
#include "flash_storage.h"
#include "sdk_common.h"
#include "app_fifo.h"
#include "nrf_uart.h"
#include "boards.h"

#define UART_TX_BUF_SIZE                256                                         /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE                256                                         /**< UART RX buffer size. */

typedef enum {
    N_E_IND = 0,
    N_W_IND = 1,
    S_E_IND = 2,
    S_W_IND = 3
} ns_ew_type_t;

typedef struct {
    float latitude;
    float longitude;
    ns_ew_type_t ns_ew_indicator;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} gps_data_t;

/* $GPRMC, Time (hhmmss.sss), Status (A - Valid, V - Invalid), Latitude, N/S, Longitude, W/E, don't care, don't care, Date (ddmmyy), don't care, don't care * Checksum \r\n */

uint8_t gps_convert_output(uint8_t * string, gps_data_t* gps_data)
{
    uint8_t i;
    const uint8_t* gprmc_cmd = "$GPRMC";
    for(i = 0; i < 6; i++) {
        if(string[i] != gprmc_cmd[i]) {
            return NRF_ERROR_INVALID_PARAM;
        }
    }
}

void uart_event_handle(app_uart_evt_t * p_event)
{
    static uint8_t data_array[64];
    uint32_t       err_code;
    uint8_t index = 0;
    static uint32_t flash_addr = 0x00044000;
    gps_data_t gps_data;

    switch (p_event->evt_type)
    {
        case APP_UART_DATA_READY:
            app_uart_get(&data_array[index++]);

            if (data_array[index - 1] == '\n')
            {
                if (index > 1)
                {
                    if (gps_convert_output(data_array, &gps_data) == NRF_SUCCESS) {
                        flash_storage_write(data_array, index, flash_addr);
                    }
                }

                index = 0;
            }
            break;

        case APP_UART_COMMUNICATION_ERROR:
            APP_ERROR_HANDLER(p_event->data.error_communication);
            break;

        case APP_UART_FIFO_ERROR:
            APP_ERROR_HANDLER(p_event->data.error_code);
            break;

        default:
            break;
    }
}
/**@snippet [Handling the data received over UART] */


/**@brief  Function for initializing the UART module.
 */
/**@snippet [UART Initialization] */
static void uart_init(void)
{
    uint32_t                     err_code;
    
    app_uart_comm_params_t const comm_params =
    {
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
    printf("$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
}
/**@snippet [UART Initialization] */ 
