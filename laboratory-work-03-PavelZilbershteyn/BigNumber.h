#ifndef BigNumber_H
#define BigNumber_H

#include <string>
#include <iostream>
#include "ADT.h"

class BigNumber : public ADT
{
private:
	void DeleteZeros();
	std::size_t length() const;

	std::string number; 
	bool sign = 0; 

public:
	BigNumber() = default;
	~BigNumber() = default;
	BigNumber(std::string source);
	BigNumber(long long source);
	BigNumber(const BigNumber& other);

	BigNumber absol() const;

	//=====
	bool operator>  (const BigNumber& right) const;
	bool operator<  (const BigNumber& right) const;
	bool operator== (const BigNumber& right) const;
	bool operator!= (const BigNumber& right) const;
	bool operator>= (const BigNumber& right) const;
	bool operator<= (const BigNumber& right) const;

	//======
	BigNumber  operator+ (const BigNumber& right) const;
	BigNumber  operator- (const BigNumber& right) const;
	BigNumber  operator* (const BigNumber& right) const;
	BigNumber  operator/ (const BigNumber& right) const;
	BigNumber  operator% (const BigNumber& right) const;
														 
	BigNumber& operator+=(const BigNumber& right);
	BigNumber& operator-=(const BigNumber& right);
	BigNumber& operator*=(const BigNumber& right);
	BigNumber& operator/=(const BigNumber& right);
	BigNumber& operator%=(const BigNumber& right);
	BigNumber& operator= (const BigNumber& right);
	BigNumber& operator= (std::string NewNum);

	BigNumber power(const BigNumber& exp) const; 

	BigNumber& operator--(); 
	BigNumber& operator++(); 
	BigNumber operator++(int); 
	BigNumber operator--(int); 

	friend std::ostream& operator<< (std::ostream& out, const BigNumber& right);
	friend std::istream& operator>> (std::istream& i, BigNumber& right);
	friend BigNumber operator- (const BigNumber& right);

	operator std::string();

	void SetNumber(std::string s); 
	void SetSign(char ch); 


	std::string GetNumber() const; 
	char GetSign() const; 

	bool isEven() const; 
};

#endif