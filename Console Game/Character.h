#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <string>

#include "Collision.h"
#include "Map.h"

class Map;

class Character
{
	public:
		Character(const std::string& name, char character, int posX, int posY) : 
			mName(name), mCharacter(character), mPosX(posX), mPosY(posY) {}

		int GetXPosition() const { return mPosX; }
		int GetYPosition() const { return mPosY; }
		char GetCharacter() const { return mCharacter; }
		std::string GetName() const { return mName; }

		void Movement(char choice, Map& map);

		void GetDirection(int playerX, int playerY, int oldX, int oldY);

	private:
		std::string mName{ "Character" };
		const char mCharacter{ 'C' };
		int mPosX{ };
		int mPosY{ };
		Collision collision;
};

#endif