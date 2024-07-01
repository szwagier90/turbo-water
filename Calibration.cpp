#include "Calibration.h"

#include <Arduino.h>

Calibration::Calibration(Calibration_States s)
  : state(s) {}

void Calibration::startCalibration(Sensor * s)
{
  Serial.println(F("Calibration::startCalibration"));
  this->sensor = s;
  state = Calibration_Dry;
  Serial.println(F("Calibration state set to Calibration_Dry"));
}

void Calibration::saveDryValue(unsigned val)
{
  Serial.println(F("Calibration::saveDryValue"));
  this->dry = val;
  Serial.print(F("Calibration Dry val set to: "));
  Serial.println(this->dry);
  state = Calibration_Wet;
  Serial.println(F("Calibration state set to Calibration_Wet"));
}

void Calibration::saveWetValue(unsigned val)
{
  Serial.println(F("Calibration::saveWetValue"));
  this->wet = val;
  Serial.print(F("Calibration Wet val set to: "));
  Serial.println(this->wet);
  state = Calibration_Confirm;
  Serial.println(F("Calibration state set to Calibration_Confirm"));
}

void Calibration::calibrateSensor()
{
  Serial.println(F("Calibration::calibrateSensor"));
  sensor->calibrate(this->dry, this->wet);
  state = Calibration_Ready;
  Serial.println(F("Calibration Finished, state set to Calibration_Ready"));
  sensor = nullptr;
}
