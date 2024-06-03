#ifndef MYEEPROM_H
#define MYEEPROM_H

#include "Sensor.h"

#define EEPROM_VERSION 13

struct Eeprom {
  uint16_t soilMoistureDry;
  uint16_t soilMoistureWet;
  uint8_t version;
};

Eeprom eeprom = {0};

bool loadEepromData(Sensor & sensor);
void saveCalibrationData(Sensor & sensor);
void eepromClearMemory();

bool loadEepromData(Sensor & sensor)
{
  EEPROM.begin(sizeof(Eeprom));
  delay(20);
  EEPROM.get(0, eeprom);

  Serial.print("EEPROM Length: ");
  Serial.println(EEPROM.length());
  Serial.print("EEPROM: SMMin - ");
  Serial.print(eeprom.soilMoistureDry);
  Serial.print(" | SMMax -  ");
  Serial.print(eeprom.soilMoistureWet);
  Serial.print(" | Version -  ");
  Serial.println(eeprom.version);

  if(EEPROM_VERSION != eeprom.version)
  {
    Serial.println("EEPROM: Version mismatch or no data");
    eepromClearMemory();
    return false;
  }

  sensor.soilMoistureDry = eeprom.soilMoistureDry;
  sensor.soilMoistureWet = eeprom.soilMoistureWet;
  Serial.println("EEPROM: Data loaded");

  EEPROM.end();

  return true;
}

void saveCalibrationData(Sensor & sensor)
{
  EEPROM.begin(sizeof(Eeprom));
  delay(20);

  eeprom.soilMoistureDry = sensor.soilMoistureDry;
  eeprom.soilMoistureWet = sensor.soilMoistureWet;
  eeprom.version = EEPROM_VERSION;

  EEPROM.put(0, eeprom);
  EEPROM.commit(); // Only needed for ESP boards
  Serial.println("EEPROM: Data saved");

  EEPROM.end();
}

void eepromClearMemory()
{
  eeprom = {0};
  EEPROM.put(0, eeprom);
  EEPROM.commit(); // Only needed for ESP boards
  Serial.println("EEPROM: Memory cleared");
}

#endif
