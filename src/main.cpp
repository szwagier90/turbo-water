#ifdef ARDUINO
#include <Arduino.h>

#include <App.h>
#include <SerialAdapter.h>
#include <LcdAdapter.h>
#include <DelayAdapter.h>
#include <GpioAdapter.h>
#include <AnalogInput.h>
#include <SoilMoistureSensor.h>
#include <Pump.h>

const int sensorGpioPin = A0;
const int pumpOutputPin = D5;

SerialAdapter serial;
LcdAdapter lcd(0x27,16,2);  // I2C address: 0x27 | LCD: 16x2
DelayAdapter delayAdapter;
GpioAdapter gpio;
AnalogInput analogInput(gpio, sensorGpioPin);
SoilMoistureSensor s_m_sensor(analogInput);
Pump pump(gpio, pumpOutputPin);
App app(
    serial
    , lcd
    , delayAdapter
    , s_m_sensor
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
