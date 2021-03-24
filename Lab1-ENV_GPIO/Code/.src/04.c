#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "mraa.h"
#include "util.h"
mraa_gpio_context pin_pl, pin_data, pin_ce, pin_clk;  //宣告gpio pin

void delay(void) { sleep_ms(0.1); }

int main() {
  pin_pl = mraa_gpio_init(35);    // 35為並行輸入腳
  pin_data = mraa_gpio_init(37);  //傳送資料的pin

  pin_ce = mraa_gpio_init(31);  // 31為致能

  pin_clk = mraa_gpio_init(29);  // 29時脈腳

  mraa_gpio_dir(pin_pl, MRAA_GPIO_OUT);  //設定腳位為輸入或輸出
  mraa_gpio_dir(pin_data, MRAA_GPIO_IN);
  mraa_gpio_dir(pin_ce, MRAA_GPIO_OUT);
  mraa_gpio_dir(pin_clk, MRAA_GPIO_OUT);

  while (1) {
    mraa_gpio_write(pin_ce, 1);  // clock enable input (active LOW)
    delay();
    mraa_gpio_write(pin_pl, 0);  //並行加載數據PL為低電壓
    delay();
    mraa_gpio_write(pin_pl, 1);  //串行移位PL為高電壓
    delay();
    mraa_gpio_write(pin_ce, 0);  // clock enable input (active LOW)
    delay();

    for (int SPICount = 0; SPICount < 8; SPICount++) {
      mraa_gpio_write(pin_clk, 0);
      delay(); /*讀8個按鍵狀態，upboard只使用3個*/
      int c = mraa_gpio_read(pin_data);
      printf("%d %d\n", SPICount, c);
      mraa_gpio_write(pin_clk, 1);
      delay();
    }

    delay();
    mraa_gpio_write(pin_clk, 0);
    delay();
    mraa_gpio_write(pin_ce, 1);
    sleep_ms(100);
  }
}
