#include "Collision.h"

Collision::Collision()
{

}

bool Collision::CheckCollision(int playerX, int playerY, const Map& map, const std::vector<std::pair<int, int>>& tileCoords)
{
    // Check if the new position is outside the map boundaries
    if (playerX < 0 || playerX >= map.GetMaxColumns() || playerY < 0 || playerY >= map.GetMaxRows())
    {
        return true;
    }

    // Check if the new position collides with any tiles
    for (const auto& coord : tileCoords)
    {
        //There was an issue where the playerX and playerY below were swapped which caused
        //the player to not collide with the corrisponding object but would hit random 
        //collision spots where there was nothing. 
        //need to remember to be consistent with coordinate order!
        if (playerY == coord.first && playerX == coord.second)
        {
            return true;
        }
    }

    return false;
}