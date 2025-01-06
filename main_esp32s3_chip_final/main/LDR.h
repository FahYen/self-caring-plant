#ifndef LDR_h
#define LDR_h

#include <stdint.h>              // unsinged integer type
#include "freertos/FreeRTOS.h"   // RTOS, gpio_num_t
#include "driver/gpio.h"
#include "SAR_ADC.h"
#define LDR_IN GPIO_NUM_11
#define LDR_READ_MAX 4095           //

// set up LDR sensor at LDR_IN
void init_LDR();
uint8_t LDR_read();

#endif