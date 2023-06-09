#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <chrono>
#include <array>

#include "Map.h"
#include "Character.h"

class Enemy : public Character
{
	public:
		Enemy(const std::string& name, char character, int posX, int posY) : Character{ name, character, posX, posY }
		{}

		void Move(std::mt19937& mt, Map& map);

	private:
		Collision collision;
};

#endif