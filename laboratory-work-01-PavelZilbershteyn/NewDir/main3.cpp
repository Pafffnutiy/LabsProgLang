#include "Matrix.h"
#include <cassert>
#include <sstream>

int main()
{
	{ //Test1. Проверка работоспособности конструкторов, геттеров и сеттеров
		Matrix m1, m2(2, 3);

		bool correct1p1 = (m1.GetRows() == 0 && m1.GetCols() == 0 && m1.GetCoefs().size() == 0)
					   && (m2.GetRows() == 2 && m2.GetCols() == 3 && m2.GetCoefs().size() == 0);
		
		m2.SetCols(3); m2.SetRows(4);

		m2(0, 0) = 1;
		m2(1, 1) = 2;
		m2(2, 2) = 3;

		Matrix m3(m2);

		bool correct1p2 = (m3.GetCols() == 3 && m3.GetRows() == 4)
					   && (m3.GetCoefs()[0].i == 0 && m3.GetCoefs()[0].j == 0 && m3.GetCoefs()[0].value == 1)
					   && (m3.GetCoefs()[1].i == 1 && m3.GetCoefs()[1].j == 1 && m3.GetCoefs()[1].value == 2)
					   && (m3.GetCoefs()[2].i == 2 && m3.GetCoefs()[2].j == 2 && m3.GetCoefs()[2].value == 3);
		
		bool correct1 = correct1p1 && correct1p2;

		assert(correct1);
	}

	{ // Test2. Проверка работоспособности арифметики, транспонирования, присваивания и равенства

		Matrix m1(2, 3), m2(2,3), mr;

		m1(0, 0) = 15; m1(1, 1) = 10; m1(0, 2) = 42;

		m2(0, 0) = 11; m2(1, 1) = 22; m2(1, 2) = 5;

		mr = m1 + m2;

		bool correct2p1 = (mr.GetRows() == 2 && mr.GetCols() == 3)
					   && (mr.GetCoefs()[0].i == 0 && mr.GetCoefs()[0].j == 0 && mr.GetCoefs()[0].value == 26)
					   && (mr.GetCoefs()[1].i == 0 && mr.GetCoefs()[1].j == 2 && mr.GetCoefs()[1].value == 42)
					   && (mr.GetCoefs()[2].i == 1 && mr.GetCoefs()[2].j == 1 && mr.GetCoefs()[2].value == 32)
					   && (mr.GetCoefs()[3].i == 1 && mr.GetCoefs()[3].j == 2 && mr.GetCoefs()[3].value ==  5);

		mr = 5 * (m2 - m1).Transpose() * (-2);

		bool correct2p2 = (mr.GetRows() == 3 && mr.GetCols() == 2)
					   && (mr.GetCoefs()[0].i == 0 && mr.GetCoefs()[0].j == 0 && mr.GetCoefs()[0].value ==   40)
					   && (mr.GetCoefs()[1].i == 2 && mr.GetCoefs()[1].j == 0 && mr.GetCoefs()[1].value ==  420)
					   && (mr.GetCoefs()[2].i == 1 && mr.GetCoefs()[2].j == 1 && mr.GetCoefs()[2].value == -120)
					   && (mr.GetCoefs()[3].i == 2 && mr.GetCoefs()[3].j == 1 && mr.GetCoefs()[3].value ==  -50);

		Matrix m3(1,3), m4(3,2);
		m3(0, 0) = 1; m3(0, 2) = 1;
		m4(0, 0) = 1; m4(1, 0) = 5;	m4(1, 1) = 6; m4(2, 1) = 3;

		mr = m3 * m4;

		bool correct2p3 = (mr.GetRows() == 1 && mr.GetCols() == 2)
					   && (mr.GetCoefs()[0].i == 0 && mr.GetCoefs()[0].j == 0 && mr.GetCoefs()[0].value == 1)
					   && (mr.GetCoefs()[1].i == 0 && mr.GetCoefs()[1].j == 1 && mr.GetCoefs()[1].value == 3);

		Matrix m5(2, 2), m6(2, 2);
		m5(0, 1) = 1; m5(1, 0) = 2;
		m6(1, 0) = 2; m6(0, 1) = 1;

		bool correct2p4 = (m5 == m6) && !(mr == m5);

		bool correct2 = correct2p1 && correct2p2 && correct2p3 && correct2p4;

		assert(correct2);
	}

	{ //Test3. Проверка работоспособности операций помещения в поток и взятия из потока
		std::stringstream ss;
		Matrix m1(3,3), m2(3,3);

		m1(0, 0) = 1; m1(1, 1) = 1; m1(2, 2) = 1;
		m2(0, 2) = 5; m2(1, 0) = 3; m2(2, 1) = 8;

		ss << (m1 * m2).Transpose();

		std::string str1, str2, str3, str4;

		std::getline(ss, str1);
		std::getline(ss, str2);
		std::getline(ss, str3);
		std::getline(ss, str4);

		bool correct3p1 = (str1 == "3 3")
				       && (str2 == "0 3 0")
					   && (str3 == "0 0 8")
					   && (str4 == "5 0 0");

		Matrix mInput1, mInput2;
		std::stringstream ss1;

		ss1 << "3 3\n0 3 0\n0 0 8\n5 0 0" << "\n2 2 0 0 0 1";

		ss1.seekg(0, std::istream::beg);

		ss1 >> mInput1 >> mInput2;

		bool correct3p2 = (mInput1 == (m1 * m2).Transpose())
					   && (mInput2.GetRows() == 2 && mInput2.GetCols() == 2)
					   && (mInput2.GetCoefs()[0].i == 1 && mInput2.GetCoefs()[0].j == 1 && mInput2.GetCoefs()[0].value == 1);

		bool correct3 = correct3p1 && correct3p2;

		assert(correct3);
	}
		return 0;
}