#include "DateAndTime.h"
#include <sstream>
#include <string>
#include <cassert>

int main()
{
	{
		//test1. Проверка работоспособности конструктора по UnixTime
		DateAndTime Obj(1618242592);

		std::stringstream ss;
		std::string str;
		ss << Obj;
		std::getline(ss, str);
		bool correct1 = (str == "18:49:52 12.04.2021");
		//Странно конечно что "Дата и время" у вас выводятся как "Время и дата"
		//в винде вроде бы пишется сначала время, а потом какой день

		assert(correct1);
	}

	{
		//test2. Проверка работоспособности конструктора по FileTime
		DateAndTime Obj(132627161920000000, true);

		std::stringstream ss;
		std::string str;
		ss << Obj;
		std::getline(ss, str);
		bool correct2 = (str == "18:49:52 12.04.2021");

		assert(correct2);
	}

	{
		//test3. Проверка работоспособности конструктора копирования
		DateAndTime Obj(1618250287);
		DateAndTime Copy(Obj);

		std::stringstream ss;
		std::string str;
		ss << Copy;
		std::getline(ss, str);
		bool correct3 = (str == "20:58:07 12.04.2021");

		assert(correct3);
	}

	{
		//test4. Проверка работоспособности перегрузки "+"
		DateAndTime Obj1(132627161920000000, true);
		DateAndTime Obj2(1618250287);

		std::stringstream ss;
		std::string str;
		ss << (Obj1 + Obj2);
		std::getline(ss, str);
		bool correct4 = (str == "12:47:59 23.07.2072");

		assert(correct4);
	}

	{
		//test5. Проверка работоспособности перегрузки "-" и метода duration
		DateAndTime Obj1(132627161920000000, true);
		DateAndTime Obj2(1618250287);//1618242592

		std::int64_t diff = (Obj1 - Obj2);
		std::uint64_t dur = Obj1.duration(Obj2);

		bool correct5 = (diff == -7695) && (dur == 7695);

		assert(correct5);
	}

	{
		//test6 Проверка работоспособности перегрузки "<<"

		assert(true); //проверена на предыдущих 4 тестах
	}

	{
		//test7. Проверка работоспособности перегрузки ">>" и Проверка работоспособности конструкций ostream << Obj1 << Obj2; istream >> Obj1 >> Obj2; (композиция операций помещения из/в поток)

		// Пусть есть 2 потока, в одному дано число в UnixTime, во втором в FileTime

		std::uint64_t Unix = 1618241234;
		std::uint64_t File = 132636859450000000;

		std::stringstream ssin;
		ssin << std::to_string(Unix) << ' ' << std::to_string(DateAndTime::FileToUnix(File));

		DateAndTime Obj1, Obj2;

		ssin >> Obj1 >> Obj2;

		std::stringstream ssout;
		ssout << Obj1 << '\n' << Obj2;

		std::string str1, str2;
		std::getline(ssout, str1);
		std::getline(ssout, str2);
		bool correct7 = (str1 == "18:27:14 12.04.2021") && (str2 == "00:12:25 24.04.2021");

		assert(correct7);
	}

	{
		//test8. Проверка работоспособности перегрузок operator=(const DateAndTime& other); operator=(std::uint64_t num);
		DateAndTime Obj1, Obj2, Obj3;

		Obj1 = 1618250287; // UnixTime
		Obj2 = DateAndTime::FileToUnix(132627238870000000); // FileTime
		Obj3 = Obj2;

		std::stringstream ss;
		std::string str1, str2, str3;
		ss << Obj1 << '\n' << Obj2 << '\n' << Obj3;
		std::getline(ss, str1); std::getline(ss, str2); std::getline(ss, str3);
		bool correct8 = (str1 == "20:58:07 12.04.2021") && (str2 == "20:58:07 12.04.2021") && (str3 == "20:58:07 12.04.2021");

		assert(correct8);
	}

	{
		//test9. Проверка работоспособности SetYear
		DateAndTime Obj1;

		Obj1 = 1618250287; // UnixTime

		std::stringstream ss;
		std::string str1, str2;
		ss << Obj1 << '\n';
		Obj1.SetYear(2100);
		ss << Obj1;

		std::getline(ss, str1); std::getline(ss, str2);
		bool correct9 = (str1 == "20:58:07 12.04.2021") && (str2 == "20:58:07 12.04.2100");

		assert(correct9);
	}

	{
		//test10. Проверка работоспособности SetMonth
		DateAndTime Obj1;

		Obj1 = 1618250287; // UnixTime

		std::stringstream ss;
		std::string str1, str2;
		ss << Obj1 << '\n';
		Obj1.SetMonth(1);
		ss << Obj1;

		std::getline(ss, str1); std::getline(ss, str2);
		bool correct10 = (str1 == "20:58:07 12.04.2021") && (str2 == "20:58:07 12.01.2021");

		assert(correct10);
	}

	{
		//test11. Проверка работоспособности SetDay. В апреле 30 дней, поэтому SetDay(31) не должен менять объект
		DateAndTime Obj1;

		Obj1 = 1618250287; // UnixTime

		std::stringstream ss;
		std::string str1, str2;
		ss << Obj1 << '\n';
		Obj1.SetDay(31);
		ss << Obj1;

		std::getline(ss, str1); std::getline(ss, str2);
		bool correct11 = (str1 == "20:58:07 12.04.2021") && (str2 == "20:58:07 12.04.2021");

		assert(correct11);
	}

	{
		//test12. Проверка работоспособности SetHour
		DateAndTime Obj1;

		Obj1 = 1618250287; // UnixTime

		std::stringstream ss;
		std::string str1, str2;
		ss << Obj1 << '\n';
		Obj1.SetHour(22);
		ss << Obj1;

		std::getline(ss, str1); std::getline(ss, str2);
		bool correct12 = (str1 == "20:58:07 12.04.2021") && (str2 == "22:58:07 12.04.2021");

		assert(correct12);
	}

	{
		//test13. Проверка работоспособности SetMinute. SetMinute(210) не должен менять объект
		DateAndTime Obj1;

		Obj1 = 1618250287; // UnixTime

		std::stringstream ss;
		std::string str1, str2;
		ss << Obj1 << '\n';
		Obj1.SetMinute(210);
		ss << Obj1;

		std::getline(ss, str1); std::getline(ss, str2);
		bool correct13 = (str1 == "20:58:07 12.04.2021") && (str2 == "20:58:07 12.04.2021");

		assert(correct13);
	}

	{
		//test14. Проверка работоспособности SetSecond
		DateAndTime Obj1;

		Obj1 = 1618250287; // UnixTime

		std::stringstream ss;
		std::string str1, str2;
		ss << Obj1 << '\n';
		Obj1.SetSecond(30);
		ss << Obj1;

		std::getline(ss, str1); std::getline(ss, str2);
		bool correct14 = (str1 == "20:58:07 12.04.2021") && (str2 == "20:58:30 12.04.2021");

		assert(correct14);
	}

	{
		//test15. Проверка работоспособности приведения к базовому типу
		DateAndTime Obj1;

		Obj1 = 1053418860; // UnixTime

		std::uint64_t Unix = static_cast<std::uint64_t> (Obj1);
		std::uint64_t File = Obj1.ToFileTime();

		bool correct15 = (Unix == 1053418860) && (File == 126978924600000000);

		assert(correct15);
	}

	{
		//test16. Проверка работоспособности геттеров

		DateAndTime obj(1618242592);

		bool correct16 = (obj.GetHour() == 18 && obj.GetMinute() == 49 && obj.GetSecond() == 52
			&& obj.GetDay() == 12 && obj.GetMonth() == 04 && obj.GetYear() == 2021);

		assert(correct16);
	}

	return 0;
}