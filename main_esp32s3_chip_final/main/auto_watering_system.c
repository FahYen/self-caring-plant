#include "auto_watering_system.h"

// Global variables
static esp_timer_handle_t periodic_timer;
static nvs_handle_t flash_memory;
static uint8_t key = 0;                        // key for Flash read and write

// Function declarations
static void init_water_timer(void);
static void init_water_storage(void);
static void init_pump_gpio(void);
static void reset_readings_storage(void);
static void timer_callback(void* arg);
static void water(void);
static void set_moisture_level(uint8_t moisture_level);
static uint8_t get_average_moisture_level(void);
static void update_key(void);

//creates a timer instance with configs
static void init_water_timer(void) {
    const esp_timer_create_args_t timer_args = {
        .callback = &timer_callback,
        .name = "moisture_sensor_reading",
        .dispatch_method = ESP_TIMER_TASK,
        .skip_unhandled_events = false
    };
    
    ESP_ERROR_CHECK(esp_timer_create(&timer_args, &periodic_timer));
}

// initialize non-volatile storage and set 6 moisture readings to be maximum
static void init_water_storage(void) {
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
    ESP_ERROR_CHECK(nvs_open("moisture", NVS_READWRITE, &flash_memory));
}

// set up pump gpio
static void init_pump_gpio(void) {
    gpio_reset_pin(PUMP_GPIO);
    gpio_set_direction(PUMP_GPIO, GPIO_MODE_OUTPUT);
}

// sets all six moisture reading key-value pairs to MAX_MOISTURE
static void reset_readings_storage(void){
    char key_reset[2];
    for (int i = 0; i < NUM_MOISTURE_READINGS; i++) {
        key_reset[0] = i + '0';
        key_reset[1] = '\0';
        ESP_ERROR_CHECK(nvs_set_u8(flash_memory, key_reset, MAX_MOISTURE));
        ESP_ERROR_CHECK(nvs_commit(flash_memory));
    }
}

// records information about moisture level and decides whether water is needed
static void timer_callback(void* arg) {
    uint8_t current_moisture_level = moisture_read();
    printf("current moisture level on key %d: %d\n", key, current_moisture_level);
    set_moisture_level(current_moisture_level);
    
    update_key();
    
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
    printf("water delay done\n");
    gpio_set_level(PUMP_GPIO, 0);
}

// save moisture reading from snapshot to nvs
static void set_moisture_level(uint8_t moisture_level) {
    char key_set[2];
    key_set[0] = key + '0';
    key_set[1] = '\0';
    ESP_ERROR_CHECK(nvs_set_u8(flash_memory, key_set, moisture_level));
}

// get average moisture readings from nvs
static uint8_t get_average_moisture_level(void) {
    uint16_t sum = 0;
    for (int i = 0; i < NUM_MOISTURE_READINGS; i++) {
        uint8_t current_reading;
        char key_get[2];
        key_get[0] = i + '0';
        key_get[1] = '\0';
        ESP_ERROR_CHECK(nvs_get_u8(flash_memory, key_get, &current_reading));
        printf("key: %d, value: %d\n", i, current_reading);
        sum += current_reading;
    }
    return sum / NUM_MOISTURE_READINGS;
}

// uses rotation to ensure the access key is within bounds
static void update_key(void) {
    key = (key + 1) % NUM_MOISTURE_READINGS;
}

void init_auto_watering_system(void) {
    init_moisture();
    init_water_timer();
    init_water_storage();
    reset_readings_storage();
    init_pump_gpio();
}

void start_auto_watering_system(void) {
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, MOISTURE_CHECK_INTERVAL * 1000000ULL));
}