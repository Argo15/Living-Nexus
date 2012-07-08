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

class Config {
private:
	static Config *m_pInstance;
	boost::unordered_map<std::string, std::string> hmConfigFields;

	Config();

public:
	static Config *getInstance();
	void initializeConfig();
	std::string getFieldString(std::string field);
	int getFieldInt(std::string field);
	void setField(std::string key, std::string value);
	std::string toString();
};

#endif