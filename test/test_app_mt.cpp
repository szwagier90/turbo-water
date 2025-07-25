#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <App.h>

#include <AnalogInput.h>
#include <Pump.h>
#include <SoilMoistureSensor.h>

#include "mocks/mock_serial.h"
#include "mocks/mock_lcd.h"
#include "mocks/mock_delay.h"
#include "mocks/mock_gpio.h"

using ::testing::StrEq;

const int sensorGpioPin = 1;
const int pumpGpioPin = 2;

TEST(AppTest, PeripherialsInitialization)
{
    MockSerial serial;
    MockLcd lcd;
    MockDelay delay;
    MockGpio gpio;
    EXPECT_CALL(gpio, pinMode);
    EXPECT_CALL(gpio, setAnalogReferenceExternal);
    AnalogInput analogInput(gpio, sensorGpioPin);
    SoilMoistureSensor s_m_sensor(analogInput);
    EXPECT_CALL(gpio, pinMode);
    Pump pump(gpio, pumpGpioPin);
    App app(
        serial
        , lcd
        , delay
        , s_m_sensor
        , pump
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
