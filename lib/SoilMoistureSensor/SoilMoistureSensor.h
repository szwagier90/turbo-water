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

    virtual bool isCalibrated() const override;

    virtual void calibrate(int dry, int wet) override;

    virtual int readPercent() const override;
    virtual int readRaw() const override;

private:
    IAnalogInput& analogInput;

    bool calibrated;
    int dry;
    int wet;
};

#endif // SOIL_MOISTURE_SENSOR_H
