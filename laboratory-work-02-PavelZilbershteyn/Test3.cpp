#include "gtest/gtest.h"
#include "Queue.h"

TEST(queue, All) {
	Queue A(4);
	
	DateAndTime  tmp1, tmp5, tmp9;
	BigNumber    tmp2, tmp6;
	YearFromAdam tmp3, tmp7;
	Matrix		 tmp4, tmp8;

	A.push_back(&tmp1); // {tmp1, - , - , - }
	
	EXPECT_EQ(A[0], &tmp1);

	A.insert(1, &tmp2); // {tmp1, tmp2 , - , - }

	EXPECT_EQ(A[0], &tmp1);
	EXPECT_EQ(A[1], &tmp2);

	A.push_back(&tmp3); A.push_back(&tmp4); // {tmp1, tmp2, tmp3, tmp4}

	EXPECT_EQ(A[0], &tmp1);
	EXPECT_EQ(A[1], &tmp2);
	EXPECT_EQ(A[2], &tmp3);
	EXPECT_EQ(A[3], &tmp4);

	A.push_back(&tmp5);	A.push_back(&tmp6);
	// {tmp5, tmp6 tmp3, tmp4}

	EXPECT_EQ(A[0], &tmp5);
	EXPECT_EQ(A[1], &tmp6);
	EXPECT_EQ(A[2], &tmp3);
	EXPECT_EQ(A[3], &tmp4);

	A.pop_front(); // {tmp6 , - , tmp4, tmp5}

	EXPECT_EQ(A[0], &tmp6); 
	EXPECT_EQ(A[1], nullptr);
	EXPECT_EQ(A[2], &tmp4);
	EXPECT_EQ(A[3], &tmp5);

	A.insert(1, &tmp7); // {tmp6 , tmp7 , tmp4, tmp5}

	EXPECT_EQ(A[0], &tmp6);
	EXPECT_EQ(A[1], &tmp7);
	EXPECT_EQ(A[2], &tmp4);
	EXPECT_EQ(A[3], &tmp5);

	A.erase(0); // {tmp7, - , tmp4, tmp5}

	EXPECT_EQ(A[0], &tmp7);
	EXPECT_EQ(A[1], nullptr);
	EXPECT_EQ(A[2], &tmp4);
	EXPECT_EQ(A[3], &tmp5);

	A.push_back(&tmp8);	A.push_back(&tmp9);
	// {tmp7, tmp8, tmp9, tmp5}

	EXPECT_EQ(A[0], &tmp7);
	EXPECT_EQ(A[1], &tmp8);
	EXPECT_EQ(A[2], &tmp9);
	EXPECT_EQ(A[3], &tmp5);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}