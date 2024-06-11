#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>

typedef enum
{
  Sensor_NonCalibrated,
  Sensor_CalibrationOK
} States;

struct Sensor
{
  Sensor(
    uint16_t dry = 10000,
    uint16_t wet = 0,
    States s = Sensor_NonCalibrated
  );

  void calibrate(uint16_t dry, uint16_t wet);

  uint16_t soilMoistureDry;
  uint16_t soilMoistureWet;
  States state;
};

#endif
