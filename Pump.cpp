#include "Pump.h"

#include <Arduino.h>

Pump::Pump(bool & _pumpOutput) : pumpOutput(_pumpOutput) {};

void Pump::pumpOn()
{
  pumpSet(HIGH);
}

void Pump::pumpOff()
{
  pumpSet(LOW);
}

void Pump::pumpSet(bool v)
{
  if(v != pumpOutput)
  {
    Serial.print("Pump: ");
    Serial.println(v ? "On" : "Off");
    pumpOutput = v;
  }
}
