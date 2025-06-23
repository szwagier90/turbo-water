#ifndef MOCK_DELAY_H
#define MOCK_DELAY_H

#include "IDelay.h"

class MockDelay : public IDelay
{
public:
    MOCK_METHOD(void, delay, (unsigned long), (override));
};

#endif // MOCK_DELAY_H
