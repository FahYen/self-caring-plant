#include <stdio.h>               // Debugging
#include "freertos/FreeRTOS.h"   // MCU OS
#include "freertos/task.h"       // For time delay
#include "esp_adc/adc_oneshot.h" // Sensor reading
#include "nvs_flash.h"           // Flash partition config
#include "nvs.h"                 // Memory read and write
#include "esp_timer.h"           // Timed sensor reading capture
#include "driver/gpio.h"         // Water pump voltage control

// GLOBAL VARIABLES
static adc_oneshot_unit_handle_t adc;
static esp_timer_handle_t periodic_timer;
static nvs_handle_t flash_memory;

static uint8_t key = 0;                           // key for Flash read and write
static uint16_t MAX_MOISTURE = 100;
static int MAX_READING = 3300;                    // in dry air
static int MIN_READING = 1200;                    // submerged in water

// user-defined
static adc_unit_t ADC_UNIT = ADC_UNIT_1;
static adc_channel_t ADC_CHANNEL = ADC_CHANNEL_3; // GPIO4
static gpio_num_t PUMP_GPIO = GPIO_NUM_6;
static uint8_t NUM_READINGS = 6;
static uint8_t WATER_DURATION = 3;                // seconds
static uint8_t MIN_WATER_THRESHOLD = 20;          // threshold is out of 100

// FUNCTION DECLARATIONS
// set up configurations
static void init_adc(void);
static void init_timer(void);
static void init_storage(void);
static void init_pump_gpio(void);
static void reset_readings_storage(void);

// callback functions
static void timer_callback(void *arg);

static void water(void);
static uint8_t measure_moisture_level(void);
static void set_moisture_level(uint8_t moisture_level);
static uint8_t get_average_moisture_level(void);
static void update_key(void);

// FUNCTION DEFINITIONS
// set up adc handle with 12db attentuation and 12 bit-width channel
static void init_adc(void) {
    // Configure ADC unit
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT,              // SAR ADC 1
        .ulp_mode = ADC_ULP_MODE_DISABLE, // ultra-low power mode disabled
    };
    // Check if adc unit created is valid
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc));
    
    // Configure ADC channel
    adc_oneshot_chan_cfg_t adc_channel_config = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_12
    };
    // Check if adc channel created is valid
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc, ADC_CHANNEL, &adc_channel_config));
}

// Creates a timer instance with configs
static void init_timer(void) {
    const esp_timer_create_args_t timer_args = {
        .callback = &timer_callback,
        .name = "moisture_sensor_reading",
        .dispatch_method = ESP_TIMER_TASK,
        .skip_unhandled_events = false
    };
    
    ESP_ERROR_CHECK(esp_timer_create(&timer_args, &periodic_timer));
}

// initialize non-volatile storage and set 6 moisture readings to be maximum
static void init_storage(void) {
    // initialize NVS
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    // check nvs flash was able to initialize
    ESP_ERROR_CHECK(err);

    // open flash memory with "storage" namespace and default NVS partition
    ESP_ERROR_CHECK(nvs_open("storage", NVS_READWRITE, &flash_memory));
}

// set up pump gpio
static void init_pump_gpio(void) {
    // Configuring GPIO pin
    gpio_reset_pin(PUMP_GPIO);
    
    // Set GPIO to output mode
    gpio_set_direction(PUMP_GPIO, GPIO_MODE_OUTPUT);
}

// sets all six moisture reading key-value pairs for 3 days to MAX_MOISTURE
static void reset_readings_storage(void){
    char key_reset[2]; // C string of one character
    for (int i = 0; i < NUM_READINGS; i++) {
        key_reset[0] = i + '0';
        key_reset[1] = '\0';

        // checks MAX_MOISTURE is properly written to flash_memory at key_reset key
        ESP_ERROR_CHECK(nvs_set_u8(flash_memory, key_reset, MAX_MOISTURE));
        
        // ensure flash_memory is written to
        ESP_ERROR_CHECK(nvs_commit(flash_memory));
    }
}

// records information about moisture level and decides whether water is needed
static void timer_callback(void* arg) {
    // measure and write moisture level
    uint8_t current_moisture_level = measure_moisture_level();
    printf("current moisture level on key %d: %d\n", key, current_moisture_level);
    set_moisture_level(current_moisture_level);
    
    // update key
    update_key();
    
    // check if needs to water
    uint8_t average_moisture_level = get_average_moisture_level();
    printf("average moisture level: %d\n", average_moisture_level);
    if (average_moisture_level < MIN_WATER_THRESHOLD) {
        water();
        printf("start resetting storage\n");
        reset_readings_storage();
        printf("done resetting storage\n");
    }
}

// activates pump for time of WATER_DURATION, then turns off
static void water(void) {
    gpio_set_level(PUMP_GPIO, 1);
    printf("water delay start\n");
    vTaskDelay(WATER_DURATION * 10 * portTICK_PERIOD_MS);
    //pdMS_TO_TICKS(WATER_DURATION * 1000)
    //WATER_DURATION * 10 * portTICK_PERIOD_MS)
    printf("water delay done\n");
    gpio_set_level(PUMP_GPIO, 0);
}

// converts voltage reading to moisture percentage
static uint8_t measure_moisture_level(void) {
    int Dout;
    ESP_ERROR_CHECK(adc_oneshot_read(adc, ADC_CHANNEL, &Dout));
    printf("Dout: %d\n", Dout);
    int range = MAX_READING - MIN_READING;
    return (double) (range - (Dout - MIN_READING)) / range * 100;
}

// save moisture reading from snapshot to nvs
static void set_moisture_level(uint8_t moisture_level) {
    char key_set[2];
    // convert key_set to C string char
    key_set[0] = key + '0';
    key_set[1] = '\0';
    
    // checks moisture_level is properly written to flash_memory at key_set key
    ESP_ERROR_CHECK(nvs_set_u8(flash_memory, key_set, moisture_level));
}

// get average moisture readings over 3 days from nvs
static uint8_t get_average_moisture_level(void) {
    uint16_t sum = 0;
    for (int i = 0; i < NUM_READINGS; i++) {
        uint8_t current_reading;
        char key_get[2];
        // convert ket_get to C string char
        key_get[0] = i + '0';
        key_get[1] = '\0';
        // checks nvs properly retrieves value at key_get and saves it in current_reading
        ESP_ERROR_CHECK(nvs_get_u8(flash_memory, key_get, &current_reading));
        printf("key: %d, value: %d\n", i, current_reading);
        sum += current_reading;
    }
    return sum / NUM_READINGS;
}

// uses rotation to ensure the access key is within bounds of the snapshot range
static void update_key(void) {
    key = (key + 1) % 6;  // rotate 0-5
}

void app_main(void) {
    init_adc();
    init_timer();
    init_storage();
    reset_readings_storage();
    init_pump_gpio();

    esp_timer_start_periodic(periodic_timer, 5 * 1000000); // 5 seconds for testing
}