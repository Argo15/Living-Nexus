#include "PerlinNoise.h"

float PerlinNoise::Noise(int x, int y, int random)
{
	int n = x + y * 57 + random * 131;
	n = (n<<13) ^ n;
	return (1.0f - ( (n * (n * n * 15731 + 789221) +
		1376312589)&0x7fffffff)* 0.000000000931322574615478515625f);
}

void PerlinNoise::SetNoise(float  *map)
{
	float temp[34][34];
	int random=rand() % 5000;

	for (int y=1; y<33; y++)
	{
		for (int x=1; x<33; x++)
		{
			temp[x][y] = 128.0f + Noise(x,  y,  random)*128.0f;
		}
	}
	for (int x=1; x<33; x++)
	{
		temp[0][x] = temp[32][x];
		temp[33][x] = temp[1][x];
		temp[x][0] = temp[x][32];
		temp[x][33] = temp[x][1];
	}
	temp[0][0] = temp[32][32];
	temp[33][33] = temp[1][1];
	temp[0][33] = temp[32][1];
	temp[33][0] = temp[1][32];

	for (int y=1; y<33; y++)
	{
		for (int x=1; x<33; x++)
		{
			float center = temp[x][y]/4.0f;
			float sides = (temp[x+1][y] + temp[x-1][y] + temp[x][y+1] + temp[x][y-1])/8.0f;
			float corners = (temp[x+1][y+1] + temp[x+1][y-1] + temp[x-1][y+1] + temp[x-1][y-1])/16.0f;

			map32[((x-1)*32) + (y-1)] = center + sides + corners;
		}
	}
}

float PerlinNoise::Interpolate(float x, float y, float  *map)
{
	int Xint = (int)x;
	int Yint = (int)y;

	float Xfrac = x - Xint;
	float Yfrac = y - Yint;
	int X0 = Xint % 32;
	int Y0 = Yint % 32;
	int X1 = (Xint + 1) % 32;
	int Y1 = (Yint + 1) % 32;
	float bot = map[X0*32 + Y0] + Xfrac * (map[X1*32 + Y0] - map[X0*32 + Y0]);
	float top = map[X0*32 + Y1] + Xfrac * (map[X1*32 +  Y1] - map[X0*32 + Y1]);

	return (bot + Yfrac * (top - bot));
}

void PerlinNoise::OverlapOctaves(float  *map32, float  *map256)
{
	for (int x=0; x<256*256; x++)
	{
		map256[x] = 0;
	}
	for (int octave=0; octave<4; octave++)
	{
		for (int x=0; x<256; x++)
		{
			for (int y=0; y<256; y++)
			{
				float scale = 1 / pow(2.0, 3-octave);
				float noise = Interpolate(x*scale, y*scale , map32);
				map256[(y*256) + x] += noise / pow(2.0, octave);
			}
		}
	}
}

void PerlinNoise::ExpFilter(float  *map)
{
  float cover = 20.0f;
  float sharpness = 0.95f;

  for (int x=0; x<256*256; x++)
  {
    float c = map[x] - (255.0f-cover);
    if (c<0)     c = 0;
    map[x] = 255.0f - ((float)(pow(sharpness, c))*255.0f);
  }
}

bool PerlinNoise::load(const char *name)
{
	srand ( time(NULL) );
	SetNoise(map32);
	OverlapOctaves(map32, map256);
	ExpFilter(map256);                   //Our cloud function  

	char texture[256][256][3];       //Temporary array to hold texture RGB values 

	for(int i=0; i<256; i++)       //Set cloud color value to temporary array
	{
		for(int j=0; j<256; j++) 
		{
			float color = map256[i*256+j]; 
			texture[i][j][0]=color;
			texture[i][j][1]=color;
			texture[i][j][2]=color;
		}
	}
                  
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, 256, 256, GL_RGB, GL_UNSIGNED_BYTE, texture);

	this->setName(string(name));

	return true;
}