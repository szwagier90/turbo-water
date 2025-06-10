#ifndef MOCK_SERIAL_H
#define MOCK_SERIAL_H

#include "ISerial.h"

class MockSerial : public ISerial
{
public:
    MOCK_METHOD(void, begin, (unsigned long), (override));
    MOCK_METHOD(void, println, (const char*), (override));
};

#endif // MOCK_SERIAL_H
