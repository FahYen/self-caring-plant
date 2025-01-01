idf_component_register(SRCS "wifi.c"
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES "nvs_flash" "esp_wifi"
                    REQUIRES esp_event esp_netif)
