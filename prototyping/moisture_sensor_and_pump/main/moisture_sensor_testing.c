#include <stdio.h>
#include "freertos/FreeRTOS.h" // opearting system
#include "esp_adc/adc_oneshot.h" // ADC driver
#include "freertos/task.h"  // vTaskDelay

static adc_oneshot_unit_handle_t adc_handle;
static adc_unit_t ADC_UNIT = ADC_UNIT_1;
static adc_channel_t ADC_CHANNEL = ADC_CHANNEL_3; // gpio 4 on esp32-s3

void app_main(void) {
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT,            // SAR ADC 1
        .ulp_mode = ADC_ULP_MODE_DISABLE, // ultra-low power mode disabled
    };

    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc_handle));

    adc_oneshot_chan_cfg_t adc_channel = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_12,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, ADC_CHANNEL, &adc_channel));

    while (1) {
        int Dout; // Dmax = 4095
        // lowest reading 1300 in water
        // highest reading 3200 in dry air
        // add to tolerance
        // set lower bound as 1200
        // upper bound as 3300
        // range = 3300 - 1200 = 2100;
        // 2100 = (MAX_READING - MIN_READING)
        // (double) ((MAX_READING - MIN_READING) - (Dout - (MAX_READING - MIN_READING))) / (MAX_READING - MIN_READING) * 100;
        ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, ADC_CHANNEL, &Dout));
        printf("Reading: %d\n", Dout);
        int moisture_percent = (double) (2100 - (Dout - 1200)) / 2100 * 100;
        printf("Percent: %d\n", moisture_percent);
        vTaskDelay(portTICK_PERIOD_MS * 5);
    }

}