#ifndef VIEW_H
#define VIEW_H

#include "LiquidCrystal_I2C.h"

class View {
public:
  View (
    LiquidCrystal_I2C & lcd,
    int & currentMenuItem,
    int & sensorValue,
    int & soilMoisturePercent,
    bool & pumpOutput) :
      lcd(lcd),
      currentMenuItem(currentMenuItem),
      lastADCViewUpdateTime(0),
      ADCViewUpdateInterval(500),
      sensorValue(sensorValue),
      soilMoisturePercent(soilMoisturePercent),
      pumpOutput(pumpOutput)
    {};

  void lcdUpdate()
  {

    if(0 == currentMenuItem)
    {
      if((millis()-lastADCViewUpdateTime) > ADCViewUpdateInterval)
      {
        lcd.setCursor(5, 1);
        lcd.print(sensorValue);
        lcd.setCursor(13, 1);
        lcd.print(soilMoisturePercent);
      }
    }
    else if(1 == currentMenuItem)
    {
      lcd.setCursor(6, 1);
      lcd.print(pumpOutput ? "On " : "Off");
    }
  }

private:
  LiquidCrystal_I2C & lcd;

  int & currentMenuItem;
  unsigned long lastADCViewUpdateTime;
  const unsigned long ADCViewUpdateInterval = 500; // 0.5 seconds
  int & sensorValue;
  int & soilMoisturePercent;
  bool & pumpOutput;
};

#endif
