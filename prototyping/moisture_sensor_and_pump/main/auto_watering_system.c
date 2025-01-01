#include <stdio.h>               // Debugging
#include "freertos/FreeRTOS.h"   // MCU OS
#include "esp_adc/adc_oneshot.h" // Sensor reading
#include "nvs_flash.h"           // Flash partition config
#include "nvs.h"                 // Memory read and write
#include "esp_timer.h"           // Timed sensor reading capture
#include "driver/gpio.h"         // Water pump voltage control

// GLOBAL VARIABLES
static adc_oneshot_unit_handle_t adc;
static esp_timer_handle_t period_timer;
static nvs_handle_t flash_memory;

static uint8_t key = 0;              // key for Flash read and write
static uint16_t MAX_MOISTURE = 1300;
static uint16_t MIN_MOISTRUE = 3150;

