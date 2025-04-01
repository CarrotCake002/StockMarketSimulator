#include <gtest/gtest.h>

const char* hello() {
    return "Hello, World!";
}

TEST(HelloWorldTest, BasicAssertions) {
    EXPECT_EQ(hello(), "Hello, World!");
}

// Example test case
TEST(ClientTest, ExampleTest) {
    EXPECT_EQ(2 * 2, 4);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}