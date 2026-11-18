#ifndef MOCK_TIME_PROVIDER_H
#define MOCK_TIME_PROVIDER_H

#include "ITimeProvider.h"

class MockTimeProvider : public ITimeProvider
{
public:
    MOCK_METHOD(unsigned, millis, (), (const, override));
};

#endif // MOCK_TIME_PROVIDER_H
