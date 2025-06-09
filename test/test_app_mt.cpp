#include <gtest/gtest.h>

#include <App.h>

#include "mocks/mock_serial.h"

TEST(AppTest, PeripherialsInitialization)
{
    MockSerial serial;
    App app(
        serial
    );
}
