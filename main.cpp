#include <iostream>
#include "date.h"
int main(void)
{
	Date date1(1, 2, 3), date2(4, 5, 6);
	std::cout << date1 + date2 << std::endl;
}