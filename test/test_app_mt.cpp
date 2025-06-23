#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <App.h>

#include "mocks/mock_serial.h"
#include "mocks/mock_lcd.h"
#include "mocks/mock_delay.h"

using ::testing::StrEq;

TEST(AppTest, PeripherialsInitialization)
{
    MockSerial serial;
    MockLcd lcd;
    MockDelay delay;
    App app(
        serial
        , lcd
        , delay
    );

    EXPECT_CALL(serial, begin(115200));
    EXPECT_CALL(serial, println(StrEq("SERIAL_INIT")));
    EXPECT_CALL(lcd, init(4, 5));
    EXPECT_CALL(lcd, backlight);
    EXPECT_CALL(lcd, print(" PLANT WATERING "));
    EXPECT_CALL(lcd, setCursor(0, 1));
    EXPECT_CALL(lcd, print("     SYSTEM     "));
    EXPECT_CALL(serial, println(StrEq("LCD Initialization")));
    EXPECT_CALL(delay, delay(2000));
    EXPECT_CALL(lcd, clear);
    app.setup();
}
