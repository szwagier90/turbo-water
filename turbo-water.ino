#include "LiquidCrystal_I2C.h"

#include <EEPROM.h>
#include <Encoder.h>

#include <ezButton.h>

#include "Calibration.h"
#include "Model.h"
#include "MyEeprom.h"
#include "Plant.h"
#include "Pump.h"
#include "Sensor.h"
#include "View.h"

const int SHORT_PRESS_TIME = 100; // 100 milliseconds
const int LONG_PRESS_TIME  = 3000; // 1000 milliseconds

const int buttonInputPin = D0;
ezButton button(buttonInputPin, INPUT_PULLUP);

unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;
bool isPressing = false;
bool isShortDetected = false;
bool isLongDetected = false;

Calibration cal;
Sensor sensor;

Plant plant;

const int pumpOutputPin = D5;
bool pumpOutput = LOW;

const int sensorPin = A0;
int sensorValue = 0;
int soilMoisturePercent = 0;

unsigned buttonInput = 0;

#define ENCODER_PIN_A D6
#define ENCODER_PIN_B D7

Encoder encoder(ENCODER_PIN_A, ENCODER_PIN_B);
int menuIndex = 0;

Pump pump(pumpOutput);

Model model = {0};

View v(model);

void setup() {
  delay(100);
  Serial.begin(115200);
  delay(100);
  Serial.println("SERIAL INIT");

  v.lcdInit();
  pumpOutputInit();
  analogInputInit();
  buttonInputInit();
  soilMoistureSensorInit();

  if(!loadEepromData(sensor))
  {
    sensor.state = Sensor_NonCalibrated;
  }
  else
  {
    sensor.state = Sensor_CalibrationOK;
  }
}

void loop() {
  handleButton();
  handleMenu();

  sensorValue = analogRead(sensorPin);
  model.moistureAdcValue = sensorValue;

  switch(sensor.state)
  {
    case Sensor_NonCalibrated:
      break;
    case Sensor_CalibrationOK:
      normal();
      break;
  }


  digitalWrite(pumpOutputPin, pumpOutput);
  v.update();

  isShortDetected = false;
  isLongDetected = false;
}

void normal()
{
  soilMoisturePercent = map(sensorValue, sensor.soilMoistureDry, sensor.soilMoistureWet, 0, 100);
  model.moisturePercent = soilMoisturePercent;

  if(millis() - plant.pumpLastActivationTime > plant.pumpIntervalTime)
  {
    if(soilMoisturePercent < plant.soilMoistureThreshold && !pump.isActivated())
    {
      pump.pumpOn();
      model.pumpOnOffState = true;
      plant.pumpActivationStartTime = millis();
    }
  }

  if(pump.isActivated() && (millis() - plant.pumpActivationStartTime >= plant.pumpActivationTime))
  {
    pump.pumpOff();
    model.pumpOnOffState = false;
    plant.pumpLastActivationTime = millis();
  }
}

void pumpOutputInit()
{
  Serial.println("Pump Output Initialization");

  pinMode(pumpOutputPin, OUTPUT);
  digitalWrite(pumpOutputPin, LOW);
}

void analogInputInit()
{
  Serial.println("Analog Soil Moisture Sensor Input Initialization");
  analogReference(EXTERNAL); // set the analog reference to 3.3V
}

void buttonInputInit()
{
  Serial.println("Button Input Initialization");
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void soilMoistureSensorInit()
{
  Serial.println("Soil Moisture Sensor Initialization");

  sensorValue = analogRead(sensorPin);
  sensor.soilMoistureDry = sensorValue;
  sensor.soilMoistureWet = sensorValue + 1;
}

void handleButton()
{
  button.loop(); // MUST call the loop() function first

  if(button.isPressed())
  {
    pressedTime = millis();
    isPressing = true;
    isShortDetected = false;
    isLongDetected = false;
  }

  if(button.isReleased())
  {
    isPressing = false;
    releasedTime = millis();

    long pressDuration = releasedTime - pressedTime;

    if((pressDuration > SHORT_PRESS_TIME) && (pressDuration < LONG_PRESS_TIME))
    {
      Serial.println("A short press is detected");
      isShortDetected = true;
    }
    else if(pressDuration > LONG_PRESS_TIME)
    {
      Serial.println("A long press is detected");
      isLongDetected = true;
    }
  }
}

void handleMenu()
{
  int newMenuIndex = (encoder.read() / 4) % MENU_SIZE;
  if(newMenuIndex < 0)
  {
    encoder.write((MENU_SIZE - 1) * 4);
    newMenuIndex = MENU_SIZE - 1;
  }

  if (menuIndex != newMenuIndex)
  {
    menuIndex = newMenuIndex;

    Serial.print("Menu: ");
    Serial.println(menu2str(menuIndex));

    v.displayMenu(menuIndex);
  }

  switch(menuIndex)
  {
    case SENSOR_STATUS:
      break;
    case SENSOR_CALIBRATION:
      model.calibrationState = handleCalibration();
      break;
    case PUMP_STATUS:
      break;
    case FACTORY_RESET:
      if(isShortDetected)
      {
        readEepromMemory();
      }
      else if(isLongDetected)
      {
        Serial.println("Clear EEPROM Memory!!!");
        eepromClearMemory();
        sensor.reset();
      }
      break;
  }
}

Calibration_States handleCalibration()
{
  switch(cal.state)
  {
    case Calibration_Ready:
      if(isShortDetected)
      {
        cal.startCalibration(&sensor);
      }
      else if(isLongDetected)
      {
        sensor.calibrate(sensor.soilMoistureDry, sensor.soilMoistureWet);
        saveCalibrationData(sensor);
      }
      break;
    case Calibration_Dry:
      if(isShortDetected)
      {
        cal.saveDryValue(model.moistureAdcValue);
      }
      break;
    case Calibration_Wet:
      if(isShortDetected)
      {
        cal.saveWetValue(model.moistureAdcValue);
      }
      break;
    case Calibration_Confirm:
      if(isShortDetected)
      {
        cal.calibrateSensor();
        saveCalibrationData(sensor);
      }
      break;
  }

  return cal.state;
}
