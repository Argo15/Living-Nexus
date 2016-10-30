#include "FreeTypeManager.h"
#include "Logger.h"

FreeTypeManager localFontManager;
FontManager *gFontManager = &localFontManager;

FreeTypeManager::FreeTypeManager()
{
	
}

void FreeTypeManager::initialize()
{
	FT_Library library;
	FT_Error error = FT_Init_FreeType( &library );
	if ( error )
	{
		Logging::GRAPHICS->error("error occurred during FreeType library initialization");
		return;
	}

	m_font = new FontTexture();
	m_font->load("Data/Fonts/Arial.ttf", library, 64);

	FT_Done_FreeType(library);
}

FontTexture *FreeTypeManager::getFont()
{
	return m_font;
}