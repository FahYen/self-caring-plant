#include "moisture.h"

void init_moisture() {
    init_adc_unit(MOISTURE_IN);
}

uint8_t moisture_read() {
    int Dout = adc_read_Dout(MOISTURE_IN);
    int range = MOISTURE_READ_MAX - MOISTURE_READ_MIN;
    return (double) (range - (Dout - MOISTURE_READ_MIN)) / range * 100;
}