#include "Sensor.h"

Sensor::Sensor(uint16_t dry, uint16_t wet, States s)
  : soilMoistureDry(dry),
    soilMoistureWet(wet),
    state(s) {}
