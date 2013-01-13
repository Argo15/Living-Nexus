#include "LoggerHelper.h"
#include "TimeManager.h"
#include <direct.h>

LoggerHelper::LoggerHelper(std::string sFileName, std::string sLoggingType) 
{
	m_sFileName = std::string(sFileName);
	m_sLoggingType = std::string(sLoggingType);
	year = 0;
}

std::string LoggerHelper::getLogDir() 
{
	char cPath[100];
	sprintf(cPath, "Logs/%i/", year);
	_mkdir(cPath);
	sprintf(cPath, "Logs/%i/%i/", year, month);
	_mkdir(cPath);
	sprintf(cPath, "Logs/%i/%i/%i/", year, month, day);
	_mkdir(cPath);
	return std::string(cPath);
}

void LoggerHelper::commonLogError(std::string sMessage, std::string sMessageType) 
{
	if (year == 0) 
	{
		year = TimeManager::getInstance()->getGameTime().getYear();
		month = TimeManager::getInstance()->getGameTime().getMonth();
		day = TimeManager::getInstance()->getGameTime().getDay();\
	}
	int timestamp = TimeManager::getInstance()->getTimeStamp();
	std::string sPath = getLogDir();
	char cFileName[200];
	sprintf(cFileName, "%s%s_%i.log", sPath.c_str(), m_sFileName.c_str(), timestamp);
	std::ofstream logfile;
	logfile.open(cFileName, std::ios::out | std::ios::app);
	if (logfile.is_open())
	{
		char cMessage[500];
		sprintf(cMessage, "%s [%s] [%s]: %s\n", TimeManager::getInstance()->toString().c_str(), m_sLoggingType.c_str(), sMessageType.c_str(), sMessage.c_str());
		logfile.seekp(0, std::ios::end);
		logfile << cMessage;
		logfile.close();
	}
}

void LoggerHelper::info(std::string sMessage) 
{
	commonLogError(sMessage, "INFO");
}

void LoggerHelper::warn(std::string sMessage) 
{
	commonLogError(sMessage, "WARNING");
}

void LoggerHelper::error(std::string sMessage) 
{
	commonLogError(sMessage, "ERROR");
}