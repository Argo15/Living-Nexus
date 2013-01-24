#include "Profiler.h"
#include "TimeManager.h"
#include "Logger.h"
#include "StringUtils.h"

Profiler* Profiler::m_pInstance = 0;
typedef boost::unordered_map<std::string, int>::value_type int_value;

Profiler::Profiler()
{
	m_sLastSection = "";
}

Profiler *Profiler::getInstance() 
{
	if (m_pInstance == 0) 
	{
		m_pInstance = new Profiler();
	}
	return m_pInstance;
}

void Profiler::startProfile(std::string sSection) 
{
	int currentTime = TimeManager::getInstance()->getTimeInMicroseconds();
	if (m_hmSectionCounts.find(sSection) == m_hmSectionCounts.end()) 
	{
		m_hmSectionCounts[sSection] = 0;
		m_hmSectionAverages[sSection] = 0;
		m_hmSectionMinimum[sSection] = 100000;
		m_hmSectionMaximum[sSection] = -100;
	}
	m_hmSectionLastTimes[sSection] = currentTime;
	m_sLastSection = sSection;
}

void Profiler::endProfile() 
{
	if (m_sLastSection != "") 
	{
		int currentTime = TimeManager::getInstance()->getTimeInMicroseconds();
		int changeInTime = currentTime - m_hmSectionLastTimes[m_sLastSection];
		if (changeInTime > 0) 
		{
			m_hmSectionCounts[m_sLastSection] = m_hmSectionCounts[m_sLastSection] + 1;
			m_hmSectionAverages[m_sLastSection] = (float)(changeInTime + (m_hmSectionCounts[m_sLastSection]-1) * m_hmSectionAverages[m_sLastSection] ) / (float)m_hmSectionCounts[m_sLastSection];
			if (changeInTime < m_hmSectionMinimum[m_sLastSection]) 
			{
				m_hmSectionMinimum[m_sLastSection] = changeInTime;
			}
			if (changeInTime > m_hmSectionMaximum[m_sLastSection]) 
			{
				m_hmSectionMaximum[m_sLastSection] = changeInTime;
			}
		}
	}
	m_sLastSection = "";
}

void Profiler::logProfile() 
{
	BOOST_FOREACH(int_value section, m_hmSectionAverages) 
	{
		Logging::PROFILER->info(section.first + " avg: " + StringUtils::valueOf(m_hmSectionAverages[section.first]));
		Logging::PROFILER->info(section.first + " min: " + StringUtils::valueOf(m_hmSectionMinimum[section.first]));
		Logging::PROFILER->info(section.first + " max: " + StringUtils::valueOf(m_hmSectionMaximum[section.first]));
	}
}