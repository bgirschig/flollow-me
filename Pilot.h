#ifndef Pilot_h
#define Pilot_h

#include "Arduino.h"
#include "Compass.h"

class Pilot {
  public:
    Pilot();
    bool is_on;
    float targetHeading;
    float headingError;

    void begin();
    void end();
    void update();

    // TODO: merge those with begin/end. Make sure to get some significant updates from compass
    // before actually starting
    void startTracking();
    void stopTracking();
  private:
    Compass compass;
};

#endif