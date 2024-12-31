You must enable PSRAM to use the ESP32 camera drive
This can be done through (a) menuconfig or (b)
adding the following line to the sdkconfig:
CONFIG_ESP32_SPIRAM_SUPPORT=y

This code sets up a web server on an ESP32-CAM module for live streaming video over the local network using esp-idf framework