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

	//������
	bool operator>  (const BigNumber& right) const;
	bool operator<  (const BigNumber& right) const;
	bool operator== (const BigNumber& right) const;
	bool operator!= (const BigNumber& right) const;
	bool operator>= (const BigNumber& right) const;
	bool operator<= (const BigNumber& right) const;

	//����������
	BigNumber  operator+ (const BigNumber& right) const;
	BigNumber  operator- (const BigNumber& right) const;
	BigNumber  operator* (const BigNumber& right) const;
	BigNumber  operator/ (const BigNumber& right) const; // ������� ������
	BigNumber  operator% (const BigNumber& right) const; // ������� �� �������, �������, ���, ���������� �� ������ �����, ������� ���������
														 // ��� ������������� ����� �� ������� ������ ����� (-13%5=3)
	BigNumber& operator+=(const BigNumber& right);
	BigNumber& operator-=(const BigNumber& right);
	BigNumber& operator*=(const BigNumber& right);
	BigNumber& operator/=(const BigNumber& right);
	BigNumber& operator%=(const BigNumber& right);
	BigNumber& operator= (const BigNumber& right);
	BigNumber& operator= (std::string NewNum);

	BigNumber power(const BigNumber& exp) const; //���������� � ������� (���� ���������� <0, �� a^(-b) = 1/a^(-b) = 0, ��� ��� ����� �����)

	BigNumber& operator--(); //���������� ���������
	BigNumber& operator++(); //���������� ���������
	BigNumber operator++(int); // ����������� ���������
	BigNumber operator--(int); // ����������� ���������

	friend std::ostream& operator<< (std::ostream& out, const BigNumber& right);
	friend std::istream& operator>> (std::istream& i, BigNumber& right);
	friend BigNumber operator- (const BigNumber& right); //������� �����

	operator std::string();

	//�������
	void SetNumber(std::string s); //������� ����� ������ ������� ���� number, � �� ������� ����� ����� ���� BigNumber
	void SetSign(char ch); //��������� ����� � ������� �������� '+' � '-'

	//�������
	std::string GetNumber() const; //��������� ���� number, � �� ����� ����� ���� BigNumber
	char GetSign() const; //��������� ����� ����� � ���� ������� '+' ��� '-'

	bool isEven() const; //�������� �������� �����
private:
	void DeleteZeros();
	std::size_t length() const;

	std::string number; //������ �����
	bool sign = 0; // 0 - positive, 1 - negative
};

#endif