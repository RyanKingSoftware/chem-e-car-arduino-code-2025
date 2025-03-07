#ifndef BH1750_H
#define BH1750_H

#include <Wire.h>

class BH1750 {
public:
    bool init() {
        Wire.begin();

        // Power on the sensor
        Wire.beginTransmission(SENSOR_ADDR);
        Wire.write(CMD_POWER_ON);
        if (Wire.endTransmission() != 0) return false;

        // Set to continuous high-resolution mode
        Wire.beginTransmission(SENSOR_ADDR);
        Wire.write(CMD_CONTINUOUS_HIGH_RES_MODE);
        return Wire.endTransmission() == 0;
    }

    uint16_t read() {
        Wire.requestFrom(SENSOR_ADDR, (uint8_t)2);
        if (Wire.available() < 2) return 0; // Failed to read

        uint16_t lux = Wire.read() << 8;
        lux |= Wire.read();

        // Clamp the value to prevent overflow (max 65535 lux)
        if (lux > 65535) {
            lux = 65535;
        }

        return lux;
    }

private:
    static constexpr uint8_t SENSOR_ADDR = 0x23;
    static constexpr uint8_t CMD_POWER_ON = 0x01;
    static constexpr uint8_t CMD_CONTINUOUS_HIGH_RES_MODE = 0x10;
};

#endif // BH1750_H
