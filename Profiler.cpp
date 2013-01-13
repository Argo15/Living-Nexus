#include "Profiler.h"
#include "TimeManager.h"
#include "Logger.h"
#include "StringUtils.h"

Profiler* Profiler::m_pInstance = 0;
typedef boost::unordered_map<std::string, int>::value_type int_value;

Profiler::Profiler()
{
	lastSection = "";
}

Profiler *Profiler::getInstance() 
{
	if (m_pInstance == 0) 
	{
		m_pInstance = new Profiler();
	}
	return m_pInstance;
}

void Profiler::startProfile(std::string section) 
{
	int currentTime = TimeManager::getInstance()->getTimeInMicroseconds();
	if (hmSectionCounts.find(section) == hmSectionCounts.end()) 
	{
		hmSectionCounts[section] = 0;
		hmSectionAverages[section] = 0;
		hmSectionMinimum[section] = 100000;
		hmSectionMaximum[section] = -100;
	}
	hmSectionLastTimes[section] = currentTime;
	lastSection = section;
}

void Profiler::endProfile() 
{
	if (lastSection != "") 
	{
		int currentTime = TimeManager::getInstance()->getTimeInMicroseconds();
		int changeInTime = currentTime - hmSectionLastTimes[lastSection];
		if (changeInTime > 0) 
		{
			hmSectionCounts[lastSection] = hmSectionCounts[lastSection] + 1;
			hmSectionAverages[lastSection] = (float)(changeInTime + (hmSectionCounts[lastSection]-1) * hmSectionAverages[lastSection] ) / (float)hmSectionCounts[lastSection];
			if (changeInTime < hmSectionMinimum[lastSection]) 
			{
				hmSectionMinimum[lastSection] = changeInTime;
			}
			if (changeInTime > hmSectionMaximum[lastSection]) 
			{
				hmSectionMaximum[lastSection] = changeInTime;
			}
		}
	}
	lastSection = "";
}

void Profiler::logProfile() 
{
	BOOST_FOREACH(int_value section, hmSectionAverages) 
	{
		Logging::PROFILER->info(section.first + " avg: " + StringUtils::valueOf(hmSectionAverages[section.first]));
		Logging::PROFILER->info(section.first + " min: " + StringUtils::valueOf(hmSectionMinimum[section.first]));
		Logging::PROFILER->info(section.first + " max: " + StringUtils::valueOf(hmSectionMaximum[section.first]));
	}
}