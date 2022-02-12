#include "gtest/gtest.h"
#include "Queue.hpp"
#include <vector>
#include <random>
#include <sstream>

TEST(queue, All) {
	for (std::size_t j{ 0 }; j < 1000; ++j)
	{
		Queue<int> A(4);

		std::vector<int> tmp(9);

		for (std::size_t i{ 0 }; i < 9; ++i)
			tmp[i] = rand() + 1;

		A.push_back(tmp[0]); // {tmp1, - , - , - }

		EXPECT_EQ(A[0], tmp[0]);

		A.insert(1, tmp[1]); // {tmp1, tmp2 , - , - }

		EXPECT_EQ(A[0], tmp[0]);
		EXPECT_EQ(A[1], tmp[1]);

		A.push_back(tmp[2]); A.push_back(tmp[3]); 
		// {tmp1, tmp2, tmp3, tmp4}

		EXPECT_EQ(A[0], tmp[0]);
		EXPECT_EQ(A[1], tmp[1]);
		EXPECT_EQ(A[2], tmp[2]);
		EXPECT_EQ(A[3], tmp[3]);

		A.push_back(tmp[4]);	A.push_back(tmp[5]);
		// {tmp5, tmp6 tmp3, tmp4}

		EXPECT_EQ(A[0], tmp[4]);
		EXPECT_EQ(A[1], tmp[5]);
		EXPECT_EQ(A[2], tmp[2]);
		EXPECT_EQ(A[3], tmp[3]);

		A.pop_front(); // {tmp6 , - , tmp4, tmp5}

		EXPECT_EQ(A[0], tmp[5]);
		EXPECT_EQ(A[1], 0/*nullptr*/);
		EXPECT_EQ(A[2], tmp[3]);
		EXPECT_EQ(A[3], tmp[4]);

		A.insert(1, tmp[6]); // {tmp6 , tmp7 , tmp4, tmp5}

		EXPECT_EQ(A[0], tmp[5]);
		EXPECT_EQ(A[1], tmp[6]);
		EXPECT_EQ(A[2], tmp[3]);
		EXPECT_EQ(A[3], tmp[4]);

		A.erase(0); // {tmp7, - , tmp4, tmp5}

		EXPECT_EQ(A[0], tmp[6]);
		EXPECT_EQ(A[1], 0/*nullptr*/);
		EXPECT_EQ(A[2], tmp[3]);
		EXPECT_EQ(A[3], tmp[4]);

		A.push_back(tmp[7]);	A.push_back(tmp[8]);
		// {tmp7, tmp8, tmp9, tmp5}

		EXPECT_EQ(A[0], tmp[6]);
		EXPECT_EQ(A[1], tmp[7]);
		EXPECT_EQ(A[2], tmp[8]);
		EXPECT_EQ(A[3], tmp[4]);
	}
}

TEST(queue, Iterator)
{
	for (std::size_t j{ 0 }; j < 1000; ++j)
	{
		std::random_device rd;
		std::mt19937 mersenne(rd());
		std::stringstream ss;
		Queue<unsigned> P(5);

		std::vector<unsigned> tmp(8);

		for (std::size_t i{ 0 }; i < 8; ++i)
		{
			tmp[i] = mersenne();
			P.push_back(tmp[i]);
		}

		P.pop_front();

		for (auto elem : P)
			ss << elem << ' ';

		std::string str, ans,
			tmp4 = std::to_string(tmp[4]),
			tmp5 = std::to_string(tmp[5]),
			tmp6 = std::to_string(tmp[6]),
			tmp7 = std::to_string(tmp[7]);
		getline(ss, str);
		ans = tmp4 + ' ' + tmp5 + ' ' + tmp6 + ' ' + tmp7
			+ " 0 ";

		EXPECT_EQ(str, ans);
	}
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}