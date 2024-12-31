#include <stdio.h>
#include "freertos/FreeRTOS.h" // opearting system
#include "esp_adc/adc_oneshot.h" // ADC driver
#include "freertos/task.h"  // vTaskDelay

// the code needs to first convert moisture sensor
// analog voltage to readings with ADC.
double moisture_sensor_reading() {

}

// then it needs to save the result into memory
void write_to_memory(double moisture_reading) {

}

// read the total moisture 
double read_memory() {

}

// clear memory after watering
void erase_memory() {

}

// powe pump for one watering session
void power_pump() {

}


void app_main(void) {

}
