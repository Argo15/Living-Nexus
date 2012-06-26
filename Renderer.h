#ifndef RENDERER_H
#define RENDERER_H

class Renderer {
public:
	virtual void init() = 0;
	virtual void resize(int w, int h) = 0;
	virtual void render() = 0;
};

#endif