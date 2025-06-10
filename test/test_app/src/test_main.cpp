#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <App.h>

#include "include/mock_serial.h"

using ::testing::StrEq;

TEST(AppTest, HelloWorld)
{
    MockSerial serial;
    App app(
        serial
    );

    EXPECT_CALL(serial, begin(115200));
    EXPECT_CALL(serial, println(StrEq("SERIAL_INIT")));
    app.setup();
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    if (RUN_ALL_TESTS())
    ;
    // Always return zero-code and allow PlatformIO to parse results
    return 0;
}
