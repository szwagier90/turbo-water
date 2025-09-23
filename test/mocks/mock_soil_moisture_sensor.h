#ifndef MOCK_SOIL_MOISTURE_SENSOR_H
#define MOCK_SOIL_MOISTURE_SENSOR_H

#include "ISoilMoistureSensor.h"

class MockSoilMoistureSensor : public ISoilMoistureSensor
{
public:
    MOCK_METHOD(bool, isCalibrated, (), (const override));
    MOCK_METHOD(void, calibrate, (int, int), (override));
    MOCK_METHOD(int, readPercent, (), (const override));
    MOCK_METHOD(int, readRaw, (), (const override));
};

#endif // MOCK_SOIL_MOISTURE_SENSOR_H
