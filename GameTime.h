#ifndef GAMETIME_H
#define GAMETIME_H

#include <time.h>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/time_clock.hpp"

class GameTime
{
private:
	boost::posix_time::ptime datetime;

	int m_nHourOffset;
	float m_nMinuteOffset;

public:
	void updateToSystemTime();
	int getYear() { return datetime.date().year();}
	int getMonth() { return datetime.date().month();}
	int getDay() { return datetime.date().day();}
	int getHours() { return datetime.time_of_day().hours();}
	int getMinutes() { return datetime.time_of_day().minutes();}
	int getSeconds() { return datetime.time_of_day().seconds();}

	GameTime();
};

#endif