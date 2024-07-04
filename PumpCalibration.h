#ifndef PUMP_CALIBRATION_H
#define PUMP_CALIBRATION_H

typedef enum
{
  PumpCalibration_Ready,
} PumpCalibration_States;

struct PumpCalibration
{
  PumpCalibration(
    PumpCalibration_States s = PumpCalibration_Ready
  );

  PumpCalibration_States state;
};

#endif
