@echo off
cd /D C:\Users\aneek\self-caring-plant\z_prototyping\hellow\build\esp-idf\esp_system || (set FAIL_LINE=2& goto :ABORT)
C:\Users\aneek\esp\esp-idf\python_env\idf5.3_py3.11_env\Scripts\python.exe C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/tools/ldgen/ldgen.py --config C:/Users/aneek/self-caring-plant/z_prototyping/hellow/sdkconfig --fragments-list C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/xtensa/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_driver_gpio/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_pm/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_mm/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/spi_flash/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_system/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_system/app.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_common/common.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_common/soc.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_rom/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/hal/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/log/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/heap/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/soc/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_hw_support/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_hw_support/dma/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_hw_support/ldo/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/freertos/linker_common.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/freertos/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/newlib/newlib.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/newlib/system_libs.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_driver_gptimer/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_ringbuf/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_driver_uart/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/app_trace/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_event/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_driver_pcnt/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_driver_spi/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_driver_mcpwm/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_driver_ana_cmpr/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_driver_dac/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_driver_rmt/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_driver_sdm/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_driver_i2c/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_driver_ledc/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_driver_parlio/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/driver/twai/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_phy/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/vfs/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/lwip/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_netif/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/wpa_supplicant/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_wifi/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_adc/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_eth/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_gdbstub/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_psram/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/esp_lcd/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/espcoredump/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/ieee802154/linker.lf;C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/components/openthread/linker.lf --input C:/Users/aneek/self-caring-plant/z_prototyping/hellow/build/esp-idf/esp_system/ld/sections.ld.in --output C:/Users/aneek/self-caring-plant/z_prototyping/hellow/build/esp-idf/esp_system/ld/sections.ld --kconfig C:/Users/aneek/esp/esp-idf/frameworks/esp-idf-v5.3.2/Kconfig --env-file C:/Users/aneek/self-caring-plant/z_prototyping/hellow/build/config.env --libraries-file C:/Users/aneek/self-caring-plant/z_prototyping/hellow/build/ldgen_libraries --objdump C:/Users/aneek/esp/esp-idf/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-objdump.exe || (set FAIL_LINE=3& goto :ABORT)
goto :EOF

:ABORT
set ERROR_CODE=%ERRORLEVEL%
echo Batch file failed at line %FAIL_LINE% with errorcode %ERRORLEVEL%
exit /b %ERROR_CODE%