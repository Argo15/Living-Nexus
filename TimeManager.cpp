#include "TimeManager.h"

TimeManager localTimeManager;
TimeManager *gTimeManager = &localTimeManager;

TimeManager::TimeManager() 
{
	m_gameTime.updateToSystemTime();
	m_nTimestamp = m_gameTime.getSecondsSinceMidnight();
}

void TimeManager::tick() 
{
	m_gameTime.updateToSystemTime();
}

std::string TimeManager::toString() 
{
	char buff[100];
	sprintf(buff, "%d:%d:%d %d/%d/%d", 
		m_gameTime.getHours(), m_gameTime.getMinutes(), m_gameTime.getSeconds(),
		m_gameTime.getMonth(), m_gameTime.getDay(), m_gameTime.getYear());
	std::string sTime = buff;
	return sTime;
}

GameTime TimeManager::getGameTime() 
{
	return m_gameTime;
}

int TimeManager::getTimeStamp() 
{
	return m_nTimestamp;
}

int TimeManager::getTimeInMilliseconds() 
{
	return boost::posix_time::microsec_clock::local_time().time_of_day().total_milliseconds();
}

int TimeManager::getTimeInMicroseconds() 
{
	return boost::posix_time::microsec_clock::local_time().time_of_day().total_microseconds();
}