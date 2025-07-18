#ifndef SOIL_MOISTURE_SENSOR_H
#define SOIL_MOISTURE_SENSOR_H

#include "ISoilMoistureSensor.h"


class SoilMoistureSensor : public ISoilMoistureSensor
{
public:
    virtual int readPercent() const override;

private:
};

#endif // SOIL_MOISTURE_SENSOR_H
