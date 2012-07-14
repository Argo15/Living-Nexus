#ifndef PROFILER_H
#define PROFILER_H

#include <string>
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>

class Profiler {
private:
	static Profiler *m_pInstance;
	std::string lastSection;
	boost::unordered_map<std::string, int> hmSectionLastTimes;
	boost::unordered_map<std::string, int> hmSectionAverages;
	boost::unordered_map<std::string, int> hmSectionMinimum;
	boost::unordered_map<std::string, int> hmSectionMaximum;
	boost::unordered_map<std::string, int> hmSectionCounts;

	Profiler();

public:
	static Profiler *getInstance();
	void startProfile(std::string section);
	void endProfile();
	void logProfile();
};

#endif