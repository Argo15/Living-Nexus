#ifndef LOGGERHELPER_H
#define LOGGERHELPER_H

#include <string>
#include <fstream>

class LoggerHelper {
private:
	std::string m_sFileName;
	std::string m_sLoggingType;
	int year;
	int month;
	int day;

	std::string getLogDir();
	void commonLogError(std::string sMessage, std::string sMessageType);

public:
	LoggerHelper(std::string sFileName, std::string sLoggingType);

	void info(std::string sMessage);
	void warn(std::string sMessage);
	void error(std::string sMessage);
};

#endif