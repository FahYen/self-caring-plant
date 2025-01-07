#ifndef MOISTURE_H
#define MOISTURE_H

#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "SAR_ADC.h"

// Example pin/channel and ranges based on auto_watering_system.c
#define MOISTURE_IN          GPIO_NUM_4
#define MOISTURE_READ_MAX    3300
#define MOISTURE_READ_MIN    1200

void init_moisture();
uint8_t moisture_read();

#endif