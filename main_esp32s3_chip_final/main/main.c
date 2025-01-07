#include "auto_watering_system.h"
#include "auto_lighting_control.h"

void app_main(void) {
    init_auto_lighting_control();
    init_auto_watering_system();
    start_auto_lighting_control();
    start_auto_watering_system();
}