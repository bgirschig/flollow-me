/* Computes distance to a target heading */

#include <Arduino.h>
#include "Pilot.h"
#include "Compass.h"

Pilot::Pilot() {
  is_on = false;
  targetHeading = 0;
}

void Pilot::begin() {
  compass.begin();
}
void Pilot::end() {
  compass.end();
  is_on = false;
}

void Pilot::update() {
  if (!is_on) return;
  compass.update();

  headingError = compass.compassHeading - targetHeading;
  if (headingError > M_PI) headingError = headingError - M_PI*2.0;
  else if (headingError < -M_PI) headingError = headingError + M_PI*2.0;
}

void Pilot::startTracking() {
  is_on = true;
  targetHeading = compass.compassHeading;
  headingError = 0;
}
void Pilot::stopTracking() {
  is_on = false;
  headingError = 0;
}