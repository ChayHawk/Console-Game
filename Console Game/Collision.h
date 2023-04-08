#ifndef COLLISION_H
#define COLLISION_H

#include <vector>
#include <iostream>
#include "Tiles.h"

class Collision
{
	public:
		Collision();

		bool CheckCollision(int playerX, int playerY, const std::vector<Tiles>& tiles);
};

#endif