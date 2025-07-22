#include "Pump.h"

Pump::Pump(
    IGpio& gpio
    , uint8_t pin
)
    : gpio(gpio)
    , pin(pin)
{
    gpio.pinMode(pin, PinMode::Output);
}

void Pump::on()
{
    gpio.digitalWrite(pin, PinOutput::High);
}

void Pump::off()
{
    gpio.digitalWrite(pin, PinOutput::Low);
}
