#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TestTest, TestTest)
{
    EXPECT_TRUE(true);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    if (RUN_ALL_TESTS())
    ;
    // Always return zero-code and allow PlatformIO to parse results
    return 0;
}
