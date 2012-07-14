#include "GameTime.h"
#include "Root.h"

GameTime::GameTime() {
	m_nHourOffset = 0;
	m_nMinuteOffset = 0;
}

void GameTime::updateToSystemTime() {
	time_t t = time(0);
	struct tm * now = localtime( & t );
    if (Root::inputManager->isKeyDownOnce('-')) {
		m_nHourOffset -= 1;
	}
	if (Root::inputManager->isKeyDownOnce('=')) {
		m_nHourOffset += 1;
	}
	if (Root::inputManager->isKeyDown('[')) {
		m_nMinuteOffset -= 1.0;
	}
	if (Root::inputManager->isKeyDown(']')) {
		m_nMinuteOffset += 1.0;
	}

	datetime = boost::posix_time::second_clock::local_time() + boost::posix_time::hours(m_nHourOffset) + boost::posix_time::minutes(m_nMinuteOffset);
}