#ifndef MOCK_TIME_PROVIDER_H
#define MOCK_TIME_PROVIDER_H

#include "IMockTimeProvider.h"

class MockTimeProvider : public IMockTimeProvider
{
public:
    MOCK_METHOD(unsigned, millis, (), (const, override));
};

#endif // MOCK_TIME_PROVIDER_H
