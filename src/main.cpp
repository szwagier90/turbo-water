#ifdef ARDUINO
#include <Arduino.h>

#include <App.h>
#include <SerialAdapter.h>

SerialAdapter serial;
App app(
    serial
);

void setup()
{
    delay(100);
    app.setup();
    delay(100);
    Serial.println("SERIAL INIT");

    lcdInit();
}

void loop()
{
}

void lcdInit()
{
  Serial.println("LCD Initialization");

  lcd.init(4, 5);
  lcd.backlight();
  lcd.print(" PLANT WATERING ");
  lcd.setCursor(0,1);
  lcd.print("     SYSTEM     ");
  delay(2000);
  lcd.clear();
}

#else
// If compiled for native testing, provide an alternative entry point
#include <iostream>

int main()
{
    std::cout << "Running in native environment. No Arduino setup needed.\n";
    return 0;
}
#endif
