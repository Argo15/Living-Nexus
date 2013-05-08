#include "FreeTypeManager.h"
#include "Logger.h"

FreeTypeManager* FreeTypeManager::m_pInstance = 0;

FreeTypeManager::FreeTypeManager()
{
	
}

FreeTypeManager *FreeTypeManager::getInstance()
{
	if (m_pInstance == 0)
	{
		m_pInstance = new FreeTypeManager();
	}
	return m_pInstance;
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
	m_font->load("Data/Fonts/ArialBlack.ttf", library, 64);

	FT_Done_FreeType(library);
}

FontTexture *FreeTypeManager::getFont()
{
	return m_font;
}