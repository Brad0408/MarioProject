#pragma once
#ifndef _LEVELMAP_H
#define _LEVELMAP_H

#include "constants.h"
#include <iostream>
#include <fstream>

using namespace std;

class LevelMap
{

public:
	LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();

	int GetTileAt(unsigned int h, unsigned int w);

	void ChangeTileAt(unsigned int row, unsigned int column, unsigned int new_value);

private:
	int** m_map;

};

#endif