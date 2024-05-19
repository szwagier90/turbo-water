#include "View.h"

MenuItem menu[MENU_SIZE] = {
  {"Moisture", "ADC:     |%:    "},
  {"Pump State", "Pump:    "}
};

View::View (
  LiquidCrystal_I2C & lcd,
  int & newMenuItem,
  int & sensorValue,
  int & soilMoisturePercent,
  bool & pumpOutput) :
    lcd(lcd),
    newMenuItem(newMenuItem),
    currentMenuItem(-1),
    lastADCViewUpdateTime(0),
    ADCViewUpdateInterval(500),
    sensorValue(sensorValue),
    soilMoisturePercent(soilMoisturePercent),
    pumpOutput(pumpOutput)
  {};

void View::redrawMenu()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(currentMenuItem+1);
  lcd.print(": ");
  lcd.print(menu[currentMenuItem].title);
  lcd.setCursor(0, 1);
  lcd.print(menu[currentMenuItem].templ);
}

void View::lcdUpdate()
{
  if (currentMenuItem != newMenuItem)
  {
    currentMenuItem = newMenuItem;
    redrawMenu();
  }

  switch(currentMenuItem)
  {
  case SENSOR_STATUS:
    sensorStatusView();
    break;
  case PUMP_STATUS:
    pumpStatusView();
    break;
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
