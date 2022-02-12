#include "gtest/gtest.h"
#include "Vector.h"
#include <algorithm>

TEST(vector, ConstructorsAndLength) {
	Vector<int> A, B(4), C(B);
	EXPECT_EQ(A.length(), 0);
	EXPECT_EQ(B.length(), 4);
	EXPECT_EQ(C.length(), 4);
}

TEST(vector, ResizeAndPushBack) {
	Vector<int> A, B(4);
	A.Resize(2); B.Resize(2);

	std::size_t i{ 0 };

	for (auto& elem : A)
	{
		++i;
		elem = i;
	}

	B.push_back(5);
	A.push_back(1234567);

	EXPECT_EQ(A.length(), 3);
	EXPECT_EQ(B.length(), 3);
	EXPECT_EQ(B[2], 5);
	EXPECT_EQ(A[0], 1);
	EXPECT_EQ(A[1], 2);
	EXPECT_EQ(A[2], 1234567);
}

TEST(vector, EraseInsertOperator) {
	Vector<std::string> A(2);
	Vector<double> B(4);

	double tmp1 = 5040.5;
	std::string tmp2 = "Hello", tmp3 = "World!";

	B.push_back(tmp1);
	A.push_back(tmp2);
	A.insert(0, tmp3);
	A.erase(1);

	B[0] = 24.2;
	B[1] = 120.3;
	B[2] = 6.1;
	B[3] = 720.4;

	std::string tmp5 = "OMG", tmp6("WTF");

	A.insert(2, tmp5);
	A.insert(1, tmp6);
	A.erase(2);

	std::swap(A[0], A[3]);
	//std::sort(B.begin(), B.end());

	EXPECT_DOUBLE_EQ(B[2], 6.1);
	EXPECT_DOUBLE_EQ(B[0], 24.2);
	EXPECT_DOUBLE_EQ(B[1], 120.3);
	EXPECT_DOUBLE_EQ(B[3], 720.4);
	EXPECT_DOUBLE_EQ(B[4], 5040.5);
	EXPECT_EQ(A.length(), 4);
	EXPECT_EQ(B.length(), 5);
	EXPECT_EQ(A[0], std::string("Hello"));
	EXPECT_EQ(A[1], std::string("WTF"));
	EXPECT_EQ(A[2], std::string("OMG"));
	EXPECT_EQ(A[3], std::string("World!"));
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}