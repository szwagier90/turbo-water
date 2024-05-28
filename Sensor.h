#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>

typedef enum
{
  STATE_CALIBRATION,
  STATE_NORMAL
} States;

struct Sensor
{
  Sensor(
    uint16_t dry = 10000,
    uint16_t wet = 0,
    States s = STATE_CALIBRATION
  );

  uint16_t soilMoistureDry;
  uint16_t soilMoistureWet;
  States state;
};

#endif