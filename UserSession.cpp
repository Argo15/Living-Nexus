#include "UserSession.h"
#include "Logger.h"

UserSession localUserSession;
UserSession *gUserSession = &localUserSession;

UserSession::UserSession() 
{
	m_activeUser = 0;
}

void UserSession::startUserSession(std::string sName) 
{
	Logging::GAME->info("Starting user session: " + sName);
	m_activeUser = new User(sName);
}

void UserSession::endUserSession() 
{
	Logging::GAME->info("Ending user session: " + m_activeUser->getName());
	delete m_activeUser;
	m_activeUser = 0;
}

bool UserSession::isUserInSession() 
{
	return (m_activeUser != 0);
}

User *UserSession::getActiveUser() 
{
	return m_activeUser;
}