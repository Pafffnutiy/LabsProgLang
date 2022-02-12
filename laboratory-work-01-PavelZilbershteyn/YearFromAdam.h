#ifndef YearFromAdam_H
#define YearFromAdam_H

/*
* Считается, что год от Рождества Христова может быть меньше нуля, а год от Адама (= год от сотворения мирв) - нет
*/

#include <iostream>

class YearFromAdam
{
public:
	YearFromAdam();
   ~YearFromAdam() = default;
    YearFromAdam(int ind, int sol, int lon);
    YearFromAdam(int year, bool Adam = true);
    YearFromAdam(const YearFromAdam& other);

	YearFromAdam& operator--(); 
	YearFromAdam& operator++(); 
	YearFromAdam  operator++(int); 
	YearFromAdam  operator--(int); 

	YearFromAdam& operator= (const YearFromAdam& right);

	YearFromAdam operator+(const YearFromAdam& right) const;
	YearFromAdam operator-(const YearFromAdam& right) const;

	YearFromAdam& operator+=(const YearFromAdam& right);
	YearFromAdam& operator-=(const YearFromAdam& right);

	bool operator==(const YearFromAdam& right) const;

	static std::ostream& NormalFormatOut(std::ostream& stream);     // Флаг вывода в виде 3 чисел (полей) (по умолчанию)
	static std::ostream& YearAdamFormatOut(std::ostream& stream);   // Флаг вывода в виде года от Адама
	static std::ostream& YearJesusFormatOut(std::ostream& stream);  // Флаг вывода в виде года от Р.Х.
	static std::istream& NormalFormatIn(std::istream& stream);		// Флаг ввода в виде 3 чисел (полей) (по умолчанию)
	static std::istream& YearAdamFormatIn(std::istream& stream);	// Флаг ввода в виде года от Адама
	static std::istream& YearJesusFormatIn(std::istream& stream);	// Флаг ввода в виде года от Р.Х.

	friend std::ostream& operator<< (std::ostream& o, const YearFromAdam& object); // по умолчанию - вывод трех чисел (меняется флагами)
	friend std::istream& operator>> (std::istream& in, YearFromAdam& object); // по умолчанию - вывод трех чисел (меняется флагами)

	static int ComputeAdamYear(int ind, int sol, int lon);

	static int AdamToJesus(int YearInAdam);
	static int JesusToAdam(int YearInJesus);

	//Геттеры
	int GetIndict() const;
	int GetSun() const;
	int GetMoon() const;

	//Сеттеры
	void SetIndict(int ind);
	void SetSun(int sol);
	void SetMoon(int lon);

	operator int(); // Возвращает год "от Адама" соответсвующий объекту

private:
	void ForConstrWithParam(int year); // Чтобы избежать копирование кода в конструкторе с параметром

	int indict;
	int sun;
	int moon;
};

#endif //YearFromAdam

