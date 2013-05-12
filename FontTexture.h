#ifndef FONTTEXTURE_H
#define FONTTEXTURE_H

#include <windows.h>
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/glee.h>
#include <string>
#include <iostream>
#include <ft2build.h>
#include <freetype/ftglyph.h>
#include FT_FREETYPE_H
using namespace std;

struct FontTextureData
{
	int nLeft;
	int nTop;
	int nAdvanceX;
	int nRows;
	int nWidth;
	int nHeight;
	float x;
	float y;
};

class FontTexture
{
protected:
	GLuint m_nTextureIds[128];
	FontTextureData m_texData[128];
	int nSize;

	void buildTexture(FT_Face face, char ch);

public:
	FontTexture();

	bool load(const char *sFilename, FT_Library library, int size);
	void use(char ch);
	void remove();
	void draw(char ch, float nX1, float nY1, float nX2, float nY2);
	void draw(string sPhrase, float nX1, float nY1, float nHeight);
	
	int getSize();
	float getPhraseWidth(string sPhrase, float nStartX, float nHeight);
};


#endif