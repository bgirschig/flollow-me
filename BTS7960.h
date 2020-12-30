#ifndef BTS7960_h
#define BTS7960_h

#include "Arduino.h"

class BTS7960 {
  public:
    int left_pwm_pin;
    int right_pwm_pin;
    int left_enable_pin;
    int right_enable_pin;

    void begin(int left_pwm_pin, int right_pwm_pin, int left_enable_pin, int right_enable_pin);
    void end();
    void setSpeed(float speed);
};

#endif