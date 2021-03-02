#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "mraa.h"

int main() {
  mraa_gpio_context gpio;
  gpio = mraa_gpio_init(18);  //指定gpio pin,18為led的pin

  mraa_gpio_dir(gpio, MRAA_GPIO_OUT);  //設18腳為輸出模式
  while (1) {
    mraa_gpio_write(gpio, 1);  // led亮的時間持續一秒
    sleep(1);
    mraa_gpio_write(gpio, 0);  // led滅的時間持續一秒
    sleep(1);
  }
  mraa_gpio_close(gpio);  //釋放腳位
}
