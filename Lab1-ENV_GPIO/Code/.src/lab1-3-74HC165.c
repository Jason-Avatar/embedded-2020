/**
 * @file
 * Read serial input from GPIO
 *
 * Read and print status of switches SW2, SW3 and SW4, which are connected to
 * the 74HC165 chip.
 *
 * Datasheet:
 * https://assets.nexperia.com/documents/data-sheet/74HC_HCT165.pdf
 */

#include <signal.h>
#include <stdint.h>
#include <time.h>
#include "mraa.h"
#include "upboard_hat.h"
#include "util.h"

volatile sig_atomic_t stopped = 0;

void int_handler(int sig) {
  printf("Received signal %d\n", sig);
  stopped = 1;
}

int main() {
  int switch_status[8] = {0};
  // PL: asynchronous parallel load input (active LOW)
  mraa_gpio_context pin_pl = mraa_gpio_init(UP_HAT_74HC165_PL);
  // Q7: serial output from the last stage
  mraa_gpio_context pin_data = mraa_gpio_init(UP_HAT_74HC165_Q7);
  // CE: clock enable input (active LOW)
  mraa_gpio_context pin_ce = mraa_gpio_init(UP_HAT_74HC165_CE);
  // CP: clock input (LOW-to-HIGH edge-triggered)
  mraa_gpio_context pin_clk = mraa_gpio_init(UP_HAT_74HC165_CP);

  if (!(pin_pl && pin_data && pin_ce && pin_clk)) {
    fprintf(stderr, "Failed to initalize GPIO. Did you run with sudo?\n");
    return EXIT_FAILURE;
  }

  mraa_gpio_dir(pin_pl, MRAA_GPIO_OUT);
  mraa_gpio_dir(pin_data, MRAA_GPIO_IN);
  mraa_gpio_dir(pin_ce, MRAA_GPIO_OUT);
  mraa_gpio_dir(pin_clk, MRAA_GPIO_OUT);

  signal(SIGINT, int_handler);
  while (!stopped) {
  
    /* modify section below this line */
    
    mraa_gpio_write(pin_ce, XXXXXXXXXXX);  // disable clk input
    sleep_ns(1000);
    mraa_gpio_write(pin_XX, XXXXXXXXXXX);  // enable parallel data input
    sleep_ns(1000);
    mraa_gpio_write(pin_pl, XXXXXXXXXXX);  // disable & hold parallel data input
    sleep_ns(1000);
    mraa_gpio_write(pin_XX, XXXXXXXXXXX);  // enable clk input
    sleep_ns(1000);

    for (int i = 0; i < 8; i++) {
      mraa_gpio_write(pin_clk, 0);  // unset clk signal
      sleep_ns(1000);
      switch_status[i] =
          mraa_gpio_read(pin_data);  // read one bit data from pin_data
      mraa_gpio_write(pin_XX, XXXXXXXXXXXX);   // set clk signal
      sleep_ns(1000);
    }
    mraa_gpio_write(pin_clk, 0);  // unset clk signal
    sleep_ns(1000);
    
    /* modify section above this line */
    
    /* modify section below this line to satisfy ex2*/
    
    // print switch status
    
    /* modify section above this line to satisfy ex2*/
    
    sleep_ms(100);
  }

  mraa_gpio_close(pin_pl);
  mraa_gpio_close(pin_data);
  mraa_gpio_close(pin_ce);
  mraa_gpio_close(pin_clk);
}
