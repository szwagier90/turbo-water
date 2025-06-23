#ifndef I_LCD_H
#define I_LCD_H

#include <stdint.h>

class ILcd
{
public:
    virtual void init(uint8_t sdaPort, uint8_t sclPort) = 0;
    virtual void backlight() = 0;
    virtual ~ILcd() = default;
};

#endif // I_LCD_H
