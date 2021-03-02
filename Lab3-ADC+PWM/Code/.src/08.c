#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "mraa.h"
#include "util.h"

mraa_pwm_context pin_pwm;
int main() {
  float bright = 0.0f;
  pin_pwm = mraa_pwm_init(32);

  mraa_pwm_period_us(pin_pwm, 200);  // 5000hz
  mraa_pwm_enable(pin_pwm, 1);

  while (1) {
    printf("%f\n", bright);
    mraa_pwm_write(pin_pwm, bright);

    if (bright < 1.0f) {
      bright = bright + 0.01f;
    } else {
      bright = 0.0f;
    }
    sleep_ms(10);
  }
}
