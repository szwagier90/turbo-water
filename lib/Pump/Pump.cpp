#include "Pump.h"

Pump::Pump(
    IGpio& gpio
    , uint8_t pin
)
    : gpio(gpio)
    , pin(pin)
    , calibrated(false)
    , onOffState(false)
{
    gpio.pinMode(pin, PinMode::Output);
}

bool Pump::isCalibrated() const
{
    return calibrated;
}

void Pump::calibrate()
{
    calibrated = true;
}

void Pump::on()
{
    if (onOffState == false)
    {
        gpio.digitalWrite(pin, PinOutput::High);
        onOffState = true;
    }
}

void Pump::off()
{
    gpio.digitalWrite(pin, PinOutput::Low);
}
