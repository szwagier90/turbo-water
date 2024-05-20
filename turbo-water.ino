#include "LiquidCrystal_I2C.h"

#include <EEPROM.h>
#include <Encoder.h>
#include "Pump.h"
#include "View.h"

#define EEPROM_VERSION 1

struct Eeprom {
  uint16_t soilMoistureMin;
  uint16_t soilMoistureMax;
  uint8_t version;
};

Eeprom eeprom = {0};

typedef enum { STATE_CALIBRATION,
               STATE_NORMAL } States;

// current state-machine state
States state = STATE_CALIBRATION;

const int pumpOutputPin = D5;
bool pumpOutput = LOW;

const int sensorPin = A0;
int sensorValue = 0;
int soilMoisturePercent = 0;
const int soilMoistureThreshold = 30;
unsigned int soilMoistureMin = 10000;
unsigned int soilMoistureMax = 0;

const int buttonInputPin = D0;
unsigned buttonInput = 0;

const unsigned long pumpActivationTime = 5000; // 5 seconds (adjust as needed)
unsigned long pumpActivationStartTime = 0;

const unsigned long pumpIntervalTime = 10000; // 10 seconds
unsigned long pumpLastActivationTime = 0;

#define ENCODER_PIN_A D6
#define ENCODER_PIN_B D7

Encoder encoder(ENCODER_PIN_A, ENCODER_PIN_B);

int newMenuItem = -1;

Pump pump(pumpOutput);

Model model = {0};

View v(model, newMenuItem);

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

  if(!loadEepromData())
  {
    state = STATE_CALIBRATION;
  }
  else
  {
    state = STATE_NORMAL;
  }
}

void loop() {
  buttonInput = digitalRead(buttonInputPin);
  sensorValue = analogRead(sensorPin);
  model.moistureAdcValue = sensorValue;

  newMenuItem = (encoder.read() / 4) % MENU_SIZE;
  if(newMenuItem < 0)
  {
    encoder.write((MENU_SIZE - 1) * 4);
    newMenuItem = MENU_SIZE - 1;
  }

  switch(state)
  {
    case STATE_CALIBRATION:
      calibration();

      if(buttonInput)
      {
        state = STATE_NORMAL;
        saveCalibrationData();
      }
      break;
    case STATE_NORMAL:
      normal();
      break;
  }


  digitalWrite(pumpOutputPin, pumpOutput);
  v.lcdUpdate();
}

void calibration()
{
  if (sensorValue < soilMoistureMin)
    soilMoistureMin = sensorValue;
  if (sensorValue > soilMoistureMax)
    soilMoistureMax = sensorValue;

}

void normal()
{
  soilMoisturePercent = map(sensorValue, soilMoistureMax, soilMoistureMin, 0, 100);
  model.moisturePercent = soilMoisturePercent;

  if(millis() - pumpLastActivationTime > pumpIntervalTime)
  {
    if(soilMoisturePercent < soilMoistureThreshold && !pump.isActivated())
    {
      pump.pumpOn();
      model.pumpOnOffState = true;
      pumpActivationStartTime = millis();
    }
  }

  if(pump.isActivated() && (millis() - pumpActivationStartTime >= pumpActivationTime))
  {
    pump.pumpOff();
    model.pumpOnOffState = false;
    pumpLastActivationTime = millis();
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
  pinMode(buttonInputPin, INPUT);
}

void soilMoistureSensorInit()
{
  Serial.println("Soil Moisture Sensor Initialization");

  sensorValue = analogRead(sensorPin);
  soilMoistureMin = sensorValue;
  soilMoistureMax = sensorValue + 1;
}

bool loadEepromData()
{
  EEPROM.begin(sizeof(Eeprom));
  delay(20);
  EEPROM.get(0, eeprom);

  Serial.print("EEPROM Length: ");
  Serial.println(EEPROM.length());
  Serial.print("EEPROM: SMMin - ");
  Serial.print(eeprom.soilMoistureMin);
  Serial.print(" | SMMax -  ");
  Serial.print(eeprom.soilMoistureMax);
  Serial.print(" | Version -  ");
  Serial.println(eeprom.version);

  if(EEPROM_VERSION != eeprom.version)
  {
    Serial.println("EEPROM: Version mismatch or no data");
    eepromClearMemory();
    return false;
  }

  soilMoistureMin = eeprom.soilMoistureMin;
  soilMoistureMax = eeprom.soilMoistureMax;
  Serial.println("EEPROM: Data loaded");

  EEPROM.end();

  return true;
}

void saveCalibrationData() {
  EEPROM.begin(sizeof(Eeprom));
  delay(20);

  eeprom.soilMoistureMin = soilMoistureMin;
  eeprom.soilMoistureMax = soilMoistureMax;
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
