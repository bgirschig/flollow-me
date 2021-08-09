#include "BlePilot.h"
#include "Utils.h"

BlePilot::BlePilot() {
}

void BlePilot::begin() {
  started = BLE.begin();

  if (!started) { 
    if (Serial) Serial.println("Failed to initialize BLE");
  }
  pinMode(LED_BUILTIN, OUTPUT);

  BLE.setLocalName("flollow-me");
  BLE.setAdvertisedService(service);

  service.addCharacteristic(headingCharacteristic);
  service.addCharacteristic(switchCharacteristic);
  
  BLE.addService(service);
  BLE.advertise();

  headingCharacteristic.writeValue(0.186);

  if (Serial) Serial.println("BLE service started");
}

void BlePilot::update() {
  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();

  if (!central && connectedToCentral) {
    // central disconnected
    connectedToCentral = false;
    if (Serial) Serial.print("Disconnected from central");
  }

  if (central && !connectedToCentral) {
    // central connected
    connectedToCentral = true;
    if (Serial) {
      Serial.print("Connected to central: ");
      Serial.println(central.address());
    }
  }
  
  // while the central is still connected to peripheral:
  if (central.connected()) {
    // if the remote device wrote to the characteristic, use the value to control the LED:
    if (switchCharacteristic.written()) {
      if (switchCharacteristic.value()) {   // any value other than 0
        if (Serial) Serial.println("LED on");
        digitalWrite(LED_BUILTIN, HIGH);    // will turn the LED on
      } else {                              // a 0 value
        if (Serial) Serial.println(F("LED off"));
        digitalWrite(LED_BUILTIN, LOW);     // will turn the LED off
      }
    }
  }

}