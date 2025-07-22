#ifndef ANALOG_INPUT_H
#define ANALOG_INPUT_H

#include "IAnalogInput.h"

#include "IGpio.h"


class AnalogInput : public IAnalogInput
{
public:
    AnalogInput(
        IGpio& gpio
        , uint8_t pin
    );

    int read() override;

private:
    IGpio& gpio;
    uint8_t pin;
};

#endif // ANALOG_INPUT_H
