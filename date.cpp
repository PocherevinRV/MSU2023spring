#include "date.h" 
Date::Date() : Date::Date(1, 1, 1){}
Date::Date(int day = 1, int month = 1, int year = 1) : 
	m_day{day},
	m_month{month},
	m_year{year}
{
	std::cout << "Constructor" << std::endl;
}
Date::~Date() {std::cout << "Destructor" << std::endl;}
Date Date::operator+(const Date &date)
{
	return Date(this->m_day + date.m_day, this->m_month + date.m_month, this->m_year + date.m_year);
}
std::ostream& operator<<(std::ostream &out, const Date& date)
{
	out << "(day = " << date.m_day << ", month = " << date.m_month << ", year = " << date.m_year << ")";
	return out;
}
void Date::copyFrom(const Date &b)
{
	m_day = b.m_day;
	m_month = b.m_month;
	m_year = b.m_year;
}