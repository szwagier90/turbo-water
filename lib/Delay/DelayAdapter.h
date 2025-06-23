#ifndef DELAY_ADAPTER_H
#define DELAY_ADAPTER_H

#include "IDelay.h"

#include <Arduino.h>

class DelayAdapter : public IDelay
{
public:
    void delay(unsigned long ms) override
    {
        ::delay(ms);
    };
};

#endif // DELAY_ADAPTER_H
