/* Reads data from an IMU sensor and computes a compass heading from it */

#include <Arduino.h>
#include "Compass.h"
#include "Utils.h"
#include <Arduino_LSM9DS1.h>

Compass::Compass() {
  compassHeading = 0;
}

void Compass::begin() {
  bool imuStartedSuccessfully = IMU.begin();
  if (!imuStartedSuccessfully) {
    Serial.println("Failed to initialize IMU!");
    Utils::exitMainLoop();
  }
}

void Compass::end() {
  IMU.end();
}

void Compass::update() {
  if (IMU.magneticFieldAvailable()) {
    // These are used to get data out of the IMU
    float x, y, z;

    // update the magnetic field vector
    IMU.readMagneticField(x, y, z);
    updateBounds(x, y, z);
    magnetic_field.set(x, y, z);
    magnetic_field.map(min_magnetometer, max_magnetometer, -1, 1);
    magnetic_field.normalize();
    magnetic_field.set(magnetic_field.y, -magnetic_field.x, magnetic_field.z);

    // update the 'up' vector
    IMU.readAcceleration(x, y, z);
    up.set(y, x, z);
    up.normalize();

    // update the north vector
    float magneticUpComponent = Vector::dotProduct(magnetic_field, up);
    north.set(
      magnetic_field.x - magneticUpComponent * up.x,
      magnetic_field.y - magneticUpComponent * up.y,
      magnetic_field.z - magneticUpComponent * up.z
    );
    north.normalize();

    // update east vector
    east = Vector::vectProduct(north, up);

    float boatUpComponent = Vector::dotProduct(boat, up);
    headingVector.set(
      boat.x - boatUpComponent * up.x,
      boat.y - boatUpComponent * up.y,
      boat.z - boatUpComponent * up.z
    );
    headingVector.normalize();

    // update heading
    float headingNorthComponent = Vector::dotProduct(headingVector, north);
    float headingEastComponent = Vector::dotProduct(headingVector, east);
    compassHeading = atan2(headingEastComponent, headingNorthComponent);
  }
}

void Compass::updateBounds(float x, float y, float z) {
  if (x < min_magnetometer.x) min_magnetometer.x = x;
  if (y < min_magnetometer.y) min_magnetometer.y = y;
  if (z < min_magnetometer.z) min_magnetometer.z = z;

  if (x > max_magnetometer.x) max_magnetometer.x = x;
  if (y > max_magnetometer.y) max_magnetometer.y = y;
  if (z > max_magnetometer.z) max_magnetometer.z = z;
}

String Compass::toString() {
  return String() + "<Compass:"+magnetic_field.toString()+","+compassHeading+">";
}