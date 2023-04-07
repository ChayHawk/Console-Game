#include "Character.h"

void Character::GetDirection(const Map& map)
{
	std::cout << mPosY << " " << mPosY + 1;
	if (mPosY < map.GetMaxColumns())
	{
		std::cout << "Moving Up\n";
	}
	else if (mPosY > mPosY - 1)
	{
		std::cout << "Moving Down\n";
	}
	else if (mPosX == mPosX - 1)
	{
		std::cout << "Moving Left\n";
	}
	else if (mPosX == mPosX + 1)
	{
		std::cout << "Moving Right\n";
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