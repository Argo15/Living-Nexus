#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <boost/unordered_map.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/foreach.hpp>

class Config 
{
private:
	boost::unordered_map<std::string, std::string> m_hmConfigFields;

public:
	Config();

	void initializeConfig();
	std::string getFieldString(std::string sField);
	int getFieldInt(std::string sField);
	void setField(std::string sKey, std::string sValue);
	std::string toString();
};

extern Config *gConfig;

#endif