#include "View.h"

View::View (
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

void View::lcdUpdate()
{
  if(0 == currentMenuItem)
  {
    sensorStatusView();
  }
  else if(1 == currentMenuItem)
  {
    pumpStatusView();
  }
}

void View::sensorStatusView()
{
  if((millis()-lastADCViewUpdateTime) > ADCViewUpdateInterval)
  {
    lcd.setCursor(5, 1);
    lcd.print(sensorValue);
    lcd.setCursor(13, 1);
    lcd.print(soilMoisturePercent);
  }
}

void View::pumpStatusView()
{
  lcd.setCursor(6, 1);
  lcd.print(pumpOutput ? "On " : "Off");
}
