#include "BigNumber.h"
#include <algorithm>
#include <vector>
#include <cmath>

BigNumber::operator std::string()
{
	if (this->sign == 1) return ('-' + this->number);
	else return this->number;
}

void BigNumber::SetNumber(std::string s)
{
	this->number = s;
}

void BigNumber::SetSign(char ch)
{
	if (ch == '+')
		this->sign = 0;
	if (ch == '-')
		this->sign = 1;
}

std::string BigNumber::GetNumber() const
{
	return this->number;
}

char BigNumber::GetSign() const
{
	if (this->sign == false)
		return '+';
	else
		return '-';
}

bool BigNumber::isEven() const
{
	if (this->number.size() != 0)
	{
		int lastdigit = this->number[this->length() - 1] - '0';
		return !(lastdigit % 2);
	}
}

void BigNumber::DeleteZeros()
{
	std::size_t pos{ 0 };
	bool flag = true;

	for (const auto& c : this->number)
	{
		if (c != '0')
		{
			pos = std::find(this->number.begin(), this->number.end(), c) - this->number.begin();
			flag = false;
			break;
		}
	}
	if (!flag)
		this->number = this->number.substr(pos, this->number.length() - pos);
	else this->number = "0";
}

std::size_t BigNumber::length() const
{
	return this->number.length();
}

BigNumber BigNumber::absol() const
{
	return BigNumber(this->number);
}

BigNumber::BigNumber(std::string source)
{
	if (source.size() != 0)
	{
		if (source[0] == '-')
		{
			this->sign = 1;
			this->number = source.substr(1, source.length() - 1);
		}
		else {
			this->number = source;
		}

		this->DeleteZeros();
	}
}

BigNumber::BigNumber(long long source)
{
	if (source < 0)
		sign = 1;

	number = std::to_string(std::llabs(source));
}

BigNumber::BigNumber(const BigNumber& other)
	: number{ other.number }, sign{ other.sign }
{}

bool BigNumber::operator> (const BigNumber& right) const
{
	if (this->sign == 1 && right.sign == 0) return false;
	if (this->sign == 0 && right.sign == 1) return true;
	if (this->sign == 0 && right.sign == 0)
	{
		if (this->length() > right.length()) return true;
		if (this->length() < right.length()) return false;
		if (this->length() == right.length())
		{
			for (std::size_t i{ 0 }; i < this->length(); ++i)
			{
				if (this->number[i] > right.number[i]) return true;
				if (this->number[i] < right.number[i]) return false;
			}
			return false;
		}
	}

	if (this->sign == 1 && right.sign == 1)
	{
		if (this->length() > right.length()) return false;
		if (this->length() < right.length()) return true;
		if (this->length() == right.length())
		{
			for (std::size_t i{ 0 }; i < this->length(); ++i)
			{
				if (this->number[i] > right.number[i]) return false;
				if (this->number[i] < right.number[i]) return true;
			}
			return false;
		}
	}
	return false;
}

bool BigNumber::operator<(const BigNumber& right) const
{
	if (this->sign == 1 && right.sign == 0) return true;
	if (this->sign == 0 && right.sign == 1) return false;
	if (this->sign == 0 && right.sign == 0)
	{
		if (this->length() > right.length()) return false;
		if (this->length() < right.length()) return true;
		if (this->length() == right.length())
		{
			for (std::size_t i{ 0 }; i < this->length(); ++i)
			{
				if (this->number[i] > right.number[i]) return false;
				if (this->number[i] < right.number[i]) return true;
			}
			return false;
		}
	}
	if (this->sign == 1 && right.sign == 1)
	{
		if (this->length() > right.length()) return true;
		if (this->length() < right.length()) return false;
		if (this->length() == right.length())
		{
			for (std::size_t i{ 0 }; i < this->length(); ++i)
			{
				if (this->number[i] > right.number[i]) return true;
				if (this->number[i] < right.number[i]) return false;
			}
			return false;
		}
	}

	return false;
}

bool BigNumber::operator==(const BigNumber& right) const
{
	if (this->sign == right.sign && this->number == right.number)
		return true;
	return false;
}

bool BigNumber::operator!=(const BigNumber& right) const
{
	return !(*this == right);
}

bool BigNumber::operator>=(const BigNumber& right) const
{
	if (*this > right || *this == right)
		return true;
	return false;
}

bool BigNumber::operator<=(const BigNumber& right) const
{
	if (*this < right || *this == right)
		return true;
	return false;
}

