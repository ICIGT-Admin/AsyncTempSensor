#ifndef ASYNC_TEMP_SENSOR_H
#define ASYNC_TEMP_SENSOR_H

#include <Arduino.h>
#include <OneWire.h>

// Type for storing 64-bit sensor address
typedef uint8_t DeviceAddress[8];

// Callback function type - now receives address instead of index
typedef void (*TempCallback)(DeviceAddress address, float temp);

class AsyncTempSensor {
public:
    static const int MAX_DEVICES = 8;

    // Constructor: specify pin and callback
    AsyncTempSensor(uint8_t pin, TempCallback callback = nullptr);

    // Initialization: search for sensors
    void begin();

    // Update temperature (non-blocking call)
    void update(unsigned long interval);

    // Enable/disable debug output
    void setDebugOutput(bool enabled);

private:
    OneWire _oneWire;
    uint8_t _pin;
    TempCallback _callback = nullptr;

    DeviceAddress _addresses[MAX_DEVICES]; // Addresses of found sensors
    int _deviceCount = 0;                  // Number of found sensors

    unsigned long _lastConversionTime = 0; // Time of last measurement start
    bool _conversionStarted = false;       // Flag: measurement in progress
    bool _debug = false;                   // Flag: debug enabled

    void findDevices();   // Search for sensors on the bus
    void startConversion(); // Start temperature measurement
};

#endif