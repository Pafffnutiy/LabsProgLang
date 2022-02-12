#include "gtest/gtest.h"
#include "List.hpp"
#include <vector>

TEST(list, All) {
	for (std::size_t j{ 0 }; j < 1000; ++j)
	{
		List<double> A;
		std::size_t i{ 0 };
		std::vector<double> tmp(6);

		for (double elem : tmp)
		{
			tmp.push_back((10 * i + i) / 10);
			++i;
		}

		A.push_back(tmp[0]); // {tmp1}

		EXPECT_EQ(A[0]->value, tmp[0]);

		A.push_front(tmp[1]); // {tmp2, tmp1}

		EXPECT_EQ(A[0]->value, tmp[1]);
		EXPECT_EQ(A[1]->value, tmp[0]);

		A.push_back(tmp[2]); // {tmp2, tmp1, tmp3}

		EXPECT_EQ(A[0]->value, tmp[1]);
		EXPECT_EQ(A[1]->value, tmp[0]);
		EXPECT_EQ(A[2]->value, tmp[2]);

		A.insert(1, tmp[3]); //{tmp2, tmp4, tmp1, tmp3}

		EXPECT_EQ(A[0]->value, tmp[1]);
		EXPECT_EQ(A[1]->value, tmp[3]);
		EXPECT_EQ(A[2]->value, tmp[0]);
		EXPECT_EQ(A[3]->value, tmp[2]);

		A.insert(1, tmp[4]); 
		// {tmp2, tmp5, tmp4, tmp1, tmp3}

		EXPECT_EQ(A[0]->value, tmp[1]);
		EXPECT_EQ(A[1]->value, tmp[4]);
		EXPECT_EQ(A[2]->value, tmp[3]);
		EXPECT_EQ(A[3]->value, tmp[0]);
		EXPECT_EQ(A[4]->value, tmp[2]);

		A.insert(4, tmp[5]); 
		// {tmp2, tmp5, tmp4, tmp1,  tmp6, tmp3}

		EXPECT_EQ(A[0]->value, tmp[1]);
		EXPECT_EQ(A[1]->value, tmp[4]);
		EXPECT_EQ(A[2]->value, tmp[3]);
		EXPECT_EQ(A[3]->value, tmp[0]);
		EXPECT_EQ(A[4]->value, tmp[5]);
		EXPECT_EQ(A[5]->value, tmp[2]);

		A.insert(4, tmp[0]); 
		// {tmp2, tmp5, tmp4, tmp1, tmp1, tmp6, tmp3}

		EXPECT_EQ(A[0]->value, tmp[1]);
		EXPECT_EQ(A[1]->value, tmp[4]);
		EXPECT_EQ(A[2]->value, tmp[3]);
		EXPECT_EQ(A[3]->value, tmp[2]);
		EXPECT_EQ(A[4]->value, tmp[0]);
		EXPECT_EQ(A[5]->value, tmp[5]);
		EXPECT_EQ(A[6]->value, tmp[2]);

		A.erase(6); 
		// {tmp2, tmp5, tmp4, tmp1, tmp1, tmp6}

		EXPECT_EQ(A[0]->value, tmp[1]);
		EXPECT_EQ(A[1]->value, tmp[4]);
		EXPECT_EQ(A[2]->value, tmp[3]);
		EXPECT_EQ(A[3]->value, tmp[0]);
		EXPECT_EQ(A[4]->value, tmp[0]);
		EXPECT_EQ(A[5]->value, tmp[5]);

		A.erase(1); 
		// {tmp2, tmp4, tmp1, tmp1, tmp6}

		EXPECT_EQ(A[0]->value, tmp[1]);
		EXPECT_EQ(A[1]->value, tmp[3]);
		EXPECT_EQ(A[2]->value, tmp[0]);
		EXPECT_EQ(A[3]->value, tmp[0]);
		EXPECT_EQ(A[4]->value, tmp[5]);

		A.erase(1); 
		// {tmp2, tmp1, tmp1, tmp6}

		EXPECT_EQ(A[0]->value, tmp[1]);
		EXPECT_EQ(A[1]->value, tmp[0]);
		EXPECT_EQ(A[2]->value, tmp[0]);
		EXPECT_EQ(A[3]->value, tmp[5]);

		List<double> B(A);

		EXPECT_EQ(B[0]->value, tmp[1]);
		EXPECT_EQ(B[1]->value, tmp[0]);
		EXPECT_EQ(B[2]->value, tmp[0]);
		EXPECT_EQ(B[3]->value, tmp[5]);

		A.pop_front(); // {tmp1, tmp1, tmp6}

		EXPECT_EQ(A[0]->value, tmp[0]);
		EXPECT_EQ(A[1]->value, tmp[0]);
		EXPECT_EQ(A[2]->value, tmp[5]);

		A.pop_back(); // {tmp1, tmp1}

		EXPECT_EQ(A[0]->value, tmp[0]);
		EXPECT_EQ(A[1]->value, tmp[0]);

		A.erase(0); // {tmp1}

		EXPECT_EQ(A[0]->value, tmp[0]);
	}
}

TEST(list, Iterator)
{
	for (std::size_t j{ 0 }; j < 1000; ++j)
	{
		List<int> K;
		std::vector<int> tmp = { 4 };
		K.push_back(4);
		for (int i{ 1 }; i < rand() % 5000; ++i)
		{
			tmp.push_back(rand());
			K.push_back(tmp[i]);
		}

		std::size_t i{ 0 };

		for (auto elem : K)
		{
			EXPECT_EQ(elem, tmp[i]);
			++i;
		}
	}
}

TEST(list, Iterator2)
{
	for (std::size_t j{ 0 }; j < 1000; ++j)
	{
		List<int> K;
		std::vector<int> tmp = { 4 };
		K.push_back(4);
		for (int i{ 1 }; i < rand() % 5000; ++i)
		{
			tmp.push_back(rand());
			K.push_back(tmp[i]);
		}

		List<int> L;
		std::swap(K, L);
		std::size_t i{ 0 };

		for (auto elem : L)
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