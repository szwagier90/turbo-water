#ifndef GPIO_ADAPTER_H
#define GPIO_ADAPTER_H

#include "IGpio.h"

#include <Arduino.h>

class GpioAdapter : public IGpio
{
public:
    void pinMode(uint8_t pin, PinMode mode) override
    {
        ::pinMode(pin,
            mode == PinMode::Output ? OUTPUT :
            mode == PinMode::Input ? INPUT :
            INPUT_PULLUP);
    }

    void digitalWrite(uint8_t pin, PinOutput po) override
    {
        ::digitalWrite(pin, (uint8_t)po);
    }
};

#endif // GPIO_ADAPTER_H
