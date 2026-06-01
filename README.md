```markdown
# AsyncTempSensor — Arduino library for DS18B20

Arduino library for **non-blocking asynchronous operation** with **DS18B20** temperature sensors.

![AsyncTempSensor](https://github.com/MouseZver/AsyncTempSensor/blob/master/sensors.png?raw=true)

## ✅ Features

- Works with **one or multiple sensors** on a single pin
- **Non-blocking** mode using `millis()`
- Supports **callback notifications** when temperature is ready
- Completely **`delay()`-free**
- Optional **debug output**
- Simple and intuitive interface

## 📌 Usage Example

### Basic example:

```cpp
#include <AsyncTempSensor.h>

// Callback receives device address and temperature
void onTemperature(DeviceAddress address, float temp) {
    Serial.print("🌡 Temperature from sensor: ");
    
    // Print the 64-bit address
    for (int i = 0; i < 8; i++) {
        if (address[i] < 16) Serial.print("0");
        Serial.print(address[i], HEX);
        if (i < 7) Serial.print(":");
    }
    
    Serial.print(" = ");
    Serial.println(temp);
}

AsyncTempSensor tempSensor(2, onTemperature);

void setup() {
    Serial.begin(9600);
    tempSensor.setDebugOutput(true); // Enable debug output
    tempSensor.begin();
}

void loop() {
    tempSensor.update(1000); // Update every 1 second
}
```

### Alternative: Lambda callback (C++11)

```cpp
AsyncTempSensor tempSensor(2, [](DeviceAddress address, float temp) {
    Serial.print("Temperature: ");
    Serial.println(temp);
});
```

## 📦 Installation

1. Go to **Sketch → Include Library → Manage Libraries**
2. Search for **AsyncTempSensor**
3. Install the library

Or manually clone the repository into your libraries folder:

```bash
cd ~/Arduino/libraries
git clone https://github.com/yourusername/AsyncTempSensor.git
```

## 📌 Functions

- `begin()` — initialize and search for sensors
- `update(unsigned long interval)` — update temperature at specified interval
- `setDebugOutput(true)` — enable debug output to Serial
- `callback` — called when temperature is ready (receives `DeviceAddress` and `float temperature`)

## 📌 Sensor Wiring

- **Sensor DATA** → **pin 2** (or any other pin specified during initialization)
- **GND** → **GND**
- **VCC** → **5V**
- **4.7kΩ resistor** between **DATA and 5V**

## 📌 DeviceAddress Format

The `DeviceAddress` is an 8-byte array containing the unique 64-bit ROM code of each DS18B20 sensor. You can store, compare, or print these addresses to identify specific sensors.

Example of printing an address:

```cpp
void printAddress(DeviceAddress address) {
    for (int i = 0; i < 8; i++) {
        if (address[i] < 16) Serial.print("0");
        Serial.print(address[i], HEX);
        if (i < 7) Serial.print(":");
    }
}
```

## 📌 Notes

- The library automatically searches for all DS18B20 sensors on the bus during `begin()`
- The callback is called for each sensor once per update cycle when measurements are complete
- Minimum conversion time is 750ms (DS18B20 default 12-bit resolution)
- If no sensors are found, the callback is called once with an empty address and `NAN` (Not a Number)
```