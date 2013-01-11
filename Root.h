#ifndef ROOT_H
#define ROOT_H
#include "GameState.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "MaterialManager.h"
#include "InputManager.h"
#include "ShaderManager.h"

class Root {
public:
	static stack<glm::mat4> ModelviewMatrix;
	static stack<glm::mat4> ProjectionMatrix;
	static stack<glm::mat3> NormalMatrix;
};

#endif