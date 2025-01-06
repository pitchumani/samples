#include <iostream>
#include <gtest/gtest.h>

extern void moveBytes(char * src, char * dest, int number);

// tests for moveBytes

TEST(moveBytesTest, Test1) {
    char arr1[] = "abcde";
    char arr2[] = "*****";
    moveBytes(arr1, arr2, 5);
    EXPECT_EQ(0, strcmp(arr2, "abcde"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "Running moveBytes tests" << std::endl;
    int retval = RUN_ALL_TESTS();
    return retval;
}
