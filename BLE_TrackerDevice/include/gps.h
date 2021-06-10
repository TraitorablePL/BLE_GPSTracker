#ifndef GPS_H__
#define GPS_H__

typedef struct {
    float latitude;
    float longitude;
    char time[20];
} gps_data_t;

void uart_init();

#endif