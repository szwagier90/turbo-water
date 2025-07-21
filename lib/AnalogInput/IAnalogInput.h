#ifndef I_ANALOG_INPUT_H
#define I_ANALOG_INPUT_H

class IAnalogInput
{
public:
    virtual int read() = 0;
};

#endif // I_ANALOG_INPUT_H
