/** @file */
#include <stdint.h>

#include "mraa.h"
#include "util.h"

// MAX7219 timings in nanoseconds

/** DIN Setup Time */
#define T_DS 25
/** CLK Pulse Width High */
#define T_CH 50
/** CLK Pulse Width Low */
#define T_CL 50
/** Minimum CS or LOAD Pulse High */
#define T_CSW 50

mraa_gpio_context pin_cs, pin_din, pin_clk;

void send_byte(uint8_t d) {
  for (int i = 7; i >= 0; --i) {
    mraa_gpio_write(pin_clk, 0);
    sleep_ns(T_CL - T_DS);
    mraa_gpio_write(pin_din, (d >> i) & 1u);
    sleep_ns(T_DS);
    mraa_gpio_write(pin_clk, 1);
    sleep_ns(T_CH);
  }
}

void write_reg(uint8_t addr, uint8_t data) {
  mraa_gpio_write(pin_clk, 1);
  mraa_gpio_write(pin_cs, 0);
  send_byte(addr);
  send_byte(data);
  mraa_gpio_write(pin_clk, 0);
  mraa_gpio_write(pin_cs, 1);
  sleep_ns(T_CSW);
}

int main() {
  pin_cs = mraa_gpio_init(24);
  pin_din = mraa_gpio_init(19);
  pin_clk = mraa_gpio_init(23);

  if (!(pin_cs && pin_din && pin_clk)) {
    fprintf(stderr, "Failed to initalize GPIO\n");
    return EXIT_FAILURE;
  }

  mraa_gpio_dir(pin_cs, MRAA_GPIO_OUT);
  mraa_gpio_dir(pin_din, MRAA_GPIO_OUT);
  mraa_gpio_dir(pin_clk, MRAA_GPIO_OUT);

  write_reg(0x0c, 0x01);  // leave shutdown mode
  write_reg(0x0f, 0x00);  // turn off display test
  write_reg(0x09, 0x00);  // set decode mode: no decode
  write_reg(0x0b, 0x07);  // set scan limit to full
  write_reg(0x0a, 0x01);  // set brightness (duty cycle = 3/32)

  uint8_t x = 1;
  for (;;) {
    for (int i = 8; i >= 1; --i) {
      write_reg(i, x);
    }
    x = x < (1 << 7) ? x << 1 : 1;
    sleep_ms(100);
  }
}
