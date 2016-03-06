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

Time::Time(int aHour, int aMinute, int aSecond) //contrcut with specified values
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
	
	

int Time::getHour() const
{
	return hour;
}
int Time::getMinute() const
{
	return minute;
}
int Time::getSecond() const
{
	return second;
}

void Time::setHour(int h)
{
	hour = h;
}
void Time::setMinute(int m)
{
	minute = m;
}
void Time::setSecond(int s)
{
	second = s;
}

void Time::print() const
{
	std::cout << hour <<":"<< minute <<":"<< second << std::endl;
}
void Time::printAmPm() const
{
	int fake_hour;
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