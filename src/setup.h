#ifndef SETUP_H
#define SETUP_H

#include <stdio.h>
#include <stdlib.h>

#define PIN_SLEEP "19" // gray
#define PIN_DIR "21" // black
#define PIN_STEP "24" // red
#define PIN_INPUT "18" // blue

#define PIN_PATH(SOME_PIN) "/sys/class/gpio/gpio" SOME_PIN "/value"

// exports all the required pins and sets their direction
void setup();

#endif
