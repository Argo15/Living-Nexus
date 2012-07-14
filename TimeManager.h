#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <time.h>
#include <string>
#include "GameTime.h"

class TimeManager 
{
private:
	static TimeManager *m_pInstance;
	GameTime gameTime;
	int timestamp;

	TimeManager();

public:
	static TimeManager *getInstance();
	std::string toString();
	void tick();
	GameTime getGameTime();
	int getTimeStamp() {return timestamp;}
};

#endif