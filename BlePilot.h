#ifndef BlePilot_h
#define BlePilot_h

#include <ArduinoBLE.h>

// read and writable by central
class BlePilot {
  public:
    BlePilot();
    void begin();
    void update();

  private:
    bool started; // wether ble was initialized successfully
    bool connectedToCentral;

    BLEService service { "19B10000-E8F2-537E-4F6C-D104768A1214" }; // BLE Service
    BLEFloatCharacteristic headingCharacteristic { "19B10001-E8F2-537E-4F6C-D104768A1214", BLERead };
    BLEBoolCharacteristic switchCharacteristic { "19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite };
};

#endif
