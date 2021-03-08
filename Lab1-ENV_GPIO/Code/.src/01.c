#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "mraa.h"

int main() {
  mraa_gpio_context gpio;     //在此宣告gpio pin
  gpio = mraa_gpio_init(22);  // 22為按鈕的pin

  mraa_gpio_dir(gpio, MRAA_GPIO_IN);  //宣告這個pin拿來輸入

  int beup = 1;  //確認現在是up還是down的函數
  printf("up\n");
  while (1) {
    if (beup != 1)  //如果從down變up則印出up,(若沒有加此條件,終端會不斷印出up)
    {
      printf("up\n");
      beup = 1;
    }

    if (mraa_gpio_read(gpio) == 0)  //當按鈕按下時pin值會變成0
    {
      printf("down\n");
      beup = 0;
      while (!mraa_gpio_read(gpio));
    }
  }
  mraa_gpio_close(gpio);  //釋放gpio pin
}
