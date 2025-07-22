#ifndef I_GPIO_H
#define I_GPIO_H

#include <stdint.h>

enum class PinMode
{
    Input,
    Output,
    InputPullup
};

enum class PinOutput
{
    Low,
    High
};

class IGpio
{
public:
    virtual void pinMode(uint8_t pin, PinMode mode) = 0;
    virtual int analogRead(uint8_t pin) = 0;
    virtual void digitalWrite(uint8_t pin, PinOutput mode) = 0;
    virtual void setAnalogReferenceExternal() = 0;
};

#endif // I_GPIO_H
