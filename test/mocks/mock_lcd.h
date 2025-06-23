#ifndef MOCK_LCD_H
#define MOCK_LCD_H

#include "ILcd.h"

class MockLcd : public ILcd
{
public:
    MOCK_METHOD(void, init, (uint8_t, uint8_t), (override));
};

#endif // MOCK_LCD_H
