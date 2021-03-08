#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "mraa.h"

int main() {
  int D[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  mraa_gpio_context DATA, E, CLOCK;
  DATA = mraa_gpio_init(13);   //傳送資料的pin
  E = mraa_gpio_init(15);      //致能
  CLOCK = mraa_gpio_init(16);  //時脈

  mraa_gpio_dir(DATA, MRAA_GPIO_OUT);
  mraa_gpio_dir(E, MRAA_GPIO_OUT);
  mraa_gpio_dir(CLOCK, MRAA_GPIO_OUT);

  int t = 1;  //時間數值
  while (1) {
    if (t == 1)  //在時間t=1時顯示led1亮其他led暗
    {
      D[0] = 1;
      D[1] = 0;
      D[2] = 0;
    } else if (t == 2)  //在時間t=2時顯示led2亮其他led暗
    {
      D[0] = 0;
      D[1] = 1;
      D[2] = 0;
    } else if (t == 3)  //在時間t=3時顯示led3亮其他led暗
    {
      D[0] = 0;
      D[1] = 0;
      D[2] = 1;
    }

    /*
    每次傳數值前把E拉低,傳完數值後把E拉高,每個數值由8個BIT的DATA組成,
        在每次傳送DATA前把CLOCK拉低,DATA傳好後把CLOCK拉高
    */

    mraa_gpio_write(E, 0);  //在傳送數值前把E拉低
    for (int i = 7; i >= 0; i--) {
      mraa_gpio_write(CLOCK, 0);    //在每次傳1 BIT DATA前把CLOCK拉低
      mraa_gpio_write(DATA, D[i]);  //把DATA內的資料給寫入
      mraa_gpio_write(CLOCK, 1);    //在每次傳完1 BIT DATA後把CLOCK拉高
    }

    mraa_gpio_write(E, 1);  //在每次完整傳完8bit的DATA(數值)後,把E拉高
    sleep(1);
    t++;
    if (t > 3)  //當t超過3時回到1(t只有1,2,3,這幾種可能)
      t = 1;
  }

  mraa_gpio_close(DATA);  //釋放gpio pin
  mraa_gpio_close(E);
  mraa_gpio_close(CLOCK);
}
