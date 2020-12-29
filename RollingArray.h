#ifndef RollingArray_h
#define RollingArray_h

#include "Arduino.h"

class RollingArray {
  public:
    RollingArray(int size);
    int max_size; // allocated array size
    int current_size; // current size
    int currentIndex;
    float sum;
    float *values;

    bool is_full();
    void append(float value);
};

#endif