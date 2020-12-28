#include "Utils.h"
#include "Compass.h"
#include "status_codes.h"
#include "Blinker.h"
#include "Pilot.h"

#define BUTTON_PIN 2

int status_code;

unsigned long frame = 0;
int last_button_state = 0;

Pilot pilot;
Blinker statusBlinker(400, 1000, LED_BUILTIN);

void setup() {
  pilot.begin();
  setStatusCode(OK);
  pinMode(BUTTON_PIN, INPUT);
}

void setStatusCode(int value) {
  status_code = value;
  statusBlinker.set_flash_count(value);
}

void loop() {
  if (status_code != OK) return;
  frame += 1;
  
  // Update objets
  statusBlinker.update();
  pilot.update();

  // Check if we should toggle the pilot on/off
  int buttonInput = digitalRead(BUTTON_PIN);
  if (last_button_state != buttonInput) {
    if (buttonInput == 1 && !pilot.is_on) pilot.startTracking();
    else if (buttonInput == 0 && pilot.is_on) pilot.stopTracking();
  }
  last_button_state = buttonInput;

  if (frame%100 == 0) {
    Serial.print(pilot.headingError / M_PI * 180.0);
    Serial.print("\n");
  }
}
