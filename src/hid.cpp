#include <Arduino.h>
#include "hid.h"

void io_setup() {
  pinMode(BUTTONL, INPUT_PULLUP);
  pinMode(BUTTONM, INPUT_PULLUP);
  pinMode(BUTTONR, INPUT_PULLUP);
  pinMode(BUTTONU, INPUT_PULLUP);
  pinMode(BUTTOND, INPUT_PULLUP);
}