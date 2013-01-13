#include "TimeManager.h"

TimeManager* TimeManager::m_pInstance = 0;

TimeManager::TimeManager() 
{
	gameTime.updateToSystemTime();
	timestamp = gameTime.getSecondsSinceMidnight();
}

TimeManager *TimeManager::getInstance() 
{
	if (m_pInstance == 0) 
	{
		m_pInstance = new TimeManager();
	}
	return m_pInstance;
}

void TimeManager::tick() 
{
	gameTime.updateToSystemTime();
}

std::string TimeManager::toString() 
{
	char buff[100];
	sprintf(buff, "%d:%d:%d %d/%d/%d", 
		gameTime.getHours(), gameTime.getMinutes(), gameTime.getSeconds(),
		gameTime.getMonth(), gameTime.getDay(), gameTime.getYear());
	std::string sTime = buff;
	return sTime;
}

GameTime TimeManager::getGameTime() 
{
	return gameTime;
}