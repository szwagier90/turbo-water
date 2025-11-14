#include "SoilMoistureSensor.h"

SoilMoistureSensor::SoilMoistureSensor
(
    IAnalogInput& analogInput
)
    : analogInput(analogInput)
    , calibrated(false)
{}

bool SoilMoistureSensor::isCalibrated() const
{
    return calibrated;
}

void SoilMoistureSensor::calibrate(int dry, int wet)
{
    this->dry = dry;
    this->wet = wet;
    calibrated = true;
}

int SoilMoistureSensor::readPercent() const
{
    return ((analogInput.read()-dry) * 100) / (wet-dry);
}

int SoilMoistureSensor::readRaw() const
{
    return analogInput.read();
}
