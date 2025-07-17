#ifndef MOCK_PUMP_H
#define MOCK_PUMP_H

#include "IPump.h"

class MockPump : public IPump
{
public:
    MOCK_METHOD(void, on, (), (override));
};

#endif // MOCK_PUMP_H
