#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "mraa.h"

int main() {
  mraa_gpio_context gpio, gpio2;
  gpio = mraa_gpio_init(18);
  gpio2 = mraa_gpio_init(22);

  mraa_gpio_dir(gpio, MRAA_GPIO_OUT);
  mraa_gpio_dir(gpio2, MRAA_GPIO_IN);
  clock_t Current_time, Previous_down_time, Previous_up_time;

  Previous_down_time = 0;  // Assuming last down time is so long ago
  Previous_up_time = 0;
  int switch_status = 1;

  while (1) {
    if (mraa_gpio_read(gpio2) == 0) {
      Current_time = clock();
      // IF switch down immediately after it up,it means bounce occurs.
      if ((double)(Current_time - Previous_up_time) / CLOCKS_PER_SEC >= 0.05) {
        if (switch_status == 1) {
          printf("down\n");
          switch_status = 0;
          Previous_down_time = Current_time;
        }
      }
    } else {
      Current_time = clock();
      // IF switch up immediately after it down,it means bounce occurs.
      if ((double)(Current_time - Previous_down_time) / CLOCKS_PER_SEC >=0.05) {
        if (switch_status == 0) {
          printf("up\n");
          switch_status = 1;
          Previous_up_time = Current_time;
        }
      }
    }
  }
}
