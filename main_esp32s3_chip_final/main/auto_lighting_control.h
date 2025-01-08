#ifndef AUTO_LIGHTING_CONTROL_H
#define AUTO_LIGHTING_CONTROL_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"           // Flash partition config
#include "nvs.h"                 // Memory read and write
#include "esp_timer.h"
#include "driver/gpio.h"
#include "LDR.h"

// Configuration
#define LIGHT_GPIO GPIO_NUM_3            // gpio for artifical light control
#define MIN_LIGHT_THRESHOLD 30           // Min average light reception to turn on artifical light
// #define LIGHT_ON_DURATION (8 * 60 * 60)  // 8 hours in seconds
// #define NUM_LIGHT_READINGS 96         // for taking 1 day's average
// #define LIGHT_CHECK_INTERVAL (15 * 60)   // Check every 15 minutes in seconds
#define LIGHT_ON_DURATION 6  // 8 hours in seconds
#define NUM_LIGHT_READINGS 6         // for taking 1 day's average
#define LIGHT_CHECK_INTERVAL 2   // Check every 15 minutes in seconds

void init_auto_lighting_control(void);
void start_auto_lighting_control(void);

#endif