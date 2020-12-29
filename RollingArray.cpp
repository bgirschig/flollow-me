#include "Arduino.h"
#include "RollingArray.h"

RollingArray::RollingArray(int size) {
  max_size = size;
  current_size = 0;
  currentIndex = 0;
  sum = 0;
  values = new float[size];
}

void RollingArray::append(float value) {
  values[currentIndex] = value;
  currentIndex += 1;
  sum += value;
  if (current_size < max_size) current_size += 1;
  if (currentIndex >= max_size) currentIndex = 0;
}