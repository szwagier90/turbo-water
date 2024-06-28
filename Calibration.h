#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "Sensor.h"

typedef enum
{
  Calibration_Ready,
  Calibration_Dry,
  Calibration_Wet,
  Calibration_Confirm
} Calibration_States;

struct Calibration
{
  Calibration(
    Calibration_States s = Calibration_Ready
  );

  void startCalibration(Sensor * sensor);
  void saveDryValue(unsigned val);
  void saveWetValue(unsigned val);

  Calibration_States state;

private:
  Sensor * sensor;
  unsigned dry;
  unsigned wet;
};

#endif
