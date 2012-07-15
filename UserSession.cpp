#include "UserSession.h"
#include "Logger.h"

UserSession* UserSession::m_pInstance = 0;

UserSession::UserSession() {
	activeUser = 0;
}

UserSession *UserSession::getInstance() {
	if (m_pInstance == 0) {
		m_pInstance = new UserSession();
	}
	return m_pInstance;
}

void UserSession::startUserSession(std::string name) {
	Logging::GAME->info("Starting user session: " + name);
	activeUser = new User(name);
}

void UserSession::endUserSession() {
	Logging::GAME->info("Ending user session: " + activeUser->getName());
	delete activeUser;
	activeUser = 0;
}

bool UserSession::isUserInSession() {
	return (activeUser != 0);
}

User *UserSession::getActiveUser() {
	return activeUser;
}