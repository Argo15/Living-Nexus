#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <time.h>
#include <string>
#include "GameTime.h"

class TimeManager 
{
private:
	GameTime m_gameTime;
	int m_nTimestamp;

public:
	TimeManager();

	std::string toString();
	void tick();
	GameTime getGameTime();
	int getTimeStamp();
	int getTimeInMilliseconds();
	int getTimeInMicroseconds();
};

extern TimeManager *gTimeManager;

#endif