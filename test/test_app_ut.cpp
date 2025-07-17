#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <App.h>

#include "mocks/mock_serial.h"
#include "mocks/mock_lcd.h"
#include "mocks/mock_delay.h"
#include "mocks/mock_pump.h"


TEST(App_UT, TurnPumpOn)
{
    MockSerial serial;
    MockLcd lcd;
    MockDelay delay;
    MockPump pump;
    App app(
        serial
        , lcd
        , delay
        , pump
    );

    EXPECT_CALL(serial, begin);
    EXPECT_CALL(serial, println).Times(2);
    EXPECT_CALL(lcd, init);
    EXPECT_CALL(lcd, backlight);
    EXPECT_CALL(lcd, print).Times(2);
    EXPECT_CALL(lcd, setCursor);
    EXPECT_CALL(delay, delay);
    EXPECT_CALL(lcd, clear);
    app.setup();

    EXPECT_CALL(pump, on);
    app.loop();
}
