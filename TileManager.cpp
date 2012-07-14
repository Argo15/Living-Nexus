#include "TileManager.h"
#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<string.h>
#include<fstream>
#include "dirent.h"
#include "Logger.h"

TileManager::TileManager()
{
	
}

void TileManager::Initialize()
{
	Logging::GRAPHICS->info("Loading Tiles");
	DIR *pDIR;
	struct dirent *entry;
	if( pDIR=opendir("./Data/Tiles") ){
		while(entry = readdir(pDIR)){
			if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
				LoadTile(string("./Data/Tiles/") + entry->d_name);
		}
		closedir(pDIR);
	}
	Logging::GRAPHICS->info("Done Loading Tiles");
}

void TileManager::LoadTile(string filename)
{
	Tile *tile = new Tile();
	if (tile->loadTile(filename)) {
		int start_pos = filename.rfind("/")+1;
		int end_pos = filename.rfind(".");
		string name = filename.substr(start_pos,end_pos-start_pos);
		tile->setName(name);
		tiles[name]=tile;
	} else {
		Logging::GRAPHICS->error("Tile failed to load: " + filename);
	}
}

void TileManager::DrawTile(string name, string shader)
{
	tiles[name]->drawTile(shader);
}

void TileManager::DeleteTile(string name)
{
	if (tiles.find(name) == tiles.end()){
		delete tiles[name];
		tiles.erase(name);
	}
}

void TileManager::DeleteAllTiles()
{
	tiles.clear();
}