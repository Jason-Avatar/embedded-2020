#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "mraa.h"

int main() {
  mraa_gpio_context gpio, gpio2;  //在此宣告gpio pin
  gpio = mraa_gpio_init(18);      //指定gpio pin,18為led的pin
  gpio2 = mraa_gpio_init(22);     // 22為按鈕的pin

  mraa_gpio_dir(gpio, MRAA_GPIO_OUT);  //宣告這個pin拿來輸出
  mraa_gpio_dir(gpio2, MRAA_GPIO_IN);  //宣告這個pin拿來輸入

  int beup = 1;  //用來確認現在是up還是down的值
  mraa_gpio_write(gpio, 0);
  while (1) {
    if (beup != 1)  //如果從down變up則印出up,(若沒有加此條件,終端會不斷印出up)
    {
      mraa_gpio_write(gpio, 0);
      beup = 1;
    }

    if (mraa_gpio_read(gpio2) == 0)  //當按鈕按下時pin值會變成0
    {
      mraa_gpio_write(gpio, 1);
      beup = 0;
      while (1)  //一值亮直到按鈕鬆開
      {
        if (mraa_gpio_read(gpio2) == 1) break;
      }
    }
  }
  mraa_gpio_close(gpio);  //釋放gpio pin
  mraa_gpio_close(gpio2);
}
