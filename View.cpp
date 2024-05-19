#include "View.h"

#include <Arduino.h>

MenuItem menu[MENU_SIZE] = {
  {"Moisture", "ADC:     |%:    "},
  {"Pump State", "Pump:    "}
};

View::View (
  int & newMenuItem,
  int & sensorValue,
  int & soilMoisturePercent,
  bool & pumpOutput) :
    lcd(0x27,16,2),  // I2C address: 0x27 | LCD: 16x2),
    newMenuItem(newMenuItem),
    currentMenuItem(-1),
    lastADCViewUpdateTime(0),
    ADCViewUpdateInterval(500),
    sensorValue(sensorValue),
    soilMoisturePercent(soilMoisturePercent),
    pumpOutput(pumpOutput)
  {};

void View::lcdInit()
{
  Serial.println("LCD Initialization");

  lcd.init();
  lcd.backlight();
  lcd.print(" PLANT WATERING ");
  lcd.setCursor(0,1);
  lcd.print("     SYSTEM     ");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Pump: ");
}

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
