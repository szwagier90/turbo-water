#ifndef PUMP_H
#define PUMP_H

#include "IPump.h"

#include "IGpio.h"


class Pump : public IPump
{
public:
    Pump(
        IGpio& gpio
        , uint8_t pin
    );

    void on() override;
    void off() override;

private:
    IGpio& gpio;
    uint8_t pin;
};

#endif // PUMP_H
