#ifndef ANALOG_INPUT_H
#define ANALOG_INPUT_H

#include "IAnalogInput.h"


class AnalogInput : public IAnalogInput
{
public:
    int read() override;

private:
};

#endif // ANALOG_INPUT_H
