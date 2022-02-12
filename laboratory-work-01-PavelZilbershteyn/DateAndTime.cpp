#include "DateAndTime.h"

#include <ctime>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <map>


static
std::vector<std::uint64_t> DayInMonths{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
static
std::vector<std::uint64_t> DayInMonthsLeap{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

static
std::map<std::string, std::size_t> MonthNumber{ {"Jan",1}, {"Feb",2}, {"Mar",3}, {"Apr",4}, {"May",5}, {"Jun",6},
												{"Jul",7}, {"Aug",8}, {"Sep",9}, {"Oct",10},{"Nov",11}, {"Dec",12} };

static
bool IsLeap(std::uint64_t year)
{
	return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) ? true : false;
}

DateAndTime::DateAndTime(std::uint64_t s, bool flag)
{
	std::uint64_t s1 = s;
	if (flag)
		s1 = (s / 10000000 - 11644473600);

	UnixSec = s1;
	FileTime = (UnixSec + 11644473600) * 10000000;
	std::time_t res = s1;
	char* str = std::ctime(&res);

	std::string temp;
	temp.push_back(str[4]); temp.push_back(str[5]); temp.push_back(str[6]);

	this->month = MonthNumber[temp];
	temp.clear();

	temp.push_back(str[8]); temp.push_back(str[9]);
	this->day = std::stoi(temp);
	temp.clear();

	temp.push_back(str[11]); temp.push_back(str[12]);
	this->hour = std::stoi(temp);
	temp.clear();

	temp.push_back(str[14]); temp.push_back(str[15]);
	this->minute = std::stoi(temp);
	temp.clear();

	temp.push_back(str[17]); temp.push_back(str[18]);
	this->second = std::stoi(temp);
	temp.clear();

	temp.push_back(str[20]); temp.push_back(str[21]); temp.push_back(str[22]); temp.push_back(str[23]);
	this->year = std::stoi(temp);
	temp.clear();
}

DateAndTime::DateAndTime(const DateAndTime& obj)
	:year{ obj.year }, month{ obj.month }, day{ obj.day },
	hour{ obj.hour }, minute{ obj.minute }, second{ obj.second },
	UnixSec{ obj.UnixSec }, FileTime{ obj.FileTime }
{}

DateAndTime DateAndTime::operator+ (const DateAndTime& right) const
{
	return DateAndTime(this->UnixSec + right.UnixSec);
}

DateAndTime DateAndTime::operator+ (int right) const
{
	return DateAndTime(this->UnixSec + right);
}

DateAndTime operator+ (int left, const DateAndTime& right)
{
	return right + left;
}

std::int64_t DateAndTime::operator- (const DateAndTime& right) const
{
	return (this->UnixSec - right.UnixSec);
}

std::ostream& operator<< (std::ostream& o, const DateAndTime& obj)
{
	// Вывод в формате hh:mi:ss dd.mm.year

	std::string hh("0"), mi("0"), ss("0"), dd("0"), mm("0"), yyyy(std::to_string(obj.year));
	if (obj.hour < 10) { hh += std::to_string(obj.hour); }
	else { hh = std::to_string(obj.hour); }

	if (obj.minute < 10) { mi += std::to_string(obj.minute); }
	else { mi = std::to_string(obj.minute); }

	if (obj.second < 10) { ss += std::to_string(obj.second); }
	else { ss = std::to_string(obj.second); }

	if (obj.day < 10) { dd += std::to_string(obj.day); }
	else { dd = std::to_string(obj.day); }

	if (obj.month < 10) { mm += std::to_string(obj.month); }
	else { mm = std::to_string(obj.month); }

	o << hh << ':' << mi << ':' << ss << ' ' << dd << '.' << mm << '.' << yyyy;

	return o;
}

std::istream& operator>> (std::istream& i, DateAndTime& obj)
{
	i >> obj.UnixSec;
	obj.FileTime = (obj.UnixSec + 11644473600) * 10000000;
	std::time_t res = obj.UnixSec;
	char* str = std::ctime(&res);

	std::string temp;
	temp.push_back(str[4]); temp.push_back(str[5]); temp.push_back(str[6]);

	obj.month = MonthNumber[temp];
	temp.clear();

	temp.push_back(str[8]); temp.push_back(str[9]);
	obj.day = std::stoi(temp);
	temp.clear();

	temp.push_back(str[11]); temp.push_back(str[12]);
	obj.hour = std::stoi(temp);
	temp.clear();

	temp.push_back(str[14]); temp.push_back(str[15]);
	obj.minute = std::stoi(temp);
	temp.clear();

	temp.push_back(str[17]); temp.push_back(str[18]);
	obj.second = std::stoi(temp);
	temp.clear();

	temp.push_back(str[20]); temp.push_back(str[21]); temp.push_back(str[22]); temp.push_back(str[23]);
	obj.year = std::stoi(temp);
	temp.clear();

	return i;
}

DateAndTime& DateAndTime::operator=(const DateAndTime& other)
{
	this->day = other.day;
	this->year = other.year;
	this->month = other.month;
	this->second = other.second;
	this->minute = other.minute;
	this->hour = other.hour;
	this->UnixSec = other.UnixSec;
	this->FileTime = other.FileTime;

	return (*this);
}
DateAndTime& DateAndTime::operator=(std::uint64_t num)
{
	this->UnixSec = num;
	this->FileTime = (this->UnixSec + 11644473600) * 10000000;

	std::time_t res = this->UnixSec;
	char* str = std::ctime(&res);

	std::string temp;
	temp.push_back(str[4]); temp.push_back(str[5]); temp.push_back(str[6]);

	this->month = MonthNumber[temp];
	temp.clear();

	temp.push_back(str[8]); temp.push_back(str[9]);
	this->day = std::stoi(temp);
	temp.clear();

	temp.push_back(str[11]); temp.push_back(str[12]);
	this->hour = std::stoi(temp);
	temp.clear();

	temp.push_back(str[14]); temp.push_back(str[15]);
	this->minute = std::stoi(temp);
	temp.clear();

	temp.push_back(str[17]); temp.push_back(str[18]);
	this->second = std::stoi(temp);
	temp.clear();

	temp.push_back(str[20]); temp.push_back(str[21]); temp.push_back(str[22]); temp.push_back(str[23]);
	this->year = std::stoi(temp);
	temp.clear();

	return (*this);
}

DateAndTime::operator std::uint64_t() { return UnixSec; }

std::uint64_t DateAndTime::ToFileTime() const
{
	return this->FileTime;
}

std::uint64_t DateAndTime::UnixToFile(std::uint64_t Unix)
{
	return ((Unix + 11644473600) * 10000000);
}

std::uint64_t DateAndTime::duration(const DateAndTime& right) const
{
	return std::llabs(*this - right);
}

std::uint64_t DateAndTime::FileToUnix(std::uint64_t File)
{
	return (File / 10000000 - 11644473600);
}

void DateAndTime::SetYear(std::uint64_t y)
{
	if (y > 0)
	{
		std::size_t sum{ 0 };
		for (std::size_t i = std::min(this->year, y); i < std::max(this->year, y); ++i)
		{
			if (IsLeap(y)) sum += 366;
			else sum += 365;
		}
		if (y < this->year) this->UnixSec -= sum * 24ull * 3600ull;
		else this->UnixSec += sum * 24ull * 3600ull;

		this->FileTime = (this->UnixSec + 11644473600) * 10000000;

		this->year = y;
	}
}
void DateAndTime::SetMonth(std::uint64_t m)
{
	if (m > 0 && m <= 12)
		if ((!IsLeap(this->year) && this->day <= DayInMonths[m - 1]) || (IsLeap(this->year) && this->day <= DayInMonthsLeap[m - 1]))
		{
			std::size_t sum{ 0 };
			for (std::uint64_t i{ std::min(this->month,m) }; i < std::max(this->month, m); ++i)
			{
				if (IsLeap(this->year)) sum += DayInMonthsLeap[i - 1];
				else sum += DayInMonths[i - 1];
			}
			//сейчас в sum хранится количество дней
			if (m < this->month) this->UnixSec -= sum * 24ull * 3600ull;
			else this->UnixSec += sum * 24ull * 3600ull;

			this->FileTime = (this->UnixSec + 11644473600) * 10000000;

			this->month = m;
		}
}
void DateAndTime::SetDay(std::uint64_t d)
{
	if (d > 0)
		if ((IsLeap(this->year) && d <= DayInMonthsLeap[this->month - 1]) || (!IsLeap(this->year) && d <= DayInMonths[this->month - 1]))
		{
			std::uint64_t diff = d - this->day;
			this->day = d;
			this->UnixSec += 24 * 3600 * diff;
			this->FileTime = (this->UnixSec + 11644473600) * 10000000;
		}
}
void DateAndTime::SetHour(std::uint64_t h)
{
	if (h <= 23)
	{
		std::uint64_t diff = h - this->hour;
		this->hour = h;
		this->UnixSec += 3600 * diff;
		this->FileTime = (this->UnixSec + 11644473600) * 10000000;
	}
}
void DateAndTime::SetMinute(std::uint64_t min)
{
	if (min <= 59)
	{
		std::uint64_t diff = min - this->minute;
		this->minute = min;
		this->UnixSec += 60 * diff;
		this->FileTime = (this->UnixSec + 11644473600) * 10000000;
	}
}
void DateAndTime::SetSecond(std::uint64_t s)
{
	if (s <= 59)
	{
		std::uint64_t diff = s - this->second;
		this->second = s;
		this->UnixSec += diff;
		this->FileTime = (this->UnixSec + 11644473600) * 10000000;
	}
}

std::uint64_t DateAndTime::GetYear() const
{
	return this->year;
}
std::uint64_t DateAndTime::GetMonth() const
{
	return this->month;
}
std::uint64_t DateAndTime::GetDay() const
{
	return this->day;
}
std::uint64_t DateAndTime::GetHour() const
{
	return this->hour;
}
std::uint64_t DateAndTime::GetMinute() const
{
	return this->minute;
}
std::uint64_t DateAndTime::GetSecond() const
{
	return this->second;
}