#include <iostream>
#include <cassert>
#include <sstream>
#include "YearFromAdam.h"

int main()
{
	{ //TEST1. Проверка работоспособности конструкторов
		YearFromAdam obj1, obj2(-2, -28, 20), obj3(7160), obj4(1652, false), obj5(obj2);

		bool correct1p1 = (obj1.GetIndict() == 0) && (obj1.GetSun() == 0) && (obj1.GetMoon() == 0);
		bool correct1p2 = (obj2.GetIndict() == 13) && (obj2.GetSun() == 28) && (obj2.GetMoon() == 1);
		bool correct1p3 = (obj3.GetIndict() == 5) && (obj3.GetSun() == 20) && (obj3.GetMoon() == 16);
		bool correct1p4 = (obj4.GetIndict() == 5) && (obj4.GetSun() == 20) && (obj4.GetMoon() == 16);
		bool correct1p5 = (obj5.GetIndict() == 13) && (obj5.GetSun() == 28) && (obj5.GetMoon() == 1);

		bool correct1 = correct1p1 && correct1p2 && correct1p3 && correct1p4 && correct1p5;

		assert(correct1);  
	}

	{//TEST2. Проверка работоспособности арифметических операций и присваивания
		YearFromAdam obj(-1, -28, 20);

		bool correct2p1 = (obj++ == YearFromAdam(14, 28, 1))
			           && (++obj == YearFromAdam(1, 2, 3))
			           && (obj-- == YearFromAdam(1, 2, 3))
			           && (--obj == YearFromAdam(14, 28, 1));

		YearFromAdam obj1(15, 28, 19), obj2;

		obj2 = obj1;

		bool correct2p2 = (obj2 == YearFromAdam(15, 28, 19));

		obj1 += obj;
		obj2 -= obj;

		bool correct2p3 = (obj1 == YearFromAdam(14, 28, 1))
					   && (obj2 == YearFromAdam(1, 28, 18));

		bool correct2p4 = (obj1 - obj2 = YearFromAdam(15, 28, 19))
					   && (obj + obj = YearFromAdam(13, 28, 2));

		bool correct2 = correct2p1 && correct2p2 && correct2p3 && correct2p4;		

		assert(correct2);
	}

	{//Test3. Проверка работоспособности геттеров и сеттеров
		YearFromAdam obj, obj1(1, 28, 13);

		bool correct3p1 = (obj1.GetIndict() == 1) && (obj1.GetSun() == 28) && (obj1.GetMoon() == 13);

		obj.SetIndict(-22); obj.SetSun(38); obj.SetMoon(0);

		bool correct3p2 = obj == YearFromAdam(8, 10, 19);

		bool correct3 = correct3p1 && correct3p2;

		assert(correct3);
	}

	{//Test4. Проверка работоспособности оператора приведения к базовому типу и функций подсчета и перевода годов
		YearFromAdam obj(3, 20, 17);

		int YearInAdam = static_cast<int>(obj);
		int YearInJesus = YearFromAdam::AdamToJesus(YearInAdam);

		int Adam = YearFromAdam::JesusToAdam(1652);


		bool correct4 = (YearInAdam == 5508)
					 && (YearInJesus == 0)
					 && (Adam == 7160);

		assert(correct4);
	}

	{//Test5. Проверка работоспособности перегрузки операции помещения в поток и взятия из потока в различных формах
		YearFromAdam obj(15, 13, 10);

		std::stringstream stream1;

		stream1 << obj << "| " << YearFromAdam::YearAdamFormatOut << obj << "| " << YearFromAdam::YearJesusFormatOut
			   << obj << "| " << YearFromAdam::NormalFormatOut   << obj;

		std::string output;
		getline(stream1, output);

		bool correct5p1 = output == "Indict: 15, CircleToSun: 13, CircleToMoon: 10| YearFromJesus: -4263| YearFromAdam: 1245| Indict: 15, CircleToSun: 13, CircleToMoon: 10";
		

		YearFromAdam obj1, obj2, obj3, obj4;

		std::stringstream stream2;

		stream2 << "-5 31 0 7895 1324 0 0 0";

		stream2 >> obj1 >> YearFromAdam::YearAdamFormatIn >> obj2 >> YearFromAdam::YearJesusFormatIn >> obj3 
			    >> YearFromAdam::NormalFormatIn >> obj4;

		bool correct5p2 = (obj1 == YearFromAdam(10, 3, 19))
					   && (obj2 == YearFromAdam(7895)) //(5,27,10)
					   && (obj3 == YearFromAdam(1324, false)) //(7,28,11)
					   && (obj4 == YearFromAdam(15, 28, 19));

		bool correct5 = correct5p1 && correct5p2;

		assert(correct5);
	}

	return 0;
}
