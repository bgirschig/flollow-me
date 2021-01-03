#ifndef RollingArray_h
#define RollingArray_h

#include <iostream>
#include <string>
#include <sstream>

class RollingArray {
  public:
    RollingArray(int alloc_size);
    void setLength(int size);

    int start_idx;
    float sum;
    float *values;
    
    float get(int index);
    void append(float value);
    std::string toString();

  private:
    int alloc_size;
    int size;
};

#endif