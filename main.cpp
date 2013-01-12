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
#include "TextureManager.h"y

int currentTime = 0;
int vsync = 0;
int sizeX = 0;
int sizeY = 0;
int counter = 0;

void init() {
	Config::getInstance();

	TextureManager::getInstance()->Initialize();
	ModelManager::getInstance()->Initialize();
	MaterialManager::getInstance()->Initialize();
	ShaderManager::getInstance()->Initialize();	

	UserSession::getInstance()->startUserSession("Argo");

	GameState::GAMESTATE = new WorldState();
}

void resize(int w, int h) {
	GameState::GAMESTATE->resize(w,h);
	sizeX = w;
	sizeY = h;
}

void render(void) {
	int lastTime = currentTime;
	currentTime = glutGet( GLUT_ELAPSED_TIME );
	int elapsedTime = currentTime - lastTime;
	vsync += elapsedTime;
	
	if (vsync > (1000/60)){
		TimeManager::getInstance()->tick();
		float fps = 1000.0f/elapsedTime;
		if (fps > 60)
			fps=60;
		vsync = 0;

		char buffer[5];
		_itoa((int)fps, buffer, 10);
		string title = string("Living Nexus - FPS: ") + string(buffer);
		glutSetWindowTitle(title.c_str());
		
		GameState::GAMESTATE->tick((int)fps);
		counter++;
	}
	
}

void keyDown(unsigned char key, int xx, int yy) {
	if (key == 27) { 
		UserSession::getInstance()->endUserSession();
		Profiler::getInstance()->logProfile();
		exit(0);
	}
	InputManager::getInstance()->registerKeyDown((int)key);
	if (key >= '1' && key <= '9') 
		RenderStateManager::RENDERSTATE = (RenderState)((int)key-(int)'0');
}

void keyUp(unsigned char key, int xx, int yy) {
	InputManager::getInstance()->registerKeyUp((int)key);
}

void mousePress(int button, int state, int x, int y) {
	if (state == GLUT_DOWN)
		InputManager::getInstance()->registerMouseButtonDown(button);
	else
		InputManager::getInstance()->registerMouseButtonUp(button);
}

void mousePressedMove(int x, int y) {
	InputManager::getInstance()->setMousePosition(x,y);
}

void mouseReleasedMove(int x, int y) {
	InputManager::getInstance()->setMousePosition(x,y);
}

void specialKeyDown(int key, int xx, int yy)
{

}

void mouseWheel(int button, int dir, int x, int y)
{
}

int main(int argc, char **argv) {
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(300,0);
	glutInitWindowSize(1600,900);
	glutCreateWindow("Living Nexus");

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
