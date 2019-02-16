#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>

#define STRLEN 64

void run(char *cmd) {
  puts(cmd);
  system(cmd);
}

// prepares a gpio pin
void setup_pin(char *pin_number) {
  char buf[STRLEN] = {0};

  snprintf(buf, STRLEN, "echo %s > /sys/class/gpio/export", pin_number);
  run(buf);

  snprintf(buf, STRLEN, "echo out > /sys/class/gpio/gpio%s/direction", pin_number);
  run(buf);
}

int main() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setup_pin("19"); // gray  - sleep
  setup_pin("21"); // black - dir
  setup_pin("24"); // red   - step

  int pin_fd = open("/sys/class/gpio/gpio19/value", O_WRONLY);
  /*
  for (int i = 0; ; i++) {
	  // 2 ms
	  write(pin_fd, "1\n", 2);
	  usleep(2000);

	  // 20ms
	  write(pin_fd, "0\n", 2);
	  usleep(18000);
  }
  */
}
