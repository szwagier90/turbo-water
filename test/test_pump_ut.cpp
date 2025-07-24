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

class Pump_Initialized_UT_Fixture : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    const int pumpGpioPin = 2;
    MockGpio gpio;
    Pump pump;

    Pump_Initialized_UT_Fixture() : pump(gpio, pumpGpioPin) {}
};

TEST_F(Pump_Initialized_UT_Fixture, TurnPumpOn)
{
    EXPECT_CALL(gpio, digitalWrite(pumpGpioPin, PinOutput::High));
    pump.on();
}

TEST_F(Pump_Initialized_UT_Fixture, TurnPumpOff)
{
    EXPECT_CALL(gpio, digitalWrite(pumpGpioPin, PinOutput::Low));
    pump.off();
}
