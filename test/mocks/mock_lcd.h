#ifndef MOCK_LCD_H
#define MOCK_LCD_H

#include "ILcd.h"

class MockLcd : public ILcd
{
public:
    MOCK_METHOD(void, init, (uint8_t, uint8_t), (override));
    MOCK_METHOD(void, print, (const std::string&), (override));
    MOCK_METHOD(void, backlight, (), (override));
};

#endif // MOCK_LCD_H
