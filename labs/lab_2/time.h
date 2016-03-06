//File: time.h
//Purpose: Header file with declaration of the Time class,
//		   including member functions and private member variables.

class Time
{
public:
	Time();
	Time(int aHour, int aMinute, int aSecond);

	// ACCESSORS
	int getHour() const;
	int getMinute() const;
	int getSecond() const;

	// MODIFIERS
	void setHour(int aHour);
	void setMinute(int aMinute);
	void setSecond(int aSecond);

	// other member functions
	void print() const;
	void printAmPm() const;

private:
	int hour;
	int minute;
	int second;
};

// other...
bool isEarlierThan(const Time & time1, const Time & time2);