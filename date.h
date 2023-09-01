#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <ostream>
class Date
{
private:
	int m_day;
	int m_month;
	int m_year;
public:
	// default constructor
	Date();
	// constructor
	Date(int day, int month, int year);
	~Date();
	Date operator+(const Date &date);
	void copyFrom(const Date &b);
	friend std::ostream& operator<<(std::ostream &out, const Date& date);
};




#endif