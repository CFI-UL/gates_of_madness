#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <string.h>
#include <stdbool.h>

#include "setup.h"

int main(int argc, char **argv) {
  struct pollfd fds;
  fds.fd = 0; /* this is STDIN */
  fds.events = POLLIN;
  int ret = 0;
  bool daemonize = false;

  for (int i = 1; i < argc; ++i)
    if (strcmp(argv[i], "-d") == 0)
      daemonize = true;

  setup();

  int sleep_fd = open(PIN_PATH(PIN_SLEEP), O_WRONLY);
  write(sleep_fd, "1\n", 2);

  puts("Entering step loop\n");

  if (!daemonize)
    puts("Press any key to stop\n");

  int pin_fd = open(PIN_PATH(PIN_STEP), O_WRONLY);
  for (int i = 0; i < 4000; i++) { // 40 * 50ms = 2s
    // 25 ms
    write(pin_fd, "1\n", 2);
    usleep(25 * 100);

    // 25 ms
    write(pin_fd, "0\n", 2);
    usleep(25 * 100);

    if (!daemonize) {
      ret = poll(&fds, 1, 0);
      if (ret == 1)
	break;
    }
  }

  puts("Loop finished, waiting some seconds...\n");
  sleep(2);

  puts("Done! Cleaning and exiting\n");
  write(sleep_fd, "0\n", 2);

}
