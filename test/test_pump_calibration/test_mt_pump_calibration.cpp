#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <App.h>

#include <AnalogInput.h>
#include <Pump.h>
#include <SoilMoistureSensor.h>

#include "mocks/mock_button_controller.h"
#include "mocks/mock_serial.h"
#include "mocks/mock_lcd.h"
#include "mocks/mock_delay.h"
#include "mocks/mock_time_provider.h"
#include "mocks/mock_gpio.h"

using ::testing::Return;
using ::testing::StrEq;
using ::testing::NiceMock;

const int sensorGpioPin = 1;
const int pumpGpioPin = 2;
const int buttonGpioPin = 0;

const uint32_t firstPressTime = 2000;
const uint32_t firstReleaseTime = 3000;
const uint32_t secondPressTime = 5000;
const uint32_t secondReleaseTime = 10000;

class AppPumpCalibrationFixture : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    NiceMock<MockSerial> serial;
    NiceMock<MockLcd> lcd;
    NiceMock<MockDelay> delay;
    MockTimeProvider timeProvider;
    MockGpio sensorGpio;
    MockGpio pumpGpio;
    AnalogInput analogInput;
    SoilMoistureSensor s_m_sensor;
    Pump pump;
    MockButtonController button;
    App app;

    AppPumpCalibrationFixture() :
        analogInput(sensorGpio, sensorGpioPin)
        , s_m_sensor(analogInput)
        , pump(pumpGpio, pumpGpioPin)
        , app(
            serial
            , lcd
            , delay
            , timeProvider
            , s_m_sensor
            , pump
            , button
        ) {};

    void expectButtonPressTime(uint32_t t)
    {
        EXPECT_CALL(button, isPressed()).WillOnce(Return(true));
        EXPECT_CALL(button, isReleased()).WillOnce(Return(false));
        EXPECT_CALL(timeProvider, millis()).WillOnce(Return(t));
    }

    void expectButtonReleaseTime(uint32_t t)
    {
        EXPECT_CALL(button, isPressed()).WillOnce(Return(false));
        EXPECT_CALL(button, isReleased()).WillOnce(Return(true));
        EXPECT_CALL(timeProvider, millis()).WillOnce(Return(t));
    }
};

TEST_F(AppPumpCalibrationFixture, FirstButtonPressRunSavesFirstDuration)
{
    EXPECT_CALL(button, loop());
    EXPECT_CALL(pumpGpio, digitalWrite(pumpGpioPin, PinOutput::High));
    expectButtonPressTime(firstPressTime);
    app.loop();

    EXPECT_CALL(button, loop());
    expectButtonReleaseTime(firstReleaseTime);
    EXPECT_CALL(pumpGpio, digitalWrite(pumpGpioPin, PinOutput::Low));

    app.loop();

    EXPECT_EQ(app.duration1, firstReleaseTime - firstPressTime);
}

TEST_F(AppPumpCalibrationFixture, TwoButtonPressesRunSavesTwoDurations)
{
    EXPECT_CALL(button, loop());
    EXPECT_CALL(pumpGpio, digitalWrite(pumpGpioPin, PinOutput::High));
    expectButtonPressTime(firstPressTime);
    app.loop();

    EXPECT_CALL(button, loop());
    expectButtonReleaseTime(firstReleaseTime);
    EXPECT_CALL(pumpGpio, digitalWrite(pumpGpioPin, PinOutput::Low));

    app.loop();

    EXPECT_CALL(button, loop());
    EXPECT_CALL(pumpGpio, digitalWrite(pumpGpioPin, PinOutput::High));
    expectButtonPressTime(secondPressTime);
    app.loop();

    EXPECT_CALL(button, loop());
    expectButtonReleaseTime(secondReleaseTime);
    EXPECT_CALL(pumpGpio, digitalWrite(pumpGpioPin, PinOutput::Low));

    app.loop();

    EXPECT_EQ(app.duration1, firstReleaseTime - firstPressTime);
    EXPECT_EQ(app.duration2, secondReleaseTime - secondPressTime);
    EXPECT_NEAR(app.getPumpFlowA(), 0.075f, 1e-5f);
    EXPECT_NEAR(app.getPumpFlowB(), 125.0f, 1e-5f);
}
