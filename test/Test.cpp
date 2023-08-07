
#include <gtest/gtest.h>
#include "../src/MyClass/MyClass.h"

// 测试MyClass类的add函数
TEST(MyClassTest, testAdd) {
    MyClass myobj;
    EXPECT_EQ(myobj.add(1, 2), 3);
    EXPECT_EQ(myobj.add(-1, 2), 1);
    EXPECT_EQ(myobj.add(0, 0), 0);
}


// 测试MyClass类的subtract函数
TEST(MyClassTest, testSubtract) {
    MyClass myobj;
    EXPECT_EQ(myobj.subtract(3, 2), 1);
    EXPECT_EQ(myobj.subtract(-1, 2), -3);
    EXPECT_EQ(myobj.subtract(0, 0), 0);
    EXPECT_EQ(myobj.subtract(1, 2), -1);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
