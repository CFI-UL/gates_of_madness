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

struct pollfd fds;
bool daemonize = false;
int ret = 0;

void spin(int work_ms, int hold_ms, int step_ms) {
  int sleep_fd = open(PIN_PATH(PIN_SLEEP), O_WRONLY);
  int pin_fd = open(PIN_PATH(PIN_STEP), O_WRONLY);

  write(sleep_fd, "1\n", 2); // start working
  for (int i = 0; i < work_ms; i += step_ms) {
    write(pin_fd, "1\n", 2);
    write(pin_fd, "0\n", 2);
    usleep(step_ms * 1000);

    if (!daemonize) {
      ret = poll(&fds, 1, 0);
      if (ret == 1)
	break;
    }
  }

  usleep(hold_ms * 1000); // hold
  write(sleep_fd, "0\n", 2); // release
}

int main(int argc, char **argv) {
  fds.fd = 0; /* this is STDIN */
  fds.events = POLLIN;

  int sleep_fd = open(PIN_PATH(PIN_SLEEP), O_WRONLY);

  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-d") == 0) {
      daemonize = true;
      printf("Starting as daemon...");
    }
  }

  setup();

  if (!daemonize)
    puts("Press any key to stop\n");

  puts("Calibrating");
  for (int i = 0; i < 5; ++i) {
    spin(600, 100, 2);
    sleep(1);
  }

  puts("Opening the door\n");
  spin(4800, 5 * 1000, 5);

  puts("Done! Cleaning and exiting\n");
  write(sleep_fd, "0\n", 2);

}
