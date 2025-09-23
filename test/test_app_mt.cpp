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
#include "mocks/mock_gpio.h"

using ::testing::Return;
using ::testing::StrEq;

const int sensorGpioPin = 1;
const int pumpGpioPin = 2;
const int buttonGpioPin = 0;

TEST(AppTest, PeripherialsInitialization)
{
    MockSerial serial;
    MockLcd lcd;
    MockDelay delay;
    MockGpio sensorGpio;
    MockGpio pumpGpio;
    EXPECT_CALL(sensorGpio, pinMode);
    EXPECT_CALL(sensorGpio, setAnalogReferenceExternal);
    AnalogInput analogInput(sensorGpio, sensorGpioPin);
    SoilMoistureSensor s_m_sensor(analogInput);
    EXPECT_CALL(pumpGpio, pinMode);
    Pump pump(pumpGpio, pumpGpioPin);
    MockButtonController button;
    App app(
        serial
        , lcd
        , delay
        , s_m_sensor
        , pump
        , button
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
    EXPECT_CALL(button, setDebounceTime);
    app.setup();
}

class AppBasicSetupFixture : public ::testing::Test
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
    MockGpio sensorGpio;
    MockGpio pumpGpio;
    AnalogInput analogInput;
    SoilMoistureSensor s_m_sensor;
    Pump pump;
    MockButtonController button;
    App app;

    AppBasicSetupFixture() :
        analogInput(sensorGpio, sensorGpioPin)
        , s_m_sensor(analogInput)
        , pump(pumpGpio, pumpGpioPin)
        , app(
            serial
            , lcd
            , delay
            , s_m_sensor
            , pump
            , button
        ) {};
};

TEST_F(AppBasicSetupFixture, DontReadSensorIfNotCalibrated)
{
    EXPECT_CALL(sensorGpio, analogRead).Times(0);
    EXPECT_CALL(pumpGpio, digitalWrite).Times(0);
    app.loop();
}

TEST_F(AppBasicSetupFixture, ReadSensorIfCalibrated)
{
    s_m_sensor.calibrate(1, 2);
    EXPECT_CALL(sensorGpio, analogRead).Times(1);
    EXPECT_CALL(pumpGpio, digitalWrite).Times(1);
    app.loop();
}

TEST_F(AppBasicSetupFixture, ButtonLoopAtTheBeginning)
{
    EXPECT_CALL(button, loop);
    app.loop();
}

TEST_F(AppBasicSetupFixture, CanDetectButtonShortPress)
{
    EXPECT_CALL(button, loop);
    EXPECT_CALL(button, isShortPressed);
    app.loop();
}

TEST_F(AppBasicSetupFixture, ReadSMSensorValueWhenButtonShortPressedButNotCalibrate)
{
    EXPECT_CALL(button, loop);
    EXPECT_CALL(button, isShortPressed).WillOnce(Return(true));
    EXPECT_CALL(sensorGpio, analogRead).Times(1);
    app.loop();
    EXPECT_FALSE(s_m_sensor.isCalibrated());
}

TEST_F(AppBasicSetupFixture, ReadTwoRawValuesForSensorCalibration)
{
    EXPECT_CALL(button, isShortPressed).WillOnce(Return(true));
    app.loop();
    EXPECT_CALL(button, isShortPressed).WillOnce(Return(true));
    app.loop();

    EXPECT_TRUE(s_m_sensor.isCalibrated());
}

TEST_F(AppBasicSetupFixture, CalculateCorrectSensorPercentValue)
{
    EXPECT_CALL(button, isShortPressed).WillOnce(Return(true));
    EXPECT_CALL(sensorGpio, analogRead).WillOnce(Return(1));
    app.loop();
    EXPECT_CALL(button, isShortPressed).WillOnce(Return(true));
    EXPECT_CALL(sensorGpio, analogRead).WillOnce(Return(100));
    app.loop();

    EXPECT_CALL(sensorGpio, analogRead).WillOnce(Return(90));
    EXPECT_GE(s_m_sensor.readPercent(), 80);
}
