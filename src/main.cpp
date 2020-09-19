#include <Arduino.h>
#include "display.h"
#include "hid.h"
#include "rh_master.h"

void setup() {
  oled_setup();
  rh_master_setup();
  io_setup();
}

void loop() {
  rh_master_handle();
  oled_handle();
}