//
// Created by 86183 on 2023/3/22.
//
#include "gtest/gtest.h"
#include "../src/MultipleManager/MultipleManager.h"


TEST(MultipleManager, testMultiple) {
    MultipleManager manager;
    EXPECT_EQ(3, manager.multiple(1, 3));
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}