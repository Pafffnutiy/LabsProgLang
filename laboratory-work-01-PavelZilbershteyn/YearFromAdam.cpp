#include "YearFromAdam.h"

YearFromAdam::YearFromAdam()
	:indict{ 0 }, sun{ 0 }, moon{ 0 }
{}

YearFromAdam::YearFromAdam(int ind, int sol, int lon)
{
	indict = (ind % 15 == 0) ? 15 : (ind % 15);
	sun    = (sol % 28 == 0) ? 28 : (sol % 28);
	moon   = (lon % 19 == 0) ? 19 : (lon % 19); 

	if (indict < 0) indict += 15;
	if (sun < 0) sun += 28;
	if (moon < 0) moon += 19;

}

void YearFromAdam::ForConstrWithParam(int year)
{
	if (year > 0)
	{
		this->indict = (year % 15 == 0) ? 15 : (year % 15);
		this->sun = (year % 28 == 0) ? 28 : (year % 28);
		this->moon = (year % 19 == 0) ? 19 : (year % 19);
	}
	else {
		this->indict = 0;
		this->sun = 0;
		this->moon = 0;
	}
}

YearFromAdam::YearFromAdam(int year, bool Adam)
{
	if (Adam)
		ForConstrWithParam(year);
	else 
		ForConstrWithParam(YearFromAdam::JesusToAdam(year));
}

YearFromAdam::YearFromAdam(const YearFromAdam& other)
	:indict{ other.indict }, sun{ other.sun }, moon{ other.moon }
{}

YearFromAdam& YearFromAdam::operator--()
{
	YearFromAdam temp(--(this->indict), --(this->sun), --(this->moon));
	*this = temp;
	return *this;
}

YearFromAdam& YearFromAdam::operator++()
{
	YearFromAdam temp(++(this->indict), ++(this->sun), ++(this->moon));
	*this = temp;
	return *this;
}

YearFromAdam YearFromAdam::operator++(int)
{
	YearFromAdam cp(*this);
	++(this->indict);
	++(this->sun);
	++(this->moon);

	return cp;
}

YearFromAdam YearFromAdam::operator--(int)
{
	YearFromAdam cp(*this);
	--(this->indict);
	--(this->sun);
	--(this->moon);

	return cp;
}

YearFromAdam& YearFromAdam::operator= (const YearFromAdam& right)
{
	this->indict = right.indict;
	this->sun = right.sun;
	this->moon = right.moon;
	return (*this);
}

YearFromAdam YearFromAdam::operator+(const YearFromAdam& right) const
{
	//int ThisAdamYear = ComputeAdamYear(this->indict, this->sun, this->moon);
	//int RightAdamYear = ComputeAdamYear(right.indict, right.sun, right.moon);
	int YearSum = ComputeAdamYear(this->indict, this->sun, this->moon) +
		          ComputeAdamYear(right.indict, right.sun, right.moon);
	return YearFromAdam(YearSum);
}

YearFromAdam YearFromAdam::operator-(const YearFromAdam& right) const
{
	int YearDif = ComputeAdamYear(this->indict, this->sun, this->moon) -
				  ComputeAdamYear(right.indict, right.sun, right.moon);
	return YearFromAdam(std::abs(YearDif));
}

YearFromAdam& YearFromAdam::operator+=(const YearFromAdam& right)
{
	*this = *this + right;
	return (*this);
}

YearFromAdam& YearFromAdam::operator-=(const YearFromAdam& right)
{
	*this = *this - right;
	return (*this);
}

bool YearFromAdam::operator==(const YearFromAdam& right) const
{
	if (this->indict == right.indict && this->sun == right.sun && this->moon == right.moon)
		return true;

	return false;
}

//Флаги для ввода и вывода
static bool FormatYearAdamOut = false;
static bool FormatYearJesusOut = false;
static bool FormatYearAdamIn  = false;
static bool FormatYearJesusIn  = false;

