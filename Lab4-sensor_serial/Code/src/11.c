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

int main() {
  int fd = open(SERIAL_DEVICE, O_RDWR | O_NOCTTY);
  if (fd == -1) {
    perror("open_port: Unable to open " SERIAL_DEVICE " - ");
  }

  char buf[MAX_LINE_LENGTH];
  dprintf(fd, "Please input something. Server will echo same string.\r\n");
  for (;;) {
    dprintf(fd, "input> ");
    echo_readline(fd, buf, MAX_LINE_LENGTH);
    printf("Client says: ");
    puts(buf);
  }
  close(fd);
}
