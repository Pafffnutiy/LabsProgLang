#include <string>
#include <iostream>

#ifndef BigNumber_H
#define BigNumber_H
class BigNumber
{
public:
	BigNumber() = default;
	~BigNumber() = default;
	BigNumber(std::string source);
	BigNumber(long long source);
	BigNumber(const BigNumber& other);

	BigNumber absol() const;

	//Логика
	bool operator>  (const BigNumber& right) const;
	bool operator<  (const BigNumber& right) const;
	bool operator== (const BigNumber& right) const;
	bool operator!= (const BigNumber& right) const;
	bool operator>= (const BigNumber& right) const;
	bool operator<= (const BigNumber& right) const;

	//Арифметика
	BigNumber  operator+ (const BigNumber& right) const;
	BigNumber  operator- (const BigNumber& right) const;
	BigNumber  operator* (const BigNumber& right) const;
	BigNumber  operator/ (const BigNumber& right) const; // Деление нацело
	BigNumber  operator% (const BigNumber& right) const; // Остаток от деления, считаем, что, независимо от знаков чисел, остаток вычисляем
														 // как положительное число от модулей данных чисел (-13%5=3)
	BigNumber& operator+=(const BigNumber& right);
	BigNumber& operator-=(const BigNumber& right);
	BigNumber& operator*=(const BigNumber& right);
	BigNumber& operator/=(const BigNumber& right);
	BigNumber& operator%=(const BigNumber& right);
	BigNumber& operator= (const BigNumber& right);
	BigNumber& operator= (std::string NewNum);

	BigNumber power(const BigNumber& exp) const; //Возведение в степень (если показатель <0, то a^(-b) = 1/a^(-b) = 0, так как целые числа)

	BigNumber& operator--(); //префиксный декремент
	BigNumber& operator++(); //префиксный инкремент
	BigNumber operator++(int); // постфиксный инкремент
	BigNumber operator--(int); // постфиксный декремент

	friend std::ostream& operator<< (std::ostream& out, const BigNumber& right);
	friend std::istream& operator>> (std::istream& i, BigNumber& right);
	friend BigNumber operator- (const BigNumber& right); //унарный минус

	operator std::string();

	//Сеттеры
	void SetNumber(std::string s); //имеется ввиду именно задание поля number, а не задание всего числа типа BigNumber
	void SetSign(char ch); //установка знака с помощью символов '+' и '-'

	//Геттеры
	std::string GetNumber() const; //получение поля number, а не всего числа типа BigNumber
	char GetSign() const; //получение знака числа в виде символа '+' или '-'

	bool isEven() const; //проверка четности числа
private:
	void DeleteZeros();
	std::size_t length() const;

	std::string number; //модуль числа
	bool sign = 0; // 0 - positive, 1 - negative
};

#endif