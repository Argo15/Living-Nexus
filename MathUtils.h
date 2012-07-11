#ifndef MATHUTILS_H
#define MATHUTILS_H

namespace MathUtils 
{
	static float clamp(float x, float a, float b)
	{
		return x < a ? a : (x > b ? b : x);
	}
}

#endif