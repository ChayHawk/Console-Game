#ifndef COLLISION_H
#define COLLISION_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "Tiles.h"
#include "Map.h"

class Map;

class Collision
{
	public:
		Collision();

		bool CheckCollision(int playerX, int playerY, const Map& map, const std::vector<std::pair<int, int>>& tileCoords);
};

#endif