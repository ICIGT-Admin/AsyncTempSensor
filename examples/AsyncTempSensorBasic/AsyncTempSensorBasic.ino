#include <AsyncTempSensor.h>

AsyncTempSensor sensor(2);
void myTempCallback(DeviceAddress address, float temp) {
    // Print the address
    Serial.print("Sensor: ");
    for (int i = 0; i < 8; i++) {
        if (address[i] < 16) Serial.print("0");
        Serial.print(address[i], HEX);
        if (i < 7) Serial.print(":");
    }
    
    Serial.print(" | Temperature: ");
    Serial.println(temp);
}

void setup() {
    Serial.begin(115200);
    AsyncTempSensor sensor(2, myTempCallback);
    sensor.begin();
}

void loop() {
    sensor.update(1000); // Update every second
}