#include <gtest/gtest.h>

#include <App.h>

#include "mocks/mock_serial.h"

TEST(AppTest, Serial_InitMessage)
{
    MockSerial serial;
    App app(
        serial
    );
}
