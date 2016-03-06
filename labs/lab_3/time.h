//File: time.h
//Purpose: Header file with declaration of the Time class,
//		   including member functions and private member variables.

class Time
{
public:
	Time();
	Time(uintptr_t aHour, uintptr_t aMinute, uintptr_t aSecond);

	// ACCESSORS
	uintptr_t getHour() const;
	uintptr_t getMinute() const;
	uintptr_t getSecond() const;

	// MODIFIERS
	void setHour(uintptr_t aHour);
	void setMinute(uintptr_t aMinute);
	void setSecond(uintptr_t aSecond);

	// other member functions
	void print() const;
	void printAmPm() const;

private:
	uintptr_t hour;
	uintptr_t minute;
	uintptr_t second;
};

// other...
bool isEarlierThan(const Time & time1, const Time & time2);