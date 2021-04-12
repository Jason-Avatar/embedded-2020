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
      
      /* modify section below this line */
      
      // IF switch down immediately after it up,it means bounce occurs.
      // hint: not immediately can be represent to
      // (double)(Current_time - Previous_up_time) / CLOCKS_PER_SEC >= 0.05
      // after state change,you should upload Previous_down_time by Current_time
      if (XXXXXXXXXXXXXXXXXXXX) {
        if (switch_status == XXXXXXXXXXXXXXXX) {
          printf("down\n");
          switch_status = XXXXXXXXXXXXXXXXX;
          // after state change,you should upload Previous_down_time by Current_time
          UPDATE_SOMETHING_HERE;
        }
      }
      
      /* modify section above this line */
      
    } else {
      Current_time = clock();
      
      /* modify section below this line */
      
      // IF switch up immediately after it down,it means bounce occurs.
      if (XXXXXXXXXXXXXXXXXXXXXXXX) {
        if (switch_status == XXXXXXXXXXXXXXXXXXXXXXXXXX) {
          printf("up\n");
          switch_status = XXXXXXXXXXXXXXXX;
          // after state change,you should upload Previous_down_time by Current_time
          UPDATE_SOMETHING_HERE;
        }
      }
      
      /* modify section above this line */
    }
  }
}
