#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState {
public:
	static GameState *GAMESTATE;

public:
	GameState() {}
	~GameState() {}

	virtual void resize(int w, int h) = 0;
	virtual void tick(int fps) = 0;

	virtual bool mouseHidden() = 0;
};

#endif