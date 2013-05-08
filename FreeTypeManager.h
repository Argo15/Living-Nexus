#ifndef FREETYPEMANAGER_H
#define FREETYPEMANAGER_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include "FontTexture.h"

/*
 * Author: wcrane
 * Date: 5/8/2013
 *
 * Wrapper for the FreeType2 font library
 */
class FreeTypeManager 
{
private:
	static FreeTypeManager *m_pInstance;
	FontTexture *m_font;

	FreeTypeManager();
public:
	static FreeTypeManager *getInstance();

    void initialize();
	FontTexture *getFont();
};

#endif