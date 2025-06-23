#include "App.h"

App::App(
    ISerial& serial
    , ILcd& lcd
) :
    serial(serial)
    , lcd(lcd)
{}

void App::setup() {
    serial.begin(115200);
    serial.println("SERIAL_INIT");
};

void App::loop()
{
}
