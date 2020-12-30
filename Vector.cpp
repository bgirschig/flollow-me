/* 3d Vector */

#include "Arduino.h"
#include "Vector.h"
#include "Utils.h"

Vector::Vector(float x, float y, float z) {
  set(x, y, z);
}

void Vector::set(float _x, float _y, float _z) {
  x = _x;
  y = _y;
  z = _z;
}

/// returns vector length
float Vector::norm() {
  return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}

/// normalize vector in-place
void Vector::normalize() {
  float len = norm();
  x = x/len;
  y = y/len;
  z = z/len;
}

String Vector::toString() {
  return String() + "<vect:" + x + "," + y + "," + z + ">";
}
String Vector::toPlot() {
  return String() + x + "," + y + "," + z;
}

/**
 * Maps each component of the vector from the range defined by in_min and in_max's components
 * to the range defined by out_min and out_max
 */
void Vector::map(Vector in_min, Vector in_max, float out_min, float out_max) {
  x = Utils::mapfloat(x, in_min.x, in_max.x, out_min, out_max);
  y = Utils::mapfloat(y, in_min.y, in_max.y, out_min, out_max);
  z = Utils::mapfloat(z, in_min.z, in_max.z, out_min, out_max);
}

float Vector::dotProduct(Vector a, Vector b) {
  return a.x*b.x + a.y*b.y + a.z*b.z;
}
Vector Vector::vectProduct(Vector a, Vector b) {
  Vector output(
    a.y*b.z - a.z*b.y,
    a.z*b.x - a.x*b.z,
    a.x*b.y - a.y*b.x
  );
  return output;
}