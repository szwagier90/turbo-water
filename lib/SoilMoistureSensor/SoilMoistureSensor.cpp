#include "SoilMoistureSensor.h"

SoilMoistureSensor::SoilMoistureSensor
(
    IAnalogInput& analogInput
)
    : analogInput(analogInput)
{}

int SoilMoistureSensor::readPercent() const
{
	return (analogInput.read() * 100) / 1023;
}
