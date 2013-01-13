#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include "Texture.h"
#include <math.h>
#include <time.h>
#include <GL/glu.h>
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/GLee.h>

class PerlinNoise : public Texture
{
private:
	float map32[32 * 32];
	float map256[256 * 256];

	float Noise(int x, int y, int random);
	void SetNoise(float  *map);
	float Interpolate(float x, float y, float  *map);
	void OverlapOctaves(float  *map32, float  *map256);
	void ExpFilter(float  *map);

public:
	bool load(const char *name);
};

#endif