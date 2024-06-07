#include "LiquidCrystal_I2C.h"

#include <EEPROM.h>
#include <Encoder.h>

#include <ezButton.h>

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
    sensor.state = STATE_CALIBRATION;
  }
  else
  {
    sensor.state = STATE_NORMAL;
  }
}

void loop() {
  handleButton();
  handleMenu();

  sensorValue = analogRead(sensorPin);
  model.moistureAdcValue = sensorValue;

  switch(sensor.state)
  {
    case STATE_CALIBRATION:
      calibration();

      if(button.isPressed())
      {
        sensor.state = STATE_NORMAL;
        saveCalibrationData(sensor);
      }
      break;
    case STATE_NORMAL:
      normal();
      break;
  }


  digitalWrite(pumpOutputPin, pumpOutput);
  v.update();

  isShortDetected = false;
  isLongDetected = false;
}

void calibration()
{
  if (sensorValue < sensor.soilMoistureWet)
    sensor.soilMoistureWet = sensorValue;
  if (sensorValue > sensor.soilMoistureDry)
    sensor.soilMoistureDry = sensorValue;
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
    case PUMP_STATUS:
      break;
    case FACTORY_RESET:
      if(isLongDetected)
      {
        Serial.println("Clear EEPROM Memory!!!");
        eepromClearMemory();
        sensor.state = STATE_CALIBRATION;
      }
      break;
  }
}
