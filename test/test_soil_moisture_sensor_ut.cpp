#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <SoilMoistureSensor.h>

#include "mocks/mock_analogInput.h"

using ::testing::Return;


class SoilMoistureSensor_Initialized_UT : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    MockAnalogInput analogInput;
    SoilMoistureSensor s_m_sensor;

    SoilMoistureSensor_Initialized_UT() : s_m_sensor(analogInput) {}
};

TEST_F(SoilMoistureSensor_Initialized_UT, ReadPercentSimple)
{
    s_m_sensor.calibrate(1, 1000);
    EXPECT_CALL(analogInput, read).WillOnce(Return(205));
    EXPECT_EQ(s_m_sensor.readPercent(), 20);
}

TEST_F(SoilMoistureSensor_Initialized_UT, ReadCalibrationStatus_false)
{
    EXPECT_EQ(s_m_sensor.isCalibrated(), false);
}

TEST_F(SoilMoistureSensor_Initialized_UT, ReadCalibrationStatus_true)
{
    s_m_sensor.calibrate(1, 2);
    EXPECT_EQ(s_m_sensor.isCalibrated(), true);
}

TEST_F(SoilMoistureSensor_Initialized_UT, ReadRawSimple)
{
    EXPECT_CALL(analogInput, read).WillOnce(Return(205));
    EXPECT_EQ(s_m_sensor.readRaw(), 205);
}

TEST_F(SoilMoistureSensor_Initialized_UT, ReadCorrectPercent)
{
    s_m_sensor.calibrate(1, 100);
    EXPECT_CALL(analogInput, read).WillOnce(Return(90));
    EXPECT_GE(s_m_sensor.readPercent(), 80);
}
