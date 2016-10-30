#ifndef FREETYPEMANAGER_H
#define FREETYPEMANAGER_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include "FontTexture.h"
#include "FontManager.h"

/*
 * Author: wcrane
 * Date: 5/8/2013
 *
 * Wrapper for the FreeType2 font library
 */
class FreeTypeManager : public FontManager
{
private:
	FontTexture *m_font;

public:
	FreeTypeManager();

    void initialize();
	FontTexture *getFont();
};

extern FontManager *gFontManager;

#endif