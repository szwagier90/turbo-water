#ifdef ARDUINO
#include <Arduino.h>

#include <App.h>
#include <SerialAdapter.h>
#include <LcdAdapter.h>
#include <DelayAdapter.h>
#include <Pump.h>

SerialAdapter serial;
LcdAdapter lcd(0x27,16,2);  // I2C address: 0x27 | LCD: 16x2
DelayAdapter delayAdapter;
Pump pump;
App app(
    serial
    , lcd
    , delayAdapter
    , pump
);

void setup()
{
    app.setup();
}

void loop()
{
    app.loop();
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
