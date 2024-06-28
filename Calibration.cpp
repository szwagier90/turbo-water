#include "Calibration.h"

#include <Arduino.h>

Calibration::Calibration(Calibration_States s)
  : state(s) {}

void Calibration::startCalibration()
{
  Serial.println(F("Calibration::startCalibration"));
}
