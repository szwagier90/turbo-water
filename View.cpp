#include "View.h"

#include <Arduino.h>

#include "Calibration.h"

MenuItem menu[MENU_SIZE] = {
  {"Moisture", "ADC:     |%:    "},
  {"Sensor Calib ", "Sensor: --------"},
  {"Pump State", "Pump:    "},
  {"Pump Calibration", "Pump:    "},
  {"FACTORY RESET", "LONGPRESS TO RST"}
};

View::View (Model & model) :
    model(model),
    lcd(0x27,16,2),  // I2C address: 0x27 | LCD: 16x2),
    menuIndex(0),
    lastADCViewUpdateTime(0),
    ADCViewUpdateInterval(500),
    pumpOnOffState(false)
  {};

void View::lcdInit()
{
  Serial.println("LCD Initialization");

  lcd.init();
  lcd.backlight();
  lcd.clear();
  initSplash();
  displayMenu(0);
}

void View::initSplash()
{
  lcd.print(" PLANT WATERING ");
  lcd.setCursor(0,1);
  lcd.print("     SYSTEM     ");
  delay(2000);
}

void View::displayMenu(int menuIndex)
{
  this->menuIndex = menuIndex;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(this->menuIndex+1);
  lcd.print(": ");
  lcd.print(menu[this->menuIndex].title);
  lcd.setCursor(0, 1);
  lcd.print(menu[this->menuIndex].templ);

  update();
}

void View::update()
{
  switch(this->menuIndex)
  {
  case SENSOR_STATUS:
    sensorStatusView();
    break;
  case SENSOR_CALIBRATION:
    sensorCalibrationView();
    break;
  case PUMP_STATUS:
    pumpStatusView();
    break;
  case FACTORY_RESET:
    factoryResetView();
  }
}

void View::sensorStatusView()
{
  if((millis()-lastADCViewUpdateTime) > ADCViewUpdateInterval)
  {
    lcd.setCursor(5, 1);
    lcd.print(model.moistureAdcValue);
    lcd.setCursor(13, 1);
    lcd.print(model.moisturePercent);
  }
}

void View::sensorCalibrationView()
{
  lcd.setCursor(8, 1);

  switch(model.calibrationState)
  {
    case Calibration_Ready:
      lcd.print("Ready ");
      break;
    case Calibration_Dry:
      lcd.print("Dry ");
      break;
    case Calibration_Wet:
      lcd.print("Wet ");
      break;
    case Calibration_Confirm:
      lcd.print("Save? ");
      break;
    default:
      lcd.print("Unknown ");
      break;
  }
}

void View::pumpStatusView()
{
  if(pumpOnOffState != model.pumpOnOffState)
  {
    pumpOnOffState = model.pumpOnOffState;
    lcd.setCursor(6, 1);
    lcd.print(pumpOnOffState ? "On " : "Off");
  }
}

void View::factoryResetView()
{
}
