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
  setup_pin_output(PIN_SLEEP);
  setup_pin_output(PIN_DIR);
  setup_pin_output(PIN_STEP);
  setup_pin_input(PIN_INPUT);
}

void setup() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setup_pins();
}
