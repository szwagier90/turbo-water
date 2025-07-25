#ifndef MOCK_SOIL_MOISTURE_SENSOR_H
#define MOCK_SOIL_MOISTURE_SENSOR_H

#include "ISoilMoistureSensor.h"

class MockSoilMoistureSensor : public ISoilMoistureSensor
{
public:
    MOCK_METHOD(int, readPercent, (), (const override));
};

#endif // MOCK_SOIL_MOISTURE_SENSOR_H
