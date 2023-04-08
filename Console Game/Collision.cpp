#include "Collision.h"

Collision::Collision()
{

}

bool Collision::CheckCollision(int playerX, int playerY, std::vector<Tiles> tiles)
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