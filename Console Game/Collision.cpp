#include "Collision.h"

Collision::Collision()
{

}

//This does not yet check for map bound collision
bool Collision::CheckCollision(int playerX, int playerY, const std::vector<Tiles>& tiles)
{
    std::cout << "DEBUG - Inside Collision::CheckCollision Function\n";
    for (auto& i : tiles)
    {
        std::cout << "DEBUG - Inside Collision::CheckCollision 1st For Loop\n";
        if (playerX == i.GetXPosition() || playerY == i.GetYPosition())
        {
            std::cout << "DEBUG - Inside Collision::CheckCollision 2nd For Loop\n";
            std::cout << "Collision Detected\n";
            return true;
        }
    }
    return false;
}