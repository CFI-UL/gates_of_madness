#include "setup.h"

void run(char *cmd) {
  puts(cmd);
  system(cmd);
}

// prepares a gpio pin
void setup_pin(char *pin_number, char *direction) {
  char buf[64] = {0};

  snprintf(buf, 64, "echo %s > /sys/class/gpio/export", pin_number);
  run(buf);

  snprintf(buf, 64, "echo %s > /sys/class/gpio/gpio%s/direction", direction, pin_number);
  run(buf);
}

void setup_pin_output(char *pin_number) {
  setup_pin(pin_number, "out");
}

void setup_pin_input(char *pin_number) {
  setup_pin(pin_number, "in");
}

void setup_pins() {
  // gray - sleep
  setup_pin_output("19");

  // black - dir
  setup_pin_output("21");

  // red - step
  setup_pin_output("24");

  // blue - input
  setup_pin_input("18");
}

void setup() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setup_pins();
}
