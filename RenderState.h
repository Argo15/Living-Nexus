#ifndef RENDER_STATE_H
#define RENDER_STATE_H

enum RenderState
{
	FORWARD, 
	FINAL, 
	POSITION, 
	NORMALMAP, 
	COLOR, 
	LIGHTING, 
	SSAO, 
	SPECULAR,
	MOTION
};

/*
 * Author: wcrane
 * Date: 3/15/2013
 *
 * Global that tells which screen to display to the user.
 */
class RenderStateManager
{
public:
	static RenderState RENDERSTATE;
};

#endif