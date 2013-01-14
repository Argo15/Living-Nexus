#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include <map>
#include "TgaTexture.h"
#include "PerlinNoise.h"
using namespace std;

class TextureManager 
{
private:
	static TextureManager *m_pInstance;
	map<string,Texture *> textures;

	TextureManager();
public:
	static TextureManager *getInstance();

    void Initialize();
	void LoadTexture(string filename);
	void BindTexture(string name);
	void DeleteTexture(string name);
	void DeleteAllTextures();

	Texture *getTexture(string name);
	map<string,Texture *> *getTextures();
};

#endif