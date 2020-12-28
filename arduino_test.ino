#include "Utils.h"
#include "Compass.h"
#include "status_codes.h"
#include "Blinker.h"

int status_code;
unsigned long frame = 0;

Compass compass;
Blinker statusBlinker(400, 1000, LED_BUILTIN);

void setup() {
  compass.begin();
  setStatusCode(OK);
}

void setStatusCode(int value) {
  status_code = value;
  statusBlinker.set_flash_count(value);
}

void loop() {
  frame += 1;
  statusBlinker.update();
  if (status_code != OK) return;

  compass.update();
}