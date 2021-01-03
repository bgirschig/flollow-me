#ifndef Utils_h
#define Utils_h

#include <Arduino.h>

class Utils {
  public:
    static float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);
    static void exitMainLoop();
};

#endif