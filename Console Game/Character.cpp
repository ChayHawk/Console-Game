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

void Character::Movement(Character::Direction choice, Collision& collision, Map& map)
{
	switch (choice)
	{
		case Direction::UP:
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

		case Direction::DOWN:
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

		case Direction::LEFT:
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

		case Direction::RIGHT:
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

		default:
			std::cout << "Error\n";
	}
}