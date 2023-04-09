#include "Collision.h"

Collision::Collision()
{

}

//This does not yet check for map bound collision
//This doesw not get the positions of the randomized obects placed on the screen yet.
//bool Collision::CheckCollision(int playerX, int playerY, const std::vector<Tiles>& tiles)
//{
//    for (auto& i : tiles)
//    {
//        if (playerX == i.GetXPosition() && playerY == i.GetYPosition())
//        {
//            std::cout << "Collision Detected\n";
//            return true;
//        }
//    }
//    return false;
//}

//bool Collision::CheckCollision(int playerX, int playerY, const std::vector<std::pair<int, int>>& tileCoords)
//{
//    for (const auto& coord : tileCoords)
//    {
//        if (playerX == coord.first && playerY == coord.second)
//        {
//            std::cout << "Collision Detected\n";
//            return true;
//        }
//    }
//    return false;
//}

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
        if (playerX == coord.first && playerY == coord.second)
        {
            return true;
        }
    }

    return false;
}

//bool Collision::CheckCollision(int playerX, int playerY, const std::vector<Tiles>& tiles) 
//{
//    return std::ranges::any_of(tiles, [playerX, playerY](const auto& t) {return t.GetXPos() == playerX || t.GetYPos() == playerY; });
//}