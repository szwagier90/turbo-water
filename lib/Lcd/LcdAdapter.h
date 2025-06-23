#ifndef LCD_ADAPTER_H
#define LCD_ADAPTER_H

#include "ILcd.h"

#include <LiquidCrystal_I2C.h>

class LcdAdapter : public ILcd
{
public:
    LcdAdapter(uint8_t address, uint8_t col, uint8_t row)
        : lcd(address, col, row) {}

    void init(uint8_t sdaPort, uint8_t sclPort) override
    {
        lcd.init(sdaPort, sclPort);
    }

private:
    LiquidCrystal_I2C lcd;
};

#endif // LCD_ADAPTER_H
