//File: main.cpp
//Purpose: Lab 2 - use classes

#include <iostream>
#include "time.h"
#include <vector>
#include <algorithm>

int main()
{
	//Check 1
	std::cout << "Check 1" << '\n';
	Time t1(5,30,59);
	Time t2;
	t1.print();
	t2.print();

	//Check 2
	std::cout << "Check 2" << '\n';
	t1.setHour(3);
	t1.setMinute(2);
	t1.setSecond(1);
	t1.print();
	t1.printAmPm();
	t2.setHour(23);
	t2.setMinute(59);
	t2.setSecond(10);
	t2.print();
	t2.printAmPm();

	//Check 3
	std::cout << "Check 3" << std::endl;
	std::vector<Time> times;
	Time t3(1,2,3);
	Time t4(45,67,18);
	times.push_back(t1);
	times.push_back(t2);
	times.push_back(t3);
	times.push_back(t4);
	sort(times.begin(), times.end(), isEarlierThan);
	for (unsigned int i=0;i<times.size();i++)
	{
		times[i].printAmPm();
	}

	//edge cases
	std::cout << "Edge Cases" << '\n';
	Time t5(0,0,0);
	Time t6(12,0,0);
	t5.printAmPm();
	t6.printAmPm();
	return 0;
}