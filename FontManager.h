#ifndef FONTMANAGER_H
#define FONTMANAGER_H

class FontManager
{
public:
	virtual void initialize() = 0;
	virtual FontTexture *getFont() = 0;
};

extern FontManager *gFontManager;

#endif