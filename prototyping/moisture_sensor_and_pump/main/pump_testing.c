#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

static uint8_t pump_state = 0;
static gpio_num_t PUMP_GPIO = GPIO_NUM_6;
void app_main(void)
{
    // Configuring GPIO pin
    gpio_reset_pin(PUMP_GPIO);
    gpio_set_direction(PUMP_GPIO, GPIO_MODE_OUTPUT);

    while (1) {
        // GPIO pin doesn't have enough power to power the pump directly
        // nor can it power the relay
        // need a MOSFET transistor as a switch to be powered by GPIO.
        gpio_set_level(PUMP_GPIO, pump_state);
        pump_state = !pump_state;
            printf("switching\n");
            // for some reason portTICK_PERIOD_MS is actually 0.1 second
            vTaskDelay(50* portTICK_PERIOD_MS); // 5 seconds
    }
}