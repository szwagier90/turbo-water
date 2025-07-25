#ifndef SOIL_MOISTURE_SENSOR_H
#define SOIL_MOISTURE_SENSOR_H

#include "ISoilMoistureSensor.h"

#include "IAnalogInput.h"


class SoilMoistureSensor : public ISoilMoistureSensor
{
public:
    SoilMoistureSensor
    (
        IAnalogInput& analogInput
    );

    virtual int readPercent() const override;

private:
    IAnalogInput& analogInput;
};

#endif // SOIL_MOISTURE_SENSOR_H
