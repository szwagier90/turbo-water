#ifndef I_GPIO_H
#define I_GPIO_H

#include <stdint.h>

enum class PinMode
{
    Input,
    Output,
    InputPullup
};

class IGpio
{
public:
    virtual void pinMode(uint8_t pin, PinMode mode) = 0;
};

#endif // I_GPIO_H
