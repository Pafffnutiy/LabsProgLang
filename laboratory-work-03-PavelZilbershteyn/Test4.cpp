#include "gtest/gtest.h"
#include "Tree.hpp"
#include <random>

TEST(tree, All) {
	for (std::size_t j{ 0 }; j < 500; ++j)
	{
		Tree<int> tree1(3), tree2(4);
		std::vector<int>  tmp(8);

		std::random_device rd;
		std::mt19937 mersenne(rd());

		for (std::size_t i{ 0 }; i < 8; ++i)
		{
			tmp[i] = mersenne();
		}

		EXPECT_EQ(tree1.length(), 7);
		EXPECT_EQ(tree2.length(), 15);

		tree1[1]->val = tmp[0];
		tree1[2]->val = tmp[1];
		tree1[3]->val = tmp[2];
		tree1[4]->val = tmp[3];
		tree1[5]->val = tmp[4];
		tree1[6]->val = tmp[5];
		tree1[7]->val = tmp[6];

		EXPECT_EQ(tree1[1]->val, tmp[0]);
		EXPECT_EQ(tree1[2]->val, tmp[1]);
		EXPECT_EQ(tree1[3]->val, tmp[2]);
		EXPECT_EQ(tree1[4]->val, tmp[3]);
		EXPECT_EQ(tree1[5]->val, tmp[4]);
		EXPECT_EQ(tree1[6]->val, tmp[5]);
		EXPECT_EQ(tree1[7]->val, tmp[6]);

		tree1.insert(3, tmp[7]);

		EXPECT_EQ(tree1.length(), 15);
		EXPECT_EQ(tree1[1]->val, tmp[0]);
		EXPECT_EQ(tree1[2]->val, tmp[1]);
		EXPECT_EQ(tree1[3]->val, tmp[7]);
		EXPECT_EQ(tree1[4]->val, tmp[3]);
		EXPECT_EQ(tree1[5]->val, tmp[4]);
		EXPECT_EQ(tree1[6]->val, tmp[2]);
		//EXPECT_EQ(tree1[7]->val, nullptr);
		//EXPECT_EQ(tree1[8]->val, nullptr);
		//EXPECT_EQ(tree1[9]->val, nullptr);
		//EXPECT_EQ(tree1[10]->val, nullptr);
		//EXPECT_EQ(tree1[11]->val, nullptr);
		EXPECT_EQ(tree1[12]->val, tmp[5]);
		EXPECT_EQ(tree1[13]->val, tmp[6]);
		//EXPECT_EQ(tree1[14]->val, nullptr);
		//EXPECT_EQ(tree1[15]->val, nullptr);

		Tree<int> tree3(tree1);

		EXPECT_EQ(tree3.length(), 15);
		EXPECT_EQ(tree3[1]->val, tmp[0]);
		EXPECT_EQ(tree3[2]->val, tmp[1]);
		EXPECT_EQ(tree3[3]->val, tmp[7]);
		EXPECT_EQ(tree3[4]->val, tmp[3]);
		EXPECT_EQ(tree3[5]->val, tmp[4]);
		EXPECT_EQ(tree3[6]->val, tmp[2]);
		//EXPECT_EQ(tree3[7]->val, nullptr);
		//EXPECT_EQ(tree3[8]->val, nullptr);
		//EXPECT_EQ(tree3[9]->val, nullptr);
		//EXPECT_EQ(tree3[10]->val, nullptr);
		//EXPECT_EQ(tree3[11]->val, nullptr);
		EXPECT_EQ(tree3[12]->val, tmp[5]);
		EXPECT_EQ(tree3[13]->val, tmp[6]);
		//EXPECT_EQ(tree3[14]->val, nullptr);
		//EXPECT_EQ(tree3[15]->val, nullptr);

		tree3.erase(2);

		EXPECT_EQ(tree3.length(), 15);
		EXPECT_EQ(tree3[1]->val, tmp[0]);
		EXPECT_EQ(tree3[2]->val, 0);
		EXPECT_EQ(tree3[3]->val, tmp[7]);
		//EXPECT_EQ(tree3[4]->val, &tmp4);
		//EXPECT_EQ(tree3[5]->val, &tmp5);
		EXPECT_EQ(tree3[6]->val, tmp[2]);
		//EXPECT_EQ(tree3[7]->val, nullptr);
		//EXPECT_EQ(tree3[8]->val, nullptr);
		//EXPECT_EQ(tree3[9]->val, nullptr);
		//EXPECT_EQ(tree3[10]->val, nullptr);
		//EXPECT_EQ(tree3[11]->val, nullptr);
		EXPECT_EQ(tree3[12]->val, tmp[5]);
		EXPECT_EQ(tree3[13]->val, tmp[6]);
		//EXPECT_EQ(tree3[14]->val, nullptr);
		//EXPECT_EQ(tree3[15]->val, nullptr);
	}
}

TEST(tree, Iterator) {
	for (std::size_t j{ 0 }; j < 1000; ++j)
	{
		Tree<int> tree1(3), tree2;
		std::vector<int>  tmp(8);

		std::random_device rd;
		std::mt19937 mersenne(rd());

		for (std::size_t i{ 0 }; i < 8; ++i)
		{
			tmp[i] = mersenne();
		}

		tree1[1]->val = tmp[0];
		tree1[2]->val = tmp[1];
		tree1[3]->val = tmp[2];
		tree1[4]->val = tmp[3];
		tree1[5]->val = tmp[4];
		tree1[6]->val = tmp[5];
		tree1[7]->val = tmp[6];

		std::swap(tree1, tree2);

		std::size_t i{ 0 };

		for (auto elem : tree2)
		{
			EXPECT_EQ(elem, tmp[i]);
			++i;
		}
	}
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}