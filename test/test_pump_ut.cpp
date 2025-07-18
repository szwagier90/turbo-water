#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Pump.h>

#include "mocks/mock_gpio.h"


TEST(Pump_UT, InitializeWithOutputPinMode)
{
    const int pumpGpioPin = 2;

    MockGpio gpio;
    EXPECT_CALL(gpio, pinMode(pumpGpioPin, PinMode::Output));

    Pump pump(gpio, pumpGpioPin);
}

TEST(Pump_UT, TurnPumpOn)
{
    const int pumpGpioPin = 2;

    MockGpio gpio;
    EXPECT_CALL(gpio, pinMode(pumpGpioPin, PinMode::Output));

    Pump pump(gpio, pumpGpioPin);

    EXPECT_CALL(gpio, digitalWrite(pumpGpioPin, PinOutput::High));
    pump.on();
}
