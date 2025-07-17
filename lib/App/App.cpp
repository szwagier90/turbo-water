#include "App.h"

App::App(
    ISerial& serial
) : serial(serial) {}

void App::setup() {
    serial.begin(115200);
};

void App::loop()
{
}
