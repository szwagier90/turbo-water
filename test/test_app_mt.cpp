#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <App.h>

#include "mocks/mock_serial.h"

using ::testing::StrEq;

TEST(AppTest, PeripherialsInitialization)
{
    MockSerial serial;
    App app(
        serial
    );

    EXPECT_CALL(serial, begin(115200));
    EXPECT_CALL(serial, println(StrEq("SERIAL_INIT")));
    app.setup();
}
