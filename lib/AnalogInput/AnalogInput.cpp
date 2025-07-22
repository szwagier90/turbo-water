#include "AnalogInput.h"


AnalogInput::AnalogInput(
    IGpio& gpio
    , uint8_t pin
)
    : gpio(gpio)
    , pin(pin)
{
    gpio.pinMode(pin, PinMode::Input);
    gpio.setAnalogReferenceExternal();
}

int AnalogInput::read()
{
	return gpio.analogRead(pin);
}
