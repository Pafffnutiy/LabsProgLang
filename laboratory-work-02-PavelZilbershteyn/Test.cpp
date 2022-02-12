#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Vector.h"

TEST(vector, ConstructorsAndLength) {
	Vector A, B(4), C(B);
	EXPECT_EQ(A.length(), 0);
	EXPECT_EQ(B.length(), 4);
	EXPECT_EQ(C.length(), 4);
}

TEST(vector, ResizeAndPushBack) {
	Vector A, B(4);
	A.Resize(2); B.Resize(2);

	ADT* tmp = new Matrix(3, 3);

	B.push_back(tmp);
	A.push_back(new BigNumber("1234567"));

	EXPECT_EQ(A.length(), 3);
	EXPECT_EQ(B.length(), 3);
}

TEST(vector, EraseInsertOperator) {
	Vector A(2), B(4);
	
	Matrix tmp1(3, 3);
	BigNumber tmp2("1234567");
	YearFromAdam tmp3;
	DateAndTime tmp4;

	B.push_back(&tmp1);
	A.push_back(&tmp2);
	A.insert(0, &tmp3);
	A.erase(1);
	B[0] = &tmp4;

	YearFromAdam K(2, 3, 4);
	B[2] = &K;

	Matrix tmp5(2, 2);
	BigNumber tmp6("12345");

	A.insert(2, &tmp5);
	A.insert(1, &tmp6);
	A.erase(2);

	EXPECT_EQ(A[0], &tmp3);
	EXPECT_EQ(A[1], &tmp6);
	EXPECT_EQ(A[2], &tmp5);
	EXPECT_EQ(A[3], &tmp2);
	EXPECT_EQ(B[4], &tmp1);
	EXPECT_EQ(A.length(), 4);
	EXPECT_EQ(B.length(), 5);
	EXPECT_EQ(B[0],&tmp4);
	EXPECT_EQ(B[2],&K);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}