#ifndef OBJECT_H
#define OBJECT_H

#include <string>
using namespace std;

/*
 * Author: wcrane
 * Date: 7/14/2012
 * Generic object that can be placed in your inventory, placed on the ground, or placed in the world/house as an interactive object.
 */
class Object
{
private:
	string m_sName;

	string m_sWorldTile;
	string m_sInventoryTexture;
	string m_sGroundTile;

public:
	Object(string sName = "");

	std::string getWorldTile();
	void setWorldTile(std::string sTile);

	std::string getInventoryTexture();
	void setInventoryTexture(std::string sTexture);

	std::string getGroundTile();
	void setGroundTile(std::string sTile);

	string getName();
	void setName(string sName);
};

#endif