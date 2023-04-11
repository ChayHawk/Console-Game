#include "Enemy.h"

void Enemy::Move(std::mt19937& mt, Map& map)
{
    // Randomize directions
    std::uniform_int_distribution<> moveEnemy{ 0, 3 };
    std::array<char, 4> directions = { 'w', 's', 'a', 'd' };

    // Pass the randomly selected direction as a char to the Movement function
    Movement(directions[moveEnemy(mt)], map);
}