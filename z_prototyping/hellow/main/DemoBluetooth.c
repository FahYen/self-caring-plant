#include <stdio.h>
#include "driver/gpio.h"

void app_main(void)
{
  gpio_set_direction(GPIO_NUM_10, GPIO_MODE_INPUT);
}
