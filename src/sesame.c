#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/poll.h>

#include "setup.h"

int main() {
  struct pollfd fds;
  fds.fd = 0; /* this is STDIN */
  fds.events = POLLIN;
  int ret;

  setup();

  int sleep_fd = open(PIN_PATH(PIN_SLEEP), O_WRONLY);
  write(sleep_fd, "1\n", 2);

  int dir_fd = open(PIN_PATH(PIN_DIR), O_WRONLY);
  write(dir_fd, "1\n", 2);

  puts("Press any key to stop\n");

  int pin_fd = open(PIN_PATH(PIN_STEP), O_WRONLY);
  for (int i = 0; i < 300; i++) {
    // 2.5 ms
    write(pin_fd, "1\n", 2);
    usleep(25 * 100);

    // 2.5 ms
    write(pin_fd, "0\n", 2);
    usleep(25 * 100);

    ret = poll(&fds, 1, 0);
    if (ret == 1)
      break;
  }

  sleep(2);

  write(sleep_fd, "0\n", 2);

}
