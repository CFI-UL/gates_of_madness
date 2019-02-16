#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>

#include "setup.h"

int main() {

  setup();

  int fd = open("/dev/mem", O_RDWR);
  void *gpio_addr = mmap(0, 1, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x30000);

  if (gpio_addr == -1)
    printf("fuck");

  printf("%x\n", gpio_addr);

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
