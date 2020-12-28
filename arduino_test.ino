#include "Utils.h"
#include "Compass.h"
#include "status_codes.h"
#include "Blinker.h"

#define BUTTON_PIN 2

int status_code;
bool autopilot_on = false;

unsigned long frame = 0;
int last_button_state = 0;
float targetHeading = 0;

Compass compass;
Blinker statusBlinker(400, 1000, LED_BUILTIN);

void setup() {
  compass.begin();
  setStatusCode(OK);
  pinMode(BUTTON_PIN, INPUT);
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

  updatePilotState();
  if (!autopilot_on) return;

  if (frame%100 == 0) {
    float headingError = compass.compassHeading - targetHeading;
    Serial.print(headingError / M_PI * 180.0);
    Serial.print(",");
    if (headingError > M_PI) headingError = headingError - M_PI*2.0;
    else if (headingError < -M_PI) headingError = headingError + M_PI*2.0;

    Serial.print(headingError / M_PI * 180.0);
    Serial.print("\n");
  }
}

void updatePilotState() {
  int buttonInput = digitalRead(BUTTON_PIN);
  if (last_button_state != buttonInput) {
    if (buttonInput == 1 && autopilot_on == false) {
      autopilot_on = true;
      targetHeading = compass.compassHeading;
      // Serial.println(String() + "turning pilot on, target: " + targetHeading);
    }
    else if (buttonInput == 0 && autopilot_on == true) {
      autopilot_on = false;
      // Serial.println(String() + "turning pilot off");
    }
  }
  last_button_state = buttonInput;
}