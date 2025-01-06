#include "LDR.h"

void init_LDR() {
    init_adc_unit(LDR_IN);
}

uint8_t LDR_read() {
    int Dout = adc_read_Dout(LDR_IN);
    uint8_t result;
    result = (double) Dout / LDR_READ_MAX * 100;
    return result;
}

