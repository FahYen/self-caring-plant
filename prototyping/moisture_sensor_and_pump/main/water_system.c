#include <stdio.h>
#include "freertos/FreeRTOS.h" // opearting system
#include "esp_adc/adc_oneshot.h" // ADC driver
#include "freertos/task.h"  // vTaskDelay
#include "nvs_flash.h" // flash partitioning init
#include "nvs.h" // read and write to flash
#include "esp_timer.h" // for reading twice a day
#include "driver/gpio.h" // for powering pumps

// Function declarations
// ADC functions
static void init_adc(void);
int read_moisture_sensor(void);

// Timer functions
static void init_timer(void);
static void timer_callback(void* arg);

// Storage functions
static void init_storage(void);
static void reset_readings_storage(void);
static void update_key(void);
void write_to_memory(uint8_t moisture_reading);
uint8_t read_memory(void);

// Pump control functions
void configure_pump_pin(void);
void power_pump(void);

// global types
static adc_oneshot_unit_handle_t adc_handle;
static esp_timer_handle_t periodic_timer;
static nvs_handle_t flash_memory;
static uint8_t key = 0;

// to be fine-tuned or user set
static uint8_t MAX_MOISTURE = 100;
static uint8_t MIN_MOISTURE = 20;
static uint8_t NUM_READINGS = 6;
static adc_unit_t ADC_UNIT = ADC_UNIT_2;
static adc_channel_t ADC_CHANNEL = ADC_CHANNEL_5;
static gpio_num_t PUMP_POWER_PIN = GPIO_NUM_4; //
static uint32_t PUMP_TIME = 3; // how long pump runs each time (seconds)

// update key rotation function
static void update_key(void) {
    key = (key + 1) % 6;  // rotate 0-5
}

// when it's time to check moisture level
static void timer_callback(void* arg) {
    // first read current moisture value
    uint8_t current_reading = read_moisture_sensor();
    // store the value into key
    write_to_memory(current_reading);
    // update key
    update_key();
    // check if past 3 days
    uint8_t three_days_average = read_memory();
    // if past three days have been dry
    if (three_days_average < MIN_MOISTURE) {
        // water
        power_pump();
        // reset 6 values
        reset_readings_storage();
    }
}

static void init_timer() {
    const esp_timer_create_args_t timer_args = {
        .callback = &timer_callback, // function that runs when time is up
        .name = "moisture_reading",
        .dispatch_method = ESP_TIMER_TASK,
        .skip_unhandled_events = false
    };

    ESP_ERROR_CHECK(esp_timer_create(&timer_args, &periodic_timer));
}

// initialize non-volatile storage and set 6 moisture readings to be maximum
static void init_storage() {
    // initialize NVS
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );

    ESP_ERROR_CHECK(nvs_open("storage", NVS_READWRITE, &flash_memory));
}

// set 6 moisture readings to be maximum
static void reset_readings_storage() {
    char key_reset[2]; // C type string: i + '\0'
    for (int i = 0; i < NUM_READINGS; i++) { // 0 to 5
        key_reset[0] = i + '0';
        key_reset[1] = '\0';
        ESP_ERROR_CHECK(nvs_set_u8(flash_memory, key_reset, MAX_MOISTURE));
        ESP_ERROR_CHECK(nvs_commit(flash_memory));
    }
}

static void init_adc() {
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT,
        .ulp_mode = ADC_ULP_MODE_DISABLE
    };

    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc_handle));

    adc_oneshot_chan_cfg_t adc_channel = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_12
    };

    // you can configure many channels
    // here only one is needed, because we are only reading moisture
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, ADC_CHANNEL, &adc_channel));
}

// the code needs to first convert moisture sensor
// analog voltage to readings with ADC.
int read_moisture_sensor() {
    double reading;

    int Dout;
    double Vmax = 3.3; // Vref in SAR ADC
    int Dmax = 0b111111111111; // determined by bitwidth configured in init_adc
    // bitwidth determines precision in approximation

    // reading from pre-configured channel 5.
    ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, ADC_CHANNEL, &Dout));
    reading = Dout * Vmax / Dmax;

    return reading * 100;
}


// then it needs to save the result into memory
void write_to_memory(uint8_t moisture_reading) {
    char key_write[2];
    key_write[0] = key + '0';
    key_write[1] = '\0';
    ESP_ERROR_CHECK(nvs_set_u8(flash_memory, key_write, moisture_reading));
}

// read the total moisture 
uint8_t read_memory() {
    uint16_t sum = 0;
    for (int i = 0; i < NUM_READINGS; i++) {
        uint8_t current_reading;
        char key_read[2];
        key_read[0] = i + '0';
        key_read[1] = '\0';
        ESP_ERROR_CHECK(nvs_get_u8(flash_memory, key_read, &current_reading));
        sum += current_reading;
    }
    return sum / NUM_READINGS;
}

void configure_pump_pin() {
    gpio_reset_pin(PUMP_POWER_PIN);
    gpio_set_direction(PUMP_POWER_PIN, GPIO_MODE_OUTPUT);
}

// power pump for one watering session
void power_pump() {
    gpio_set_level(PUMP_POWER_PIN, 1);
    vTaskDelay(PUMP_TIME * 1000);
    gpio_set_level(PUMP_POWER_PIN, 1);
}


void app_main(void) {
    init_adc();
    init_timer();
    init_storage();
    reset_readings_storage();
    configure_pump_pin();

    esp_timer_start_periodic(periodic_timer, 10 * 1000000); // 10 seconds for testing
}
