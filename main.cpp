#include <algorithm>
#include <stdlib.h>
#include <windows.h>
#include <GL/freeglut.h>
#include "WorldState.h"
#include "TimeManager.h"
#include "Config.h"
#include "Profiler.h"
#include "UserSession.h"
#include "RenderState.h"
#include "GameState.h"
#include "InputManager.h"
#include "MaterialManager.h"
#include "TextureManager.h"

int nCurrentTime = 0;
int nVsync = 0;
int nSizeX = 0;
int nSizeY = 0;

int nSumFps = 0;
int nCounter = 10;

void init() 
{
	Config::getInstance();

	TextureManager::getInstance()->initialize();
	ModelManager::getInstance()->initialize();
	MaterialManager::getInstance()->initialize();
	ShaderManager::getInstance()->initialize();	

	UserSession::getInstance()->startUserSession("Argo");

	GameState::GAMESTATE = new WorldState();
}

void resize(int nWidth, int nHeight) 
{
	GameState::GAMESTATE->resize(nWidth, nHeight);
	nSizeX = nWidth;
	nSizeY = nHeight;
}

void render(void) 
{
	int nLastTime = nCurrentTime;
	nCurrentTime = glutGet( GLUT_ELAPSED_TIME );
	int nElapsedTime = nCurrentTime - nLastTime;
	nVsync += nElapsedTime;
	
	if (nVsync > 0*(1000/60))
	{
		TimeManager::getInstance()->tick();
		int nFps = 1000/nElapsedTime;
		if (nFps > 60)
		{
			nFps=60;
		}
		nVsync = 0;

		nSumFps+=nFps;
		nCounter++;
		if (nCounter >= 60)
		{
			char buffer[5];
			_itoa((int)nSumFps/nCounter, buffer, 10);
			string title = string("LiNex - FPS: ") + string(buffer);
			glutSetWindowTitle(title.c_str());
			nCounter = 0;
			nSumFps = 0;
		}
		
		GameState::GAMESTATE->tick((int)nFps);
	}
	
}

void keyDown(unsigned char key, int xx, int yy) 
{
	if (key == 27) 
	{ 
		UserSession::getInstance()->endUserSession();
		Profiler::getInstance()->logProfile();
		exit(0);
	}
	InputManager::getInstance()->registerKeyDown((int)key);
	if (key >= '1' && key <= '9') 
	{
		RenderStateManager::RENDERSTATE = (RenderState)((int)key-(int)'0');
	}
}

void keyUp(unsigned char key, int xx, int yy) 
{
	InputManager::getInstance()->registerKeyUp((int)key);
}

void mousePress(int button, int state, int x, int y) 
{
	if (state == GLUT_DOWN)
	{
		InputManager::getInstance()->registerMouseButtonDown(button);
	}
	else
	{
		InputManager::getInstance()->registerMouseButtonUp(button);
	}
}

void mousePressedMove(int x, int y) 
{
	InputManager::getInstance()->setMousePosition(x,y);
}

void mouseReleasedMove(int x, int y) 
{
	InputManager::getInstance()->setMousePosition(x,y);
}

void specialKeyDown(int key, int xx, int yy)
{

}

void mouseWheel(int button, int dir, int x, int y)
{
}

int main(int argc, char **argv) 
{
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(300,0);
	glutInitWindowSize(1600,900);
	glutCreateWindow("LiNex");

	// register callbacks
	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutIdleFunc(render);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(specialKeyDown);
	glutMouseFunc(mousePress);
	glutMotionFunc(mousePressedMove);
	glutPassiveMotionFunc(mouseReleasedMove);

	// enter GLUT event processing cycle
	init();
	glutMainLoop();

	return 1;
}
