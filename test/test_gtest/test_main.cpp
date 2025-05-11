#include <gtest/gtest.h>

TEST(DummyTest, gtest_test)
{
    EXPECT_EQ(1, 1);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    if (RUN_ALL_TESTS())
    ;
    // Always return zero-code and allow PlatformIO to parse results
    return 0;
}
