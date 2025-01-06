#include "SAR_ADC.h"

adc_oneshot_unit_handle_t adc1;
adc_oneshot_unit_handle_t adc2;

void init_adc_unit(gpio_num_t gpio_num) {
    // same ADC channel configuration
    adc_oneshot_chan_cfg_t adc_channel_config = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_12
    };

    // use ADC unit 1
    if (gpio_num < 11) {
        adc_oneshot_unit_init_cfg_t init_config = {
            .unit_id = ADC_UNIT_1,              // SAR ADC 1
            .ulp_mode = ADC_ULP_MODE_DISABLE,   // ultra-low power mode disabled
        };
        // Check if adc unit created is valid
        ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc1));
        ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1, (adc_channel_t)(gpio_num-1), &adc_channel_config));

    // use ADC unit 2
    } else {
        adc_oneshot_unit_init_cfg_t init_config = {
            .unit_id = ADC_UNIT_2,              // SAR ADC 1
            .ulp_mode = ADC_ULP_MODE_DISABLE,   // ultra-low power mode disabled
        };
        // Check if adc unit created is valid
        ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc2));
        ESP_ERROR_CHECK(adc_oneshot_config_channel(adc2, (adc_channel_t)(gpio_num-11), &adc_channel_config));
    }
}

int adc_read_Dout(gpio_num_t gpio_num) {
    int Dout;
    if (gpio_num < 11) {
        ESP_ERROR_CHECK(adc_oneshot_read(adc1, (adc_channel_t)(gpio_num-1), &Dout));
    } else {
        ESP_ERROR_CHECK(adc_oneshot_read(adc2, (adc_channel_t)(gpio_num-11), &Dout));
    }
    return Dout;
}