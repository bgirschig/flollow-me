#include "Arduino.h"
#include "BTS7960.h"

BTS7960::BTS7960(int left_pwm_pin, int right_pwm_pin, int left_enable_pin, int right_enable_pin) {
  this->left_pwm_pin = left_pwm_pin;
  this->right_pwm_pin = right_pwm_pin;

  pinMode(left_pwm_pin, OUTPUT);
  pinMode(right_pwm_pin, OUTPUT);
  pinMode(left_enable_pin, OUTPUT);
  pinMode(right_enable_pin, OUTPUT);

  digitalWrite(left_enable_pin, HIGH);
  digitalWrite(right_enable_pin, HIGH);

  setSpeed(0);
}

void BTS7960::setSpeed(float speed) {
  // cap input speed
  if (speed > 1) speed = 1;
  if (speed < -1) speed = -1;

  // Compute pwm value (0-255) for left and right pins
  int left_pwm = 0;
  int right_pwm = 0;
  if (speed > 0) left_pwm = int(speed * 255);
  else right_pwm = int(-speed * 255);

  if (Serial.ready()) {
    Serial.println(String() + left_pwm_pin + "," + left_pwm + "," + right_pwm_pin + "," + right_pwm);
  }

  // apply pwm
  analogWrite(left_pwm_pin, left_pwm);
  analogWrite(right_pwm_pin, right_pwm);
}