#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27,16,2);  // I2C address: 0x27 | LCD: 16x2

const int pumpOutputPin = D5;
bool pumpOutput = LOW;

void setup() {
  delay(100);
  Serial.begin(115200);
  delay(100);
  Serial.println("SERIAL INIT");

  lcdInit();
  pumpOutputInit();
}

void loop() {
  pumpOn();
  delay(200);
  pumpOff();
  delay(200);
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
}

void pumpOutputInit()
{
  Serial.println("Pump Output Initialization");

  pinMode(pumpOutputPin, OUTPUT);
  digitalWrite(pumpOutputPin, LOW);
}

void pumpOn()
{
  pumpSet(HIGH);
}

void pumpOff()
{
  pumpSet(LOW);
}

void pumpSet(bool v)
{
  if(v != pumpOutput)
  {
    Serial.print("Pump: ");
    Serial.println(v ? "On" : "Off");
    pumpOutput = v;
    digitalWrite(pumpOutputPin, pumpOutput);
  }
}
