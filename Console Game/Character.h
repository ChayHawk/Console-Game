#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <string>

#include "Map.h"
#include "Collision.h"

class Map;
class Collision;

class Character
{
	public:
		Character(const std::string& name, char character, int posX, int posY) : mName(name), mCharacter(character), mPosX(posX), mPosY(posY) {}

		enum class Direction
		{
			UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4
		};

		int GetXPosition() const { return mPosX; }
		int GetYPosition() const { return mPosY; }
		char GetCharacter() const { return mCharacter; }
		std::string GetName() const { return mName; }

		void Movement(Character::Direction choice, Collision& collision, Map& map, std::vector<Tiles> tiles);

		void GetDirection(int playerX, int playerY, int oldX, int oldY);

	private:
		std::string mName{ "Character" };
		const char mCharacter{ 'C' };
		int mPosX{ };
		int mPosY{ };
};

#endif