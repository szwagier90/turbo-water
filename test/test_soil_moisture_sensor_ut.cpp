#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <SoilMoistureSensor.h>

#include "mocks/mock_analogInput.h"

using ::testing::Return;


TEST(SoilMoistureSensor_UT, ReadPercentSimple)
{
    MockAnalogInput analogInput;
    SoilMoistureSensor s_m_sensor(analogInput);

    EXPECT_CALL(analogInput, read).WillOnce(Return(205));
    EXPECT_EQ(s_m_sensor.readPercent(), 20);
}

TEST(SoilMoistureSensor_UT, ReadCalibrationStatus_false)
{
    MockAnalogInput analogInput;
    SoilMoistureSensor s_m_sensor(analogInput);

    EXPECT_EQ(s_m_sensor.isCalibrated(), false);
}

TEST(SoilMoistureSensor_UT, ReadCalibrationStatus_true)
{
    MockAnalogInput analogInput;
    SoilMoistureSensor s_m_sensor(analogInput);

    s_m_sensor.calibrate();
    EXPECT_EQ(s_m_sensor.isCalibrated(), true);
}
