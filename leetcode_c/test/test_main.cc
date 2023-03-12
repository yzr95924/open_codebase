/**
 * @file test_main.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief for test
 * @version 0.1
 * @date 2023-03-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <gtest/gtest.h>

TEST(HelloTest, BasicAssertions)
{
    // Demonstrate some basic assertions
    EXPECT_STRNE("hello", "world");
    // Expect equality
    EXPECT_EQ(7 * 6, 42);

    ASSERT_EQ(8, 8) << "Vectors x and y are of unequal length";
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}