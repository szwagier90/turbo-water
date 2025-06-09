#include <gtest/gtest.h>

#include <App.h>

#include "mocks/mock_serial.h"

TEST(AppTest, HelloWorld)
{
    MockSerial serial;
    App app(
        serial
    );
}
