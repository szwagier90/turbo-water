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

void SoilMoistureSensor::calibrate()
{
    calibrated = true;
}

int SoilMoistureSensor::readPercent() const
{
    return (analogInput.read() * 100) / 1023;
}

int SoilMoistureSensor::readRaw() const
{
    return analogInput.read();
}
