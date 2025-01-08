#include "auto_lighting_control.h"

// Global variables
static esp_timer_handle_t periodic_timer;
static esp_timer_handle_t light_off_timer;
static nvs_handle_t flash_memory;
static uint8_t key = 0;                        // key for Flash read and write

static void init_light_timer(void);
static void init_light_storage(void);
static void init_light_gpio(void);
static void reset_readings_storage(void);
static void timer_callback(void* arg);
static void light_off_callback(void* arg);
static void turn_on_light(void);
static void turn_off_light(void);
static void set_light_level(uint8_t light_level);
static uint8_t get_average_light_level(void);
static void update_key(void);

// Creates timer instances with configs
static void init_light_timer(void) {
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &timer_callback,
        .name = "light_sensor_reading",
        .dispatch_method = ESP_TIMER_TASK,
        .skip_unhandled_events = false
    };
    
    const esp_timer_create_args_t light_off_timer_args = {
        .callback = &light_off_callback,
        .name = "light_off_timer",
        .dispatch_method = ESP_TIMER_TASK,
        .skip_unhandled_events = false
    };
    
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_create(&light_off_timer_args, &light_off_timer));
}

// initialize non-volatile storage and set readings to be maximum
static void init_light_storage(void) {
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
    ESP_ERROR_CHECK(nvs_open("light_storage", NVS_READWRITE, &flash_memory));
}

// set up light control gpio
static void init_light_gpio(void) {
    gpio_reset_pin(LIGHT_GPIO);
    gpio_set_direction(LIGHT_GPIO, GPIO_MODE_OUTPUT);
}

// sets all light reading key-value pairs to maximum
static void reset_readings_storage(void) {
    char key_reset[4];
    for (int i = 0; i < NUM_LIGHT_READINGS; i++) {
        sprintf(key_reset, "%d", i);
        ESP_ERROR_CHECK(nvs_set_u8(flash_memory, key_reset, 100));
        ESP_ERROR_CHECK(nvs_commit(flash_memory));
    }
}

// records light level and decides whether artificial light is needed
static void timer_callback(void* arg) {
    uint8_t current_light_level = LDR_read();
    printf("current light level on key %d: %d\n", key, current_light_level);
    set_light_level(current_light_level);
    
    update_key();
    
    uint8_t average_light_level = get_average_light_level();
    printf("average light level: %d\n", average_light_level);
    if (average_light_level < MIN_LIGHT_THRESHOLD) {
        turn_on_light();
        esp_timer_stop(light_off_timer);
        ESP_ERROR_CHECK(esp_timer_start_once(light_off_timer, LIGHT_ON_DURATION * 1000000ULL));
    }
}

// callback to turn off light after duration
static void light_off_callback(void* arg) {
    printf("reached one shot timer call back");
    turn_off_light();
}

static void turn_on_light(void) {
    gpio_set_level(LIGHT_GPIO, 1);
    printf("Light turned on\n");
}

static void turn_off_light(void) {
    gpio_set_level(LIGHT_GPIO, 0);
    printf("Light turned off\n");
}

// save light reading from snapshot to nvs
static void set_light_level(uint8_t light_level) {
    char key_set[4];
    sprintf(key_set, "%d", key);
    ESP_ERROR_CHECK(nvs_set_u8(flash_memory, key_set, light_level));
    ESP_ERROR_CHECK(nvs_commit(flash_memory));
}

// get average light readings from nvs
static uint8_t get_average_light_level(void) {
    uint32_t sum = 0;
    for (int i = 0; i < NUM_LIGHT_READINGS; i++) {
        uint8_t current_reading;
        char key_get[4];
        sprintf(key_get, "%d", i);
        ESP_ERROR_CHECK(nvs_get_u8(flash_memory, key_get, &current_reading));
        printf("key: %d, value: %d\n", i, current_reading);
        sum += current_reading;
    }
    return sum / NUM_LIGHT_READINGS;
}

// uses rotation to ensure the access key is within bounds
static void update_key(void) {
    key = (key + 1) % NUM_LIGHT_READINGS;
}

void init_auto_lighting_control(void) {
    init_LDR();
    init_light_timer();
    init_light_storage();
    reset_readings_storage();
    init_light_gpio();
}

void start_auto_lighting_control(void) {
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LIGHT_CHECK_INTERVAL * 1000000ULL));
}