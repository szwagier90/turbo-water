#include "LiquidCrystal_I2C.h"
#include "Pump.h"

LiquidCrystal_I2C lcd(0x27,16,2);  // I2C address: 0x27 | LCD: 16x2

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

Pump pump(pumpOutput);

void setup() {
  delay(100);
  Serial.begin(115200);
  delay(100);
  Serial.println("SERIAL INIT");

  lcdInit();
  pumpOutputInit();
  analogInputInit();
  buttonInputInit();
  soilMoistureSensorInit();
}

void loop() {
  buttonInput = digitalRead(buttonInputPin);
  sensorValue = analogRead(sensorPin);

  switch(state)
  {
    case STATE_CALIBRATION:
      calibration();

      if(buttonInput)
      {
        state = STATE_NORMAL;
      }
      break;
    case STATE_NORMAL:
      normal();
      break;
  }


  digitalWrite(pumpOutputPin, pumpOutput);
  lcdUpdate();
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

  if(millis() - pumpLastActivationTime > pumpIntervalTime)
  {
    if(soilMoisturePercent < soilMoistureThreshold && !pump.isActivated())
    {
      pump.pumpOn();
      pumpActivationStartTime = millis();
    }
  }

  if(pump.isActivated() && (millis() - pumpActivationStartTime >= pumpActivationTime))
  {
    pump.pumpOff();
    pumpLastActivationTime = millis();
  }
}

void lcdInit()
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

void lcdUpdate()
{
  lcd.setCursor(6, 0);
  lcd.print(pumpOutput ? "On " : "Off");
}

void soilMoistureSensorInit()
{
  Serial.println("Soil Moisture Sensor Initialization");

  sensorValue = analogRead(sensorPin);
  soilMoistureMin = sensorValue;
  soilMoistureMax = sensorValue + 1;
}
