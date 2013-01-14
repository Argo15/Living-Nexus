#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "Camera.h"
#include "View.h"
#include "Matrix.h"

#define F_NEAR	0
#define F_FAR	1
#define F_LEFT	2
#define F_RIGHT	3
#define F_UP	4
#define F_DOWN	5

struct FrustumPlane
{
	Vector3 point;
	Vector3 normal;
	float d;

	float distance(Vector3 *p)
	{
		return (*p).dot(normal)-d;
	}
};

class Frustum
{
private:
	FrustumPlane plane[6];
	float Hnear;
	float Wnear;
	float Hfar;
	float Wfar;
	Vector3 ftl,ftr,fbl,fbr;

public:
	Frustum();

	void getFrustum(Camera *camera, View *view);
	void getOrthoFrustum(Camera *camera, View *view);
	void calcFarPlane(Camera *camera, View *view);
	bool isInFrustum(Vector3 center, float radius);

	float getHNear();
	float getWNear();
	float getHFar();
	float getWFar();
};

#endif