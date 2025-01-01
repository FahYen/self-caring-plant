#include <stdio.h>

#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"

#include "protocol_examples_common.h"
#include "esp_wifi.h"

#define TAG "simple_connect_example"

void app_main(void)
{
  	// System initialization
	ESP_ERROR_CHECK(nvs_flash_init());
	ESP_ERROR_CHECK(esp_netif_init());
	ESP_ERROR_CHECK(esp_event_loop_create_default());

	// Establish Wi-Fi connection
	ESP_ERROR_CHECK(example_connect());

	// Print out Access Point Information
	wifi_ap_record_t ap_info;
	ESP_ERROR_CHECK(esp_wifi_sta_get_ap_info(&ap_info));
	ESP_LOGI(TAG, "--- Access Point Information ---");
	ESP_LOG_BUFFER_HEX("Computer Address", ap_info.bssid, sizeof(ap_info.bssid));
	ESP_LOG_BUFFER_CHAR("SSID", ap_info.ssid, sizeof(ap_info.ssid));
	ESP_LOGI(TAG, "Primary Channel: %d", ap_info.primary);
	ESP_LOGI(TAG, "RSSI: %d", ap_info.rssi);

	// Disconnect from Wi-Fi
	ESP_ERROR_CHECK(example_disconnect());
}
