#ifndef AUTO_WATERING_SYSTEM_H
#define AUTO_WATERING_SYSTEM_H

#include <stdio.h>               // Debugging
#include "freertos/FreeRTOS.h"   // MCU OS
#include "freertos/task.h"       // For time delay
#include "nvs_flash.h"           // Flash partition config
#include "nvs.h"                 // Memory read and write
#include "esp_timer.h"           // Timed sensor reading capture
#include "driver/gpio.h"         // Water pump voltage control
#include "moisture.h"

// System Configuration
#define MAX_MOISTURE 100
#define MAX_READING 3300                    // in dry air
#define MIN_READING 1200                    // submerged in water

// User-defined Configuration
#define PUMP_GPIO GPIO_NUM_6
#define MIN_WATER_THRESHOLD 20               // threshold is out of 100
#define WATER_DURATION 3                     // time the pump turns on for in seconds
#define NUM_MOISTURE_READINGS 6              // for taking 1 day's average
#define MOISTURE_CHECK_INTERVAL ((uint64_t)12 * 60 * 60)  // Check every 12 hours in seconds

void init_auto_watering_system(void);
void start_auto_watering_system(void);

#endif