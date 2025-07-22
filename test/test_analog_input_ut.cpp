#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <AnalogInput.h>

#include "mocks/mock_gpio.h"

using ::testing::Return;


TEST(AnalogInput_UT, Init)
{
    const int sensorGpioPin = 1;
    const int expectedValue = 512;

    MockGpio gpio;

    EXPECT_CALL(gpio, pinMode(sensorGpioPin, PinMode::Input));
    EXPECT_CALL(gpio, setAnalogReferenceExternal);
    EXPECT_CALL(gpio, analogRead(sensorGpioPin)).WillOnce(Return(512));

    AnalogInput analogInput(gpio, sensorGpioPin);

    EXPECT_EQ(analogInput.read(), expectedValue);
}
