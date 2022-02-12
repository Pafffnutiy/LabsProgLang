#include "gtest/gtest.h"
#include "Stack.h"

TEST(stack, ConstructorsLengthResize) {
	Stack A, B(4), C(B);
	A.Resize(10);
	B.Resize(5);
	C.Resize(0);

	EXPECT_EQ(A.length(), 10);
	EXPECT_EQ(B.length(), 5);
	EXPECT_EQ(C.length(), 0);
}

TEST(stack, Other) {
	Stack A;

	DateAndTime tmp1;
	BigNumber tmp2("123456789");
	YearFromAdam tmp3(1, 2, 3);

	A.push_back(&tmp1); // {tmp1}
	A.push_back(&tmp2); // {tmp1, tmp2}
	A.push_up(&tmp3);   // {tmp3, tmp1, tmp2}
	A.push_up(&tmp2);   // {tmp2, tmp3, tmp1, tmp2}

	Stack B(A);

	B.pop_back();
	B.pop_up();
	B.pop_back();

	EXPECT_EQ(A[0], &tmp2);
	EXPECT_EQ(A[1], &tmp3);
	EXPECT_EQ(A[2], &tmp1);
	EXPECT_EQ(A[3], &tmp2);
	EXPECT_EQ(A.length(), 4);
	EXPECT_EQ(B.length(), 1);
	EXPECT_EQ(B[0], &tmp3);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}