#include <stdlib.h>

#include "mraa.h"
#include "util.h"

#define I2C_BUS 0

#define MRAA_ASSERT(ret)       \
  do {                         \
    mraa_result_t res = (ret); \
    if (res != MRAA_SUCCESS) { \
      mraa_result_print(res);  \
      exit(EXIT_FAILURE);      \
    }                          \
  } while (0)

int main() {
  mraa_i2c_context i2c = mraa_i2c_init(I2C_BUS);
  if (!i2c) {
    fprintf(stderr, "Cannot initalize I2C bus %d\n", I2C_BUS);
    exit(EXIT_FAILURE);
  }

  MRAA_ASSERT(mraa_i2c_address(i2c, 0x40));
  for (;;) {
    uint8_t buf[2];

    MRAA_ASSERT(mraa_i2c_write_byte(i2c, 0xf3));
    sleep_ms(50);
    mraa_i2c_read(i2c, buf, 2);
    uint16_t temp_raw = (buf[0] << 8) + buf[1];
    double temp = -46.85 + 175.72 * temp_raw / (1 << 16);

    MRAA_ASSERT(mraa_i2c_write_byte(i2c, 0xf5));
    sleep_ms(20);
    mraa_i2c_read(i2c, buf, 2);
    uint16_t hum_raw = (buf[0] << 8) + buf[1];
    double hum = -6.0 + 125.0 * hum_raw / (1 << 16);

    printf("TEMP: %.2f C\tHUM: %.2f %%\n", temp, hum);
    sleep_ms(100);
  }
}