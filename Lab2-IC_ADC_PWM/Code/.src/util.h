#include <time.h>

void sleep_ns(long ns) {
  struct timespec ts;
  int res;

  ts.tv_sec = ns / 1000000000;
  ts.tv_nsec = ns % 1000000000;

  do {
    res = nanosleep(&ts, &ts);
  } while (res);
}

void sleep_ms(double ms) { sleep_ns(ms * 1000000); }
