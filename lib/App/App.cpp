#include "App.h"

App::App(
    ISerial& serial
    , ILcd& lcd
    , IDelay& delay
) :
    serial(serial)
    , lcd(lcd)
    , delay(delay)
{}

void App::setup() {
    serial.begin(115200);
    serial.println("SERIAL_INIT");

    lcd.init(4, 5);
    lcd.backlight();
    lcd.print(" PLANT WATERING ");
    lcd.setCursor(0,1);
    lcd.print("     SYSTEM     ");
    serial.println("LCD Initialization");

    delay.delay(2000);
    lcd.clear();
};

void App::loop()
{
}
