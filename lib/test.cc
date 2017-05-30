#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "rand.hpp"

TEST(LibraryTest, RandTest) {
	ASSERT_NE(11, hkl::rand::MakeRangeNum(1,10));

	ASSERT_EQ(true, hkl::rand::TrueOrFalse(100));

	ASSERT_EQ(true, hkl::rand::TrueOrFalse(1.0));

	int num =  hkl::rand::NumOfSuccess(1000, 0.9); // 1000명의 사람중 90%사람이 지구탈출을 할 수 있다면 몇명일까?
	std::cout<<"생존자: "<< num <<std::endl;
	ASSERT_LE(30, num) << "1000명중 90%사람은 30보다 커야한다"; // 1000명의 사람중 90%사람이 지구탈출을 할 수 있다면 몇명일까?
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
