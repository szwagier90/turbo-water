#ifndef MOCK_ANALOG_INPUT_H
#define MOCK_ANALOG_INPUT_H

#include "IAnalogInput.h"

class MockAnalogInput : public IAnalogInput
{
public:
    MOCK_METHOD(int, read, (), (override));
};

#endif // MOCK_ANALOG_INPUT_H
