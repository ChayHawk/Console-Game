#include "Character.h"

void Character::GetDirection(int playerY, int playerX, int oldY, int oldX)
{
	if (playerY == oldY && playerX == oldX)
	{
		std::cout << "Player is not moving.\n";
	}
	else if (playerY < oldY && playerX == oldX)
	{
		std::cout << "Player is moving up.\n";
	}
	else if (playerY > oldY && playerX == oldX)
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

void Character::Movement(char choice, Map& map)
{
	switch (choice)
	{
		case 'w':
			if (collision.CheckCollision(mPosX, mPosY - 1, map, map.GetTileCoords()))
			{
				std::cout << "Cannot move Up.\n";
			}
			else
			{
				const auto oldY{ mPosY-- };

				map.Update(mPosX, oldY, mPosX, mPosY, mCharacter);
				return;
			}
			break;

		case 's':
			if (collision.CheckCollision(mPosX, mPosY + 1, map, map.GetTileCoords()))
			{
				std::cout << "Cannot move Down.\n";
			}
			else
			{
				const auto oldY{ mPosY++ };

				map.Update(mPosX, oldY, mPosX, mPosY, mCharacter);
				return;
			}
			break;

		case 'a':
			if (collision.CheckCollision(mPosX - 1, mPosY, map, map.GetTileCoords()))
			{
				std::cout << "Cannot move Left.\n";
			}
			else
			{
				const auto oldX{ mPosX-- };

				map.Update(oldX, mPosY, mPosX, mPosY, mCharacter);
				return;
			}
			break;

		case 'd':
			if (collision.CheckCollision(mPosX + 1 , mPosY, map, map.GetTileCoords()))
			{
				std::cout << "Cannot move Right.\n";
			}
			else
			{
				const auto oldX{ mPosX++ };

				map.Update(oldX, mPosY, mPosX, mPosY, mCharacter);
				return;
			}
			break;

		case 'p':
			//Add code to handle finding hidden treasure
			break;
		default:
			std::cout << "Error\n";
	}
}