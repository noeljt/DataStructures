//File: time.cpp
//Purpose: time class implementation

#include <iostream>
#include "time.h"
#include <iomanip>

Time::Time() //default constructor
{
	hour = 0;
	minute = 0;
	second = 0;
}

Time::Time(uintptr_t aHour, uintptr_t aMinute, uintptr_t aSecond) //contrcut with specified values
{
	hour = aHour;
	minute = aMinute;
	second = aSecond;

	if ((second/60.0)>=1)
	{
		minute += second/60;
		second = second%60;
	}
	if ((minute/60.0)>=1)
	{
		hour += minute/60;
		minute = minute%60;
	}
	if (hour/24.0>=1)
	{
		hour = hour%24;
	}
}
	
	

uintptr_t Time::getHour() const
{
	return hour;
}
uintptr_t Time::getMinute() const
{
	return minute;
}
uintptr_t Time::getSecond() const
{
	return second;
}

void Time::setHour(uintptr_t h)
{
	hour = h;
}
void Time::setMinute(uintptr_t m)
{
	minute = m;
}
void Time::setSecond(uintptr_t s)
{
	second = s;
}

void Time::print() const
{
	std::cout << hour <<":"<< minute <<":"<< second << std::endl;
}
void Time::printAmPm() const
{
	uintptr_t fake_hour;
	if (hour>=12)
	{
		if (hour>=13)
		{
			fake_hour = hour%12;
		}
		else
		{
			fake_hour = hour;
		}
		std::cout << fake_hour << ":"
				  << std::setfill('0') << std::setw(2) << minute << ":"
				  << std::setfill('0') << std::setw(2) << second <<  " pm" << '\n';
	}
	else
	{
		if (hour<1)
		{
			fake_hour = 12;
		}
		else
		{
			fake_hour = hour;
		}
		std::cout << fake_hour << ":"
				  << std::setfill('0') << std::setw(2) << minute << ":"
				  << std::setfill('0') << std::setw(2) << second <<  " am" << '\n';
	}
}

bool isEarlierThan(const Time & time1, const Time & time2)
{
	if (time1.getHour()<time2.getHour())
	{
		return true;
	}
	else if (time1.getHour()>time2.getHour())
	{
		return false;
	}
	else
	{
		if (time1.getMinute()<time2.getMinute())
		{
			return true;
		}
		if (time1.getMinute()>time2.getMinute())
		{
			return false;
		}
		else
		{
			if (time1.getSecond()<time2.getSecond())
			{
				return true;
			}
			if (time1.getSecond()>time2.getSecond())
			{
				return false;
			}
			else
			{
				return false;
			}
		}
	}
}