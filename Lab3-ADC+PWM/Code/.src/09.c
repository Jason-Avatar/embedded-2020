
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "mraa.h"
#include "util.h"

void delay(void) { sleep_ms(0.1); }
mraa_gpio_context pin_clk, pin_data, pin_cs;  
mraa_pwm_context pin_pwm;
int main() {
  pin_clk = mraa_gpio_init(12);   // clock pin
  pin_data = mraa_gpio_init(38);  // data pin
  pin_cs = mraa_gpio_init(40);    //pin_cs used to initiate communication with the device
  pin_pwm = mraa_pwm_init(32);    //pwm pin

  mraa_gpio_dir(pin_clk, MRAA_GPIO_OUT);
  mraa_gpio_dir(pin_data, MRAA_GPIO_IN);
  mraa_gpio_dir(pin_cs, MRAA_GPIO_OUT);

  mraa_pwm_period_us(pin_pwm, 200); //5000 Hz
  mraa_pwm_enable(pin_pwm, 1);

  while (1) {
    float result;
    int abc_buffer[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int tens[12] = {2048, 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1};
    mraa_gpio_write(pin_clk, 1);
    mraa_gpio_write(pin_cs, 1);
    delay();

    mraa_gpio_write(pin_cs, 0);
    delay();
    mraa_gpio_write(pin_clk, 0);
    delay();
    for (int SPICount = 0; SPICount < 15; SPICount++) {
      mraa_gpio_write(pin_clk, 0);
      delay();
      mraa_gpio_write(pin_clk, 1);
      abc_buffer[SPICount] = mraa_gpio_read(pin_data);  // read data pin's value into buffer
      delay();
    }
    delay();
    mraa_gpio_write(pin_clk, 0);
    delay();
    mraa_gpio_write(pin_cs, 1);
    result = 0;
    for (int i = 3; i < 15; i++) {  // calculate real voltage value
      result = result + (abc_buffer[i] * tens[i - 3]);
    }
    result = result / 4096;
    printf("%f\n", result);
    mraa_pwm_write(pin_pwm, result);
    sleep_ms(100);
  }
}
