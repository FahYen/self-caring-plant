#ifndef ADC_h
#define ADC_h
#include "freertos/FreeRTOS.h"   // opearting system
#include "esp_adc/adc_oneshot.h" // ADC driver
#include "driver/gpio.h"         // gpio_num_t

// set up adc handle with 12db attentuation and 12 bit-width channel
void init_adc_unit(gpio_num_t);
// reads voltage from adc
int adc_read_Dout(gpio_num_t);

#endif
