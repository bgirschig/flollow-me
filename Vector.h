#ifndef Vector_h
#define Vector_h

#include "Arduino.h"

class Vector {
  public:
    Vector(float x, float y, float z);

    float x;
    float y;
    float z;

    void set(float x, float y, float z);
    float norm();
    void normalize();
    void map(Vector in_min, Vector in_max, float out_min, float out_max);
    String toString();
    String toPlot();

    static float dotProduct(Vector a, Vector b);
    static Vector vectProduct(Vector a, Vector b);
};

#endif