BigNumber BigNumber::operator+ (const BigNumber& right) const
{
	BigNumber result;

	if (this->sign == 1 && right.sign == 0) return (right.absol() - this->absol()); //-x+y = y-x
	if (this->sign == 0 && right.sign == 1) return (this->absol() - right.absol());   // x-y
	if (this->sign == 1 && right.sign == 1)						    // -x-y = -(x+y)
	{
		/*BigNumber first(*this), second(right);
		first.sign = 0; second.sign = 0;*/
		result = this->absol() + right.absol();
		result.sign = 1;
		return result;
	}

	if (this->sign == 0 && right.sign == 0)
	{
		int diff = this->length() - right.length();
		std::string ImZero(std::abs(diff)+1, '0');  //xxxxxx + 000yyy

		BigNumber first("0"), second;
		if (*this > right) {
			first.number += this->number;
			second = ImZero + right.number;
		}
		else {
			first.number += right.number;
			second = ImZero + this->number;
		}
		std::string stroka(first.length() + 1, '0');

		result = stroka;

		//result.number[result.length() - 1] = static_cast<char>((((first.number[this->length() - 1] - '0') + (second.number[this->length() - 1] - '0'))) % 10 + '0');

		for (std::size_t  i =  first.length(); i > 0; --i)
		{
			int digit1 = (first.number[i-1] - '0');
			int digit2 = (second.number[i-1] - '0');
			int cnt = i-2;
			//int olddigit1 = (first.number[i + 1] - '0');
			//int olddigit2 = (second.number[i + 1] - '0');

			if (digit1 + digit2 >= 10)
			{
				result.number[i] = (digit1 + digit2) % 10 + '0';
				if ((first.number[i-2]-'0') + 1 == 10)
				{
					while ((first.number[cnt] + 1 - '0') == 10)
					{
						first.number[cnt] = '0';
						--cnt;
					}
					first.number[cnt] = (first.number[cnt] - '0') + 1 + '0';
				}
				else { first.number[i-2] += 1; }
			}
			else { result.number[i] = digit1 + digit2 + '0'; }

			//result.number[i+1] = static_cast<char>(((digit1 + digit2 + (olddigit1 + olddigit2) / 10) % 10) + '0');
		}

		result.number[0] = ((first.number[0]-'0') + (second.number[0]-'0')) / 10 + '0';

		/*std::size_t pos{ 0 };

		for (const auto& c : result.number)
		{
			if (c != '0')
			{
				pos = std::find(result.number.begin(), result.number.end(), c) - result.number.begin();
				break;
			}
		}

		result.number = result.number.substr(pos, result.number.length() - pos);*/

		result.DeleteZeros();
		return result;
	}
	return result;
}
BigNumber  BigNumber::operator- (const BigNumber& right) const
{
	BigNumber result;
	if (this->sign == 0 && right.sign == 1) //x-(-y) = x+y
	{
		return this->absol() + right.absol();
	}
	if (this->sign == 1 && right.sign == 0) //-x-y = -(x+y)
	{
		result = this->absol() + right.absol();
		result.sign = 1;
		return result;
	}
	if (this->sign == 1 && right.sign == 1) //-x-(-y) = y-x
	{
		return right.absol() - this->absol();
	}

	if (this->sign == 0 && right.sign == 0)
	{
		if (right > *this)
		{
			result = right.absol() - this->absol();
			result.sign = 1;
			return result;
		}
		else
		{
			std::string zeros(this->length(), '0');
			result.number = zeros;
			int diff = this->length() - right.length();
			std::string ImZero(std::abs(diff), '0');
			std::string stroka = ImZero + right.number;
			BigNumber second, first(*this);
			second.number = stroka;

			for (int i = this->length() - 1 ; i >= 0; --i)
			{
				int olddigit1 = first.number[i] - '0';
				int olddigit2 = second.number[i] - '0';
				int cnt = i - 1;

				if (olddigit1 < olddigit2)
				{
					result.number[i] = (10 + olddigit1 - olddigit2) + '0';
					if (this->number[i - 1] != '0')
					{
						first.number[i-1] = (first.number[i - 1] - '0') - 1 + '0';
					}
					else {
						while (first.number[cnt] == '0')
						{
							first.number[cnt] = '9';
							--cnt;
						}
						--first.number[cnt];
					}
				}
				else { result.number[i] = olddigit1 - olddigit2 + '0'; }
			}

			result.DeleteZeros();
		}

	}
	return result;
}
BigNumber  BigNumber::operator* (const BigNumber& right) const
{
	BigNumber first(*this), second(right);
	std::reverse(first.number.begin(), first.number.end());
	std::reverse(second.number.begin(), second.number.end());
	//std::string zeros(this->length() + right.length() + 1, '0');
	BigNumber result;
	//result.number = zeros;

	/*std::int64_t diff = this->length() - right.length();
	std::string addzeros(std::abs(diff), '0');

	if (diff < 0)
		first.number = addzeros + first.number;
	if (diff > 0)
		second.number = addzeros + second.number;*/

	// из-за переполнения char'a при данном алгоритме перейдем от string к vector<unsigned short>

	std::vector<unsigned short> firstVec, secondVec, resultVec(this->length() + right.length() + 1);

	for (const auto& c : first.number)
		firstVec.push_back(c - '0');
	for (const auto& c : second.number)
		secondVec.push_back(c - '0');


	for (std::size_t i{0}; i < first.length(); ++i) {
		for (std::size_t j{ 0 }; j < second.length(); ++j) {
			resultVec[i + j] += firstVec[i] * secondVec[j];
		}
	}

	std::reverse(resultVec.begin(), resultVec.end());

	for (std::size_t i{ resultVec.size()-1 }; i > 0; --i)
	{
		long digit = resultVec[i];
		if (digit >= 10)
		{
			resultVec[i] = digit % 10;
			resultVec[i - 1] += digit / 10;
		}
	}

	for (const auto& v : resultVec)
		result.number += (v + '0');

	result.DeleteZeros();
	result.sign = (this->sign ^ right.sign) ? 1 : 0;

	return result;
}


