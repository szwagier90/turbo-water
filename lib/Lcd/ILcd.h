#ifndef I_LCD_H
#define I_LCD_H

#include <stdint.h>
#include <string>

class ILcd
{
public:
    virtual void init(uint8_t sdaPort, uint8_t sclPort) = 0;
    virtual void clear() = 0;
    virtual void print(const std::string&) = 0;
    virtual void backlight() = 0;
    virtual void setCursor(uint8_t col, uint8_t row) = 0;
    virtual ~ILcd() = default;
};

#endif // I_LCD_H
