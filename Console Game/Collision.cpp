#include "Collision.h"

Collision::Collision()
{

}

//This does not yet check for map bound collision
//This doesw not get the positions of the randomized obects placed on the screen yet.
bool Collision::CheckCollision(int playerX, int playerY, const std::vector<Tiles>& tiles)
{
    for (auto& i : tiles)
    {
        if (playerX == i.GetXPosition() && playerY == i.GetYPosition())
        {
            std::cout << "Collision Detected\n";
            return true;
        }
    }
    return false;
}

//bool Collision::CheckCollision(int playerX, int playerY, const std::vector<Tiles>& tiles) 
//{
//    return std::ranges::any_of(tiles, [playerX, playerY](const auto& t) {return t.GetXPos() == playerX || t.GetYPos() == playerY; });
//}