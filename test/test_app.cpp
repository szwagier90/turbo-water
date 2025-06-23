#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <App.h>

#include "mocks/mock_serial.h"
#include "mocks/mock_lcd.h"

using ::testing::StrEq;

TEST(AppTest, Serial_InitMessage)
{
    MockSerial serial;
    MockLcd lcd;
    App app(
        serial,
        lcd
    );

    EXPECT_CALL(serial, begin(115200));
    EXPECT_CALL(serial, println(StrEq("SERIAL_INIT")));
    app.setup();
}

TEST(AppTest, Lcd_InitMessage)
{
    MockSerial serial;
    MockLcd lcd;
    App app(
        serial,
        lcd
    );

    EXPECT_CALL(lcd, init(4, 5));
    EXPECT_CALL(lcd, backlight);
    EXPECT_CALL(lcd, print(" PLANT WATERING "));
    app.setup();
}
