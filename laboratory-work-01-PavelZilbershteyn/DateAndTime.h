#ifndef DateAndTime_h
#define DateAndTime_h

#include <iostream>

class DateAndTime
{
public:
	// "��� ������� ����������� ����������� ������������, ����������, ����������� �����������"
	DateAndTime() = default;
	//DateAndTime(std::uint64_t s, bool flag = true); // �������������� �� UnixTime � DateAndTime
	DateAndTime(std::uint64_t s, bool flag = false); // �������������� �� FileTime � DateAndTime
	DateAndTime(const DateAndTime& obj);
	~DateAndTime() = default;

	/*
	* ��������� ���������� ����������(operator) ����������� ����������� ���������� ��������,
	* ���������� �������������� �������� ��� ���������
	* � ������������ ������(������, �������������, �������� � � ����������� �� ���� ��������), ������������, ���� � ����� �
	* ����������� ������(��������� ��������� � << � � � >> �),
	*/

	DateAndTime operator+ (const DateAndTime& right) const;
	DateAndTime operator+ (int right) const;
	friend DateAndTime operator+ (int left, const DateAndTime& right);
	std::int64_t operator- (const DateAndTime& right) const;
	friend std::ostream& operator<< (std::ostream& o, const DateAndTime& obj); // ����� � ������� hh:mi:ss dd.mm.yyyy
	friend std::istream& operator>> (std::istream& i, DateAndTime& obj); //���� � ������� UnixTime
	DateAndTime& operator=(const DateAndTime& other);
	DateAndTime& operator=(std::uint64_t num);
	//� ��� DateAndTime + int ?
	//������ ����, int+DateAndTime ����

	//������, �������������� ��������� ��������� ��������� ������ ������� (�������)
	void SetYear(std::uint64_t y);
	void SetMonth(std::uint64_t m);
	void SetDay(std::uint64_t d);
	void SetHour(std::uint64_t h);
	void SetMinute(std::uint64_t min);
	void SetSecond(std::uint64_t s);
	//� ��� "�������" ?
	//������ ����

	std::uint64_t GetYear() const;
	std::uint64_t GetMonth() const;
	std::uint64_t GetDay() const;
	std::uint64_t GetHour() const;
	std::uint64_t GetMinute() const;
	std::uint64_t GetSecond() const;

	/*
	* "���������� �/�� �������� ���� ������"
	*
	* ���������� �� �������� ���� - ����������� DateAndTime(std::uint64_t s), ������� �������� �� UnixTime (std::uint64_t) � DateAndTime
	*							 � ����������� DateAndTime(std::uint64_t s, bool) ������� �������� �� FileTime (std::uint64_t) � DateAndTime
	* ���������� � �������� ���� ��������� � ����� ���������� ��������� ���������� ���� (������ 48) � ��������������� ������ (������ 49)
	*
	*/

	operator std::uint64_t(); // ���������� � UnixTime format
	std::uint64_t ToFileTime() const; // ���������� � FileTime format

	//======

	//����� ��������������� ������ ����������� �� Unix � File � ������� 
	//(����� ������������ ��� �������� ������ �� ������ � �������� ������������, ��� ��� ��� ��� ���������� ������ ��� UnixTime)

	static std::uint64_t UnixToFile(std::uint64_t Unix);
	static std::uint64_t FileToUnix(std::uint64_t File);

	//======

	// �������� �������� �������. ������������ � ��������
	std::uint64_t duration(const DateAndTime& right) const;

private:
	std::uint64_t year;
	std::uint64_t month;
	std::uint64_t day;
	std::uint64_t hour;
	std::uint64_t minute;
	std::uint64_t second;
	std::uint64_t UnixSec;  //�����?
	std::uint64_t FileTime; //--"--?
};

#endif