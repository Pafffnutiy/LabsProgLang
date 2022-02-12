#ifndef YearFromAdam_H
#define YearFromAdam_H

#include "ADT.h"

#include <iostream>

class YearFromAdam : public ADT
{
private:
	void ForConstrWithParam(int year); 

	static bool FormatYearAdamOut;
	static bool FormatYearJesusOut;
	static bool FormatYearAdamIn;
	static bool FormatYearJesusIn;

	int indict;
	int sun;
	int moon;
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

	static std::ostream& NormalFormatOut(std::ostream& stream);     
	static std::ostream& YearAdamFormatOut(std::ostream& stream);   
	static std::ostream& YearJesusFormatOut(std::ostream& stream);  
	static std::istream& NormalFormatIn(std::istream& stream);		
	static std::istream& YearAdamFormatIn(std::istream& stream);	
	static std::istream& YearJesusFormatIn(std::istream& stream);	

	friend std::ostream& operator<< (std::ostream& o, const YearFromAdam& object); 
	friend std::istream& operator>> (std::istream& in, YearFromAdam& object); 

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

	operator int(); 
};

#endif //YearFromAdam

