#include "FontTexture.h"
#include "Logger.h"

FontTexture::FontTexture()
{
}

///This function gets the first power of 2 >= the
///int that we pass it.
inline int next_p2 ( int a )
{
	int rval=1;
	while(rval<a) rval<<=1;
	return rval;
}

void FontTexture::buildTexture(FT_Face face, char ch)
{
	if(FT_Load_Glyph( face, FT_Get_Char_Index( face, ch ), FT_LOAD_DEFAULT ))
	{
		Logging::GRAPHICS->error("FT_Load_Glyph failed");
	}

	FT_Glyph glyph;
    if(FT_Get_Glyph( face->glyph, &glyph ))
	{
		Logging::GRAPHICS->error("FT_Get_Glyph failed");
	}

	FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
    FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
	FT_Bitmap& bitmap=bitmap_glyph->bitmap;

	int width = next_p2( bitmap.width );
	int height = next_p2( bitmap.rows );

	m_texData[ch].nLeft = bitmap_glyph->left;
	m_texData[ch].nTop = bitmap_glyph->top;
	m_texData[ch].nWidth = bitmap.width;
	m_texData[ch].nHeight = height;
	m_texData[ch].nAdvanceX = face->glyph->advance.x >> 6;
	m_texData[ch].nRows = bitmap.rows;
	m_texData[ch].x = (float)bitmap.width / (float)width;
	m_texData[ch].y = (float)bitmap.rows / (float)height;

	/*cout << (unsigned char)ch 
		<< ": " << m_texData[ch].nLeft
		<< " " << m_texData[ch].nTop
		<< " " << m_texData[ch].nWidth
		<< " " << m_texData[ch].nHeight
		<< " " << m_texData[ch].nAdvanceX
		<< " " << m_texData[ch].nRows
		<< " " << m_texData[ch].x
		<< " " << m_texData[ch].y << endl;*/


	GLubyte* expanded_data = new GLubyte[ 2 * width * height];

	for(int j=0; j <height;j++) {
		for(int i=0; i < width; i++){
			expanded_data[2*(i+j*width)]= expanded_data[2*(i+j*width)+1] = 
				(i>=bitmap.width || j>=bitmap.rows) ?
				0 : bitmap.buffer[i + bitmap.width*j];
		}
	}

	glBindTexture( GL_TEXTURE_2D, m_nTextureIds[ch]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		  0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data );
	delete [] expanded_data;
}

bool FontTexture::load(const char *sFilename, FT_Library library, int size)
{
	FT_Face face;
	FT_Error error = FT_New_Face(library, sFilename, 0, &face );
	if ( error )
	{
		Logging::GRAPHICS->error("error occurred creating font. " + string(sFilename));
		return false;
	}
	
	error = FT_Set_Char_Size(
            face,		/* handle to face object           */
            0,			/* char_width in 1/64th of points  */
            size*64,	/* char_height in 1/64th of points */
            96,			/* horizontal device resolution    */
            96 );		/* vertical device resolution      */
	
	nSize = size;

	if ( error )
	{
		Logging::GRAPHICS->error("error setting font size. " + string(sFilename));
		return false;
	}

	glGenTextures(128, m_nTextureIds);
	for(unsigned char i=0;i<128;i++)
	{
		buildTexture(face,i);
	}

	FT_Done_Face(face);

	return true;
}

void FontTexture::use(char ch)
{
	glBindTexture(GL_TEXTURE_2D, m_nTextureIds[ch]);
}

void FontTexture::remove()
{
	 glDeleteTextures(128,m_nTextureIds);
}

void FontTexture::draw(char ch, float nX1, float nY1, float nX2, float nY2)
{
	use(ch);
	glBegin(GL_QUADS);
		glTexCoord2f(0,	0);								glVertex2f(nX1,nY2);
		glTexCoord2f(0,	m_texData[ch].y);				glVertex2f(nX1,nY1);
		glTexCoord2f(m_texData[ch].x, m_texData[ch].y);	glVertex2f(nX2,nY1);
		glTexCoord2f(m_texData[ch].x, 0);				glVertex2f(nX2,nY2);
	glEnd();
}

void FontTexture::draw(string sPhrase, float nX1, float nY1, float nHeight)
{
	float nCurX = nX1;
	for (int i=0; i<sPhrase.length(); i++)
	{
		char ch = sPhrase[i];
		float leftOffset = nHeight * ((float)m_texData[ch].nLeft/(float)nSize);
		float fontWidth = nHeight * ((float)m_texData[ch].nWidth/(float)nSize);

		float bottom = nY1-nHeight*((m_texData[ch].nRows-m_texData[ch].nTop)/(float)nSize);
		float fontHeight = nHeight*((m_texData[ch].nRows)/(float)nSize);

		draw(sPhrase[i], nCurX+leftOffset, bottom, nCurX+leftOffset+fontWidth, bottom+fontHeight);
		nCurX += nHeight*(float)m_texData[ch].nAdvanceX/(float)nSize;
	}
}

int FontTexture::getSize()
{
	return nSize;
}

float FontTexture::getPhraseWidth(string sPhrase, float nStartX, float nHeight)
{
	float nCurWidth = nStartX;
	for (int i=0; i<sPhrase.length(); i++)
	{
		nCurWidth += nHeight*(float)m_texData[sPhrase[i]].nAdvanceX/(float)nSize;
	}
	return nCurWidth;
}