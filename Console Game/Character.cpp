#include "Character.h"

void Character::GetDirection(int playerX, int playerY, int oldX, int oldY)
{
	if (playerX == oldX && playerY == oldY)
	{
		std::cout << "Player is not moving.\n";
	}
	else if (playerX == oldX && playerY < oldY)
	{
		std::cout << "Player is moving up.\n";
	}
	else if (playerX == oldX && playerY > oldY)
	{
		std::cout << "Player is moving down.\n";
	}
	else if (playerY == oldY && playerX < oldX)
	{
		std::cout << "Player is moving left.\n";
	}
	else if (playerY == oldY && playerX > oldX)
	{
		std::cout << "Player is moving right.\n";
	}
}

void Character::Movement(Character::Direction choice, Map& map)
{
	switch (choice)
	{
	case Direction::UP:
		if (mPosY)
		{
			const auto oldY{ mPosY-- }; //This

			map.Update(mPosX, oldY, mPosX, mPosY, mCharacter);
			return;
		}
		break;

	case Direction::DOWN:
		if (mPosY < map.GetMaxRows() - 1)
		{
			const auto oldY{ mPosY++ };

			map.Update(mPosX, oldY, mPosX, mPosY, mCharacter);
			return;
		}
		break;

	case Direction::LEFT:
		if (mPosX)
		{
			const auto oldX{ mPosX-- };

			map.Update(oldX, mPosY, mPosX, mPosY, mCharacter);
			return;
		}
		break;

	case Direction::RIGHT:
		if (mPosX < map.GetMaxColumns() - 1)
		{
			const auto oldX{ mPosX++ };

			map.Update(oldX, mPosY, mPosX, mPosY, mCharacter);
			return;
		}
		break;

	default:
		std::cout << "Invalid Input\n";
		return;
	}
}