#include "gtest/gtest.h"
#include "Stack.h"
#include <string>
#include <sstream>
#include <numeric>
#include <iostream>

TEST(stack, ConstructorsLengthResize) {
	Stack<std::string> A, B(4), C(B);
	A.Resize(10);
	B.Resize(5);
	C.Resize(0);

	EXPECT_EQ(A.length(), 10);
	EXPECT_EQ(B.length(), 5);
	EXPECT_EQ(C.length(), 0);
}

TEST(stack, Iter) {
	Stack<std::string> A, B(4), C(B);
	A.Resize(10);
	B.Resize(5);
	C.Resize(0);

	std::fill(A.begin(), A.end(), "OMG");

	std::stringstream ss;

	for (const auto& elem : A)
		ss << elem << ' ';

	std::string stroka;
	std::getline(ss, stroka);

	EXPECT_EQ(stroka, "OMG OMG OMG OMG OMG OMG OMG OMG OMG OMG ");
	EXPECT_EQ(B.length(), 5);
	EXPECT_EQ(C.length(), 0);
}

TEST(stack, Other) {
	Stack<long> A;

	long tmp1 = 987654321;
	long tmp2 = 123456789;
	long tmp3 = 0;

	A.push_back(tmp1); // {tmp1}
	A.push_back(tmp2); // {tmp1, tmp2}
	A.push_up(tmp3);   // {tmp3, tmp1, tmp2}
	A.push_up(tmp2);   // {tmp2, tmp3, tmp1, tmp2}

	Stack<long> B(A);

	B.pop_back();
	B.pop_up();
	B.pop_back();

	long sum = std::accumulate(A.begin(), A.end(), 0);

	EXPECT_EQ(A[0], tmp2);
	EXPECT_EQ(A[1], tmp3);
	EXPECT_EQ(A[2], tmp1);
	EXPECT_EQ(A[3], tmp2);
	EXPECT_EQ(A.length(), 4);
	EXPECT_EQ(B.length(), 1);
	EXPECT_EQ(B[0], tmp3);
	EXPECT_EQ(sum, 1234567899);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}