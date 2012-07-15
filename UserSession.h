#ifndef USERSESSION_H
#define USERSESSION_H

#include <string>
#include "User.h"


/*
 * author wcrane
 * date 7/14/2012
 * Allows access to the current user, enforces that only one user is active at any given time.
 */
class UserSession {
private:
	static UserSession *m_pInstance;
	User *activeUser;

	UserSession();
public:
	static UserSession *getInstance();
	void startUserSession(std::string name);
	void endUserSession();
	bool isUserInSession();
	User *getActiveUser();
};

#endif