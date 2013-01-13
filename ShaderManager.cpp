#include "ShaderManager.h"
#include <assert.h>
#include "Logger.h"

ShaderManager* ShaderManager::m_pInstance = 0;

ShaderManager::ShaderManager()
{

}

ShaderManager *ShaderManager::getInstance() 
{
	if (m_pInstance == 0) 
	{
		m_pInstance = new ShaderManager();
	}
	return m_pInstance;
}

void ShaderManager::compileProgram(GLSLProgram *program, string shaderName)
{
	std::string log;
	if (!program->vertex_->isCompiled())
	{
		program->vertex_->getShaderLog(log);
		Logging::GRAPHICS->error("Vertex shader failed to compile: " + shaderName + "\n" + log);
	}
	if (!program->fragment_->isCompiled())
	{	
		program->fragment_->getShaderLog(log);
		Logging::GRAPHICS->error("Fragment shader failed to compile " + shaderName + "\n" + log);
	}
}

void ShaderManager::Initialize()
{
	Logging::GRAPHICS->info("Loading Shaders");
	LoadShader("Basic", "Data/Shaders/v_material.glsl","Data/Shaders/f_material.glsl");
	LoadShader("GBuffer", "Data/Shaders/v_GBuffer.glsl","Data/Shaders/f_GBuffer.glsl");
	LoadShader("DirectLight", "Data/Shaders/v_light.glsl","Data/Shaders/f_dlight.glsl");
	LoadShader("Final", "Data/Shaders/v_final.glsl","Data/Shaders/f_final.glsl");
	LoadShader("SunShadow", "Data/Shaders/v_dShadow.glsl","Data/Shaders/f_dShadow.glsl");
	LoadShader("MotionBlur", "Data/Shaders/v_motionBlur.glsl","Data/Shaders/f_motionBlur.glsl");
	LoadShader("Atmosphere", "Data/Shaders/v_motionBlur.glsl","Data/Shaders/f_atmosphere.glsl");
	Logging::GRAPHICS->info("Done Loading Shaders");
}

void ShaderManager::LoadShader(string name, string vertexShader, string fragmentShader)
{
	GLSLProgram *glslProgram = new GLSLProgram(vertexShader,fragmentShader);
	compileProgram(glslProgram, name);
	shaders[name] = glslProgram;
}

void ShaderManager::UseShader(string name)
{
	shaders[name]->use();
}

void ShaderManager::DisableShader(string name)
{
	shaders[name]->disable();
}

void ShaderManager::DeleteShader(string name)
{
	delete shaders[name];
}

void ShaderManager::DeleteAllShaders()
{
	shaders.clear();
}
