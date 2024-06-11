#include "Sensor.h"

Sensor::Sensor(uint16_t dry, uint16_t wet, States s)
  : soilMoistureDry(dry),
    soilMoistureWet(wet),
    state(s) {}

void Sensor::calibrate(uint16_t dry, uint16_t wet)
{
  soilMoistureDry = dry;
  soilMoistureWet = wet;

  state = STATE_NORMAL;
}
