#include <stdio.h>
#include "freertos/FreeRTOS.h" // opearting system
#include "esp_adc/adc_oneshot.h" // ADC driver
#include "freertos/task.h"  // vTaskDelay

void app_main(void)
{
    // a handle to the ADC unit
    // a software abstraction of the ADC hardware
    adc_oneshot_unit_handle_t adc_handle;

    // Settings of the ADC unit
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_2,            // SAR ADC 1
        .ulp_mode = ADC_ULP_MODE_DISABLE, // ultra-low power mode disabled
    };

    // Initialize the ADC unit with the settings
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc_handle));

    // Settings of the ADC channel
    adc_oneshot_chan_cfg_t adc_channel = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };

    // Configure the ADC channel with the settings
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, ADC_CHANNEL_5, &adc_channel));

    while (1) {
        int Dout; // ADC raw digital reading result.
        double Vmax = 3.3; // Maximum ADC value.
        int Dmax = 4095; // Maximum voltage value.
        // which is 12'b111111111111 in binary.
        // Vref in SAR ADC is 3.3V. 
        double Vout; // ADC voltage reading result.

        // Measure the ADC value
        ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, ADC_CHANNEL_5, &Dout));
        Vout = Dout * Vmax / Dmax;
        printf("Dout: %.3f\n", Vout);
        vTaskDelay(portTICK_PERIOD_MS * 2); // two seconds
    }
}
