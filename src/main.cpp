#ifdef ARDUINO
#include <Arduino.h>

#include <App.h>
#include <SerialAdapter.h>
#include <LcdAdapter.h>
#include <DelayAdapter.h>

SerialAdapter serial;
LcdAdapter lcd(0x27,16,2);  // I2C address: 0x27 | LCD: 16x2
DelayAdapter delayAdapter;
App app(
    serial,
    lcd,
    delayAdapter
);

void setup()
{
    app.setup();
}

void loop()
{
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
