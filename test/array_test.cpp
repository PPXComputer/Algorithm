#include <gtest/gtest.h>
#include<ArrayAlgo.h>
int add(int a, int b){
    return a+b;
}

TEST(testCase, test0){
    EXPECT_EQ(add(2,3),5);
}
TEST(testCase ,Josn){
    ArrayAlgo::JosephProblem();
}
int main(int argc, char **argv){
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

