#include "Enemy.h"

void Enemy::Move(std::mt19937& mt, Map& map)
{
	//Randomize directions
	std::uniform_int_distribution<> moveEnemy{ 1, 4 };

	Movement(static_cast<Character::Direction>(moveEnemy(mt)), map);
}