std::ostream& YearFromAdam::NormalFormatOut(std::ostream& stream) 
{
	FormatYearJesusOut = false;
	FormatYearAdamOut = false;

	return stream;
}

std::ostream& YearFromAdam::YearAdamFormatOut(std::ostream& stream) 
{
	FormatYearJesusOut = true;
	FormatYearAdamOut = false;

	return stream;
}

std::ostream& YearFromAdam::YearJesusFormatOut(std::ostream& stream) 
{
	FormatYearJesusOut = false;
	FormatYearAdamOut = true;

	return stream;
}

std::istream& YearFromAdam::NormalFormatIn(std::istream& stream) 
{
	FormatYearJesusIn = false;
	FormatYearAdamIn = false;

	return stream;
}

std::istream& YearFromAdam::YearAdamFormatIn(std::istream& stream) 
{
	FormatYearJesusIn = false;
	FormatYearAdamIn = true;
	
	return stream;
}

std::istream& YearFromAdam::YearJesusFormatIn(std::istream& stream) 
{
	FormatYearJesusIn = true;
	FormatYearAdamIn = false;

	return stream;
}

std::ostream& operator<<(std::ostream& o, const YearFromAdam& object)
{
	if (FormatYearAdamOut)
		o << "YearFromAdam: " << YearFromAdam::ComputeAdamYear(object.indict, object.sun, object.moon);
	else if (FormatYearJesusOut)
		o << "YearFromJesus: " << YearFromAdam::AdamToJesus(YearFromAdam::ComputeAdamYear(object.indict, object.sun, object.moon));
	else
		o << "Indict: " << object.indict << ", CircleToSun: " << object.sun << ", CircleToMoon: " << object.moon;

	return o;
}

std::istream& operator>>(std::istream& in, YearFromAdam& object)
{
	if (FormatYearAdamIn)
	{
		int y;
		in >> y;
		YearFromAdam temp(y);
		object = temp;
	}
	else if (FormatYearJesusIn)
	{
		int y;
		in >> y;
		YearFromAdam temp(y,false);
		object = temp;
	}
	else {
		int ind, sol, lon;
		in >> ind >> sol >> lon;
		YearFromAdam temp(ind, sol, lon);
		object = temp;
	}

	return in;
}

int YearFromAdam::ComputeAdamYear(int ind, int sol, int lon)
{
	int a = (ind % 15 >= 0) ? (ind % 15) : (ind % 15 + 15);
	int b = (sol % 28 >= 0) ? (sol % 28) : (sol % 28 + 28);
	int c = (lon % 19 >= 0) ? (lon % 19) : (lon % 19 + 19);

	int ans = 940576 * a - 944775 * b + 4200 * c;

	return (ans > 0) ? (ans % 7980) : (ans % 7980 + 7980);
}

int YearFromAdam::AdamToJesus(int YearInAdam)
{
	return (YearInAdam >= 0) ? (YearInAdam - 5508) : (-YearInAdam);
}

int YearFromAdam::JesusToAdam(int YearInJesus)
{
	return (YearInJesus + 5508 >= 0) ? (YearInJesus + 5508) : 0;
}

int YearFromAdam::GetIndict() const
{
	return this->indict;
}

int YearFromAdam::GetSun() const
{
	return this->sun;
}

int YearFromAdam::GetMoon() const
{
	return this->moon;
}

void YearFromAdam::SetIndict(int ind)
{
	this->indict = (ind % 15 == 0) ? 15 : (ind % 15);
	if (this->indict < 0) this->indict += 15;
}

void YearFromAdam::SetSun(int sol)
{
	this->sun = (sol % 28 == 0) ? 28 : (sol % 28);
	if (this->sun < 0) this->sun += 28;
}

void YearFromAdam::SetMoon(int lon)
{
	this->moon = (lon % 19 == 0) ? 19 : (lon % 19);
	if (this->moon < 0) this->moon += 19;
}

YearFromAdam::operator int()
{
	return YearFromAdam::ComputeAdamYear(this->indict, this->sun, this->moon);
}