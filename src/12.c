#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mraa.h"
#include "util.h"

#define SERIAL_DEVICE "/dev/ttyS0"
#define MAX_LINE_LENGTH 500
#define I2C_BUS 0

mraa_i2c_context i2c;

/**
 * Read a string terminated by CR, into buf, with length at most buf_size,
 * while echoing the input
 */
void echo_readline(int fd, char *buf, int buf_size) {
  struct pollfd fds = {
      .fd = fd,
      .events = POLLIN,
  };
  int chars_read = 0;
  for (;;) {
    poll(&fds, 1, -1);
    char c;
    if (read(fd, &c, 1) != 1) {
      perror("read");
    }
    if (write(fd, &c, 1) != 1) {
      perror("write");
    }
    if (c == '\r' || c == '\n') {
      c = '\n';
      if (write(fd, &c, 1) != 1) {
        perror("write");
      }
      buf[chars_read] = '\0';
      return;
    }
    if (chars_read + 1 >= buf_size) continue;
    buf[chars_read++] = c;
  }
}

double read_temperature(mraa_i2c_context i2c) {
  uint8_t buf[2];

  mraa_i2c_write_byte(i2c, 0xf3);
  sleep_ms(50);
  mraa_i2c_read(i2c, buf, 2);
  uint16_t temp_raw = (buf[0] << 8) + buf[1];
  return -46.85 + 175.72 * temp_raw / (1 << 16);
}

double read_humidity(mraa_i2c_context i2c) {
  uint8_t buf[2];

  mraa_i2c_write_byte(i2c, 0xf5);
  sleep_ms(20);
  mraa_i2c_read(i2c, buf, 2);
  uint16_t hum_raw = (buf[0] << 8) + buf[1];
  return -6.0 + 125.0 * hum_raw / (1 << 16);
}

int main() {
  int fd = open(SERIAL_DEVICE, O_RDWR | O_NOCTTY);
  if (fd == -1) {
    perror("open_port: Unable to open " SERIAL_DEVICE " - ");
  }

  i2c = mraa_i2c_init(I2C_BUS);
  if (!i2c) {
    fprintf(stderr, "Cannot initalize I2C bus %d\n", I2C_BUS);
    exit(EXIT_FAILURE);
  }
  mraa_i2c_address(i2c, 0x40);

  char buf[MAX_LINE_LENGTH];
  dprintf(fd, "Enter 'temp?' for temperature, 'hum?' for humidity\r\n");
  for (;;) {
    dprintf(fd, "> ");
    echo_readline(fd, buf, MAX_LINE_LENGTH);
    puts(buf);
    if (!strncmp("temp?", buf, 5)) {
      dprintf(fd, "Temperature: %.2f C\r\n", read_temperature(i2c));
    } else if (!strncmp("hum?", buf, 4)) {
      dprintf(fd, "Humidity: %.2f %%\r\n", read_humidity(i2c));
    }
  }
  close(fd);
}
