
// https://content.instructables.com/ORIG/FYD/V3VU/HUL8W2ZW/FYDV3VUHUL8W2ZW.pdf

#ifndef BTS7960_h
#define BTS7960_h

#include "Arduino.h"

class BTS7960 {
  public:
    int left_pwm_pin;
    int right_pwm_pin;

    BTS7960(int left_pwm_pin, int right_pwm_pin, int left_enable_pin, int right_enable_pin);
    void setSpeed(float speed);
};

#endif