BigNumber  BigNumber::operator/ (const BigNumber& right) const
{
	if (this->absol() < right) return BigNumber(0);

	BigNumber delimoe(this->absol());
	BigNumber cnt;

	std::size_t j = 0;

	//какой-то цикл
	while(this->absol() - right.absol()*cnt >= right.absol())
	//for (std::size_t i{ 0 }; i < delimoe.length(); ++i)
	{
		BigNumber delitel(right.absol());
		BigNumber temp(0);

		if (delimoe < delitel)
		{
			cnt.number += '0';
			++j;
			continue;
		}

		std::string zeros(delimoe.length() - delitel.length() - j, '0');
		delitel.number += zeros;

		while (delimoe >= delitel)
		{
			delimoe -= delitel;
			temp += 1;
		}

		cnt.number += temp.number;

	}

	cnt.DeleteZeros();
	cnt.sign = (this->sign ^ right.sign) ? 1 : 0;
	return cnt;
}

BigNumber BigNumber::operator% (const BigNumber& right) const
{
	BigNumber result;
	if (this->absol() < right.absol())
		return (*this);

	BigNumber Antje(this->absol() / right.absol());

	result = this->absol() - Antje * right.absol();

	return result;
}

BigNumber& BigNumber::operator+=(const BigNumber& right)
{
	*this = *this + right;
	return (*this);
}

BigNumber& BigNumber::operator-=(const BigNumber& right)
{
	*this = *this - right;
	return (*this);
}

BigNumber& BigNumber::operator*=(const BigNumber& right)
{
	*this = *this * right;
	return (*this);
}

BigNumber& BigNumber::operator/=(const BigNumber& right)
{
	*this = *this / right;
	return (*this);
}

BigNumber& BigNumber::operator%=(const BigNumber& right)
{
	*this = *this % right;
	return (*this);
}


BigNumber& BigNumber::operator= (const BigNumber& right)
{
	this->number = right.number;
	this->sign = right.sign;
	return (*this);
}
BigNumber& BigNumber::operator= (std::string NewNum)
{
	if (NewNum[0] == '-')
	{
		this->sign = 1;
		this->number = NewNum.substr(1, NewNum.length() - 1);
	}
	else {
		this->number = NewNum;
		this->sign = 0;
	}
	return (*this);
}

BigNumber BigNumber::power(const BigNumber& exp) const
{
	if (exp == 0) return BigNumber(1);
	if (exp <  0) return BigNumber(0);

	BigNumber result("1");
	for (BigNumber i("0"); i < exp; ++i)
	{
		result *= (*this);
	}

	return result;
}

BigNumber& BigNumber::operator--()
{
	BigNumber dec("1");
	*this = *this - dec;
	return *this;
}

BigNumber& BigNumber::operator++()
{
	BigNumber inc(1);

	*this = *this + inc;
	return *this;
}

BigNumber BigNumber::operator++(int)
{
	BigNumber nov(*this);
	++(*this);
	return nov;
}

BigNumber BigNumber::operator--(int)
{
	BigNumber nov(*this);
	--(*this);
	return nov;
}

std::ostream& operator<< (std::ostream& out, const BigNumber& right)
{
	if (right.sign == 1)
		out << "-" << right.number;
	else
	{
		out << right.number;
	}

	return out;

}

std::istream& operator>> (std::istream& i, BigNumber& right)
{
	std::string source;
	i >> source;

	if (source[0] == '-')
	{
		right.sign = 1;
		right.number = source.substr(1, source.length() - 1);
	}
	else { right.number = source; }

	return i;
}

BigNumber operator-(const BigNumber& right)
{
	BigNumber result(right);
	result.sign = !right.sign;
	return result;
}
