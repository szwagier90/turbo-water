#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <App.h>

#include "mocks/mock_serial.h"
#include "mocks/mock_lcd.h"
#include "mocks/mock_delay.h"
#include "mocks/mock_soil_moisture_sensor.h"
#include "mocks/mock_pump.h"
#include "mocks/mock_button_controller.h"

using ::testing::Return;

TEST(Initialization, BasicInit)
{
    MockSerial serial;
    MockLcd lcd;
    MockDelay delay;
    MockSoilMoistureSensor s_m_sensor;
    MockPump pump;
    MockButtonController button;
    App app(
        serial
        , lcd
        , delay
        , s_m_sensor
        , pump
        , button
    );

    EXPECT_CALL(serial, begin);
    EXPECT_CALL(serial, println).Times(2);
    EXPECT_CALL(lcd, init);
    EXPECT_CALL(lcd, backlight);
    EXPECT_CALL(lcd, print).Times(2);
    EXPECT_CALL(lcd, setCursor);
    EXPECT_CALL(delay, delay);
    EXPECT_CALL(lcd, clear);
    EXPECT_CALL(button, setDebounceTime);

    app.setup();
}

class ApplicationSimpleWateringFixture : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    MockSerial serial;
    MockLcd lcd;
    MockDelay delay;
    MockSoilMoistureSensor s_m_sensor;
    MockPump pump;
    MockButtonController button;
    App app;

    ApplicationSimpleWateringFixture() : app(
        serial
        , lcd
        , delay
        , s_m_sensor
        , pump
        , button
    ) {};
};

TEST_F(ApplicationSimpleWateringFixture, DoNotTurnPumpOnWhenMoistureAboveThreshold)
{
    EXPECT_CALL(s_m_sensor, isCalibrated).WillOnce(Return(true));
    EXPECT_CALL(s_m_sensor, readPercent).WillOnce(Return(50));
    EXPECT_CALL(pump, on).Times(0);
    app.loop();
}

TEST_F(ApplicationSimpleWateringFixture, TurnPumpOffWhenMoistureAboveThreshold)
{
    EXPECT_CALL(s_m_sensor, isCalibrated).WillRepeatedly(Return(true));
    EXPECT_CALL(s_m_sensor, readPercent).WillOnce(Return(19));
    EXPECT_CALL(pump, on).Times(1);
    app.loop();
    EXPECT_CALL(s_m_sensor, readPercent).WillOnce(Return(21));
    EXPECT_CALL(pump, off).Times(1);
    app.loop();
}

TEST_F(ApplicationSimpleWateringFixture, DoNotWaterIfSensorNotCalibrated)
{
    EXPECT_CALL(s_m_sensor, isCalibrated).WillOnce(Return(false));
    EXPECT_CALL(s_m_sensor, readPercent).Times(0);
    app.loop();
}

TEST_F(ApplicationSimpleWateringFixture, LoopButton)
{
    EXPECT_CALL(button, loop);
    app.loop();
}

TEST_F(ApplicationSimpleWateringFixture, CanReadRawSensorValue)
{
    EXPECT_CALL(button, loop);
    EXPECT_CALL(button, isShortPressed).WillOnce(Return(true));
    EXPECT_CALL(s_m_sensor, readRaw);
    EXPECT_CALL(s_m_sensor, calibrate).Times(0);
    app.loop();
}

TEST_F(ApplicationSimpleWateringFixture, ReadTwoRawValuesForSensorCalibration)
{
    EXPECT_CALL(button, isShortPressed).WillOnce(Return(true));
    app.loop();

    EXPECT_CALL(button, isShortPressed).WillOnce(Return(true));
    EXPECT_CALL(s_m_sensor, calibrate).Times(1);
    app.loop();
}
