#include "Utils.h"
#include "Compass.h"
#include "status_codes.h"
#include "Blinker.h"
#include "Pilot.h"
#include "BTS7960.h"

#define BUTTON_PIN 2

int status_code;

unsigned long next_frame_time = 0;
int last_button_state = 0;
float target_frame_interval = 1000.0 / 120.0;

Pilot pilot;
BTS7960 legoMotor;
Blinker statusBlinker(400, 1000, LED_BUILTIN);

void setup() {
  pilot.begin();
  legoMotor.begin(3, 4, 5, 6);
  setStatusCode(OK);
  pinMode(BUTTON_PIN, INPUT);
  next_frame_time = millis();
}

void setStatusCode(int value) {
  status_code = value;
  statusBlinker.set_flash_count(value);
}

void loop() {
  if (status_code != OK) return;

  // throttle main loop
  unsigned long now = millis();
  if (now < next_frame_time) return;
  next_frame_time += target_frame_interval;
  
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

  // update motor speed
  if (pilot.is_on) {
    float speed = pilot.headingError * RAD_TO_DEG / 180.0;
    legoMotor.setSpeed(speed);
  } else {
    legoMotor.setSpeed(0);
  }
}
