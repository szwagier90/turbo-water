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

    void clear() override
    {
        lcd.clear();
    }

    void print(const std::string& str) override
    {
        lcd.print(str.c_str());
    }

    void backlight() override
    {
        lcd.backlight();
    }

    void setCursor(uint8_t col, uint8_t row) override
    {
        lcd.setCursor(col, row);
    }

private:
    LiquidCrystal_I2C lcd;
};

#endif // LCD_ADAPTER_H
