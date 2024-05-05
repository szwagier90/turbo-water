#include "Pump.h"

#include <Arduino.h>

Pump::Pump(bool & _pumpOutput) :
  pumpOutput(_pumpOutput),
  activated(false)
  {};

void Pump::pumpOn()
{
  activated = true;
  pumpSet(HIGH);
}

void Pump::pumpOff()
{
  pumpSet(LOW);
  activated = false;
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

bool Pump::isActivated()
{
  return activated;
}
