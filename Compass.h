/* Reads data from an IMU sensor and computes a compass heading from it */

#ifndef Compass_h
#define Compass_h

#include "Arduino.h"
#include "Vector.h"
#include "Utils.h"

class Compass {
  public:
    Compass();
    float compassHeading = 0;

    void begin();
    void end();
    void update();
    String toString();

  private:
    Vector magnetic_field {0,0,0};
    Vector min_magnetometer {-12.95, -28.81, -32.82};
    Vector max_magnetometer {65.15, 50.99, 46.85};

    Vector up {0,0,0};
    Vector north {0,0,0};
    Vector east {0,0,0};

    Vector boat {0,1,0};
    Vector headingVector {0,0,0};

    void updateBounds(float x, float y, float z);
};

#endif