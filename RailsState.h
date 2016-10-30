#ifndef RAILSSTATE_H
#define RAILSSTATE_H

#include "GameState.h"

class RailsState : public GameState {
private: 

public:
	GameState();
	~GameState() {}

	void resize(int w, int h);
	void tick(int fps);

	bool mouseHidden() {return false;}

};

#endif