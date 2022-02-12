#ifndef DateAndTime_h
#define DateAndTime_h

#include <iostream>

class DateAndTime
{
public:
	// "Для классов разработать необходимые конструкторы, деструктор, конструктор копирования"
	DateAndTime() = default;
	//DateAndTime(std::uint64_t s, bool flag = true); // преобразование из UnixTime в DateAndTime
	DateAndTime(std::uint64_t s, bool flag = false); // преобразование из FileTime в DateAndTime
	DateAndTime(const DateAndTime& obj);
	~DateAndTime() = default;

	/*
	* Используя перегрузку операторов(operator) разработать стандартную арифметику объектов,
	* включающую арифметические действия над объектами
	* и стандартными типами(целыми, вещественными, строками – в зависимости от вида объектов), присваивание, ввод и вывод в
	* стандартные потоки(используя операторы « << » и « >> »),
	*/

	DateAndTime operator+ (const DateAndTime& right) const;
	DateAndTime operator+ (int right) const;
	friend DateAndTime operator+ (int left, const DateAndTime& right);
	std::int64_t operator- (const DateAndTime& right) const;
	friend std::ostream& operator<< (std::ostream& o, const DateAndTime& obj); // Вывод в формате hh:mi:ss dd.mm.yyyy
	friend std::istream& operator>> (std::istream& i, DateAndTime& obj); //Ввод в формате UnixTime
	DateAndTime& operator=(const DateAndTime& other);
	DateAndTime& operator=(std::uint64_t num);
	//а где DateAndTime + int ?
	//теперь есть, int+DateAndTime тоже

	//методы, обеспечивающие изменение отдельных составных частей объекта (Сеттеры)
	void SetYear(std::uint64_t y);
	void SetMonth(std::uint64_t m);
	void SetDay(std::uint64_t d);
	void SetHour(std::uint64_t h);
	void SetMinute(std::uint64_t min);
	void SetSecond(std::uint64_t s);
	//а где "геттеры" ?
	//теперь есть

	std::uint64_t GetYear() const;
	std::uint64_t GetMonth() const;
	std::uint64_t GetDay() const;
	std::uint64_t GetHour() const;
	std::uint64_t GetMinute() const;
	std::uint64_t GetSecond() const;

	/*
	* "Приведение к/от базового типа данных"
	*
	* Приведение от базового типа - конструктор DateAndTime(std::uint64_t s), который приводит от UnixTime (std::uint64_t) к DateAndTime
	*							 и конструктор DateAndTime(std::uint64_t s, bool) который приводит от FileTime (std::uint64_t) к DateAndTime
	* Приведение к базовому типу реализуем в ввиде перегрузки оператора приведения типа (строка 48) и соответсвующего метода (строка 49)
	*
	*/

	operator std::uint64_t(); // Приведение к UnixTime format
	std::uint64_t ToFileTime() const; // Приведение к FileTime format

	//======

	//Чисто вспомогательные методы конвертации из Unix в File и обратно 
	//(можно использовать для операции взятия из потока и операции присваивания, так как для них перегрузка только для UnixTime)

	static std::uint64_t UnixToFile(std::uint64_t Unix);
	static std::uint64_t FileToUnix(std::uint64_t File);

	//======

	// Возможно полезная функция. Длительность в секундах
	std::uint64_t duration(const DateAndTime& right) const;

private:
	std::uint64_t year;
	std::uint64_t month;
	std::uint64_t day;
	std::uint64_t hour;
	std::uint64_t minute;
	std::uint64_t second;
	std::uint64_t UnixSec;  //зачем?
	std::uint64_t FileTime; //--"--?
};

#endif