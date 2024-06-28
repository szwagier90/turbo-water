#ifndef CALIBRATION_H
#define CALIBRATION_H

typedef enum
{
  Calibration_Ready
} Calibration_States;

struct Calibration
{
  Calibration(
    Calibration_States s = Calibration_Ready
  );

  void startCalibration();

  Calibration_States state;
};

#endif
