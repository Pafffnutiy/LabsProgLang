#include "gtest/gtest.h"
#include "Tree.h"

TEST(tree, All) {
	DateAndTime  tmp1, tmp5;
	BigNumber	 tmp2, tmp6;
	YearFromAdam tmp3, tmp7;
	Matrix		 tmp4, tmp8;

	Tree tree1(3), tree2(4);
	
	EXPECT_EQ(tree1.length(), 7);
	EXPECT_EQ(tree2.length(), 15);

	tree1[1]->val = &tmp1;
	tree1[2]->val = &tmp2;
	tree1[3]->val = &tmp3;
	tree1[4]->val = &tmp4;
	tree1[5]->val = &tmp5;
	tree1[6]->val = &tmp6;
	tree1[7]->val = &tmp7;

	EXPECT_EQ(tree1[1]->val, &tmp1);
	EXPECT_EQ(tree1[2]->val, &tmp2);
	EXPECT_EQ(tree1[3]->val, &tmp3);
	EXPECT_EQ(tree1[4]->val, &tmp4);
	EXPECT_EQ(tree1[5]->val, &tmp5);
	EXPECT_EQ(tree1[6]->val, &tmp6);
	EXPECT_EQ(tree1[7]->val, &tmp7);

	tree1.insert(3, &tmp8);

	EXPECT_EQ(tree1.length(), 15);
	EXPECT_EQ(tree1[1]->val, &tmp1);
	EXPECT_EQ(tree1[2]->val, &tmp2);
	EXPECT_EQ(tree1[3]->val, &tmp8);
	EXPECT_EQ(tree1[4]->val, &tmp4);
	EXPECT_EQ(tree1[5]->val, &tmp5);
	EXPECT_EQ(tree1[6]->val, &tmp3);
	//EXPECT_EQ(tree1[7]->val, nullptr);
	//EXPECT_EQ(tree1[8]->val, nullptr);
	//EXPECT_EQ(tree1[9]->val, nullptr);
	//EXPECT_EQ(tree1[10]->val, nullptr);
	//EXPECT_EQ(tree1[11]->val, nullptr);
	EXPECT_EQ(tree1[12]->val, &tmp6);
	EXPECT_EQ(tree1[13]->val, &tmp7);
	//EXPECT_EQ(tree1[14]->val, nullptr);
	//EXPECT_EQ(tree1[15]->val, nullptr);

	Tree tree3(tree1);

	EXPECT_EQ(tree3.length(), 15);
	EXPECT_EQ(tree3[1]->val, &tmp1);
	EXPECT_EQ(tree3[2]->val, &tmp2);
	EXPECT_EQ(tree3[3]->val, &tmp8);
	EXPECT_EQ(tree3[4]->val, &tmp4);
	EXPECT_EQ(tree3[5]->val, &tmp5);
	EXPECT_EQ(tree3[6]->val, &tmp3);
	//EXPECT_EQ(tree3[7]->val, nullptr);
	//EXPECT_EQ(tree3[8]->val, nullptr);
	//EXPECT_EQ(tree3[9]->val, nullptr);
	//EXPECT_EQ(tree3[10]->val, nullptr);
	//EXPECT_EQ(tree3[11]->val, nullptr);
	EXPECT_EQ(tree3[12]->val, &tmp6);
	EXPECT_EQ(tree3[13]->val, &tmp7);
	//EXPECT_EQ(tree3[14]->val, nullptr);
	//EXPECT_EQ(tree3[15]->val, nullptr);

	tree3.erase(2);

	EXPECT_EQ(tree3.length(), 15);
	EXPECT_EQ(tree3[1]->val, &tmp1);
	EXPECT_EQ(tree3[2]->val, nullptr);
	EXPECT_EQ(tree3[3]->val, &tmp8);
	//EXPECT_EQ(tree3[4]->val, &tmp4);
	//EXPECT_EQ(tree3[5]->val, &tmp5);
	EXPECT_EQ(tree3[6]->val, &tmp3);
	//EXPECT_EQ(tree3[7]->val, nullptr);
	//EXPECT_EQ(tree3[8]->val, nullptr);
	//EXPECT_EQ(tree3[9]->val, nullptr);
	//EXPECT_EQ(tree3[10]->val, nullptr);
	//EXPECT_EQ(tree3[11]->val, nullptr);
	EXPECT_EQ(tree3[12]->val, &tmp6);
	EXPECT_EQ(tree3[13]->val, &tmp7);
	//EXPECT_EQ(tree3[14]->val, nullptr);
	//EXPECT_EQ(tree3[15]->val, nullptr);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}