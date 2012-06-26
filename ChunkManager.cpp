#include "ChunkManager.h"
#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<string.h>
#include<fstream>
#include "dirent.h"

ChunkManager::ChunkManager()
{
	
}

void ChunkManager::Initialize()
{
	DIR *pDIR;
	struct dirent *entry;
	if( pDIR=opendir("./Data/Chunks") ){
		while(entry = readdir(pDIR)){
			if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
				LoadChunk(string("./Data/Chunks/") + entry->d_name);
		}
		closedir(pDIR);
	}
}

void ChunkManager::LoadChunk(string filename)
{
	Chunk *chunk = new Chunk();
	if (chunk->loadChunk(filename)) {
		int start_pos = filename.rfind("/")+1;
		int end_pos = filename.rfind(".");
		string name = filename.substr(start_pos,end_pos-start_pos);
		chunk->setName(name);
		chunks[name]=chunk;
	}
}

void ChunkManager::DrawChunk(string name, string shader)
{
	chunks[name]->drawChunk(shader);
}

void ChunkManager::DeleteChunk(string name)
{
	if (chunks.find(name) == chunks.end()){
		delete chunks[name];
		chunks.erase(name);
	}
}

void ChunkManager::DeleteAllChunks()
{
	chunks.clear();
}