# `Flo`llow-me
An arduino-based autopilot for Flo

to fix intellisense issues (`missing include pinnames.h`, or similar) add the following to includepaths in c_cpp_properties.json
/Users/bastienGirschig/Library/Arduino15/packages/arduino/hardware/mbed_nano/2.3.1/cores/arduino/mbed/**

## Sensing
We take advantage of the intergated sensors in the arduino sense, we can determine the current
heading:
- A preset vector indicates the orientation of the arduino relative to the boat
- Using the accelerometer, we determine the "down" direction
- Using the magnetometer, we know the direction of the magnetic field. after removing its vertical
  component, it points north

## Actuation
We're using a motor controller board based on the BTS7960 chip to control an electric oil pump that
drives the rudder.

## Settings / UI
We plan on using three interfaces for this controller:
- Built-in LED blink patterns for very basic and reliable 'display'
  - Current mode
  - Missing hardware
  - Catastrophic failures
- Physical controller(s): LEDs, buttons, potentiometers/encoders, etc...
  - tweak Sensitivity
  - Tracking On/Off
  - Calibrate accelerometer
  - Calibrate magnetometer (how ?)
- Phone app, via bluetooth

## Failure modes
Failure | Worst Effect | Severity | Mitigation
--- | --- | --- | ---
Bluetooth fail | Can't use the remote | Minor | Every critical function accessible through a physical interface
Water damage | The pilot cannot function at all | Critical | Backup arduino with preloaded software + waterproof enclosure
Motor controller fail | The pilot cannot function at all | Critical | Backup motor controller
Logic failure | Erratic rudder control | Catastrophic | "panic button", phisically disconnects electric pump
Bad wire connection | Erratic rudder control | Catastrophic | "panic button", phisically disconnects electric pump
Short circuit | Fire | Catastrophic | Fuse, BTS7960 protection, temp sensor + alarm (?)


## CSYS
The inertial sensor and the magnetometer do not have the same coord systems... se we correct them and create our own CSYS:
x is in the Arduino card plan, transversal, pointing right if you have USB plug towards yourself 
y is in the Arduino card plan, longitudinal, pointing towards the side opposite to the USB plug 
z is perpendicular to the Arduino card, towards the top
x y z is a base orthonormee, right handed (standard) 



## Tips and tricks 
Serial.println(pilot.headingError*180/M_PI);

    Serial.print(pilot.headingError*180/M_PI);
    Serial.print(",");
    Serial.print(-90);
    Serial.print(",");
    Serial.print(90);
    Serial.print("\n");


## Connections Arduino Vs motor controller 
Arduino - motor controller
D3 LPWM
D4 RPWM
D5 L_EN
D6 R_EN
GND GND
3V3 VCC 
Motor controller L_IS R_IS are not connected 

## Arduino Vs start button
Arduino D2 connected to Vin -> pilot ON 
Arduino D2 connected to GND -> pilot OFF 
(D2 always connected to GND through 10kOhm resistance, and connected to Vin by switch to be ON)

