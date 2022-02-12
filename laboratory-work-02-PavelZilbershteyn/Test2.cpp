#include "gtest/gtest.h"
#include "List.h"

TEST(list, All) {

	List A;

	BigNumber tmp1;
	DateAndTime tmp2;
	YearFromAdam tmp3;
	Matrix tmp4;
	BigNumber tmp5;
	DateAndTime tmp6;

	A.push_back(&tmp1); // {tmp1}

	EXPECT_EQ(A[0]->value, &tmp1);

	A.push_front(&tmp2); // {tmp2, tmp1}

	EXPECT_EQ(A[0]->value, &tmp2);
	EXPECT_EQ(A[1]->value, &tmp1); 

	A.push_back(&tmp3); // {tmp2, tmp1, tmp3}

	EXPECT_EQ(A[0]->value, &tmp2);
	EXPECT_EQ(A[1]->value, &tmp1);
	EXPECT_EQ(A[2]->value, &tmp3);

	A.insert(1, &tmp4); //{tmp2, tmp4, tmp1, tmp3}

	EXPECT_EQ(A[0]->value, &tmp2);
	EXPECT_EQ(A[1]->value, &tmp4);
	EXPECT_EQ(A[2]->value, &tmp1);
	EXPECT_EQ(A[3]->value, &tmp3);

	A.insert(1, &tmp5); // {tmp2, tmp5, tmp4, tmp1, tmp3}

	EXPECT_EQ(A[0]->value, &tmp2);
	EXPECT_EQ(A[1]->value, &tmp5);
	EXPECT_EQ(A[2]->value, &tmp4);
	EXPECT_EQ(A[3]->value, &tmp1);
	EXPECT_EQ(A[4]->value, &tmp3);

	A.insert(4, &tmp6); // {tmp2, tmp5, tmp4, tmp1,  tmp6, tmp3}

	EXPECT_EQ(A[0]->value, &tmp2);
	EXPECT_EQ(A[1]->value, &tmp5);
	EXPECT_EQ(A[2]->value, &tmp4);
	EXPECT_EQ(A[3]->value, &tmp1);
	EXPECT_EQ(A[4]->value, &tmp6);
	EXPECT_EQ(A[5]->value, &tmp3); 

	A.insert(4, &tmp1); // {tmp2, tmp5, tmp4, tmp1, tmp1, tmp6, tmp3}

	EXPECT_EQ(A[0]->value, &tmp2);
	EXPECT_EQ(A[1]->value, &tmp5);
	EXPECT_EQ(A[2]->value, &tmp4);
	EXPECT_EQ(A[3]->value, &tmp1);
	EXPECT_EQ(A[4]->value, &tmp1);
	EXPECT_EQ(A[5]->value, &tmp6);
	EXPECT_EQ(A[6]->value, &tmp3);	

	A.erase(6); // {tmp2, tmp5, tmp4, tmp1, tmp1, tmp6}

	EXPECT_EQ(A[0]->value, &tmp2);
	EXPECT_EQ(A[1]->value, &tmp5);
	EXPECT_EQ(A[2]->value, &tmp4);
	EXPECT_EQ(A[3]->value, &tmp1);
	EXPECT_EQ(A[4]->value, &tmp1);
	EXPECT_EQ(A[5]->value, &tmp6); 

	A.erase(1); // {tmp2, tmp4, tmp1, tmp1, tmp6}

	EXPECT_EQ(A[0]->value, &tmp2);
	EXPECT_EQ(A[1]->value, &tmp4);
	EXPECT_EQ(A[2]->value, &tmp1);
	EXPECT_EQ(A[3]->value, &tmp1);
	EXPECT_EQ(A[4]->value, &tmp6); 

	A.erase(1); // {tmp2, tmp1, tmp1, tmp6

	EXPECT_EQ(A[0]->value, &tmp2);
	EXPECT_EQ(A[1]->value, &tmp1);
	EXPECT_EQ(A[2]->value, &tmp1);
	EXPECT_EQ(A[3]->value, &tmp6); 

	List B(A);

	EXPECT_EQ(B[0]->value, &tmp2);
	EXPECT_EQ(B[1]->value, &tmp1);
	EXPECT_EQ(B[2]->value, &tmp1);
	EXPECT_EQ(B[3]->value, &tmp6);

	A.pop_front(); // {tmp1, tmp1, tmp6}

	EXPECT_EQ(A[0]->value, &tmp1);
	EXPECT_EQ(A[1]->value, &tmp1);
	EXPECT_EQ(A[2]->value, &tmp6); 

	A.pop_back(); // {tmp1, tmp1}

	EXPECT_EQ(A[0]->value, &tmp1);
	EXPECT_EQ(A[1]->value, &tmp1);

	A.erase(0); // {tmp1}

	EXPECT_EQ(A[0]->value, &tmp1);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}