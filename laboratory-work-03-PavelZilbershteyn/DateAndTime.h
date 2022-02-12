#ifndef DateAndTime_h
#define DateAndTime_h

#include <iostream>
#include "ADT.h"

class DateAndTime : public ADT
{
public:
	
	DateAndTime() = default;
	DateAndTime(std::uint64_t s, bool flag = false);
	DateAndTime(const DateAndTime& obj);
	~DateAndTime() = default;

	DateAndTime operator+ (const DateAndTime& right) const;
	DateAndTime operator+ (int right) const;
	friend DateAndTime operator+ (int left, const DateAndTime& right);
	std::int64_t operator- (const DateAndTime& right) const;
	friend std::ostream& operator<< (std::ostream& o, const DateAndTime& obj); 
	friend std::istream& operator>> (std::istream& i, DateAndTime& obj); 
	DateAndTime& operator=(const DateAndTime& other);
	DateAndTime& operator=(std::uint64_t num);


	void SetYear(std::uint64_t y);
	void SetMonth(std::uint64_t m);
	void SetDay(std::uint64_t d);
	void SetHour(std::uint64_t h);
	void SetMinute(std::uint64_t min);
	void SetSecond(std::uint64_t s);

	std::uint64_t GetYear() const;
	std::uint64_t GetMonth() const;
	std::uint64_t GetDay() const;
	std::uint64_t GetHour() const;
	std::uint64_t GetMinute() const;
	std::uint64_t GetSecond() const;

	operator std::uint64_t(); 
	std::uint64_t ToFileTime() const; 

	
	static std::uint64_t UnixToFile(std::uint64_t Unix);
	static std::uint64_t FileToUnix(std::uint64_t File);

	std::uint64_t duration(const DateAndTime& right) const;

private:
	std::uint64_t year;
	std::uint64_t month;
	std::uint64_t day;
	std::uint64_t hour;
	std::uint64_t minute;
	std::uint64_t second;
	std::uint64_t UnixSec;  
	std::uint64_t FileTime; 
};

#endif