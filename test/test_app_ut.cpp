#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <App.h>

#include "mocks/mock_serial.h"
#include "mocks/mock_lcd.h"
#include "mocks/mock_delay.h"
#include "mocks/mock_soil_moisture_sensor.h"
#include "mocks/mock_pump.h"

using ::testing::Return;

class ApplicationSimpleWateringFixture : public ::testing::Test
{
protected:
    void SetUp() override
    {
        EXPECT_CALL(serial, begin);
        EXPECT_CALL(serial, println).Times(2);
        EXPECT_CALL(lcd, init);
        EXPECT_CALL(lcd, backlight);
        EXPECT_CALL(lcd, print).Times(2);
        EXPECT_CALL(lcd, setCursor);
        EXPECT_CALL(delay, delay);
        EXPECT_CALL(lcd, clear);
        app.setup();
    }

    void TearDown() override
    {
    }

    MockSerial serial;
    MockLcd lcd;
    MockDelay delay;
    MockSoilMoistureSensor s_m_sensor;
    MockPump pump;
    App app;

    ApplicationSimpleWateringFixture() : app(
        serial
        , lcd
        , delay
        , s_m_sensor
        , pump
    ) {};
};

TEST_F(ApplicationSimpleWateringFixture, TurnPumpOn)
{
    EXPECT_CALL(pump, on);
    app.loop();
}

TEST_F(ApplicationSimpleWateringFixture, DoNotTurnPumpOnWhenMoistureAboveThreshold)
{
    EXPECT_CALL(s_m_sensor, readPercent).WillOnce(Return(50));
    EXPECT_CALL(pump, on).Times(0);
    app.loop();
}
