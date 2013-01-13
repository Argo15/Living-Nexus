#include "Config.h"

static std::string S_COMMON_INI_PATH = "Config/common.ini";

typedef boost::unordered_map<std::string, std::string>::value_type string_value;

Config* Config::m_pInstance = 0;

Config::Config() 
{
	initializeConfig();
}

Config *Config::getInstance() 
{
	if (m_pInstance == 0) 
	{
		m_pInstance = new Config();
	}
	return m_pInstance;
}

void Config::initializeConfig() 
{
	std::string line;
	std::ifstream configFile(S_COMMON_INI_PATH.c_str());
	if (configFile.is_open())
	{
		while ( configFile.good() )
		{
			std::getline(configFile,line);
			std::vector<std::string> splitLine;
			boost::algorithm::split(splitLine, line, boost::algorithm::is_any_of("=") );
			if (splitLine.size() == 2)
			{
				setField(splitLine[0], splitLine[1]);
			}
		}
		configFile.close();
	}
}

std::string Config::getFieldString(std::string field) 
{
	return hmConfigFields[field];
}

int Config::getFieldInt(std::string field) 
{
	return atoi(hmConfigFields[field].c_str());
}

void Config::setField(std::string key, std::string value) 
{
	hmConfigFields[key] = value;
}

std::string Config::toString() 
{
	std::string fieldList;
	BOOST_FOREACH(string_value i, hmConfigFields) 
	{
		fieldList = fieldList + i.first + " = " + i.second + "\n";
	}
	return fieldList;
}